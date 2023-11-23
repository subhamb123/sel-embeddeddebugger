# source source C:/Users/deoch/Documents/WSU/CPTS_421/sel-embeddeddebugger/debugger/read_stack.tcl
# Set the base address and size of the stack memory region
set STACK_BASE_ADDRESS 0x0000c0c0
set STACK_SIZE 0xC00

# Read stack memory from the board
proc readStackMemory {baseAddress size} {
    # Use the mrd command to read memory in XSCT
    set stackData [mrd $baseAddress $size]
    return $stackData
}

# Read stack memory data
set stackMemoryData [readStackMemory $STACK_BASE_ADDRESS $STACK_SIZE]

# Print the stack memory data
puts "Stack Memory Data:"
puts $stackMemoryData