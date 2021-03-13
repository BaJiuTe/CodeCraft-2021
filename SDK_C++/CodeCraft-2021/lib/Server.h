#pragma once
#include<iostream>
#include<string.h>

using namespace std;

// 服务器类
class Server {
private:
    string type;            // 服务器类型
    int id;                 // 服务器 id
    int CPUCapacity;        // CPU 总容量
    int CPULeft;            // CPU 剩余
    int memoryCapacity;     // 内存容量
    int memoryLeft;         // 内存剩余
    int partACPULeft;       // A 节点 CPU 剩余
    int partBCPULeft;       // B 节点 CPU 剩余
    int partAMemoryLeft;    // A 节点内存剩余
    int partBMemoryLeft;    // B 节点内存剩余
    int hardwareCost;       // 硬件成本
    int dailyCost;          // 日常能耗成本
    int runDay;             // 服务器运行天数

    // 定义一个 map 用来存挂载在该服务器上的虚拟机



public:
    // 构造函数
    Server(string type, int id, int CPUCapacity, int CPULeft, int memoryCapacity, int memoryLeft, 
        int partACPULeft, int partBCPULeft, int partAMemoryLeft, int partBMemoryLeft, 
        int hardwareCost, int dailyCost, int runDay);
    
    //构造函数，只需要给出购入时的初始状态，
    Server(string type,int CPUCapacity,int memoryCapacity,int hardwareCost,int dailyCost);

    //默认构造
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