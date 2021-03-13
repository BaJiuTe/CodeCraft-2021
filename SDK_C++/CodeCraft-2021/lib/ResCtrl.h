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
		//Ŀǰ����������������б�
		map<string, shared_ptr<VisualMachine>>& VMsaleable;

		//�ɹ���ķ�����������
		map<string, shared_ptr<Server>> & SERpurcheable;

		//���ڱ�ʾ�Ѿ�����������,Ӧ�����ٿɹ����������е�ĳһ̨���������
		//����������ʱ�����ɹ���������е�ĳ̨�������������ô��뵽��map��
		//��������Ӧ��ID
		map<int, VisualMachine&>&  DeployedVM;

		//���ڱ�ʾ����ķ�������������÷�����ʱ���㽫�÷������Ķ�������ô��뵽��map,
		//��ɾ������������ʱӦ���޸���Ӧ����������Դʣ�ࡣ
		map<int, Server&>& BoughtServ;

public:

	//���캯����
	ResCtrl(map<string, shared_ptr<VisualMachine>>& VMsaleable1, map<string, shared_ptr<Server>>& SERpurcheable1,
		map<int, VisualMachine&>& DeployedVM1, map<int, Server&>& BoughtServ1);




	//getter
	map<string, shared_ptr<VisualMachine>> & getVMsaleable();
	map<string, shared_ptr<Server>> & getSERpurcheable();
	map<int, VisualMachine&>&  getDeployedVM();
	map<int, Server&> & getBoughtServ();
};

