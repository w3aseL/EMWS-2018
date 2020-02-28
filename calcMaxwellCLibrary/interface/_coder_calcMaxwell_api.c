/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_calcMaxwell_api.c
 *
 * Code generation for function '_coder_calcMaxwell_api'
 *
 */

/* Include files */
#include "_coder_calcMaxwell_api.h"
#include "_coder_calcMaxwell_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131483U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "calcMaxwell",                       /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real32_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[9];
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *w, const
  char_T *identifier);
static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static real32_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[9];
static real32_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  char_T *identifier))[9];
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const creal32_T u
  [16]);
static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);

/* Function Definitions */
static real32_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[9]
{
  real32_T (*y)[9];
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *w, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(w), &thisId);
  emlrtDestroyArray(&w);
  return y;
}

static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real32_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[9]
{
  real32_T (*ret)[9];
  static const int32_T dims[2] = { 3, 3 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "single", false, 2U, dims);
  ret = (real32_T (*)[9])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  static real32_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const char_T *identifier))[9]
{
  real32_T (*y)[9];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(u), &thisId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const creal32_T u
  [16])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 4, 4 };

  y = NULL;
  m = emlrtCreateNumericArray(2, iv, mxSINGLE_CLASS, mxCOMPLEX);
  emlrtExportNumericArrayR2013b(sp, m, (void *)&u[0], 4);
  emlrtAssign(&y, m);
  return y;
}

static real_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

void calcMaxwell_api(const mxArray * const prhs[5], int32_T nlhs, const mxArray *
                     plhs[3])
{
  real32_T (*u)[9];
  real32_T (*e)[9];
  real_T w;
  real_T k1;
  real_T k2;
  creal32_T eigvec[16];
  creal32_T eigval[16];
  creal32_T maxMat[16];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  u = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "u");
  e = emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "e");
  w = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "w");
  k1 = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "k1");
  k2 = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "k2");

  /* Invoke the target function */
  calcMaxwell(*u, *e, w, k1, k2, eigvec, eigval, maxMat);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(&st, eigvec);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(&st, eigval);
  }

  if (nlhs > 2) {
    plhs[2] = emlrt_marshallOut(&st, maxMat);
  }
}

void calcMaxwell_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  calcMaxwell_xil_terminate();
  calcMaxwell_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void calcMaxwell_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void calcMaxwell_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (_coder_calcMaxwell_api.c) */
