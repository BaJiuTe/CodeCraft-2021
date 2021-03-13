#pragma once
#include<iostream>
#include<string.h>

using namespace std;

class VisualMachine {
private:
    string type;           // ���������
    int id;                // ����� id
    int CPUNeed;           // CPU ����
    int memoryNeed;        // �ڴ�����
    int sigle;             // ��¼��˫�ڵ�
    int serverId;          // ������һ����������

    


public:

    /*
    / VisualMachine �๹�캯��
    */
    VisualMachine(string type, int id, int CPUNeed, int memoryNeed, int sigle);

    VisualMachine();


    //////////////////////////////
    // ������ getter �� setter    
    string getType();
    int getId();
    int getCPUNeed();
    int getMemoryNeed();
    int getSigle();
    int getServerId();


    void setType(string type);
    void setId(int id);
    void setCPUNeed(int CPUNeed);
    void setMemoryNeed(int memoryNeed);
    void setSigle(int sigle);
    void setServerId(int serverId);
};