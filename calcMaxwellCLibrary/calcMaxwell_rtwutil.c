/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * calcMaxwell_rtwutil.c
 *
 * Code generation for function 'calcMaxwell_rtwutil'
 *
 */

/* Include files */
#include "calcMaxwell_rtwutil.h"
#include "calcMaxwell.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
float rt_hypotf_snf(float u0, float u1)
{
  float y;
  float a;
  a = fabsf(u0);
  y = fabsf(u1);
  if (a < y) {
    a /= y;
    y *= sqrtf(a * a + 1.0F);
  } else if (a > y) {
    y /= a;
    y = a * sqrtf(y * y + 1.0F);
  } else {
    if (!rtIsNaNF(y)) {
      y = a * 1.41421354F;
    }
  }

  return y;
}

/* End of code generation (calcMaxwell_rtwutil.c) */
