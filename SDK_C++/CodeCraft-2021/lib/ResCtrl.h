#pragma once
#include<iostream>
#include "ResCtrl.h"
#include<memory>
#include<string>
#include<map>
#include"Server.h"
#include"VisualMachine.h"


using namespace std;

class ResCtrl
{
	private:
		//目前可售卖的虚拟机的列表
		map<string, shared_ptr<VisualMachine>>& VMsaleable;

		//可购入的服务器的数量
		map<string, shared_ptr<Server>> & SERpurcheable;

		//用于表示已经部署的虚拟机,应该是再可购入的虚拟机中的某一台虚拟机对象
		//当添加虚拟机时，将可购入虚拟机中的某台虚拟机对象的引用传入到该map，
		//并设置相应的ID
		map<int, VisualMachine&>&  DeployedVM;

		//用于表示买入的服务器，当买入该服务器时，便将该服务器的对象的引用传入到该map,
		//当删除或添加虚拟机时应该修改相应服务器的资源剩余。
		map<int, Server&>& BoughtServ;

public:

	//构造函数；
	ResCtrl(map<string, shared_ptr<VisualMachine>>& VMsaleable1, map<string, shared_ptr<Server>>& SERpurcheable1,
		map<int, VisualMachine&>& DeployedVM1, map<int, Server&>& BoughtServ1);




	//getter
	map<string, shared_ptr<VisualMachine>> & getVMsaleable();
	map<string, shared_ptr<Server>> & getSERpurcheable();
	map<int, VisualMachine&>&  getDeployedVM();
	map<int, Server&> & getBoughtServ();
};