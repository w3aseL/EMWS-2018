/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xztgevc.c
 *
 * Code generation for function 'xztgevc'
 *
 */

/* Include files */
#include "xztgevc.h"
#include "calcMaxwell.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void xztgevc(const creal32_T A[16], creal32_T V[16])
{
  float rworka[4];
  float anorm;
  int j;
  float xmx;
  int i;
  int re_tmp;
  float ascale;
  float d_re;
  int je;
  int x_tmp_tmp_tmp;
  float temp;
  float salpha_re;
  float salpha_im;
  float acoeff;
  boolean_T lscalea;
  float z;
  boolean_T lscaleb;
  float scale;
  creal32_T work1[4];
  float dmin;
  int b_i;
  creal32_T work2[4];
  int b_j;
  int d_re_tmp_tmp;
  float d_im;
  float brm;
  rworka[0] = 0.0F;
  rworka[1] = 0.0F;
  rworka[2] = 0.0F;
  rworka[3] = 0.0F;
  anorm = fabsf(A[0].re) + fabsf(A[0].im);
  for (j = 0; j < 3; j++) {
    for (i = 0; i <= j; i++) {
      re_tmp = i + ((j + 1) << 2);
      rworka[j + 1] += fabsf(A[re_tmp].re) + fabsf(A[re_tmp].im);
    }

    i = (j + ((j + 1) << 2)) + 1;
    d_re = rworka[j + 1] + (fabsf(A[i].re) + fabsf(A[i].im));
    if (d_re > anorm) {
      anorm = d_re;
    }
  }

  xmx = anorm;
  if (1.17549435E-38F > anorm) {
    xmx = 1.17549435E-38F;
  }

  ascale = 1.0F / xmx;
  for (je = 0; je < 4; je++) {
    x_tmp_tmp_tmp = (3 - je) << 2;
    i = (x_tmp_tmp_tmp - je) + 3;
    xmx = (fabsf(A[i].re) + fabsf(A[i].im)) * ascale;
    if (1.0F > xmx) {
      xmx = 1.0F;
    }

    temp = 1.0F / xmx;
    salpha_re = ascale * (temp * A[i].re);
    salpha_im = ascale * (temp * A[i].im);
    acoeff = temp * ascale;
    if ((temp >= 1.17549435E-38F) && (acoeff < 3.94430453E-31F)) {
      lscalea = true;
    } else {
      lscalea = false;
    }

    z = fabsf(salpha_re) + fabsf(salpha_im);
    if ((z >= 1.17549435E-38F) && (z < 3.94430453E-31F)) {
      lscaleb = true;
    } else {
      lscaleb = false;
    }

    scale = 1.0F;
    if (lscalea) {
      xmx = anorm;
      if (2.5353012E+30F < anorm) {
        xmx = 2.5353012E+30F;
      }

      scale = 3.94430453E-31F / temp * xmx;
    }

    if (lscaleb) {
      d_re = 3.94430453E-31F / z;
      if (d_re > scale) {
        scale = d_re;
      }
    }

    if (lscalea || lscaleb) {
      xmx = acoeff;
      if (1.0F > acoeff) {
        xmx = 1.0F;
      }

      if (z > xmx) {
        xmx = z;
      }

      d_re = 1.0F / (1.17549435E-38F * xmx);
      if (d_re < scale) {
        scale = d_re;
      }

      if (lscalea) {
        acoeff = ascale * (scale * temp);
      } else {
        acoeff *= scale;
      }

      salpha_re *= scale;
      salpha_im *= scale;
    }

    work1[0].re = 0.0F;
    work1[0].im = 0.0F;
    work1[1].re = 0.0F;
    work1[1].im = 0.0F;
    work1[2].re = 0.0F;
    work1[2].im = 0.0F;
    work1[3].re = 0.0F;
    work1[3].im = 0.0F;
    work1[3 - je].re = 1.0F;
    work1[3 - je].im = 0.0F;
    d_re = 1.1920929E-7F * (fabsf(salpha_re) + fabsf(salpha_im));
    dmin = 1.1920929E-7F * acoeff * anorm;
    if (d_re > dmin) {
      dmin = d_re;
    }

    if (1.17549435E-38F > dmin) {
      dmin = 1.17549435E-38F;
    }

    b_i = 2 - je;
    for (re_tmp = 0; re_tmp <= b_i; re_tmp++) {
      i = re_tmp + x_tmp_tmp_tmp;
      work1[re_tmp].re = acoeff * A[i].re;
      work1[re_tmp].im = acoeff * A[i].im;
    }

    work1[3 - je].re = 1.0F;
    work1[3 - je].im = 0.0F;
    b_i = (int)(((-1.0 - ((-(double)je + 4.0) - 1.0)) + 1.0) / -1.0);
    for (j = 0; j < b_i; j++) {
      b_j = 2 - (je + j);
      d_re_tmp_tmp = b_j << 2;
      i = b_j + d_re_tmp_tmp;
      d_re = acoeff * A[i].re - salpha_re;
      d_im = acoeff * A[i].im - salpha_im;
      if (fabsf(d_re) + fabsf(d_im) <= dmin) {
        d_re = dmin;
        d_im = 0.0F;
      }

      brm = fabsf(d_re);
      scale = fabsf(d_im);
      xmx = brm + scale;
      if (xmx < 1.0F) {
        z = fabsf(work1[b_j].re) + fabsf(work1[b_j].im);
        if (z >= 2.12676479E+37F * xmx) {
          temp = 1.0F / z;
          i = 3 - je;
          for (re_tmp = 0; re_tmp <= i; re_tmp++) {
            work1[re_tmp].re *= temp;
            work1[re_tmp].im *= temp;
          }
        }
      }

      if (d_im == 0.0F) {
        if (-work1[b_j].im == 0.0F) {
          scale = -work1[b_j].re / d_re;
          xmx = 0.0F;
        } else if (-work1[b_j].re == 0.0F) {
          scale = 0.0F;
          xmx = -work1[b_j].im / d_re;
        } else {
          scale = -work1[b_j].re / d_re;
          xmx = -work1[b_j].im / d_re;
        }
      } else if (d_re == 0.0F) {
        if (-work1[b_j].re == 0.0F) {
          scale = -work1[b_j].im / d_im;
          xmx = 0.0F;
        } else if (-work1[b_j].im == 0.0F) {
          scale = 0.0F;
          xmx = -(-work1[b_j].re / d_im);
        } else {
          scale = -work1[b_j].im / d_im;
          xmx = -(-work1[b_j].re / d_im);
        }
      } else if (brm > scale) {
        z = d_im / d_re;
        xmx = d_re + z * d_im;
        scale = (-work1[b_j].re + z * -work1[b_j].im) / xmx;
        xmx = (-work1[b_j].im - z * -work1[b_j].re) / xmx;
      } else if (scale == brm) {
        if (d_re > 0.0F) {
          z = 0.5F;
        } else {
          z = -0.5F;
        }

        if (d_im > 0.0F) {
          xmx = 0.5F;
        } else {
          xmx = -0.5F;
        }

        scale = (-work1[b_j].re * z + -work1[b_j].im * xmx) / brm;
        xmx = (-work1[b_j].im * z - -work1[b_j].re * xmx) / brm;
      } else {
        z = d_re / d_im;
        xmx = d_im + z * d_re;
        scale = (z * -work1[b_j].re + -work1[b_j].im) / xmx;
        xmx = (z * -work1[b_j].im - (-work1[b_j].re)) / xmx;
      }

      work1[b_j].re = scale;
      work1[b_j].im = xmx;
      if (b_j + 1 > 1) {
        if (fabsf(work1[b_j].re) + fabsf(work1[b_j].im) > 1.0F) {
          temp = 1.0F / (fabsf(work1[b_j].re) + fabsf(work1[b_j].im));
          if (acoeff * rworka[b_j] >= 2.12676479E+37F * temp) {
            i = 3 - je;
            for (re_tmp = 0; re_tmp <= i; re_tmp++) {
              work1[re_tmp].re *= temp;
              work1[re_tmp].im *= temp;
            }
          }
        }

        d_re = acoeff * work1[b_j].re;
        d_im = acoeff * work1[b_j].im;
        for (re_tmp = 0; re_tmp < b_j; re_tmp++) {
          i = re_tmp + d_re_tmp_tmp;
          work1[re_tmp].re += d_re * A[i].re - d_im * A[i].im;
          work1[re_tmp].im += d_re * A[i].im + d_im * A[i].re;
        }
      }
    }

    work2[0].re = 0.0F;
    work2[0].im = 0.0F;
    work2[1].re = 0.0F;
    work2[1].im = 0.0F;
    work2[2].re = 0.0F;
    work2[2].im = 0.0F;
    work2[3].re = 0.0F;
    work2[3].im = 0.0F;
    b_i = 3 - je;
    for (i = 0; i <= b_i; i++) {
      re_tmp = i << 2;
      work2[0].re += V[re_tmp].re * work1[i].re - V[re_tmp].im * work1[i].im;
      work2[0].im += V[re_tmp].re * work1[i].im + V[re_tmp].im * work1[i].re;
      b_j = re_tmp + 1;
      work2[1].re += V[b_j].re * work1[i].re - V[b_j].im * work1[i].im;
      work2[1].im += V[b_j].re * work1[i].im + V[b_j].im * work1[i].re;
      b_j = re_tmp + 2;
      work2[2].re += V[b_j].re * work1[i].re - V[b_j].im * work1[i].im;
      work2[2].im += V[b_j].re * work1[i].im + V[b_j].im * work1[i].re;
      re_tmp += 3;
      work2[3].re += V[re_tmp].re * work1[i].re - V[re_tmp].im * work1[i].im;
      work2[3].im += V[re_tmp].re * work1[i].im + V[re_tmp].im * work1[i].re;
    }

    xmx = fabsf(work2[0].re) + fabsf(work2[0].im);
    d_re = fabsf(work2[1].re) + fabsf(work2[1].im);
    if (d_re > xmx) {
      xmx = d_re;
    }

    d_re = fabsf(work2[2].re) + fabsf(work2[2].im);
    if (d_re > xmx) {
      xmx = d_re;
    }

    d_re = fabsf(work2[3].re) + fabsf(work2[3].im);
    if (d_re > xmx) {
      xmx = d_re;
    }

    if (xmx > 1.17549435E-38F) {
      temp = 1.0F / xmx;
      V[x_tmp_tmp_tmp].re = temp * work2[0].re;
      V[x_tmp_tmp_tmp].im = temp * work2[0].im;
      b_i = x_tmp_tmp_tmp + 1;
      V[b_i].re = temp * work2[1].re;
      V[b_i].im = temp * work2[1].im;
      b_i = x_tmp_tmp_tmp + 2;
      V[b_i].re = temp * work2[2].re;
      V[b_i].im = temp * work2[2].im;
      b_i = x_tmp_tmp_tmp + 3;
      V[b_i].re = temp * work2[3].re;
      V[b_i].im = temp * work2[3].im;
    } else {
      V[x_tmp_tmp_tmp].re = 0.0F;
      V[x_tmp_tmp_tmp].im = 0.0F;
      b_i = x_tmp_tmp_tmp + 1;
      V[b_i].re = 0.0F;
      V[b_i].im = 0.0F;
      b_i = x_tmp_tmp_tmp + 2;
      V[b_i].re = 0.0F;
      V[b_i].im = 0.0F;
      b_i = x_tmp_tmp_tmp + 3;
      V[b_i].re = 0.0F;
      V[b_i].im = 0.0F;
    }
  }
}

/* End of code generation (xztgevc.c) */
