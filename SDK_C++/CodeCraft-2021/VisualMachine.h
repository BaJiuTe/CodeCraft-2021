#include<iostream>
#include<string.h>

using namespace std;

class VisualMachine{
private:
    string type;           // 虚拟机类型
    int id;                // 虚拟机 id
    int CPUNeed;           // CPU 需求
    int memoryNeed;        // 内存需求
    int sigle;             // 记录单双节点
    

public:






    /*
    / VisualMachine 类构造函数
    */
    VisualMachine(string type, int id, int CPUNeed, int memoryNeed, int sigle) {
        this->type = type;
        this->id = id;
        this->CPUNeed = CPUNeed;
        this->memoryNeed = memoryNeed;
        this->sigle = sigle;
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

    int getCPUNeed() {
        return CPUNeed;
    }

    void setCPUNeed(int CPUNeed) {
        this->CPUNeed = CPUNeed;
    }

    int getMemoryNeed() {
        return memoryNeed;
    }

    void setMemoryNeed(int memoryNeed) {
        this->memoryNeed = memoryNeed;
    }

    int getSigle() {
        return sigle;
    }

    void setSigle(int sigle) {
        this->sigle = sigle;
    }
};