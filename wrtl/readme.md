# Ethernet mac  
### 目录
#### 一. 主要修改
#### 二. 注意事项
#### 三. 使用EMAC外设
#### 四. 仿真测试
---
## 一. 主要修改
1. RTL:主要修改的是 [e203_subsys_perips.v](rtl/subsys/e203_subsys_perips.v): E203本身就为扩展AXI核APB外设提供了接口，只需要将EthernetLite IP核实例化，并且完成接口的连线就可以。其中与Phy芯片接口有关的信号，要逐级连接到最顶层 [system.v](rtl/system.v)。AXI接口信号与ICB2AXI模块进行连接。中断信号 ip2intc_irpt 要连接到PLIC模块。同时EMAC外设的对应地址也在  
其次就是PLIC模块要增加对应的引脚信号，并且将外部中断的数目增加到53。  
最后在 [system.v](rtl/system.v)中需要增加给phy芯片的时钟。增加核phy芯片的输入输出接口。其中MDIO信号需要格外注意以下。作为inout端口，我们要在输出端加三态门。  
```verilog
assign eth_mdio = (!phy_mdio_t)? phy_mdio_o:1'bz;
assign phy_mdio_i = eth_mdio;
```
2. IP核：MMCM IP核需要增加一路输出时钟（25MHz）作为phy芯片的输入时钟，可以直接由 primary clock 在MMCM中生成。  
增加一个EthernetLite IP核，需要注意的是，如果您想进行环回测试，请使能MDIO和MDC信号。  
具体IP核如何设置，请参考[TCL_for_IP.txt](IP/TCL_for_IP.txt)中的TCL脚本。
3. 约束文件：将连接phy芯片应交的物理约束的注释取消。

## 二. 注意事项
1. phy_mdio_t 为低电平时使能输出，这一点在product guide 中没有提到。
2. 当AXI接口时钟小于100 MHz 时只能使用 10Mb/s 以太网。如果需要进行环回测试（无论是internal的还是，基于phy芯片的），都需要设置phy芯片的工作模式。
3. 出于应用场景的需要，目前EMAC 外设只支持全双工模式。
4. 虽然在原理图中给phy芯片画了对应的晶振，但实际上arty A7-35T的开发板上时没有晶振的，需要自己产生时钟。
5. 目标开发板中的phy芯片默认地址为0x01

## 三. 使用EMAC外设
更多使用EMAC的信息请参阅 [product guide](doc/pg135-axi-ethernetlite.pdf)。这里只对最简单的应用场景进行介绍。  
1. 主要寄存器  
   
 |Address Offset| Register Name| Description| 
 | :----| :----| :----|
 |1500_07E4h| MDIOADDR|  MDIO address register|
 |1500_07E8h| MDIOWR | MDIO write data register| 
 |1500_07ECh| MDIORD | MDIO read data register| 
 |1500_07F0h| MDIOCTRL| MDIO control register|
 |1500_07F4h| TX Ping Length| Transmit length register for ping buffer| 
 |1500_07F8h| GIE| Global interrupt register| 
 |1500_07FCh| TX Ping Control |Transmit control register for ping buffer|
 |1500_17FCh| RX Ping Control| Receive control register for ping buffer|

2. 发送流程（非中断）  
   1）读TX Ping Control寄存器，检查发送端口是否忙碌，最低比特位为1表示忙碌。如果忙碌等待。  
   2）将发送数据按照目的mac地址，源mac地址，type/length，数据的顺序写入，0x1500_000开始的地址处。其中目的mac地址和源mac地址按照从低字节到高字节的顺序。type/length按照网络字节序（先发高字节，再发低字节）。  
   3）将发送数据长度写入TX Ping Length寄存器。  
   4）将TX Ping Control寄存器最低比特位置1，使能发送。并读TX Ping Control寄存器寄存器，当最低比特归零时，表示发送结束。  

3. 接收流程（非中断）  
   1）读RX Ping Control寄存器，检查接收端口是否接收到完整数据帧，最低比特位为1表示接收完成。否则等待。  
   2）从0x1500_1000开始读接收数据。分别为目的mac地址，源mac地址，type/length，数据，以及CRC校验结果。  
   3）如何得到接收数据帧的长度：我们可以将整个接收缓冲区都读下来，然后依靠上层协议处理。或者结合type/length和IP数据报格式获得接收区长度。  
   4）将RX Ping Control寄存器的最低比特位置0，使能接收。

有关如何操作MDIO接口以及，修改MAC地址的内容，请阅读[product guide](doc/pg135-axi-ethernetlite.pdf)。

## 四. 仿真测试
仿真测试分为三个阶段：  
1. IP核的行为级仿真。需要注意的是，如果你使用example design对应的仿真文件。并且AXI时钟小于100 MHz时。请在tb文件中修改phy接口的时钟为2.5MHz，否则可能无法测试成功。（Done）
2. Internal 和 phy芯片级别的环回测试，验证发送接收数据是否一致，并且测试中断功能。具体main函数可以在sim目录下找到。（Running）
3. 移植FreeRTOS+TCP内核，与上位机的FTP服务器进行通信，能够正常接收文件。（Queue）

   
