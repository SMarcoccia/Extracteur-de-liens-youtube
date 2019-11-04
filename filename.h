
#ifndef __FILENAME_H__
#define __FILENAME_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/param.h> 
#include <errno.h>

#include "ctypes.h"
#include "keyboard.h"
#include "error.h"

#define NB_LINKS_BY_FILE_Output  10000 // Nb de liens par fichier. Choix user.
#define FILENAME_MAX_FILE 50
#define FILENAME_MAXPATHLEN 260

FILE *gpFile; // Pointeur sur le fichier.

// Pour la récupération des fichiers dans un répertoire.
struct SFileDir{
  char **gpPtrFileDir;
  u32 nNbFilesDir;
};

struct SFileDir gFileDir;

// Gére le fichier htm(l).
struct SFilename{
  char pFilenameHTM[FILENAME_MAXPATHLEN +1]; // Nom du fichier htm. +1 pour le caractère de
  // fin de chaîne.
};
struct SFilename gFilename[FILENAME_MAX_FILE];

// Pour la création du fichier .txt de sortie contenant les URLs.
struct SFilenameOutPut
{
  s32 nNumFile; // N° du fichier à convertir en ASCII. 
  char pFilename[FILENAME_MAXPATHLEN +1]; // Nom du fichier.
};
struct SFilenameOutPut gFilenameOutPut;

// Conversion du n° du fichier .txt en ASCCI.
void Filename_MyItoA_FileOutPut(s32 nNb, char *pDst);

// Libération de la mémoire pour les noms des fichiers de la liste du repertoire.
void Filename_ReleaseListFileDir(void);
// Realloc du nombre de fichiers quand tout les slots dispo ont été remplies.
u32 Fileneame_ReallocListFilesDir(u32 nNbFiles, u32 nNbFilesMax);
// Récupération de la liste des fichiers d'un dossier.
u32 Filename_RecoveryListFilesDir(void);
// Malloc pour le nom du fichier à récupérer.
u32 Filename_MallocFileListDir(struct dirent *ent, u32 nNbFiles);

// Récupération du nom du fichier avec stdin (saisie utilisateur), avant entré.
u32 Filename_RecoveryInputUser(void);

// Init de la struct SFilenameOutPut.
void Filename_InitFilenameOutPut(u32 nIdx);
// Suppressions des anciens fichier de sortie.
void Filename_RemoveFileOutPut(void);
// Nommage des fichiers de sorties.
void Filename_NamingFileOutPut(s32 *nNumFile);

#endif
