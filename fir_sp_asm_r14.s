; file firlib\src\fir_sp_asm_r14.s
; brief FIR filtering function in radix 4 vectorized C6600 assembler (single precision IEEE754)
; warning radix 4 input and coefficients arrays sizes
; author 
; date 

	.global fir_sp_asm_r14
	
; C prototype :							match registers :
;
; void fir_sp_asm_r14 (	const float * restrict xk, 	-> A4
;						const float * restrict a,	-> B4
;						float * restrict yk, 		-> A6
;						int na,						-> B6
;						int nyk);					-> A8

save_context	.macro	rsp
				; save core working registers context on the top of stack
				; cf. SPRU187V Optimizing Compiler
				; Chapter 7.3 Register Conventions, table 7.2
				MV				B15,rsp 	; save Stack Pointer
				STDW			B15:B14,*rsp--[1]
				STDW			B13:B12,*rsp--[1]
				STDW			B11:B10,*rsp--[1]
				STDW			A15:A14,*rsp--[1]
				STDW			A13:A12,*rsp--[1]
				STDW			A11:A10,*rsp--[1]
				MVC				ILC,B15
				MVC				RILC,B14
				STDW			B15:B14,*rsp--[1]				
				; do not use rsp register in current ASM procedure 
				.endm

restore_context	.macro	rsp
				; restore core working registers context from the top of stack
				LDDW			*++rsp[1],B15:B14	
				MVC				B14,RILC
				MVC				B15,ILC				
				LDDW			*++rsp[1],A11:A10
				LDDW			*++rsp[1],A13:A12
				LDDW			*++rsp[1],A15:A14
				LDDW			*++rsp[1],B11:B10
				LDDW			*++rsp[1],B13:B12
				LDDW			*++rsp[1],B15:B14		
				MV				rsp,B15 	; restore Stack Pointer
				NOP				3
				.endm
				
fir_sp_asm_r14:
				; save core registers context
				save_context	A3

				; user code
				
				; restore core registers context and leave procedure
				restore_context	A3
				B				B3
				NOP				5