
#include "keyboard.h"

#define Idx_FirstCara 0
#define Idx_SecondCara 1

void Keyboard_CleanStdin(void)
{
  s32 c;
  do
  {
    // ATTENTION voir si pas mettre stdout évite de retaper entrer ou clavier ou de réécrire dans 
    // la console.
    c = fgetc(stdin); 
  }while(c != '\n' && c !=EOF);
}

s32 Keyboard_ChoiceUserValidate(u32 idx)
{
  char nCara = gFilename[idx].pFilenameHTM[Idx_FirstCara];

  if(gFilename[idx].pFilenameHTM[Idx_SecondCara] == '\0' && (nCara == 'v' || nCara == 'V'))
    return 0;

  return 1;
}

s32 Keyboard_ChoiceUserQuit(u32 idx)
{
  char nCara = gFilename[idx].pFilenameHTM[Idx_FirstCara];

  if(gFilename[idx].pFilenameHTM[Idx_SecondCara] == '\0' && (nCara == 'q' || nCara == 'Q'))
    return 0;

  return 1;
}
