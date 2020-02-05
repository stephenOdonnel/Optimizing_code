/*
* file firlib\src\fir_sp_r4.c
* brief FIR filtering function in radix 4 canonical C (single precision IEEE754)
* warning radix 4 input and coefficients arrays sizes
* author
* date
*/

#include "firlib.h"

/*
* FIR filtering function in radix 4 canonical C (single precision IEEE754)
* warning radix 4 input and coefficients arrays sizes
*/
void fir_sp_r4 (const float * restrict xk, 	\
				const float * restrict a,	\
				float * restrict yk, 		\
				int na,						\
				int nyk){
	int i, j;
	float acc1, acc2, acc3, acc4;
	float a0, a1, a2, a3;
	float xk0, xk1, xk2, xk3, xk4, xk5, xk6;

	/* input array loop */
	for (i=0; i<nyk; i+=4) {
		/* user code */
		//yk[i] = 0;
		acc1 = 0;
		acc2 = 0;
		acc3 = 0;
		acc4 = 0;

		/* FIR filter algorithm - dot product */
		for (j=0; j<na; j+=4){
			/* user code */
			a0 = a[j];
			a1 = a[j+1];
			a2 = a[j+2];
			a3 = a[j+3];

			xk0 = xk[j+i];
			xk1 = xk[j+i+1];
			xk2 = xk[j+i+2];
			xk3 = xk[j+i+3];
			xk4 = xk[j+i+4];
			xk5 = xk[j+i+5];
			xk6 = xk[j+i+6];


			acc1 += xk0 * a0 + xk1 * a1 + xk2 * a2 + xk3 *a3;

			acc2 += xk1 * a0 + xk2 * a1 + xk3 * a2 + xk4 *a3;
			acc3 += xk2 * a0 + xk3 * a1 + xk4 * a2 + xk5 *a3;
			acc4 += xk3 * a0 + xk4 * a1 + xk5 * a2 + xk6 *a3;



		}
		
		/* user code */
		yk[i] = acc1;
		yk[i+1] = acc2;
		yk[i+2] = acc3;
		yk[i+3] = acc4;
	}
}
