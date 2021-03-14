#include<iostream>
#include<memory>
#include<string.h>
#include"Server.h"

using namespace std;

Server::Server() {}

/*
* 构造函数，只需要给出购入时的初始状态
* input type：服务器类型
* input CPUCapacity：CPU 容量
* input memoryCapacity：内存容量
* input hardwareCost：硬件成本
* input dailyCost：日常成本
*/
Server::Server(string type, int serverId, int CPUCapacity, int memoryCapacity, int hardwareCost, int dailyCost)
    : type(type), 
    serverId(serverId), 
    CPUCapacity(CPUCapacity),
    memoryCapacity(memoryCapacity), 
    partACPULeft(CPUCapacity / 2), 
    partBCPULeft(CPUCapacity / 2),
    partAMemoryLeft(memoryCapacity / 2), 
    partBMemoryLeft(memoryCapacity / 2),
    hardwareCost(hardwareCost),
    dailyCost(dailyCost), 
    status(0),
    mountedVM()
{}



/*
* 挂载一个虚拟机
* input VMList：虚拟机列表，类型为vector<VisualMachine>
* input VMtype：虚拟机类型
* input VNId：虚拟机id
* output ：void
*/
void Server::mountVM(map<string, shared_ptr<VisualMachine>>& VMsaleable, string VMtype, int VMId) {   // 这里改成 map
    
    // 拿到虚拟机的引用
    VisualMachine &VM = *(VMsaleable[VMtype]);

    // 更新服务器的数据
    if (VM.getNodeType() == 0) {  // 单节点，哪个节点剩余空间多，就放哪里
        if (this->getPartACPULeft() > this->getPartBCPULeft()) {
            this->setPartACPULeft(this->getPartACPULeft() - VM.getCPUNeed()); 
            this->setPartAMemoryLeft(this->getPartAMemoryLeft() - VM.getMemoryNeed());
            VM.setDeployNode('A');
        } else {
            this->setPartBCPULeft(this->getPartBCPULeft() - VM.getCPUNeed()); 
            this->setPartBMemoryLeft(this->getPartBMemoryLeft() - VM.getMemoryNeed());
            VM.setDeployNode('B');
        }
    } else {  // 双节点，平分
        this->setPartACPULeft(this->getPartACPULeft() - VM.getCPUNeed() / 2); 
        this->setPartAMemoryLeft(this->getPartAMemoryLeft() - VM.getMemoryNeed() / 2);
        this->setPartBCPULeft(this->getPartBCPULeft() - VM.getCPUNeed() / 2); 
        this->setPartBMemoryLeft(this->getPartBMemoryLeft() - VM.getMemoryNeed() / 2);
        VM.setDeployNode('C');
    }
    this->setStatus(true);

    // 把虚拟机挂载到服务器上
    mountedVM[VMId] = VM;

}



/*
* 删除该服务器里面的一个虚拟机
* input VMId：虚拟机id
* output ：void
*/
void Server::deleteVM(int VMId) {
    // 不判断虚拟机是否在服务器中，在调度中进行判断
    VisualMachine VM = this->mountedVM[VMId];

    // 对服务器数据进行更新
    switch(VM.getDeployNode()) {
        case 'A':
            this->setPartACPULeft(this->getPartACPULeft() + VM.getCPUNeed()); 
            this->setPartAMemoryLeft(this->getPartAMemoryLeft() + VM.getMemoryNeed());
            break;
        case 'B':
            this->setPartBCPULeft(this->getPartBCPULeft() - VM.getCPUNeed()); 
            this->setPartBMemoryLeft(this->getPartBMemoryLeft() - VM.getMemoryNeed());
            break;
        case 'C':
            this->setPartACPULeft(this->getPartACPULeft() + VM.getCPUNeed() / 2); 
            this->setPartAMemoryLeft(this->getPartAMemoryLeft() + VM.getMemoryNeed() / 2);
            this->setPartBCPULeft(this->getPartBCPULeft() + VM.getCPUNeed() / 2); 
            this->setPartBMemoryLeft(this->getPartBMemoryLeft() + VM.getMemoryNeed() / 2);
            break;
        default:break;
    }

    // 将虚拟机从服务器挂载列表中移除
    this->mountedVM.erase(VMId);
}









// getter

string Server::getType() {
    return type;
}

int Server::getServerId() {
    return serverId;
}

int Server::getCPUCapacity() {
    return CPUCapacity;
}

int Server::getMemoryCapacity() {
    return memoryCapacity;
}


int Server::getPartACPULeft() {
    return partACPULeft;
}

int Server::getPartBCPULeft() {
    return partBCPULeft;
}

int Server::getPartAMemoryLeft() {
    return partAMemoryLeft;
}

int Server::getPartBMemoryLeft() {
    return partBMemoryLeft;
}

int Server::getHardwareCost() {
    return hardwareCost;
}

int Server::getDailyCost() {
    return dailyCost;
}

bool Server::getStatus() {
    return status;
}




// setter

void Server::setType(string type) {
    this->type = type;
}

void Server::setServerId(int id) {
    this->serverId = serverId;
}

void Server::setCPUCapacity(int CPUCapacity) {
    this->CPUCapacity = CPUCapacity;
}

void Server::setPartACPULeft(int partACPULeft) {
    this->partACPULeft = partACPULeft;
}

void Server::setPartBCPULeft(int partBCPULeft) {
    this->partBCPULeft = partBCPULeft;
}

void Server::setMemoryCapacity(int memoryCapacity) {
    this->memoryCapacity = memoryCapacity;
}

void Server::setPartAMemoryLeft(int partAMemoryLeft) {
    this->partAMemoryLeft = partAMemoryLeft;
}

void Server::setPartBMemoryLeft(int partBMemoryLeft) {
    this->partBMemoryLeft = partBMemoryLeft;
}


void Server::setPartACPULeft(int partACPULeft) {
    this->partACPULeft = partACPULeft;
}

void Server::setPartBCPULeft(int partBCPULeft) {
    this->partBCPULeft = partBCPULeft;
}

void Server::setPartAMemoryLeft(int partAMemoryLeft) {
    this->partAMemoryLeft = partAMemoryLeft;
}

void Server::setPartBMemoryLeft(int partBMemoryLeft) {
    this->partBMemoryLeft = partBMemoryLeft;
}

void Server::setHardwareCost(int hardwareCost) {
    this->hardwareCost = hardwareCost;
}

void Server::setDailyCost(int dailyCost) {
    this->dailyCost = dailyCost;
}

void Server::setStatus(bool status) {
    this->status = status;
}