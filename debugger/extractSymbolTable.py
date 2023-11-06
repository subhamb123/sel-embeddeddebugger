import subprocess

def extractSymbolsFromElf(elfPath, objdumpPath, outputFilePath):
    try:
        # Run objdump tool to extract symbols from the ELF file
        command = [objdumpPath, '-t', elfPath]
        symbol_table_output = subprocess.check_output(command, stderr=subprocess.STDOUT, text=True)

        # Skip the first four lines of the symbol table output
        symbol_table_lines = symbol_table_output.splitlines()[4:]

        # Write the modified symbol table output to the specified file
        with open(outputFilePath, 'w') as outputFile:
            outputFile.write('\n'.join(symbol_table_lines))
        
        print(f"Symbols extracted and saved to {outputFilePath}")
    except subprocess.CalledProcessError as e:
        print(f"Error occurred: {e.output}")
        print("Failed to extract symbols.")

# Path to the ELF file and objdump tool
elfPath = r"C:\\projects\\sel-debugger\\SELDebugger\\Debug\\SELDebugger.elf"
objdumpPath = r"C:\Xilinx\Vitis\2023.1\gnu\aarch64\nt\aarch64-none\bin\aarch64-none-elf-objdump.exe"
outputFilePath = "symbolTable.txt"

# Extract symbols from the ELF file
extractSymbolsFromElf(elfPath, objdumpPath, outputFilePath)
