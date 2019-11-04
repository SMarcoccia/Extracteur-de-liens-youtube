#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "ctypes.h"
#include "url.h"

enum{
  e_ERROR_NotError, // Aucune erreur détecté.
  e_ERROR_Error
};

enum{
  e_ERROR_NotEffect,
  e_ERROR_RecoveryListFilesDir,
  e_ERROR_LinksSaveTxt
};

s32 gnError;
// Emet un message d'erreur et renvoie e_ERROR_Opendir.
u32 Error_OpendirMsg(char *pFile, u32 nLine, const char *pFunc);
// Emet un message d'erreur et renvoie e_ERROR_Malloc.
u32 Error_MallocMsg(char* pFile, u32 nLine, const char *pFunc);
// Emet un message d'erreur et renvoie e_ERROR_Realloc.
u32 Error_ReallocMsg(char* pFile, u32 nLine, const char *pFunc);
// Emet un message d'erreur et renvoie e_ERROR_Fopen.
u32 Error_FopenMsg(char* pFile, u32 nLine, const char *pFunc, const char *pMsg);
// Libère la mémoire des différentes allocations efféctués.
void Error_RelleaseAlloc(u32 nNoError);

#endif
