#include "Wave.h"

unitpack *Wave::create_unitpack(std::string &unit_name, int unit_count)
{
    unitpack *unit_pack = new unitpack;
    
    if (unit_name == "BacteriaUnit")
        for (int i = 0; i < unit_count; i++)
        {
            Unit *unit = new BacteriaUnit(/**/);
            unit_pack->push_back(unit);
        }
    else if (unit_name == "VirusUnit")
        for (int i = 0; i < unit_count; i++)
        {
            Unit *unit = new BacteriaUnit(/**/);
            unit_pack->push_back(unit);
        }
    else
        printf("wrong wave file\n");
    
    return unit_pack;
}


Wave::Wave(const char *wave_info)
{
    std::string input(wave_info);
    std::istringstream stream(input);
    std::string unit_name;
    int unit_count = -1;
    while (!stream.eof())
    {
        stream >> unit_name >> unit_count;
        unitpack *unit_pack = create_unitpack(unit_name, unit_count);
        this->packs.push_back(unit_pack);
    }
}

Wave::~Wave()
{
    for (auto &pack : this->packs)
    {
        for (auto &unit : *pack)
            delete unit;
        delete pack;        
    }
}
