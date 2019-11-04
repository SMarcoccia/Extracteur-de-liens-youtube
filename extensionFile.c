
#include "extensionFile.h"

char *pExtension[EXTENSION_Nb] = EXTENSION_File;

s32 ExtensionFile_VerifExistence(char *pFilename, s32 nFilenameLg)
{
  s32 nExtensionLg[EXTENSION_Nb];
  s32 nFilenameLg_Cnt = nFilenameLg; 
  s32 i = 0, j = 0, ii = 0;
  
  for(i = 0; i < EXTENSION_Nb; i++)
  {
    nExtensionLg[i] = strlen(pExtension[i])-1; // -1 car on ne compte pas le point.
  }

  for(i = 0; i < EXTENSION_Nb; i++)
  {
    j = nExtensionLg[i]; 
    while(pExtension[i][j] != '.')
    {
      if(pFilename[--nFilenameLg_Cnt] == pExtension[i][j]) 
      {
        ii++; 
      }
      else
      {
        nFilenameLg_Cnt = nFilenameLg;
        ii=0;
        break;
      }
      j--;
    }

    // L'extension existe ?
    if(ii ==  nExtensionLg[i])
    {
      return 0;
    }
  }

  return 1;
}

void ExtensionFile_Verif(u32 i)
{ 
  u32 nStrLg = strlen(gFilename[i].pFilenameHTM); 

  // Si l'extension n'existe pas on entre dans le if. 
  if(ExtensionFile_VerifExistence(gFilename[i].pFilenameHTM, nStrLg)) 
  {
    u32 j; 
    for(j = 0; j < NBELEM(pExtension); j++)
    {
      // Rajout du nom de l'extension.
      strcat(gFilename[i].pFilenameHTM, pExtension[j]); 

      // La bonne extension ? 
      u32 ij, nFileExist = 0;
      for(ij = 0; ij < gFileDir.nNbFilesDir; ij++)
      {
        if(! strcmp(gFileDir.gpPtrFileDir[ij], gFilename[i].pFilenameHTM))
        {
          nFileExist = 1;
          break;
        }
      }
      
      if(nFileExist) 
        break;
      else // Netoyage de gFilename à partir du '.'. 
      {
        char *pCara = strrchr(gFilename[i].pFilenameHTM, '.');
        u32 k;
        for(k = 0; pCara[k] != '\0'; k++)
        {
          pCara[k] = '\0';
        }
      }
    }
  }
}
