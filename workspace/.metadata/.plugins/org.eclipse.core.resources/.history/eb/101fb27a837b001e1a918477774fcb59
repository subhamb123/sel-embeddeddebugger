#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "xil_printf.h"

extern uintptr_t baseAddress;  // Declaration of baseAddress
extern size_t size;            // Declaration of size
extern void (*synchronous_interrupt_handler)(void);

void set_exception_vector_table_entry(void* table_entry_address, uint32_t branch_instruction);
void start_up();
void printStack(uintptr_t baseAddress, size_t size);
void printXRegisters();
void print32BitSystemRegisters();
void printGICRRegisters();
void print64BitSystemRegisters();
void printVRegisters();
void printSPRegister();
void exception_handler();

#endif
