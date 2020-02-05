; file firlib\src\fir_sp_asm.s
; brief FIR filtering function in canonical C6600 assembler (single precision IEEE754)
; author 
; date

	.global fir_sp_asm
	
; C prototype :						match registers :
;
; void fir_sp_asm ( const float * restrict xk, 	-> A4
;		   			const float * restrict a,	-> B4
;		   			float * restrict yk, 		-> A6
;		   			int na,						-> B6
;		   			int nyk);					-> A8
fir_sp_asm:
				; user code

				
				MV		.L2		A8,B0
				
fir_sp_asm_l1:
				
				ZERO	.L1		A5
				MV		.L1 	B6,A1
				MV		.L1		A4,A19
				MV		.L2 	B4,B19
				

fir_sp_asm_l2:
				
				LDW		.D1		*A19++,A9
				NOP				4
				LDW		.D2 	*B19++,B9
				NOP				4
				MPYSP	.M1x 	A9,B9,A17
				NOP				3
				FADDSP 	.L1 	A17,A5,A5
				NOP				3
		[A1]	SUB		.L1		A1,1,A1
		[A1]	B		.S1		fir_sp_asm_l2
				NOP				5
				
				STW 	.D1		A5,*A6++
				ADD 	.L1 	A4,4,A4
		[B0]	SUB		.L2		B0,1,B0
		[B0]	B		.S1		fir_sp_asm_l1
				NOP				5
		
				B				B3
				NOP				5
				
				;B				B3 ; enable us to jump back a forth to the c code
				;NOP				5 ; end of fir_sp_asm procedure
				