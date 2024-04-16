.section .text
.global freertos_exception_startup
.extern registers

.macro MRS_REG reg_name, dest
    MRS \dest, \reg_name
.endm

freertos_exception_startup:
    // Load registers x29 and x30 from the stack
    ldp     x29, x30, [sp], #16
    // Load registers x18 to x2 from the stack
    ldp     x18, x19, [sp], #16
    ldp     x16, x17, [sp], #16
    ldp     x14, x15, [sp], #16
    ldp     x12, x13, [sp], #16
    ldp     x10, x11, [sp], #16
    ldp     x8, x9, [sp], #16
    ldp     x6, x7, [sp], #16
    ldp     x4, x5, [sp], #16
    ldp     x2, x3, [sp], #16

    // Load the address of the external register pointer (registers)
    adrp    x1, registersx      // Load the page address of registersx into x1
	add     x1, x1, :lo12:registersx // Add the low 12 bits of registersx address to x1

    // Calculate the memory address for each register and store its value in the corresponding element of the registers array
    stp     x29, x30, [x1, #29*8]    // Write x29 and x30 to registers[29] and registers[30]
    stp     x27, x28, [x1, #27*8]    // not from stack
    stp     x25, x26, [x1, #25*8]    // not from stack
    stp     x23, x24, [x1, #23*8]    // not from stack
    stp     x21, x22, [x1, #21*8]    // not from stack
    str     x20, [x1, #20*8]		 // outlier
    stp     x18, x19, [x1, #18*8]    // Write x18 and x19 to registers[18] and registers[19]
    stp     x16, x17, [x1, #16*8]    // Write x16 and x17 to registers[16] and registers[17]
    stp     x14, x15, [x1, #14*8]    // Write x14 and x15 to registers[14] and registers[15]
    stp     x12, x13, [x1, #12*8]    // Write x12 and x13 to registers[12] and registers[13]
    stp     x10, x11, [x1, #10*8]    // Write x10 and x11 to registers[10] and registers[11]
    stp     x8, x9, [x1, #8*8]       // Write x8 and x9 to registers[8] and registers[9]
    stp     x6, x7, [x1, #6*8]       // Write x6 and x7 to registers[6] and registers[7]
    stp     x4, x5, [x1, #4*8]       // Write x4 and x5 to registers[4] and registers[5]
    stp     x2, x3, [x1, #2*8]       // Write x2 and x3 to registers[2] and registers[3]

    // Move the address of the external register pointer (registers) from x1 to x2
    mov     x2, x1

    // Load registers x29 and x30 from the stack
    ldp     x0, x1, [sp], #16


    // Store x0 and x1 to registers[0] and registers[1] using stp
    stp     x0, x1, [x2]             // Write x0 and x1 to registers[0] and registers[1]

    // Store pc
    MRS_REG ELR_EL3, x0   // Get PC from elr_el3
    str x0, [x2, #31*8]

    // Store 32 bit system registers

    // Load the address of the external register pointer (registers)
    adrp    x1, registers32      // Load the page address of registers32 into x1
	add     x1, x1, :lo12:registers32 // Add the low 12 bits of registers32 address to x1

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

    // Store 64 bit system registers

    // Load the address of the external register pointer (registers)
    adrp    x1, registers64      // Load the page address of registers64 into x1
	add     x1, x1, :lo12:registers64 // Add the low 12 bits of registers64 address to x1

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

    // Store v registers

    // Load the address of the external register pointer (registers)
    adrp    x1, registersv      // Load the page address of registersv into x1
	add     x1, x1, :lo12:registersv // Add the low 12 bits of registersv address to x1

	MOV x0, v0.d[0]
	STR x0, [x1, #0]

	MOV x0, v0.d[1]
	STR x0, [x1, #8]

	MOV x0, v1.d[0]
	STR x0, [x1, #16]

	MOV x0, v1.d[1]
	STR x0, [x1, #24]

	MOV x0, v2.d[0]
	STR x0, [x1, #32]

	MOV x0, v2.d[1]
	STR x0, [x1, #40]

	MOV x0, v3.d[0]
	STR x0, [x1, #48]

	MOV x0, v3.d[1]
	STR x0, [x1, #56]

	MOV x0, v4.d[0]
	STR x0, [x1, #64]

	MOV x0, v4.d[1]
	STR x0, [x1, #72]

	MOV x0, v5.d[0]
	STR x0, [x1, #80]

	MOV x0, v5.d[1]
	STR x0, [x1, #88]

	MOV x0, v6.d[0]
	STR x0, [x1, #96]

	MOV x0, v6.d[1]
	STR x0, [x1, #104]

	MOV x0, v7.d[0]
	STR x0, [x1, #112]

	MOV x0, v7.d[1]
	STR x0, [x1, #120]

	MOV x0, v8.d[0]
	STR x0, [x1, #128]

	MOV x0, v8.d[1]
	STR x0, [x1, #136]

	MOV x0, v9.d[0]
	STR x0, [x1, #144]

	MOV x0, v9.d[1]
	STR x0, [x1, #152]

	MOV x0, v10.d[0]
	STR x0, [x1, #160]

	MOV x0, v10.d[1]
	STR x0, [x1, #168]

	MOV x0, v11.d[0]
	STR x0, [x1, #176]

	MOV x0, v11.d[1]
	STR x0, [x1, #184]

	MOV x0, v12.d[0]
	STR x0, [x1, #192]

	MOV x0, v12.d[1]
	STR x0, [x1, #200]

	MOV x0, v13.d[0]
	STR x0, [x1, #208]

	MOV x0, v13.d[1]
	STR x0, [x1, #216]

	MOV x0, v14.d[0]
	STR x0, [x1, #224]

	MOV x0, v14.d[1]
	STR x0, [x1, #232]

	MOV x0, v15.d[0]
	STR x0, [x1, #240]

	MOV x0, v15.d[1]
	STR x0, [x1, #248]

	MOV x0, v16.d[0]
	STR x0, [x1, #256]

	MOV x0, v16.d[1]
	STR x0, [x1, #264]

	MOV x0, v17.d[0]
	STR x0, [x1, #272]

	MOV x0, v17.d[1]
	STR x0, [x1, #280]

	MOV x0, v18.d[0]
	STR x0, [x1, #288]

	MOV x0, v18.d[1]
	STR x0, [x1, #296]

	MOV x0, v19.d[0]
	STR x0, [x1, #304]

	MOV x0, v19.d[1]
	STR x0, [x1, #312]

	MOV x0, v20.d[0]
	STR x0, [x1, #320]

	MOV x0, v20.d[1]
	STR x0, [x1, #328]

	MOV x0, v21.d[0]
	STR x0, [x1, #336]

	MOV x0, v21.d[1]
	STR x0, [x1, #344]

	MOV x0, v22.d[0]
	STR x0, [x1, #352]

	MOV x0, v22.d[1]
	STR x0, [x1, #360]

	MOV x0, v23.d[0]
	STR x0, [x1, #368]

	MOV x0, v23.d[1]
	STR x0, [x1, #376]

	MOV x0, v24.d[0]
	STR x0, [x1, #384]

	MOV x0, v24.d[1]
	STR x0, [x1, #392]

	MOV x0, v25.d[0]
	STR x0, [x1, #400]

	MOV x0, v25.d[1]
	STR x0, [x1, #408]

	MOV x0, v26.d[0]
	STR x0, [x1, #416]

	MOV x0, v26.d[1]
	STR x0, [x1, #424]

	MOV x0, v27.d[0]
	STR x0, [x1, #432]

	MOV x0, v27.d[1]
	STR x0, [x1, #440]

	MOV x0, v28.d[0]
	STR x0, [x1, #448]

	MOV x0, v28.d[1]
	STR x0, [x1, #456]

	MOV x0, v29.d[0]
	STR x0, [x1, #464]

	MOV x0, v29.d[1]
	STR x0, [x1, #472]

	MOV x0, v30.d[0]
	STR x0, [x1, #480]

	MOV x0, v30.d[1]
	STR x0, [x1, #488]

	MOV x0, v31.d[0]
	STR x0, [x1, #496]

	MOV x0, v31.d[1]
	STR x0, [x1, #504]

	// Store GICD registers

    // Branch to the exception_handler() function
    adr     x0, freertos_exception_handler    // Load the address of exception_handler() into x0
    b       freertos_exception_handler        // Branch with link to exception_handler()
