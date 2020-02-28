/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * calcMaxwell.h
 *
 * Code generation for function 'calcMaxwell'
 *
 */

#ifndef CALCMAXWELL_H
#define CALCMAXWELL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "calcMaxwell_types.h"

/* Function Declarations */
extern void calcMaxwell(const float u[9], const float e[9], double w, double k1,
  double k2, creal32_T eigvec[16], creal32_T eigval[16], creal32_T maxMat[16]);

#endif

/* End of code generation (calcMaxwell.h) */
