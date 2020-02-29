#pragma once

#include "constants.h"
#include "BacteriaUnit.h"
#include <string>
#include <iostream>
#include <sstream>

typedef std::vector<Unit*> unitpack;

class Wave
{
private:
    static unitpack *create_unitpack(std::string &unit_name, int unit_count);
    /* data */
public:
    std::vector<unitpack*> packs;

    Wave(const char *filename);
   ~Wave();//delete all units inside
};
