#pragma once
#include<iostream>
#include<string.h>

using namespace std;

// ��������
class Server {
private:
    string type;            // ����������
    int id;                 // ������ id
    int CPUCapacity;        // CPU ������
    int CPULeft;            // CPU ʣ��
    int memoryCapacity;     // �ڴ�����
    int memoryLeft;         // �ڴ�ʣ��
    int partACPULeft;       // A �ڵ� CPU ʣ��
    int partBCPULeft;       // B �ڵ� CPU ʣ��
    int partAMemoryLeft;    // A �ڵ��ڴ�ʣ��
    int partBMemoryLeft;    // B �ڵ��ڴ�ʣ��
    int hardwareCost;       // Ӳ���ɱ�
    int dailyCost;          // �ճ��ܺĳɱ�
    int runDay;             // ��������������

    // ����һ�� map ����������ڸ÷������ϵ������



public:
    // ���캯��
    Server(string type, int id, int CPUCapacity, int CPULeft, int memoryCapacity, int memoryLeft, 
        int partACPULeft, int partBCPULeft, int partAMemoryLeft, int partBMemoryLeft, 
        int hardwareCost, int dailyCost, int runDay);
    
    //���캯����ֻ��Ҫ��������ʱ�ĳ�ʼ״̬��
    Server(string type,int CPUCapacity,int memoryCapacity,int hardwareCost,int dailyCost);

    //Ĭ�Ϲ���
    Server();


    bool isUsed();
    int totalCost();                // 

    // getter
    string getType();
    int getId();
    int getCPUCapacity();
    int getCPULeft();
    int getMemoryCapacity();
    int getMemoryLeft();
    int getPartACPULeft();
    int getPartBCPULeft();
    int getPartAMemoryLeft();
    int getPartBMemoryLeft();
    int getHardwareCost();
    int getDailyCost();
    int getRunDay();

    // setter
    void setType(string type);
    void setId(int id);
    void setCPUCapacity(int CPUCapacity);
    void setCPULeft(int CPULeft);
    void setMemoryCapacity(int memoryCapacity);
    void setMemoryLeft(int memoryLeft);
    void setPartACPULeft(int partACPULeft);
    void setPartBCPULeft(int partBCPULeft);
    void setPartAMemoryLeft(int partAMemoryLeft);
    void setPartBMemoryLeft(int partBMemoryLeft);
    void setHardwareCost(int hardwareCost);
    void setDailyCost(int dailyCost);
    void setRunDay(int runDay);

};