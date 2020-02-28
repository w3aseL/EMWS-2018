/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * recip.c
 *
 * Code generation for function 'recip'
 *
 */

/* Include files */
#include "recip.h"
#include "calcMaxwell.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
creal32_T recip(const creal32_T y)
{
  creal32_T z;
  float brm;
  float bim;
  float d;
  brm = fabsf(y.re);
  bim = fabsf(y.im);
  if (y.im == 0.0F) {
    z.re = 1.0F / y.re;
    z.im = 0.0F;
  } else if (y.re == 0.0F) {
    z.re = 0.0F;
    z.im = -1.0F / y.im;
  } else if (brm > bim) {
    bim = y.im / y.re;
    d = y.re + bim * y.im;
    z.re = 1.0F / d;
    z.im = -bim / d;
  } else if (brm == bim) {
    bim = 0.5F;
    if (y.re < 0.0F) {
      bim = -0.5F;
    }

    d = 0.5F;
    if (y.im < 0.0F) {
      d = -0.5F;
    }

    z.re = bim / brm;
    z.im = -d / brm;
  } else {
    bim = y.re / y.im;
    d = y.im + bim * y.re;
    z.re = bim / d;
    z.im = -1.0F / d;
  }

  return z;
}

/* End of code generation (recip.c) */
