## CodeCraft2021：华为软件精英挑战赛

### 一、问题描述
给定服务器的型号参数列表，包括（**服务器的型号，CPU核数，内存大小，硬件成本，每天能耗成本**）。
![服务器示例](https://github.com/BaJiuTe/CodeCraft-2021/raw/main/images/1.png)


给定所有可申请的虚拟机型号，包括（**虚拟机的型号，CPU核数，内存大小，是否单双节点部署**）。
![虚拟机示例](https://github.com/BaJiuTe/CodeCraft-2021/raw/main/images/2.png)

#### 1. 输入
每个测试用例包括以下内容：
- 可以购买的服务器类型数量 N，接下来包括 N 个服务器型号，格式如上所示。
- 可以售卖的虚拟机类型数量 M，接下来包括 M 个虚拟机型号，格式如上所示。
- T 天用户请求。
- 每一天有 R 条请求 (**add, 虚拟机型号, 虚拟机 ID**) 或者 (**del, 虚拟机 ID**)。

输入实例：
> 2 
> (NV603, 92, 324, 53800, 500)
>  (NV604, 128, 512, 87800, 800) 
>  2 
> (c3.large.4, 2, 8, 0) 
> (c3.8xlarge.2, 32, 64, 1) 
> 3 
> 2 
> (add, c3.large.4, 5) 
> (add, c3.large.4, 0) 
> 2 
> (del, 0) 
> (add, c3.8xlarge.2, 1) 
> 3 
> (add, c3.large.4, 2)
>  (del, 1) 
>  (del, 2) 

#### 2. 输出
输出格式如下：
- 首先第一行输出(**purchase, Q**)，其中Q是一个整数表示你需要扩容购买多少种类型的服务器。Q不能为负数且不能大于N。
- 接下来Q行，每行的格式为：(**服务器型号, 购买数量**)。所购买的服务器都会被分配一个编号，从 0 开始。
- 接下来一行输出(**migration, W**)，其中W是一个整数表示你要迁移的虚拟机的数量。迁移格式为 (**虚拟机 ID, 目的服务器 ID**) 或 (**虚拟机 ID, 目的服务器 ID, 目的服务器节点**)。
- 接下来是请求的顺序，输出对当前的每一个创建请求，格式为(**服务器ID**)或者(**服务器ID, 部署节点**)

输出实例：
>(purchase, 2) 
>(NV603, 1) 
>(NV604, 1) 
>(migration, 0) 
>(0, A) 
>(0, B) 
>(purchase, 0) 
>(migration, 0) 
>(1) 
>(purchase, 0) 
>(migration, 0) 
>(1, B) 


#### 3. 任务目的
- 任务目的是为虚拟机设计一套调度算法。
- 要求在能部署所有虚拟机的情况下，**最小化价格**（服务器的购买价格+每天能耗花费），也就是说**尽可能的提高服务器的利用率**。



### 二、难点
简单的背包问题是，有一个背包，尽可能的装东西。这个问题是背包问题的升级版，维度增加了很多，约束条件增加很多，难度直线上升。

1. 要求有**单双节点部署**，有时候可能某一节点剩余很少，另一节点剩余很多，请求添加一个双节点部署的虚拟机的时候放不下。

2. 申请的某些虚拟机型号很恶心，CPU需要很少，内存却需要很多，导致**分配不均匀**。



### 三、解决方法
#### 1. 主要类设计
##### ①服务器类 server.cpp

| 变量名 | 变量类型 | 描述 |
| --- | --- | --- |
| type | string | 服务器类型 |
| serverId | int | 服务器 id |
| CPUCapacity | int | CPU 总容量 |
| partACPULeft | int | A 节点 CPU 剩余 |
| partBCPULeft | int | B 节点 CPU 剩余 |
| memoryCapacity | int | 内存总容量 |
| partAMemoryLeft | int | A 节点内存剩余 |
| partBMemoryLeft | int | B 节点内存剩余 |
| hardwareCost | int | 硬件成本 |
| dailyCost | int | 日常能耗成本 |

| 方法名 | 返回类型 | 描述 |
| --- | --- | --- |
| getter() | 参考变量类型 | 获取类中私有变量 |
| setter() | 参考变量类型 | 获取类中私有变量 |
| getScore() | double | 负载均衡参数：CPU/内存 |


##### ②虚拟机类 VrtualMachine.cpp

| 变量名 | 变量类型 | 描述 |
| --- | --- | --- |
| type | string | 虚拟机类型 |
| VMId | int | 虚拟机 id |
| CPUNeed | int | CPU 需求 |
| memoryNeed | int | 内存需求 |
| nodeType | int | 部署类型 0:单节点，1：双节点 |
| serverId | int | 部署到了哪一个服务器上 |
| deployNode | char | 部署到服务器上哪个节点，'A','B','C'：双节点 |

| 方法名 | 返回类型 | 描述 |
| --- | --- | --- |
| getter() | 参考变量类型 | 获取类中私有变量 |
| setter() | 参考变量类型 | 获取类中私有变量 |


##### ③调度类 Scheduling.cpp

| 方法名 | 返回类型 | 描述 |
| --- | --- | --- |
| showMessage() | void | 打印所有资源，包括（可购买的服务器列表，可购买的虚拟机列表，已购买的服务器资源列表，已部署的虚拟机列表) |
| findServerAddVM() | shared_ptr<Server>  |  根据策略，找到可以部署虚拟机的服务器 |
| addUpdate() | char | 部署虚拟机到服务器上，更新服务器的资源信息，并打印部署控制台信息 |
| delVM() | void | 删除一个虚拟机 |
| delUpdate*( | void | 删除虚拟机后，更新服务器和虚拟机的资源信息 |



#### 2. 策略
##### 方法1：暴力
作为第一个版本，我们的想法很简单：盯着一种服务器来买，先**模拟**一遍看当天需要买多少服务器，买够之后，再把虚拟机放到服务器里面，**有位置就放**，迁移虚拟机从后往前迁，也是有位置就迁。

显然这种方法问题很大，没有考虑虚拟机的 CPU/内存 比，会浪费大量资源。这种方法的运行结果是我们的最终成绩的四倍花费。

##### 方法2：先看再挑
和现实情况不一样的是，我们有预知能力，可以提前看到接下来所有的请求和删除虚拟机操作，那么我们可以先看，再来挑选组合虚拟机放到同一台服务器上，尽量让虚拟机的搭配更加均衡（就像俄罗斯方块的 L 和 7 搭配均衡更好），让服务器资源利用更高。服务器我们还是盯着同一台来买，根据所有的 CPU/内存 来挑选服务器。

这里还是存在问题，挑服务器是根据整体的 CPU/内存 比例来选的，局部某一天的虚拟机请求和这个比例可能相差很大，还是会放不均匀。

##### 方法3：优化后最终版本
服务器挑选：按 CPU/内存 的比例来划分区间，一共划分了 9 个区间，每个区间，选一种比例相近的服务器作为代表，当天的比例接近哪种服务器，当天就买那种服务器。

部署虚拟机：先挑选搭配合理的虚拟机先部署。

迁移：对 9 种型号的服务器队列，把后面的服务器往前迁移，能够放下就迁移。


### 四、结果与感想
排名：50/573，一轮游，喜提三等奖。
![最终排名](https://github.com/BaJiuTe/CodeCraft-2021/raw/main/images/3.png)

总的来说，对自己代码提升还是挺大的，队友都很给力。

感觉打比赛自己的想法可能不是很好，在下手写代码之前，最好先去找一下有没有前辈做的类似的研究，先把前人的复现一下，然后再次基础上进行改进。这次比赛我们全都是靠讨论，按自己的想法来写的，所以效果可能不太好，还有很多可以优化的地方，期待下次的华为软挑比赛！
