import unittest
def get_registers_expected():
    registers_expected = {}
    with open ("registers_expected.txt", 'r') as f:
        for line in f:
            # Remove leading spaces and newline characters
            line = line.strip()

            if not line:
                continue 

            # Split the line into words
            words = line.split(":")
            # store name and value
            registers_expected[words[0].upper()] = "0x" + words[1].upper().strip()
    return registers_expected

def get_stack_expected():
    stack_expected = {}
    with open ("stack_expected.txt", 'r') as f:
        for line in f:
            # Remove leading spaces and newline characters
            line = line.strip()

            # Split the line into words
            # Splitting the string by comma to separate address and value
            words = line.split(':')

            # store name and value
            stack_expected[words[0]] = words[1]
    return stack_expected

def get_registers_actual():
    registers_actual = {}
    with open ("registers.txt", 'r') as f:
        for line in f:
            # Remove leading spaces and newline characters
            line = line.strip()

            # Split the line into words
            words = line.split(":")
            
            # store name and value
            registers_actual[words[0].upper()] = words[1]
    return registers_actual

def get_stack_actual():
    stack_actual = {}
    with open ("stack.txt", 'r') as f:
        for line in f:
            # Remove leading spaces and newline characters
            line = line.strip()

            # Split the line into words
            # Splitting the string by comma to separate address and value
            address_value = line.split(',')
            # Extracting address and value from the split string
            address = address_value[0].split(':')[1]
            value = address_value[1].split(':')[1]
            
            # store name and value
            stack_actual[address] = value
    return stack_actual


def main():
    registers_expected = get_registers_expected()
    stack_expected =get_stack_expected()

    registers_actual = get_registers_actual()
    stack_actual = get_stack_actual()

    registers_actual.pop("RVBAR_EL3")
    registers_actual.pop("CNTVCT_EL0")

    for key in registers_actual.keys():
        if registers_expected[key] != registers_actual[key]:
            pass
            print(key, registers_actual[key], registers_expected[key])

    for key in stack_expected.keys():
        print(key, stack_expected[key])

if __name__ == "__main__":
    main()