#include<iostream>
#include<memory>
#include<string.h>
#include"Server.h"

using namespace std;

Server::Server():
    type(""),
    serverId(0),
    CPUCapacity(0),
    memoryCapacity(0),
    partACPULeft(0),
    partBCPULeft(0),
    partAMemoryLeft(0),
    partBMemoryLeft(0),
    hardwareCost(0),
    dailyCost(0),
    status(0)
{}

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
    status(0)
{}

Server::Server(string type, int CPUCapacity, int memoryCapacity, int hardwareCost, int dailyCost)
    : type(type),
    CPUCapacity(CPUCapacity),
    memoryCapacity(memoryCapacity),
    partACPULeft(CPUCapacity / 2),
    partBCPULeft(CPUCapacity / 2),
    partAMemoryLeft(memoryCapacity / 2),
    partBMemoryLeft(memoryCapacity / 2),
    hardwareCost(hardwareCost),
    dailyCost(dailyCost),
    status(0)
{}

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
    this->serverId = id;
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

void Server::setHardwareCost(int hardwareCost) {
    this->hardwareCost = hardwareCost;
}

void Server::setDailyCost(int dailyCost) {
    this->dailyCost = dailyCost;
}

void Server::setStatus(bool status) {
    this->status = status;
}