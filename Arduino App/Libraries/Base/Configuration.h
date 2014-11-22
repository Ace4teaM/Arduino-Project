#ifndef configuration_h
#define configuration_h
#include <Arduino.h>
#include <inttypes.h>
#include "Message.h"

class Configuration{
public:
        Configuration();
        // lit les paramètres d'un message
        int LireParam(MessageTexte* message, char* ofs);
};

#endif
