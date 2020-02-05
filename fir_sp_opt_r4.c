/*
* file firlib\src\fir_sp_opt_r4.c
* brief FIR filtering function in radix 4 vectorized C (single precision IEEE754)
* warning radix 4 input and coefficients arrays sizes
* author
* date
*/

#include "firlib.h"

/*
* FIR filtering function in radix 4 vectorized C (single precision IEEE754)
* warning radix 4 input and coefficients arrays sizes
*/
void fir_sp_opt_r4 (const float * restrict xk, 	\
					const float * restrict a,	\
					float * restrict yk, 		\
					int na,						\
					int nyk){
	int i, j;
	__float2_t acc1, acc2, acc3, acc4, acc5, acc6, acc7, acc8;
	__float2_t a10, a32;
	__float2_t xk10, xk21, xk32, xk43, xk54, xk65;


	_nassert(na >= 4);
	_nassert(na % 4 == 0);
	_nassert((int) a % 8 == 0);

	_nassert(nyk >= 4);
	_nassert(nyk % 4 == 0);
	_nassert((int) yk % 8 == 0);
	_nassert((int) xk % 8 == 0);

	/* user code */
	for (i=0; i<nyk; i+=4) {
			/* user code */
			//yk[i] = 0;
			acc1 = 0.0f;
			acc2 = 0.0f;
			acc3 = 0.0f;
			acc4 = 0.0f;
			acc5 = 0.0f;
			acc6 = 0.0f;
			acc7 = 0.0f;
			acc8 = 0.0f;

			/* FIR filter algorithm - dot product */
			for (j=0; j<na; j+=4){
				/* user code */
				a10 = _amemd8_const(a+j);
				a32 = _amemd8_const(a+j+2);

				xk10 = _amemd8_const(xk+j+i);
				xk32 = _amemd8_const(xk+j+i+2);
				xk54 = _amemd8_const(xk+j+i+4);  //LDDW
				xk21 = _ftod(_lof(xk32),_hif(xk10));

				xk43 = _ftod(_lof(xk54),_hif(xk32));

				xk65 = _memd8_const(xk+i+j+5); //MV



				acc1 = _daddsp(acc1,_dmpysp(a10,xk10));
				acc2 = _daddsp(acc2,_dmpysp(a32,xk32));
				acc3 = _daddsp(acc3,_dmpysp(a10,xk21));
				acc4 = _daddsp(acc4,_dmpysp(a32,xk43));
				acc5 = _daddsp(acc5,_dmpysp(a10,xk32));
				acc6 = _daddsp(acc6,_dmpysp(a32,xk54));
				acc7 = _daddsp(acc7,_dmpysp(a10,xk43));
				acc8 = _daddsp(acc8,_dmpysp(a32,xk65));



			}

			acc1 = _daddsp(acc1,acc2);
			acc3 = _daddsp(acc3,acc4);


			acc5 = _daddsp(acc5,acc6);
			acc7 = _daddsp(acc7,acc8);

			acc2 = _ftod(_lof(acc3)+_hif(acc3),_lof(acc1)+_hif(acc1));
			acc4 = _ftod(_lof(acc7)+_hif(acc7),_lof(acc5)+_hif(acc5));

			_amemd8(yk+i) = acc2;
			_amemd8(yk+i+2) = acc4;



		}
	}
