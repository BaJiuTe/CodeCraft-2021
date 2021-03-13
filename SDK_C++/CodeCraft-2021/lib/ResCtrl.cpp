#include<iostream>
#include "ResCtrl.h"
#include<memory>
#include<string>
#include<map>

using namespace std;


//¹¹Ôìº¯Êý£»
ResCtrl::ResCtrl(map<string, shared_ptr<VisualMachine>>& VMsaleable1, map<string, shared_ptr<Server>>& SERpurcheable1,
	map<int, VisualMachine&>& DeployedVM1, map<int, Server&>& BoughtServ1):
	VMsaleable(VMsaleable1),
	SERpurcheable(SERpurcheable1),
	DeployedVM(DeployedVM1),
	BoughtServ(BoughtServ1)
{}

map<string, shared_ptr<VisualMachine>>& ResCtrl::getVMsaleable() {
	return this->VMsaleable;
};


map<string, shared_ptr<Server>>& ResCtrl::getSERpurcheable() {
	return this->SERpurcheable;
};


map<int, VisualMachine&> & ResCtrl::getDeployedVM() {
	return this->DeployedVM;
};


map<int, Server&> & ResCtrl::getBoughtServ() {
	return this->BoughtServ;
};