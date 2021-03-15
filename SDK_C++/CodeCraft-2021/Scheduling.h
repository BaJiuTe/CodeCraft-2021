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
     * ����һ�������
     * input BoughtServ���Ѿ�����ķ������� map
     * input VMsaleable���ɹ����������б�� map
     * input VMType��������ͺ�
     * input VMId������� id
     */
    void addVM(map<int, shared_ptr<Server>>& BoughtServ, map<int, shared_ptr<VisualMachine>>& DeployedVM, 
        map<string, shared_ptr<VisualMachine>>& VMsaleable, string VMType, int VMId) {

        shared_ptr<VisualMachine> VM = make_shared<VisualMachine>(*(VMsaleable[VMType]));

        VM->setVMId(VMId);

        shared_ptr<Server> addServer = this->findServerAddVM(BoughtServ, VM);
        int serverId = addServer->getServerId();
        VM->setServerId(serverId);

        char ch = this->addUpdate(addServer, VM);

        DeployedVM[VMId] = VM;


        // ��ӡ����̨��Ϣ
        if (ch == 'C') {
            cout << "(" << serverId << ")" << endl;
        }
        else {
            cout << "(" << serverId << ", " << ch << ")" << endl;
        }
    }


    /**
     * ���ݲ��ԣ��ҵ����Բ���������ķ���������ǰ���ԣ�������������Դ���ã��Ͳ�����ȥ
     * input map<int, Server&>BoughtServ���Ѿ�����ķ������б�
     * input map<string, shared_ptr<VisualMachine>> VMsaleable���ɹ�����������б�
     * input string VMType����Ҫ��������������
     * return Server�����ؿɲ���ķ���������
     */
    shared_ptr<Server> findServerAddVM(map<int, shared_ptr<Server>>& BoughtServ, shared_ptr<VisualMachine> VM) {
        shared_ptr<Server> ret;

        // ���������Ѿ�����õķ������� m
        for (auto iter : BoughtServ) {
            if (VM->getNodeType() == 0) { // ������ǵ��ڵ�ģ���һ���ڵ�ﵽҪ�󣬷����������������
                if ((iter.second->getPartACPULeft() > VM->getCPUNeed() && iter.second->getPartAMemoryLeft() > VM->getMemoryNeed()) ||
                    (iter.second->getPartBCPULeft() > VM->getCPUNeed() && iter.second->getPartBMemoryLeft() > VM->getMemoryNeed()))
                {
                    ret = iter.second;
                    break;
                }
            }
            else { // �������˫�ڵ�ģ�����������Դ������Ҫ��
                if (iter.second->getPartACPULeft() > (VM->getCPUNeed() / 2) && iter.second->getPartBCPULeft() > (VM->getCPUNeed() / 2) &&
                    iter.second->getPartAMemoryLeft() > (VM->getMemoryNeed() / 2) && iter.second->getPartBMemoryLeft() > (VM->getMemoryNeed() / 2)
                    ) {
                    ret = iter.second;
                    break;
                }
            }
        }
       // cout << "����ķ����� id Ϊ��" << ret->getServerId() << endl;
        return ret;
    }


    /**
     * ������������������ϣ����·���������Դ��Ϣ������ӡ�������̨��Ϣ
     * input shared_ptr<Server> addServer��Ҫ����ķ�����
     * input shared_ptr<VisualMachine> VM��Ҫ����������
     * return char�����ز���Ľڵ����� A | B | C
     */
    char addUpdate(shared_ptr<Server>& updateServer, const shared_ptr<VisualMachine>& VM) {
        // ���·�����������
        if (VM->getNodeType() == 0) {  // ���ڵ㣬�ĸ��ڵ�ʣ��ռ�࣬�ͷ�����
            if (updateServer->getPartACPULeft() > updateServer->getPartBCPULeft()) {
                updateServer->setPartACPULeft(updateServer->getPartACPULeft() - VM->getCPUNeed());
                updateServer->setPartAMemoryLeft(updateServer->getPartAMemoryLeft() - VM->getMemoryNeed());
                VM->setDeployNode('A');
            }
            else {
                updateServer->setPartBCPULeft(updateServer->getPartBCPULeft() - VM->getCPUNeed());
                updateServer->setPartBMemoryLeft(updateServer->getPartBMemoryLeft() - VM->getMemoryNeed());
                VM->setDeployNode('B');

            }
        }
        else {  // ˫�ڵ㣬ƽ��
            updateServer->setPartACPULeft(updateServer->getPartACPULeft() - VM->getCPUNeed() / 2);
            updateServer->setPartAMemoryLeft(updateServer->getPartAMemoryLeft() - VM->getMemoryNeed() / 2);
            updateServer->setPartBCPULeft(updateServer->getPartBCPULeft() - VM->getCPUNeed() / 2);
            updateServer->setPartBMemoryLeft(updateServer->getPartBMemoryLeft() - VM->getMemoryNeed() / 2);
            VM->setDeployNode('C');
        }
        updateServer->setStatus(true);

        // ����������𵽷�������
        updateServer->mountedVM[VM->getVMId()] = VM;

        return VM->getDeployNode();
    }




    /**
     * ɾ��һ�������
     * input BoughtServ���Ѿ�����ķ������� map
     * input DeployedVM���Ѿ������������� map
     * input VMId������� id
     * return void
     */
    void delVM(map<int, shared_ptr<Server>>& BoughtServ, map<int, shared_ptr<VisualMachine>>& DeployedVM, int VMId) {
        // �ҵ�Ҫɾ���������
        shared_ptr<VisualMachine> VM = DeployedVM[VMId];

        // �ҵ����������ķ������� id
        int serverId = VM->getServerId();

        // �ҵ�����������
        shared_ptr<Server> delServer = BoughtServ[serverId];

        // ���·�������Դ
        this->delUpdate(delServer, VM);

        // ����������Ѳ���� map ���Ƴ�
        DeployedVM.erase(VMId);
    }



    /**
    * ɾ���÷����������һ�������
    * input shared_ptr<Server> & updateServer����Ҫ���µķ�����
    * input const shared_ptr<VisualMachine> &VM����Ҫɾ���������
    * output ��void
    */
    void delUpdate(shared_ptr<Server>& updateServer, const shared_ptr<VisualMachine>& VM) {

        // �Է��������ݽ��и���
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

        // ��������ӷ����������б����Ƴ�
        int VMId = VM->getVMId();
        updateServer->mountedVM.erase(VMId);
    }


};