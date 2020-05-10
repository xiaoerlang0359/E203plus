# DDR3
### 目录
#### 一. 主要更改
#### 二. 注意事项
#### 三. ICB总线深入学习
#### 四. 仿真测试
****
## 一. 主要更改
对于DDR3控制器，通过网上的检索，发现主流的方案是采用MIG IP核来生成DDR3控制器。因此本设计中也采用了MIG IP核。关于如何将控制器 IP核嵌入到SoC平台中，这是一个需要思考的问题。因为不像EMAC外设，接口时钟和CPU的内核时钟是同一个时钟。对于DDR3控制器 IP核的接口时钟却是IP核自己生成的时钟。这里面就可能存在跨时钟域的问题。同时接口的数据位宽是128位的，与CPU内核的32位位宽不匹配。这里提供两种思路：  

思路一：应用成熟的IP核和AXI接口，思路一非常的稳定和可靠。 
![解决思路1](DDR3_1.png)  

思路二：自己写一个ICB到DDR3 native interface的桥接协议。要同时解决跨时钟域，和数据位宽的问题。为了更好的学习ICB总线协议，同时这也是一个练习跨时钟域处理的好机会，因此我们选择了思路二。

具体的更改如下：
1. RTL：在E203内核的LSU中，给DCACHE留了ICB接口，但外部并没有接DCACHE设备，我们就利用这个接口来做内存扩容。ICB接口参见[e203_lsu.v](rtl/core/e203_lsu.v)。同时我们在[e203_lsu.v](rtl/core/e203_lsu.v)实例化了我们的桥接协议[ICBBridge](rtl/icb_bridge.v)。有关桥接协议的更详细信息，请 doc 目录下的相关文档。有了桥接协议之后MIG 的83MHz 的native interface 就变成了16.6MHz 的ICB interface。从而能够从LSU接收访存指令，并能够将读到的数据传递给写回模块。  
之后我们需要把native interface 的信号引出到顶层模块。并在顶层模块实例化DDR3 控制器。这就是我们的主要步骤。因为在ICBBridge中我们已经加入了对ICB cmd和 rsp的缓存因此，桥接外层无需加入缓冲模块也能够满足时序要求。

2. IP核：primary clock 依然是板载的晶振产生的100 MHz时钟。源时钟进入MMCM产生sys_clk_i(166.667 MHz)和clk_ref_i(200 MHz)给DDR3控制器。DDR3控制器的输出时钟ui_clk(83.333 MHz)再次作为源时钟进入MMCM2中产生16.666 MHz的系统时钟和8.388 MHz时钟。  
另一个需要关注的IP核是MIG。有关MIG的各种信息请参考doc目录下的product guide。同时，在IP目录下有mig.prj文件，您可以通过这个文件直接生成MIG 核。需要注意的是，如果您需要native interface（UI interface）的话，您还需要在GUI环境下，重新更改interface设置，并重新生成IP核。如果选择AXI接口就无需上述操作。
3. 约束文件：增加了[mig_7series_0.xdc](constraint/mig_7series_0.xdc)作为与DDR3接口的引脚的物理约束。增加了[example_top.xdc](constraint/example_top.xdc)设置了内部参考电压。