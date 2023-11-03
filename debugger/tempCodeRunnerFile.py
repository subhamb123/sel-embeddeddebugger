def read_file():
    registers = {}
    with open("registers_to_save.txt") as f:
        for line in f:
            # Remove leading spaces and newline characters
            line = line.strip()

            #Split the line into words
            words = line.split()
            if (len(words) == 2):
                registers[words[0]] = int(words[1])
    return registers

def write_32_c_array(list32):
    with open ("register32.txt", 'w') as f:
        for register in list32:
            f.write(f"\"{register}\",\n") 
            
def write_64_c_array(list64):
    with open ("register64.txt", 'w') as f:
        for register in list64:
            f.write(f"\"{register}\",\n")

def write_GICR_c_array(address32):
    with open ("registerGICR.txt", 'w') as f:
        for key in address32:
            f.write(f"\"{key}\",\n")

def write_32_assembly(list32):
    with open ("assembly32.txt", 'w') as f:
        i = 0
        for register in list32:
            f.write(f"MRS_REG {register}, x0\n")
            f.write(f"STR x0, [x1, #{i}]    // Store {register} in the array\n\n")
            i += 4

def write_64_assembly(list64):
    with open ("assembly64.txt", 'w') as f:
        i = 0
        for register in list64:
            f.write(f"MRS_REG {register}, x0\n")
            f.write(f"STR x0, [x1, #{i}]    // Store {register} in the array\n\n")
            i += 8

def write_GICR_assembly(address32):
    with open("assemblyGICR.txt", 'w') as f:
        i = 0
        for key in address32:
            f.write(f"LDR x0, ={address32[key]}       // Address for {key} register\nLDR x0, [x0]              // Load value from the address\nSTR x0, [x1, #{i}]          // Store GICC_CTRL value at offset {i}\n\n")
            i += 4

def write_V_assembly():
    with open("assemblyV.txt", 'w') as f:
        i = 0
        j = 1
        k = 0
        for n in range(64):
            f.write(f"MOV x0, v{i}.d[{j}]\nSTR x0, [x1, #{k}]\n\n")
            k += 8
            if j == 1:
                j -= 1
            else:
                j += 1
                i += 1
                
def write_X_assembly():
    with open("assemblyX.txt", 'w') as f:
        for i in range(2,31):
            f.write(f"STR x{i}, [x1, #{8*(i-2)}]\n")
def main():
    # read registers
    registers = read_file()
    
    # dictionary for registers that need address
    address32 = { "GICC_CTRL" : "0xf9020000", "GICC_PMR" : "0xf9020004", "GICC_BPR" : "0xf9020008", 
               "GICC_RPR" : "0xf9020014", "GICC_HPPIR" : "0xf9020018", "GICC_ABPR" : "0xf902001c",
               "GICC_AHPPIR" : "0xf9020028", "GICC_APR0" : "0xf90200d0", "GICC_NSAPR0" : "0xf90200e0",
               "GICD_CTLR" : "0xf9010000", "GICD_IGROUPR0-5" : "0xf9010094", "GICD_ISENABLER0-5" : "0xf9010114",
               "GICD_ISPENDR0-5" : "0xf9010214", "GICD_ISACTIVER0-5" : "0xf9010314", "GICD_IPRIORITYR0-47" : "0xf90104bc",
               "GICD_ITARGETSR0-47" : "0xf90108bc", "GICD_ICFGR0-11" : "0xf9010c2c", "GICD_PPISR" : "0xf9010d00",
               "GICD_SPISR0-4" : "0xf9010d14", "GICD_SPENDSGIR0-3" : "0xf9010f2c"}
    
    # dictionary for ignore
    address64 = {"R0-R30" : 0, "SP" : 0, "PC" : 0, "V0-V31" : 0, "CPUACTLR_EL1" : 0, "CPUECTLR_EL1" : 0, "CPUMERRSR_EL1" : 0, "L2MERRSR_EL1" : 0}
    
    # store registers in appropriate list
    list32 = []
    list64 = []    
    for register in registers:
        if register in address32 or register in address64:
            continue
        if registers[register] == 32:
            list32.append(register)
        if registers[register] == 64:
            list64.append(register)
    
    # write out register names to hold in c char array
    write_32_c_array(list32)
    write_64_c_array(list64)
    write_GICR_c_array(address32)
    
    # write out assembly to read registers
    write_32_assembly(list32)
    write_64_assembly(list64)
    
    # write out assembly to read GICR registers
    write_GICR_assembly(address32)
    
    # write out assembly to read V registers
    write_V_assembly()
    
    # write out assembly to read X registers
    write_X_assembly()
    
    
    
            
    
if __name__ == "__main__":
    main()