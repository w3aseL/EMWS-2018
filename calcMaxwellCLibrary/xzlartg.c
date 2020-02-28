/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzlartg.c
 *
 * Code generation for function 'xzlartg'
 *
 */

/* Include files */
#include "xzlartg.h"
#include "calcMaxwell.h"
#include "calcMaxwell_rtwutil.h"
#include "rt_nonfinite.h"
#include "xhseqr.h"
#include <math.h>

/* Function Definitions */
void b_xzlartg(const creal32_T f, const creal32_T g, float *cs, creal32_T *sn)
{
  float scale_tmp;
  float f2;
  float scale;
  float fs_re;
  float fs_im;
  float gs_re;
  float gs_im;
  boolean_T guard1 = false;
  float g2;
  float g2s;
  scale_tmp = fabsf(f.re);
  f2 = fabsf(f.im);
  if (f2 > scale_tmp) {
    scale_tmp = f2;
  }

  f2 = fabsf(g.re);
  scale = fabsf(g.im);
  if (scale > f2) {
    f2 = scale;
  }

  scale = scale_tmp;
  if (f2 > scale_tmp) {
    scale = f2;
  }

  fs_re = f.re;
  fs_im = f.im;
  gs_re = g.re;
  gs_im = g.im;
  guard1 = false;
  if (scale >= 5.49755814E+11F) {
    do {
      fs_re *= 1.8189894E-12F;
      fs_im *= 1.8189894E-12F;
      gs_re *= 1.8189894E-12F;
      gs_im *= 1.8189894E-12F;
      scale *= 1.8189894E-12F;
    } while (!(scale < 5.49755814E+11F));

    guard1 = true;
  } else if (scale <= 1.8189894E-12F) {
    if ((g.re == 0.0F) && (g.im == 0.0F)) {
      *cs = 1.0F;
      sn->re = 0.0F;
      sn->im = 0.0F;
    } else {
      do {
        fs_re *= 5.49755814E+11F;
        fs_im *= 5.49755814E+11F;
        gs_re *= 5.49755814E+11F;
        gs_im *= 5.49755814E+11F;
        scale *= 5.49755814E+11F;
      } while (!(scale > 1.8189894E-12F));

      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    f2 = fs_re * fs_re + fs_im * fs_im;
    g2 = gs_re * gs_re + gs_im * gs_im;
    scale = g2;
    if (1.0F > g2) {
      scale = 1.0F;
    }

    if (f2 <= scale * 1.97215226E-31F) {
      if ((f.re == 0.0F) && (f.im == 0.0F)) {
        *cs = 0.0F;
        g2 = rt_hypotf_snf(gs_re, gs_im);
        sn->re = gs_re / g2;
        sn->im = -gs_im / g2;
      } else {
        g2s = sqrtf(g2);
        *cs = rt_hypotf_snf(fs_re, fs_im) / g2s;
        if (scale_tmp > 1.0F) {
          g2 = rt_hypotf_snf(f.re, f.im);
          fs_re = f.re / g2;
          fs_im = f.im / g2;
        } else {
          f2 = 5.49755814E+11F * f.re;
          scale = 5.49755814E+11F * f.im;
          g2 = rt_hypotf_snf(f2, scale);
          fs_re = f2 / g2;
          fs_im = scale / g2;
        }

        gs_re /= g2s;
        gs_im = -gs_im / g2s;
        sn->re = fs_re * gs_re - fs_im * gs_im;
        sn->im = fs_re * gs_im + fs_im * gs_re;
      }
    } else {
      scale = sqrtf(g2 / f2 + 1.0F);
      *cs = 1.0F / scale;
      g2 += f2;
      fs_re = scale * fs_re / g2;
      fs_im = scale * fs_im / g2;
      sn->re = fs_re * gs_re - fs_im * -gs_im;
      sn->im = fs_re * -gs_im + fs_im * gs_re;
    }
  }
}

void xzlartg(const creal32_T f, const creal32_T g, float *cs, creal32_T *sn,
             creal32_T *r)
{
  float scale_tmp;
  float f2s;
  float scale;
  float fs_re;
  float fs_im;
  float gs_re;
  float gs_im;
  int count;
  int rescaledir;
  boolean_T guard1 = false;
  float f2;
  float g2;
  scale_tmp = fabsf(f.re);
  f2s = fabsf(f.im);
  if (f2s > scale_tmp) {
    scale_tmp = f2s;
  }

  f2s = fabsf(g.re);
  scale = fabsf(g.im);
  if (scale > f2s) {
    f2s = scale;
  }

  scale = scale_tmp;
  if (f2s > scale_tmp) {
    scale = f2s;
  }

  fs_re = f.re;
  fs_im = f.im;
  gs_re = g.re;
  gs_im = g.im;
  count = -1;
  rescaledir = 0;
  guard1 = false;
  if (scale >= 5.49755814E+11F) {
    do {
      count++;
      fs_re *= 1.8189894E-12F;
      fs_im *= 1.8189894E-12F;
      gs_re *= 1.8189894E-12F;
      gs_im *= 1.8189894E-12F;
      scale *= 1.8189894E-12F;
    } while (!(scale < 5.49755814E+11F));

    rescaledir = 1;
    guard1 = true;
  } else if (scale <= 1.8189894E-12F) {
    if ((g.re == 0.0F) && (g.im == 0.0F)) {
      *cs = 1.0F;
      sn->re = 0.0F;
      sn->im = 0.0F;
      *r = f;
    } else {
      do {
        count++;
        fs_re *= 5.49755814E+11F;
        fs_im *= 5.49755814E+11F;
        gs_re *= 5.49755814E+11F;
        gs_im *= 5.49755814E+11F;
        scale *= 5.49755814E+11F;
      } while (!(scale > 1.8189894E-12F));

      rescaledir = -1;
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    f2 = fs_re * fs_re + fs_im * fs_im;
    g2 = gs_re * gs_re + gs_im * gs_im;
    scale = g2;
    if (1.0F > g2) {
      scale = 1.0F;
    }

    if (f2 <= scale * 1.97215226E-31F) {
      if ((f.re == 0.0F) && (f.im == 0.0F)) {
        *cs = 0.0F;
        r->re = rt_hypotf_snf(g.re, g.im);
        r->im = 0.0F;
        f2 = rt_hypotf_snf(gs_re, gs_im);
        sn->re = gs_re / f2;
        sn->im = -gs_im / f2;
      } else {
        g2 = sqrtf(g2);
        *cs = rt_hypotf_snf(fs_re, fs_im) / g2;
        if (scale_tmp > 1.0F) {
          f2 = rt_hypotf_snf(f.re, f.im);
          fs_re = f.re / f2;
          fs_im = f.im / f2;
        } else {
          scale = 5.49755814E+11F * f.re;
          f2s = 5.49755814E+11F * f.im;
          f2 = rt_hypotf_snf(scale, f2s);
          fs_re = scale / f2;
          fs_im = f2s / f2;
        }

        gs_re /= g2;
        gs_im = -gs_im / g2;
        sn->re = fs_re * gs_re - fs_im * gs_im;
        sn->im = fs_re * gs_im + fs_im * gs_re;
        r->re = *cs * f.re + (sn->re * g.re - sn->im * g.im);
        r->im = *cs * f.im + (sn->re * g.im + sn->im * g.re);
      }
    } else {
      f2s = sqrtf(g2 / f2 + 1.0F);
      r->re = f2s * fs_re;
      r->im = f2s * fs_im;
      *cs = 1.0F / f2s;
      f2 += g2;
      f2s = r->re / f2;
      scale = r->im / f2;
      sn->re = f2s * gs_re - scale * -gs_im;
      sn->im = f2s * -gs_im + scale * gs_re;
      if (rescaledir > 0) {
        for (rescaledir = 0; rescaledir <= count; rescaledir++) {
          r->re *= 5.49755814E+11F;
          r->im *= 5.49755814E+11F;
        }
      } else {
        if (rescaledir < 0) {
          for (rescaledir = 0; rescaledir <= count; rescaledir++) {
            r->re *= 1.8189894E-12F;
            r->im *= 1.8189894E-12F;
          }
        }
      }
    }
  }
}

/* End of code generation (xzlartg.c) */
