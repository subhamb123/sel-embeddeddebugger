#include "snapshot.h"
void (*synchronous_interrupt_handler)(void); // Define the function pointer variable

uintptr_t baseAddress = 0x000c0c0;  // Definition of baseAddress
size_t size = 12288;                // Definition of size

void set_exception_vector_table_entry(void* table_entry_address, uint32_t branch_instruction) {
    // Store the branch instruction in the table entry
    // Use inline assembly to do this
    asm volatile (
        "str %0, [%1]\n"  // Store the branch instruction into the table entry
        :
        : "r" (branch_instruction), "r" (table_entry_address)
    );
}

void start_up()
{
	void* handler_address = (void*)(&exception_handler);

	// Get the address of the Exception Vector Table
	void* vector_table_address = get_vbar_el1_register_value(); // Obtain the address of the vector table

	// Set the offset to +0x200
	uintptr_t table_offset = 0x200;

	// Calculate the address of the specific exception entry in the table
	void* entry_address = vector_table_address + table_offset;

	// Get original branch instruction
	uint32_t original_branch = *((uint32_t*)entry_address);

	// Extract offset
	uint32_t original_handler_offset = original_branch & 0x03FFFFFF;

	// Get Address of Original Handler
	uint32_t original_address = original_handler_offset * 4 + entry_address;

	// Set functionPointer to Original Handler
	synchronous_interrupt_handler = (void (*)(void))original_address;


	// Calculate the offset for the branch instruction
	uintptr_t branch_offset = ((uintptr_t)handler_address - (uintptr_t)entry_address)/4;

	// Create the branch instruction (B opcode is 0x14) with the offset
	uint32_t branch_instruction = 0x14000000 | (branch_offset & 0x03FFFFFF);

	// Set the branch instruction in the exception vector table entry
	set_exception_vector_table_entry(entry_address, branch_instruction);

}

void print_stack(uintptr_t baseAddress, size_t size, uintptr_t addresses[], int addressesSize)
{
    // Declare a pointer to an unsigned integer (assuming 4 bytes per word)
    unsigned int *ptr = (unsigned int *)baseAddress;

    // Get iterator for addresses
    int j = get_index(addresses, addressesSize);

    // Iterate through the stack memory and print each value
    for (size_t i = 0; i < size / sizeof(unsigned int); ++i) {
        // Print the value at the current memory location
        xil_printf("Address:0x%08lx,Value:0x%08x\n", (unsigned long)(ptr + i), *(ptr + i));
        if (j < addressesSize && *(ptr + i) > LOW && *(ptr + i) < HIGH )
        {
        	addresses[j] = *(ptr + i);
        	j++;
        }
    }
}

void print_x_registers(uintptr_t addresses[], int addressesSize)
{
	// Allocate memory for register values
	uint64_t register_values[31];

	// Get X0 and X1 respectively
	register_values[0] = get_x0register_value();
	register_values[1] = get_x1register_value();

	// Get X2-x30 values
	get_Xregister_values(register_values + 2);

	// Get iterator for addresses
	int j = get_index(addresses, addressesSize);

	// Print register values along with their names
	for (int i = 0; i < 31; ++i) {
		xil_printf("r%d:0x%016llx\n", i, register_values[i]);

		if (j < addressesSize && register_values[i] > LOW && register_values[i] < HIGH )
		{
			addresses[j] = register_values[i];
			j++;
		}
	}
}

void print_32_bit_system_registers(uintptr_t addresses[], int addressesSize)
{
	// Allocate memory for register values
	uint32_t register_values[64];

	// Get iterator for addresses
	int j = get_index(addresses, addressesSize);

    // Array of register names
    const char* register_names[] = {
    		"FPCR",
    		"FPSR",
    		"MPIDR_EL1",
    		"IFSR32_EL2",
			"ESR_EL1",
			"ESR_EL2",
    		"ESR_EL3",
    		"ISR_EL1",
    		"SCTLR_EL3",
    		"TCR_EL3",
    		"CONTEXTIDR_EL1",
    		"CPACR_EL1",
    		"ACTLR_EL3",
    		"PMCR_EL0",
    		"PMCNTENSET_EL0",
    		"PMOVSCLR_EL0",
    		"PMUSERENR_EL0",
    		"PMINTENSET_EL1",
    		"PMEVCNTR0_EL0",
    		"PMEVCNTR1_EL0",
    		"PMEVCNTR2_EL0",
    		"PMEVCNTR3_EL0",
    		"PMEVCNTR4_EL0",
    		"PMEVCNTR5_EL0",
    		"PMEVTYPER0_EL0",
    		"PMEVTYPER1_EL0",
    		"PMEVTYPER2_EL0",
    		"PMEVTYPER3_EL0",
    		"PMEVTYPER4_EL0",
    		"PMEVTYPER5_EL0",
    		"PMCCFILTR_EL0",
    		"SCR_EL3",
    		"CPTR_EL3",
    		"MDCR_EL3",
    		"CNTKCTL_EL1",
    		"CNTP_TVAL_EL0",
    		"CNTP_CTL_EL0",
    		"CNTV_TVAL_EL0",
    		"CNTV_CTL_EL0",
    		"CNTHCTL_EL2",
    		"CNTHP_TVAL_EL2",
    		"CNTHP_CTL_EL2",
    		"CNTPS_TVAL_EL1",
    		"CNTPS_CTL_EL1"

    };

	// Call the assembly function and pass the array's pointer
	get_32register_values(register_values);

	// Print register values along with their names
	for (int i = 0; i < 44; ++i) {
		xil_printf("%s:0x%08x\n", register_names[i], register_values[i]);
		if (j < addressesSize && register_values[i] > LOW && register_values[i] < HIGH )
		{
			addresses[j] = register_values[i];
			j++;
		}
	}
}

void print_gicr_registers()
{
	// Allocate memory for register values
	//uint32_t register_values[20];

    // Array of register names
    const char* register_names[] = {
    		"GICC_CTLR",
    		"GICC_PMR",
    		"GICC_BPR",
    		"GICC_RPR",
    		"GICC_HPPIR",
    		"GICC_ABPR",
    		"GICC_AHPPIR",
    		"GICC_APR0",
    		"GICC_NSAPR0",
    		"GICD_CTLR",
    		"GICD_PPISR"


    };

    uint64_t addresses[] = {
    	0x00f9020000,
		0x00f9020004,
		0x00f9020008,
        0x00f9020014,
        0x00f9020018,
        0x00f902001c,
        0x00f9020028,
        0x00f90200d0,
        0x00f90200e0,
		0x00f9010000,
		0x00f9010d00

    };
    for (int i = 0; i < sizeof(addresses) / sizeof(uint64_t); ++i) {
    		volatile uint32_t* addr_ptr = (volatile uint32_t*) addresses[i];
    	    uint32_t value = *addr_ptr;
    		xil_printf("%s:0x%08x\n", register_names[i], value);;
        }
	// Call the assembly function and pass the array's pointer
	//get_GICRregister_values(register_values);

	// Print register values along with their names
	//for (int i = 0; i < 20; ++i) {
	//	xil_printf("\n\r%s: 0x%08x\n", register_names[i], register_values[i]);
	//}

    // Print out the non-singular registers

    const char* register_names_multiple[] = {
        		"GICD_IGROUP",
        		"GICD_ISENABLE",
        		"GICD_ISPEND",
        		"GICD_ISACTIVE",
        		"GICD_IPRIORITY",
        		"GICD_ITARGETS",
        		"GICD_ICFG",
        		"GICD_SPIS",
        		"GICD_SPENDSGI",
        };

    uint64_t addresses_multiple[] = {
    		0x00f9010080,
			0x00f9010100,
			0x00f9010200,
			0x00f9010300,
			0x00f9010400,
			0x00f9010800,
			0x00f9010c00,
			0x00f9010d04,
			0x00f9010f20
        };

    int range[] = {
    		6,
			6,
			6,
			6,
			48,
			48,
			12,
			5,
			4
    };

    for (int i = 0; i < sizeof(addresses_multiple) / sizeof(uint64_t); ++i) {
        		volatile uint32_t* base_addr_ptr = (volatile uint32_t*) addresses_multiple[i];
        		for (int j = 0; j < range[i]; j++) {
        			uint32_t value = *(base_addr_ptr + (j));
        			xil_printf("%sR%d:0x%08x\n", register_names_multiple[i], j, value);;
        		}

            }
}

void print_64_bit_system_registers(uintptr_t addresses[], int addressesSize)
{
	// Allocate memory for register values
	uint64_t register_values[20];

	// Get iterator for addresses
	int j = get_index(addresses, addressesSize);

    // Array of register names
    const char* register_names[] = {

    		"FAR_EL3",
    		"VBAR_EL3",
    		"TTBR0_EL3",
    		"MAIR_EL3",
    		"AMAIR_EL3",
    		"PAR_EL1",
    		"TPIDR_EL0",
    		"TPIDRRO_EL0",
    		"TPIDR_EL1",
    		"TPIDR_EL3",
    		"RVBAR_EL3",
    		"RMR_EL3",
    		"SDER32_EL3",
    		"CNTFRQ_EL0",
    		"CNTVCT_EL0",
    		"CNTP_CVAL_EL0",
    		"CNTV_CVAL_EL0",
    		"CNTVOFF_EL2",
    		"CNTHP_CVAL_EL2",
    		"CNTPS_CVAL_EL1",
			"ELR_EL1",
			"ELR_EL2",
			"ELR_EL3"

    };

	// Call the assembly function and pass the array's pointer
	get_64register_values(register_values);

	// Print register values along with their names
	for (int i = 0; i < 23; ++i) {
		xil_printf("%s:0x%016llx\n", register_names[i], register_values[i]);
		if (j < addressesSize && register_values[i] > LOW && register_values[i] < HIGH )
		{
			addresses[j] = register_values[i];
			j++;
		}
	}
}

void print_v_registers()
{
	// Allocate memory for register values
	//uint64_t register_values[32][2];
	__int128_t register_values[32];
	get_Vregister_values(register_values);

	for (int i = 0; i < 32; i++){
		xil_printf("v%d: 0x%016llx\n", i, register_values[i]);
		//xil_printf("\n\rv%d.d[0]: 0x%016llx", i, register_values[i][0]);
		//xil_printf("\n\rv%d.d[1]: 0x%016llx", i, register_values[i][1]);
	}
}

void print_sp_register()
{
	uint64_t value = get_SPregister_value();
	xil_printf("SP:0x%016llx\n", value);
}

void printAddress(uintptr_t address)
{
	for (int i = -RANGE; i <= RANGE; i++)
	{
		if (address + i > LOW && address+ i < HIGH)
			xil_printf("Address:0x%08lx,Value:0x%08lx\n", (unsigned long)(address + i), *((uintptr_t*)(address + i)));
	}
}

void print_data(uintptr_t addresses[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (addresses[i] == 0)
			break;
		xil_printf("Address:0x%08lx\n", addresses[i]);
		printAddress(addresses[i]);
	}
}

int get_index(uintptr_t addresses[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (addresses[i] == 0)
			return i;
	}

	return size;
}

void exception_handler()
{
	uintptr_t addresses[SIZE] = {0};
	xil_printf("\nSTART\n"); // send start signal
	print_stack(baseAddress, size, addresses, SIZE);
    xil_printf("STACK_END\n"); // end stack delimiter
	print_x_registers(addresses, SIZE);
	print_32_bit_system_registers(addresses, SIZE);
	print_gicr_registers();
	print_64_bit_system_registers(addresses, SIZE);
	print_v_registers();
	print_sp_register();
	xil_printf("REGISTER_END\n"); // end stack delimiter
	print_data(addresses, SIZE);
	xil_printf("END\n"); // send end signal
	//synchronous_interrupt_handler();
}
