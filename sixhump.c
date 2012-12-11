/*
 * MATLAB Compiler: 4.14 (R2010b)
 * Date: Tue Dec 11 19:21:47 2012
 * Arguments: "-B" "macro_default" "-t" "-L" "C" "-W" "lib:sixhump" "-T"
 * "link:lib" "-h" "sixhump.m" "libmmfile.mlib" 
 */

#include <stdio.h>
#define EXPORTING_sixhump 1
#include "sixhump.h"

static HMCRINSTANCE _mcr_inst = NULL;


#if defined( _MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__) || defined(__LCC__)
#ifdef __LCC__
#undef EXTERN_C
#endif
#include <windows.h>

static char path_to_dll[_MAX_PATH];

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, void *pv)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        if (GetModuleFileName(hInstance, path_to_dll, _MAX_PATH) == 0)
            return FALSE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
    }
    return TRUE;
}
#endif
#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultPrintHandler(const char *s)
{
  return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultErrorHandler(const char *s)
{
  int written = 0;
  size_t len = 0;
  len = strlen(s);
  written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
  if (len > 0 && s[ len-1 ] != '\n')
    written += mclWrite(2 /* stderr */, "\n", sizeof(char));
  return written;
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_sixhump_C_API
#define LIB_sixhump_C_API /* No special import/export declaration */
#endif

LIB_sixhump_C_API 
bool MW_CALL_CONV sixhumpInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler)
{
    int bResult = 0;
  if (_mcr_inst != NULL)
    return true;
  if (!mclmcrInitialize())
    return false;
  if (!GetModuleFileName(GetModuleHandle("sixhump"), path_to_dll, _MAX_PATH))
    return false;
    {
        mclCtfStream ctfStream = 
            mclGetEmbeddedCtfStream(path_to_dll, 
                                    84217);
        if (ctfStream) {
            bResult = mclInitializeComponentInstanceEmbedded(   &_mcr_inst,
                                                                error_handler, 
                                                                print_handler,
                                                                ctfStream, 
                                                                84217);
            mclDestroyStream(ctfStream);
        } else {
            bResult = 0;
        }
    }  
    if (!bResult)
    return false;
  return true;
}

LIB_sixhump_C_API 
bool MW_CALL_CONV sixhumpInitialize(void)
{
  return sixhumpInitializeWithHandlers(mclDefaultErrorHandler, mclDefaultPrintHandler);
}

LIB_sixhump_C_API 
void MW_CALL_CONV sixhumpTerminate(void)
{
  if (_mcr_inst != NULL)
    mclTerminateInstance(&_mcr_inst);
}

LIB_sixhump_C_API 
long MW_CALL_CONV sixhumpGetMcrID() 
{
  return mclGetID(_mcr_inst);
}

LIB_sixhump_C_API 
void MW_CALL_CONV sixhumpPrintStackTrace(void) 
{
  char** stackTrace;
  int stackDepth = mclGetStackTrace(&stackTrace);
  int i;
  for(i=0; i<stackDepth; i++)
  {
    mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
    mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
  }
  mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_sixhump_C_API 
bool MW_CALL_CONV mlxSixhump(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "sixhump", nlhs, plhs, nrhs, prhs);
}

LIB_sixhump_C_API 
bool MW_CALL_CONV mlfSixhump(int nargout, mxArray** sixhump, mxArray* x0, mxArray* x1)
{
  return mclMlfFeval(_mcr_inst, "sixhump", nargout, 1, 2, sixhump, x0, x1);
}
