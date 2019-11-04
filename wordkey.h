
#ifndef __WORDKEY_H__
#define __WORDKEY_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "ctypes.h"
#include "playlist.h"
#include "url.h"

// Todo : pour plusieurs url youtube, dailymotion.
// Recherche du mot clé. Retourne 1 si realloc erreur, sinon 0.
void WordKey_Search(u32 nURL_Lg);
// Récupération des longueurs des mots clé.
void WordKey_RecoveryLg(void);

#endif
