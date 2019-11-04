#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <windows.h>

#include "ctypes.h"
#include "playlist.h"
#include "filename.h"
#include "extensionFile.h"
#include "keyboard.h"
#include "wordkey.h"
#include "url.h"



// Todo : Option, si plusieurs fichier htm, rajouter les liens des differents fichiers dans des .txt diff�rents.
// Todo : Option, Choisir le nombre de liens par .txt.
// Todo : si pas trouvé liens => rechercher liens autrements.
// Todo : entrer le noms de plusieurs pages html. 1 page une save.
// Todo : 25 liens / pages, ... oo / pages.
// Todo : glissé les pages sur appli. 
// Todo : enregistre les pages dans un dossier. 
// Todo : choix de l'emplacement du dossier.
// Todo : un nom de save par page html. (linksA001.txt ; linksB001.txt ...).
// Todo : entrer le nom de la save.
// Todo : un abon de 1 euro / mois. Si pas donné prog s'arrête.
// A REVOIR : extensionFile.c, ExtensionFile_Verif ligne : else // Netoyage de 
// suite : gFilename à partir du '.'.
// A REVOIR : filename.c, Filename_InitFilenameOutPut et Filename_RemoveFileOutPut : 
// suite : par rapport nbre de fichiers récupéré.
// Todo : voir realloc plus petit que le premier.
// Todo : test realloc pour char *tab[1000];
// Todo : création d'un dossier.
// Todo : gérer le retour arrière.
// Todo : dans le Url_RecoveryId paufiner si pas de playlist.
// Todo : faire un try si dépasse limite de liens.
// Todo : gérer si 2 mots clé dans un file. 
// Todo : gérer si pas de playlist mais vidéo en vrac et prend le mot clé pour la 
// playlist au lieu de celui contre.

u32 Main_Treatment_Filename(void)
{
  u32 i, nQuit = 0;
  for(i = 0; i < FILENAME_MAX_FILE; i++)
  {
    // Vérifie le choix utilisateur si c'est 'v' (validé) on break.
    if(Keyboard_ChoiceUserValidate(i))
    {
      ExtensionFile_Verif(i); 
      if((gpFile = fopen(gFilename[i].pFilenameHTM, "r")) != NULL)
      {
        if(Url_RecoveryId(i)) // Si pas de liens trouvé on break.
          break;
        // Todo: dans Filename_InitFilenameOutPut changer le nom du fichier 
        // en fonction du nombre de fichiers trouvés dans le repertoire, voir pour
        // mettre une variable nb de fichiers valides.
        if(Url_LinksSaveTxt(i)) 
          break;

        gPlaylist.nLink_Nb = -1;
      }
      else 
      {
        if((nQuit = Keyboard_ChoiceUserQuit(KEYBOARD_Idx))) 
        {       
          printf("\nImpossible d'ouvrir le fichier %s, le nom de fichier n'est pas valide.\n", gFilename[i].pFilenameHTM);
        }
        else
          break;
      }
    }
    else
      break;
  }  
  return 1;
}



int main(void)
{
  freopen("CON", "w", stdout);
  s32 nQuit = 1;
  // Attention récupère la liste qu'une fois. Voir pour remettre fopen.
  if((gnError = Filename_RecoveryListFilesDir()) > 0)
    goto MANAGEMENT_ERROR_1;
  else if(gnError == 0)
    return EXIT_FAILURE;

  Url_InitLinkURL();
  
  WordKey_RecoveryLg();

  while(nQuit)
  { 
    printf("\nEntrez les noms des fichiers html, tapez entree, puis v pour valider (q pour quitter).\n");

    if(Filename_RecoveryInputUser() == e_KEYBOARD_Quit)
      break;

    // Todo: normalement dans extensionfile qu'on dit si fichier existe ou pas.
    // Un message d'erreur si un fichier n'a pas été authentifier. 
    // Voir si fusionner recoveryInput et Keyboard un a un.
    if((gnError = Filename_RecoveryListFilesDir()) > 0)
      goto MANAGEMENT_ERROR_1;
    else if(gnError == 0)
      return EXIT_FAILURE;    
    nQuit = Main_Treatment_Filename();
 
  }

  Filename_ReleaseListFileDir();
  return EXIT_SUCCESS;

  MANAGEMENT_ERROR_1:
    Error_RelleaseAlloc(gnError);
  return EXIT_FAILURE;
}
