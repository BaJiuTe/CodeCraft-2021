#include "iostream"
#include<fstream>
#include<string>
#include<sstream>
#include<map>
#include<memory>
#include<vector>
#include"Server.h"
#include"VisualMachine.h"
#include"Resource.h"
#include"Scheduling.h"


using namespace std;

string path("training-1.txt");

//服务器ID

int ser_id = 0;
//string path("data.txt");
int Mock_serid = 0;

int Mtimes = 0;


// 消耗成本
int consumptionCost = 0;

map<int, string>ID_tostring;
map<int, string>Mock_ID_tostring;

/**********************************************************

函数：Serv_info
	处理一条服务器信息，并将相应的信息存入到map中
参数1：istringstream& out  字符串流，保存一条序列请求
参数2：map<string, shared_ptr<Server>>& SERpurcheable 保存所有可购入的服务器的map

**********************************************************/

void Serv_info(istringstream& out, map<string, shared_ptr<Server>>& SERpurcheable)
{

	shared_ptr<Server>temp = make_shared<Server>();

	string str;
	out >> str;
	str.pop_back();
	str.erase(0, 1);
	temp->setType(str);
	out >> str;
	temp->setCPUCapacity(atoi(str.c_str()));
	temp->setPartACPULeft((temp->getCPUCapacity()) / 2);
	temp->setPartBCPULeft(temp->getPartACPULeft());
	out >> str;
	temp->setMemoryCapacity(atoi(str.c_str()));
	temp->setPartAMemoryLeft((temp->getMemoryCapacity()) / 2);
	temp->setPartBMemoryLeft(temp->getPartAMemoryLeft());
	out >> str;
	temp->setHardwareCost(atoi(str.c_str()));
	out >> str;
	temp->setDailyCost(atoi(str.c_str()));
	//
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
	out >> str;
	temp->setCPUNeed(atoi(str.c_str()));
	out >> str;
	temp->setMemoryNeed(atoi(str.c_str()));
	out >> str;
	if (atoi(str.c_str())) {
		temp->setNodeType(atoi(str.c_str()));
		//str = "双节点";
	}
	else {
		temp->setNodeType(atoi(str.c_str()));
		//str = "单节点";
	}

	saleable.emplace(temp->getType(), temp);
}




/**********************************************************

函数：Request_info
	处理一条请求序列，并完成相应的动作，即删除或者添加虚拟机
参数1：字符串流，保存一条序列请求
参数2：

**********************************************************/
void Request_info(istringstream& out,
	Scheduling& sch, map<string, shared_ptr<VisualMachine>>& VMsaleable,
	map<string, shared_ptr<Server>>& SERpurcheable,
	Resource& s
)
{
	string str;
	string type;
	int id;
	out >> str;
	str.pop_back();
	str.erase(0, 1);
	//请求序列
	if (str == "add") {
		out >> type;
		type.pop_back();
		out >> str;
		id = atoi(str.c_str());

		s.DeployedSize++;

		//添加虚拟机, ID ,type

		if (VMsaleable[type]->getScore() < 0.1 || VMsaleable[type]->getScore() > 9.5) {
			sch.addVM(s.ClassN, s.N_DeployedVM, SERpurcheable, VMsaleable, type, id);
			ID_tostring.insert({ id,"N" });
		}
		else if (VMsaleable[type]->getScore() < 0.4) {
			sch.addVM(s.ClassA00, s.A00_DeployedVM, SERpurcheable, VMsaleable, type, id);
			ID_tostring.insert({ id,"A00" });//将每种类别其ID对应，可以根据ID，得到虚拟机所部署的服务器类别
		}
		else if (VMsaleable[type]->getScore() < 0.47) {
			sch.addVM(s.ClassA0, s.A0_DeployedVM, SERpurcheable, VMsaleable, type, id);
			ID_tostring.insert({ id,"A0" });//将每种类别其ID对应，可以根据ID，得到虚拟机所部署的服务器类别
		}
		else if (VMsaleable[type]->getScore() < 0.7) {
			sch.addVM(s.ClassA01, s.A01_DeployedVM, SERpurcheable, VMsaleable, type, id);
			ID_tostring.insert({ id,"A01" });//将每种类别其ID对应，可以根据ID，得到虚拟机所部署的服务器类别
		}
		else if (VMsaleable[type]->getScore() < 1.05) {
			sch.addVM(s.ClassA1, s.A1_DeployedVM, SERpurcheable, VMsaleable, type, id);
			ID_tostring.insert({ id,"A1" });
		}
		else if (VMsaleable[type]->getScore() < 1.41) {
			sch.addVM(s.ClassB0, s.B0_DeployedVM, SERpurcheable, VMsaleable, type, id);
			ID_tostring.insert({ id,"B0" });
		}
		else if (VMsaleable[type]->getScore() < 2.02) {
			sch.addVM(s.ClassB1, s.B1_DeployedVM, SERpurcheable, VMsaleable, type, id);
			ID_tostring.insert({ id,"B1" });
		}
		else if (VMsaleable[type]->getScore() < 3.3) {
			sch.addVM(s.ClassC, s.C_DeployedVM, SERpurcheable, VMsaleable, type, id);
			ID_tostring.insert({ id,"C" });
		}
		else {
			sch.addVM(s.ClassD, s.D_DeployedVM, SERpurcheable, VMsaleable, type, id);
			ID_tostring.insert({ id,"D" });
		}
	}
	else if (str == "del") {
		//cout << "请求删除虚拟机" << "  ";
		out >> str;
		//str.pop_back();
		id = atoi(str.c_str());
		//cout << "ID：" << ID << endl;

		s.DeployedSize--;


		if (ID_tostring[id] == "N") {
			sch.delVM(s.ClassN, s.N_DeployedVM, id);
		}
		else if (ID_tostring[id] == "A00") {
			sch.delVM(s.ClassA00, s.A00_DeployedVM, id);
		}
		else if (ID_tostring[id] == "A0") {
			sch.delVM(s.ClassA0, s.A0_DeployedVM, id);
		}
		else if (ID_tostring[id] == "A01") {
			sch.delVM(s.ClassA01, s.A01_DeployedVM, id);
		}
		else if (ID_tostring[id] == "A1") {
			sch.delVM(s.ClassA1, s.A1_DeployedVM, id);
		}
		else if (ID_tostring[id] == "B0") {
			sch.delVM(s.ClassB0, s.B0_DeployedVM, id);
		}
		else if (ID_tostring[id] == "B1") {
			sch.delVM(s.ClassB1, s.B1_DeployedVM, id);
		}
		else if (ID_tostring[id] == "C") {
			sch.delVM(s.ClassC, s.C_DeployedVM, id);
		}
		else if (ID_tostring[id] == "D") {
			sch.delVM(s.ClassD, s.D_DeployedVM, id);
		}
		else {
			cout << "处理异常退出" << endl;
			exit(1);
		}
		ID_tostring.erase(id);
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
void PurchaseServer(int countN, int countA00, int countA0, int countA01, int countA1, int countB0, int countB1, int countC, int countD,
	map<string, shared_ptr<Server>>& SERpurcheable, Resource& s
)
{
	//输出购买的台数

	//统计购买的种类数目
	int count = 0;
	if (countN != 0)
		count++;
	if (countA00 != 0)
		count++;
	if (countA0 != 0)
		count++;
	if (countA01 != 0)
		count++;
	if (countA1 != 0)
		count++;
	if (countB0 != 0)
		count++;
	if (countB1 != 0)
		count++;
	if (countC != 0)
		count++;
	if (countD != 0)
		count++;

	//输出购买种类
	cout << "(purchase, " << count << ")" << endl;


	for (int i = 0; i < countN; i++) {
		auto temp = (*(SERpurcheable[s.typeN]));
		auto temp_ptr = make_shared<Server>(temp);
		temp_ptr->setServerId(ser_id);
		s.ClassN[ser_id++] = temp_ptr;
	}
	for (int i = 0; i < countA00; i++) {
		auto temp = (*(SERpurcheable[s.typeA00]));
		auto temp_ptr = make_shared<Server>(temp);
		temp_ptr->setServerId(ser_id);
		s.ClassA00[ser_id++] = temp_ptr;
	}
	for (int i = 0; i < countA0; i++) {
		auto temp = (*(SERpurcheable[s.typeA0]));
		auto temp_ptr = make_shared<Server>(temp);
		temp_ptr->setServerId(ser_id);
		s.ClassA0[ser_id++] = temp_ptr;
	}
	for (int i = 0; i < countA01; i++) {
		auto temp = (*(SERpurcheable[s.typeA01]));
		auto temp_ptr = make_shared<Server>(temp);
		temp_ptr->setServerId(ser_id);
		s.ClassA01[ser_id++] = temp_ptr;
	}
	for (int i = 0; i < countA1; i++) {
		auto temp = (*(SERpurcheable[s.typeA1]));
		auto temp_ptr = make_shared<Server>(temp);
		temp_ptr->setServerId(ser_id);
		s.ClassA1[ser_id++] = temp_ptr;
	}

	for (int i = 0; i < countB0; i++) {
		auto temp = (*(SERpurcheable[s.typeB0]));
		auto temp_ptr = make_shared<Server>(temp);
		temp_ptr->setServerId(ser_id);
		s.ClassB0[ser_id++] = temp_ptr;
	}
	for (int i = 0; i < countB1; i++) {
		auto temp = (*(SERpurcheable[s.typeB1]));
		auto temp_ptr = make_shared<Server>(temp);
		temp_ptr->setServerId(ser_id);
		s.ClassB1[ser_id++] = temp_ptr;
	}

	for (int i = 0; i < countC; i++) {
		auto temp = (*(SERpurcheable[s.typeC]));
		auto temp_ptr = make_shared<Server>(temp);
		temp_ptr->setServerId(ser_id);
		s.ClassC[ser_id++] = temp_ptr;
	}

	for (int i = 0; i < countD; i++) {
		auto temp = (*(SERpurcheable[s.typeD]));
		auto temp_ptr = make_shared<Server>(temp);
		temp_ptr->setServerId(ser_id);
		s.ClassD[ser_id++] = temp_ptr;
	}


	if (countN != 0) {

		cout << "(" << s.typeN << ", " << countN << ")" << endl;
	}
	if (countA00 != 0) {

		cout << "(" << s.typeA00 << ", " << countA00 << ")" << endl;
	}
	if (countA0 != 0) {

		cout << "(" << s.typeA0 << ", " << countA0 << ")" << endl;
	}
	if (countA01 != 0) {

		cout << "(" << s.typeA01 << ", " << countA01 << ")" << endl;
	}
	if (countA1 != 0) {

		cout << "(" << s.typeA1 << ", " << countA1 << ")" << endl;
	}
	if (countB0 != 0) {

		cout << "(" << s.typeB0 << ", " << countB0 << ")" << endl;
	}
	if (countB1 != 0) {

		cout << "(" << s.typeB1 << ", " << countB1 << ")" << endl;
	}
	if (countC != 0) {

		cout << "(" << s.typeC << ", " << countC << ")" << endl;
	}
	if (countD != 0) {

		cout << "(" << s.typeD << ", " << countD << ")" << endl;
	}
}



/**********************************************************

函数：QuestNeed
	该函数用于求出一条序列的请求的容量
参数1：字符串流，存放一条序列
参数2：可以出售的虚拟机列表
参数3：一条序列的CPU需求
参数4: 一条序列内存需求

**********************************************************/
void QuestNeed(istringstream& out,
	map<string, shared_ptr<VisualMachine>>& VMsaleable,
	map< string, shared_ptr< Server > >& SERpurcheable,
	Scheduling sch,
	int* countN, int* countA00, int* countA0, int* countA01, int* countA1, int* countB0, int* countB1, int* countC, int* countD,
	Resource& s
)
{
	string str;
	string type;
	out >> str;
	str.pop_back();
	str.erase(0, 1);
	//返回一天的所有请求
	if (str == "add") {
		out >> type;
		type.pop_back();
		int id;
		out >> id;
		//对这四类分别进行操作
		//A类

		s.MockDeployedSize++;

		if (VMsaleable[type]->getScore() < 0.1 || VMsaleable[type]->getScore() > 9.5) {
			sch.MockaddVM(s.MockClassN, s.MockN_DeployedVM, SERpurcheable, VMsaleable, type, id, countN, &Mock_serid, s.typeN);
			Mock_ID_tostring.insert({ id,"N" });// 将每种类别其ID对应，可以根据ID，得到虚拟机所部署的服务器类别
		}
		else if (VMsaleable[type]->getScore() < 0.4) {
			sch.MockaddVM(s.MockClassA00, s.MockA00_DeployedVM, SERpurcheable, VMsaleable, type, id, countA00, &Mock_serid, s.typeA00);
			Mock_ID_tostring.insert({ id,"A00" });// 将每种类别其ID对应，可以根据ID，得到虚拟机所部署的服务器类别
		}
		else if (VMsaleable[type]->getScore() < 0.47) {
			sch.MockaddVM(s.MockClassA0, s.MockA0_DeployedVM, SERpurcheable, VMsaleable, type, id, countA0, &Mock_serid, s.typeA0);
			Mock_ID_tostring.insert({ id,"A0" });// 将每种类别其ID对应，可以根据ID，得到虚拟机所部署的服务器类别
		}
		else if (VMsaleable[type]->getScore() < 0.7) {
			sch.MockaddVM(s.MockClassA01, s.MockA01_DeployedVM, SERpurcheable, VMsaleable, type, id, countA01, &Mock_serid, s.typeA01);
			Mock_ID_tostring.insert({ id,"A01" });// 将每种类别其ID对应，可以根据ID，得到虚拟机所部署的服务器类别
		}
		else if (VMsaleable[type]->getScore() < 1.05) {
			sch.MockaddVM(s.MockClassA1, s.MockA1_DeployedVM, SERpurcheable, VMsaleable, type, id, countA1, &Mock_serid, s.typeA1);
			Mock_ID_tostring.insert({ id,"A1" });
		}
		else if (VMsaleable[type]->getScore() < 1.41) {
			sch.MockaddVM(s.MockClassB0, s.MockB0_DeployedVM, SERpurcheable, VMsaleable, type, id, countB0, &Mock_serid, s.typeB0);
			Mock_ID_tostring.insert({ id,"B0" });
		}
		else if (VMsaleable[type]->getScore() < 2.02) {
			sch.MockaddVM(s.MockClassB1, s.MockB1_DeployedVM, SERpurcheable, VMsaleable, type, id, countB1, &Mock_serid, s.typeB1);
			Mock_ID_tostring.insert({ id,"B1" });
		}
		else if (VMsaleable[type]->getScore() < 3.3) {
			sch.MockaddVM(s.MockClassC, s.MockC_DeployedVM, SERpurcheable, VMsaleable, type, id, countC, &Mock_serid, s.typeC);
			Mock_ID_tostring.insert({ id,"C" });
		}
		else {
			sch.MockaddVM(s.MockClassD, s.MockD_DeployedVM, SERpurcheable, VMsaleable, type, id, countD, &Mock_serid, s.typeD);
			Mock_ID_tostring.insert({ id,"D" });
		}

	}
	else {//删除虚拟机

		s.MockDeployedSize--;
		out >> type;//实际为ID
		int ID = atoi(type.c_str());
		//按类别进行删除
		if (Mock_ID_tostring[ID] == "N") {
			sch.delVM(s.MockClassN, s.MockN_DeployedVM, ID);
			Mock_ID_tostring.erase(ID);
		}
		else if (Mock_ID_tostring[ID] == "A00") {
			sch.delVM(s.MockClassA00, s.MockA00_DeployedVM, ID);
			Mock_ID_tostring.erase(ID);
		}
		else if (Mock_ID_tostring[ID] == "A0") {
			sch.delVM(s.MockClassA0, s.MockA0_DeployedVM, ID);
			Mock_ID_tostring.erase(ID);
		}
		else if (Mock_ID_tostring[ID] == "A01") {
			sch.delVM(s.MockClassA01, s.MockA01_DeployedVM, ID);
			Mock_ID_tostring.erase(ID);
		}
		else if (Mock_ID_tostring[ID] == "A1") {
			sch.delVM(s.MockClassA1, s.MockA1_DeployedVM, ID);
			Mock_ID_tostring.erase(ID);
		}
		else if (Mock_ID_tostring[ID] == "B0") {
			sch.delVM(s.MockClassB0, s.MockB0_DeployedVM, ID);
			Mock_ID_tostring.erase(ID);
		}
		else if (Mock_ID_tostring[ID] == "B1") {
			sch.delVM(s.MockClassB1, s.MockB1_DeployedVM, ID);
			Mock_ID_tostring.erase(ID);
		}
		else if (Mock_ID_tostring[ID] == "C") {
			sch.delVM(s.MockClassC, s.MockC_DeployedVM, ID);
			Mock_ID_tostring.erase(ID);
		}
		else if (Mock_ID_tostring[ID] == "D") {
			sch.delVM(s.MockClassD, s.MockD_DeployedVM, ID);
			Mock_ID_tostring.erase(ID);
		}
		else {
			cout << "模拟异常退出" << endl;
			exit(1);
		}
	}
	return;
}

/**
 * 计算硬件成本
 */
int ComputationHardwareCost(Resource s)
{
	// 硬件成本
	int hardwareCost = 0;

	for (auto iter : s.ClassA00)
	{
		hardwareCost += iter.second->getHardwareCost();
	}
	for (auto iter : s.ClassA0)
	{
		hardwareCost += iter.second->getHardwareCost();
	}
	for (auto iter : s.ClassA01)
	{
		hardwareCost += iter.second->getHardwareCost();
	}
	for (auto iter : s.ClassA1)
	{
		hardwareCost += iter.second->getHardwareCost();
	}
	for (auto iter : s.ClassB0)
	{
		hardwareCost += iter.second->getHardwareCost();
	}
	for (auto iter : s.ClassB1)
	{
		hardwareCost += iter.second->getHardwareCost();
	}
	for (auto iter : s.ClassC)
	{
		hardwareCost += iter.second->getHardwareCost();
	}
	for (auto iter : s.ClassD)
	{
		hardwareCost += iter.second->getHardwareCost();
	}
	for (auto iter : s.ClassN)
	{
		hardwareCost += iter.second->getHardwareCost();
	}
	return hardwareCost;
}

/**
 * 日消耗成本
 */
void ComputationDayCost(Resource s)
{
	for (auto iter : s.ClassA00)
	{
		if (iter.second->mountedVM.size() != 0)
		{
			consumptionCost += iter.second->getDailyCost();
		}
	}
	for (auto iter : s.ClassA0)
	{
		if (iter.second->mountedVM.size() != 0)
		{
			consumptionCost += iter.second->getDailyCost();
		}
	}
	for (auto iter : s.ClassA01)
	{
		if (iter.second->mountedVM.size() != 0)
		{
			consumptionCost += iter.second->getDailyCost();
		}
	}
	for (auto iter : s.ClassA1)
	{
		if (iter.second->mountedVM.size() != 0)
		{
			consumptionCost += iter.second->getDailyCost();
		}
	}
	for (auto iter : s.ClassB0)
	{
		if (iter.second->mountedVM.size() != 0)
		{
			consumptionCost += iter.second->getDailyCost();
		}
	}
	for (auto iter : s.ClassB1)
	{
		if (iter.second->mountedVM.size() != 0)
		{
			consumptionCost += iter.second->getDailyCost();
		}
	}
	for (auto iter : s.ClassC)
	{
		if (iter.second->mountedVM.size() != 0)
		{
			consumptionCost += iter.second->getDailyCost();
		}
	}
	for (auto iter : s.ClassD)
	{
		if (iter.second->mountedVM.size() != 0)
		{
			consumptionCost += iter.second->getDailyCost();
		}
	}
	for (auto iter : s.ClassN)
	{
		if (iter.second->mountedVM.size() != 0)
		{
			consumptionCost += iter.second->getDailyCost();
		}
	}
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

void Day_task(
	map<string, shared_ptr<VisualMachine>>& VMsaleable,
	map< string, shared_ptr< Server > >& SERpurcheable,
	Scheduling& sch,
	Resource& s
)
{

	//info中存放一天的信息，包括所有序列
	vector<string> info;
	//当天的CPU总需求
	int countN = 0;
	int countA00 = 0;
	int countA0 = 0;
	int countA01 = 0;
	int countA1 = 0;
	int countB0 = 0;
	int countB1 = 0;
	int countC = 0;
	int countD = 0;


	string str;
	getline(cin, str);

	//读取当天的所有序列，并做解析
	int n = atoi(str.c_str());
	//求和，保存信息
	vector<string> MockInfo;
	int MockLimits = s.MockDeployedSize * 5 / 1000;
	int MockTimes = 0;



	sch.MockMagrition(s, VMsaleable, SERpurcheable, MockTimes, MockLimits, MockInfo);

	for (int i = 0; i < n; i++) {

		getline(cin, str);
		//将每天的序列保存起来方便后续使用
		info.push_back(str);
		//
		istringstream out(str);

		QuestNeed(out,
			VMsaleable,
			SERpurcheable,
			sch,
			&countN, &countA00, &countA0, &countA01, &countA1, &countB0, &countB1, &countC, &countD,
			s
		);

		//istringstream out1(str);
		//Request_info(out1);
	}
	//cout << "*********CPU需求：" << CPUneed << " *********" << endl;
	//cout << "*********内存需求：" << Memoryneed << " *********" << endl;

	PurchaseServer(countN, countA00, countA0, countA01, countA1,
		countB0, countB1,
		countC, countD,
		SERpurcheable, s);

	/*for (auto it : BoughtServ) {
		cout << "型号： "<<it.second->getType()<<"   ID:" <<it.second->getServerId() << endl;
	}*/


	//cout << "(migration, 0)" << endl;

	/*for (auto iter : BoughtServ) {
		cout << "（" << iter.second->getType() << "，" << iter.second->getServerId() << ", " << iter.second->getPartACPULeft() << ", "
			<< iter.second->getPartBCPULeft() << ", " << iter.second->getPartAMemoryLeft() << ", " << iter.second->getPartBMemoryLeft() << ")" << endl;
	}*/

	int limits = s.DeployedSize * 5 / 1000;
	int times = 0;
	vector<string> MagritionInfo;

	sch.Magrition(s, VMsaleable, SERpurcheable, times, limits, MagritionInfo);

	cout << "(migration, " << times << ")" << endl;

	// Mtimes += times;

	for (auto it : MagritionInfo) {
		cout << it << endl;
	}
	// for (auto it : MagritionInfo) {
	// 	cout << it << endl;
	// }


	for (int i = 0; i < info.size(); i++) {
		istringstream out(info[i]);
		Request_info(out, sch, VMsaleable, SERpurcheable, s);
	}

	ComputationDayCost(s);

	//cout << countA << " " << countB << " " << countC << " " << countD << endl;
	return;

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

	//调度类
	Scheduling sch;
	//用于读取数据的流
	//ifstream reader(path);

	//目前可售卖的虚拟机的列表
	map<string, shared_ptr<VisualMachine>> VMsaleable;

	//可购入的服务器的种类
	map<string, shared_ptr<Server>> SERpurcheable;

	//ID—type对应关系
	map<int, string> ID_type;


	//模拟部署用的序列
	map<int, shared_ptr<Server>>MockBoughtServ;
	map<int, shared_ptr<VisualMachine>> MockDeployedVM;
	//模拟已经部署的虚拟机序列

	//to manage the resourcese
	Resource SinglePoint;




	/*****************************************************************************

	这段代码用于读取可采购服务器的数量，以及对可采购服务器的信息的解析

	******************************************************************************/


	//读取可采购服务器种类数目
	//ifstream reader(path);
	string temp;

	getline(cin, temp);

	//依次读取每台的服务器的信息，并解析信息的格式
	int n = atoi(temp.c_str());
	//cout << "可购买服务器数： " << n << endl;
	for (int i = 0; i < n; i++) {

		//now = read_line(reader, temp, now);
		getline(cin, temp);
		//cout << temp << endl;
		istringstream out(temp);
		Serv_info(out, SERpurcheable);

	}

	/*****************************************************************************

	这段代码用于读取可售卖虚拟机的数量，以及对可售卖虚拟机的信息的解析

	******************************************************************************/


	//读取可售卖的虚拟机的数目
	//now = read_line(reader, temp, now);
	getline(cin, temp);
	//cout << "可购买虚拟机种数： " <<temp << endl;

	//依次读取每台的虚拟机的信息，并解析信息的格式	
	n = atoi(temp.c_str());
	for (int i = 0; i < n; i++) {

		getline(cin, temp);
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


	//now = read_line(reader, temp, now);
	getline(cin, temp);
	//cout << temp << endl;

	//依次读取每天的序列，并解析序列的格式	
	n = atoi(temp.c_str());
	//cout <<  n << "天的数据需要处理" << endl;
	for (int i = 0; i < n; i++) {
		//cout << "***********第" << i << "天******************" << endl;
		Day_task(VMsaleable, SERpurcheable, sch, SinglePoint);
	}

	//for (auto it:A_DeployedVM) {
	//	cout << "A:  " << it.second->getScore() << endl;
	//}
	//for (auto it : B_DeployedVM) {
	//	cout << "B:  " << it.second->getScore() << endl;
	//}
	//for (auto it : C_DeployedVM) {
	//	cout << "C:  " << it.second->getScore() << endl;
	//}
	//for (auto it : D_DeployedVM) {
	//	cout << "D:  " << it.second->getScore() << endl;
	//}
	//reader.close();
	cout << "总成本：" << ComputationHardwareCost(SinglePoint) + consumptionCost << endl;
	// cout << ser_id << endl;
	// cout << Mtimes << endl;
	return 0;
}
