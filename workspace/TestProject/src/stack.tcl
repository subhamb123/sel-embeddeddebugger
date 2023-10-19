# Set the base address and size of the stack memory region
set STACK_BASE_ADDRESS 0x0000b0c0
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
set symbolTable [dict create 00000d00 main 00000d50 valid 00000d74 invalid]

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
	    puts found
	} else {
	    set functionName "UnknownFunction"
	}
    
    puts "address: $stripped -> Function: $functionName"
        
    }
}

# Decode and display the call stack
decodeCallStack $stackAddresses $symbolTable