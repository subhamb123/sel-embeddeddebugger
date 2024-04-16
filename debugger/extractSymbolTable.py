import subprocess


def extractSymbolsFromElf(elfPath, objdumpPath, outputFilePath):
    try:
        # Run objdump tool to extract symbols from the ELF file
        command = [objdumpPath, '-t', elfPath]
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

        if result.returncode == 0:
            # Skip the first four lines of the symbol table output
            symbol_table_lines = result.stdout.splitlines()[4:]

            # Write the modified symbol table output to the specified file
            with open(outputFilePath, 'w', encoding='utf-8') as outputFile:
                outputFile.write('\n'.join(symbol_table_lines))

            print(f"Symbols extracted and saved to {outputFilePath}")
        else:
            print(f"Error occurred: {result.stderr}")
            print("Failed to extract symbols.")
    except Exception as e:
        print(f"Error occurred: {e}")
        print("Failed to extract symbols.")


# Path to the ELF file and objdump tool
elfPath = r"C:\projects\sel-debugger-mar24\freertos\Debug\freertos.elf"
# elfPath = r"C:\projects\sel-debugger-new\kv260_ispMipiRx_vcu_DP\export\kv260_ispMipiRx_vcu_DP\sw\kv260_ispMipiRx_vcu_DP\boot\fsbl.elf"
objdumpPath = r"C:\Xilinx\Vitis\2023.1\gnu\aarch64\nt\aarch64-none\bin\aarch64-none-elf-objdump.exe"
outputFilePath = "symbolTable.txt"


# Extract symbols from the ELF file
extractSymbolsFromElf(elfPath, objdumpPath, outputFilePath)
