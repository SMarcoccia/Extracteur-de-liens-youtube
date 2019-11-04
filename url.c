
#include "url.h"



// Todo : recherche de la bonne url sans id.

// Gère les URL youtube.
struct SURL
{
  s32 nURL_Lg;
  char *pURL;
};

struct SURL gpUrl[] = {
  {0, "https://www.youtube.com/watch?v="}
};


void Url_InitLinkURL(void)
{
  gPlaylist.nLink_Nb = -1;

  Url_LgUrlLessId();
  Url_RecoveryUrlLessId();
}

void Url_CleanStrLinksURL(void)
{
  s32 i;
  for(i = 0; i < LINK_Nb; i++)
    gpLinksUrl[i].pLinkURL[0] = '\0';
}

void Url_LgUrlLessId(void)
{
  s32 i = 0;
  for(i = 0; i < (s32)NBELEM(gpUrl); i++)
  {
    gpUrl[i].nURL_Lg = strlen(gpUrl[i].pURL);
  }
}

void Url_RecoveryUrlLessId(void)
{ 
  int i = 0, j = 0;
    for(i = 0; i < LINK_Nb; i++)
      for(j = 0; j < gpUrl[0].nURL_Lg; j++)
        gpLinksUrl[i].pLinkURL[j] = gpUrl[0].pURL[j];
}

// Todo : si pas de palylist vérifier autrement.
u32 Url_RecoveryId(u32 nIdx)
{
    //Suppression des anciens fichiers .txt.
    Filename_InitFilenameOutPut(nIdx);
    Filename_RemoveFileOutPut();

    Playlist_InitSearchStartAndEndPlaylist();
    // On recherche la position du début et de fin de la playlist.
    Playlist_SearchStartAndEndPlaylist();
    
    // Playlist ? 
    if( ! (gPlaylist.nPosPlaylistStartFile && gPlaylist.nPosPlaylistEndFile))
    {
      // Todo: si pas de playlist. A paufiner
      rewind(gpFile);
      WordKey_Search(gpUrl[0].nURL_Lg); 
      // printf("Aucun liens trouvés pour %s.\n\n", gFilename[nIdx].pFilenameHTM);
      printf("%d liens trouvés pour %s\n", (gPlaylist.nLink_Nb + 1), gFilename[nIdx].pFilenameHTM);

      // return e_ERROR_Error;
    }
    else // Recherche du mot clé pour trouver l'id et récupération de l'id. 
    {
      WordKey_Search(gpUrl[0].nURL_Lg); 
      printf("%d liens trouvés pour %s\n", (gPlaylist.nLink_Nb + 1), gFilename[nIdx].pFilenameHTM);
    }

    fclose (gpFile);
    return e_ERROR_NotError;
}

u32 Url_LinksSaveTxt(u32 nIdx)
{   
  if(gPlaylist.nLink_Nb > 0)
  {
    s32 i = 0, nNumFile = 0; 
    errno = 0;

    Filename_InitFilenameOutPut(nIdx);    
    char *pStrEnd = "\r\n";

    // Ecriture des liens par lot et par fichier.
    for(i = 0; i <= gPlaylist.nLink_Nb; i++)
    {
      if( ! nNumFile) 
      {
        if((gpFile = fopen(gFilenameOutPut.pFilename, "w")) != NULL){}
        else
        {
          Error_FopenMsg(__FILE__, __LINE__, __FUNCTION__, "Couldn't to save links");  
          return e_ERROR_Error;
        }
      }
      
      // On écrit les liens dans le fichier.  
      fwrite(gpLinksUrl[i].pLinkURL, strlen(gpLinksUrl[i].pLinkURL), 1, gpFile);
      // Saut de ligne.
      if(nNumFile < NB_LINKS_BY_FILE_Output && i < gPlaylist.nLink_Nb)
        fwrite(pStrEnd, sizeof(*pStrEnd), strlen(pStrEnd), gpFile);
      Filename_NamingFileOutPut(&nNumFile); 
    }
    fclose(gpFile); 
  }
  return e_ERROR_NotError;
}

