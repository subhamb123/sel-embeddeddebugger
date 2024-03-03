.section .text
.global get_Vregister_values

get_Vregister_values:
	MOV x1, x0              // Load the address of the destination array into x1

    MOV x0, v0.d[0]
	STR x0, [x1, #0]

	MOV x0, v0.d[1]
	STR x0, [x1, #8]

	MOV x0, v1.d[0]
	STR x0, [x1, #16]

	MOV x0, v1.d[1]
	STR x0, [x1, #24]

	MOV x0, v2.d[0]
	STR x0, [x1, #32]

	MOV x0, v2.d[1]
	STR x0, [x1, #40]

	MOV x0, v3.d[0]
	STR x0, [x1, #48]

	MOV x0, v3.d[1]
	STR x0, [x1, #56]

	MOV x0, v4.d[0]
	STR x0, [x1, #64]

	MOV x0, v4.d[1]
	STR x0, [x1, #72]

	MOV x0, v5.d[0]
	STR x0, [x1, #80]

	MOV x0, v5.d[1]
	STR x0, [x1, #88]

	MOV x0, v6.d[0]
	STR x0, [x1, #96]

	MOV x0, v6.d[1]
	STR x0, [x1, #104]

	MOV x0, v7.d[0]
	STR x0, [x1, #112]

	MOV x0, v7.d[1]
	STR x0, [x1, #120]

	MOV x0, v8.d[0]
	STR x0, [x1, #128]

	MOV x0, v8.d[1]
	STR x0, [x1, #136]

	MOV x0, v9.d[0]
	STR x0, [x1, #144]

	MOV x0, v9.d[1]
	STR x0, [x1, #152]

	MOV x0, v10.d[0]
	STR x0, [x1, #160]

	MOV x0, v10.d[1]
	STR x0, [x1, #168]

	MOV x0, v11.d[0]
	STR x0, [x1, #176]

	MOV x0, v11.d[1]
	STR x0, [x1, #184]

	MOV x0, v12.d[0]
	STR x0, [x1, #192]

	MOV x0, v12.d[1]
	STR x0, [x1, #200]

	MOV x0, v13.d[0]
	STR x0, [x1, #208]

	MOV x0, v13.d[1]
	STR x0, [x1, #216]

	MOV x0, v14.d[0]
	STR x0, [x1, #224]

	MOV x0, v14.d[1]
	STR x0, [x1, #232]

	MOV x0, v15.d[0]
	STR x0, [x1, #240]

	MOV x0, v15.d[1]
	STR x0, [x1, #248]

	MOV x0, v16.d[0]
	STR x0, [x1, #256]

	MOV x0, v16.d[1]
	STR x0, [x1, #264]

	MOV x0, v17.d[0]
	STR x0, [x1, #272]

	MOV x0, v17.d[1]
	STR x0, [x1, #280]

	MOV x0, v18.d[0]
	STR x0, [x1, #288]

	MOV x0, v18.d[1]
	STR x0, [x1, #296]

	MOV x0, v19.d[0]
	STR x0, [x1, #304]

	MOV x0, v19.d[1]
	STR x0, [x1, #312]

	MOV x0, v20.d[0]
	STR x0, [x1, #320]

	MOV x0, v20.d[1]
	STR x0, [x1, #328]

	MOV x0, v21.d[0]
	STR x0, [x1, #336]

	MOV x0, v21.d[1]
	STR x0, [x1, #344]

	MOV x0, v22.d[0]
	STR x0, [x1, #352]

	MOV x0, v22.d[1]
	STR x0, [x1, #360]

	MOV x0, v23.d[0]
	STR x0, [x1, #368]

	MOV x0, v23.d[1]
	STR x0, [x1, #376]

	MOV x0, v24.d[0]
	STR x0, [x1, #384]

	MOV x0, v24.d[1]
	STR x0, [x1, #392]

	MOV x0, v25.d[0]
	STR x0, [x1, #400]

	MOV x0, v25.d[1]
	STR x0, [x1, #408]

	MOV x0, v26.d[0]
	STR x0, [x1, #416]

	MOV x0, v26.d[1]
	STR x0, [x1, #424]

	MOV x0, v27.d[0]
	STR x0, [x1, #432]

	MOV x0, v27.d[1]
	STR x0, [x1, #440]

	MOV x0, v28.d[0]
	STR x0, [x1, #448]

	MOV x0, v28.d[1]
	STR x0, [x1, #456]

	MOV x0, v29.d[0]
	STR x0, [x1, #464]

	MOV x0, v29.d[1]
	STR x0, [x1, #472]

	MOV x0, v30.d[0]
	STR x0, [x1, #480]

	MOV x0, v30.d[1]
	STR x0, [x1, #488]

	MOV x0, v31.d[0]
	STR x0, [x1, #496]

	MOV x0, v31.d[1]
	STR x0, [x1, #504]



	RET
