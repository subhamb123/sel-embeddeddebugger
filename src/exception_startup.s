.section .text
.global exception_startup
.extern registers

.macro MRS_REG reg_name, dest
    MRS \dest, \reg_name
.endm

exception_startup:
    // Load registers x29 and x30 from the stack
    ldp     x29, x30, [sp], #16
    // Load registers x18 to x2 from the stack
    ldp     x18, x19, [sp], #16
    ldp     x16, x17, [sp], #16
    ldp     x14, x15, [sp], #16
    ldp     x12, x13, [sp], #16
    ldp     x10, x11, [sp], #16
    ldp     x8, x9, [sp], #16
    ldp     x6, x7, [sp], #16
    ldp     x4, x5, [sp], #16
    ldp     x2, x3, [sp], #16

    // Load the address of the external register pointer (registers)
    adrp    x1, registers      // Load the page address of registers into x1
	add     x1, x1, :lo12:registers // Add the low 12 bits of registers address to x1

    // Calculate the memory address for each register and store its value in the corresponding element of the registers array
    stp     x29, x30, [x1, #29*8]    // Write x29 and x30 to registers[29] and registers[30]
    stp     x27, x28, [x1, #27*8]    // not from stack
    stp     x25, x26, [x1, #25*8]    // not from stack
    stp     x23, x24, [x1, #23*8]    // not from stack
    stp     x21, x22, [x1, #21*8]    // not from stack
    str     x20, [x1, #20*8]		 // outlier
    stp     x18, x19, [x1, #18*8]    // Write x18 and x19 to registers[18] and registers[19]
    stp     x16, x17, [x1, #16*8]    // Write x16 and x17 to registers[16] and registers[17]
    stp     x14, x15, [x1, #14*8]    // Write x14 and x15 to registers[14] and registers[15]
    stp     x12, x13, [x1, #12*8]    // Write x12 and x13 to registers[12] and registers[13]
    stp     x10, x11, [x1, #10*8]    // Write x10 and x11 to registers[10] and registers[11]
    stp     x8, x9, [x1, #8*8]       // Write x8 and x9 to registers[8] and registers[9]
    stp     x6, x7, [x1, #6*8]       // Write x6 and x7 to registers[6] and registers[7]
    stp     x4, x5, [x1, #4*8]       // Write x4 and x5 to registers[4] and registers[5]
    stp     x2, x3, [x1, #2*8]       // Write x2 and x3 to registers[2] and registers[3]

    // Move the address of the external register pointer (registers) from x1 to x2
    mov     x2, x1

    // Load registers x29 and x30 from the stack
    ldp     x0, x1, [sp], #16


    // Store x0 and x1 to registers[0] and registers[1] using stp
    stp     x0, x1, [x2]             // Write x0 and x1 to registers[0] and registers[1]

    // Store pc
    MRS_REG ELR_EL3, x0   // Get PC from elr_el3
    str x0, [x2, #31*8]

    // Branch to the exception_handler() function
    adr     x0, exception_handler    // Load the address of exception_handler() into x0
    b       exception_handler        // Branch with link to exception_handler()
