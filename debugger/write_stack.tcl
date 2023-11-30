# source C:/Users/deoch/Documents/WSU/CPTS_421/sel-embeddeddebugger/debugger/write_stack.tcl

# Open the file for reading
set file [open "C:/Users/deoch/Documents/WSU/CPTS_421/sel-embeddeddebugger/debugger/stack.txt" r]

# Read each line from the file
while {[gets $file line] != -1} {
    # Use regular expressions to extract address and value
    if {[regexp {Address:0x([0-9A-Fa-f]+),Value:0x([0-9A-Fa-f]+)} $line - addressHex valueHex]} {
        # Convert hex strings to integers
        set addressInt [scan $addressHex %x]
        set valueInt [scan $valueHex %x]

        mwr $addressInt $valueInt

        # Print the values in hex
        puts "Wrote 0x$valueHex to address 0x$addressHex"
    } else {
        puts "Error: Invalid line format - $line"
    }
}

# Close the file
close $file