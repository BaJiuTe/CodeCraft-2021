# CodeCraft-2021

## git 使用教程
1. 克隆仓库到本地当前目录
```bash
git clone git@github.com:BaJiuTe/CodeCraft-2021.git
```

2. 以后每天写代码，都需要 pull 一下仓库，更新版本
```bash
git pull origin main
```

3. 将本地仓库推送到远程仓库
```bash
git add .

git commit -m "写上你所作的更改"

git push -u origin main
```


## 文件结构说明
- 所有的代码都放在 `/CodeCraft-2021/SDK_C++/CodeCraft-2021`，包括.h .hpp .cpp
- `build_and_run.sh` 包括了`build.sh`，所以只需要执行 `./build_and_run.sh`，就行了，脚本还会自动帮我们生成 bin 目录和 build 目录
- 我们只需要往 `CodeCraft-2021.cpp` 里面写主程序就好了
- 打包提交作品的话，执行 `./CodeCraft_zip.sh` 就行

## 接口列表
### Server 类
| 参数 | 描述 |
| -- | -- |
| string type |服务器类型 |
| int serverId |服务器 id, id 从 0 递增 |
| int CPUCapacity | CPU 总容量 |
| int partACPULeft | A 节点 CPU 剩余 |
| int partBCPULeft | B 节点 CPU 剩余 |
| int memoryCapacity | 内存容量 |
| int partAMemoryLeft | A 节点内存剩余 |
| int partBMemoryLeft | B 节点内存剩余 |
| int hardwareCost | 硬件成本 |
| int dailyCost | 日常能耗成本 |
| bool status | 服务器状态，默认关闭，在 add | del | migration 的时候设置 |

| 方法 | 描述 |
| -- | -- |
| getter | 获取类里面的私有参数 |
| setter | 修改类里面的私有参数 |
| Server(string type,int CPUCapacity,int memoryCapacity,int hardwareCost,int dailyCost); | 构造函数（类型，CPU，内存，硬件成本，每日成本） |

### VisualMachine 类
| 参数 | 描述 |
| -- | -- |
| string type | 虚拟机类型 |
| int VMId | 虚拟机 id |
| int CPUNeed | CPU 需求 |
| int memoryNeed | 内存需求 |
| int nodeType | 节点类型 0:单节点，1：双节点 |
| int serverId | 部署到哪一个服务器上 |
| char deployNode | 部署到服务器上哪个节点，'A','B','C'：双节点 |

| 方法 | 描述 |
| -- | -- |
| getter | 获取类里面的私有参数 |
| setter | 修改类里面的私有参数 |

### Scheduling 类
| 方法 | 描述 |
|-- | -- |
| addVM(BoughtServ, DeployedVM, VMsaleable, type, ID) | 添加一个虚拟机 |
| delVM(BoughtServ, DeployedVM, ID) | 删除一个虚拟机 |


### 调度问题
1. 如何购买服务器的问题
2. 如何将虚拟机放置到服务器中
3. 如何迁移的问题