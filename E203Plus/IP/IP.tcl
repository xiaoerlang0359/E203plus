# mmcm
create_ip -name clk_wiz -vendor xilinx.com -library ip -version 6.0 -module_name mmcm -dir d:/fpgawork/axi_ethernetlite_0_ex/axi_ethernetlite_0_ex.srcs/sources_1/ip
set_property -dict [list CONFIG.Component_Name {mmcm} CONFIG.CLKOUT2_USED {true} CONFIG.CLKOUT3_USED {true} CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {166.667} CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {200} CONFIG.CLKOUT3_REQUESTED_OUT_FREQ {25} CONFIG.RESET_TYPE {ACTIVE_LOW} CONFIG.MMCM_DIVCLK_DIVIDE {1} CONFIG.MMCM_CLKOUT0_DIVIDE_F {6.000} CONFIG.MMCM_CLKOUT1_DIVIDE {5} CONFIG.MMCM_CLKOUT2_DIVIDE {40} CONFIG.NUM_OUT_CLKS {3} CONFIG.RESET_PORT {resetn} CONFIG.CLKOUT1_JITTER {118.758} CONFIG.CLKOUT2_JITTER {114.829} CONFIG.CLKOUT2_PHASE_ERROR {98.575} CONFIG.CLKOUT3_JITTER {175.402} CONFIG.CLKOUT3_PHASE_ERROR {98.575}] [get_ips mmcm]
# MMCM2
create_ip -name clk_wiz -vendor xilinx.com -library ip -version 6.0 -module_name MMCM2 -dir d:/fpgawork/mac_ip/mac_ip.srcs/sources_1/ip
set_property -dict [list CONFIG.Component_Name {MMCM2} CONFIG.PRIM_IN_FREQ {83.333} CONFIG.CLKOUT2_USED {true} CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {8.388} CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {16.667} CONFIG.RESET_TYPE {ACTIVE_LOW} CONFIG.CLKIN1_JITTER_PS {120.0} CONFIG.MMCM_DIVCLK_DIVIDE {5} CONFIG.MMCM_CLKFBOUT_MULT_F {48.000} CONFIG.MMCM_CLKIN1_PERIOD {12.000} CONFIG.MMCM_CLKIN2_PERIOD {10.000} CONFIG.MMCM_CLKOUT0_DIVIDE_F {95.375} CONFIG.MMCM_CLKOUT1_DIVIDE {48} CONFIG.NUM_OUT_CLKS {2} CONFIG.RESET_PORT {resetn} CONFIG.CLKOUT1_JITTER {505.001} CONFIG.CLKOUT1_PHASE_ERROR {386.976} CONFIG.CLKOUT2_JITTER {453.432} CONFIG.CLKOUT2_PHASE_ERROR {386.976}] [get_ips MMCM2]
# reset_sys
create_ip -name proc_sys_reset -vendor xilinx.com -library ip -version 5.0 -module_name reset_sys -dir d:/fpgawork/mac_ip/mac_ip.srcs/sources_1/ip
set_property -dict [list CONFIG.Component_Name {reset_sys} CONFIG.C_EXT_RESET_HIGH {0} CONFIG.C_AUX_RESET_HIGH {0}] [get_ips reset_sys]
# mig_7series_0     make sure you know where is your mig.prg file
# you need to change the tcl based on your directories
create_ip -name mig_7series -version 4.1 -vendor xilinx.com -library ip -module_name mig_7series_0
set_property CONFIG.XML_INPUT_FILE {<absolute path of the old core mig.prj>} [get_ips <ip_name>]
# EthernetLite AXI
create_ip -name axi_ethernetlite -vendor xilinx.com -library ip -version 3.0 -module_name axi_ethernetlite_0 -dir d:/fpgawork/mac_ip/mac_ip.srcs/sources_1/ip
set_property -dict [list CONFIG.C_RX_PING_PONG {0} CONFIG.C_TX_PING_PONG {0} CONFIG.C_INCLUDE_INTERNAL_LOOPBACK {1} CONFIG.C_S_AXI_PROTOCOL {AXI4} CONFIG.AXI_ACLK_FREQ_MHZ {16.667}] [get_ips axi_ethernetlite_0]

