#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "xil_printf.h"

extern uintptr_t baseAddress;  // Declaration of baseAddress
extern size_t size;            // Declaration of size
extern void (*synchronous_interrupt_handler)(void);

#define SIZE 20                       // Size of addresses array
#define RANGE 30                      // Range of addresses
#define LOW 0x0000000000000000      // Lowest Valid Address
#define HIGH 0x0003c4fb                // Highest Valid Address

void set_exception_vector_table_entry(void* table_entry_address, uint32_t branch_instruction);
void start_up();
void printStack(uintptr_t baseAddress, size_t size, uintptr_t addresses[], int addressesSize);
void printXRegisters(uintptr_t addresses[], int addressesSize);
void print32BitSystemRegisters();
void printGICRRegisters();
void print64BitSystemRegisters();
void printVRegisters();
void printSPRegister(uintptr_t addresses[], int addressesSize);
void printAddress(uintptr_t address);
int validAddress(uintptr_t address);
void print_data(uintptr_t addresses[], int size);
void exception_handler();

#endif
