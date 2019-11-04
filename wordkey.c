
#include "wordkey.h"



#define NB_WORDKEY 4

// Structure qui gère les mots clés pour trouver les id.
struct SWordKey
{
  s32 pLenWordKey; // Longueur du mot clé.
  const char *pWordKey; // Mot clé pour récupération de l'id.
};

struct SWordKey gpWordKey[] = {
  // {0, "data-video-id=\""},
  // {0, "playlistVideoRenderer\":{\"videoId\":\""}, // Si fichier enregistrer comme playlist.htm.
  // {0, "\"removedVideoId\":\""},
  {0, "rel=\"null\" href=\"https://www.youtube.com/watch?v="}
};

void WordKey_RecoveryLg(void)
{
  s32 i = 0;
  for(i = 0; i < (s32)NBELEM(gpWordKey); i++)
  {
    gpWordKey[i].pLenWordKey = strlen(gpWordKey[i].pWordKey);
  }
}

void WordKey_Search(u32 nURL_Lg)
{
  s32 nCara = 0, i=0, k = 0, ij = 0, nVal = 0; 
  u32 j = nURL_Lg;
  gPlaylist.nLink_Nb = 0;
  
  // Recherche mot clé + récupération des Id. // Ici géré si 2 wordkey.
  for(ij = 0; ij < NB_WORDKEY; ij++)
  {
    do
    {
      nCara = fgetc(gpFile); 
      if(gpWordKey[ij].pWordKey[i] == nCara) 
      {
        i++;
      }
      else
        i=0;

      // Si on à trouvé un mot clé.
      if(i == gpWordKey[nVal].pLenWordKey) 
      { 
        // Récupération de l'Id.
        while((nCara = fgetc(gpFile)) != '"')
        {
          gpLinksUrl[k].pLinkURL[j] = nCara;
          j++;
        }
        gpLinksUrl[k].pLinkURL[j] = '\0';
        j = nURL_Lg; 
        gPlaylist.nLink_Nb = k++; 
        i = 0;
      }
    }while(nCara != EOF);

    if(gPlaylist.nLink_Nb != 0)
      break; 
    else  
    {
      nVal++;
      // Replace le curseur au début de l'emplacement de la playlist.
      fsetpos(gpFile, &gPlaylist.nPosPlaylistStartFile); 
      
    }
  }
}

