#include<iostream>
#include<string>
#include"Server.h"
#include"VisualMachine.h"

using namespace std;

/*
*  VisualMachine 类构造函数
*/
VisualMachine::VisualMachine(string type, int id, int CPUNeed, int memoryNeed, int nodeType):
    type(type),
    VMId(VMId),
    CPUNeed(CPUNeed),
    memoryNeed(memoryNeed),
    nodeType(nodeType)
{}

// 无参数的默认构造函数
VisualMachine::VisualMachine() {};




// getter

string VisualMachine::getType() {
    return type;
}

int VisualMachine::getVMId() {
    return VMId;
}

int VisualMachine::getCPUNeed() {
    return CPUNeed;
}

int VisualMachine::getMemoryNeed() {
    return memoryNeed;
}

int VisualMachine::getNodeType() {
    return nodeType;
}

int VisualMachine::getServerId() {
    return serverId;
}

char VisualMachine::getDeployNode() {
    return deployNode;
}

double VisualMachine::getScore()
{
    double ret;
    ret = (double)getCPUNeed() / getMemoryNeed();
    return ret;
}

// setter
void VisualMachine::setType(string type) {
    this->type = type;
}

void VisualMachine::setVMId(int VMId) {
    this->VMId = VMId;
}

void VisualMachine::setCPUNeed(int CPUNeed) {
    this->CPUNeed = CPUNeed;
}

void VisualMachine::setMemoryNeed(int memoryNeed) {
    this->memoryNeed = memoryNeed;
}

void VisualMachine::setNodeType(int nodeType) {
    this->nodeType = nodeType;
}

void VisualMachine::setServerId(int serverId) {
    this->serverId = serverId;
}

void VisualMachine::setDeployNode(char deployNode) {
    this->deployNode = deployNode;
}



