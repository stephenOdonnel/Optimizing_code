#ifndef __FIR_TEST_H
#define __FIR_TEST_H

/**
* @file test\h\firtest.h
* @brief conformity and performance tests for FIR algorithms library
*
* @li documentations :\n
* - TMS320C6678 TI references <a href="http://www.ti.com/product/tms320c6678">www.ti.com/product/tms320c6678</a>\n\n
*
* @li include dependencies :\n
* - FIR library header ..\\h\\firlib.h\n
* - IDMA library header ..\\h\\idmalib.h\n
* - EDMA library header ..\\h\\edmalib.h\n
* - C:\\ti\\dsplib_c66x_latest_version\\inc\n
* - C:\\ti\\dsplib_c66x_latest_version\\packages\n
* - C:\\ti\\pdk_C6678_latest_version\\packages\n\n
*
* @li library dependencies :\n
* - C standard Library\n
* - CSL (Chip Support Library) in PDK package (Platform Development Kit) :\n
* C:\\ti\\pdk_C6678_latest_version\\packages\\ti\\csl\\lib\\ti.csl.ae66\n
* - DSPLIB (Digital Signal Processing Library) :\n
* C:\\ti\\dsplib_c66x_latest_version\\lib\\dsplib.ae66\n\n
*
* @li predefined symbol for benchmarking :\n
* - _TMS320C6600\n
*
* @author hugo descoubes
* @date september 2015
*/

/* texas instruments dependencies */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <c6x.h>
#include <dsplib.h>
#include <csl_tsc.h>
#include <csl_cache.h>
#include <csl_cacheAux.h>

/* project specific dependencies */
#include <firlib.h>
//#include <idmalib.h>
//#include <edmalib.h>

/* project specific types */
typedef uint8_t Boolean;
typedef struct {
	char		error_status[4];	// string to specify validity of test (OK or NOK)
	uint64_t 	error_samples;		// number of false samples
	float 		error_percent;		// maximum percentage error
	float 		error_margin;		// maximum tolerated margin. Have to be initialized
} TestSystem_obj;					// conformity test object
typedef struct {
	uint32_t 	perf_rep;			// number of test repetitions
	CSL_Uint64	perf_nbcycles;		// duration in number of CPU cycles
	float32_t 	perf_usertime_ms;	// duration in ms
	float32_t 	perf_macs;			// algorithm performance in MAC per CPU cycle
} TestPerf_obj;						// performance test object


/* algorithms and memory model under test */
#define TEST_FIR_SP					1
#define TEST_FIR_SP_R4				0
#define TEST_FIR_SP_OPT_R4			0
#define TEST_FIR_ASM				1
#define TEST_FIR_ASM_VLIW			1
#define TEST_FIR_ASM_PIPE			1
#define TEST_FIR_ASM_R4				0
#define TEST_FIR_L2SRAM_L1DCACHE	0
#define TEST_FIR_L2SRAM_L1DSRAM		0
#define TEST_FIR_L2SRAM_L1DIDMA		0
#define TEST_FIR_L2EDMA_L1DIDMA		0

/* TMS32C6678 memory model :
* L1D/L1P 32Kb per core
* L2 512Kb per core
* MSM SRAM 4Mb shared by cores
* DDR3 512Mb shared by cores (TMDSEVM6678L board specific)
*
* Project specific :
* XK_LENGTH 		: length of input array in DDR
* AK_LENGTH 		: length of coefficients array in L1D cache
* YK_LENGTH 		: length of output array in DDR
* DDR_ARRAY_LENGTH 	: generic array length in DDR
* L2_ARRAY_LENGTH 	: generic array length in L2 SRAM, 32K/128Kb samples
* L1D_ARRAY_LENGTH 	: generic array length in L1D SRAM, 2K/8Kb samples
*/
#define XK_LENGTH 2048		/* 8kb vector*/
//#define XK_LENGTH 65536	/* 256kb vector*/
//#define XK_LENGTH 1048576	/* 4Mb vector*/
#define A_LENGTH 64
#define	YK_LENGTH XK_LENGTH - A_LENGTH + 1
#define	DDR_ARRAY_LENGTH 	XK_LENGTH
#define L2_ARRAY_LENGTH 	32768
#define	L1D_ARRAY_LENGTH	2048

/* misc parameters */
#define CPU_CLOCK_KHZ   		1400000
#define CPU_CLOCK_MS   		 	1/CPU_CLOCK_KHZ
#define MARGIN_LIMIT   		 	1.0
#define NB_OF_REP   		 	10
#define FIR_NB_MACS   		 	A_LENGTH * YK_LENGTH 	/* FIR algorithm complexity */
#define UMA_L2CACHE_L1DCACHE	0
#define UMA_L2SRAM_L1DCACHE		1
#define UMA_L2SRAM_L1DSRAM		2
#define UMA_L2SRAM_L1DIDMA		3
#define UMA_L2EDMA_L1DIDMA		4

/* input, temporary and ouput vectors */
extern float xk_sp[XK_LENGTH];
extern const float a_sp[A_LENGTH];
extern float yk_sp_ti[YK_LENGTH];
extern float yk_sp[YK_LENGTH];
extern float xk_sp_l2[L2_ARRAY_LENGTH + A_LENGTH - 1];
extern float xk_sp_l1d[L1D_ARRAY_LENGTH + A_LENGTH - 1];
extern float a_sp_l1d[A_LENGTH];
extern float yk_sp_l1d[L1D_ARRAY_LENGTH];
extern float yk_sp_l2[L2_ARRAY_LENGTH];

/* API reference */

/**
 * @brief initializations for FIR algorithms library tests procedures
 * @li input vector initialization
 * @li core timer initialization
 * @li test margin initialization
 * @li number of algorithm repetitions initialization
 * @param margin initialize conformity test margin
 * @param repetition initialize the number of algorithm repetitions
 * @param input pointer to the input vector for initialization
 * @param size input vector size
 */
void firtest_init (	TestSystem_obj *margin,
					TestPerf_obj *repetition,
					float *input,
					uint64_t size);

/**
 * @brief system/conformity test for outputs vectors of miscellaneous algorithms.
 * Sample by sample comparison with tolerated margin error
 * @param conformity statistics about vectors test
 * @param src1 bench vector
 * @param src2 vector under test
 * @param size size of inputs vectors
 * @return TRUE if sample by sample comparison is less important
 * than margin. Else return FALSE
 */
Boolean firtest_sys(	TestSystem_obj *conformity,
						float *src1,
						float *src2,
						uint64_t size);

/**
 * @brief performance test for FIR algorithms library
 * @param benchmark statistics about current algorithm performance
 * @param memoryModel memory model architecture. Accepted values :
 * @li UMA_L2CACHE_L1DCACHE
 * @li UMA_L2SRAM_L1DCACHE
 * @li UMA_L2SRAM_L1DSRAM
 * @param output output vector to overwrite
 * @param fir_fct pointer to function under test
 */
void firtest_perf(	TestPerf_obj *benchmark,
					uint8_t memoryModel,
					float * restrict output,
					void (*fir_fct) (	const float * restrict,
										const float * restrict,
										float * restrict,
										int,
										int) );

#endif /* __FIR_TEST_H */
