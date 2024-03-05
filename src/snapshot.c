#include "snapshot.h"

uint64_t registers[32] = {0};      		// Definition of registers

// Linker file symbol values definitions

const uint64_t data_start = (uintptr_t)& __data_start;
const uint64_t data_end = (uintptr_t)& __data_end;
const uint64_t sdata_start = (uintptr_t)& __sdata_start;
const uint64_t sdata_end = (uintptr_t)& __sdata_end;
const uint64_t sbss_start = (uintptr_t)& __sbss_start;
const uint64_t sbss_end = (uintptr_t)& __sbss_end;
const uint64_t tdata_start = (uintptr_t)& __tdata_start;
const uint64_t tdata_end = (uintptr_t)& __tdata_start;
const uint64_t tbss_start = (uintptr_t)& __tbss_start;
const uint64_t tbss_end = (uintptr_t)& __tbss_end;
const uint64_t bss_start = (uintptr_t)& __bss_start__;
const uint64_t bss_end = (uintptr_t)& __bss_end__;
const uint64_t heap_start = (uintptr_t)& _heap_start;
const uint64_t heap_end = (uintptr_t)& _heap_end;
const uint64_t stack_start = (uintptr_t)&_el3_stack_end;
const uint64_t el3_stack_size = (uintptr_t)&_STACK_SIZE;
const uint64_t el2_stack_size = (uintptr_t)&_EL2_STACK_SIZE;
const uint64_t el1_stack_size = (uintptr_t)&_EL1_STACK_SIZE;
const uint64_t el0_stack_size = (uintptr_t)&_EL0_STACK_SIZE;

void split_uint64(uint64_t input, uint32_t *high, uint32_t *low)
{
    // Mask for extracting the lower 32 bits
    uint64_t lower_mask = 0xFFFFFFFFULL;
    // Extract the lower 32 bits
    *low = (uint32_t)(input & lower_mask);
    // Shift the input to the right by 32 bits to get the higher 32 bits
    *high = (uint32_t)(input >> 32);
}

void split_int128(__int128_t input, uint32_t *part1, uint32_t *part2, uint32_t *part3, uint32_t *part4)
{
    // Extract each 32-bit segment
    *part4 = (uint32_t)(input & 0xFFFFFFFF);
    *part3 = (uint32_t)((input >> 32) & 0xFFFFFFFF);
    *part2 = (uint32_t)((input >> 64) & 0xFFFFFFFF);
    *part1 = (uint32_t)((input >> 96) & 0xFFFFFFFF);
}

int valid_address(uintptr_t address, int j, int addressesSize)
{
	// Get stack size
	uint64_t stack_size = el3_stack_size + el2_stack_size + el1_stack_size + el0_stack_size;


	if (j >= addressesSize) // no more room
		{
			return 0;
		}

	if (address >=data_start  && address < data_end) // in data
	{
		return 1;
	}

	if (address >=sdata_start  && address < sdata_end) // in sdata
	{
		return 1;
	}

	if (address >=sbss_start  && address < sbss_end) // in sbss
	{
		return 1;
	}

	if (address >=tdata_start  && address < tdata_end) // in tdata
	{
		return 1;
	}

	if (address >=tbss_start  && address < tbss_end) // in tbss
	{
		return 1;
	}

	if (address >=bss_start  && address < bss_end) // in bss
	{
		return 1;
	}

	if (address >=heap_start  && address < heap_end) // in heap
	{
		return 1;
	}

	if (address >=stack_start  && address < (stack_start + stack_size)) // in stack
	{
		return 1;
	}

	return 0; // not valid
}

void print_stack(uintptr_t addresses[], int addressesSize)
{
    // Declare a pointer to an unsigned integer (assuming 4 bytes per word)
    unsigned int *ptr = (unsigned int *)stack_start;

    // Get stack size
    uint64_t stack_size = el3_stack_size + el2_stack_size + el1_stack_size + el0_stack_size;

    // Get stack end pointer
    uintptr_t stack_end = stack_start + stack_size;

    // Get iterator for addresses
    int j = get_index(addresses, addressesSize);

    // Iterate through the stack memory and print each value
    while ((uintptr_t)ptr < stack_end) {
        // Print the value at the current memory location
    	xil_printf("Address:0x%08x,Value:0x%08x\n",(uint32_t) ptr, *ptr);
		//xil_printf("Address:0x");
		//xil_printf("%08x",(uint32_t) ptr);
		//xil_printf(",Value:0x");
		//xil_printf("%08x\n", *ptr);



        if (valid_address(*ptr, j, addressesSize))
        {
        	addresses[j] = *ptr;
        	j++;
        }

        ptr++;
    }
}


void print_x_sp_pc_registers(uintptr_t addresses[], int addressesSize)
{

	// Get iterator for addresses
	int j = get_index(addresses, addressesSize);

	// Print register values along with their names
	for (int i = 0; i < 32; ++i) {

		if (i == 31){
			uint64_t input = registers[i];
			uint32_t high, low;

			// Split the input value into high and low parts
			split_uint64(input, &high, &low);

			xil_printf("PC:0x%08x%08x\n", high, low);
			//xil_printf("PC:0x");
			//xil_printf("%08x", high);
			//xil_printf("%08x\n", low);
		}

		else{
			uint64_t input = registers[i];
			uint32_t high, low;

			// Split the input value into high and low parts
			split_uint64(input, &high, &low);

			xil_printf("r%d:0x%08x%08x\n", i, high, low);
			//xil_printf("r%d:0x", i);
			//xil_printf("%08x", high);
			//xil_printf("%08x\n", low);
		}

		if (valid_address(registers[i], j, addressesSize))
		{
			addresses[j] = registers[i];
			j++;
		}
	}

	// Print SP register from x29
	uint64_t input = registers[29];
	uint32_t high, low;

	// Split the input value into high and low parts
	split_uint64(input, &high, &low);
	xil_printf("SP:0x%08x%08x\n", high, low);
	//xil_printf("SP:0x");
	//xil_printf("%08x", high);
	//xil_printf("%08x\n", low);

}

void print_32_bit_system_registers()
{
	// Allocate memory for register values
	uint32_t register_values[43];

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
    		"CNTPS_TVAL_EL1"

    };

	// Call the assembly function and pass the array's pointer
	get_32register_values(register_values);

	// Print register values along with their names
	for (int i = 0; i < 43; i++) {
		xil_printf("%s:0x%08x\n", register_names[i],register_values[i]);
		//xil_printf("%s:0x", register_names[i]);
		//xil_printf("%08x\n", register_values[i]);
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

    uint32_t addresses[] = {
    	0xf9020000,
		0xf9020004,
		0xf9020008,
        0xf9020014,
        0xf9020018,
        0xf902001c,
        0xf9020028,
        0xf90200d0,
        0xf90200e0,
		0xf9010000,
		0xf9010d00

    };
    for (int i = 0; i < 11; i++) {
    		volatile uint32_t* addr_ptr = (volatile uint32_t*) addresses[i];
    	    uint32_t value = *addr_ptr;
    	    xil_printf("%s:0x%08x\n", register_names[i], value);
    		//xil_printf("%s:0x", register_names[i]);
    		//xil_printf("%08x\n", value);
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

    uint32_t addresses_multiple[] = {
    		0xf9010080,
			0xf9010100,
			0xf9010200,
			0xf9010300,
			0xf9010400,
			0xf9010800,
			0xf9010c00,
			0xf9010d04,
			0xf9010f20
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

    for (int i = 0; i < 9; ++i) {
        		volatile uint32_t* base_addr_ptr = (volatile uint32_t*) addresses_multiple[i];
        		for (int j = 0; j < range[i]; j++) {
        			uint32_t value = *(base_addr_ptr + (j));
        			xil_printf("%sR%d:0x%08x\n", register_names_multiple[i], j, value);
        			//xil_printf("%sR%d:0x", register_names_multiple[i], j);
        			//xil_printf("%08x\n", value);
        		}

            }
}

void print_64_bit_system_registers()
{
	// Allocate memory for register values
	uint64_t register_values[24];

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
			"CNTPS_CTL_EL1",
			"ELR_EL1",
			"ELR_EL2",
			"ELR_EL3"

    };

	// Call the assembly function and pass the array's pointer
	get_64register_values(register_values);

	// Print register values along with their names
	for (int i = 0; i < 24; i++) {
		uint64_t input = register_values[i];
		uint32_t high, low;

		// Split the input value into high and low parts
		split_uint64(input, &high, &low);

		xil_printf("%s:0x%08x%08x\n", register_names[i], high, low);
		//xil_printf("%s:0x", register_names[i]);
		//xil_printf("%08x", high);
		//xil_printf("%08x\n", low);
	}
}

void print_v_registers()
{
	// Allocate memory for register values
	//uint64_t register_values[32][2];
	__int128_t register_values[32];
	get_Vregister_values(register_values);

	for (int i = 0; i < 32; i++){
		__int128_t input = register_values[i];
		uint32_t part1, part2, part3, part4;

		// Split the input value into four 32-bit parts
		split_int128(input, &part1, &part2, &part3, &part4);

		xil_printf("v%d:0x%08x%08x%08x%08x\n", i, part1, part2, part3, part4);
		//xil_printf("v%d:0x", i);
		//xil_printf("%08x", part1);
		//xil_printf("%08x", part2);
		//xil_printf("%08x", part3);
		//xil_printf("%08x\n", part4);
	}
}

void printAddress(uintptr_t address)
{
	for (int i = -RANGE; i <= RANGE; i++)
	{
		uint64_t input = *((uint64_t*)(address + i));
		uint32_t high, low;

		// Split the input value into high and low parts
		split_uint64(input, &high, &low);

		xil_printf("Address:0x%08x,Value:0x%08x%08x\n",(uint32_t) (address + i), high, low);
		//xil_printf("Address:0x");
		//xil_printf("%08x",(uint32_t) (address + i));
		//xil_printf(",Value:0x");
		//xil_printf("%08x", high);
		//xil_printf("%08x\n", low);
	}
}

void print_data(uintptr_t addresses[], int size)
{
	int j = get_index(addresses, size);
	for (int i = 0; i < j; i++)
	{
		if (addresses[i] == 0)
			break;
		xil_printf("Address:0x%08x\n", addresses[i]);
		//xil_printf("Address:0x");
		//xil_printf("%08x\n", addresses[i]);
		//printAddress(addresses[i]);
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
	print_x_sp_pc_registers(addresses, SIZE);
	print_32_bit_system_registers();
	print_gicr_registers();
	print_64_bit_system_registers();
	print_v_registers();
	xil_printf("REGISTER_END\n"); // end stack delimiter
	print_stack(addresses, SIZE);
    xil_printf("STACK_END\n"); // end stack delimiter
	print_data(addresses, SIZE);
	xil_printf("END\n"); // send end signal
	for(;;){
	}
}
