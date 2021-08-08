#include<iostream>
#include<memory>
#include<string>
#include"Server.h"
#include"VisualMachine.h"
#include<memory>
#include<cmath>
#include"Resource.h"
using namespace std;

class VisualMachine;
class Server;

class Scheduling {
public:

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


    void addVM(map<int, shared_ptr<Server>>& BoughtServ, map<int, shared_ptr<VisualMachine>>& DeployedVM, map< string, shared_ptr< Server > >& SERpurcheable,
        map<string, shared_ptr<VisualMachine>>& VMsaleable, string VMType, int VMId) {

        shared_ptr<VisualMachine> VM = make_shared<VisualMachine>(*(VMsaleable[VMType]));

        VM->setVMId(VMId);
        char flag = '\0';
        shared_ptr<Server> addServer = this->findServerAddVM(BoughtServ, VM, flag);
        int serverId = addServer->getServerId();

        VM->setServerId(serverId);
        DeployedVM[VMId] = VM;
        char ch = this->addUpdate(addServer, VM, flag);
        // 打印控制台信息
        if (ch == 'C') {
            cout << "(" << serverId << ")" << endl;
        }
        else {
            cout << "(" << serverId << ", " << ch << ")" << endl;
        }
    }




    ////用于演练的add Vm
    void MockaddVM(map<int, shared_ptr<Server>>& BoughtServ, map<int, shared_ptr<VisualMachine>>& DeployedVM, map< string, shared_ptr< Server > >& SERpurcheable,
        map<string, shared_ptr<VisualMachine>>& VMsaleable, string VMType, int VMId, int* count, int* MockSer_id, string& type) {

        shared_ptr<VisualMachine> VM = make_shared<VisualMachine>(*(VMsaleable[VMType]));
        int tempid = *MockSer_id;
        VM->setVMId(VMId);
        char flag = '\0';

        shared_ptr<Server> addServer = findServerAddVM(BoughtServ, VM, flag);
        while (addServer.get() == nullptr) {

            (*count)++;
            auto temp = (*(SERpurcheable[type]));
            auto temp_ptr = make_shared<Server>(temp);
            temp_ptr->setServerId(tempid);
            BoughtServ[tempid++] = temp_ptr;

            // 买了之后继续查找
            addServer = this->findServerAddVM(BoughtServ, VM, flag);
        }

        int serverId = addServer->getServerId();
        VM->setServerId(serverId);

        char ch = this->addUpdate(addServer, VM, flag);

        DeployedVM[VMId] = VM;
        *MockSer_id = tempid;

        // 打印控制台信息
        /*if (ch == 'C') {
            cout << "(" << serverId << ")" << endl;
        }
        else {
            cout << "(" << serverId << ", " << ch << ")" << endl;
        }*/
    }


    /**
     * 根据策略，找到可以部署虚拟机的服务器。当前策略：但凡服务器资源够用，就部署上去
     * input map<int, Server&>BoughtServ：已经购买的服务器列表
     * input map<string, shared_ptr<VisualMachine>> VMsaleable：可购买虚拟机的列表
     * input string VMType：需要部署的虚拟机类型
     * return Server：返回可部署的服务器对象
     */
    shared_ptr<Server> findServerAddVM(map<int, shared_ptr<Server>>& BoughtServ, shared_ptr<VisualMachine>& VM, char& flag) {

        shared_ptr<Server> ret;
        int mark = 0;
        //double rate = 10000000.0;

        //pair<const int, shared_ptr<Server>> *it=nullptr;
        int min = 10000;
        int CPU = 0, Mem = 0;

        // 遍历所有已经购买好的服务器的 m
        for (auto iter : BoughtServ) {
            if (VM->getNodeType() == 0) { // 虚拟机是单节点的，有一个节点达到要求，返回这个服务器对象

                //if (iter.second->isAmore()) {
                if ((iter.second->getPartACPULeft() >= VM->getCPUNeed() && iter.second->getPartAMemoryLeft() >= VM->getMemoryNeed()))
                {
                    if (((iter.second->getPartACPULeft() - VM->getCPUNeed()) + (iter.second->getPartAMemoryLeft() - VM->getMemoryNeed())) < min)
                    {
                        flag = 'A';
                        ret = iter.second;
                        min = (iter.second->getPartACPULeft() - VM->getCPUNeed()) + (iter.second->getPartAMemoryLeft() - VM->getMemoryNeed());
                    }
                }
                //}
                //else {
                if (iter.second->getPartBCPULeft() >= VM->getCPUNeed() && iter.second->getPartBMemoryLeft() >= VM->getMemoryNeed()) {

                    if (((iter.second->getPartBCPULeft() - VM->getCPUNeed()) + (iter.second->getPartBMemoryLeft() - VM->getMemoryNeed())) < min)
                    {
                        flag = 'B';
                        ret = iter.second;
                        min = ((iter.second->getPartBCPULeft() - VM->getCPUNeed()) + (iter.second->getPartBMemoryLeft() - VM->getMemoryNeed()));
                    }
                }
            }
            else
            { // 虚拟机是双节点的，必须四类资源都满足要求
                if (iter.second->getPartACPULeft() >= (VM->getCPUNeed() / 2) && iter.second->getPartBCPULeft() >= (VM->getCPUNeed() / 2) &&
                    iter.second->getPartAMemoryLeft() >= (VM->getMemoryNeed() / 2) && iter.second->getPartBMemoryLeft() >= (VM->getMemoryNeed() / 2))
                {
                    CPU = (iter.second->getPartACPULeft() - (VM->getCPUNeed() / 2)) + (iter.second->getPartBCPULeft() - (VM->getCPUNeed() / 2));
                    Mem = (iter.second->getPartAMemoryLeft() - (VM->getMemoryNeed() / 2)) + (iter.second->getPartBMemoryLeft() - (VM->getMemoryNeed() / 2));
                    if (min > (CPU + Mem))
                    {
                        min = CPU + Mem;
                        flag = 'C';
                        ret = iter.second;
                    }
                }
                //}
            }
        }
        return ret;
    }




    /**
     * 部署虚拟机到服务器上，更新服务器的资源信息，并打印部署控制台信息
     * input shared_ptr<Server> addServer：要部署的服务器
     * input shared_ptr<VisualMachine> VM：要部署的虚拟机
     * return char：返回部署的节点类型 A | B | C
     */
    char addUpdate(shared_ptr<Server>& updateServer, const shared_ptr<VisualMachine>& VM, char& flag) {
        // 更新服务器的数据
        if ('A' == flag) {
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

        //cout <<updateServer->getServerId()<< "  A:" << updateServer->getPartACPULeft() << "  " << updateServer->getPartAMemoryLeft() << endl;
        //cout << updateServer->getServerId()<< "  B:" << updateServer->getPartBCPULeft() << "  " << updateServer->getPartBMemoryLeft() << endl;
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


        int VMId = VM->getVMId();
        updateServer->mountedVM.erase(VMId);

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
        //cout <<updateServer->getServerId()<< "  A:" << updateServer->getPartACPULeft() << "  " << updateServer->getPartAMemoryLeft() << endl;
        //cout << updateServer->getServerId()<< "  B:" << updateServer->getPartBCPULeft() << "  " << updateServer->getPartBMemoryLeft() << endl;

    }

    shared_ptr<Server> Magrition_findServerAddVM(map<int, shared_ptr<Server>>& BoughtServ, shared_ptr<VisualMachine>& VM, char& flag,
        shared_ptr<Server>& Self, Resource& s)
    {

        shared_ptr<Server> ret;
        // int mark = 0;
        //double rate = 10000000.0;

        //pair<const int, shared_ptr<Server>> *it=nullptr;
        // map<int, shared_ptr<Server>> AllServ;
        // AllServ.insert(s.ClassA0.begin(), s.ClassA0.end());
        // AllServ.insert(s.ClassA1.begin(), s.ClassA1.end());
        // AllServ.insert(s.ClassB0.begin(), s.ClassB0.end());
        // AllServ.insert(s.ClassB1.begin(), s.ClassB1.end());
        // AllServ.insert(s.ClassC.begin(), s.ClassC.end());
        // AllServ.insert(s.ClassD.begin(), s.ClassD.end());
        // AllServ.insert(s.ClassN.begin(), s.ClassN.end());

        // for(auto iter : AllServ)
        // {
        //     if (iter.second == Self)
        //     {
        //         continue;
        //     }
        //     int min = 1000;
        //     int CPU = 0, Mem = 0;

        //     if (VM->getNodeType() == 0)
        //     { // 虚拟机是单节点的，有一个节点达到要求，返回这个服务器对象

        //         if ((iter.second->getPartACPULeft() >= VM->getCPUNeed() && iter.second->getPartAMemoryLeft() >= VM->getMemoryNeed()))
        //         {
        //             if (((iter.second->getPartACPULeft() - VM->getCPUNeed()) + (iter.second->getPartAMemoryLeft() - VM->getMemoryNeed())) < min)
        //             {
        //                 flag = 'A';
        //                 ret = iter.second;
        //                 min = (iter.second->getPartACPULeft() - VM->getCPUNeed()) + (iter.second->getPartAMemoryLeft() - VM->getMemoryNeed());
        //             }
        //         }
        //         else
        //         {
        //             if (iter.second->getPartBCPULeft() >= VM->getCPUNeed() && iter.second->getPartBMemoryLeft() >= VM->getMemoryNeed())
        //             {

        //                 if (((iter.second->getPartBCPULeft() - VM->getCPUNeed()) + (iter.second->getPartBMemoryLeft() - VM->getMemoryNeed())) < min)
        //                 {
        //                     flag = 'B';
        //                     ret = iter.second;
        //                     min = (iter.second->getPartBCPULeft() - VM->getCPUNeed()) + (iter.second->getPartBMemoryLeft() - VM->getMemoryNeed());
        //                 }
        //             }
        //         }
        //     }
        //     else
        //     { // 虚拟机是双节点的，必须四类资源都满足要求
        //         if (iter.second->getPartACPULeft() >= (VM->getCPUNeed() / 2) && iter.second->getPartBCPULeft() >= (VM->getCPUNeed() / 2) &&
        //             iter.second->getPartAMemoryLeft() >= (VM->getMemoryNeed() / 2) && iter.second->getPartBMemoryLeft() >= (VM->getMemoryNeed() / 2))
        //         {
        //             CPU = (iter.second->getPartACPULeft() - (VM->getCPUNeed() / 2)) + (iter.second->getPartBCPULeft() - (VM->getCPUNeed() / 2));
        //             Mem = (iter.second->getPartAMemoryLeft() - (VM->getMemoryNeed() / 2)) + (iter.second->getPartBMemoryLeft() - (VM->getMemoryNeed() / 2));
        //             if (min > (CPU + Mem))
        //             {
        //                 min = CPU + Mem;
        //                 flag = 'C';
        //                 ret = iter.second;
        //             }
        //         }
        //     }

        // 遍历所有已经购买好的服务器的 m
        for (auto iter : BoughtServ)
        {

            if (iter.second == Self)
            {
                // return iter.second;
                return ret;
            }

            // int min = 1000;
            // int CPU = 0, Mem = 0;

            if (VM->getNodeType() == 0)
            { // 虚拟机是单节点的，有一个节点达到要求，返回这个服务器对象

                //if (iter.second->isAmore()) {
                if ((iter.second->getPartACPULeft() >= VM->getCPUNeed() && iter.second->getPartAMemoryLeft() >= VM->getMemoryNeed()))
                {
                    // if(((iter.second->getPartACPULeft() - VM->getCPUNeed()) + (iter.second->getPartAMemoryLeft() - VM->getMemoryNeed())) < min)
                    // {
                    //     flag = 'A';
                    //     ret = iter.second;
                    //     min = (iter.second->getPartACPULeft() - VM->getCPUNeed()) + (iter.second->getPartAMemoryLeft() - VM->getMemoryNeed());
                    // }

                    flag = 'A';
                    ret = iter.second;
                    break;

                    //}
                }
                //}
                //else {
                if (iter.second->getPartBCPULeft() >= VM->getCPUNeed() && iter.second->getPartBMemoryLeft() >= VM->getMemoryNeed())
                {

                    // if(((iter.second->getPartBCPULeft() - VM->getCPUNeed()) + (iter.second->getPartBMemoryLeft() - VM->getMemoryNeed())) < min)
                    // {
                    //     flag = 'B';
                    //     ret = iter.second;
                    //     min = (iter.second->getPartBCPULeft() - VM->getCPUNeed()) + (iter.second->getPartBMemoryLeft() - VM->getMemoryNeed());
                    // }
                    flag = 'B';
                    ret = iter.second;
                    break;

                    //}
                }
                //}
            }
            else
            { // 虚拟机是双节点的，必须四类资源都满足要求
                if (iter.second->getPartACPULeft() >= (VM->getCPUNeed() / 2) && iter.second->getPartBCPULeft() >= (VM->getCPUNeed() / 2) &&
                    iter.second->getPartAMemoryLeft() >= (VM->getMemoryNeed() / 2) && iter.second->getPartBMemoryLeft() >= (VM->getMemoryNeed() / 2))
                {
                    // CPU = (iter.second->getPartACPULeft() - (VM->getCPUNeed() / 2)) + (iter.second->getPartBCPULeft() - (VM->getCPUNeed() / 2));
                    // Mem = (iter.second->getPartAMemoryLeft() - (VM->getMemoryNeed() / 2)) + (iter.second->getPartBMemoryLeft() - (VM->getMemoryNeed() / 2));
                    // if(min > (CPU + Mem))
                    // {
                    //     min = CPU + Mem;
                    //     flag = 'C';
                    //     ret = iter.second;
                    // }
                    flag = 'C';
                    ret = iter.second;
                    break;
                }
                //}
            }
        }
        return ret;
    }

    void MagritionaddVM(map<int, shared_ptr<Server>>& BoughtServ, map<int, shared_ptr<VisualMachine>>& DeployedVM, map< string, shared_ptr< Server > >& SERpurcheable,
        map<string, shared_ptr<VisualMachine>>& VMsaleable, shared_ptr<VisualMachine>& VM, shared_ptr<Server>& Self, Resource& s) {

        //shared_ptr<VisualMachine> VM = VMsaleable[VMType];
         //VM->setVMId(VMId);
        char flag = '\0';
        shared_ptr<Server> addServer = this->Magrition_findServerAddVM(BoughtServ, VM, flag, Self, s);
        int serverId = addServer->getServerId();

        VM->setServerId(serverId);
        DeployedVM[VM->getVMId()] = VM;
        char ch = this->addUpdate(addServer, VM, flag);
    }



    // to magrite a type of ServerList
    void MagritionList(map<int, shared_ptr<Server>>& BoughtSer, map<int, shared_ptr<VisualMachine>>& DeployedVM, int& times, int limits,
        map<string, shared_ptr<VisualMachine>>& VMsaleable, map<string, shared_ptr<Server>>& SERpurcheable,
        vector<string>& MigriationInfo, Resource& s)
    {

        if (times >= limits)
            return;

        // for (auto it = BoughtSer.rbegin(); it != BoughtSer.rend(); it++)
        // {
        for (auto it = BoughtSer.rbegin(); it != BoughtSer.rend(); it++)
        {

            auto temp = it->second->mountedVM;

            for (auto it_VM = temp.begin(); it_VM != temp.end();)
            {
                // for (auto it_VM = temp.rbegin(); it_VM != temp.rend(); it_VM++) {

                char flag = '\0';

                shared_ptr<Server> MagrationServer = Magrition_findServerAddVM(BoughtSer, it_VM->second, flag, it->second, s);

                if (MagrationServer.get() == nullptr || MagrationServer == it->second)
                {
                    return;
                }
                else
                {

                    shared_ptr<VisualMachine> tempVM_it = it_VM->second;

                    it_VM++;

                    delVM(BoughtSer, DeployedVM, tempVM_it->getVMId());
                    MagritionaddVM(BoughtSer, DeployedVM, SERpurcheable, VMsaleable, tempVM_it, it->second, s);

                    //finish input then record the infomation
                    string info;
                    if (flag == 'C')
                    {
                        string s1 = "(";
                        string s = ", ";
                        string s2 = ")";
                        info = s1 + to_string(tempVM_it->getVMId()) + s + to_string(MagrationServer->getServerId()) + s2;
                    }
                    else
                    {
                        string sf;
                        if (flag == 'A')
                            sf = "A";
                        else
                            sf = "B";

                        string s1 = "(";
                        string s = ", ";
                        string s2 = ")";
                        info = s1 + to_string(tempVM_it->getVMId()) + s + to_string(MagrationServer->getServerId()) + s + sf + s2;
                    }
                    MigriationInfo.push_back(info);
                    times++;
                    if (times >= limits)
                        return;
                }
            }
        }
    }

    void Magrition(Resource& s, map<string, shared_ptr<VisualMachine>>& VMsaleable,
        map<string, shared_ptr<Server>>& SERpurcheable, int& times, int limits, vector<string>& Magritioninfo) {

        if (times > limits)
            return;

        MagritionList(s.ClassA00, s.A00_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.ClassA0, s.A0_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.ClassA01, s.A01_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.ClassA1, s.A1_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.ClassB0, s.B0_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.ClassB1, s.B1_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.ClassC, s.C_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.ClassD, s.D_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.ClassN, s.N_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);

    }

    void MockMagrition(Resource& s, map<string, shared_ptr<VisualMachine>>& VMsaleable,
        map<string, shared_ptr<Server>>& SERpurcheable, int& times, int limits, vector<string>& Magritioninfo) {

        if (times > limits)
            return;

        MagritionList(s.MockClassA00, s.MockA00_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.MockClassA0, s.MockA0_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.MockClassA01, s.MockA01_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.MockClassA1, s.MockA1_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.MockClassB0, s.MockB0_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.MockClassB1, s.MockB1_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.MockClassC, s.MockC_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.MockClassD, s.MockD_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
        MagritionList(s.MockClassN, s.MockN_DeployedVM, times, limits, VMsaleable, SERpurcheable, Magritioninfo, s);
    }

};