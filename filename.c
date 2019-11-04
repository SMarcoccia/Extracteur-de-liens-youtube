

#include "filename.h"

#define NB_MAX_FILE_DIR 5025

u32 Fileneame_ReallocListFilesDir(u32 nNbFiles, u32 nNbFilesMax)
{
  char **pTmp = NULL;
  if(nNbFiles >= nNbFilesMax )
    nNbFilesMax += NB_MAX_FILE_DIR;
  else
    return e_ERROR_NotError;

  if((pTmp = realloc(gFileDir.gpPtrFileDir, nNbFilesMax*sizeof(char *))) == NULL)
  {
    return Error_ReallocMsg(__FILE__, __LINE__, __FUNCTION__);
  }
  else
  {
    gFileDir.gpPtrFileDir = pTmp;
  }
  return e_ERROR_NotError;
}

u32 Filename_MallocFileListDir(struct dirent *ent, u32 nNbFiles)
{
  gFileDir.gpPtrFileDir[nNbFiles] = malloc((strlen(ent->d_name) + 1)*sizeof(char));

  if(gFileDir.gpPtrFileDir[nNbFiles] == NULL)
    return Error_MallocMsg(__FILE__, __LINE__, __FUNCTION__);

  return e_ERROR_NotError;
}

u32 Filename_RecoveryListFilesDir(void)
{
  DIR * rep = opendir("."); 
  u32 nNbFiles = 0, nNbFilesMax = 0;

  if (rep != NULL) 
  { 
    struct dirent * ent; 

    while ((ent = readdir(rep)) != NULL) 
    { 
      if(Fileneame_ReallocListFilesDir(nNbFiles, nNbFilesMax))
        return e_ERROR_RecoveryListFilesDir;

      if(Filename_MallocFileListDir(ent, nNbFiles))
        return e_ERROR_RecoveryListFilesDir;
      strcpy(gFileDir.gpPtrFileDir[nNbFiles], ent->d_name);
      nNbFiles++;
    } 
    closedir(rep); 
    gFileDir.nNbFilesDir = nNbFiles;
  }
  else
  {
    Error_OpendirMsg(__FILE__, __LINE__, __FUNCTION__);
    return e_ERROR_NotEffect;
  }
  return -1;
}

void Filename_ReleaseListFileDir(void)
{
  u32 i;

  for(i = 0; i < gFileDir.nNbFilesDir; i++)
  {
    free(gFileDir.gpPtrFileDir[i]);
    gFileDir.gpPtrFileDir[i] = NULL;
  }

  free(gFileDir.gpPtrFileDir);
    gFileDir.gpPtrFileDir = NULL;
}

u32 Filename_RecoveryInputUser(void)
{
  u32 i;

  for(i = 0; i < FILENAME_MAX_FILE; i++)
  {
    fgets(gFilename[i].pFilenameHTM, MAXPATHLEN + 1, stdin); // +1 pour '\0';
    gFilename[i].pFilenameHTM[strlen(gFilename[i].pFilenameHTM)-1] = '\0'; // On écrase le '\n'.

    if( ! Keyboard_ChoiceUserValidate(i))
      break;
    else if( ! Keyboard_ChoiceUserQuit(i))
      return e_KEYBOARD_Quit;
  }
  return e_KEYBOARD_Validate;
}

void Filename_InitFilenameOutPut(u32 nIdx)
{
  u32 i;
  char *pTmp = NULL;
  char pFileOutPut[FILENAME_MAXPATHLEN +1];
  gFilenameOutPut.nNumFile = 1;

  pTmp = strrchr(gFilename[nIdx].pFilenameHTM, '.');
  for(i = 0; gFilename[nIdx].pFilenameHTM+i < pTmp; i++)
    pFileOutPut[i] = gFilename[nIdx].pFilenameHTM[i];

  pFileOutPut[i] = '\0';

  strcat(pFileOutPut, " - 0001.txt");
  strcpy(gFilenameOutPut.pFilename, pFileOutPut);
}

void Filename_RemoveFileOutPut(void)
{
  s32 stop = 0;

  while(! stop)
  {
    stop = remove(gFilenameOutPut.pFilename);
    Filename_MyItoA_FileOutPut(++gFilenameOutPut.nNumFile, gFilenameOutPut.pFilename);
  }
}

void Filename_NamingFileOutPut(s32 *nNumFile)
{
  //Si on est arrivé au nombre de liens par fichier.
  if(++(*nNumFile) > NB_LINKS_BY_FILE_Output-1)// Si nb de liens  < nb de liens par lot.
  {
    fclose(gpFile);
    Filename_MyItoA_FileOutPut(++gFilenameOutPut.nNumFile, gFilenameOutPut.pFilename);
    *nNumFile = 0; 
  }
}

void Filename_MyItoA_FileOutPut(s32 nNb, char *pDst)
{
  u32 i;
  char *pStr = "0000";
  char *pTmp = strrchr(pDst, '.');
  
  for(i = 0, pTmp--; i < strlen(pStr); i++)
    *(pTmp - i) = *(pStr + i);

  char *pDstStart = strchr(pDst, '0');
  char *pDstEnd = strrchr(pDstStart, '0');

  u32 nTmp = nNb;
  do
  {
    *pDstEnd-- = (char)(nTmp % 10 + '0');
  }while(pDstEnd >= pDstStart && (nTmp /= 10) > 0);
}
