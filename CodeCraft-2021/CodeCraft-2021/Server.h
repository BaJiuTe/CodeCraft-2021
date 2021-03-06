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
    string type;                        // 服务器类型
    int serverId;                       // 服务器 id, id 从 0 递增
    int CPUCapacity;                    // CPU 总容量
    int partACPULeft;                   // A 节点 CPU 剩余
    int partBCPULeft;                   // B 节点 CPU 剩余
    int memoryCapacity;                 // 内存容量
    int partAMemoryLeft;                // A 节点内存剩余
    int partBMemoryLeft;                // B 节点内存剩余
    int hardwareCost;                   // 硬件成本
    int dailyCost;                      // 日常能耗成本
    bool status;                        // 服务器状态，默认关闭，在 add | del | migration 的时候设置
    //double score;                       //负载均衡分数


public:
    map<int, shared_ptr<VisualMachine>> mountedVM;  // 挂载的虚拟机，初始为空 <虚拟机 id， 虚拟机所有信息>
    
    Server();

    // 构造函数，只需要给出购入时的初始状态
    Server(string type, int serverId, int CPUCapacity, int memoryCapacity, int hardwareCost, int dailyCost);

    Server(string type, int CPUCapacity, int memoryCapacity, int hardwareCost, int dailyCost);

    //A节点的容量大于B节点则返回true
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