/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_calcMaxwell_mex.c
 *
 * Code generation for function '_coder_calcMaxwell_mex'
 *
 */

/* Include files */
#include "_coder_calcMaxwell_mex.h"
#include "_coder_calcMaxwell_api.h"

/* Function Declarations */
MEXFUNCTION_LINKAGE void calcMaxwell_mexFunction(int32_T nlhs, mxArray *plhs[3],
  int32_T nrhs, const mxArray *prhs[5]);

/* Function Definitions */
void calcMaxwell_mexFunction(int32_T nlhs, mxArray *plhs[3], int32_T nrhs, const
  mxArray *prhs[5])
{
  const mxArray *outputs[3];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 5) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 5, 4,
                        11, "calcMaxwell");
  }

  if (nlhs > 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 11,
                        "calcMaxwell");
  }

  /* Call the function. */
  calcMaxwell_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(calcMaxwell_atexit);

  /* Module initialization. */
  calcMaxwell_initialize();

  /* Dispatch the entry-point. */
  calcMaxwell_mexFunction(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  calcMaxwell_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_calcMaxwell_mex.c) */
