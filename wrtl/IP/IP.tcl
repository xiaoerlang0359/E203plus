# EthernetLite AXI
create_ip -name axi_ethernetlite -vendor xilinx.com -library ip -version 3.0 -module_name axi_ethernetlite_0 -dir d:/fpgawork/mac_ip/mac_ip.srcs/sources_1/ip
set_property -dict [list CONFIG.C_RX_PING_PONG {0} CONFIG.C_TX_PING_PONG {0} CONFIG.C_INCLUDE_INTERNAL_LOOPBACK {1} CONFIG.C_S_AXI_PROTOCOL {AXI4} CONFIG.AXI_ACLK_FREQ_MHZ {16.667}] [get_ips axi_ethernetlite_0]

# MMCM
create_ip -name clk_wiz -vendor xilinx.com -library ip -version 6.0 -module_name mmcm -dir d:/fpgawork/mac_ip/mac_ip.srcs/sources_1/ip
set_property -dict [list CONFIG.Component_Name {mmcm} CONFIG.CLKOUT2_USED {true} CONFIG.CLKOUT3_USED {true} CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {8.388} CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {16.667} CONFIG.CLKOUT3_REQUESTED_OUT_FREQ {25} CONFIG.RESET_TYPE {ACTIVE_LOW} CONFIG.MMCM_DIVCLK_DIVIDE {1} CONFIG.MMCM_CLKFBOUT_MULT_F {8.000} CONFIG.MMCM_CLKOUT0_DIVIDE_F {95.375} CONFIG.MMCM_CLKOUT1_DIVIDE {48} CONFIG.MMCM_CLKOUT2_DIVIDE {32} CONFIG.NUM_OUT_CLKS {3} CONFIG.RESET_PORT {resetn} CONFIG.CLKOUT1_JITTER {237.316} CONFIG.CLKOUT1_PHASE_ERROR {114.212} CONFIG.CLKOUT2_JITTER {207.611} CONFIG.CLKOUT2_PHASE_ERROR {114.212} CONFIG.CLKOUT3_JITTER {191.696} CONFIG.CLKOUT3_PHASE_ERROR {114.212}] [get_ips mmcm]

# Processor System Reset
create_ip -name proc_sys_reset -vendor xilinx.com -library ip -version 5.0 -module_name proc_sys_reset_0 -dir d:/fpgawork/mac_ip/mac_ip.srcs/sources_1/ip
set_property -dict [list CONFIG.C_EXT_RESET_HIGH {0} CONFIG.C_AUX_RESET_HIGH {0}] [get_ips proc_sys_reset_0]