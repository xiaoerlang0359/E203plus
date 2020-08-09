onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /tb_top/clk
add wave -noupdate /tb_top/lfextclk
add wave -noupdate /tb_top/rst_n
add wave -noupdate /tb_top/hfclk
add wave -noupdate /tb_top/x3
add wave -noupdate /tb_top/pc
add wave -noupdate -label cmd_valid /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/cmd_valid
add wave -noupdate -label cmd_ready /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/cmd_ready
add wave -noupdate -label cmd_read /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/cmd_read
add wave -noupdate -label cmd_addr /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/cmd_addr
add wave -noupdate -label cmd_wdata /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/cmd_wdata
add wave -noupdate -label cmd_wmask /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/cmd_wmask
add wave -noupdate -label rsp_valid /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/rsp_valid
add wave -noupdate -label rsp_ready /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/rsp_ready
add wave -noupdate -label rsp_rdata_r /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/rsp_rdata_r
add wave -noupdate -label ui_clk /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/ui_clk
add wave -noupdate -label cmd_clk /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/cmd_clk
add wave -noupdate -label r_ptr_cmd /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/r_ptr_cmd
add wave -noupdate -label w_ptr_cmd /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/w_ptr_cmd
add wave -noupdate -label w_ptr_rsp /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/w_ptr_rsp
add wave -noupdate -label r_ptr_rsp /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/r_ptr_rsp
add wave -noupdate -label state /tb_top/u_system/u_e203_soc_top/u_e203_subsys_top/u_e203_subsys_main/u_e203_cpu_top/u_e203_cpu/u_e203_core/u_e203_lsu/u_icb_bridge/state
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {9135005310277 fs} 0}
quietly wave cursor active 1
configure wave -namecolwidth 131
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits fs
update
WaveRestoreZoom {9134829949032 fs} {9134991293474 fs}
