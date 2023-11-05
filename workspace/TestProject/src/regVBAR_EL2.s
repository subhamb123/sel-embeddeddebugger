.global get_vbar_el1_register_value

.macro MRS_REG reg_name, dest
    MRS \dest, \reg_name
.endm

get_vbar_el1_register_value:
	MRS_REG VBAR_EL1, x0
	RET
