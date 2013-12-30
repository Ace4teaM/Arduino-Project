#ifndef RIFF_H
#define RIFF_H

/*
 * Defintions utiles au format de fichier RIFF utilisé pour la configuration de l'arduino
*/

typedef struct _RIFF_EQUIP{
    int id;
    char name[64];
    char type[32];
}RIFF_EQUIP;

#endif // RIFF_H
