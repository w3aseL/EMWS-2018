/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xdlapy3.c
 *
 * Code generation for function 'xdlapy3'
 *
 */

/* Include files */
#include "xdlapy3.h"
#include "calcMaxwell.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
float xdlapy3(float x1, float x2, float x3)
{
  float y;
  float a;
  float b;
  float c;
  a = fabsf(x1);
  b = fabsf(x2);
  c = fabsf(x3);
  y = fmaxf(a, b);
  if (c > y) {
    y = c;
  }

  if ((y > 0.0F) && (!rtIsInfF(y))) {
    a /= y;
    b /= y;
    c /= y;
    y *= sqrtf((a * a + c * c) + b * b);
  } else {
    y = (a + b) + c;
  }

  return y;
}

/* End of code generation (xdlapy3.c) */
