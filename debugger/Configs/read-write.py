import serial
import os
import subprocess

# register groups

registers = {}

read_only = {"FPCR", "FPSR", "MPIDR_EL1", "ISR_EL1", "GICC_RPR", "GICC_HPPIR", "GICC_AHPPIR", "GICD_ITARGETSR0", "GICD_ITARGETSR1", "GICD_ITARGETSR2",
             "GICD_ITARGETSR3", "GICD_ITARGETSR4", "GICD_ITARGETSR5", "GICD_ITARGETSR6","GICD_ITARGETSR7","GICD_ICFGR0", "GICD_ICFGR1", "GICD_PPISR", 
             "GICD_SPISR0", "GICD_SPISR1", "GICD_SPISR2", "GICD_SPISR3", "GICD_SPISR4", "RVBAR_EL3", "CNTVCT_EL0"}

def read_serial(ser):
    received_data = []
    record = False
    print("Waiting for data")
    try:
        while True:
            # Read data from the serial port
            data = ser.readline()
            if data:
                try:
                    decoded_data = data.decode().strip()
                    #print(decoded_data)
                    if (decoded_data == "END"):
                        break
                    if (decoded_data == "START"):
                        print("Saving Data")
                        record = True
                        continue
                    if (record):
                        #print(decoded_data)
                        received_data.append(decoded_data)
                except:
                    continue
                
            # Check for termination condition (e.g., '!')
            #if '!' in data:
                #break
        print("Data saved")
        return received_data

    except KeyboardInterrupt:
        pass
        

def write_output(recieved_data):
    i = 1
    
    f1 = open("../version.txt", "r")
    val = f1.read()
    f2 = open("../archive.txt", "a")
    filename = "../Versions/stack" + val + ".txt"
    f2.write("stack" + val + ".txt")
    
    with open(filename, 'w') as f:
        f.write(recieved_data[0])
        for item in recieved_data[1:]:
            if (item == ""):
                continue
            if (item == "STACK_END"):
                i += 1
                break
            f.write("\n")
            f.write(item)
            i += 1
    
    with open("../registers.txt", 'w') as f:
        f.write(recieved_data[i])
        for item in recieved_data[i+1:]:
            if (item == ""):
                continue
            f.write("\n")
            f.write(item)
            
    f1.close()
            

def read_data():
    # Define the serial port and baud rate
    ser = serial.Serial('COM4', baudrate=115200, timeout=1)
    
    # Read Data
    received_data = read_serial(ser)
    
    if received_data is None:
        return
    
    # Write Data
    write_output(received_data)
    
    # Close connection
    ser.close()

def generate_register_tcl():
    __location__ = os.path.realpath(
    os.path.join(os.getcwd(), os.path.dirname(__file__)))
    f = open(os.path.join(__location__, "../registers.txt"))
    with open ("../write_registers.tcl", 'w') as g:
        g.write("# source ../write_registers.tcl")
        for line in f:
            # Remove leading spaces and newline characters
            line = line.strip()

            # Split the line into words
            words = line.split(":")
            
            # Get register name
            register = words[0]
            
            # Skip readonly
            if register in read_only:
                continue
            
            # Remove numbers except for ELx
            if len(register) <= 3 or (len(register) > 4 and (register[:6] == "GICD_I" or register[:6] == "GICD_S")):
                register = ''.join((x for x in register if not x.isdigit()))
                
            # Write out TCL script
            g.write("\n")
            g.write(f"rwr{registers[register]}{words[0].lower()} {words[1]}")

            
            
    f.close()



def write_data():
    generate_register_tcl()
    # Start xsct.bat with pipes for stdin and stdout
    process = subprocess.Popen([r'C:\Xilinx\Vitis\2023.1\bin\xsct.bat'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    
    # Example: Send multiple commands to xsct
    commands = ["connect", "target 9", "dow C:/Subham/Capstone/Capstone/Debug/Capstone.elf", #Not sure relative path
                "source ../write_registers.tcl"]
                #"source C:/Subham/Test/write_stack.tcl"]
    
    for command in commands:
        print(command)
        process.stdin.write(command + "\n")
        process.stdin.flush()  # Ensure data is written to stdin
    
    # Close stdin to signal that no more input will be provided
    process.stdin.close()

    # Read output from the subprocess
    output, error = process.communicate()

    # Print the output and error
    print("Output:", output)
    print("Error:", error)

    
    
def display_menu():
    print("1. Read data from serial")
    print("2. Write data back to board")
    print("3. Exit")

def process_menu(option):
    match option:
        case "1":
            read_data()
        case "2":
            write_data()
        case "3":
            return False
        case _:
            return True
    return True
    
def write_registers():
    file1 = open('../debugger_registers.txt', 'r')
    lines = file1.readlines()
    
    for line in lines:
        tokens = line.split(":")
        registers[tokens[0]] = tokens[1]

def main():
    # Start Main Menu
    write_registers()
    run = True
    while(run):
        display_menu()
        option = input()
        run = process_menu(option)
    
if __name__ == "__main__":
    main()