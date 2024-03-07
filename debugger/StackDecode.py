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


def symbolLookup(symbolTable, exceptionAddress):
    for entry in symbolTable:
        address = entry['Address']
        size = entry['Size']
        #entry_address_decimal = address#int(address, 16)

        if exceptionAddress >= address and exceptionAddress < address + size:
            funtionReference = {'functionName': entry['Name'], 'Address': address}
            # traceStack.append({'FunctionName': entry['Name'], 'Address': address})

    return funtionReference


def stackLookup(stackData, addressRef):
    for address, value in stackData:
        if address == addressRef:
            return value
    return None


def registerLookup(registerData, registerName):
    for register, value in registerData:
        if register == registerName:
            return value
    return None


def traceStack(registers, dataStack, symbolTable):

    traceStack = []

    # 1. Record the value in the exception link register as the faulted program counter.
    # Exception link register is ELR_EL3 (check)
    exceptionRegEL3 = registerLookup(registers, 'ELR_EL3')  # Finds address 0xE28
    #exceptionRegEL2 = registerLookup(registers, 'ELR_EL2')
    #exceptionRegEL1 = registerLookup(registers, 'ELR_EL1')

    exceptionRegDecimal = int(exceptionRegEL3, 16)  # ELR_EL3 is E28, which is within bar, which calls foo
    funtionReference = symbolLookup(symbolTable, exceptionRegDecimal)
    traceStack.append(funtionReference)

    # 2. Record the value in x30 as the current function’s return program counter.
    retPC = registerLookup(registers, 'r30')

    # 3. Record the program counter associated with the previous stack frame using: program_counter = *(x29 + 8 bytes)
    reg29 = registerLookup(registers, 'r29')    
    reg29 = int(reg29, 16)
    prevProgramCounter = reg29 + 0x8   

    functRef = stackLookup(dataStack, prevProgramCounter)

    # Continue tracing stack until a stack value '0' is hit
    while stackLookup(dataStack, reg29) != 0:
        functRef = symbolLookup(symbolTable, functRef)
        traceStack.append(functRef)
        reg29 = stackLookup(dataStack, reg29)  
        prevProgramCounter = reg29 + 8                  
        functRef = stackLookup(dataStack, prevProgramCounter)

    return traceStack


def printTraceStack(traceStack):
    print("Trace Stack:")
    for stackEntry in traceStack:
        functionName = stackEntry.get('functionName', 'Unknown')
        address = stackEntry.get('Address', 'Unknown')
        print(f"{functionName} (0x{address:08X})")
        

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
    # Initialize empty list for symbolTable
    SymbolTable = []

    try:
        with open(filePath, 'r') as file:
            for line in file:
                # Split the line into columns using whitespace
                columns = line.strip().split()

                # Check if line has 6 entries (valid entry)
                if len(columns) == 6:
                    # Convert hexadecimal strings to decimal integers for easier comparison
                    address_decimal = int(columns[0], 16)
                    size_decimal = int(columns[4], 16)
                    # Create a dictionary for each line and append it to the SymbolTable
                    symbol_entry = {
                        'Address': address_decimal,
                        'Type': columns[1],         # Can probably be removed
                        'Binding': columns[2],      # Can probably be removed
                        'Section': columns[3],      # Can probably be removed
                        'Size': size_decimal,
                        'Name': columns[5]
                    }
                    SymbolTable.append(symbol_entry)
                else:
                    pass
                    #print(f"Skipping invalid line: {line}") # Print the invalid line for debugging

    except FileNotFoundError:
        print(f"Error: File not found - {filePath}")
    except Exception as e:
        print(f"Error: {e}")

    return SymbolTable


def main():
    stackData = readStackFromFile('stack.txt')
    symbolTable = readSymbolsFromFile('symbolTable.txt')    # Symbol table file is generated by other script using .elf file, see extractSymbolTable.py
    registerData = readRegistersFromFile('registers.txt')

    tracedStack = traceStack(registerData, stackData, symbolTable)
    printTraceStack(tracedStack)


if __name__ == "__main__":
    main()
