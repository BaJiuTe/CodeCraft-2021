#include<iostream>
#include<string.h>
#include"Server.h"

using namespace std;

/*
/ �������Ƿ���ʹ��
/ return bool
/ 0 û��ʹ�ã�1 ��ʹ��
*/
bool Server::isUsed() {
    return CPUCapacity != CPULeft || memoryCapacity != memoryLeft;
}


/*
/ ����������������ܳɱ�
/ return int
*/
int Server::totalCost() {
    return hardwareCost + runDay * dailyCost;
}




/*
/ Server �๹�캯��
*/
Server::Server(string type, int id, int CPUCapacity, int CPULeft, int memoryCapacity, int memoryLeft, int partACPULeft, int partBCPULeft,
    int partAMemoryLeft, int partBMemoryLeft, int hardwareCost, int dailyCost, int runDay)
    :type(type),
    id(id), 
    CPUCapacity(CPUCapacity),
    CPULeft(CPULeft),
    memoryCapacity(memoryCapacity),
    memoryLeft(memoryLeft),
    partACPULeft(partACPULeft),
    partBCPULeft(partBCPULeft),
    partAMemoryLeft(partAMemoryLeft), 
    partBMemoryLeft(partBMemoryLeft),
    hardwareCost(hardwareCost), 
    dailyCost(dailyCost),
    runDay(runDay)
{}

//���캯����ֻ��Ҫ��������ʱ�ĳ�ʼ״̬��
Server::Server(string type, int CPUCapacity, int memoryCapacity, int hardwareCost, int dailyCost)
    : type(type), 
    id(0), 
    CPUCapacity(CPUCapacity),
    CPULeft(CPULeft),
    memoryCapacity(memoryCapacity), 
    memoryLeft(memoryCapacity),
    partACPULeft(CPUCapacity), 
    partBCPULeft(CPUCapacity),
    partAMemoryLeft(memoryCapacity), 
    partBMemoryLeft(memoryCapacity),
    hardwareCost(hardwareCost),
    dailyCost(dailyCost), 
    runDay(0)
{}


Server::Server() {}

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