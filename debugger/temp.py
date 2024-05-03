import os

registers = { "IFSR32_EL2": " sys 5 ",  "ESR_EL1": " sys 5 ",  "ESR_EL2": " sys 5 ", "ESR_EL3": " sys 5 ", "SCTLR_EL3" : " sys 1 ", 
             "TCR_EL3" : " sys 2 ", "CONTEXTIDR_EL1" : " sys 13 ", "ELR_EL1" : " sys 4 ", "ELR_EL2" : " sys 4 ", "ELR_EL3" : " sys 4 ",
             "CPACR_EL1" : " sys 1 ", "ACTLR_EL3" : " sys 1 ", "PMCR_EL0" : " sys 9 ", "PMCNTENSET_EL0" : " sys 9 ", "PMOVSCLR_EL0" : " sys 9 ",
             "PMUSERENR_EL0" : " sys 9 ", "PMINTENSET_EL1" :" sys 9 ", "PMEVCNTR0_EL0" : " sys 14 ", "PMEVCNTR1_EL0" : " sys 14 ",
             "PMEVCNTR2_EL0" : " sys 14 ", "PMEVCNTR3_EL0" : " sys 14 ", "PMEVCNTR4_EL0" : " sys 14 ", "PMEVCNTR5_EL0" : " sys 14 ",
             "PMEVTYPER0_EL0" : " sys 14 ", "PMEVTYPER1_EL0" : " sys 14 ", "PMEVTYPER2_EL0" : " sys 14 ", "PMEVTYPER3_EL0" : " sys 14 ",
             "PMEVTYPER4_EL0" : " sys 14 ", "PMEVTYPER5_EL0" : " sys 14 ", "PMCCFILTR_EL0" :" sys 14 ", "SCR_EL3" : " sys 1 ",
             "CPTR_EL3" : " sys 1 ", "MDCR_EL3" : " sys 1 ", "CNTKCTL_EL1" : " sys 14 ", "CNTP_TVAL_EL0" :" sys 14 ",
             "CNTP_CTL_EL0" : " sys 14 ", "CNTV_TVAL_EL0" : " sys 14 ", "CNTV_CTL_EL0" : " sys 14 ", "CNTHCTL_EL2" : " sys 14 ",
             "CNTHP_TVAL_EL2" : " sys 14 ", "CNTHP_CTL_EL2" : " sys 14 ", "CNTPS_TVAL_EL1" : " sys 14 ", "CNTPS_CTL_EL1" : " sys 14 ",
             "GICC_CTLR" : " acpu_gic ", "GICC_PMR" : " acpu_gic ", "GICC_BPR" : " acpu_gic ", "GICC_ABPR" : " acpu_gic ", "GICC_APR0" : " acpu_gic ",
             "GICC_NSAPR0" : " acpu_gic ", "GICD_CTLR" : " acpu_gic ", "GICD_IGROUPR" : " acpu_gic ", "GICD_ISENABLER" : " acpu_gic ",
             "GICD_ISPENDR" : " acpu_gic ", "GICD_ISACTIVER" : " acpu_gic ", "GICD_IPRIORITYR" : " acpu_gic ","GICD_ITARGETSR" : " acpu_gic ",
             "GICD_ICFGR" : " acpu_gic ", "GICD_SPISR" : " acpu_gic ", "GICD_SPENDSGIR" : " acpu_gic ", "FAR_EL3" : " sys 6 ", "VBAR_EL3" : " sys 12 ",
             "TTBR0_EL3" : " sys 2 ", "MAIR_EL3" : " sys 10 ", "AMAIR_EL3" : " sys 10 ", "PAR_EL1" : " sys 7 ", "TPIDR_EL0" : " sys 13 ", 
             "TPIDRRO_EL0" : " sys 13 ", "TPIDR_EL1" : " sys 13 ", "TPIDR_EL3" : " sys 13 ", "RVBAR_EL3" : " sys 12 ", "RMR_EL3" : " sys 12 ",
             "SDER32_EL3": " sys 1 ", "CNTFRQ_EL0" : " sys 14 ", "CNTP_CVAL_EL0" : " sys 14 ", "CNTV_CVAL_EL0" : " sys 14 ",
             "CNTVOFF_EL2" : " sys 14 ", "CNTHP_CVAL_EL2" : " sys 14 ", "CNTPS_CVAL_EL1" : " sys 14 ", "v" : " vfp ", "r" : " ", "SP" : " ", "PC" : " ",
             "FPCR" : " sys 4 ", "FPSR" : " sys 4 ", "MPIDR_EL1" : " sys 0 ", "ISR_EL1" : " sys 12 ", "GICC_RPR" : " acpu_gic ", "GICC_HPPIR" : " acpu_gic ",
               "GICC_AHPPIR" : " acpu_gic ", "GICD_PPISR" : " acpu_gic ", "GICD_SPISR" : " acpu_gic ", "RVABR_EL3" : " sys 12 ", "CNTVCT_EL0" : " sys 12 "}

def generate_register_tcl():
    __location__ = os.path.realpath(
    os.path.join(os.getcwd(), os.path.dirname(__file__)))
    f = open(os.path.join(__location__, "registers.txt"))
    with open ("read_registers.tcl", 'w') as g:
        g.write("# source C:/Users/deoch/Documents/sel-embeddeddebugger/debugger/read_registers.tcl\n")
        for line in f:
            # Remove leading spaces and newline characters
            line = line.strip()

            # Split the line into words
            words = line.split(":")
            
            # Get register name
            register = words[0]

            if (register == "RVBAR_EL3" or register == "CNTVCT_EL0"):
                continue
            
            # Remove numbers except for ELx
            if len(register) <= 3 or (len(register) > 4 and (register[:6] == "GICD_I" or register[:6] == "GICD_S")):
                register = ''.join((x for x in register if not x.isdigit()))
                
            # Write out TCL script
            g.write(f"puts [rrd{registers[register]}{words[0].lower()}]")
            g.write("\n")    
    f.close()

generate_register_tcl()