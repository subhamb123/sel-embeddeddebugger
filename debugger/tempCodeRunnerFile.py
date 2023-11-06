import serial

# Define the serial port and baud rate
ser = serial.Serial('COM7', baudrate=112500, timeout=1)
    
def read_serial():
    received_data = []
    record = False
    try:
        while True:
            # Read data from the serial port
            data = ser.readline()
            if data:
                decoded_data = data.decode().strip()
                print(decoded_data)
                if (decoded_data == "!"):
                    break
                if (decoded_data == "|"):
                    record = True
                    continue
                if (record):
                    received_data.append(decoded_data)
                
            # Check for termination condition (e.g., '!')
            #if '!' in data:
                #break
        return received_data

    except KeyboardInterrupt:
        pass
        

def write_output(recieved_data):
    i = 0
    with open("stack.txt", 'w') as f:
        for item in recieved_data:
            if (item == "+"):
                i += 1
                break
            f.write(item)
            f.write("\n")
            i += 1
    
    with open("registers.txt", 'w') as f:
        for item in recieved_data[i:]:
            f.write(item)
            f.write("\n")
            i += 1

def main():
    
    received_data = read_serial()
    write_output(received_data)
    
    #stack = read_stack()
    #registers = read_registers()
    
    # remove empty strings
    #stack = [i for i in stack if i]
    #registers = [i for i in registers if i]
    
    '''
    print(stack)
    print("Stack Length: " + str(len(stack)))
    print("\n\n\n\n")
    print(registers)
    print("Register Length: " + str(len(registers)))
    print("\n\n")
    '''
    
    #write_stack(stack)
    #write_registers(registers)
    ser.close()
    
if __name__ == "__main__":
    main()