/*==============================================================================

   魔法使いジョブ 実装 [Job_Mage.cpp]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "Job_Mage.h"
#include "Fighter.h"
#include <iostream>

void Job_Mage::Attack(Fighter& self, Fighter& enemy)
{
    self.NormalAttack(enemy);
}

void Job_Mage::Special(Fighter& self, Fighter& target)
{
    // target は敵想定
    if (!self.ConsumeMP(COST_PIERCE))
    {
        std::cout << self.GetName() << " はMPが足りない！ → 通常攻撃へ\n";
        self.NormalAttack(target);
        return;
    }

    const int def = target.ConsumeEffectiveDEFForHit();

    int damage = self.GetATK() - (def / 4);
    if (damage < 1) damage = 1;

    target.Damage(damage);

    std::cout << self.GetName() << " の貫通魔法！ "
        << "ダメージ：" << damage
        << " / " << target.GetName() << " 残りHP：" << target.GetHP()
        << "\n";
}
