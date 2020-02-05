; file firlib\src\fir_sp_asm_manual.s
; brief FIR filtering function in C6600 assembler with typical VLIW optimization
; (single precision IEEE754)
; author 
; date 

	.global fir_sp_asm_vliw

fir_sp_asm_vliw:
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
				MPYSP	.M1x 	A9,B9,A17
	||  [A1]	SUB		.L1		A1,1,A1
		[A1]	B		.S1		fir_sp_asm_l2
				NOP				2
			    FADDSP 	.L1 	A17,A5,A5
				NOP				2
				
				STW 	.D1		A5,*A6++
				ADD 	.L1 	A4,4,A4
	||	[B0]	SUB		.L2		B0,1,B0
		[B0]	B		.S1		fir_sp_asm_l1
				NOP				5
	
				B				B3
				NOP				5
				; end of fir_sp_asm_vliw procedure