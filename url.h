
#ifndef __URL_H__
#define __URL_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ctypes.h"
#include "playlist.h"
#include "filename.h"
#include "wordkey.h"
#include "keyboard.h"
#include "error.h"

#define URL_Nb 1 // Url hébergeurs.
#define NBELEM(tab) (sizeof(tab)/sizeof(tab[0])) // Utiliser que pour les tableau 
// static.
#define ID_Len 11 // Longueur de l'url. Attention bien mettre la taille total de 
// caractère du lien sinon ne marche pas.
#define LINK_Nb 1000 // Nombre de liens Max. 
// Todo : Géré LINK_Nb < Nb de liens dans le fichier.
#define LINK_LgURL 100

// Récupération des liens.
struct SLinkURL{
  char pLinkURL[LINK_LgURL]; 
};    

struct SLinkURL gpLinksUrl[LINK_Nb];

void Url_InitLinkURL(void);
void Url_ReleaseLinkURL(void); // Libération mémoire pour pLinkURL.
void Url_RecoveryUrlLessId(void); // Récupération de l'url sans l'id.
void Url_LgUrlLessId(void); // Calcule la longueur de l'url sans le id.
u32 Url_RecoveryId(u32 nIdx);  // Récuperation de l'id de la vidéo youtube. 
u32 Url_LinksSaveTxt(u32 nIdx); // Sauvegarde des liens dans un fichier.  
void Url_CleanStrLinksURL(void); // Nettoyage des chaînes des liens url avec '\0' à l'idx 0. 

#endif
