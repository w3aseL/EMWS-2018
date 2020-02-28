/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xnrm2.c
 *
 * Code generation for function 'xnrm2'
 *
 */

/* Include files */
#include "xnrm2.h"
#include "calcMaxwell.h"
#include "calcMaxwell_rtwutil.h"
#include "rt_nonfinite.h"
#include "xhseqr.h"
#include <math.h>

/* Function Definitions */
float xnrm2(int n, const creal32_T x[16], int ix0)
{
  float y;
  float scale;
  int kend;
  int k;
  float absxk;
  float t;
  y = 0.0F;
  if (n >= 1) {
    if (n == 1) {
      y = rt_hypotf_snf(x[ix0 - 1].re, x[ix0 - 1].im);
    } else {
      scale = 1.29246971E-26F;
      kend = ix0 + 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabsf(x[k - 1].re);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }

        absxk = fabsf(x[k - 1].im);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrtf(y);
    }
  }

  return y;
}

/* End of code generation (xnrm2.c) */
