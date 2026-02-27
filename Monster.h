/*==============================================================================

   モンスター管理 [Monster.h]
														 Author : 51106
														 Date   : 2025/11/18
--------------------------------------------------------------------------------

==============================================================================*/

#include "Character.h"
#include <iostream>

#ifndef MONSTER_H
#define MONSTER_H

class Monster : public Character
{

private:
    std::string m_race_name{ "不明" };

public:
    // デフォルトコンストラクタ
    Monster()
        : Character()   // Character のデフォルトコンストラクタ呼ぶ
    {
    }

   
    Monster(const std::string& name,
        const std::string& race_name,
        const std::string& job_name,
        int age,
        int lv,
        int hp,
        int mp,
        int atk,
        int def)
        : Character(name, job_name, age, lv, hp, mp, atk, def),m_race_name(race_name)
    {
    }

    const std::string&GetRaceName()const
    {
        return m_race_name;
    }

    void SpecialAttack()
    {
        std::cout << "特殊攻撃"<<std::endl;
    }

};

#endif // !MONSTER_H

