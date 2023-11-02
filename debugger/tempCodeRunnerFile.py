import serial

# Define the serial port and baud rate
ser = serial.Serial('COM7', baudrate=112500, timeout=1)


def read_stack():
    stack = []
    try:
        while True:
            # Read data from the serial port
            data = ser.readline().decode('utf-8').strip()
            
            # Check for termination condition (e.g., '!')
            if '!' in data:
                break
            
            # Print the received data
            #print(data)                   
            stack.append(data)
        return stack

    except KeyboardInterrupt:
            pass

def read_registers():
    registers = []
    try:
        while True:
            # Read data from the serial port
            data = ser.readline().decode('utf-8').strip()
            
            # Check for termination condition (e.g., '!')
            if '!' in data:
                break
            
            # Print the received data
            #print(data)
                
            registers.append(data)
            

        return registers

    except KeyboardInterrupt:
        pass

def write_stack(stack):
    with open("stack.txt", 'w') as f:
        for item in stack:
            addresses = item.split("|")
            for address in addresses:
                f.write(address)
                f.write("\n")

def write_registers(registers):
    with open("registers.txt", 'w') as f:
        for item in registers:
            values = item.split("|")
            for value in values:
                f.write(value)
                f.write("\n")
            

def main():
    stack = read_stack()
    registers = read_registers()
    
    # remove empty strings
    stack = [i for i in stack if i]
    registers = [i for i in registers if i]
    
    
    print(stack)
    print("Stack Length: " + str(len(stack)))
    print("\n\n\n\n")
    print(registers)
    print("Register Length: " + str(len(registers)))
    print("\n\n")
    
    write_stack(stack)
    write_registers(registers)
    ser.close()
    
if __name__ == "__main__":
    main()