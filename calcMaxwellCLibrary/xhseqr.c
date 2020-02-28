/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xhseqr.c
 *
 * Code generation for function 'xhseqr'
 *
 */

/* Include files */
#include "xhseqr.h"
#include "calcMaxwell.h"
#include "calcMaxwell_rtwutil.h"
#include "recip.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xdlapy3.h"
#include <math.h>

/* Function Definitions */
int xhseqr(creal32_T h[16], creal32_T z[16])
{
  int info;
  int i;
  int b_i;
  boolean_T exitg1;
  float tst;
  float htmp2;
  int L;
  float br;
  boolean_T goto140;
  int its;
  creal32_T sc;
  boolean_T exitg2;
  int k;
  boolean_T exitg3;
  float re;
  float im;
  float ba;
  int h_tmp;
  int ix0;
  int tst_tmp_tmp;
  int t_re_tmp;
  float bb;
  float t_re;
  int knt;
  float t_im;
  creal32_T v;
  boolean_T goto70;
  int m;
  float u_re;
  float u_im;
  float s;
  int b_k;
  creal32_T b_v[2];
  int j;
  info = 0;
  h[2].re = 0.0F;
  h[2].im = 0.0F;
  h[3].re = 0.0F;
  h[3].im = 0.0F;
  h[7].re = 0.0F;
  h[7].im = 0.0F;
  for (i = 0; i < 3; i++) {
    b_i = (i + (i << 2)) + 1;
    if (h[b_i].im != 0.0F) {
      tst = h[b_i].re;
      htmp2 = h[b_i].im;
      br = fabsf(h[b_i].re) + fabsf(h[b_i].im);
      if (htmp2 == 0.0F) {
        sc.re = tst / br;
        sc.im = 0.0F;
      } else if (tst == 0.0F) {
        sc.re = 0.0F;
        sc.im = htmp2 / br;
      } else {
        sc.re = tst / br;
        sc.im = htmp2 / br;
      }

      br = rt_hypotf_snf(sc.re, sc.im);
      if (-sc.im == 0.0F) {
        re = sc.re / br;
        im = 0.0F;
      } else if (sc.re == 0.0F) {
        re = 0.0F;
        im = -sc.im / br;
      } else {
        re = sc.re / br;
        im = -sc.im / br;
      }

      h[b_i].re = rt_hypotf_snf(h[b_i].re, h[b_i].im);
      h[b_i].im = 0.0F;
      h_tmp = (i + 1) << 2;
      ix0 = (i + h_tmp) + 2;
      b_i = ix0 + ((2 - i) << 2);
      for (k = ix0; k <= b_i; k += 4) {
        htmp2 = re * h[k - 1].im + im * h[k - 1].re;
        h[k - 1].re = re * h[k - 1].re - im * h[k - 1].im;
        h[k - 1].im = htmp2;
      }

      ix0 = h_tmp + 1;
      knt = i + 3;
      if (4 < knt) {
        knt = 4;
      }

      b_i = h_tmp + knt;
      for (k = ix0; k <= b_i; k++) {
        htmp2 = re * h[k - 1].im + -im * h[k - 1].re;
        h[k - 1].re = re * h[k - 1].re - -im * h[k - 1].im;
        h[k - 1].im = htmp2;
      }

      b_i = h_tmp + 4;
      for (k = ix0; k <= b_i; k++) {
        htmp2 = re * z[k - 1].im + -im * z[k - 1].re;
        z[k - 1].re = re * z[k - 1].re - -im * z[k - 1].im;
        z[k - 1].im = htmp2;
      }
    }
  }

  i = 3;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    L = -1;
    goto140 = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 301)) {
      k = i;
      exitg3 = false;
      while ((!exitg3) && (k + 1 > L + 2)) {
        b_i = k + ((k - 1) << 2);
        htmp2 = fabsf(h[b_i].re);
        ba = htmp2 + fabsf(h[b_i].im);
        if (ba <= 3.94430453E-31F) {
          exitg3 = true;
        } else {
          tst_tmp_tmp = k + (k << 2);
          bb = fabsf(h[tst_tmp_tmp].re) + fabsf(h[tst_tmp_tmp].im);
          knt = b_i - 1;
          tst = (fabsf(h[knt].re) + fabsf(h[knt].im)) + bb;
          if (tst == 0.0F) {
            if (k - 1 >= 1) {
              tst = fabsf(h[(k + ((k - 2) << 2)) - 1].re);
            }

            if (k + 2 <= 4) {
              tst += fabsf(h[tst_tmp_tmp + 1].re);
            }
          }

          if (htmp2 <= 1.1920929E-7F * tst) {
            ix0 = tst_tmp_tmp - 1;
            htmp2 = fabsf(h[ix0].re) + fabsf(h[ix0].im);
            if (ba > htmp2) {
              tst = ba;
              ba = htmp2;
            } else {
              tst = htmp2;
            }

            htmp2 = fabsf(h[knt].re - h[tst_tmp_tmp].re) + fabsf(h[knt].im -
              h[tst_tmp_tmp].im);
            if (bb > htmp2) {
              t_im = bb;
              bb = htmp2;
            } else {
              t_im = htmp2;
            }

            s = t_im + tst;
            if (ba * (tst / s) <= fmaxf(3.94430453E-31F, 1.1920929E-7F * (bb *
                  (t_im / s)))) {
              exitg3 = true;
            } else {
              k--;
            }
          } else {
            k--;
          }
        }
      }

      L = k - 1;
      if (k + 1 > 1) {
        b_i = k + ((k - 1) << 2);
        h[b_i].re = 0.0F;
        h[b_i].im = 0.0F;
      }

      if (k + 1 >= i + 1) {
        goto140 = true;
        exitg2 = true;
      } else {
        if (its == 10) {
          t_re_tmp = k + (k << 2);
          t_re = 0.75F * fabsf(h[(k + (k << 2)) + 1].re) + h[t_re_tmp].re;
          t_im = h[t_re_tmp].im;
        } else if (its == 20) {
          t_re_tmp = i + (i << 2);
          t_re = 0.75F * fabsf(h[i + ((i - 1) << 2)].re) + h[t_re_tmp].re;
          t_im = h[t_re_tmp].im;
        } else {
          t_re_tmp = i + (i << 2);
          t_re = h[t_re_tmp].re;
          t_im = h[t_re_tmp].im;
          v = h[t_re_tmp - 1];
          b_sqrt(&v);
          h_tmp = i + ((i - 1) << 2);
          sc = h[h_tmp];
          b_sqrt(&sc);
          u_re = v.re * sc.re - v.im * sc.im;
          u_im = v.re * sc.im + v.im * sc.re;
          s = fabsf(u_re) + fabsf(u_im);
          if (s != 0.0F) {
            knt = h_tmp - 1;
            bb = 0.5F * (h[knt].re - h[t_re_tmp].re);
            im = 0.5F * (h[knt].im - h[t_re_tmp].im);
            ba = fabsf(bb) + fabsf(im);
            s = fmaxf(s, ba);
            if (im == 0.0F) {
              t_re = bb / s;
              t_im = 0.0F;
            } else if (bb == 0.0F) {
              t_re = 0.0F;
              t_im = im / s;
            } else {
              t_re = bb / s;
              t_im = im / s;
            }

            re = t_re * t_re - t_im * t_im;
            tst = t_re * t_im;
            if (u_im == 0.0F) {
              sc.re = u_re / s;
              sc.im = 0.0F;
            } else if (u_re == 0.0F) {
              sc.re = 0.0F;
              sc.im = u_im / s;
            } else {
              sc.re = u_re / s;
              sc.im = u_im / s;
            }

            htmp2 = sc.re * sc.re - sc.im * sc.im;
            t_im = sc.re * sc.im;
            v.re = re + htmp2;
            v.im = (tst + tst) + (t_im + t_im);
            b_sqrt(&v);
            sc.re = s * v.re;
            sc.im = s * v.im;
            if (ba > 0.0F) {
              if (im == 0.0F) {
                t_re = bb / ba;
                t_im = 0.0F;
              } else if (bb == 0.0F) {
                t_re = 0.0F;
                t_im = im / ba;
              } else {
                t_re = bb / ba;
                t_im = im / ba;
              }

              if (t_re * sc.re + t_im * sc.im < 0.0F) {
                sc.re = -sc.re;
                sc.im = -sc.im;
              }
            }

            br = bb + sc.re;
            t_im = im + sc.im;
            if (t_im == 0.0F) {
              if (u_im == 0.0F) {
                bb = u_re / br;
                tst = 0.0F;
              } else if (u_re == 0.0F) {
                bb = 0.0F;
                tst = u_im / br;
              } else {
                bb = u_re / br;
                tst = u_im / br;
              }
            } else if (br == 0.0F) {
              if (u_re == 0.0F) {
                bb = u_im / t_im;
                tst = 0.0F;
              } else if (u_im == 0.0F) {
                bb = 0.0F;
                tst = -(u_re / t_im);
              } else {
                bb = u_im / t_im;
                tst = -(u_re / t_im);
              }
            } else {
              ba = fabsf(br);
              tst = fabsf(t_im);
              if (ba > tst) {
                s = t_im / br;
                tst = br + s * t_im;
                bb = (u_re + s * u_im) / tst;
                tst = (u_im - s * u_re) / tst;
              } else if (tst == ba) {
                if (br > 0.0F) {
                  htmp2 = 0.5F;
                } else {
                  htmp2 = -0.5F;
                }

                if (t_im > 0.0F) {
                  tst = 0.5F;
                } else {
                  tst = -0.5F;
                }

                bb = (u_re * htmp2 + u_im * tst) / ba;
                tst = (u_im * htmp2 - u_re * tst) / ba;
              } else {
                s = br / t_im;
                tst = t_im + s * br;
                bb = (s * u_re + u_im) / tst;
                tst = (s * u_im - u_re) / tst;
              }
            }

            t_re = h[t_re_tmp].re - (u_re * bb - u_im * tst);
            t_im = h[t_re_tmp].im - (u_re * tst + u_im * bb);
          }
        }

        goto70 = false;
        m = i;
        exitg3 = false;
        while ((!exitg3) && (m > k + 1)) {
          knt = m + ((m - 1) << 2);
          h_tmp = knt - 1;
          sc.re = h[h_tmp].re - t_re;
          sc.im = h[h_tmp].im - t_im;
          tst = h[knt].re;
          s = (fabsf(sc.re) + fabsf(sc.im)) + fabsf(tst);
          if (sc.im == 0.0F) {
            re = sc.re / s;
            im = 0.0F;
          } else if (sc.re == 0.0F) {
            re = 0.0F;
            im = sc.im / s;
          } else {
            re = sc.re / s;
            im = sc.im / s;
          }

          sc.re = re;
          sc.im = im;
          tst /= s;
          b_v[0] = sc;
          b_v[1].re = tst;
          b_v[1].im = 0.0F;
          b_i = m + (m << 2);
          if (fabsf(h[(m + ((m - 2) << 2)) - 1].re) * fabsf(tst) <=
              1.1920929E-7F * ((fabsf(re) + fabsf(im)) * ((fabsf(h[h_tmp].re) +
                 fabsf(h[h_tmp].im)) + (fabsf(h[b_i].re) + fabsf(h[b_i].im)))))
          {
            goto70 = true;
            exitg3 = true;
          } else {
            m--;
          }
        }

        if (!goto70) {
          h_tmp = k + (k << 2);
          sc.re = h[h_tmp].re - t_re;
          sc.im = h[h_tmp].im - t_im;
          tst = h[(k + (k << 2)) + 1].re;
          s = (fabsf(sc.re) + fabsf(sc.im)) + fabsf(tst);
          if (sc.im == 0.0F) {
            b_v[0].re = sc.re / s;
            b_v[0].im = 0.0F;
          } else if (sc.re == 0.0F) {
            b_v[0].re = 0.0F;
            b_v[0].im = sc.im / s;
          } else {
            b_v[0].re = sc.re / s;
            b_v[0].im = sc.im / s;
          }

          tst /= s;
          b_v[1].re = tst;
          b_v[1].im = 0.0F;
        }

        for (b_k = m; b_k <= i; b_k++) {
          if (b_k > m) {
            knt = b_k + ((b_k - 2) << 2);
            b_v[0] = h[knt - 1];
            b_v[1] = h[knt];
          }

          bb = b_v[1].re;
          im = b_v[1].im;
          sc = b_v[0];
          t_re = 0.0F;
          t_im = 0.0F;
          tst = rt_hypotf_snf(b_v[1].re, b_v[1].im);
          if ((tst != 0.0F) || (b_v[0].im != 0.0F)) {
            htmp2 = xdlapy3(b_v[0].re, b_v[0].im, tst);
            if (b_v[0].re >= 0.0F) {
              htmp2 = -htmp2;
            }

            if (fabsf(htmp2) < 9.86076132E-32F) {
              knt = -1;
              do {
                knt++;
                bb *= 1.01412048E+31F;
                im *= 1.01412048E+31F;
                htmp2 *= 1.01412048E+31F;
                sc.re *= 1.01412048E+31F;
                sc.im *= 1.01412048E+31F;
              } while (!(fabsf(htmp2) >= 9.86076132E-32F));

              htmp2 = xdlapy3(sc.re, sc.im, rt_hypotf_snf(bb, im));
              if (sc.re >= 0.0F) {
                htmp2 = -htmp2;
              }

              tst = htmp2 - sc.re;
              if (0.0F - sc.im == 0.0F) {
                t_re = tst / htmp2;
                t_im = 0.0F;
              } else if (tst == 0.0F) {
                t_re = 0.0F;
                t_im = (0.0F - sc.im) / htmp2;
              } else {
                t_re = tst / htmp2;
                t_im = (0.0F - sc.im) / htmp2;
              }

              v.re = sc.re - htmp2;
              v.im = sc.im;
              sc = recip(v);
              re = sc.re * bb - sc.im * im;
              im = sc.re * im + sc.im * bb;
              bb = re;
              for (tst_tmp_tmp = 0; tst_tmp_tmp <= knt; tst_tmp_tmp++) {
                htmp2 *= 9.86076132E-32F;
              }

              sc.re = htmp2;
              sc.im = 0.0F;
            } else {
              tst = htmp2 - b_v[0].re;
              if (0.0F - b_v[0].im == 0.0F) {
                t_re = tst / htmp2;
                t_im = 0.0F;
              } else if (tst == 0.0F) {
                t_re = 0.0F;
                t_im = (0.0F - b_v[0].im) / htmp2;
              } else {
                t_re = tst / htmp2;
                t_im = (0.0F - b_v[0].im) / htmp2;
              }

              v.re = b_v[0].re - htmp2;
              v.im = b_v[0].im;
              v = recip(v);
              bb = v.re * b_v[1].re - v.im * b_v[1].im;
              im = v.re * b_v[1].im + v.im * b_v[1].re;
              sc.re = htmp2;
              sc.im = 0.0F;
            }
          }

          b_v[0] = sc;
          b_v[1].re = bb;
          b_v[1].im = im;
          if (b_k > m) {
            h[(b_k + ((b_k - 2) << 2)) - 1] = sc;
            b_i = b_k + ((b_k - 2) << 2);
            h[b_i].re = 0.0F;
            h[b_i].im = 0.0F;
          }

          tst = t_re * bb - t_im * im;
          for (j = b_k; j < 5; j++) {
            ix0 = b_k + ((j - 1) << 2);
            t_re_tmp = ix0 - 1;
            sc.re = (t_re * h[t_re_tmp].re - -t_im * h[t_re_tmp].im) + tst *
              h[ix0].re;
            sc.im = (t_re * h[t_re_tmp].im + -t_im * h[t_re_tmp].re) + tst *
              h[ix0].im;
            h[t_re_tmp].re -= sc.re;
            h[t_re_tmp].im -= sc.im;
            h[ix0].re -= sc.re * bb - sc.im * im;
            h[ix0].im -= sc.re * im + sc.im * bb;
          }

          if (b_k + 2 < i + 1) {
            b_i = b_k + 1;
          } else {
            b_i = i;
          }

          for (j = 0; j <= b_i; j++) {
            t_re_tmp = j + ((b_k - 1) << 2);
            h_tmp = j + (b_k << 2);
            sc.re = (t_re * h[t_re_tmp].re - t_im * h[t_re_tmp].im) + tst *
              h[h_tmp].re;
            sc.im = (t_re * h[t_re_tmp].im + t_im * h[t_re_tmp].re) + tst *
              h[h_tmp].im;
            h[t_re_tmp].re -= sc.re;
            h[t_re_tmp].im -= sc.im;
            h[h_tmp].re -= sc.re * bb - sc.im * -im;
            h[h_tmp].im -= sc.re * -im + sc.im * bb;
          }

          t_re_tmp = (b_k - 1) << 2;
          h_tmp = b_k << 2;
          sc.re = (t_re * z[t_re_tmp].re - t_im * z[t_re_tmp].im) + tst *
            z[h_tmp].re;
          sc.im = (t_re * z[t_re_tmp].im + t_im * z[t_re_tmp].re) + tst *
            z[h_tmp].im;
          z[t_re_tmp].re -= sc.re;
          z[t_re_tmp].im -= sc.im;
          z[h_tmp].re -= sc.re * bb - sc.im * -im;
          z[h_tmp].im -= sc.re * -im + sc.im * bb;
          ix0 = t_re_tmp + 1;
          tst_tmp_tmp = h_tmp + 1;
          sc.re = (t_re * z[ix0].re - t_im * z[ix0].im) + tst * z[tst_tmp_tmp].
            re;
          sc.im = (t_re * z[ix0].im + t_im * z[ix0].re) + tst * z[tst_tmp_tmp].
            im;
          z[ix0].re -= sc.re;
          z[ix0].im -= sc.im;
          z[tst_tmp_tmp].re -= sc.re * bb - sc.im * -im;
          z[tst_tmp_tmp].im -= sc.re * -im + sc.im * bb;
          ix0 = t_re_tmp + 2;
          tst_tmp_tmp = h_tmp + 2;
          sc.re = (t_re * z[ix0].re - t_im * z[ix0].im) + tst * z[tst_tmp_tmp].
            re;
          sc.im = (t_re * z[ix0].im + t_im * z[ix0].re) + tst * z[tst_tmp_tmp].
            im;
          z[ix0].re -= sc.re;
          z[ix0].im -= sc.im;
          z[tst_tmp_tmp].re -= sc.re * bb - sc.im * -im;
          z[tst_tmp_tmp].im -= sc.re * -im + sc.im * bb;
          t_re_tmp += 3;
          h_tmp += 3;
          sc.re = (t_re * z[t_re_tmp].re - t_im * z[t_re_tmp].im) + tst *
            z[h_tmp].re;
          sc.im = (t_re * z[t_re_tmp].im + t_im * z[t_re_tmp].re) + tst *
            z[h_tmp].im;
          z[t_re_tmp].re -= sc.re;
          z[t_re_tmp].im -= sc.im;
          z[h_tmp].re -= sc.re * bb - sc.im * -im;
          z[h_tmp].im -= sc.re * -im + sc.im * bb;
          if ((b_k == m) && (m > k + 1)) {
            br = rt_hypotf_snf(1.0F - t_re, 0.0F - t_im);
            if (0.0F - t_im == 0.0F) {
              re = (1.0F - t_re) / br;
              im = 0.0F;
            } else if (1.0F - t_re == 0.0F) {
              re = 0.0F;
              im = (0.0F - t_im) / br;
            } else {
              re = (1.0F - t_re) / br;
              im = (0.0F - t_im) / br;
            }

            knt = m + ((m - 1) << 2);
            htmp2 = h[knt].re * -im + h[knt].im * re;
            h[knt].re = h[knt].re * re - h[knt].im * -im;
            h[knt].im = htmp2;
            if (m + 2 <= i + 1) {
              knt = (m << 2) + 3;
              htmp2 = h[knt].re * im + h[knt].im * re;
              h[knt].re = h[knt].re * re - h[knt].im * im;
              h[knt].im = htmp2;
            }

            for (j = m; j <= i + 1; j++) {
              if (j != m + 1) {
                if (4 > j) {
                  ix0 = j + (j << 2);
                  b_i = ix0 + ((3 - j) << 2);
                  for (tst_tmp_tmp = ix0; tst_tmp_tmp <= b_i; tst_tmp_tmp += 4)
                  {
                    htmp2 = re * h[tst_tmp_tmp - 1].im + im * h[tst_tmp_tmp - 1]
                      .re;
                    h[tst_tmp_tmp - 1].re = re * h[tst_tmp_tmp - 1].re - im *
                      h[tst_tmp_tmp - 1].im;
                    h[tst_tmp_tmp - 1].im = htmp2;
                  }
                }

                tst_tmp_tmp = (j - 1) << 2;
                knt = tst_tmp_tmp - 1;
                h_tmp = tst_tmp_tmp + 1;
                b_i = knt + j;
                for (tst_tmp_tmp = h_tmp; tst_tmp_tmp <= b_i; tst_tmp_tmp++) {
                  htmp2 = re * h[tst_tmp_tmp - 1].im + -im * h[tst_tmp_tmp - 1].
                    re;
                  h[tst_tmp_tmp - 1].re = re * h[tst_tmp_tmp - 1].re - -im *
                    h[tst_tmp_tmp - 1].im;
                  h[tst_tmp_tmp - 1].im = htmp2;
                }

                b_i = knt + 5;
                for (tst_tmp_tmp = h_tmp; tst_tmp_tmp <= b_i; tst_tmp_tmp++) {
                  htmp2 = re * z[tst_tmp_tmp - 1].im + -im * z[tst_tmp_tmp - 1].
                    re;
                  z[tst_tmp_tmp - 1].re = re * z[tst_tmp_tmp - 1].re - -im *
                    z[tst_tmp_tmp - 1].im;
                  z[tst_tmp_tmp - 1].im = htmp2;
                }
              }
            }
          }
        }

        h_tmp = i + ((i - 1) << 2);
        sc = h[h_tmp];
        if (h[h_tmp].im != 0.0F) {
          htmp2 = rt_hypotf_snf(h[h_tmp].re, h[h_tmp].im);
          h[h_tmp].re = htmp2;
          h[h_tmp].im = 0.0F;
          if (sc.im == 0.0F) {
            re = sc.re / htmp2;
            im = 0.0F;
          } else if (sc.re == 0.0F) {
            re = 0.0F;
            im = sc.im / htmp2;
          } else {
            re = sc.re / htmp2;
            im = sc.im / htmp2;
          }

          if (4 > i + 1) {
            ix0 = (i + ((i + 1) << 2)) + 1;
            b_i = ix0 + ((2 - i) << 2);
            for (k = ix0; k <= b_i; k += 4) {
              htmp2 = re * h[k - 1].im + -im * h[k - 1].re;
              h[k - 1].re = re * h[k - 1].re - -im * h[k - 1].im;
              h[k - 1].im = htmp2;
            }
          }

          tst_tmp_tmp = i << 2;
          h_tmp = tst_tmp_tmp + 1;
          b_i = tst_tmp_tmp + i;
          for (k = h_tmp; k <= b_i; k++) {
            htmp2 = re * h[k - 1].im + im * h[k - 1].re;
            h[k - 1].re = re * h[k - 1].re - im * h[k - 1].im;
            h[k - 1].im = htmp2;
          }

          b_i = tst_tmp_tmp + 4;
          for (k = h_tmp; k <= b_i; k++) {
            htmp2 = re * z[k - 1].im + im * z[k - 1].re;
            z[k - 1].re = re * z[k - 1].re - im * z[k - 1].im;
            z[k - 1].im = htmp2;
          }
        }

        its++;
      }
    }

    if (!goto140) {
      info = i + 1;
      exitg1 = true;
    } else {
      i = L;
    }
  }

  h[3].re = 0.0F;
  h[3].im = 0.0F;
  return info;
}

/* End of code generation (xhseqr.c) */
