/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * calcMaxwell.c
 *
 * Code generation for function 'calcMaxwell'
 *
 */

/* Include files */
#include "calcMaxwell.h"
#include "calcMaxwell_data.h"
#include "calcMaxwell_initialize.h"
#include "rt_nonfinite.h"
#include "schur.h"
#include "xzggev.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void calcMaxwell(const float u[9], const float e[9], double w, double k1, double
                 k2, creal32_T eigvec[16], creal32_T eigval[16], creal32_T
                 maxMat[16])
{
  float scale;
  float colnorm;
  float absxk;
  double d;
  float t;
  boolean_T p;
  int info;
  int j;
  boolean_T exitg2;
  int i;
  creal32_T At[16];
  creal32_T alpha1[4];
  creal32_T beta1[4];
  int exitg1;
  int maxMat_tmp;
  if (isInitialized_calcMaxwell == false) {
    calcMaxwell_initialize();
  }

  /* Author: Michael <michael@sheppardsoftware> */
  /* Created: 2019-03-25 */
  /* Function that takes values of mu, epsilon, omega, and k */
  /* returns eigen values and vectors of the associated Maxwell matrix */
  scale = (float)(k1 * k2);
  colnorm = scale / e[8];
  scale /= u[8];
  absxk = (-(e[2] * (float)k1 / e[8]) - (float)k2 * u[7] / u[8]) * (float)w;
  maxMat[0].re = absxk * 0.0F;
  maxMat[0].im = absxk;
  absxk = (-(e[5] * (float)k1 / e[8]) + (float)k1 * u[7] / u[8]) * (float)w;
  maxMat[4].re = absxk * 0.0F;
  maxMat[4].im = absxk;
  absxk = ((colnorm + u[1]) - u[7] * u[2] / u[8]) * (float)w;
  maxMat[8].re = absxk * 0.0F;
  maxMat[8].im = absxk;
  d = k1 * k1;
  absxk = (((float)-d / e[8] + u[4]) - u[7] * u[5] / u[8]) * (float)w;
  maxMat[12].re = absxk * 0.0F;
  maxMat[12].im = absxk;
  absxk = (-(e[2] * (float)k2 / e[8]) - (float)k2 * (u[6] / u[8])) * (float)w;
  maxMat[1].re = absxk * 0.0F;
  maxMat[1].im = absxk;
  absxk = (-(e[5] * (float)k2 / e[8]) - (float)k1 * u[6] / u[8]) * (float)w;
  maxMat[5].re = absxk * 0.0F;
  maxMat[5].im = absxk;
  absxk = (float)(k2 * k2);
  t = ((absxk / e[8] - u[0]) + u[6] * u[2] / u[8]) * (float)w;
  maxMat[9].re = t * 0.0F;
  maxMat[9].im = t;
  t = ((-colnorm - u[3]) + u[6] * u[5] / u[8]) * (float)w;
  maxMat[13].re = t * 0.0F;
  maxMat[13].im = t;
  t = ((-e[1] + e[7] * e[2] / e[8]) - scale) * (float)w;
  maxMat[2].re = t * 0.0F;
  maxMat[2].im = t;
  t = ((-e[4] + e[7] * e[5] / e[8]) + (float)d / u[8]) * (float)w;
  maxMat[6].re = t * 0.0F;
  maxMat[6].im = t;
  t = (-(e[7] * (float)k2 / e[8]) - (float)k1 * u[2] / u[8]) * (float)w;
  maxMat[10].re = t * 0.0F;
  maxMat[10].im = t;
  t = (e[7] * (float)k1 / e[8] - (float)k1 * u[5] / u[8]) * (float)w;
  maxMat[14].re = t * 0.0F;
  maxMat[14].im = t;
  absxk = ((e[0] - e[6] * e[2] / e[8]) - absxk / u[8]) * (float)w;
  maxMat[3].re = absxk * 0.0F;
  maxMat[3].im = absxk;
  absxk = ((e[3] - e[6] * e[5] / e[8]) + scale) * (float)w;
  maxMat[7].re = absxk * 0.0F;
  maxMat[7].im = absxk;
  absxk = (e[6] * (float)k2 / e[8] - (float)k2 * u[2] / u[8]) * (float)w;
  maxMat[11].re = absxk * 0.0F;
  maxMat[11].im = absxk;
  absxk = (-(e[6] * (float)k1 / e[8]) - (float)k2 * u[5] / u[8]) * (float)w;
  maxMat[15].re = absxk * 0.0F;
  maxMat[15].im = absxk;
  p = true;
  for (info = 0; info < 16; info++) {
    if ((!p) || (rtIsInfF(maxMat[info].im) || (rtIsNaNF(maxMat[info].re) ||
          rtIsNaNF(maxMat[info].im)))) {
      p = false;
    }
  }

  if (!p) {
    for (info = 0; info < 16; info++) {
      eigvec[info].re = rtNaNF;
      eigvec[info].im = 0.0F;
      eigval[info].re = 0.0F;
      eigval[info].im = 0.0F;
    }

    eigval[0].re = rtNaNF;
    eigval[0].im = 0.0F;
    eigval[5].re = rtNaNF;
    eigval[5].im = 0.0F;
    eigval[10].re = rtNaNF;
    eigval[10].im = 0.0F;
    eigval[15].re = rtNaNF;
    eigval[15].im = 0.0F;
  } else {
    p = true;
    j = 0;
    exitg2 = false;
    while ((!exitg2) && (j < 4)) {
      i = 0;
      do {
        exitg1 = 0;
        if (i <= j) {
          info = j + (i << 2);
          maxMat_tmp = i + (j << 2);
          if ((!(maxMat[maxMat_tmp].re == maxMat[info].re)) ||
              (!(maxMat[maxMat_tmp].im == -maxMat[info].im))) {
            p = false;
            exitg1 = 1;
          } else {
            i++;
          }
        } else {
          j++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }

    if (p) {
      schur(maxMat, eigvec, eigval);
      eigval[0].im = 0.0F;
      for (j = 0; j < 3; j++) {
        info = (j + 1) << 2;
        eigval[(j + info) + 1].im = 0.0F;
        maxMat_tmp = (j + (j << 2)) + 1;
        eigval[maxMat_tmp].re = 0.0F;
        eigval[maxMat_tmp].im = 0.0F;
        for (i = 0; i <= j; i++) {
          maxMat_tmp = i + info;
          eigval[maxMat_tmp].re = 0.0F;
          eigval[maxMat_tmp].im = 0.0F;
        }
      }
    } else {
      memcpy(&At[0], &maxMat[0], 16U * sizeof(creal32_T));
      xzggev(At, &info, alpha1, beta1, eigvec);
      colnorm = 0.0F;
      scale = 1.29246971E-26F;
      for (info = 1; info < 5; info++) {
        absxk = fabsf(eigvec[info - 1].re);
        if (absxk > scale) {
          t = scale / absxk;
          colnorm = colnorm * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          colnorm += t * t;
        }

        absxk = fabsf(eigvec[info - 1].im);
        if (absxk > scale) {
          t = scale / absxk;
          colnorm = colnorm * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          colnorm += t * t;
        }
      }

      colnorm = scale * sqrtf(colnorm);
      for (j = 1; j < 5; j++) {
        scale = eigvec[j - 1].re;
        t = eigvec[j - 1].im;
        if (t == 0.0F) {
          absxk = scale / colnorm;
          scale = 0.0F;
        } else if (scale == 0.0F) {
          absxk = 0.0F;
          scale = t / colnorm;
        } else {
          absxk = scale / colnorm;
          scale = t / colnorm;
        }

        eigvec[j - 1].re = absxk;
        eigvec[j - 1].im = scale;
      }

      colnorm = 0.0F;
      scale = 1.29246971E-26F;
      for (info = 5; info < 9; info++) {
        absxk = fabsf(eigvec[info - 1].re);
        if (absxk > scale) {
          t = scale / absxk;
          colnorm = colnorm * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          colnorm += t * t;
        }

        absxk = fabsf(eigvec[info - 1].im);
        if (absxk > scale) {
          t = scale / absxk;
          colnorm = colnorm * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          colnorm += t * t;
        }
      }

      colnorm = scale * sqrtf(colnorm);
      for (j = 5; j < 9; j++) {
        scale = eigvec[j - 1].re;
        t = eigvec[j - 1].im;
        if (t == 0.0F) {
          absxk = scale / colnorm;
          scale = 0.0F;
        } else if (scale == 0.0F) {
          absxk = 0.0F;
          scale = t / colnorm;
        } else {
          absxk = scale / colnorm;
          scale = t / colnorm;
        }

        eigvec[j - 1].re = absxk;
        eigvec[j - 1].im = scale;
      }

      colnorm = 0.0F;
      scale = 1.29246971E-26F;
      for (info = 9; info < 13; info++) {
        absxk = fabsf(eigvec[info - 1].re);
        if (absxk > scale) {
          t = scale / absxk;
          colnorm = colnorm * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          colnorm += t * t;
        }

        absxk = fabsf(eigvec[info - 1].im);
        if (absxk > scale) {
          t = scale / absxk;
          colnorm = colnorm * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          colnorm += t * t;
        }
      }

      colnorm = scale * sqrtf(colnorm);
      for (j = 9; j < 13; j++) {
        scale = eigvec[j - 1].re;
        t = eigvec[j - 1].im;
        if (t == 0.0F) {
          absxk = scale / colnorm;
          scale = 0.0F;
        } else if (scale == 0.0F) {
          absxk = 0.0F;
          scale = t / colnorm;
        } else {
          absxk = scale / colnorm;
          scale = t / colnorm;
        }

        eigvec[j - 1].re = absxk;
        eigvec[j - 1].im = scale;
      }

      colnorm = 0.0F;
      scale = 1.29246971E-26F;
      for (info = 13; info < 17; info++) {
        absxk = fabsf(eigvec[info - 1].re);
        if (absxk > scale) {
          t = scale / absxk;
          colnorm = colnorm * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          colnorm += t * t;
        }

        absxk = fabsf(eigvec[info - 1].im);
        if (absxk > scale) {
          t = scale / absxk;
          colnorm = colnorm * t * t + 1.0F;
          scale = absxk;
        } else {
          t = absxk / scale;
          colnorm += t * t;
        }
      }

      colnorm = scale * sqrtf(colnorm);
      for (j = 13; j < 17; j++) {
        scale = eigvec[j - 1].re;
        t = eigvec[j - 1].im;
        if (t == 0.0F) {
          absxk = scale / colnorm;
          scale = 0.0F;
        } else if (scale == 0.0F) {
          absxk = 0.0F;
          scale = t / colnorm;
        } else {
          absxk = scale / colnorm;
          scale = t / colnorm;
        }

        eigvec[j - 1].re = absxk;
        eigvec[j - 1].im = scale;
      }

      memset(&eigval[0], 0, 16U * sizeof(creal32_T));
      if (beta1[0].im == 0.0F) {
        if (alpha1[0].im == 0.0F) {
          eigval[0].re = alpha1[0].re / beta1[0].re;
          eigval[0].im = 0.0F;
        } else if (alpha1[0].re == 0.0F) {
          eigval[0].re = 0.0F;
          eigval[0].im = alpha1[0].im / beta1[0].re;
        } else {
          eigval[0].re = alpha1[0].re / beta1[0].re;
          eigval[0].im = alpha1[0].im / beta1[0].re;
        }
      } else if (beta1[0].re == 0.0F) {
        if (alpha1[0].re == 0.0F) {
          eigval[0].re = alpha1[0].im / beta1[0].im;
          eigval[0].im = 0.0F;
        } else if (alpha1[0].im == 0.0F) {
          eigval[0].re = 0.0F;
          eigval[0].im = -(alpha1[0].re / beta1[0].im);
        } else {
          eigval[0].re = alpha1[0].im / beta1[0].im;
          eigval[0].im = -(alpha1[0].re / beta1[0].im);
        }
      } else {
        t = fabsf(beta1[0].re);
        scale = fabsf(beta1[0].im);
        if (t > scale) {
          scale = beta1[0].im / beta1[0].re;
          absxk = beta1[0].re + scale * beta1[0].im;
          eigval[0].re = (alpha1[0].re + scale * alpha1[0].im) / absxk;
          eigval[0].im = (alpha1[0].im - scale * alpha1[0].re) / absxk;
        } else if (scale == t) {
          if (beta1[0].re > 0.0F) {
            scale = 0.5F;
          } else {
            scale = -0.5F;
          }

          if (beta1[0].im > 0.0F) {
            absxk = 0.5F;
          } else {
            absxk = -0.5F;
          }

          eigval[0].re = (alpha1[0].re * scale + alpha1[0].im * absxk) / t;
          eigval[0].im = (alpha1[0].im * scale - alpha1[0].re * absxk) / t;
        } else {
          scale = beta1[0].re / beta1[0].im;
          absxk = beta1[0].im + scale * beta1[0].re;
          eigval[0].re = (scale * alpha1[0].re + alpha1[0].im) / absxk;
          eigval[0].im = (scale * alpha1[0].im - alpha1[0].re) / absxk;
        }
      }

      if (beta1[1].im == 0.0F) {
        if (alpha1[1].im == 0.0F) {
          eigval[5].re = alpha1[1].re / beta1[1].re;
          eigval[5].im = 0.0F;
        } else if (alpha1[1].re == 0.0F) {
          eigval[5].re = 0.0F;
          eigval[5].im = alpha1[1].im / beta1[1].re;
        } else {
          eigval[5].re = alpha1[1].re / beta1[1].re;
          eigval[5].im = alpha1[1].im / beta1[1].re;
        }
      } else if (beta1[1].re == 0.0F) {
        if (alpha1[1].re == 0.0F) {
          eigval[5].re = alpha1[1].im / beta1[1].im;
          eigval[5].im = 0.0F;
        } else if (alpha1[1].im == 0.0F) {
          eigval[5].re = 0.0F;
          eigval[5].im = -(alpha1[1].re / beta1[1].im);
        } else {
          eigval[5].re = alpha1[1].im / beta1[1].im;
          eigval[5].im = -(alpha1[1].re / beta1[1].im);
        }
      } else {
        t = fabsf(beta1[1].re);
        scale = fabsf(beta1[1].im);
        if (t > scale) {
          scale = beta1[1].im / beta1[1].re;
          absxk = beta1[1].re + scale * beta1[1].im;
          eigval[5].re = (alpha1[1].re + scale * alpha1[1].im) / absxk;
          eigval[5].im = (alpha1[1].im - scale * alpha1[1].re) / absxk;
        } else if (scale == t) {
          if (beta1[1].re > 0.0F) {
            scale = 0.5F;
          } else {
            scale = -0.5F;
          }

          if (beta1[1].im > 0.0F) {
            absxk = 0.5F;
          } else {
            absxk = -0.5F;
          }

          eigval[5].re = (alpha1[1].re * scale + alpha1[1].im * absxk) / t;
          eigval[5].im = (alpha1[1].im * scale - alpha1[1].re * absxk) / t;
        } else {
          scale = beta1[1].re / beta1[1].im;
          absxk = beta1[1].im + scale * beta1[1].re;
          eigval[5].re = (scale * alpha1[1].re + alpha1[1].im) / absxk;
          eigval[5].im = (scale * alpha1[1].im - alpha1[1].re) / absxk;
        }
      }

      if (beta1[2].im == 0.0F) {
        if (alpha1[2].im == 0.0F) {
          eigval[10].re = alpha1[2].re / beta1[2].re;
          eigval[10].im = 0.0F;
        } else if (alpha1[2].re == 0.0F) {
          eigval[10].re = 0.0F;
          eigval[10].im = alpha1[2].im / beta1[2].re;
        } else {
          eigval[10].re = alpha1[2].re / beta1[2].re;
          eigval[10].im = alpha1[2].im / beta1[2].re;
        }
      } else if (beta1[2].re == 0.0F) {
        if (alpha1[2].re == 0.0F) {
          eigval[10].re = alpha1[2].im / beta1[2].im;
          eigval[10].im = 0.0F;
        } else if (alpha1[2].im == 0.0F) {
          eigval[10].re = 0.0F;
          eigval[10].im = -(alpha1[2].re / beta1[2].im);
        } else {
          eigval[10].re = alpha1[2].im / beta1[2].im;
          eigval[10].im = -(alpha1[2].re / beta1[2].im);
        }
      } else {
        t = fabsf(beta1[2].re);
        scale = fabsf(beta1[2].im);
        if (t > scale) {
          scale = beta1[2].im / beta1[2].re;
          absxk = beta1[2].re + scale * beta1[2].im;
          eigval[10].re = (alpha1[2].re + scale * alpha1[2].im) / absxk;
          eigval[10].im = (alpha1[2].im - scale * alpha1[2].re) / absxk;
        } else if (scale == t) {
          if (beta1[2].re > 0.0F) {
            scale = 0.5F;
          } else {
            scale = -0.5F;
          }

          if (beta1[2].im > 0.0F) {
            absxk = 0.5F;
          } else {
            absxk = -0.5F;
          }

          eigval[10].re = (alpha1[2].re * scale + alpha1[2].im * absxk) / t;
          eigval[10].im = (alpha1[2].im * scale - alpha1[2].re * absxk) / t;
        } else {
          scale = beta1[2].re / beta1[2].im;
          absxk = beta1[2].im + scale * beta1[2].re;
          eigval[10].re = (scale * alpha1[2].re + alpha1[2].im) / absxk;
          eigval[10].im = (scale * alpha1[2].im - alpha1[2].re) / absxk;
        }
      }

      if (beta1[3].im == 0.0F) {
        if (alpha1[3].im == 0.0F) {
          eigval[15].re = alpha1[3].re / beta1[3].re;
          eigval[15].im = 0.0F;
        } else if (alpha1[3].re == 0.0F) {
          eigval[15].re = 0.0F;
          eigval[15].im = alpha1[3].im / beta1[3].re;
        } else {
          eigval[15].re = alpha1[3].re / beta1[3].re;
          eigval[15].im = alpha1[3].im / beta1[3].re;
        }
      } else if (beta1[3].re == 0.0F) {
        if (alpha1[3].re == 0.0F) {
          eigval[15].re = alpha1[3].im / beta1[3].im;
          eigval[15].im = 0.0F;
        } else if (alpha1[3].im == 0.0F) {
          eigval[15].re = 0.0F;
          eigval[15].im = -(alpha1[3].re / beta1[3].im);
        } else {
          eigval[15].re = alpha1[3].im / beta1[3].im;
          eigval[15].im = -(alpha1[3].re / beta1[3].im);
        }
      } else {
        t = fabsf(beta1[3].re);
        scale = fabsf(beta1[3].im);
        if (t > scale) {
          scale = beta1[3].im / beta1[3].re;
          absxk = beta1[3].re + scale * beta1[3].im;
          eigval[15].re = (alpha1[3].re + scale * alpha1[3].im) / absxk;
          eigval[15].im = (alpha1[3].im - scale * alpha1[3].re) / absxk;
        } else if (scale == t) {
          if (beta1[3].re > 0.0F) {
            scale = 0.5F;
          } else {
            scale = -0.5F;
          }

          if (beta1[3].im > 0.0F) {
            absxk = 0.5F;
          } else {
            absxk = -0.5F;
          }

          eigval[15].re = (alpha1[3].re * scale + alpha1[3].im * absxk) / t;
          eigval[15].im = (alpha1[3].im * scale - alpha1[3].re * absxk) / t;
        } else {
          scale = beta1[3].re / beta1[3].im;
          absxk = beta1[3].im + scale * beta1[3].re;
          eigval[15].re = (scale * alpha1[3].re + alpha1[3].im) / absxk;
          eigval[15].im = (scale * alpha1[3].im - alpha1[3].re) / absxk;
        }
      }
    }
  }
}

/* End of code generation (calcMaxwell.c) */
