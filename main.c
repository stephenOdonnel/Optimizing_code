/*
* file test\src\main.c
* brief conformity and performance tests for FIR algorithms library
* author
* date
*/

#include <firtest.h>
#include <a_sp.h>

/* input and ouputs vectors */
float32_t xk_sp[XK_LENGTH];
float32_t yk_sp_ti[YK_LENGTH];
float32_t yk_sp[YK_LENGTH];

/*
* main entry point
*/
void main(void)
{
	Boolean 		validity;
	TestSystem_obj 	conformity;
	TestPerf_obj	benchmark;

	/* initializations */
	firtest_init(&conformity, &benchmark, xk_sp, XK_LENGTH);

	/* texas instruments fir reference : output benchmark (full cacheability) */
	printf(	"\nFIR algorithms benchmarking on TI TMS320C6678 DSP architecture"
			"\ntesting conditions :"
			"\n--> input vector size : %d samples"
			"\n--> floating MAC's per cycle max : 8"
			"\n--> repetitions : %d"
			"\n--> tolerated error : less than %3.1f%%",
			XK_LENGTH,
			benchmark.perf_rep,
			conformity.error_margin);

	firtest_perf (&benchmark, UMA_L2CACHE_L1DCACHE, yk_sp_ti, &DSPF_sp_fir_gen);

	printf(	"\n--> reference algorithm : Texas Instruments, DSPF_sp_fir_gen, dsplib_c66x_3_1_0_0"
			"\n--> memory model : full cacheability"
			"\n--> performance : %d cycles, %3.3f ms, %1.2f MAC's per cycle\n"	, benchmark.perf_nbcycles
																				, benchmark.perf_usertime_ms
																				, benchmark.perf_macs);

#if ( TEST_FIR_SP != 0 )
	/* fir benchmarking : single precision in canonical c (full cacheability) */
	printf(	"\n--> fir algorithm : single precision in canonical c"
			"\nmemory model : full cacheability");
	firtest_perf (&benchmark, UMA_L2CACHE_L1DCACHE, yk_sp, &fir_sp);

	validity = firtest_sys (&conformity, yk_sp_ti, yk_sp, YK_LENGTH);
	printf("\nconformity : status %s, max %3.3f%%, %d samples\n"	, conformity.error_status
																	, conformity.error_percent
																	, conformity.error_samples);
	if ( validity ) {
		printf("performance : %d cycles, %3.3f ms, %1.2f floating MAC's per cycle\n"	, benchmark.perf_nbcycles
																						, benchmark.perf_usertime_ms
																						, benchmark.perf_macs);
	}
#endif


#if ( TEST_FIR_ASM != 0 )
	/* fir benchmarking : single precision in canonical C6600 asm (full cacheability) */
	printf(	"\n--> fir algorithm : single precision in canonical C6600 asm"
			"\nmemory model : full cacheability");
	firtest_perf (&benchmark, UMA_L2CACHE_L1DCACHE, yk_sp, &fir_sp_asm);

	validity = firtest_sys (&conformity, yk_sp_ti, yk_sp, YK_LENGTH);
	printf("\nconformity : status %s, max %3.3f%%, %d samples\n"	, conformity.error_status
																	, conformity.error_percent
																	, conformity.error_samples);
	if ( validity ) {
		printf("performance : %d cycles, %3.3f ms, %1.2f floating MAC's per cycle\n"	, benchmark.perf_nbcycles
																						, benchmark.perf_usertime_ms
																						, benchmark.perf_macs);
	}
#endif

#if ( TEST_FIR_ASM_VLIW != 0 )
	/* fir benchmarking : single precision in canonical C6600 asm (full cacheability) */
	printf(	"\n--> fir algorithm : single precision in vliw C6600 asm"
			"\nmemory model : full cacheability");
	firtest_perf (&benchmark, UMA_L2CACHE_L1DCACHE, yk_sp, &fir_sp_asm_vliw);

	validity = firtest_sys (&conformity, yk_sp_ti, yk_sp, YK_LENGTH);
	printf("\nconformity : status %s, max %3.3f%%, %d samples\n"	, conformity.error_status
																	, conformity.error_percent
																	, conformity.error_samples);
	if ( validity ) {
		printf("performance : %d cycles, %3.3f ms, %1.2f floating MAC's per cycle\n"	, benchmark.perf_nbcycles
																						, benchmark.perf_usertime_ms
																						, benchmark.perf_macs);
	}
#endif

#if ( TEST_FIR_ASM_PIPE != 0 )
	/* fir benchmarking : single precision in canonical C6600 asm (full cacheability) */
	printf(	"\n--> fir algorithm : single precision in pipe C6600 asm"
			"\nmemory model : full cacheability");
	firtest_perf (&benchmark, UMA_L2CACHE_L1DCACHE, yk_sp, &fir_sp_asm_softPipeline);

	validity = firtest_sys (&conformity, yk_sp_ti, yk_sp, YK_LENGTH);
	printf("\nconformity : status %s, max %3.3f%%, %d samples\n"	, conformity.error_status
																	, conformity.error_percent
																	, conformity.error_samples);
	if ( validity ) {
		printf("performance : %d cycles, %3.3f ms, %1.2f floating MAC's per cycle\n"	, benchmark.perf_nbcycles
																						, benchmark.perf_usertime_ms
																						, benchmark.perf_macs);
	}
#endif

	
	fflush(stdout);
	while(1);
}
