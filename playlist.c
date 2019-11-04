
#include "playlist.h"

// Todo: rajouter : "playlistPanelVideoRenderer":{"title":{"simpleText":" recherche
// du titre. Pour la recherche du titre.

void Playlist_InitSearchStartAndEndPlaylist(void)
{
  gPlaylist.nPosPlaylistStartFile = 0; 
  gPlaylist.nPosPlaylistEndFile = 0; 
}

void Playlist_SearchStartAndEndPlaylist(void)
{
  s32 nCara = 0, ik = 0, jk = 0;
  gPlaylist.pPlaylistStart[0] = "\"playlist\":"; // Mot clé début liste.
  gPlaylist.nPlaylistStartLg = strlen(gPlaylist.pPlaylistStart[0]);
  
  gPlaylist.pPlaylistEnd[0] = "watchPlaylistEndpoint"; // Mot clé fin liste.
  gPlaylist.nPlaylistEndLg = strlen(gPlaylist.pPlaylistEnd[0]);
  //Recherche du mot clé d'entré de la playliste.
  do
  {
    nCara = fgetc(gpFile); // On peut faire une fonction.
    if(nCara == gPlaylist.pPlaylistStart[0][ik])
    {
      ik++;
    }
    else
    {
      ik = 0;
    }

    if(nCara == gPlaylist.pPlaylistEnd[0][jk])
    {
      jk++;
    }
    else
    {
      jk = 0;
    }

    // Récupération de la position du curseur au début de la playlist. 
    if(ik == gPlaylist.nPlaylistStartLg) //-1 car on commence à 0.
    {
      fgetpos(gpFile, &gPlaylist.nPosPlaylistStartFile);
    }
    
    // Récupération de la position du curseur à la fin de la playlist. 
    if(jk == gPlaylist.nPlaylistEndLg)
    {
      fgetpos(gpFile, &gPlaylist.nPosPlaylistEndFile);
      break;
    }
  }while(nCara != EOF);
}
