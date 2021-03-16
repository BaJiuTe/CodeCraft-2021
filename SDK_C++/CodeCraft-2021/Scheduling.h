#include<iostream>
#include<memory>
#include<string>
#include"Server.h"
#include"VisualMachine.h"

using namespace std;

class VisualMachine;
class Server;


class Scheduling {
public:


    /**
     * 部署一个虚拟机
     * input BoughtServ：已经购买的服务器的 map
     * input VMsaleable：可购买的虚拟机列表的 map
     * input VMType：虚拟机型号
     * input VMId：虚拟机 id
     */
    void showMessage(map<string, shared_ptr<VisualMachine>> VMsaleable, map<int, shared_ptr<Server>> BoughtServ, map<int, shared_ptr<VisualMachine>> DeployedVM) {

        /*cout << "============可购买的服务器列表============" << endl;
        for (auto iter : SERpurcheable) {
            cout << "（" << iter.second->getType() << "，" << iter.second->getServerId() << ", " << iter.second->getPartACPULeft() << ", " << iter.second->getPartBCPULeft() << ", " << iter.second->getPartAMemoryLeft() << ", " << iter.second->getPartBMemoryLeft() << ")" << endl;
        }
        cout << "========================================" << endl;


        cout << "============可购买的虚拟机列表============" << endl;
        for (auto iter : VMsaleable) {
            cout << "（" << iter.second->getType() << "，" << iter.second->getVMId() << ", " << iter.second->getCPUNeed() << ", " << iter.second->getMemoryNeed() << ", " << iter.second->getNodeType() << ", " << iter.second->getServerId() << ", " << iter.second->getDeployNode() << ")" << endl;
        }
        cout << "========================================" << endl;*/

        cout << "============已购买的服务器资源列表============" << endl;
        for (auto iter : BoughtServ) {
            cout << "（" << iter.second->getType() << "，" << iter.second->getServerId() << ", " << iter.second->getPartACPULeft() << ", " << iter.second->getPartBCPULeft() << ", " << iter.second->getPartAMemoryLeft() << ", " << iter.second->getPartBMemoryLeft() << ")" << endl;
        }
        cout << "========================================" << endl;

        cout << "============已部署的虚拟机列表============" << endl;
        for (auto iter : DeployedVM) {
            cout << "（" << iter.second->getType() << "，" << iter.second->getVMId() << ", " << iter.second->getCPUNeed() << ", " << iter.second->getMemoryNeed() << ", " << iter.second->getNodeType() << ", " << iter.second->getServerId() << ", " << iter.second->getDeployNode() << ")" << endl;
        }
        cout << "========================================" << endl;

    }


    /**
    * 添加一个虚拟机
    * input map<int, Server&>BoughtServ：已经购买的服务器列表
    * input shared_ptr<VisualMachine>>& DeployedVM:已经部署的虚拟机
    * input map<string, shared_ptr<VisualMachine>>& VMsaleable：可购买的虚拟机
    * input string VMType：虚拟机型号
    * input int VMId：虚拟机id
    * output ：void
    */
    void addVM(map<int, shared_ptr<Server>>& BoughtServ, map<int, shared_ptr<VisualMachine>>& DeployedVM, 
        map<string, shared_ptr<VisualMachine>>& VMsaleable, string VMType, int VMId) {

        

        shared_ptr<VisualMachine> VM = make_shared<VisualMachine>(*(VMsaleable[VMType]));

        VM->setVMId(VMId);
        char flag='\0';
        shared_ptr<Server> addServer = this->findServerAddVM(BoughtServ, VM, flag);
        int serverId = addServer->getServerId();
        VM->setServerId(serverId);

        char ch = this->addUpdate(addServer, VM,flag);

        DeployedVM[VMId] = VM;


        // 打印控制台信息
        if (ch == 'C') {
            cout << "(" << serverId << ")" << endl;
        }
        else {
            cout << "(" << serverId << ", " << ch << ")" << endl;
        }
    }


    /**
     * 根据策略，找到可以部署虚拟机的服务器。当前策略：但凡服务器资源够用，就部署上去
     * input map<int, Server&>BoughtServ：已经购买的服务器列表
     * input map<string, shared_ptr<VisualMachine>> VMsaleable：可购买虚拟机的列表
     * input string VMType：需要部署的虚拟机类型
     * return Server：返回可部署的服务器对象
     */
    shared_ptr<Server> findServerAddVM(map<int, shared_ptr<Server>>& BoughtServ, shared_ptr<VisualMachine> &VM, char & flag) {
        
        //shared_ptr<Server> ret=make_shared<Server>();

        // 遍历所有已经购买好的服务器的 m
        for (auto iter : BoughtServ) {
            if (VM->getNodeType() == 0) { // 虚拟机是单节点的，有一个节点达到要求，返回这个服务器对象
                if ((iter.second->getPartACPULeft() > VM->getCPUNeed() && iter.second->getPartAMemoryLeft() > VM->getMemoryNeed())) 
                {
                    flag='A';
                    return iter.second;
                    break;
                }else if(iter.second->getPartBCPULeft() > VM->getCPUNeed() && iter.second->getPartBMemoryLeft() > VM->getMemoryNeed()) {
                        flag = 'B';
                            return iter.second;
                }
            }
            else { // 虚拟机是双节点的，必须四类资源都满足要求
                if (iter.second->getPartACPULeft() > (VM->getCPUNeed() / 2) && iter.second->getPartBCPULeft() > (VM->getCPUNeed() / 2) &&
                    iter.second->getPartAMemoryLeft() > (VM->getMemoryNeed() / 2) && iter.second->getPartBMemoryLeft() > (VM->getMemoryNeed() / 2)
                    ) {
                    flag = 'C';
                    return iter.second;
                    break;
                }
            }
        }
       // cout << "部署的服务器 id 为：" << ret->getServerId() << endl;
        //return ret;
    }


    /**
     * 部署虚拟机到服务器上，更新服务器的资源信息，并打印部署控制台信息
     * input shared_ptr<Server> addServer：要部署的服务器
     * input shared_ptr<VisualMachine> VM：要部署的虚拟机
     * return char：返回部署的节点类型 A | B | C
     */
    char addUpdate(shared_ptr<Server>& updateServer, const shared_ptr<VisualMachine>& VM, char& flag) {
        // 更新服务器的数据
        if ('A'==flag) {
            updateServer->setPartACPULeft(updateServer->getPartACPULeft() - VM->getCPUNeed());
            updateServer->setPartAMemoryLeft(updateServer->getPartAMemoryLeft() - VM->getMemoryNeed());
            VM->setDeployNode('A');
        }
        else if ('B' == flag) {
            updateServer->setPartBCPULeft(updateServer->getPartBCPULeft() - VM->getCPUNeed());
            updateServer->setPartBMemoryLeft(updateServer->getPartBMemoryLeft() - VM->getMemoryNeed());
            VM->setDeployNode('B');
        }
        else {  // 双节点，平分
            updateServer->setPartACPULeft(updateServer->getPartACPULeft() - VM->getCPUNeed() / 2);
            updateServer->setPartAMemoryLeft(updateServer->getPartAMemoryLeft() - VM->getMemoryNeed() / 2);
            updateServer->setPartBCPULeft(updateServer->getPartBCPULeft() - VM->getCPUNeed() / 2);
            updateServer->setPartBMemoryLeft(updateServer->getPartBMemoryLeft() - VM->getMemoryNeed() / 2);
            VM->setDeployNode('C');
        }
        updateServer->setStatus(true);

        // 把虚拟机部署到服务器上
        updateServer->mountedVM[VM->getVMId()] = VM;

        return VM->getDeployNode();
    }




    /**
     * 删除一个虚拟机
     * input BoughtServ：已经购买的服务器的 map
     * input DeployedVM：已经部署的虚拟机的 map
     * input VMId：虚拟机 id
     * return void
     */
    void delVM(map<int, shared_ptr<Server>>& BoughtServ, map<int, shared_ptr<VisualMachine>>& DeployedVM, int VMId) {
        // 找到要删除的虚拟机
        shared_ptr<VisualMachine> VM = DeployedVM[VMId];

        // 找到虚拟机部署的服务器的 id
        int serverId = VM->getServerId();

        // 找到服务器对象
        shared_ptr<Server> delServer = BoughtServ[serverId];

        // 更新服务器资源
        this->delUpdate(delServer, VM);

        // 将虚拟机从已部署的 map 中移除
        DeployedVM.erase(VMId);
    }



    /**
    * 删除该服务器里面的一个虚拟机
    * input shared_ptr<Server> & updateServer：需要更新的服务器
    * input const shared_ptr<VisualMachine> &VM：需要删除的虚拟机
    * output ：void
    */
    void delUpdate(shared_ptr<Server>& updateServer, const shared_ptr<VisualMachine>& VM) {

        // 对服务器数据进行更新
        switch (VM->getDeployNode()) {
        case 'A':
            updateServer->setPartACPULeft(updateServer->getPartACPULeft() + VM->getCPUNeed());
            updateServer->setPartAMemoryLeft(updateServer->getPartAMemoryLeft() + VM->getMemoryNeed());
            break;
        case 'B':
            updateServer->setPartBCPULeft(updateServer->getPartBCPULeft() + VM->getCPUNeed());
            updateServer->setPartBMemoryLeft(updateServer->getPartBMemoryLeft() + VM->getMemoryNeed());
            break;
        case 'C':
            updateServer->setPartACPULeft(updateServer->getPartACPULeft() + VM->getCPUNeed() / 2);
            updateServer->setPartAMemoryLeft(updateServer->getPartAMemoryLeft() + VM->getMemoryNeed() / 2);
            updateServer->setPartBCPULeft(updateServer->getPartBCPULeft() + VM->getCPUNeed() / 2);
            updateServer->setPartBMemoryLeft(updateServer->getPartBMemoryLeft() + VM->getMemoryNeed() / 2);
            break;
        default:break;
        }

        // 将虚拟机从服务器挂载列表中移除
        int VMId = VM->getVMId();
        updateServer->mountedVM.erase(VMId);
    }


};


