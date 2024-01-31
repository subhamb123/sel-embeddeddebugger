# Open the file for reading
set file [open "C:/Users/deoch/Documents/sel-embeddeddebugger/debugger/stack.txt" r]

# Create List

set values {}
# Read each line from the file
while {[gets $file line] != -1} {
    # Use regular expressions to extract address and value
    if {[regexp {Address:0x[0-9A-Fa-f]+,Value:0x([0-9A-Fa-f]+)} $line match valueHex]} {
        # Convert hex strings to integers
        set valueInt [scan $valueHex %x]
        lappend values $valueInt

    } else {
        puts "Error: Invalid line format - $line"
    }
}

mwr 0x0000c0c0 $values
        