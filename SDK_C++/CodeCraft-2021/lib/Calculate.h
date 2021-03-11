#include<iostream>
#include <vector>
#include "Server.h"


using namespace std;

class Calculate{
private:
    static int serverID;


public:

    /*
    * 计算服务器总成本
    * input: 服务器的列表
    * output: 总成本
    */
    int calculateTotalCost(vector<Server> ServerList) {
        int cost = 0;
        for (Server server : ServerList) {
            cost += server.totalCost();
        }
        return cost;
    }

    

};