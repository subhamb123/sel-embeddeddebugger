.section .text
.global get_GICRregister_values

get_GICRregister_values:
	MOV x1, x0              // Load the address of the destination array into x1

    LDR x0, =0xf9020000       // Address for GICC_CTRL register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #0]          // Store GICC_CTRL value at offset 0

	LDR x0, =0xf9020004       // Address for GICC_PMR register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #4]          // Store GICC_CTRL value at offset 4

	LDR x0, =0xf9020008       // Address for GICC_BPR register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #8]          // Store GICC_CTRL value at offset 8

	LDR x0, =0xf9020014       // Address for GICC_RPR register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #12]          // Store GICC_CTRL value at offset 12

	LDR x0, =0xf9020018       // Address for GICC_HPPIR register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #16]          // Store GICC_CTRL value at offset 16

	LDR x0, =0xf902001c       // Address for GICC_ABPR register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #20]          // Store GICC_CTRL value at offset 20

	LDR x0, =0xf9020028       // Address for GICC_AHPPIR register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #24]          // Store GICC_CTRL value at offset 24

	LDR x0, =0xf90200d0       // Address for GICC_APR0 register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #28]          // Store GICC_CTRL value at offset 28

	LDR x0, =0xf90200e0       // Address for GICC_NSAPR0 register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #32]          // Store GICC_CTRL value at offset 32

	LDR x0, =0xf9010000       // Address for GICD_CTLR register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #36]          // Store GICC_CTRL value at offset 36

	LDR x0, =0xf9010094       // Address for GICD_IGROUPR0-5 register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #40]          // Store GICC_CTRL value at offset 40

	LDR x0, =0xf9010114       // Address for GICD_ISENABLER0-5 register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #44]          // Store GICC_CTRL value at offset 44

	LDR x0, =0xf9010214       // Address for GICD_ISPENDR0-5 register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #48]          // Store GICC_CTRL value at offset 48

	LDR x0, =0xf9010314       // Address for GICD_ISACTIVER0-5 register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #52]          // Store GICC_CTRL value at offset 52

	LDR x0, =0xf90104bc       // Address for GICD_IPRIORITYR0-47 register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #56]          // Store GICC_CTRL value at offset 56

	LDR x0, =0xf90108bc       // Address for GICD_ITARGETSR0-47 register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #60]          // Store GICC_CTRL value at offset 60

	LDR x0, =0xf9010c2c       // Address for GICD_ICFGR0-11 register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #64]          // Store GICC_CTRL value at offset 64

	LDR x0, =0xf9010d00       // Address for GICD_PPISR register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #68]          // Store GICC_CTRL value at offset 68

	LDR x0, =0xf9010d14       // Address for GICD_SPISR0-4 register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #72]          // Store GICC_CTRL value at offset 72

	LDR x0, =0xf9010f2c       // Address for GICD_SPENDSGIR0-3 register
	LDR x0, [x0]              // Load value from the address
	STR x0, [x1, #76]          // Store GICC_CTRL value at offset 76






	RET
