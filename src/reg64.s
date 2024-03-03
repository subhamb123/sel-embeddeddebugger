.section .text
.global get_64register_values

.macro MRS_REG reg_name, dest
    MRS \dest, \reg_name
.endm

get_64register_values:
    MOV x1, x0              // Load the address of the destination array into x1

    // Read and store the values of the specified registers
	MRS_REG FAR_EL3, x0
	STR x0, [x1, #0]    // Store FAR_EL3 in the array

	MRS_REG VBAR_EL3, x0
	STR x0, [x1, #8]    // Store VBAR_EL3 in the array

	MRS_REG TTBR0_EL3, x0
	STR x0, [x1, #16]    // Store TTBR0_EL3 in the array

	MRS_REG MAIR_EL3, x0
	STR x0, [x1, #24]    // Store MAIR_EL3 in the array

	MRS_REG AMAIR_EL3, x0
	STR x0, [x1, #32]    // Store AMAIR_EL3 in the array

	MRS_REG PAR_EL1, x0
	STR x0, [x1, #40]    // Store PAR_EL1 in the array

	MRS_REG TPIDR_EL0, x0
	STR x0, [x1, #48]    // Store TPIDR_EL0 in the array

	MRS_REG TPIDRRO_EL0, x0
	STR x0, [x1, #56]    // Store TPIDRRO_EL0 in the array

	MRS_REG TPIDR_EL1, x0
	STR x0, [x1, #64]    // Store TPIDR_EL1 in the array

	MRS_REG TPIDR_EL3, x0
	STR x0, [x1, #72]    // Store TPIDR_EL3 in the array

	MRS_REG RVBAR_EL3, x0
	STR x0, [x1, #80]    // Store RVBAR_EL3 in the array

	MRS_REG RMR_EL3, x0
	STR x0, [x1, #88]    // Store RMR_EL3 in the array

	MRS_REG SDER32_EL3, x0
	STR x0, [x1, #96]    // Store SDER32_EL3 in the array

	MRS_REG CNTFRQ_EL0, x0
	STR x0, [x1, #104]    // Store CNTFRQ_EL0 in the array

	MRS_REG CNTVCT_EL0, x0
	STR x0, [x1, #112]    // Store CNTVCT_EL0 in the array

	MRS_REG CNTP_CVAL_EL0, x0
	STR x0, [x1, #120]    // Store CNTP_CVAL_EL0 in the array

	MRS_REG CNTV_CVAL_EL0, x0
	STR x0, [x1, #128]    // Store CNTV_CVAL_EL0 in the array

	MRS_REG CNTVOFF_EL2, x0
	STR x0, [x1, #136]    // Store CNTVOFF_EL2 in the array

	MRS_REG CNTHP_CVAL_EL2, x0
	STR x0, [x1, #144]    // Store CNTHP_CVAL_EL2 in the array

	MRS_REG CNTPS_CVAL_EL1, x0
	STR x0, [x1, #152]    // Store CNTPS_CVAL_EL1 in the array

	MRS_REG CNTPS_CTL_EL1, x0
	STR x0, [x1, #160]    // Store CNTPS_CTL_EL1 in the array

	MRS_REG ELR_EL1, x0
	STR x0, [x1, #168]    // Store ELR_EL1 in the array

	MRS_REG ELR_EL2, x0
	STR x0, [x1, #176]    // Store ELR_EL2 in the array

	MRS_REG ELR_EL3, x0
	STR x0, [x1, #184]    // Store ELR_EL3 in the array




    RET
