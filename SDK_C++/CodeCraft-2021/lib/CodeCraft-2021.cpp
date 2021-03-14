#include "iostream"
#include<istream>
#include<fstream>
#include<string>
#include<sstream>
#include<map>
#include<memory>
#include"Server.h"
#include"VisualMachine.h"


using namespace std;

//streamoff read_line(ifstream&, string&, streamoff);
//void Serv_info(istringstream& out, map<string, shared_ptr<Server>> & SERpurcheable);
//void VirM_info(istringstream& out, map<string, shared_ptr<VisualMachine>> & saleable);
//void Request_info(istringstream& out);
//streamoff Day_task(ifstream& line, streamoff start, int date);


string path("data.txt");

//每次读取文件的一行，并返回下一行的文件游标；
streamoff read_line(ifstream& line, string& str, streamoff start)
{
	if (!line.is_open())
		line.open(path, ifstream::in);
	//如果读取文件失败

	if (!line)
	{
		perror("open file error!");
		exit(1);
	}
	//定位文件读取位置
	line.seekg(start);
	getline(line, str);//读取文件test.txt的一行到temp
	streamoff ret = line.tellg();
	line.close();
	return ret;
}

//服务器信息解析函数
void Serv_info(istringstream& out, map<string, shared_ptr<Server>>& SERpurcheable)
{

	shared_ptr<Server>temp = make_shared<Server>();

	string str;
	out >> str;
	str.pop_back();
	str.erase(0, 1);
	temp->setType(str);
	cout << "服务器型号：" << temp->getType() << endl;
	out >> str;
	//str.pop_back();
	temp->setCPUCapacity(atoi(str.c_str()));
	cout << "服务器CPU核数：" << temp->getCPUCapacity() << endl;
	out >> str;
	//str.pop_back();
	temp->setMemoryCapacity(atoi(str.c_str()));
	cout << "服务器内存：" << temp->getMemoryCapacity() << "GB" << endl;
	out >> str;
	//str.pop_back();
	temp->setHardwareCost(atoi(str.c_str()));
	cout << "服务器硬件成本：" << temp->getHardwareCost() << endl;
	out >> str;
	//str.pop_back();
	temp->setDailyCost(atoi(str.c_str()));
	cout << "服务器日能耗：" << temp->getDailyCost() << endl;

	SERpurcheable.emplace(temp->getType(), temp);

}

//虚拟机信息解析函数
void VirM_info(istringstream& out, map<string, shared_ptr<VisualMachine>>& saleable)
{

	shared_ptr<VisualMachine>temp = make_shared<VisualMachine>();

	string str;
	out >> str;
	str.pop_back();
	str.erase(0, 1);
	temp->setType(str);
	cout << "虚拟机型号：" << temp->getType() << endl;
	out >> str;
	//str.pop_back();
	temp->setCPUNeed(atoi(str.c_str()));
	cout << "虚拟机CPU核数：" << temp->getCPUNeed() << endl;
	out >> str;
	//str.pop_back();
	temp->setMemoryNeed(atoi(str.c_str()));
	cout << "虚拟机内存：" << temp->getMemoryNeed() << "GB" << endl;
	out >> str;
	if (atoi(str.c_str())) {
		temp->setNodeType(atoi(str.c_str()));
		str = "双节点";
	}
	else {
		temp->setNodeType(atoi(str.c_str()));
		str = "单节点";
	}
	cout << "节点部署方式：" << str << " " << temp->getNodeType() << endl;

	saleable.emplace(temp->getType(), temp);
}




//该函数用于解析一条请求序列的信息
void Request_info(istringstream& out)
{
	string str;
	string type;
	int ID;
	out >> str;
	str.pop_back();
	str.erase(0, 1);
	//请求序列
	if (str == "add") {
		cout << "请求添加虚拟机" << "  ";
		out >> type;
		type.pop_back();
		cout << "型号：" << type << "  ";
		out >> str;
		//str.pop_back();
		ID = atoi(str.c_str());
		cout << "ID：" << ID << endl;
	}
	else if (str == "del") {
		cout << "请求删除虚拟机" << "  ";
		out >> str;
		//str.pop_back();
		ID = atoi(str.c_str());
		cout << "ID：" << ID << endl;
	}
}



//该函数用于读取一天序列，并对每一条信息进行解析；
streamoff Day_task(ifstream& line, streamoff start)
{
	//判断文件是否打开，若未打开则打开
	if (!line.is_open())
		line.open(path, ifstream::in);

	//如果读取文件失败
	if (!line)
	{
		perror("open file error!");
		exit(1);
	}
	string str;
	start = read_line(line, str, start);
	cout << endl;
	//cout << "第" << date << "天一共有" << str << "条请求序列" << endl;

	//读取第date天的所有序列，并做解析
	int n = atoi(str.c_str());
	for (int i = 0; i < n; i++) {

		start = read_line(line, str, start);
		cout << str << endl;
		istringstream out(str);
		Request_info(out);
	}

	return start;
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

	Server s;


	//用于读取数据的流
	ifstream reader(path);

	//目前可售卖的虚拟机的列表
	map<string, shared_ptr<VisualMachine>> VMsaleable;

	//可购入的服务器的容量
	map<string, shared_ptr<Server>> SERpurcheable;

	//用于表示已经部署的虚拟机,应该是再可购入的虚拟机中的某一台虚拟机对象
	//当添加虚拟机时，将可购入虚拟机中的某台虚拟机对象的引用传入到该map，
	//并设置相应的ID
	map<int, VisualMachine&> DeployedVM;

	//用于表示买入的服务器，当买入该服务器时，便将该服务器的对象的引用传入到该map,
	//当删除或添加虚拟机时应该修改相应服务器的资源剩余。
	map<int, Server&>BoughtServ;

	/*****************************************************************************

	这段代码用于读取可采购服务器的数量，以及对可采购服务器的信息的解析

	******************************************************************************/


	//读取可采购服务器种类数目
	string temp;
	streamoff now = read_line(reader, temp, ifstream::beg);
	cout << temp << endl;

	//依次读取每台的服务器的信息，并解析信息的格式
	int n = atoi(temp.c_str());
	for (int i = 0; i < n; i++) {

		now = read_line(reader, temp, now);
		cout << temp << endl;
		istringstream out(temp);
		Serv_info(out, SERpurcheable);

	}

	/*****************************************************************************

	这段代码用于读取可售卖虚拟机的数量，以及对可售卖虚拟机的信息的解析

	******************************************************************************/


	//读取可售卖的虚拟机的数目
	now = read_line(reader, temp, now);
	cout << temp << endl;

	//依次读取每台的虚拟机的信息，并解析信息的格式	
	n = atoi(temp.c_str());
	for (int i = 0; i < n; i++) {

		now = read_line(reader, temp, now);
		cout << temp << endl;
		istringstream out(temp);
		VirM_info(out, VMsaleable);

	}
	for (auto it = VMsaleable.begin(); it != VMsaleable.end(); it++) {
		cout << it->first << " " << (it->second)->getCPUNeed() << endl;
	}

	/*****************************************************************************

	这段代码用于读取天数，以及对每天的数据序列的一个解析

	******************************************************************************/


	now = read_line(reader, temp, now);
	cout << temp << endl;

	//依次读取每天的序列，并解析序列的格式	
	n = atoi(temp.c_str());
	cout << "there are requests of" << n << "days" << endl;
	for (int i = 0; i < n; i++) {

		now = Day_task(reader, now);

	}

	return 0;
}