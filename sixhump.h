/*
 * MATLAB Compiler: 4.14 (R2010b)
 * Date: Tue Dec 11 19:21:47 2012
 * Arguments: "-B" "macro_default" "-t" "-L" "C" "-W" "lib:sixhump" "-T"
 * "link:lib" "-h" "sixhump.m" "libmmfile.mlib" 
 */

#ifndef __sixhump_h
#define __sixhump_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_sixhump
#define PUBLIC_sixhump_C_API __global
#else
#define PUBLIC_sixhump_C_API /* No import statement needed. */
#endif

#define LIB_sixhump_C_API PUBLIC_sixhump_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_sixhump
#define PUBLIC_sixhump_C_API __declspec(dllexport)
#else
#define PUBLIC_sixhump_C_API __declspec(dllimport)
#endif

#define LIB_sixhump_C_API PUBLIC_sixhump_C_API


#else

#define LIB_sixhump_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_sixhump_C_API 
#define LIB_sixhump_C_API /* No special import/export declaration */
#endif

extern LIB_sixhump_C_API 
bool MW_CALL_CONV sixhumpInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_sixhump_C_API 
bool MW_CALL_CONV sixhumpInitialize(void);

extern LIB_sixhump_C_API 
void MW_CALL_CONV sixhumpTerminate(void);



extern LIB_sixhump_C_API 
void MW_CALL_CONV sixhumpPrintStackTrace(void);

extern LIB_sixhump_C_API 
bool MW_CALL_CONV mlxSixhump(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_sixhump_C_API 
long MW_CALL_CONV sixhumpGetMcrID();



extern LIB_sixhump_C_API bool MW_CALL_CONV mlfSixhump(int nargout, mxArray** sixhump, mxArray* x0, mxArray* x1);

#ifdef __cplusplus
}
#endif
#endif
