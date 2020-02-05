; file firlib\src\fir_sp_asm_softPipeline.s
; brief FIR filtering function in C6600 assembler with software 
; pipelining optimizations(single precision IEEE754)
; author 
; date 

PROLOG_LENGTH .equ	1
	
	.global fir_sp_asm_softPipeline

fir_sp_asm_softPipeline:
				; user code
				MV		.L2		A8,B0
				
fir_sp_asm_l1:
				
				ZERO	.L1		A5
				MV		.L1 	B6,A1
				MV		.L1		A4,A19
			||	MV		.L2 	B4,B19
				

fir_sp_asm_l2:
				
				LDW		.D1		*A19++,A9
			||	LDW		.D2 	*B19++,B9
				NOP				4
				
				LDW		.D1		*A19++,A9
			||	LDW		.D2 	*B19++,B9
			||	MPYSP	.M1x 	A9,B9,A17
				NOP				4
kernel:			
		[A1]	FADDSP 	.L1 	A17,A5,A5 ;we call the condiation on A1 to prevent useless multiplication
	||	[A1]	LDW		.D1		*A19++,A9
	||	[A1]	LDW		.D2 	*B19++,B9
	||	[A1]	MPYSP	.M1x 	A9,B9,A17
	||	[A1]	BDEC	.S1		kernel,A1
				NOP				5
				
				MPYSP	.M1x 	A9,B9,A17
			||  FADDSP 	.L1 	A17,A5,A5
				NOP 3
				
				FADDSP 	.L1 	A17,A5,A5
				
				STW 	.D1		A5,*A6++
				NOP				2
				ADD 	.L1 	A4,4,A4
		[B0]	BDEC	.S2		fir_sp_asm_l1,B0
				NOP				5
		
				B				B3
				NOP				5
				
				; end of fir_sp_asm_softPipeline procedure	
				