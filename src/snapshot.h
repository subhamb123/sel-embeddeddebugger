#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "xil_printf.h"

extern uint64_t registers[31]; // Declaration of registers array

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

void printStack(uintptr_t baseAddress, size_t size, uintptr_t addresses[], int addressesSize);
int valid_address(uintptr_t address, int j, int addressesSize);
void printXRegisters(uintptr_t addresses[], int addressesSize);
void print32BitSystemRegisters();
void printGICRRegisters();
void print64BitSystemRegisters();
void printVRegisters();
void printSPRegister(uintptr_t addresses[], int addressesSize);
void printAddress(uintptr_t address);
void print_data(uintptr_t addresses[], int size);
int get_index(uintptr_t addresses[], int size);
void exception_handler();

#endif
