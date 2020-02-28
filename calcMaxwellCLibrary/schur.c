/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * schur.c
 *
 * Code generation for function 'schur'
 *
 */

/* Include files */
#include "schur.h"
#include "calcMaxwell.h"
#include "recip.h"
#include "rt_nonfinite.h"
#include "xdlapy3.h"
#include "xhseqr.h"
#include "xnrm2.h"
#include "xzlarf.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void schur(const creal32_T A[16], creal32_T V[16], creal32_T T[16])
{
  boolean_T p;
  int k;
  int i;
  creal32_T work[4];
  int knt;
  int b_i;
  int im1n_tmp;
  int in;
  int ix0;
  int alpha1_tmp;
  creal32_T alpha1;
  int c_i;
  creal32_T tau[3];
  float xnorm;
  float beta1;
  int jy;
  int lastv;
  int lastc;
  float f;
  creal32_T b_tau;
  boolean_T exitg2;
  float f1;
  float im;
  int ix;
  int exitg1;
  int i1;
  creal32_T b_alpha1;
  p = true;
  for (k = 0; k < 16; k++) {
    if ((!p) || (rtIsInfF(A[k].re) || rtIsInfF(A[k].im) || (rtIsNaNF(A[k].re) ||
          rtIsNaNF(A[k].im)))) {
      p = false;
    }
  }

  if (!p) {
    for (i = 0; i < 16; i++) {
      V[i].re = rtNaNF;
      V[i].im = 0.0F;
    }

    knt = 2;
    for (k = 0; k < 3; k++) {
      if (knt <= 4) {
        memset(&V[(k * 4 + knt) + -1], 0, (5 - knt) * sizeof(creal32_T));
      }

      knt++;
    }

    for (i = 0; i < 16; i++) {
      T[i].re = rtNaNF;
      T[i].im = 0.0F;
    }
  } else {
    memcpy(&T[0], &A[0], 16U * sizeof(creal32_T));
    work[0].re = 0.0F;
    work[0].im = 0.0F;
    work[1].re = 0.0F;
    work[1].im = 0.0F;
    work[2].re = 0.0F;
    work[2].im = 0.0F;
    work[3].re = 0.0F;
    work[3].im = 0.0F;
    for (b_i = 0; b_i < 3; b_i++) {
      knt = b_i << 2;
      im1n_tmp = knt + 2;
      in = (b_i + 1) << 2;
      alpha1_tmp = (b_i + knt) + 1;
      alpha1 = T[alpha1_tmp];
      if (b_i + 3 < 4) {
        c_i = b_i + 1;
      } else {
        c_i = 2;
      }

      ix0 = c_i + im1n_tmp;
      tau[b_i].re = 0.0F;
      tau[b_i].im = 0.0F;
      xnorm = xnrm2(2 - b_i, T, ix0);
      if ((xnorm != 0.0F) || (T[alpha1_tmp].im != 0.0F)) {
        beta1 = xdlapy3(T[alpha1_tmp].re, T[alpha1_tmp].im, xnorm);
        if (T[alpha1_tmp].re >= 0.0F) {
          beta1 = -beta1;
        }

        if (fabsf(beta1) < 9.86076132E-32F) {
          knt = -1;
          i = (ix0 - b_i) + 1;
          do {
            knt++;
            for (k = ix0; k <= i; k++) {
              f = T[k - 1].im;
              f1 = T[k - 1].re;
              im = 1.01412048E+31F * f + 0.0F * f1;
              f1 = 1.01412048E+31F * f1 - 0.0F * f;
              T[k - 1].re = f1;
              T[k - 1].im = im;
            }

            beta1 *= 1.01412048E+31F;
            alpha1.re *= 1.01412048E+31F;
            alpha1.im *= 1.01412048E+31F;
          } while (!(fabsf(beta1) >= 9.86076132E-32F));

          beta1 = xdlapy3(alpha1.re, alpha1.im, xnrm2(2 - b_i, T, ix0));
          if (alpha1.re >= 0.0F) {
            beta1 = -beta1;
          }

          xnorm = beta1 - alpha1.re;
          if (0.0F - alpha1.im == 0.0F) {
            tau[b_i].re = xnorm / beta1;
            tau[b_i].im = 0.0F;
          } else if (xnorm == 0.0F) {
            tau[b_i].re = 0.0F;
            tau[b_i].im = (0.0F - alpha1.im) / beta1;
          } else {
            tau[b_i].re = xnorm / beta1;
            tau[b_i].im = (0.0F - alpha1.im) / beta1;
          }

          b_alpha1.re = alpha1.re - beta1;
          b_alpha1.im = alpha1.im;
          alpha1 = recip(b_alpha1);
          i = (ix0 - b_i) + 1;
          for (k = ix0; k <= i; k++) {
            f = T[k - 1].im;
            f1 = T[k - 1].re;
            im = alpha1.re * f + alpha1.im * f1;
            f1 = alpha1.re * f1 - alpha1.im * f;
            T[k - 1].re = f1;
            T[k - 1].im = im;
          }

          for (k = 0; k <= knt; k++) {
            beta1 *= 9.86076132E-32F;
          }

          alpha1.re = beta1;
          alpha1.im = 0.0F;
        } else {
          xnorm = beta1 - T[alpha1_tmp].re;
          if (0.0F - T[alpha1_tmp].im == 0.0F) {
            tau[b_i].re = xnorm / beta1;
            tau[b_i].im = 0.0F;
          } else if (xnorm == 0.0F) {
            tau[b_i].re = 0.0F;
            tau[b_i].im = (0.0F - T[alpha1_tmp].im) / beta1;
          } else {
            tau[b_i].re = xnorm / beta1;
            tau[b_i].im = (0.0F - T[alpha1_tmp].im) / beta1;
          }

          alpha1.re = T[alpha1_tmp].re - beta1;
          alpha1.im = T[alpha1_tmp].im;
          alpha1 = recip(alpha1);
          i = (ix0 - b_i) + 1;
          for (k = ix0; k <= i; k++) {
            f = T[k - 1].im;
            f1 = T[k - 1].re;
            im = alpha1.re * f + alpha1.im * f1;
            f1 = alpha1.re * f1 - alpha1.im * f;
            T[k - 1].re = f1;
            T[k - 1].im = im;
          }

          alpha1.re = beta1;
          alpha1.im = 0.0F;
        }
      }

      T[alpha1_tmp].re = 1.0F;
      T[alpha1_tmp].im = 0.0F;
      jy = (b_i + im1n_tmp) - 1;
      k = in + 1;
      if ((tau[b_i].re != 0.0F) || (tau[b_i].im != 0.0F)) {
        lastv = 2 - b_i;
        c_i = (jy - b_i) + 2;
        while ((lastv + 1 > 0) && ((T[c_i].re == 0.0F) && (T[c_i].im == 0.0F)))
        {
          lastv--;
          c_i--;
        }

        lastc = 4;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          knt = in + lastc;
          ix0 = knt;
          do {
            exitg1 = 0;
            if (ix0 <= knt + (lastv << 2)) {
              if ((T[ix0 - 1].re != 0.0F) || (T[ix0 - 1].im != 0.0F)) {
                exitg1 = 1;
              } else {
                ix0 += 4;
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
        lastv = -1;
        lastc = 0;
      }

      if (lastv + 1 > 0) {
        if (lastc != 0) {
          if (0 <= lastc - 1) {
            memset(&work[0], 0, lastc * sizeof(creal32_T));
          }

          ix = jy;
          i = (in + (lastv << 2)) + 1;
          for (knt = k; knt <= i; knt += 4) {
            xnorm = T[ix].re - 0.0F * T[ix].im;
            beta1 = T[ix].im + 0.0F * T[ix].re;
            c_i = 0;
            i1 = (knt + lastc) - 1;
            for (ix0 = knt; ix0 <= i1; ix0++) {
              f = T[ix0 - 1].re;
              f1 = T[ix0 - 1].im;
              work[c_i].re += f * xnorm - f1 * beta1;
              work[c_i].im += f * beta1 + f1 * xnorm;
              c_i++;
            }

            ix++;
          }
        }

        f = tau[b_i].re;
        f1 = tau[b_i].im;
        if ((!(-tau[b_i].re == 0.0F)) || (!(-tau[b_i].im == 0.0F))) {
          knt = in;
          for (k = 0; k <= lastv; k++) {
            if ((T[jy].re != 0.0F) || (T[jy].im != 0.0F)) {
              xnorm = T[jy].re * -f + T[jy].im * -f1;
              beta1 = T[jy].re * -f1 - T[jy].im * -f;
              ix = 0;
              i = knt + 1;
              i1 = lastc + knt;
              for (c_i = i; c_i <= i1; c_i++) {
                T[c_i - 1].re += work[ix].re * xnorm - work[ix].im * beta1;
                T[c_i - 1].im += work[ix].re * beta1 + work[ix].im * xnorm;
                ix++;
              }
            }

            jy++;
            knt += 4;
          }
        }
      }

      b_tau.re = tau[b_i].re;
      b_tau.im = -tau[b_i].im;
      xzlarf(3 - b_i, 3 - b_i, b_i + im1n_tmp, b_tau, T, (b_i + in) + 2, work);
      T[alpha1_tmp] = alpha1;
    }

    memcpy(&V[0], &T[0], 16U * sizeof(creal32_T));
    for (k = 2; k >= 0; k--) {
      ix0 = (k + 1) << 2;
      for (b_i = 0; b_i <= k; b_i++) {
        i = ix0 + b_i;
        V[i].re = 0.0F;
        V[i].im = 0.0F;
      }

      i = k + 3;
      for (b_i = i; b_i < 5; b_i++) {
        knt = ix0 + b_i;
        V[knt - 1] = V[knt - 5];
      }
    }

    V[1].re = 0.0F;
    V[1].im = 0.0F;
    V[2].re = 0.0F;
    V[2].im = 0.0F;
    V[3].re = 0.0F;
    V[3].im = 0.0F;
    V[0].re = 1.0F;
    V[0].im = 0.0F;
    knt = 2;
    work[0].re = 0.0F;
    work[0].im = 0.0F;
    work[1].re = 0.0F;
    work[1].im = 0.0F;
    work[2].re = 0.0F;
    work[2].im = 0.0F;
    work[3].re = 0.0F;
    work[3].im = 0.0F;
    for (b_i = 2; b_i >= 0; b_i--) {
      c_i = (b_i + (b_i << 2)) + 5;
      if (b_i + 1 < 3) {
        V[c_i].re = 1.0F;
        V[c_i].im = 0.0F;
        xzlarf(3 - b_i, 2 - b_i, c_i + 1, tau[knt], V, c_i + 5, work);
        ix0 = c_i + 2;
        xnorm = -tau[knt].re;
        beta1 = -tau[knt].im;
        i = (c_i - b_i) + 3;
        for (k = ix0; k <= i; k++) {
          f = V[k - 1].im;
          f1 = V[k - 1].re;
          im = xnorm * f + beta1 * f1;
          f1 = xnorm * f1 - beta1 * f;
          V[k - 1].re = f1;
          V[k - 1].im = im;
        }
      }

      V[c_i].re = 1.0F - tau[knt].re;
      V[c_i].im = 0.0F - tau[knt].im;
      for (k = 0; k < b_i; k++) {
        i = (c_i - k) - 1;
        V[i].re = 0.0F;
        V[i].im = 0.0F;
      }

      knt--;
    }

    xhseqr(T, V);
  }
}

/* End of code generation (schur.c) */
