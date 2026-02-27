/*==============================================================================

   戦士ジョブ 実装 [Job_Warrior.cpp]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "Job_Warrior.h"
#include "Fighter.h"
#include <iostream>

void Job_Warrior::Attack(Fighter& self, Fighter& enemy)
{
    self.NormalAttack(enemy);
}

void Job_Warrior::Special(Fighter& self, Fighter& target)
{
    // target は敵想定
    if (!self.ConsumeMP(COST_POWER))
    {
        std::cout << self.GetName() << " はMPが足りない！ → 通常攻撃へ\n";
        self.NormalAttack(target);
        return;
    }

    const int def = target.ConsumeEffectiveDEFForHit();

    int damage = (self.GetATK() * 3 / 2) - (def / 2);
    if (damage < 1) damage = 1;

    target.Damage(damage);

    std::cout << self.GetName() << " の強打！！ "
        << "ダメージ：" << damage
        << " / " << target.GetName() << " 残りHP：" << target.GetHP()
        << "\n";
}

