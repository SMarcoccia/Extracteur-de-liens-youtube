
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

#include "ctypes.h"
#include "filename.h"

#define KEYBOARD_Idx 0 // Idx pour traitement du choix utilisateur.

enum KEYBOARD
{
  e_KEYBOARD_Quit = 0,
  e_KEYBOARD_Validate,
  e_KEYBOARD_Continue
};

// Nettoyage du buffer.
void Keyboard_CleanStdin(void);

// Gestion du clavier.
s32 Keyboard_ChoiceUserQuit(u32 idx); // Si l'utilisateur choisie de quitter.
s32 Keyboard_ChoiceUserValidate(u32 idx); // Si l'utilisateur choisie de valider le nom du lien.

#endif
