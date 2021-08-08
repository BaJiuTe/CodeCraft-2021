#ifndef _BASESMOOTHINGALGORITHM_H_
#define _BASESMOOTHINGALGORITHM_H_

#include "iostream"
#include<fstream>
#include<string>
#include<sstream>
#include<map>
#include<memory>
#include"Server.h"
#include"VisualMachine.h"
#include<vector>

class Resource {
public:

	//模拟部署用的序列
	map<int, shared_ptr<Server>> MockClassA00; map<int, shared_ptr<VisualMachine>> MockA00_DeployedVM;
	map<int, shared_ptr<Server>> MockClassA0; map<int, shared_ptr<VisualMachine>> MockA0_DeployedVM;
	map<int, shared_ptr<Server>> MockClassA01; map<int, shared_ptr<VisualMachine>> MockA01_DeployedVM;
	map<int, shared_ptr<Server>> MockClassA1; map<int, shared_ptr<VisualMachine>> MockA1_DeployedVM;
	map<int, shared_ptr<Server>> MockClassB0; map<int, shared_ptr<VisualMachine>> MockB0_DeployedVM;
	map<int, shared_ptr<Server>> MockClassB1; map<int, shared_ptr<VisualMachine>> MockB1_DeployedVM;
	map<int, shared_ptr<Server>> MockClassC; map<int, shared_ptr<VisualMachine>> MockC_DeployedVM;
	map<int, shared_ptr<Server>> MockClassD; map<int, shared_ptr<VisualMachine>> MockD_DeployedVM;
	map<int, shared_ptr<Server>> MockClassN; map<int, shared_ptr<VisualMachine>> MockN_DeployedVM;


	//将服务器分为9个类别，里面分别存放的是服务器对应的类型号
	map<int, shared_ptr<Server>> ClassA00;  map<int, shared_ptr<VisualMachine>> A00_DeployedVM;
	map<int, shared_ptr<Server>> ClassA0; map<int, shared_ptr<VisualMachine>>  A0_DeployedVM;
	map<int, shared_ptr<Server>> ClassA01; map<int, shared_ptr<VisualMachine>>  A01_DeployedVM;
	map<int, shared_ptr<Server>> ClassA1; map<int, shared_ptr<VisualMachine>>  A1_DeployedVM;
	map<int, shared_ptr<Server>> ClassB0;  map<int, shared_ptr<VisualMachine>> B0_DeployedVM;
	map<int, shared_ptr<Server>> ClassB1;  map<int, shared_ptr<VisualMachine>> B1_DeployedVM;
	map<int, shared_ptr<Server>> ClassC;  map<int, shared_ptr<VisualMachine>> C_DeployedVM;
	map<int, shared_ptr<Server>> ClassD;  map<int, shared_ptr<VisualMachine>> D_DeployedVM;
	map<int, shared_ptr<Server>> ClassN;  map<int, shared_ptr<VisualMachine>> N_DeployedVM;


	string typeA00 = "hostP08J3"; // 0.1~0.3
	string typeA0 = "host0Y6DP";  // 0.3~0.5
	string typeA01 = "hostJFC2V"; // 0.5~0.75
	string typeA1 = "hostVIHCW"; // 0.75~1.0
	string typeB0 = "hostZHR5X"; // 1.0~1.5
	string typeB1 = "hostGCX19"; // 1.5~2.0
	string typeC = "hostD6AF5";  // 2.0~3.3
	string typeD = "host4NLZ1";  // 3.3~9.5
	string typeN = "hostVIHCW";  // 0~0.1&9.5~

	int DeployedSize = 0;
	int MockDeployedSize = 0;
};

#endif