/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzhgeqz.c
 *
 * Code generation for function 'xzhgeqz'
 *
 */

/* Include files */
#include "xzhgeqz.h"
#include "calcMaxwell.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xzlartg.h"
#include <math.h>

/* Function Definitions */
void xzhgeqz(creal32_T A[16], int ilo, int ihi, creal32_T Z[16], int *info,
             creal32_T alpha1[4], creal32_T beta1[4])
{
  float eshift_re;
  float eshift_im;
  creal32_T ctemp;
  float anorm;
  float scale;
  float reAij;
  float sumsq;
  float b_atol;
  boolean_T firstNonZero;
  int j;
  int ctemp_tmp_tmp;
  float ascale;
  int i;
  int jp1;
  float imAij;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  int ifirst;
  int istart;
  float temp2;
  int ilast;
  int ilastm1;
  int iiter;
  boolean_T goto60;
  boolean_T goto70;
  boolean_T goto90;
  int jiter;
  int exitg1;
  boolean_T b_guard1 = false;
  boolean_T guard3 = false;
  boolean_T exitg2;
  creal32_T shift;
  float ad22_re;
  float ad22_im;
  float t1_re;
  float t1_im;
  float t1_im_tmp;
  creal32_T b_ascale;
  int shift_re_tmp;
  int ad22_re_tmp;
  *info = 0;
  alpha1[0].re = 0.0F;
  alpha1[0].im = 0.0F;
  beta1[0].re = 1.0F;
  beta1[0].im = 0.0F;
  alpha1[1].re = 0.0F;
  alpha1[1].im = 0.0F;
  beta1[1].re = 1.0F;
  beta1[1].im = 0.0F;
  alpha1[2].re = 0.0F;
  alpha1[2].im = 0.0F;
  beta1[2].re = 1.0F;
  beta1[2].im = 0.0F;
  alpha1[3].re = 0.0F;
  alpha1[3].im = 0.0F;
  beta1[3].re = 1.0F;
  beta1[3].im = 0.0F;
  eshift_re = 0.0F;
  eshift_im = 0.0F;
  ctemp.re = 0.0F;
  ctemp.im = 0.0F;
  anorm = 0.0F;
  if (ilo <= ihi) {
    scale = 0.0F;
    sumsq = 0.0F;
    firstNonZero = true;
    for (j = ilo; j <= ihi; j++) {
      ctemp_tmp_tmp = j + 1;
      if (ihi < j + 1) {
        ctemp_tmp_tmp = ihi;
      }

      for (i = ilo; i <= ctemp_tmp_tmp; i++) {
        jp1 = (i + ((j - 1) << 2)) - 1;
        reAij = A[jp1].re;
        imAij = A[jp1].im;
        if (reAij != 0.0F) {
          anorm = fabsf(reAij);
          if (firstNonZero) {
            sumsq = 1.0F;
            scale = anorm;
            firstNonZero = false;
          } else if (scale < anorm) {
            temp2 = scale / anorm;
            sumsq = sumsq * temp2 * temp2 + 1.0F;
            scale = anorm;
          } else {
            temp2 = anorm / scale;
            sumsq += temp2 * temp2;
          }
        }

        if (imAij != 0.0F) {
          anorm = fabsf(imAij);
          if (firstNonZero) {
            sumsq = 1.0F;
            scale = anorm;
            firstNonZero = false;
          } else if (scale < anorm) {
            temp2 = scale / anorm;
            sumsq = sumsq * temp2 * temp2 + 1.0F;
            scale = anorm;
          } else {
            temp2 = anorm / scale;
            sumsq += temp2 * temp2;
          }
        }
      }
    }

    anorm = scale * sqrtf(sumsq);
  }

  reAij = 1.1920929E-7F * anorm;
  b_atol = 1.17549435E-38F;
  if (reAij > 1.17549435E-38F) {
    b_atol = reAij;
  }

  reAij = 1.17549435E-38F;
  if (anorm > 1.17549435E-38F) {
    reAij = anorm;
  }

  ascale = 1.0F / reAij;
  firstNonZero = true;
  ctemp_tmp_tmp = ihi + 1;
  for (j = ctemp_tmp_tmp; j < 5; j++) {
    alpha1[j - 1] = A[(j + ((j - 1) << 2)) - 1];
  }

  guard1 = false;
  guard2 = false;
  if (ihi >= ilo) {
    ifirst = ilo;
    istart = ilo;
    ilast = ihi - 1;
    ilastm1 = ihi - 2;
    iiter = 0;
    goto60 = false;
    goto70 = false;
    goto90 = false;
    jiter = 0;
    do {
      exitg1 = 0;
      if (jiter <= 30 * ((ihi - ilo) + 1) - 1) {
        b_guard1 = false;
        if (ilast + 1 == ilo) {
          goto60 = true;
          b_guard1 = true;
        } else {
          ctemp_tmp_tmp = ilast + (ilastm1 << 2);
          if (fabsf(A[ctemp_tmp_tmp].re) + fabsf(A[ctemp_tmp_tmp].im) <= b_atol)
          {
            A[ctemp_tmp_tmp].re = 0.0F;
            A[ctemp_tmp_tmp].im = 0.0F;
            goto60 = true;
            b_guard1 = true;
          } else {
            j = ilastm1;
            guard3 = false;
            exitg2 = false;
            while ((!exitg2) && (j + 1 >= ilo)) {
              if (j + 1 == ilo) {
                guard3 = true;
                exitg2 = true;
              } else {
                ctemp_tmp_tmp = j + ((j - 1) << 2);
                if (fabsf(A[ctemp_tmp_tmp].re) + fabsf(A[ctemp_tmp_tmp].im) <=
                    b_atol) {
                  A[ctemp_tmp_tmp].re = 0.0F;
                  A[ctemp_tmp_tmp].im = 0.0F;
                  guard3 = true;
                  exitg2 = true;
                } else {
                  j--;
                  guard3 = false;
                }
              }
            }

            if (guard3) {
              ifirst = j + 1;
              goto70 = true;
            }

            if (goto70) {
              b_guard1 = true;
            } else {
              alpha1[0].re = rtNaNF;
              alpha1[0].im = 0.0F;
              beta1[0].re = rtNaNF;
              beta1[0].im = 0.0F;
              alpha1[1].re = rtNaNF;
              alpha1[1].im = 0.0F;
              beta1[1].re = rtNaNF;
              beta1[1].im = 0.0F;
              alpha1[2].re = rtNaNF;
              alpha1[2].im = 0.0F;
              beta1[2].re = rtNaNF;
              beta1[2].im = 0.0F;
              alpha1[3].re = rtNaNF;
              alpha1[3].im = 0.0F;
              beta1[3].re = rtNaNF;
              beta1[3].im = 0.0F;
              for (ctemp_tmp_tmp = 0; ctemp_tmp_tmp < 16; ctemp_tmp_tmp++) {
                Z[ctemp_tmp_tmp].re = rtNaNF;
                Z[ctemp_tmp_tmp].im = 0.0F;
              }

              *info = 1;
              exitg1 = 1;
            }
          }
        }

        if (b_guard1) {
          if (goto60) {
            goto60 = false;
            alpha1[ilast] = A[ilast + (ilast << 2)];
            ilast = ilastm1;
            ilastm1--;
            if (ilast + 1 < ilo) {
              firstNonZero = false;
              guard2 = true;
              exitg1 = 1;
            } else {
              iiter = 0;
              eshift_re = 0.0F;
              eshift_im = 0.0F;
              jiter++;
            }
          } else {
            if (goto70) {
              goto70 = false;
              iiter++;
              if (iiter - iiter / 10 * 10 != 0) {
                jp1 = ilastm1 + (ilastm1 << 2);
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0F) {
                  shift.re = anorm / 0.5F;
                  shift.im = 0.0F;
                } else if (anorm == 0.0F) {
                  shift.re = 0.0F;
                  shift.im = reAij / 0.5F;
                } else {
                  shift.re = anorm / 0.5F;
                  shift.im = reAij / 0.5F;
                }

                jp1 = ilast + (ilast << 2);
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0F) {
                  ad22_re = anorm / 0.5F;
                  ad22_im = 0.0F;
                } else if (anorm == 0.0F) {
                  ad22_re = 0.0F;
                  ad22_im = reAij / 0.5F;
                } else {
                  ad22_re = anorm / 0.5F;
                  ad22_im = reAij / 0.5F;
                }

                t1_re = 0.5F * (shift.re + ad22_re);
                t1_im = 0.5F * (shift.im + ad22_im);
                t1_im_tmp = t1_re * t1_im;
                jp1 = ilastm1 + (ilast << 2);
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0F) {
                  imAij = anorm / 0.5F;
                  temp2 = 0.0F;
                } else if (anorm == 0.0F) {
                  imAij = 0.0F;
                  temp2 = reAij / 0.5F;
                } else {
                  imAij = anorm / 0.5F;
                  temp2 = reAij / 0.5F;
                }

                jp1 = ilast + (ilastm1 << 2);
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0F) {
                  sumsq = anorm / 0.5F;
                  anorm = 0.0F;
                } else if (anorm == 0.0F) {
                  sumsq = 0.0F;
                  anorm = reAij / 0.5F;
                } else {
                  sumsq = anorm / 0.5F;
                  anorm = reAij / 0.5F;
                }

                reAij = shift.re * ad22_re - shift.im * ad22_im;
                scale = shift.re * ad22_im + shift.im * ad22_re;
                shift.re = ((t1_re * t1_re - t1_im * t1_im) + (imAij * sumsq -
                  temp2 * anorm)) - reAij;
                shift.im = ((t1_im_tmp + t1_im_tmp) + (imAij * anorm + temp2 *
                  sumsq)) - scale;
                b_sqrt(&shift);
                if ((t1_re - ad22_re) * shift.re + (t1_im - ad22_im) * shift.im <=
                    0.0F) {
                  shift.re += t1_re;
                  shift.im += t1_im;
                } else {
                  shift.re = t1_re - shift.re;
                  shift.im = t1_im - shift.im;
                }
              } else {
                jp1 = ilast + (ilastm1 << 2);
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0F) {
                  imAij = anorm / 0.5F;
                  temp2 = 0.0F;
                } else if (anorm == 0.0F) {
                  imAij = 0.0F;
                  temp2 = reAij / 0.5F;
                } else {
                  imAij = anorm / 0.5F;
                  temp2 = reAij / 0.5F;
                }

                eshift_re += imAij;
                eshift_im += temp2;
                shift.re = eshift_re;
                shift.im = eshift_im;
              }

              j = ilastm1;
              jp1 = ilastm1 + 1;
              exitg2 = false;
              while ((!exitg2) && (j + 1 > ifirst)) {
                istart = j + 1;
                ctemp_tmp_tmp = j << 2;
                i = j + ctemp_tmp_tmp;
                ctemp.re = ascale * A[i].re - shift.re * 0.5F;
                ctemp.im = ascale * A[i].im - shift.im * 0.5F;
                anorm = fabsf(ctemp.re) + fabsf(ctemp.im);
                jp1 += ctemp_tmp_tmp;
                temp2 = ascale * (fabsf(A[jp1].re) + fabsf(A[jp1].im));
                reAij = anorm;
                if (temp2 > anorm) {
                  reAij = temp2;
                }

                if ((reAij < 1.0F) && (reAij != 0.0F)) {
                  anorm /= reAij;
                  temp2 /= reAij;
                }

                ctemp_tmp_tmp = j + ((j - 1) << 2);
                if ((fabsf(A[ctemp_tmp_tmp].re) + fabsf(A[ctemp_tmp_tmp].im)) *
                    temp2 <= anorm * b_atol) {
                  goto90 = true;
                  exitg2 = true;
                } else {
                  jp1 = j;
                  j--;
                }
              }

              if (!goto90) {
                istart = ifirst;
                i = (ifirst + ((ifirst - 1) << 2)) - 1;
                ctemp.re = ascale * A[i].re - shift.re * 0.5F;
                ctemp.im = ascale * A[i].im - shift.im * 0.5F;
              }

              goto90 = false;
              jp1 = istart + ((istart - 1) << 2);
              b_ascale.re = ascale * A[jp1].re;
              b_ascale.im = ascale * A[jp1].im;
              b_xzlartg(ctemp, b_ascale, &anorm, &shift);
              j = istart;
              jp1 = istart - 2;
              while (j < ilast + 1) {
                if (j > istart) {
                  ctemp_tmp_tmp = j + (jp1 << 2);
                  xzlartg(A[ctemp_tmp_tmp - 1], A[ctemp_tmp_tmp], &anorm, &shift,
                          &A[(j + (jp1 << 2)) - 1]);
                  A[ctemp_tmp_tmp].re = 0.0F;
                  A[ctemp_tmp_tmp].im = 0.0F;
                }

                for (jp1 = j; jp1 < 5; jp1++) {
                  shift_re_tmp = j + ((jp1 - 1) << 2);
                  ad22_re_tmp = shift_re_tmp - 1;
                  ad22_re = anorm * A[ad22_re_tmp].re + (shift.re *
                    A[shift_re_tmp].re - shift.im * A[shift_re_tmp].im);
                  ad22_im = anorm * A[ad22_re_tmp].im + (shift.re *
                    A[shift_re_tmp].im + shift.im * A[shift_re_tmp].re);
                  reAij = A[ad22_re_tmp].im;
                  scale = A[ad22_re_tmp].re;
                  A[shift_re_tmp].re = anorm * A[shift_re_tmp].re - (shift.re *
                    A[ad22_re_tmp].re + shift.im * A[ad22_re_tmp].im);
                  A[shift_re_tmp].im = anorm * A[shift_re_tmp].im - (shift.re *
                    reAij - shift.im * scale);
                  A[ad22_re_tmp].re = ad22_re;
                  A[ad22_re_tmp].im = ad22_im;
                }

                shift.re = -shift.re;
                shift.im = -shift.im;
                jp1 = j;
                if (ilast + 1 < j + 2) {
                  jp1 = ilast - 1;
                }

                for (i = 1; i <= jp1 + 2; i++) {
                  shift_re_tmp = (i + ((j - 1) << 2)) - 1;
                  ad22_re_tmp = (i + (j << 2)) - 1;
                  ad22_re = anorm * A[ad22_re_tmp].re + (shift.re *
                    A[shift_re_tmp].re - shift.im * A[shift_re_tmp].im);
                  ad22_im = anorm * A[ad22_re_tmp].im + (shift.re *
                    A[shift_re_tmp].im + shift.im * A[shift_re_tmp].re);
                  reAij = A[ad22_re_tmp].im;
                  scale = A[ad22_re_tmp].re;
                  A[shift_re_tmp].re = anorm * A[shift_re_tmp].re - (shift.re *
                    A[ad22_re_tmp].re + shift.im * A[ad22_re_tmp].im);
                  A[shift_re_tmp].im = anorm * A[shift_re_tmp].im - (shift.re *
                    reAij - shift.im * scale);
                  A[ad22_re_tmp].re = ad22_re;
                  A[ad22_re_tmp].im = ad22_im;
                }

                shift_re_tmp = (j - 1) << 2;
                ad22_re_tmp = j << 2;
                ad22_re = anorm * Z[ad22_re_tmp].re + (shift.re * Z[shift_re_tmp]
                  .re - shift.im * Z[shift_re_tmp].im);
                ad22_im = anorm * Z[ad22_re_tmp].im + (shift.re * Z[shift_re_tmp]
                  .im + shift.im * Z[shift_re_tmp].re);
                reAij = Z[ad22_re_tmp].im;
                scale = Z[ad22_re_tmp].re;
                Z[shift_re_tmp].re = anorm * Z[shift_re_tmp].re - (shift.re *
                  Z[ad22_re_tmp].re + shift.im * Z[ad22_re_tmp].im);
                Z[shift_re_tmp].im = anorm * Z[shift_re_tmp].im - (shift.re *
                  reAij - shift.im * scale);
                Z[ad22_re_tmp].re = ad22_re;
                Z[ad22_re_tmp].im = ad22_im;
                jp1 = shift_re_tmp + 1;
                ctemp_tmp_tmp = ad22_re_tmp + 1;
                ad22_re = anorm * Z[ctemp_tmp_tmp].re + (shift.re * Z[jp1].re -
                  shift.im * Z[jp1].im);
                ad22_im = anorm * Z[ctemp_tmp_tmp].im + (shift.re * Z[jp1].im +
                  shift.im * Z[jp1].re);
                reAij = Z[ctemp_tmp_tmp].im;
                scale = Z[ctemp_tmp_tmp].re;
                Z[jp1].re = anorm * Z[jp1].re - (shift.re * Z[ctemp_tmp_tmp].re
                  + shift.im * Z[ctemp_tmp_tmp].im);
                Z[jp1].im = anorm * Z[jp1].im - (shift.re * reAij - shift.im *
                  scale);
                Z[ctemp_tmp_tmp].re = ad22_re;
                Z[ctemp_tmp_tmp].im = ad22_im;
                jp1 = shift_re_tmp + 2;
                ctemp_tmp_tmp = ad22_re_tmp + 2;
                ad22_re = anorm * Z[ctemp_tmp_tmp].re + (shift.re * Z[jp1].re -
                  shift.im * Z[jp1].im);
                ad22_im = anorm * Z[ctemp_tmp_tmp].im + (shift.re * Z[jp1].im +
                  shift.im * Z[jp1].re);
                reAij = Z[ctemp_tmp_tmp].im;
                scale = Z[ctemp_tmp_tmp].re;
                Z[jp1].re = anorm * Z[jp1].re - (shift.re * Z[ctemp_tmp_tmp].re
                  + shift.im * Z[ctemp_tmp_tmp].im);
                Z[jp1].im = anorm * Z[jp1].im - (shift.re * reAij - shift.im *
                  scale);
                Z[ctemp_tmp_tmp].re = ad22_re;
                Z[ctemp_tmp_tmp].im = ad22_im;
                shift_re_tmp += 3;
                ad22_re_tmp += 3;
                ad22_re = anorm * Z[ad22_re_tmp].re + (shift.re * Z[shift_re_tmp]
                  .re - shift.im * Z[shift_re_tmp].im);
                ad22_im = anorm * Z[ad22_re_tmp].im + (shift.re * Z[shift_re_tmp]
                  .im + shift.im * Z[shift_re_tmp].re);
                reAij = Z[ad22_re_tmp].im;
                scale = Z[ad22_re_tmp].re;
                Z[shift_re_tmp].re = anorm * Z[shift_re_tmp].re - (shift.re *
                  Z[ad22_re_tmp].re + shift.im * Z[ad22_re_tmp].im);
                Z[shift_re_tmp].im = anorm * Z[shift_re_tmp].im - (shift.re *
                  reAij - shift.im * scale);
                Z[ad22_re_tmp].re = ad22_re;
                Z[ad22_re_tmp].im = ad22_im;
                jp1 = j - 1;
                j++;
              }
            }

            jiter++;
          }
        }
      } else {
        guard2 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  } else {
    guard1 = true;
  }

  if (guard2) {
    if (firstNonZero) {
      *info = ilast + 1;
      for (jp1 = 0; jp1 <= ilast; jp1++) {
        alpha1[jp1].re = rtNaNF;
        alpha1[jp1].im = 0.0F;
        beta1[jp1].re = rtNaNF;
        beta1[jp1].im = 0.0F;
      }

      for (ctemp_tmp_tmp = 0; ctemp_tmp_tmp < 16; ctemp_tmp_tmp++) {
        Z[ctemp_tmp_tmp].re = rtNaNF;
        Z[ctemp_tmp_tmp].im = 0.0F;
      }
    } else {
      guard1 = true;
    }
  }

  if (guard1) {
    for (j = 0; j <= ilo - 2; j++) {
      alpha1[j] = A[j + (j << 2)];
    }
  }
}

/* End of code generation (xzhgeqz.c) */
