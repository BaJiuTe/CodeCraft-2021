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


### 读数据
#### 服务器
直接读服务器存到服务器的 map 中，<int serverId, Server server>

#### 虚拟机
直接读虚拟机存到虚拟机的 map 中，<string VMType, VisualMachine vm>

#### 每天的请求
一天一天读当天的请求，把请求存到 `vector<string>` 中


### 调度
#### 买服务器
- 在当天的请求开始之前，先对请求列表的数据进行统计，只计算 add （减去 del 的总和，可优化），就是当天需要买入的量
- 决定怎么搭配服务器，可以有很多种策略，最简单的就是，只买一种服务器

#### 部署虚拟机流程
- 根据虚拟机的 type，怎么找到合适服务器的 id
- 遍历一下已经购买的服务器，看看是否有多余的空位，有就取出服务器的 id，从 map 里面取出虚拟机的对象，调用服务器的 add 接口，挂载虚拟机

#### 删除虚拟机
- 根据虚拟机的 id，从已部署的虚拟机 map 中，找到该虚拟机的对象，并根据虚拟机所部署的服务器 id，从已购买的服务器列表找到服务器对象，调用 del 接口，移除虚拟机
- 再改变外面的 map

#### 迁移虚拟机
- 先不做

#### 部署服务器的策略
策略1：按 CPU 和内存的比例来部署虚拟机。定义一个函数返回 CPU / 内存 的比值

...
