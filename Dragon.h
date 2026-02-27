/*==============================================================================

   ƒhƒ‰ƒSƒ“ŠÇ— [Dragon.h]
														 Author : 51106
														 Date   : 2025/11/18
--------------------------------------------------------------------------------

==============================================================================*/
#include "Monster.h"


#ifndef DRAGON_H
#define DRAGON_H

class Dragon:public Monster
{


public:
    Dragon(const std::string& name,
        const std::string& job_name,
        int age,
        int lv,
        int hp,
        int mp,
        int atk,
        int def) :
        Monster(name, "ƒhƒ‰ƒSƒ“", job_name, age, lv, hp, mp, atk, def)
    {

    }

};


#endif