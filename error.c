#include "error.h"

u32 Error_MallocMsg(char *pFile, u32 nLine, const char *pFunc)
{
  errno = 0;
  fprintf(stderr, "Malloc failed. %s. ", strerror(errno));
  #ifndef DEBUG
    printf("%s - Line: %d - Function : %s.\n", pFile, nLine, pFunc);
  #endif
  return e_ERROR_Error;
}

u32 Error_ReallocMsg(char *pFile, u32 nLine, const char *pFunc)
{
  errno = 0;
  fprintf(stderr, "Realloc failed. %s. ", strerror(errno));
  #ifndef DEBUG
    printf("%s - Line: %d - Function: %s.\n", pFile, nLine, pFunc);
  #endif
  return e_ERROR_Error;
}

u32 Error_OpendirMsg(char *pFile, u32 nLine, const char *pFunc)
{
  errno = 0;
  fprintf(stderr, "Couldn't open the folder%s", strerror(errno));
  #ifndef DEBUG
    printf("%s - Line: %d - Function: %s.\n", pFile, nLine, pFunc);
  #endif
  return e_ERROR_Error;
}

u32 Error_FopenMsg(char *pFile, u32 nLine, const char *pFunc, const char *pMsg)
{
  errno = 0;
  if(pMsg == NULL)
    fprintf(stderr, "Couldn't to open the file. %s. ", strerror(errno));
  else
    fprintf(stderr, "%s. %s. ", pMsg, strerror(errno));

  #ifndef DEBUG
    printf("%s - Line: %d - Function: %s.\n", pFile, nLine, pFunc);
  #endif
  return e_ERROR_Error;
}
  
void Error_RelleaseAlloc(u32 nNoError)
{
  switch(nNoError)
  {
    case e_ERROR_RecoveryListFilesDir:
      Filename_ReleaseListFileDir();
      printf("Je suis dans e_ERROR_RecoveryListFileDir\n");
  }
}
