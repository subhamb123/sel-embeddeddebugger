#ifndef SNAPSHOT_H
#define SNAPSHOT_H

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
/* Xilinx includes. */
#include "xil_printf.h"
#include "xparameters.h"

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

// section type for data dump

// Define an enumerated type with 8 types
enum section {
    DATA,
    SDATA,
    SBSS,
    TDATA,
    TBSS,
    BSS,
    HEAP,
    STACK,
	INVALID
};


extern void freertos_exception_startup(void);

#define SIZE 20                       // Size of addresses array
#define RANGE 30                      // Range of addresses

void print_tasks();
void print_task_stack(long unsigned int base);
void split_uint64(uint64_t input, uint32_t *high, uint32_t *low);
void split_int128(__int128_t input, uint32_t *part1, uint32_t *part2, uint32_t *part3, uint32_t *part4);
void printStack(uintptr_t addresses[], enum section type[], int addressesSize);
enum section valid_address(uintptr_t address, int j, int addressesSize);
void print_x_sp_pc_registers(uintptr_t addresses[], enum section type[], int addressesSize);
void print32BitSystemRegisters();
void printGICRRegisters();
void print64BitSystemRegisters();
void printVRegisters();
void printAddress(uintptr_t address, int i, enum section sec);
void print_data(uintptr_t addresses[], enum section type[], int size);
int get_index(uintptr_t addresses[], int size);
void get_range(uint32_t address, enum section sec, int *low, int *high);
void exception_handler();

#endif
