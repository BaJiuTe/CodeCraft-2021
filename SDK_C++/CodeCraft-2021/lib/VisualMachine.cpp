#include<iostream>
#include<string>
#include"VisualMachine.h"

using namespace std;

/*
    / VisualMachine 类构造函数
    */
VisualMachine::VisualMachine(string type, int id, int CPUNeed, int memoryNeed, int sigle):
type(type),id(id),CPUNeed(CPUNeed),memoryNeed(memoryNeed),sigle(sigle)
{}

//无参数的默认构造函数
VisualMachine::VisualMachine() {};

// getter

string VisualMachine::getType() {
    return type;
}

int VisualMachine::getId() {
    return id;
}

int VisualMachine::getCPUNeed() {
    return CPUNeed;
}

int VisualMachine::getMemoryNeed() {
    return memoryNeed;
}

int VisualMachine::getSigle() {
    return sigle;
}

int VisualMachine::getServerId() {
    return serverId;
}

// setter
void VisualMachine::setType(string type) {
    this->type = type;
}

void VisualMachine::setId(int id) {
    this->id = id;
}

void VisualMachine::setCPUNeed(int CPUNeed) {
    this->CPUNeed = CPUNeed;
}

void VisualMachine::setMemoryNeed(int memoryNeed) {
    this->memoryNeed = memoryNeed;
}

void VisualMachine::setSigle(int sigle) {
    this->sigle = sigle;
}

void VisualMachine::setServerId(int serverId) {
    this->serverId = serverId;
}