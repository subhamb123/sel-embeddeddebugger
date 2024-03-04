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

# Create List

set values {}
# Read each line from the file
while {[gets $file line] != -1} {
    # Use regular expressions to extract address and value
    if {[regexp {Address:0x([0-9A-Fa-f]+),Value:0x([0-9A-Fa-f]+)} $line - addressHex valueHex]} {
        # Convert hex strings to integers
        set valueInt [scan $valueHex %x]
        lappend values $valueInt

        # If base address is not set, set it to the first address encountered
        if {$base_address eq ""} {
            set addressInt [scan $addressHex %x]
            set base_address $addressInt

        }

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

        