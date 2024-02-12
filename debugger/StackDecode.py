# Directories are currently hard coded.
# Double check all directories before running.

import struct
import subprocess
import re

'''
Here is a checklist of requirements need to implement the stack decoder:

    The code on the SOM must be compiled with the -mno-omit-leaf-frame-pointer to force the compiler to generate stack frames for all function calls.
    The parser must have access to the .elf file that was running on the SOM when the snapshot data was generated.
    The parser must have access to the stack data and the values of x29, x30, and the exception link register (ELR_EL1/ELR_EL2/ELR_EL3). These values should be included in the snapshot data.
        X29 will be the head of the linked list of stack frames
        X30 will be the return program counter for the function where the exception/snapshot occurred
        The exception link register will contain the program counter where the exception/snapshot occurred. 

The steps below can be used to implement the parser. For every program counter we find in the call stack, we can use the .elf file to determine which C function the address is associated with.

    0. Verify the above requirements are met
    1. Record the value in the exception link register as the faulted program counter.
    2. Record the value in x30 as the current function’s return program counter.
    3. Record the program counter associated with the previous stack frame using: program_counter = *(x29 + 8 bytes)
    4. Evaluate x29 = *(x29) to make x29 point to the previous frame pointer
    5. Record the program counter associated with the previous stack frame using: program_counter = *(x29 + 8 bytes)
    6. Loop back to step 5 until all stack frames are processed
'''

def traceStack(registers, dataStack):

    traceStack = []

    # 1. Record the value in the exception link register as the faulted program counter.
    # Exception link register is ELR_ELI3 (check)
    exceptionReg = None
    for register, value in registers:
        if register == 'ELR_ELI3':
            exceptionReg = value
            break
    traceStack.append(exceptionReg)

    # 2. Record the value in x30 as the current function’s return program counter.
    # X30 register is ELR_ELI2 (check)
    regX30 = None
    for register, value in registers:
        if register == 'ELR_ELI2':
            regX30 = value
            break
    traceStack.append(regX30)
    
    # 3. Record the program counter associated with the previous stack frame using: program_counter = *(x29 + 8 bytes)
    prevProgramCounter = None
    for register, value in registers:
        if register == 'ELR_ELI1':
            prevProgramCounter = value
            break
    traceStack.append(prevProgramCounter)

    # 4. Evaluate x29 = *(x29) to make x29 point to the previous frame pointer
    regX29Offset = int(prevProgramCounter, 16) + 0x8
    x29Value = None
    if prevProgramCounter is not None:
        for address, value in dataStack:
            if address == regX29Offset:
                x29Value = value
                break
        if x29Value is not None:
            traceStack.append(hex(x29Value))


    # 5. Record the program counter associated with the previous stack frame using: program_counter = *(x29 + 8 bytes)
    while x29Value is not None:
        regX29Offset = int(x29Value, 16) + 0x8
        x29Value = None
        for address, value in dataStack:
            if address == regX29Offset:
                x29Value = value
                break
        
        if x29Value is not None:
            traceStack.append(hex(x29Value))

    return traceStack


def readRegistersFromFile(filepath):
    registerList = []
    
    with open(filepath, 'r') as file:
        for line in file:
            if ":" in line:
                register, value = line.strip().split(':')
                register = register.strip()
                value = value.strip()
                registerList.append((register, value))
    return registerList




def readStackFromFile(filePath):
    stackData = []
    with open(filePath, 'r') as file:
        for line in file:
            if line.startswith("Address:") and "Value:" in line:
                addressValue = line.strip().replace('Address:', '').replace('Value:', '').split(',')
                address = int(addressValue[0].strip(), 16)
                value = int(addressValue[1].strip(), 16)
                stackData.append((address, value))
    return stackData


def readSymbolsFromFile(filePath):
    symbolTable = []
    with open(filePath, 'r') as file:
        lines = file.readlines()
        for line in lines:
            match = re.match(r'^\s*([0-9a-fA-F]+)\s+[glld]\s+.+\s+(\w+)$', line)
            if match:
                address = int(match.group(1), 16)
                symbol = match.group(2)
                symbolTable.append((address, symbol))
    return symbolTable


def main():
    stackData = readStackFromFile('./Versions/stack.txt')
    symbolTable = readSymbolsFromFile('symbolTable.txt')
    registerData = readRegistersFromFile('registers.txt')

    tracedStack = traceStack(registerData, stackData)
    # The starting address of the program
    # Modify if starting address changes - or create method to have it not matter.
    # startAddress = 0xc0c0

    # decodedStack = decodeStack(stackData, symbolTable, startAddress)

    # # Print the stacks to files
    # with open('decoded.txt', 'w') as outputFile:
    #     for address, functionName in decodedStack:
    #         outputFile.write(f"Address: 0x{address:08X}, Function: {functionName}\n")


if __name__ == "__main__":
    main()
