# Directories are currently hard coded.
# Double check all directories before running.

import struct
import subprocess

def extract_program_counters(stack_data):
    program_counters = []
    stack_format = 'Q' * (len(stack_data) // struct.calcsize('Q'))
    program_counters = struct.unpack(stack_format, stack_data)
    return program_counters

def extract_function_names(elf_file):
    objdump_output = subprocess.check_output(["C:\\Xilinx\\Vitis\\2023.1\\gnu\\aarch64\\nt\\aarch64-none\\bin\\aarch64-none-elf-objdump.exe", "-t", elf_file])
    function_names = []
    for line in objdump_output.decode('utf-8').splitlines():
        parts = line.split()
        if len(parts) >= 6 and parts[1].lower() == 'f':
            function_names.append(parts[-1])
    return function_names

def map_program_counters_to_functions(program_counters, function_names):
    pc_to_function = {}
    for pc in program_counters:
        for func_name in function_names:
            if func_name.startswith(hex(pc)):
                pc_to_function[pc] = func_name
    return pc_to_function

def main():
    # Stand in for stack data - needs to be replaced with actual stack data.
    stack_data = b'\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00'
    
    # Extract program counters from stack data
    program_counters = extract_program_counters(stack_data)
    print("Program Counters:", program_counters)
    
    # Extract function names from .elf file
    elf_file = "C:\\projects\\sel-debugger\\SEL-Debugger\\Debug\\SEL-Debugger.elf"
    functions = extract_function_names(elf_file)
    print("Function Names:", functions)
    
    # Map program counters to function names
    pc_to_function_mapping = map_program_counters_to_functions(program_counters, functions)
    print("Program Counters to Function Names:", pc_to_function_mapping)

if __name__ == "__main__":
    main()
