#pragma once
#include<iostream>
#include<string.h>

using namespace std;

class VisualMachine {
private:
    string type;           // 虚拟机类型
    int id;                // 虚拟机 id
    int CPUNeed;           // CPU 需求
    int memoryNeed;        // 内存需求
    int sigle;             // 记录单双节点
    int serverId;          // 部署到哪一个服务器上

    


public:

    /*
    / VisualMachine 类构造函数
    */
    VisualMachine(string type, int id, int CPUNeed, int memoryNeed, int sigle);

    VisualMachine();


    //////////////////////////////
    // 下面是 getter 和 setter    
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