# Open the file for reading

# Open the file for reading
set filename "C:/Users/deoch/Documents/sel-embeddeddebugger/debugger/stack.txt"
set file [open $filename r]
if {[catch {open $filename r} file]} {
    puts "Error: Unable to open file $filename"
    exit 1
}

# Initialize base address
set base_address ""
set values {}

# Create List

# Read the first line from the file separately
if {[gets $file first_line] != -1} {
    # Use regular expression to extract address and value
    if {[regexp {Address:(0x[0-9A-Fa-f]+),Value:(0x[0-9A-Fa-f]+)} $first_line - addressHex valueHex]} {
        lappend values $valueHex
        set base_address $addressHex
    } else {
        puts "Error: Invalid line format - $first_line"
    }
} else {
    puts "Error: Unable to read the first line from the file."
    exit 1
}

# Read each line from the file
while {[gets $file line] != -1} {
    # Use regular expressions to extract address and value
    if {[regexp {Address:(0x[0-9A-Fa-f]+),Value:(0x[0-9A-Fa-f]+)} $line - addressHex valueHex]} {
        lappend values $valueHex

    } else {
        puts "Error: Invalid line format - $line"
    }
}

# Close the file
close $file

# Execute the mwr command with the values
if {$base_address ne ""} {
    mwr $base_address $values
} else {
    puts "Error: No valid addresses found in the file."
}

        