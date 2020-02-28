/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzlarf.c
 *
 * Code generation for function 'xzlarf'
 *
 */

/* Include files */
#include "xzlarf.h"
#include "calcMaxwell.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void xzlarf(int m, int n, int iv0, const creal32_T tau, creal32_T C[16], int ic0,
            creal32_T work[4])
{
  int lastv;
  int lastc;
  int i;
  boolean_T exitg2;
  float c_re;
  float c_im;
  int b_i;
  int jy;
  int ia;
  int j;
  int ix;
  int exitg1;
  float temp_re;
  float temp_im;
  float C_im;
  if ((tau.re != 0.0F) || (tau.im != 0.0F)) {
    lastv = m;
    i = iv0 + m;
    while ((lastv > 0) && ((C[i - 2].re == 0.0F) && (C[i - 2].im == 0.0F))) {
      lastv--;
      i--;
    }

    lastc = n - 1;
    exitg2 = false;
    while ((!exitg2) && (lastc + 1 > 0)) {
      i = ic0 + (lastc << 2);
      ia = i;
      do {
        exitg1 = 0;
        if (ia <= (i + lastv) - 1) {
          if ((C[ia - 1].re != 0.0F) || (C[ia - 1].im != 0.0F)) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = -1;
  }

  if (lastv > 0) {
    if (lastc + 1 != 0) {
      if (0 <= lastc) {
        memset(&work[0], 0, (lastc + 1) * sizeof(creal32_T));
      }

      i = 0;
      b_i = ic0 + (lastc << 2);
      for (jy = ic0; jy <= b_i; jy += 4) {
        ix = iv0 - 1;
        c_re = 0.0F;
        c_im = 0.0F;
        j = (jy + lastv) - 1;
        for (ia = jy; ia <= j; ia++) {
          c_re += C[ia - 1].re * C[ix].re + C[ia - 1].im * C[ix].im;
          c_im += C[ia - 1].re * C[ix].im - C[ia - 1].im * C[ix].re;
          ix++;
        }

        work[i].re += c_re - 0.0F * c_im;
        work[i].im += c_im + 0.0F * c_re;
        i++;
      }
    }

    c_re = -tau.re;
    c_im = -tau.im;
    if ((!(-tau.re == 0.0F)) || (!(-tau.im == 0.0F))) {
      i = ic0;
      jy = 0;
      for (j = 0; j <= lastc; j++) {
        if ((work[jy].re != 0.0F) || (work[jy].im != 0.0F)) {
          temp_re = work[jy].re * c_re + work[jy].im * c_im;
          temp_im = work[jy].re * c_im - work[jy].im * c_re;
          ix = iv0;
          b_i = lastv + i;
          for (ia = i; ia < b_i; ia++) {
            C_im = C[ix - 1].re * temp_im + C[ix - 1].im * temp_re;
            C[ia - 1].re += C[ix - 1].re * temp_re - C[ix - 1].im * temp_im;
            C[ia - 1].im += C_im;
            ix++;
          }
        }

        jy++;
        i += 4;
      }
    }
  }
}

/* End of code generation (xzlarf.c) */
