/*==============================================================================

   僧侶ジョブ 実装 [Job_Priest.cpp]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "Job_Priest.h"
#include "Fighter.h"
#include <iostream>

void Job_Priest::Attack(Fighter& self, Fighter& enemy)
{
    self.NormalAttack(enemy);
}

void Job_Priest::Special(Fighter& self, Fighter& target)
{
    // target は味方（自分含む）想定
    if (!self.ConsumeMP(COST_HEAL))
    {
        std::cout << self.GetName() << " はMPが足りない！ → 通常攻撃へ\n";
        self.NormalAttack(target); // ※運用は味方対象で呼ぶ（2v2UIで制御）
        return;
    }

    const int before = target.GetHP();
    target.Heal(HEAL_VALUE);
    const int after = target.GetHP();

    std::cout << self.GetName() << " のヒール！ "
        << target.GetName() << " HP " << before << " → " << after
        << "\n";
}
