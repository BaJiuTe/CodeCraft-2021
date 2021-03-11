#include<iostream>
#include<string.h>
#include<Server.h>

using namespace std;

/*
/ 服务器是否在使用
/ return bool
/ 0 没在使用，1 在使用
*/
bool Server::isUsed() {
    return CPUCapacity != CPULeft || memoryCapacity != memoryLeft;
}


/*
/ 计算这个服务器的总成本
/ return int
*/
int Server::totalCost() {
    return hardwareCost + runDay * dailyCost;
}




/*
/ Server 类构造函数
*/ 
Server::Server(string type, int id, int CPUCapacity, int CPULeft, int memoryCapacity,int memoryLeft, int partACPULeft, int partBCPULeft,
                int partAMemoryLeft, int partBMemoryLeft, int hardwareCost, int dailyCost, int runDay) 
                :type(type), id(id), CPUCapacity(CPUCapacity), memoryCapacity(memoryCapacity), memoryLeft(memoryLeft), partACPULeft(partACPULeft), partBCPULeft(partBCPULeft),
                partAMemoryLeft(partAMemoryLeft), partBMemoryLeft(partBMemoryLeft), hardwareCost(hardwareCost), dailyCost(dailyCost), runDay(runDay)                
                {}


// getter

string Server::getType() {
    return type;
}

int Server::getId() {
    return id;
}

int Server::getCPUCapacity() {
    return CPUCapacity;
}

int Server::getCPULeft() {
    return CPULeft;
}

int Server::getMemoryCapacity() {
    return memoryCapacity;
}

int Server::getMemoryLeft() {
    return memoryLeft;
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

int Server::getRunDay() {
    return runDay;
}



// setter

void Server::setType(string type) {
    this->type = type;
}

void Server::setId(int id) {
    this->id = id;
}

void Server::setCPUCapacity(int CPUCapacity) {
    this->CPUCapacity = CPUCapacity;
}

void Server::setCPULeft(int CPULeft) {
    this->CPULeft = CPULeft;
}

void Server::setMemoryCapacity(int memoryCapacity) {
    this->memoryCapacity = memoryCapacity;
}

void Server::setMemoryLeft(int memoryLeft) {
    this->memoryLeft = memoryLeft;
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

void Server::setRunDay(int runDay) {
    this->runDay = runDay;
}