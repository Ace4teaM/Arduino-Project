#ifndef IEQUIPPROP_H
#define IEQUIPPROP_H

#include "model/Equipment.h"

class IEquipProp
{
public:
    virtual void applyProp(Equipment & equip) = 0;
};

#endif // IEQUIPPROP_H
