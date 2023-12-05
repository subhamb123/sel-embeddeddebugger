# Directories are currently hard coded.
# Double check all directories before running.

import struct
import subprocess
import re


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

    # Stand in for stack data - needs to be replaced with actual stack data.
    f = open("option.txt", "r")
    f2 = open("version.txt", "r")
    if int(f.read()) == 1:
        stackData = readStackFromFile('./Versions/stack' + f2.read() + '.txt')
    else:
        with open("archive.txt", "r") as f3:
            lines = f3.readlines()
            i = 0
            for line in lines:
                i += 1
                print(str(i) + ". " + line + "\n")
                
            choice = input("\nYour choice: ")
            stackData = readStackFromFile("./Versions/" + lines[int(choice)-1])
    
    symbolTable = readSymbolsFromFile('symbolTable.txt')

    # The starting address of the program
    # Modify if starting address changes - or create method to have it not matter.
    startAddress = 0xc0c0

    decodedStack = decodeStack(stackData, symbolTable, startAddress)

    # Print the stacks to files
    with open('decoded.txt', 'w') as outputFile:
        for address, functionName in decodedStack:
            outputFile.write(f"Address: 0x{address:08X}, Function: {functionName}\n")

    
    # File with (function:none) addresses excluded.
    with open('decoded-functions.txt', 'w') as functionsFile:
        for address, functionName in decodedFunctions:
            functionsFile.write(f"Address: 0x{address:08X}, Function: {functionName}\n")
            
    f.close()
    f2.close()



if __name__ == "__main__":
    main()
