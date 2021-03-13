#pragma once
#include<iostream>
#include<string.h>

using namespace std;

class VisualMachine {
private:
    string type;            // 虚拟机类型
    int VMId;               // 虚拟机 id
    int CPUNeed;            // CPU 需求
    int memoryNeed;         // 内存需求
    int nodeType;           // 节点类型 0:单节点，1：双节点
    int serverId;           // 部署到哪一个服务器上
    char deployNode;        // 部署到服务器上哪个节点，'A','B','C'：双节点


    


public:


    // VisualMachine 类构造函数
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
    void setDeployNode(char nodeType);
};