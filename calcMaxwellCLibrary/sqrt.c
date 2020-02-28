/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sqrt.c
 *
 * Code generation for function 'sqrt'
 *
 */

/* Include files */
#include "sqrt.h"
#include "calcMaxwell.h"
#include "calcMaxwell_rtwutil.h"
#include "rt_nonfinite.h"
#include "xhseqr.h"
#include <math.h>

/* Function Definitions */
void b_sqrt(creal32_T *x)
{
  float xr;
  float xi;
  float absxi;
  float absxr;
  xr = x->re;
  xi = x->im;
  if (xi == 0.0F) {
    if (xr < 0.0F) {
      absxi = 0.0F;
      xr = sqrtf(-xr);
    } else {
      absxi = sqrtf(xr);
      xr = 0.0F;
    }
  } else if (xr == 0.0F) {
    if (xi < 0.0F) {
      absxi = sqrtf(-xi / 2.0F);
      xr = -absxi;
    } else {
      absxi = sqrtf(xi / 2.0F);
      xr = absxi;
    }
  } else if (rtIsNaNF(xr)) {
    absxi = xr;
  } else if (rtIsNaNF(xi)) {
    absxi = xi;
    xr = xi;
  } else if (rtIsInfF(xi)) {
    absxi = fabsf(xi);
    xr = xi;
  } else if (rtIsInfF(xr)) {
    if (xr < 0.0F) {
      absxi = 0.0F;
      xr = xi * -xr;
    } else {
      absxi = xr;
      xr = 0.0F;
    }
  } else {
    absxr = fabsf(xr);
    absxi = fabsf(xi);
    if ((absxr > 8.50705867E+37F) || (absxi > 8.50705867E+37F)) {
      absxr *= 0.5F;
      absxi = rt_hypotf_snf(absxr, absxi * 0.5F);
      if (absxi > absxr) {
        absxi = sqrtf(absxi) * sqrtf(absxr / absxi + 1.0F);
      } else {
        absxi = sqrtf(absxi) * 1.41421354F;
      }
    } else {
      absxi = sqrtf((rt_hypotf_snf(absxr, absxi) + absxr) * 0.5F);
    }

    if (xr > 0.0F) {
      xr = 0.5F * (xi / absxi);
    } else {
      if (xi < 0.0F) {
        xr = -absxi;
      } else {
        xr = absxi;
      }

      absxi = 0.5F * (xi / xr);
    }
  }

  x->re = absxi;
  x->im = xr;
}

/* End of code generation (sqrt.c) */
