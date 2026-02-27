/*==============================================================================

   ドラゴン管理 [Orc.h]
                                                         Author : 51106
                                                         Date   : 2025/11/18
--------------------------------------------------------------------------------

==============================================================================*/
#include "Monster.h"


#ifndef ORC_H
#define ORC_H

class Orc :public Monster
{


public:
    Orc(const std::string& name,
        const std::string& job_name,
        int age,
        int lv,
        int hp,
        int mp,
        int atk,
        int def) :
        Monster(name, "オーク", job_name, age, lv, hp, mp, atk, def)
    {

    }

};


#endif
