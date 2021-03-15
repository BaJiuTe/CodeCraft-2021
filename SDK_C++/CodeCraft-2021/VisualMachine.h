#pragma once
#include<iostream>
#include<string.h>

using namespace std;

class VisualMachine {
private:
    string type;            // ���������
    int VMId;               // ����� id
    int CPUNeed;            // CPU ����
    int memoryNeed;         // �ڴ�����
    int nodeType;           // �ڵ����� 0:���ڵ㣬1��˫�ڵ�
    int serverId;           // ������һ����������
    char deployNode;        // ���𵽷��������ĸ��ڵ㣬'A','B','C'��˫�ڵ�


    


public:


    // VisualMachine �๹�캯��
    VisualMachine(string type, int VMId, int CPUNeed, int memoryNeed, int sigle);
    VisualMachine();





    // getter    
    string getType();
    int getVMId();
    int getCPUNeed();
    int getMemoryNeed();
    int getNodeType();
    int getServerId();
    char getDeployNode();


    // setter
    void setType(string type);
    void setVMId(int VMId);
    void setCPUNeed(int CPUNeed);
    void setMemoryNeed(int memoryNeed);
    void setNodeType(int nodeType);
    void setServerId(int serverId);
    void setDeployNode(char deployNode);
};