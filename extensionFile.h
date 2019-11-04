
#ifndef __EXTENSIONFILE_H__
#define __EXTENSIONFILE_H__

#include <string.h>
#include <limits.h>

#include "ctypes.h"
#include "filename.h"

#define EXTENSION_Nb 2
#define EXTENSION_File {".htm", ".html"}
#define EXTENSION_NB_CARA (3 + 1) // 3 pour htm. 1 pour le pt, écrase le '\0' de la chaine à modifier.
#define NBELEM(tab) (sizeof(tab)/sizeof(tab[0]))

// Vérification de l'existence d'une extension d'un fichier.
// Retourne : 0 pour oui, 1 pour non.
s32 ExtensionFile_VerifExistence(char *pFilename, s32 nFilenameLg);
// Vérification de l'extension du fichier (gère uniquement htm).
void ExtensionFile_Verif(u32 i);

#endif
