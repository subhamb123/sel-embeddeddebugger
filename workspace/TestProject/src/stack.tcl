# source C:/Users/deoch/workspace/TestProject/src/stack.tcl
# Set the base address and size of the stack memory region
set STACK_BASE_ADDRESS 0x0000c0c0
set STACK_SIZE 0x2000

# Read stack memory from the board
proc readStackMemory {baseAddress size} {
    # Use the mrd command to read memory in XSCT
    set stackData [mrd $baseAddress $size]
    return $stackData
}

# Read stack memory data
set stackMemoryData [readStackMemory $STACK_BASE_ADDRESS $STACK_SIZE]

# Print the stack memory data
#puts "Stack Memory Data:"
#puts $stackMemoryData

# Make a dictionary to map functions to addresses
set symbolTable [dict create 00000D00 main 00000D98 add 00000DBC divide]

proc decodeCallStack {stackAddresses symbolTable} {
    foreach row $stackAddresses {
    
    # Split into fields on colons
	set fields [split $row ":"]
	
	# Assign fields to variables and print some out...
	lassign $fields \
		number address
	
	set stripped [string map {" " ""} $address]		
		
	if {[dict exists $symbolTable $stripped]} {
	    set functionName [dict get $symbolTable $stripped]
	} else {
	    set functionName "UnknownFunction"
	}
    
    puts "$row -> Function: $functionName"
        
    }
}

# Split the stack memory data into individual addresses
set stackAddresses [split $stackMemoryData "\n"]

# Decode and display the call stack
decodeCallStack $stackAddresses $symbolTable