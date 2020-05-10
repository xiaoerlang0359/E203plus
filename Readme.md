# E203Plus  
### 目录  

#### 一. 概述  

#### 二. 与E203的区别  

#### 三. TODO List  

#### 四. 时钟  

#### 五. 内存映射  

#### 六. 结构图  

#### 七. 将项目移植到Vivado IDE中  

#### 八. Vivado+Modelsim仿真平台  

#### 九. 嵌入式环境搭建  

## 一. 概述  
E203Plus是为了参加全国大学生创新创业大赛，以开源的蜂鸟E203为基础定制的SoC（一个图像识别任务）。有关E203的详细信息请参见[E203.md](E203.md)。E203属于risc-v架构，具体为RV32IMAC，使用多周期的硬件乘除法单元。E203Plus将在E203的基础上增加浮点运算单元（也有可能是协处理器，视项目进展，目前来看，浮点运算单元的可能性更大），和一些配套外设（DDR3 controller, Ethernet Mac, DMA, VGA controller)。    

E203Plus目前的目标平台为Arty A7-35T，您可以通过修改约束文件移植到其他平台。  

文件组织，在E203原有的文件基础上，增加了WRTL和YRTL两个目录。  

>e200_opensource
>>WRTL
>>YRTL
>>>rtl
>>>sim
>>>con
>>>doc


## 二. 与E203的区别  
1. +浮点运算单元，由于任务要求，需要进行大量的浮点乘加运算。  
2. +DDR3 controler 作为DTCM扩容。由于FPGA的资源限制，DTCM大小只能在64K到128K。因此需要利用板载的DDR3 SDRAM做数据内存扩容。扩容后的数据区域内存大小为128M+64K。DDR3 controler 使用了MIG IP核(native interface)，和一个跨时钟域处理电路。跨时钟域握手电路完成了与LSU的ICB总线接口。具体使用时，您可以像使用DTCM一样，访问内存。DDR3 的起始地址为 0xa0000000。具体代码和介绍见WRTL文件夹。  
3. +Ethernet Mac 作为私有外设。使用EthernetLite IP核和AXI到ICB的协议转换电路完成设计。并且在PLIC平台增加了对应的中断接口（中断号为53），您可以通过配置对应寄存器设置发送中断与接收中断。因为处理器内核时钟的限制，目前仅支持 10 Mb/s 以太网。如果您需要进行环回测试，请先对板载的Phy芯片进行配置。  
4. +DMA  
5. +VGA controller  
## 三. TODO List  
任务完成表  

|任务名称|注释|状态|完成人| 
| :-------| :-----| :------| :------|
|**General**|
|linux环境下基于VCS和Verdi的仿真环境搭建|tb/tb_top.v, vsim/bin/run.makefile|Done|Liu|  
|linux环境下内核RTL代码综合与上板测试|请按照fpga/readme的要求操作|Done|Liu|  
|将工程移植到Vivado IDE中|根据TCL脚本建立IP核，注意MCS文件生成的配置|Done|Liu|  
|windows平台下基于Modelsim的仿真环境搭建|tb/tb_top.v|Done|Liu|  
|搭建嵌入式开发平台|Debugger设置，board.h|Done|Liu|  
|Jtag->Pmod转接板制作|忽略TRST|Done|Liu|  
|**DDR3**|
|了解E203的存储结构|eai+agu->lsu-> biu+itcm+dtcm+dcache|Running|Liu|  
|了解DDR3, 熟悉MIG IP核的接口| tcl+mig.prj | Done|Liu|  
|编写DDR3 controller spec||Done|Liu|  
|编写跨时钟域处理电路RTL代码|MIG 产生的ui_clk和sys_clk_i,相位不一致|Done|Liu|  
|将DDR3_controller整合到E203SoC中|Dcache|Done|Liu|  
|建立仿真环境进行行为级仿真|risc_test中修改.S文件,产生对应的.verilog文件|Done|Liu|  
|综合实现后进行STA|接口部分对ICB的命令和数据，进行缓存，满足时序要求|Done|Liu|  
|下载到目标fpga平台上验证访存测试程序|访存100次字，半字和字节|Done|Li|  
|目标fpga平台验证FreeRTOS+heap5|对DDR3进行内存分配操作|Done|Li|  
|**Ethernet**|
|了解以太网协议和数据帧格式|大小端|Running|Li|  
|了解E203的外设组织和中断处理|外设->PLIC->交付|Done|Liu|  
|寻找开源和vivado集成的mac IP核|Ethernet Lite| Done| Liu|  
|将IP核加入E203 SoC中|inout 端口的设计| Done|Liu|  
|对EthernetLite IP核进行行为级仿真| 注意时钟|Done|Liu|  
|综合实现后进行STA|原始SOC中已经缓存，不存在时序违例|Done|Liu|  
|下载到开发板进行环回测试|phy_mido_t低有效|Done|Liu|  
|下载到开发板中进行中断测试||Running|Liu|  
|移植FreeRTOS到目标fpga平台||Done|Li|  
|移植FreeRTOS+TCP到目标fpga平台||Running|Li|  
|**FPU**|
|选择开源的FPU IP 核|.sv,.v|Running|Liu|
|了解IP核的接口协议和IEEE 754标准||Running|Liu|  
|对IP核进行行为级仿真，测试||Queue|Liu|  
|将FPU整合到E203Plus SoC中||Queue|Liu|  
|对SoC的FPU进行测试和验证|riscv_test|Queue|Liu|  
|DMA||Queue||  
|VGA controller||Queue||  

## 四. 时钟
>CLK100MHz
>> CLK100MHz-->eth_ref_clk(25M)
>> CLK100MHz-->ref_clk_i(200M)
>> CLK100MHz-->sys_clk_i(166.667M)
>>> sys_clk_i-->ui_clk(83.333M)
>>>> ui_clk-->CLK16MHz(16.667M)
>>>> ui_clk-->CLK8388(8.388M)

## 五. 地址映射
|总线分组|组件|地址区间|
| :-------|:-----| :------|
|处理器核直属|CLINT|0x0200_0000 ~ 0x0200_FFFF|
|处理器核直属|PLIC|0x0C00_0000 ~ 0x0CFF_FFFF|
|处理器核直属|ITCM|0x8000_0000 ~ 0x8000_FFFF|
|处理器核直属|DTCM|0x9000_0000 ~ 0x9000_FFFF|
|处理器核直属|Dcache|0xA000_0000 ~ 0xA7FF_FFFF|
|系统存储接口|调试模块|0x0000_0000 ~ 0x0000_0FFF|
|系统存储接口|Mask-ROM|0x0000_1000 ~ 0x0000_1FFF|
|系统存储接口|Off-Chip QSPI0|0x2000_0000 ~ 0x0003_FFFF|
|系统存储接口|On-Chip OTP Read|0x0002_0000 ~ 0x0003_FFFF|
|私有外设接口|常开域|0x1000_0000 ~ 0x1000_7FFF|
|私有外设接口|HCLKGEN|0x1000_8000 ~ 0x1000_8FFF|
|私有外设接口|OTP|0x1001_0000 ~ 0x1001_0FFF|
|私有外设接口|GPIO|0x1001_2000 ~ 0x1001_2FFF|
|私有外设接口|UART0|0x1001_3000 ~ 0x1001_3FFF|
|私有外设接口|QSPI0|0x1001_4000 ~ 0x1001_4FFF|
|私有外设接口|PWM0|0x1001_5000 ~ 0x1001_5FFF|
|私有外设接口|UART1|0x1002_3000 ~ 0x1002_3FFF|
|私有外设接口|QSPI1|0x1002_4000 ~ 0x1002_4FFF|
|私有外设接口|PWM1|0x1002_5000 ~ 0x1002_5FFF|
|私有外设接口|QSPI2|0x1003_4000 ~ 0x1003_4FFF|
|私有外设接口|PWM2|0x1003_5000 ~ 0x1003_5FFF|
|私有外设接口|EMAC|0x1005_0000 ~ 0x1005_1FFF|

## 六. 结构图  
![SoC 结构图](SoC.png)

## 七. 将工程移植到Vivado IDE中  
原有的E203为一个非工程的项目，在linux环境下用TCL脚本来进行维护。如果你对Linux环境或者TCL脚本还不是很熟练，您可以将工程移植到Vivado IDE中。这里提几点注意事项：

1. 首先在linux环境的FPGA目录下用make install 命令（详见 readme)，生成对应开发板的RTL文件。然后在新建的Vivado工程中，加入这些文件。
2. 有三个头文件，config.v等需要从工程中删除，然后再设置工具选项中，添加对应的头文件路径。
3. 按照TCL脚本，生成对应的IP核。
4. 添加对应的约束文件。之后就可以综合实现，生成比特流文件。
5. 注意在生成MCS文件是，要按照TCL脚本中的对应命令生成，包括采用SPI4，以及起始地址为0x00800000。

## 八. Vivado+Modelsim仿真平台  
将tb_top.v作为仿真文件添加到工程中。在Linux环境下生成标准的测试文件，在riscv_test/isa中。将.verilog文件复制到已知位置。然后将对应的文件路径添加到tb_top.v中。这样就可以愉快的仿真了。

这种方式的缺点是一次只能仿真一个测试集（如果熟练TCL脚本，应该可以改善这个问题）。需要不断的修改对应的文件。优点是Modelsim仿真速度还可以，并且有教育版。

如果您想在VCS+Verdi平台上进行仿真测试。我们已经对原始的文件进行了修改，clone到本地后，你可以直接运行仿真。

主要参考了以下两个博主的文章：

[E203 VCS+Verdi by 迈克老狼](https://www.cnblogs.com/mikewolf2002/p/11399364.html)  
[一些错误的修改 by SunicYosen](https://www.cnblogs.com/sunic/p/9899013.html)

## 九. 嵌入式开发环境搭建  
我们所用的嵌入式开发环境为windows环境下的芯来科技IDE。您可以在他们的官网下载并查看教程。使用的Jtag调试器，也是芯来科技的，您可以在他们的淘宝店铺找到。

关于如何把Jtag接口迁移到Pmod，我们制作了一个小电路板作为转换电路。对应的原理图和光绘文件在文件夹JTAG下。
