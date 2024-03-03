.section .text
.global get_32register_values

.macro MRS_REG reg_name, dest
    MRS \dest, \reg_name
.endm

get_32register_values:
    MOV x1, x0              // Load the address of the destination array into x1

    // Read and store the values of the specified registers
	MRS_REG FPCR, x0
	STR x0, [x1, #0]    // Store FPCR in the array

	MRS_REG FPSR, x0
	STR x0, [x1, #4]    // Store FPSR in the array

	MRS_REG MPIDR_EL1, x0
	STR x0, [x1, #8]    // Store MPIDR_EL1 in the array

	MRS_REG IFSR32_EL2, x0
	STR x0, [x1, #12]    // Store IFSR32_EL2 in the array

	MRS_REG ESR_EL1, x0
	STR x0, [x1, #16]    // Store ESR_EL1 in the array

	MRS_REG ESR_EL2, x0
	STR x0, [x1, #20]    // Store ESR_EL2 in the array

	MRS_REG ESR_EL3, x0
	STR x0, [x1, #24]    // Store ESR_EL3 in the array

	MRS_REG ISR_EL1, x0
	STR x0, [x1, #28]    // Store ISR_EL1 in the array

	MRS_REG SCTLR_EL3, x0
	STR x0, [x1, #32]    // Store SCTLR_EL3 in the array

	MRS_REG TCR_EL3, x0
	STR x0, [x1, #36]    // Store TCR_EL3 in the array

	MRS_REG CONTEXTIDR_EL1, x0
	STR x0, [x1, #40]    // Store CONTEXTIDR_EL1 in the array

	MRS_REG CPACR_EL1, x0
	STR x0, [x1, #44]    // Store CPACR_EL1 in the array

	MRS_REG ACTLR_EL3, x0
	STR x0, [x1, #48]    // Store ACTLR_EL3 in the array

	MRS_REG PMCR_EL0, x0
	STR x0, [x1, #52]    // Store PMCR_EL0 in the array

	MRS_REG PMCNTENSET_EL0, x0
	STR x0, [x1, #56]    // Store PMCNTENSET_EL0 in the array

	MRS_REG PMOVSCLR_EL0, x0
	STR x0, [x1, #60]    // Store PMOVSCLR_EL0 in the array

	MRS_REG PMUSERENR_EL0, x0
	STR x0, [x1, #64]    // Store PMUSERENR_EL0 in the array

	MRS_REG PMINTENSET_EL1, x0
	STR x0, [x1, #68]    // Store PMINTENSET_EL1 in the array

	MRS_REG PMEVCNTR0_EL0, x0
	STR x0, [x1, #72]    // Store PMEVCNTR0_EL0 in the array

	MRS_REG PMEVCNTR1_EL0, x0
	STR x0, [x1, #76]    // Store PMEVCNTR1_EL0 in the array

	MRS_REG PMEVCNTR2_EL0, x0
	STR x0, [x1, #80]    // Store PMEVCNTR2_EL0 in the array

	MRS_REG PMEVCNTR3_EL0, x0
	STR x0, [x1, #84]    // Store PMEVCNTR3_EL0 in the array

	MRS_REG PMEVCNTR4_EL0, x0
	STR x0, [x1, #88]    // Store PMEVCNTR4_EL0 in the array

	MRS_REG PMEVCNTR5_EL0, x0
	STR x0, [x1, #92]    // Store PMEVCNTR5_EL0 in the array

	MRS_REG PMEVTYPER0_EL0, x0
	STR x0, [x1, #96]    // Store PMEVTYPER0_EL0 in the array

	MRS_REG PMEVTYPER1_EL0, x0
	STR x0, [x1, #100]    // Store PMEVTYPER1_EL0 in the array

	MRS_REG PMEVTYPER2_EL0, x0
	STR x0, [x1, #104]    // Store PMEVTYPER2_EL0 in the array

	MRS_REG PMEVTYPER3_EL0, x0
	STR x0, [x1, #108]    // Store PMEVTYPER3_EL0 in the array

	MRS_REG PMEVTYPER4_EL0, x0
	STR x0, [x1, #112]    // Store PMEVTYPER4_EL0 in the array

	MRS_REG PMEVTYPER5_EL0, x0
	STR x0, [x1, #116]    // Store PMEVTYPER5_EL0 in the array

	MRS_REG PMCCFILTR_EL0, x0
	STR x0, [x1, #120]    // Store PMCCFILTR_EL0 in the array

	MRS_REG SCR_EL3, x0
	STR x0, [x1, #124]    // Store SCR_EL3 in the array

	MRS_REG CPTR_EL3, x0
	STR x0, [x1, #128]    // Store CPTR_EL3 in the array

	MRS_REG MDCR_EL3, x0
	STR x0, [x1, #132]    // Store MDCR_EL3 in the array

	MRS_REG CNTKCTL_EL1, x0
	STR x0, [x1, #136]    // Store CNTKCTL_EL1 in the array

	MRS_REG CNTP_TVAL_EL0, x0
	STR x0, [x1, #140]    // Store CNTP_TVAL_EL0 in the array

	MRS_REG CNTP_CTL_EL0, x0
	STR x0, [x1, #144]    // Store CNTP_CTL_EL0 in the array

	MRS_REG CNTV_TVAL_EL0, x0
	STR x0, [x1, #148]    // Store CNTV_TVAL_EL0 in the array

	MRS_REG CNTV_CTL_EL0, x0
	STR x0, [x1, #152]    // Store CNTV_CTL_EL0 in the array

	MRS_REG CNTHCTL_EL2, x0
	STR x0, [x1, #156]    // Store CNTHCTL_EL2 in the array

	MRS_REG CNTHP_TVAL_EL2, x0
	STR x0, [x1, #160]    // Store CNTHP_TVAL_EL2 in the array

	MRS_REG CNTHP_CTL_EL2, x0
	STR x0, [x1, #164]    // Store CNTHP_CTL_EL2 in the array

	MRS_REG CNTPS_TVAL_EL1, x0
	STR x0, [x1, #168]    // Store CNTPS_TVAL_EL1 in the array

	RET

