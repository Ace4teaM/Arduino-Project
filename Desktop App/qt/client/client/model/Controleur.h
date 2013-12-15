/***********************************************************************
 * Module:  Controleur.h
 * Author:  developpement
 * Modified: dimanche 15 décembre 2013 19:08:54
 * Purpose: Declaration of the class Controleur
 ***********************************************************************/

#if !defined(__DATA_Controleur_h)
#define __DATA_Controleur_h

class Pin;

class Controleur
{
public:
   int controleurId;
   QString adresseIp;
   
   Pin** reserve;
   Pin** libre;

protected:
private:

};

#endif