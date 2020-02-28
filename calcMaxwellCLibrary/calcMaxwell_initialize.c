/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * calcMaxwell_initialize.c
 *
 * Code generation for function 'calcMaxwell_initialize'
 *
 */

/* Include files */
#include "calcMaxwell_initialize.h"
#include "calcMaxwell.h"
#include "calcMaxwell_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void calcMaxwell_initialize(void)
{
  rt_InitInfAndNaN();
  isInitialized_calcMaxwell = true;
}

/* End of code generation (calcMaxwell_initialize.c) */
