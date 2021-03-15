#include "iostream"
#include<fstream>
#include<string>
#include<sstream>
#include<map>
#include<memory>
#include"Server.h"
#include"VisualMachine.h"
#include<vector>
#include"Scheduling.h"

using namespace std;


//服务器ID

int ser_id = 0;
//string path("data.txt");

/**********************************************************

函数：read_line
每次读取文件的一行到字符串str，并返回下一行的文件游标；
参数1：读取文件的流
参数2：缓冲区，用于存取一行的数据
参数3：文件读取的游标

**********************************************************/
void read_line(istream& line, string& str)
{

	//定位文件读取位置
	//line.seekg(start);
	getline(line, str);//读取文件test.txt的一行到temp
	//streamoff ret = line.tellg();
	//line.close();
	return ;
}


/**********************************************************

函数：Serv_info
	处理一条服务器信息，并将相应的信息存入到map中
参数1：字符串流，保存一条序列请求
参数2：保存所有可购入的服务器的map

**********************************************************/
void Serv_info(istringstream& out, map<string, shared_ptr<Server>>& SERpurcheable)
{

	shared_ptr<Server>temp = make_shared<Server>();

	string str;
	out >> str;
	str.pop_back();
	str.erase(0, 1);
	temp->setType(str);
	//cout << "服务器型号：" << temp->getType() << endl;
	out >> str;
	//str.pop_back();
	temp->setCPUCapacity(atoi(str.c_str()));
	temp->setPartACPULeft((temp->getCPUCapacity())/2);
	temp->setPartBCPULeft(temp->getPartACPULeft());
	//cout << "服务器CPU核数：" << temp->getCPUCapacity() << endl;
	out >> str;
	//str.pop_back();
	temp->setMemoryCapacity(atoi(str.c_str()));
	temp->setPartAMemoryLeft((temp->getMemoryCapacity())/2);
	temp->setPartBMemoryLeft(temp->getPartAMemoryLeft());
	//cout << "服务器内存：" << temp->getMemoryCapacity() << "GB" << endl;
	out >> str;
	//str.pop_back();
	temp->setHardwareCost(atoi(str.c_str()));
	//cout << "服务器硬件成本：" << temp->getHardwareCost() << endl;
	out >> str;
	//str.pop_back();
	temp->setDailyCost(atoi(str.c_str()));
	//cout << "服务器日能耗：" << temp->getDailyCost() << endl;

	SERpurcheable.emplace(temp->getType(), temp);

}



/**********************************************************

函数：VirM_info
	处理一条虚拟机信息，并将相应的信息存入到map中
参数1：字符串流，保存一条信息
参数2：保存所有可卖出的虚拟机的map

**********************************************************/
void VirM_info(istringstream& out, map<string, shared_ptr<VisualMachine>>& saleable)
{

	shared_ptr<VisualMachine>temp = make_shared<VisualMachine>();

	string str;
	out >> str;
	str.pop_back();
	str.erase(0, 1);
	temp->setType(str);
	//cout << "虚拟机型号：" << temp->getType() << endl;
	out >> str;
	//str.pop_back();
	temp->setCPUNeed(atoi(str.c_str()));
	//cout << "虚拟机CPU核数：" << temp->getCPUNeed() << endl;
	out >> str;
	//str.pop_back();
	temp->setMemoryNeed(atoi(str.c_str()));
	//cout << "虚拟机内存：" << temp->getMemoryNeed() << "GB" << endl;
	out >> str;
	if (atoi(str.c_str())) {
		temp->setNodeType(atoi(str.c_str()));
		//str = "双节点";
	}
	else {
		temp->setNodeType(atoi(str.c_str()));
		//str = "单节点";
	}
	//cout << "节点部署方式：" << str << " " << temp->getNodeType() << endl;

	saleable.emplace(temp->getType(), temp);
}




/**********************************************************

函数：Request_info
	处理一条请求序列，并完成相应的动作，即删除或者添加虚拟机
参数1：字符串流，保存一条序列请求
参数2：

**********************************************************/
void Request_info(istringstream& out, Scheduling & sch, map<string, shared_ptr<VisualMachine>> &VMsaleable,
	map<int, shared_ptr<VisualMachine>> &DeployedVM, map<int, shared_ptr<Server>> &BoughtServ)
{
	string str;
	string type;
	int ID;
	out >> str;
	str.pop_back();
	str.erase(0, 1);
	//请求序列
	if (str == "add") {
		//cout << "请求添加虚拟机" << "  ";
		out >> type;
		type.pop_back();
		//cout << "型号：" << type << "  ";
		out >> str;
		ID = atoi(str.c_str());
		//cout << "ID：" << ID << endl;

		//添加虚拟机, ID ,type

		sch.addVM(BoughtServ,DeployedVM,VMsaleable,type,ID);

	}
	else if (str == "del") {
		//cout << "请求删除虚拟机" << "  ";
		out >> str;
		//str.pop_back();
		ID = atoi(str.c_str());
		//cout << "ID：" << ID << endl;

		sch.delVM(BoughtServ, DeployedVM, ID);

	}
}



/**********************************************************

函数：PurchaseServer
	该函数用于再适当的时候购买服务器
参数1：可购买的服务器的列表
参数2：已经购买的服务器的列表
参数3：购买的服务器CPU需求
参数4: 购买的服务器内存需求

**********************************************************/
void PurchaseServer( map< string, shared_ptr< Server > >& SERpurcheable , map< int, shared_ptr< Server > >& BoughtServ,
					int CPUneed,int Memoryneed)
{
	int LeftCpu = 0;
	int LeftMem = 0;
	int count = ser_id;
	//当没有购买任何服务器则先购买一台
	if (BoughtServ.empty()) {
		auto temp = (*(SERpurcheable.begin()->second));
		auto temp_ptr = make_shared<Server>(temp);
		temp_ptr->setServerId(ser_id);
		BoughtServ[ser_id++] = temp_ptr;
	}


	//统计剩余服务器中有多少的剩余
	for (auto it: BoughtServ) {
		
		LeftCpu += it.second->getPartACPULeft();
		LeftCpu += it.second->getPartBCPULeft();
		LeftMem += it.second->getPartAMemoryLeft();
		LeftMem += it.second->getPartBMemoryLeft();
	
	}

	//接下来买服务器
	int deltaCPU = CPUneed - LeftCpu;
	int deltaMem = Memoryneed - LeftMem;

	//目前购买策略并没完善，先买一台的方式进行处理。
	/*for (auto it : SERpurcheable) {
		
		
	}*/
	

	//要购买的台数
	int nums = 0;
	auto temp =(*(SERpurcheable.begin()->second));//temp为选定的要买的服务器对象
	int c=deltaCPU / temp.getCPUCapacity();
	int m = deltaMem / temp.getMemoryCapacity();
	m < c ? nums = c + 1: nums = m+1;

	for (int i=0;i<nums-1;i++)
	{
		auto temp_ptr = make_shared<Server>(temp);
		temp_ptr->setServerId(ser_id);
		BoughtServ[ser_id++] = temp_ptr;
	}
	
	//cout << "********购买***********" << endl;
	//输出购买的台数
	cout << "(purchase, " << ser_id - count << ")" << endl;

	if(ser_id - count!=0)
		cout << "(" << BoughtServ[count]->getType() << "," << ser_id - count << ")" << endl;
}



/**********************************************************

函数：QuestNeed
	该函数用于求出一条序列的请求的容量
参数1：字符串流，存放一条序列
参数2：可以出售的虚拟机列表
参数3：一条序列的CPU需求
参数4: 一条序列内存需求

**********************************************************/
void QuestNeed(istringstream &out, map<string, shared_ptr<VisualMachine>> & VMsaleable,
				int * cpu, int * memory)
{
	string str;
	string type;
	out >> str;
	str.pop_back();
	str.erase(0, 1);
	//返回一天的所有请求
	if (str == "add") {
		//cout << "请求添加虚拟机" << "  ";
		out >> type;
		type.pop_back();
		//cout << "型号：" << type << "  ";
		*(cpu)+=(*VMsaleable[type]).getCPUNeed();
		*(memory) += (*VMsaleable[type]).getMemoryNeed();
	}
	return ;
}


/**********************************************************

函数：Day_task
该函数用于完成一天的任务，包括对每条序列的相应，以及数据的输入
参数1：文件流，逐条读取信息
参数2：读取文件的位置
参数3：可以出售的虚拟机
参数4 : 可买入的服务器
参数5：已经买入的服务器

* *********************************************************/

void Day_task(istream& line, map<string, shared_ptr<VisualMachine>> &VMsaleable,
	              map< string, shared_ptr< Server > >& SERpurcheable, map< int, shared_ptr< Server > >& BoughtServ,
					map<int, shared_ptr<VisualMachine>> &DeployedVM)
{
	//info中存放一天的信息，包括所有序列
	vector<string> info;
	//当天的CPU总需求
	int CPUneed = 0;
	//当天的内存需求
	int Memoryneed = 0;
	string str;
	read_line(line, str);

	//读取当天的所有序列，并做解析
	int n = atoi(str.c_str());
	//求和，保存信息
	for (int i = 0; i < n; i++) {

		read_line(line, str);
		//将每天的序列保存起来方便后续使用
		info.push_back(str);
		//
		istringstream out(str);
		QuestNeed(out, VMsaleable,&CPUneed,&Memoryneed);
		//istringstream out1(str);
		//Request_info(out1);
	}
	//cout << "*********CPU需求：" << CPUneed << " *********" << endl;
	//cout << "*********内存需求：" << Memoryneed << " *********" << endl;
	
	PurchaseServer(SERpurcheable,BoughtServ,CPUneed, Memoryneed);

	cout << "(migration, 0)" << endl;

	/*for (auto it : BoughtServ) {
		cout << "目前已购买的Id:" << it.second->getServerId() << "  型号：" << it.second->getType() << endl;
	}*/

	//处理数据

	for (int i = 0; i < info.size(); i++ ) {
		
		istringstream out(info[i]);
		Scheduling s;
		Request_info(out,s,VMsaleable,DeployedVM,BoughtServ);
	}

	

}

/**********************************************************
* 主函数
**********************************************************/



int main()
{
	// TODO:read standard input
	// TODO:process
	// TODO:write standard output
	// TODO:fflush(stdout);

	//Server s;


	//用于读取数据的流
	//ifstream reader(path);

	//目前可售卖的虚拟机的列表
	map<string, shared_ptr<VisualMachine>> VMsaleable;

	//可购入的服务器的种类
	map<string, shared_ptr<Server>> SERpurcheable;

	//用于表示已经部署的虚拟机,应该是再可购入的虚拟机中的某一台虚拟机对象
	//当添加虚拟机时，将可购入虚拟机中的某台虚拟机对象的引用传入到该map，
	//并设置相应的ID
	map<int, shared_ptr<VisualMachine>> DeployedVM;

	//用于表示买入的服务器，当买入该服务器时，便将该服务器的对象的引用传入到该map,
	//当删除或添加虚拟机时应该修改相应服务器的资源剩余。
	map<int, shared_ptr<Server>>BoughtServ;





	/*****************************************************************************

	这段代码用于读取可采购服务器的数量，以及对可采购服务器的信息的解析

	******************************************************************************/


	//读取可采购服务器种类数目
	string temp;
	read_line(cin, temp);
	//cout << temp << endl;

	//依次读取每台的服务器的信息，并解析信息的格式
	int n = atoi(temp.c_str());
	for (int i = 0; i < n; i++) {

		read_line(cin, temp);
		//cout << temp << endl;
		istringstream out(temp);
		Serv_info(out, SERpurcheable);

	}

	/*****************************************************************************

	这段代码用于读取可售卖虚拟机的数量，以及对可售卖虚拟机的信息的解析

	******************************************************************************/


	//读取可售卖的虚拟机的数目
	read_line(cin, temp);
	//cout << "可购买虚拟机种数： " <<temp << endl;

	//依次读取每台的虚拟机的信息，并解析信息的格式	
	n = atoi(temp.c_str());
	for (int i = 0; i < n; i++) {

		read_line(cin, temp);
		//cout << temp << endl;
		istringstream out(temp);
		VirM_info(out, VMsaleable);

	}

	/*for (auto it = VMsaleable.begin(); it != VMsaleable.end(); it++) {
		cout << it->first << " " << (it->second)->getCPUNeed() << endl;
	}*/

	/*****************************************************************************

	这段代码用于读取天数，以及对每天的数据序列的一个解析

	******************************************************************************/


	read_line(cin, temp);
	//cout << temp << endl;

	//依次读取每天的序列，并解析序列的格式	
	n = atoi(temp.c_str());
	//cout <<  n << "天的数据需要处理" << endl;
	for (int i = 0; i < n; i++) {

		Day_task(cin,VMsaleable,SERpurcheable,BoughtServ,DeployedVM);

	}

	return 0;
}
