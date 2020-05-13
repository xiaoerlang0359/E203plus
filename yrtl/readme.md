# DDR3内存扩展设计文档
## 目录
### 1. 概述
>##### 1.1 功能介绍
>##### 1.2 总体框图 
### 2. 实现描述
>##### 2.1 rtl
>##### 2.2 IP核
>##### 2.3 约束文件
>##### 2.4 IO PORT
### 3. 仿真测试
### 4. 设计反思
### 5. ICB总线学习

****
## 1. 概述
### 1.1 功能介绍
将板载DDR3加入内存空间，实现内存扩容。
### 1.2 总体框图
![project](project.png)
## 2. 实现描述
对于原有E203工程增加了两个模块，一个时DDR3控制器 IP核，另一个时ICB协议到DDR3 控制器的桥接转换模块。  
|Index|module|function|Note|
|:---|:---|:----|:----|
|1|u_mig_7series_0|DDR3控制器 IP核|使用mig.prj生成，AXI端口->native端口|
|2|u_icb_bridge|ICB协议到native interface的协议转换电路|详见[icbbridge设计文档](doc/ICBBridge设计文档.docx)|
|3|u_mmcm|mmcm IP核|修改，输出时钟|
|4|u_mmcm2|mmcm IP核|时钟源为DDR3控制器，生成核心时钟|


对于DDR3控制器，通过网上的检索，发现主流的方案是采用MIG IP核来生成DDR3控制器。因此本设计中也采用了MIG IP核。关于如何将控制器 IP核嵌入到SoC平台中，这是一个需要思考的问题。因为不像EMAC外设，接口时钟和CPU的内核时钟是同一个时钟。对于DDR3控制器 IP核的接口时钟却是IP核自己生成的时钟。这里面就可能存在跨时钟域的问题。同时接口的数据位宽是128位的，与CPU内核的32位位宽不匹配。这里提供两种思路：  

思路一：应用成熟的IP核和AXI接口，思路一非常的稳定和可靠。 
![解决思路1](DDR3_1.png)  

思路二：自己写一个ICB到DDR3 native interface的桥接协议。要同时解决跨时钟域，和数据位宽的问题。为了更好的学习ICB总线协议，同时这也是一个练习跨时钟域处理的好机会，因此我们选择了思路二。对于思路二其实E203也为我们提供了跨时钟域的桥接模块：sirv_gnrl_cdc_rx和sirv_gnrl_cdc_tx。不过我们也没有使用，原因前面也提到了。

### 2.1 RTL
在E203内核的LSU中，给DCACHE留了ICB接口，但外部并没有接DCACHE设备，我们就利用这个接口来做内存扩容。ICB接口参见[e203_lsu.v](rtl/core/e203_lsu.v)。同时我们在[e203_lsu.v](rtl/core/e203_lsu.v)实例化了我们的桥接协议[ICBBridge](rtl/icb_bridge.v)。有关桥接协议的更详细信息，请 doc 目录下的相关文档。有了桥接协议之后MIG 的83MHz 的native interface 就变成了16.6MHz 的ICB interface。从而能够从LSU接收访存指令，并能够将读到的数据传递给写回模块。  
之后我们需要把native interface 的信号引出到顶层模块。并在顶层模块实例化DDR3 控制器。这就是我们的主要步骤。因为在ICBBridge中我们已经加入了对ICB cmd和 rsp的缓存因此，桥接外层无需加入缓冲模块也能够满足时序要求。

### 2.2 IP核
primary clock 依然是板载的晶振产生的100 MHz时钟。源时钟进入MMCM产生sys_clk_i(166.667 MHz)和clk_ref_i(200 MHz)给DDR3控制器。DDR3控制器的输出时钟ui_clk(83.333 MHz)再次作为源时钟进入MMCM2中产生16.666 MHz的系统时钟和8.388 MHz时钟。  
另一个需要关注的IP核是MIG。有关MIG的各种信息请参考doc目录下的product guide。同时，在IP目录下有mig.prj文件，您可以通过这个文件直接生成MIG 核。需要注意的是，如果您需要native interface（UI interface）的话，您还需要在GUI环境下，重新更改interface设置，并重新生成IP核。如果选择AXI接口就无需上述操作。
### 2.3 约束文件
增加了[mig_7series_0.xdc](constraint/mig_7series_0.xdc)作为与DDR3接口的引脚的物理约束。增加了[example_top.xdc](constraint/example_top.xdc)设置了内部参考电压。
## 3. 仿真测试
有关扩展内存的仿真测试，需要.verilog文件，这个需要在linux环境下用芯来科技提供的工具链汇编isa下的汇编文件。您可以通过修改isa文件夹下现成的.S文件来完成内存设计的功能测试。这里需要注意到时，要同时修改32位和64位的.S文件，如果只修改64位的，make是无法识别修改的。
我们主要进行的仿真测试如下：  
1. 行为级仿真，测试了连续读写100个字节，半字，字，测试读出和写入是否一致。
2. fpga原型测试，测试了连续读写100个字节，半字，字，测试读出和写入是否一致。
3. freeRTOS内存分配测试，尝试用heap5.c连续在扩展内存上申请释放内存。
## 4. 设计反思
1. 使用MIG IP核的时候，该IP核会产生一个时钟ui_clk。需要注意的是这个时钟和他的时钟源 sys_clk_i 的相位是不一致的。这是我在行为级仿真的时候发现的。后来仔细检查了一下report，发现人家本来就给我报了warning。在论坛上问了一下，得到的答复是这个warning是正常的，可以忽略的。不过，对于我们的这个跨时钟域设计，相位的不一致还是会造成很多困扰。所以我们更改了时钟生成的方案。
2. E203采用的是两级流水线，也就是取指之后就没有寄存器帮我们缓存数据了，所以当数据从译码阶段，到派遣再到执行，再到我们接口的ICB信号。所以很有必要在核LSU的接口插入一级寄存器，同理在和协会模块的ICB宗信啊通信上最好也加上一级流水。这个我们最早的设计没有考虑，所以综合后，很多setup 是违背的。有关如何在ICB总线上插入流水，请看第三部分。
3. 在我们学习SDRAM的时候知道，DRAM是需要刷新的，这个刷新，如果选择不去控制那个接口的话，对于我们来说就是透明的。刷新可能在任何时候发生。之前我们在给DDR3 控制器发送的指令时，只是在IDLE阶段判断了一下DDR3控制器是否准备好，之后就默认准备好了。发送指令和判断准备正好差了一个时钟周期。这一点是致命的，会出现前一个周期，控制器还是准备好的，下一个周期就不准备好了。这个时候发给控制器的指令没有被接收，整个CPU就stall了。
4. 说一下MASK，在E203中MASK的1，表示不屏蔽，而在DDR3的native接口上，MASK的1表示屏蔽。
5. 在E203中的地址是以字节为单位的，但在DDR3 的native 接口中，地址事宜半字为单位的。
6. DDR3的存储和E203采用的都是小端模式，这一点比较方便。
## 5. ICB总线学习
原谅我的无知，当我第一次阅读源码的时候，E203中关于ICB总线的使用真的是非常让人震惊。在整个设计中ICB总线不仅作为连接外设，内存的接口，也是CPU各级流水线传递的接口。在我们学习计算机组成原理的时候，会学到CPU有一个部件是控制器，控制器来控制整个数据通路的流动，是否需要stall和flush流水线。整个控制器会用到非常复杂的组合逻辑。而在E203中将控制器的作用分散到来不同模块，比如译码，派遣，交付，写回，都会执行控制器的一部分作用。其中ICB总线也完成了控制流水线stall的部分功能。并且这种stall并不是全局的stall，它只会stall自己所在的那条支路，然后这种stall就会向前传递，直到这条支路已经堵塞了太多指令，堵到了主干路，那么整个CPU就被stall了。真是天才的构想，钦佩不已。  
ICB总线的接口时序更详细的介绍可以参考《手把手教你设计CPU——risc-v处理器》。按照作者的介绍ICB总线是对AXI接口的简化。ICB总线涉及到的主要信号如下：   
|通道|方向|信号名|介绍|
|:---|:---|:---|:---|
|命令通道|output|icb_cmd_valid|主设备向从设备发送的读写请求信号|
||input|icb_cmd_ready|从设备向主设备返回读写接收信号|
||output|icb_cmd_addr|读写地址|
||output|icb_cmd_read|读或者写操作的指示|
||output|icb_cmd_wdata|写操作的数据|
||outout|icb_cmd_wmask|写操作的字节掩码|
|反馈通道|input|icb_rsp_valid|从设备向主设备发送读写反馈请求信号|
||output|icb_rsp_ready|主设备向从设备返回读写反馈接收信号|
||input|icb_rsp_rdata|读反馈数据|
||input|icb_rsp_err|读或者写错误标志|  

当然这些信号并不是全部，完全可以根据自己的需要增加新的信号。一个典型的ICB总线读写过程如下：  
![ICB总线](ICB.png)  
当我们有一个读写请求的时候，icb_cmd_valid拉高，直到icb_cmd_ready拉高后，表示此次命令传递成功，在下一个时钟周期valid和ready都拉低。当icb_cmd_ready为低时，icb_cmd_valid就会持续拉高直到两个信号同时为高。  
当从设备完成数据处理或者读数据准备好后会将icb_rsp_valid拉高，直到icb_rsp_ready也同时为高时，表示这次握手成功，两个信号再次被拉低。

下面我们来说一下如何在ICB总线的传输路径上插入一级流水线。
## 四. 在ICB总线插入一级缓存
E203的作者在源码中是这么描述在ICB总线中插入一级流水线的，这里主要涉及到两个模块：sirv_gnrl_pipe_stage 和 sirv_gnrl_bypbuf。其中pipe模块用于完成命令通道和反馈通道的握手。而bybuffer模块用于解决ready信号的反压问题。
````verilog
// This module is a super-weapon for timing fix,
// but it is tricky, think it harder when you are reading, or contact Bob Hu
````
我们可以得到两个信息：1. 缓存模块很强大，可以解决你的时序问题；2. 这个模块很难懂，要认真看。  
关于缓存模块的源码在[sirv_gnrl_bufs.v](rtl\general\sirv_gnrl_bufs.v)，有兴趣的朋友可以自己阅读源码。同时再次推荐一下迈克老狼2012关于[bypass buffer](https://www.cnblogs.com/mikewolf2002/p/11250356.html)和[同步fifo](https://www.cnblogs.com/mikewolf2002/p/11248870.html)的两篇文章，里面有作者写的激励文件和仿真波形，会更加有利于理解。因为我的能力有限，把自己的理解分享给大家，有任何错误请及时指出。  
我们先看bypass buffer，也就是前向旁路缓存：
````verilog
module sirv_gnrl_bypbuf # (
  parameter DP = 8,
  parameter DW = 32
) (
  input           i_vld,
  output          i_rdy,
  input  [DW-1:0] i_dat,

  output          o_vld,
  input           o_rdy,
  output [DW-1:0] o_dat,

  input           clk,
  input           rst_n
);


  wire          fifo_i_vld;
  wire          fifo_i_rdy;
  wire [DW-1:0] fifo_i_dat;
  
  wire          fifo_o_vld;
  wire          fifo_o_rdy;
  wire [DW-1:0] fifo_o_dat;
  
  sirv_gnrl_fifo # (
       .DP(DP),
       .DW(DW),
       .CUT_READY(1) 
  ) u_bypbuf_fifo(
    .i_vld   (fifo_i_vld),
    .i_rdy   (fifo_i_rdy),
    .i_dat   (fifo_i_dat),
    .o_vld   (fifo_o_vld),
    .o_rdy   (fifo_o_rdy),
    .o_dat   (fifo_o_dat),
    .clk     (clk  ),
    .rst_n   (rst_n)
  );
  
   // This module is a super-weapon for timing fix,
   // but it is tricky, think it harder when you are reading, or contact Bob Hu
  
  assign i_rdy = fifo_i_rdy;
  
  // The FIFO is bypassed when:
  //   * fifo is empty, and o_rdy is high
  wire byp = i_vld & o_rdy & (~fifo_o_vld);

  // FIFO o-ready just use the o_rdy
  assign fifo_o_rdy = o_rdy;
  
  // The output is valid if FIFO or input have valid
  assign o_vld = fifo_o_vld | i_vld;

  // The output data select the FIFO as high priority
  assign o_dat = fifo_o_vld ? fifo_o_dat : i_dat;

  assign fifo_i_dat  = i_dat; 

  // Only pass to FIFO i-valid if FIFO is not bypassed
  assign fifo_i_vld = i_vld & (~byp);


endmodule 
````
以上是bypass buffer的全部源码，从这源码里我们其实可以看出来这个bypass buffer 其实是一个带有bypass功能的同步fifo。当下一级流水线准备好了，o_rdy=1,上一级流水线命令准备好了，i_vld=1，并且此时同步FIFO为空时，就会直接pass掉这个FIFO，把上下两级流水线的握手信号直接连起来（除了rdy信号）。如图：  
![bypass](bypass.png)  
从截图我们可以看出,在请求较稀疏的时候，o_rdy一直维持高电平所以没有用到fifo，因此i_rdy也维持高电平。这里的i_rdy其实就是fifo的满信号的反。然后就o_vld=i_vld。整个bypass buffer 就像消失一样，并不会影响前向通路的性能。

下图是使用buffer的时候。[迈克老狼2012](https://www.cnblogs.com/mikewolf2002/p/11250356.html)。因为没有获得别人的授权，就不把图加到这里了。其实就是一个同步fifo的典型读写时序。i_rdy & i_vld 作为写使能，o_rdy & o_vld 作为读使能，o_rdy 是fifo非空信号，i_rdy是FIFO非满信号。  
关于bypass buffer的最后一点是关于cut ready信号的解释。首先解释一下什么是反压，所谓反压就是流水线的下一级，向上一级或上很多级的反馈信号，比如握手协议中的cmd_ready信号。那么反压会引起什么问题吗？单纯的反压信号并不会引起什么问题，问题在于当我们在本级流水线的ready信号用了下一级流水线的ready信号的组合逻辑时，就会出现问题。说了这么多可能还没说清楚。让我们看一下源码（同步FIFO模块）：
````verilog
    if(DP == 1) begin:cut_dp_eq1//{
        if(CUT_READY == 1) begin:cut_ready//{
          // If cut ready, then only accept when fifo is not full
          assign i_rdy = (~i_vec[DP-1]);
        end//}
        else begin:no_cut_ready//{
          // If not cut ready, then can accept when fifo is not full or it is popping 
          assign i_rdy = (~i_vec[DP-1]) | ren;
        end//}
    end//}
    else begin : no_cut_dp_gt1//}{
      assign i_rdy = (~i_vec[DP-1]);
    end//}
````
我们重点看一下这一句：
````verilog
wire ren = o_vld & o_rdy;
assign i_rdy = (~i_vec[DP-1]) | ren;
````
这下清楚一些了，在i_rdy中出现了o_rdy，这意味着这个o_rdy可能会随着i_rdy继续向上一级流水线传递，当传递了很多级流水线后，我们会发现这个o_rdy信号经过一个很长的逻辑链才到达第一季流水线并被某个触发器寄存。所以说从最后一级流水线一直反馈到第一级了流水线，这是一个很长的逻辑路径，并且很可能成为整个涉及的关键路径，造成设计的时序问题。那如何解决呢？
````verilog
assign i_rdy = (~i_vec[DP-1]);
````
我们直接用fifo的空满来判断是否rdy。我们知道fifo的空满是由读写指针决定的，而读写指针作为一级寄存器，就把o_rdy和i_rdy分割开了。

这样整个bypass模块就做到，前向通路可以在bypass机制下完成单周期内的握手信号传递，不影响性能，反向通路上又通过fifo的读写指针，分割开来反压信号。用比ping pong buffer少一倍的硬件，实现了ping pong buffer的性能。

关于pipe module我们就不在这里介绍了，因为我还是没有完全理解流水线设计的结构。这里就提几点问题：  
1. 这个bypass buffer模块加入的位置都是在访问ITCM和DTCM的时候，其他流水线都不需要了吗？
2. 如果你看pipe stage 的源码时，你会看到，pipe本身就有cut ready的机制，但E203的设计中都没有使用这种机制，是为什么呢？是应为无法做到前向bypass，影响性能吗？
3. 在总线的arbt和splt中也出现了pipe stage，所以在每次总线仲裁和分线的时候都会切一级流水吗？


您可以在sim文件夹下找到测试用的.verilog，和main.c文件。


