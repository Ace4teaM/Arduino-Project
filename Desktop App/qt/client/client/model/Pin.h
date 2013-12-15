/***********************************************************************
 * Module:  Pin.h
 * Author:  developpement
 * Modified: dimanche 15 décembre 2013 19:08:54
 * Purpose: Declaration of the class Pin
 ***********************************************************************/

#if !defined(__DATA_Pin_h)
#define __DATA_Pin_h

class Equipement;
class Controleur;

class Pin
{
public:
   int pinId;
   QString pinType;
   int pinNum;
   
   Equipement** Requis;
   Controleur* reserve;
   Controleur* libre;

protected:
private:

};

#endif