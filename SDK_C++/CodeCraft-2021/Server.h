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




public:


    /*
    / 服务器是否在使用
    / return bool
    / 0 没在使用，1 在使用
    */
    bool isUsed() {
        return CPUCapacity != CPULeft || memoryCapacity != memoryLeft;
    }


    /*
    / 计算这个服务器的总成本
    / return int
    */
    int totalCost() {
        return hardwareCost + dailyCost * runDay;
    }



    /*
    / Server 类构造函数
    */ 
    Server(string type, int id, int CPUCapacity, int CPULeft, int memoryCapacity, int memoryLeft, int hardwareCost, int dailyCost, int runDay) {
        this->type = type;
        this->id = id;
        this->CPUCapacity = CPUCapacity;
        this->CPULeft = CPULeft;
        this->memoryCapacity = memoryCapacity;
        this->memoryLeft = memoryLeft;
        this->hardwareCost = hardwareCost;
        this->dailyCost = dailyCost;
        this->runDay = runDay;
    }


    //////////////////////////////
    // 下面是 getter 和 setter
    string getType() {
        return type;
    }

    void setType(string type) {
        this->type = type;
    }

    int getId() {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    int getCPUCapacity() {
        return CPUCapacity;
    }

    void setCPUCapacity(int CPUCapacity) {
        this->CPUCapacity = CPUCapacity;
    }

    int getCPULeft() {
        return CPULeft;
    }

    void setCPULeft(int CPULeft) {
        this->CPULeft = CPULeft;
    }

    int getMemoryCapacity() {
        return memoryCapacity;
    }

    void setMemoryCapacity(int memoryCapacity) {
        this->memoryCapacity = memoryCapacity;
    }

    int getMemoryLeft() {
        return memoryLeft;
    }

    void setMemoryLeft(int memoryLeft) {
        this->memoryLeft = memoryLeft;
    }

    int getHardwareCost() {
        return hardwareCost;
    }

    void setHardwareCost(int hardwareCost) {
        this->hardwareCost = hardwareCost;
    }

    int getDailyCost() {
        return dailyCost;
    }

    void setDailyCost(int dailyCost) {
        this->dailyCost = dailyCost;
    }

    int getRunDay() {
        return runDay;
    }

    void setRunDay(int runDay) {
        this->runDay = runDay;
    }
};