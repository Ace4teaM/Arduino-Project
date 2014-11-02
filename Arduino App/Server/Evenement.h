#ifndef evenement_h
#define evenement_h
#include <Arduino.h>
#include <inttypes.h>

class Evenement{
public:
        virtual int Executer()=0;
};


#endif
