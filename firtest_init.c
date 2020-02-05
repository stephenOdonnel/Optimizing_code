/*
* file test/src/firtest_init.c
* brief initializations for FIR algorithms library procedure
* benchmarking
* author
* date
*/

/* dependencies */
#include <firtest.h>

/* input vector parameters */
#define F1 100.0f
#define F2 1000.0f
#define Fs 10000.0f
#define Ts 1/Fs
#define PI 3.14159f

 /*
  * initializations for FIR algorithms library procedure
  */
void firtest_init (	TestSystem_obj *margin,
					TestPerf_obj *repetition,
					float *input,
					uint64_t size) {
	int k;

	/* input vector initialization */
	for (k=0; k<size; k++) {

		/* temporal input vector :
		 * xk(t) = sinus (w1.t) + sinus (w2.t)
		 * xk(t) = sinus (2.pi.F1.t) + sinus (2.pi.F2.t)
		 * xk(k.Ts) = sinus (2.pi.F1.k.Ts) + sinus (2.pi.F2.k.Ts)
		 */
		input[k] = 	(float32_t) sin ( (double) 2.0*PI*F1*k*Ts)			\
					+ (float32_t) sin ( (double) 2.0*PI*F2*k*Ts);
	}

	/* enable TSC (Time Stamp Counter) core Timer for performance tests */
	CSL_tscEnable();

	/* initialize conformity test margin */
	margin->error_margin = MARGIN_LIMIT;

	/* initialize number of algorithm repetitions */
	repetition->perf_rep = NB_OF_REP;
}
