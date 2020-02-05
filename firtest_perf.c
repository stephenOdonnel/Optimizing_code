/*
* file test/src/firtest_perf.c
* brief performance test for FIR algorithms library
* author
* date
*/

/* dependencies */
#include <firtest.h>

 /*
  * performance test for FIR algorithms library
  */
void firtest_perf(	TestPerf_obj *benchmark,
					uint8_t memoryModel,
					float * restrict output,
					void (*fir_fct) (	const float * restrict,
										const float * restrict,
										float * restrict,
										int,
										int) ) 
{
	register CSL_Uint64 start, end, duration=0;
	register uint32_t k, rep;

	/* initialization */
	rep = benchmark->perf_rep;

	/* fix number of algorithm repetitions */
	for (k=0; k < rep; k++) {

		/* read current TSC value */
		start = CSL_tscRead ();

		/* call fir algorithm for performance test */
		(*fir_fct) (xk_sp, a_sp, output, A_LENGTH, YK_LENGTH);

		/* processing time calculation */
		end = CSL_tscRead ();
		duration += end-start;
	}

	/* back up */
	duration /= benchmark->perf_rep; // calcul de la moyenne de 10 répétitions
	benchmark->perf_nbcycles = duration;
	benchmark->perf_usertime_ms = (float32_t) duration * CPU_CLOCK_MS;
	benchmark->perf_macs = ((float32_t) FIR_NB_MACS) / ((float32_t) duration);
	
	/* DEBUG : bug printf */
	printf("");
}
