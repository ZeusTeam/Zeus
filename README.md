> **关于宙斯**  
> **[宙斯](https://github.com/ZeusTeam/Zeus "宙斯")**是一个开放源代码的mmorpg游戏。  
> 代码：[https://github.com/ZeusTeam/Zeus](https://github.com/ZeusTeam/Zeus)

## **版本开发计划**
`*粗体版本号表示已完成版本。`

- 客户端  
    [
[**c0.1**](https://github.com/ZeusTeam/Zeus/blob/master/VERSION.md#c01) | 
[**c0.2**](https://github.com/ZeusTeam/Zeus/blob/master/VERSION.md#c02) | 
[**c0.2.1**](https://github.com/ZeusTeam/Zeus/blob/master/VERSION.md#c021) | 
[**c0.2.2**](https://github.com/ZeusTeam/Zeus/blob/master/VERSION.md#c022) | 
[**c0.2.3**](https://github.com/ZeusTeam/Zeus/blob/master/VERSION.md#c023) | 
[**c0.2.4**](https://github.com/ZeusTeam/Zeus/blob/master/VERSION.md#c024) | 
[c0.2.5](https://github.com/ZeusTeam/Zeus#c025) |
[c0.2.6](https://github.com/ZeusTeam/Zeus#c026)
]
    
- 服务端  
    [
[**s0.1**](https://github.com/ZeusTeam/Zeus/blob/master/VERSION.md#s01) | 
[**s0.2**](https://github.com/ZeusTeam/Zeus/blob/master/VERSION.md#s02) |
[s0.3](https://github.com/ZeusTeam/Zeus#s03) | 
[s0.4](https://github.com/ZeusTeam/Zeus#s04) | 
[s0.5](https://github.com/ZeusTeam/Zeus#s05) | 
[s0.6](https://github.com/ZeusTeam/Zeus#s06) | 
[s0.7](https://github.com/ZeusTeam/Zeus#s07) ]


### **客户端 [`详细`](https://github.com/ZeusTeam/Zeus/blob/master/VERSION.md)**
----------
####c0.2.4
1.角色选择页面(able)  
2.角色创建页面(sum)  
3.可选角色头像图片列表  

####c0.2.5
1.游戏配置文件  
2.提取地图接口  
3.支持多地图切换  

####c0.2.6
1.鼠标走路  
2.人物头顶显示名字  

### **服务端 [`详细`](https://github.com/ZeusTeam/Zeus/blob/master/VERSION.md)**
----------
####s0.3
1.封装通信底层IO接口（send/recv, 包括事件回调）  
2.整理server线程模型

####s0.4
1.完成Buffer，用于处理缓冲区数据  
2.增加消息队列

####s0.5
1.约定PDU格式  
2.解析网络数据包

####s0.6
1.封装应用层Message类  
2.完成应用层Session类  
3.增加应用层发送接口（unicast/multicast）

####s0.7
1.增加GUID管理  
2.增加应用层Session状态管理器  
3.协议处理管理器