# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\deoch\Documents\WSU\CPTS_421\sel-embeddeddebugger\workspace\TestProject_system\_ide\scripts\debugger_testproject-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\deoch\Documents\WSU\CPTS_421\sel-embeddeddebugger\workspace\TestProject_system\_ide\scripts\debugger_testproject-default.tcl
# 
connect -url tcp:127.0.0.1:3121
source C:/Xilinx/Vitis/2023.1/scripts/vitis/util/zynqmp_utils.tcl
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -nocase -filter {name =~"APU*"}
reset_apu
targets -set -nocase -filter {name =~"RPU*"}
clear_rpu_reset
enable_split_mode
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/deoch/workspace/kv260_ispMipiRx_vcu_DP/export/kv260_ispMipiRx_vcu_DP/hw/kv260_ispMipiRx_vcu_DP.xsa -mem-ranges [list {0x80000000 0xbfffffff} {0x400000000 0x5ffffffff} {0x1000000000 0x7fffffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/deoch/Documents/WSU/CPTS_421/sel-embeddeddebugger/workspace/TestProject/_ide/psinit/psu_init.tcl
psu_init
after 1000
psu_ps_pl_isolation_removal
after 1000
psu_ps_pl_reset_config
catch {psu_protection}
targets -set -nocase -filter {name =~ "*A53*#0"}
rst -processor
dow C:/Users/deoch/Documents/WSU/CPTS_421/sel-embeddeddebugger/workspace/TestProject/Debug/TestProject.elf
configparams force-mem-access 0
bpadd -addr &main
