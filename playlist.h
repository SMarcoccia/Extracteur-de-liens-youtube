
#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ctypes.h"
#include "filename.h"


#define WORDKEY_Playlist_Nb 1 // Nombre paire de mots clés (dans le fichier) 
// du début et de fin de la playlist.

struct SPlaylist
{
  char *pPlaylistStart[WORDKEY_Playlist_Nb]; // Mot clé début liste.
  s32 nPlaylistStartLg;
  char *pPlaylistEnd[WORDKEY_Playlist_Nb]; // Mot clé fin liste.
  s32 nPlaylistEndLg;
  
  fpos_t nPosPlaylistStartFile; // Pos du curseur au départ de la playlist.
  fpos_t nPosPlaylistEndFile; // Pos du curseur à la fin de la playlist.
  fpos_t nPosCaraStartId;

  s32 nLink_Nb; // Nb de liens.
};

struct SPlaylist gPlaylist;

void Playlist_InitSearchStartAndEndPlaylist(void);
// Todo faire un gPlaylistInit.
// Recherche le mot clé du début de la playlist et celui de fin qui encadre les id des liens.
// Evite de repartir au début du fichier pour la recherche des mots clés.
void Playlist_SearchStartAndEndPlaylist(void); 


#endif
