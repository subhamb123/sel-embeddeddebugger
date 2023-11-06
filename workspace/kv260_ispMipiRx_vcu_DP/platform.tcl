# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\deoch\workspace\kv260_ispMipiRx_vcu_DP\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\deoch\workspace\kv260_ispMipiRx_vcu_DP\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {kv260_ispMipiRx_vcu_DP}\
-hw {C:\Xilinx\Vitis\2023.1\data\embeddedsw\lib\fixed_hwplatforms\kv260_ispMipiRx_vcu_DP.xsa}\
-arch {64-bit} -fsbl-target {psu_cortexa53_0} -out {C:/Users/deoch/workspace}

platform write
domain create -name {standalone_psu_cortexa53_0} -display-name {standalone_psu_cortexa53_0} -os {standalone} -proc {psu_cortexa53_0} -runtime {cpp} -arch {64-bit} -support-app {hello_world}
platform generate -domains 
platform active {kv260_ispMipiRx_vcu_DP}
domain active {zynqmp_fsbl}
domain active {zynqmp_pmufw}
domain active {standalone_psu_cortexa53_0}
platform generate -quick
platform generate
platform generate
platform generate
