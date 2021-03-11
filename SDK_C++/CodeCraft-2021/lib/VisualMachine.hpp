#include<iostream>
#include<string.h>
#include<VisualMachine.h>

using namespace std;




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