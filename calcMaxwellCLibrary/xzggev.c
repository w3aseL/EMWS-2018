/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzggev.c
 *
 * Code generation for function 'xzggev'
 *
 */

/* Include files */
#include "xzggev.h"
#include "calcMaxwell.h"
#include "calcMaxwell_rtwutil.h"
#include "rt_nonfinite.h"
#include "xhseqr.h"
#include "xzhgeqz.h"
#include "xzlartg.h"
#include "xztgevc.h"
#include <math.h>

/* Function Definitions */
void xzggev(creal32_T A[16], int *info, creal32_T alpha1[4], creal32_T beta1[4],
            creal32_T V[16])
{
  float anrm;
  int nzcount;
  boolean_T exitg1;
  float absxk;
  boolean_T ilascl;
  float anrmto;
  boolean_T guard1 = false;
  int rscale[4];
  float ctoc;
  boolean_T notdone;
  int ilo;
  float stemp_im;
  int ihi;
  float cto1;
  int exitg3;
  float a;
  int jj;
  int i;
  int j;
  int ii;
  creal32_T atmp;
  boolean_T exitg4;
  int jcol;
  int exitg2;
  int A_re_tmp;
  signed char b_I[16];
  int jcolp1;
  int jrow;
  float f;
  float f1;
  float f2;
  *info = 0;
  anrm = 0.0F;
  nzcount = 0;
  exitg1 = false;
  while ((!exitg1) && (nzcount < 16)) {
    absxk = rt_hypotf_snf(A[nzcount].re, A[nzcount].im);
    if (rtIsNaNF(absxk)) {
      anrm = rtNaNF;
      exitg1 = true;
    } else {
      if (absxk > anrm) {
        anrm = absxk;
      }

      nzcount++;
    }
  }

  if (rtIsInfF(anrm) || rtIsNaNF(anrm)) {
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
    for (jj = 0; jj < 16; jj++) {
      V[jj].re = rtNaNF;
      V[jj].im = 0.0F;
    }
  } else {
    ilascl = false;
    anrmto = anrm;
    guard1 = false;
    if ((anrm > 0.0F) && (anrm < 9.09494702E-13F)) {
      anrmto = 9.09494702E-13F;
      ilascl = true;
      guard1 = true;
    } else {
      if (anrm > 1.09951163E+12F) {
        anrmto = 1.09951163E+12F;
        ilascl = true;
        guard1 = true;
      }
    }

    if (guard1) {
      absxk = anrm;
      ctoc = anrmto;
      notdone = true;
      while (notdone) {
        stemp_im = absxk * 1.97215226E-31F;
        cto1 = ctoc / 5.0706024E+30F;
        if ((stemp_im > ctoc) && (ctoc != 0.0F)) {
          a = 1.97215226E-31F;
          absxk = stemp_im;
        } else if (cto1 > absxk) {
          a = 5.0706024E+30F;
          ctoc = cto1;
        } else {
          a = ctoc / absxk;
          notdone = false;
        }

        for (jj = 0; jj < 16; jj++) {
          A[jj].re *= a;
          A[jj].im *= a;
        }
      }
    }

    rscale[0] = 1;
    rscale[1] = 1;
    rscale[2] = 1;
    rscale[3] = 1;
    ilo = 1;
    ihi = 4;
    do {
      exitg3 = 0;
      i = 0;
      j = 0;
      notdone = false;
      ii = ihi;
      exitg1 = false;
      while ((!exitg1) && (ii > 0)) {
        nzcount = 0;
        i = ii;
        j = ihi;
        jj = 0;
        exitg4 = false;
        while ((!exitg4) && (jj <= ihi - 1)) {
          A_re_tmp = (ii + (jj << 2)) - 1;
          if ((A[A_re_tmp].re != 0.0F) || (A[A_re_tmp].im != 0.0F) || (ii == jj
               + 1)) {
            if (nzcount == 0) {
              j = jj + 1;
              nzcount = 1;
              jj++;
            } else {
              nzcount = 2;
              exitg4 = true;
            }
          } else {
            jj++;
          }
        }

        if (nzcount < 2) {
          notdone = true;
          exitg1 = true;
        } else {
          ii--;
        }
      }

      if (!notdone) {
        exitg3 = 2;
      } else {
        if (i != ihi) {
          atmp = A[i - 1];
          A[i - 1] = A[ihi - 1];
          A[ihi - 1] = atmp;
          atmp = A[i + 3];
          A[i + 3] = A[ihi + 3];
          A[ihi + 3] = atmp;
          atmp = A[i + 7];
          A[i + 7] = A[ihi + 7];
          A[ihi + 7] = atmp;
          atmp = A[i + 11];
          A[i + 11] = A[ihi + 11];
          A[ihi + 11] = atmp;
        }

        if (j != ihi) {
          for (nzcount = 0; nzcount < ihi; nzcount++) {
            jcol = nzcount + ((j - 1) << 2);
            atmp = A[jcol];
            jj = nzcount + ((ihi - 1) << 2);
            A[jcol] = A[jj];
            A[jj] = atmp;
          }
        }

        rscale[ihi - 1] = j;
        ihi--;
        if (ihi == 1) {
          rscale[0] = 1;
          exitg3 = 1;
        }
      }
    } while (exitg3 == 0);

    if (exitg3 != 1) {
      do {
        exitg2 = 0;
        i = 0;
        j = 0;
        notdone = false;
        jj = ilo;
        exitg1 = false;
        while ((!exitg1) && (jj <= ihi)) {
          nzcount = 0;
          i = ihi;
          j = jj;
          ii = ilo;
          exitg4 = false;
          while ((!exitg4) && (ii <= ihi)) {
            A_re_tmp = (ii + ((jj - 1) << 2)) - 1;
            if ((A[A_re_tmp].re != 0.0F) || (A[A_re_tmp].im != 0.0F) || (ii ==
                 jj)) {
              if (nzcount == 0) {
                i = ii;
                nzcount = 1;
                ii++;
              } else {
                nzcount = 2;
                exitg4 = true;
              }
            } else {
              ii++;
            }
          }

          if (nzcount < 2) {
            notdone = true;
            exitg1 = true;
          } else {
            jj++;
          }
        }

        if (!notdone) {
          exitg2 = 1;
        } else {
          if (i != ilo) {
            for (nzcount = ilo; nzcount < 5; nzcount++) {
              jcol = (nzcount - 1) << 2;
              ii = (i + jcol) - 1;
              atmp = A[ii];
              jj = (ilo + jcol) - 1;
              A[ii] = A[jj];
              A[jj] = atmp;
            }
          }

          if (j != ilo) {
            for (nzcount = 0; nzcount < ihi; nzcount++) {
              jcol = nzcount + ((j - 1) << 2);
              atmp = A[jcol];
              jj = nzcount + ((ilo - 1) << 2);
              A[jcol] = A[jj];
              A[jj] = atmp;
            }
          }

          rscale[ilo - 1] = j;
          ilo++;
          if (ilo == ihi) {
            rscale[ilo - 1] = ilo;
            exitg2 = 1;
          }
        }
      } while (exitg2 == 0);
    }

    for (jj = 0; jj < 16; jj++) {
      b_I[jj] = 0;
    }

    b_I[0] = 1;
    b_I[5] = 1;
    b_I[10] = 1;
    b_I[15] = 1;
    for (jj = 0; jj < 16; jj++) {
      V[jj].re = b_I[jj];
      V[jj].im = 0.0F;
    }

    if (ihi >= ilo + 2) {
      for (jcol = ilo - 1; jcol + 1 < ihi - 1; jcol++) {
        jcolp1 = jcol + 2;
        for (jrow = ihi - 1; jrow + 1 > jcol + 2; jrow--) {
          nzcount = jrow + (jcol << 2);
          xzlartg(A[nzcount - 1], A[nzcount], &absxk, &atmp, &A[(jrow + (jcol <<
                    2)) - 1]);
          A[nzcount].re = 0.0F;
          A[nzcount].im = 0.0F;
          for (j = jcolp1; j < 5; j++) {
            jj = jrow + ((j - 1) << 2);
            A_re_tmp = jj - 1;
            ctoc = absxk * A[A_re_tmp].re + (atmp.re * A[jj].re - atmp.im * A[jj]
              .im);
            stemp_im = absxk * A[A_re_tmp].im + (atmp.re * A[jj].im + atmp.im *
              A[jj].re);
            f = A[A_re_tmp].im;
            f1 = A[A_re_tmp].re;
            A[jj].re = absxk * A[jj].re - (atmp.re * A[A_re_tmp].re + atmp.im *
              A[A_re_tmp].im);
            A[jj].im = absxk * A[jj].im - (atmp.re * f - atmp.im * f1);
            A[A_re_tmp].re = ctoc;
            A[A_re_tmp].im = stemp_im;
          }

          atmp.re = -atmp.re;
          atmp.im = -atmp.im;
          for (i = 1; i <= ihi; i++) {
            jj = (i + ((jrow - 1) << 2)) - 1;
            A_re_tmp = (i + (jrow << 2)) - 1;
            ctoc = absxk * A[A_re_tmp].re + (atmp.re * A[jj].re - atmp.im * A[jj]
              .im);
            stemp_im = absxk * A[A_re_tmp].im + (atmp.re * A[jj].im + atmp.im *
              A[jj].re);
            f = A[A_re_tmp].im;
            f1 = A[A_re_tmp].re;
            A[jj].re = absxk * A[jj].re - (atmp.re * A[A_re_tmp].re + atmp.im *
              A[A_re_tmp].im);
            A[jj].im = absxk * A[jj].im - (atmp.re * f - atmp.im * f1);
            A[A_re_tmp].re = ctoc;
            A[A_re_tmp].im = stemp_im;
          }

          jj = (jrow - 1) << 2;
          A_re_tmp = jrow << 2;
          ctoc = absxk * V[A_re_tmp].re + (atmp.re * V[jj].re - atmp.im * V[jj].
            im);
          stemp_im = absxk * V[A_re_tmp].im + (atmp.re * V[jj].im + atmp.im *
            V[jj].re);
          f = V[A_re_tmp].re;
          V[jj].re = absxk * V[jj].re - (atmp.re * V[A_re_tmp].re + atmp.im *
            V[A_re_tmp].im);
          V[jj].im = absxk * V[jj].im - (atmp.re * V[A_re_tmp].im - atmp.im * f);
          V[A_re_tmp].re = ctoc;
          V[A_re_tmp].im = stemp_im;
          ii = jj + 1;
          nzcount = A_re_tmp + 1;
          ctoc = absxk * V[nzcount].re + (atmp.re * V[ii].re - atmp.im * V[ii].
            im);
          stemp_im = absxk * V[nzcount].im + (atmp.re * V[ii].im + atmp.im *
            V[ii].re);
          f = V[nzcount].re;
          V[ii].re = absxk * V[ii].re - (atmp.re * V[nzcount].re + atmp.im *
            V[nzcount].im);
          V[ii].im = absxk * V[ii].im - (atmp.re * V[nzcount].im - atmp.im * f);
          V[nzcount].re = ctoc;
          V[nzcount].im = stemp_im;
          ii = jj + 2;
          nzcount = A_re_tmp + 2;
          ctoc = absxk * V[nzcount].re + (atmp.re * V[ii].re - atmp.im * V[ii].
            im);
          stemp_im = absxk * V[nzcount].im + (atmp.re * V[ii].im + atmp.im *
            V[ii].re);
          f = V[nzcount].re;
          V[ii].re = absxk * V[ii].re - (atmp.re * V[nzcount].re + atmp.im *
            V[nzcount].im);
          V[ii].im = absxk * V[ii].im - (atmp.re * V[nzcount].im - atmp.im * f);
          V[nzcount].re = ctoc;
          V[nzcount].im = stemp_im;
          jj += 3;
          A_re_tmp += 3;
          ctoc = absxk * V[A_re_tmp].re + (atmp.re * V[jj].re - atmp.im * V[jj].
            im);
          stemp_im = absxk * V[A_re_tmp].im + (atmp.re * V[jj].im + atmp.im *
            V[jj].re);
          f = V[A_re_tmp].re;
          V[jj].re = absxk * V[jj].re - (atmp.re * V[A_re_tmp].re + atmp.im *
            V[A_re_tmp].im);
          V[jj].im = absxk * V[jj].im - (atmp.re * V[A_re_tmp].im - atmp.im * f);
          V[A_re_tmp].re = ctoc;
          V[A_re_tmp].im = stemp_im;
        }
      }
    }

    xzhgeqz(A, ilo, ihi, V, info, alpha1, beta1);
    if (*info == 0) {
      xztgevc(A, V);
      if (ilo > 1) {
        for (i = ilo - 2; i + 1 >= 1; i--) {
          nzcount = rscale[i] - 1;
          if (rscale[i] != i + 1) {
            atmp = V[i];
            V[i] = V[nzcount];
            V[nzcount] = atmp;
            atmp = V[i + 4];
            V[i + 4] = V[nzcount + 4];
            V[nzcount + 4] = atmp;
            atmp = V[i + 8];
            V[i + 8] = V[nzcount + 8];
            V[nzcount + 8] = atmp;
            atmp = V[i + 12];
            V[i + 12] = V[nzcount + 12];
            V[nzcount + 12] = atmp;
          }
        }
      }

      if (ihi < 4) {
        jj = ihi + 1;
        for (i = jj; i < 5; i++) {
          nzcount = rscale[i - 1];
          if (nzcount != i) {
            atmp = V[i - 1];
            V[i - 1] = V[nzcount - 1];
            V[nzcount - 1] = atmp;
            atmp = V[i + 3];
            ii = nzcount + 3;
            V[i + 3] = V[ii];
            V[ii] = atmp;
            atmp = V[i + 7];
            ii = nzcount + 7;
            V[i + 7] = V[ii];
            V[ii] = atmp;
            atmp = V[i + 11];
            ii = nzcount + 11;
            V[i + 11] = V[ii];
            V[ii] = atmp;
          }
        }
      }

      for (ii = 0; ii < 4; ii++) {
        nzcount = ii << 2;
        absxk = fabsf(V[nzcount].re) + fabsf(V[nzcount].im);
        jj = nzcount + 1;
        f = V[jj].re;
        f1 = V[jj].im;
        ctoc = fabsf(V[jj].re) + fabsf(V[jj].im);
        if (ctoc > absxk) {
          absxk = ctoc;
        }

        A_re_tmp = nzcount + 2;
        stemp_im = V[A_re_tmp].re;
        cto1 = V[A_re_tmp].im;
        ctoc = fabsf(V[A_re_tmp].re) + fabsf(V[A_re_tmp].im);
        if (ctoc > absxk) {
          absxk = ctoc;
        }

        jcol = nzcount + 3;
        a = V[jcol].re;
        f2 = V[jcol].im;
        ctoc = fabsf(V[jcol].re) + fabsf(V[jcol].im);
        if (ctoc > absxk) {
          absxk = ctoc;
        }

        if (absxk >= 9.09494702E-13F) {
          absxk = 1.0F / absxk;
          V[nzcount].re *= absxk;
          V[nzcount].im *= absxk;
          f *= absxk;
          V[jj].re = f;
          f1 *= absxk;
          V[jj].im = f1;
          stemp_im *= absxk;
          V[A_re_tmp].re = stemp_im;
          cto1 *= absxk;
          V[A_re_tmp].im = cto1;
          a *= absxk;
          V[jcol].re = a;
          f2 *= absxk;
          V[jcol].im = f2;
        }
      }

      if (ilascl) {
        notdone = true;
        while (notdone) {
          stemp_im = anrmto * 1.97215226E-31F;
          cto1 = anrm / 5.0706024E+30F;
          if ((stemp_im > anrm) && (anrm != 0.0F)) {
            a = 1.97215226E-31F;
            anrmto = stemp_im;
          } else if (cto1 > anrmto) {
            a = 5.0706024E+30F;
            anrm = cto1;
          } else {
            a = anrm / anrmto;
            notdone = false;
          }

          alpha1[0].re *= a;
          alpha1[0].im *= a;
          alpha1[1].re *= a;
          alpha1[1].im *= a;
          alpha1[2].re *= a;
          alpha1[2].im *= a;
          alpha1[3].re *= a;
          alpha1[3].im *= a;
        }
      }
    }
  }
}

/* End of code generation (xzggev.c) */
