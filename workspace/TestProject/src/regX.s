.section .text
.global get_Xregister_values

get_Xregister_values:
	MOV x1, x0              // Load the address of the destination array into x1

    STR x2, [x1, #0]
	STR x3, [x1, #8]
	STR x4, [x1, #16]
	STR x5, [x1, #24]
	STR x6, [x1, #32]
	STR x7, [x1, #40]
	STR x8, [x1, #48]
	STR x9, [x1, #56]
	STR x10, [x1, #64]
	STR x11, [x1, #72]
	STR x12, [x1, #80]
	STR x13, [x1, #88]
	STR x14, [x1, #96]
	STR x15, [x1, #104]
	STR x16, [x1, #112]
	STR x17, [x1, #120]
	STR x18, [x1, #128]
	STR x19, [x1, #136]
	STR x20, [x1, #144]
	STR x21, [x1, #152]
	STR x22, [x1, #160]
	STR x23, [x1, #168]
	STR x24, [x1, #176]
	STR x25, [x1, #184]
	STR x26, [x1, #192]
	STR x27, [x1, #200]
	STR x28, [x1, #208]
	STR x29, [x1, #216]
	STR x30, [x1, #224]

	RET
