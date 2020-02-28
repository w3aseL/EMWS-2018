/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_calcMaxwell_api.h
 *
 * Code generation for function '_coder_calcMaxwell_api'
 *
 */

#ifndef _CODER_CALCMAXWELL_API_H
#define _CODER_CALCMAXWELL_API_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void calcMaxwell(real32_T u[9], real32_T e[9], real_T w, real_T k1,
  real_T k2, creal32_T eigvec[16], creal32_T eigval[16], creal32_T maxMat[16]);
extern void calcMaxwell_api(const mxArray * const prhs[5], int32_T nlhs, const
  mxArray *plhs[3]);
extern void calcMaxwell_atexit(void);
extern void calcMaxwell_initialize(void);
extern void calcMaxwell_terminate(void);
extern void calcMaxwell_xil_shutdown(void);
extern void calcMaxwell_xil_terminate(void);

#endif

/* End of code generation (_coder_calcMaxwell_api.h) */
