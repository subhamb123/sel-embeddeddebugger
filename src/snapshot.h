#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "xil_printf.h"

extern uint64_t registers[32]; 		// Declaration of registers array

extern uint32_t registers32[43];	// Declaration of registers32

extern uint64_t registers64[24]; 	// Declaration of registers64

extern __int128_t registersv[32];	// Declaration of registersv

extern uint32_t registersg[141]; 	// Declaration of registersg

// Linker Symbols
extern const int __data_start;
extern const int __data_end;
extern const int __sdata_start;
extern const int __sdata_end;
extern const int __sbss_start;
extern const int __sbss_end;
extern const int __tdata_start;
extern const int __tdata_end;
extern const int __tbss_start;
extern const int __tbss_end;
extern const int __bss_start__;
extern const int __bss_end__;
extern const int _heap_start;
extern const int _heap_end;
extern const int _el3_stack_end;
extern const int _STACK_SIZE;
extern const int _EL2_STACK_SIZE;
extern const int _EL1_STACK_SIZE;
extern const int _EL0_STACK_SIZE;


extern void exception_startup(void);

#define SIZE 20                       // Size of addresses array
#define RANGE 30                      // Range of addresses

void split_uint64(uint64_t input, uint32_t *high, uint32_t *low);
void split_int128(__int128_t input, uint32_t *part1, uint32_t *part2, uint32_t *part3, uint32_t *part4);
void printStack(uintptr_t baseAddress, size_t size, uintptr_t addresses[], int addressesSize);
int valid_address(uintptr_t address, int j, int addressesSize);
void print_x_sp_pc_registers(uintptr_t addresses[], int addressesSize);
void print32BitSystemRegisters();
void printGICRRegisters();
void print64BitSystemRegisters();
void printVRegisters();
void printAddress(uintptr_t address);
void print_data(uintptr_t addresses[], int size);
int get_index(uintptr_t addresses[], int size);
void exception_handler();

#endif
