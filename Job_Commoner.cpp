/*==============================================================================

   •½–¯ƒWƒ‡ƒu ŽÀ‘• [Job_Commoner.cpp]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "Job_Commoner.h"
#include "Fighter.h"
#include <iostream>

void Job_Commoner::Attack(Fighter& self, Fighter& enemy)
{
    self.NormalAttack(enemy);
}

void Job_Commoner::Special(Fighter& self, Fighter& target)
{
    if (!self.ConsumeMP(COST_GUARD))
    {
        std::cout << self.GetName() << " ‚ÍMP‚ª‘«‚è‚È‚¢I ¨ ’ÊíUŒ‚‚Ö\n";
        self.NormalAttack(target); // target ‚ª“G‘z’è‚Ìê–Ê‚ÅŒÄ‚Ô‚Ì‚ªˆÀ‘S
        return;
    }

    target.ApplyDefBuffNextHit();
    std::cout << self.GetName() << " ‚ÌŽçŒìI "
        << target.GetName() << " ‚ÍŽŸ‚Ì”í’e‚Ü‚Å DEF~2\n";
}
