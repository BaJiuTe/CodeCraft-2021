#pragma once
#include<iostream>
#include<string.h>
#include<map>
#include<vector> 
#include "VisualMachine.h"
#include<memory>

using namespace std;


class Server {
private:
    string type;                        // ����������
    int serverId;                       // ������ id, id �� 0 ����
    int CPUCapacity;                    // CPU ������
    int partACPULeft;                   // A �ڵ� CPU ʣ��
    int partBCPULeft;                   // B �ڵ� CPU ʣ��
    int memoryCapacity;                 // �ڴ�����
    int partAMemoryLeft;                // A �ڵ��ڴ�ʣ��
    int partBMemoryLeft;                // B �ڵ��ڴ�ʣ��
    int hardwareCost;                   // Ӳ���ɱ�
    int dailyCost;                      // �ճ��ܺĳɱ�
    bool status;                        // ������״̬��Ĭ�Ϲرգ��� add | del | migration ��ʱ������
    //double score;                       //���ؾ������


public:
    map<int, shared_ptr<VisualMachine>> mountedVM;  // ���ص����������ʼΪ�� <����� id�� �����������Ϣ>
    
    Server();

    // ���캯����ֻ��Ҫ��������ʱ�ĳ�ʼ״̬
    Server(string type, int serverId, int CPUCapacity, int memoryCapacity, int hardwareCost, int dailyCost);

    Server(string type, int CPUCapacity, int memoryCapacity, int hardwareCost, int dailyCost);

    //A�ڵ����������B�ڵ��򷵻�true
    bool isAmore();
    



    // getter
    string getType();
    int getServerId();
    int getCPUCapacity();
    int getPartACPULeft();
    int getPartBCPULeft();
    int getMemoryCapacity();
    int getPartAMemoryLeft();
    int getPartBMemoryLeft();
    int getHardwareCost();
    int getDailyCost();
    bool getStatus();
    double getAScore();
    double getBScore();
    double getScore();
    // setter
    void setType(string type);
    void setServerId(int serverId);
    void setCPUCapacity(int CPUCapacity);
    void setPartACPULeft(int partACPULeft);
    void setPartBCPULeft(int partBCPULeft);
    void setMemoryCapacity(int memoryCapacity);
    void setPartAMemoryLeft(int partAMemoryLeft);
    void setPartBMemoryLeft(int partBMemoryLeft);
    void setHardwareCost(int hardwareCost);
    void setDailyCost(int dailyCost);
    void setStatus(bool status);
    
};