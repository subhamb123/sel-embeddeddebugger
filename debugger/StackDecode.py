# Directories are currently hard coded.
# Double check all directories before running.

import struct
import subprocess
import re

def createCallStack(decodedStack):
    callStack = []
    for address, functionName in reversed(decodedStack):
        callStack.append(functionName)
    return callStack


def decodeStack(stackData, symbolTable, startAddress):
    decodedStack = []
    for address, value in stackData:
        # Skip addresses that are below the start address
        if address < startAddress:
            continue
      # Find the symbol that corresponds to the address
        for symbolAddress, symbolName in symbolTable:
            if address == symbolAddress:
                decodedStack.append((address, symbolName))
    return decodedStack


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
    stackData = readStackFromFile('stack.txt')
    symbolTable = readSymbolsFromFile('symbolTable.txt')

    # The starting address of the program
    # Modify if starting address changes - or create method to have it not matter.
    startAddress = 0xc0c0

    decodedStack = decodeStack(stackData, symbolTable, startAddress)

    # Print the stacks to files
    with open('decoded.txt', 'w') as outputFile:
        for address, functionName in decodedStack:
            outputFile.write(f"Address: 0x{address:08X}, Function: {functionName}\n")

    callStack = createCallStack(decodedStack)

    # Print the call stack to a file
    with open('callStack.txt', 'w') as outputFile:
       for functionName in callStack:
           outputFile.write(f"{functionName}\n")


if __name__ == "__main__":
    main()
