/*==============================================================================

   êÌì¨ÉVÉXÉeÉÄ [Battle.h]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef BATTLE_H
#define BATTLE_H

#include "Fighter.h"
#include <cassert>

class Battle
{
private:
    Fighter* m_pFighter[2]{};
    int m_TurnCount{ 0 };

public:
    Battle(Fighter* pA, Fighter* pB)
        : m_pFighter{ pA, pB }
    {
        assert(pA && pB && "Battle: null Fighter passed.");
        assert(pA != pB && "Battle: same Fighter passed for both sides. (self attack)");
    }

    bool Fight();
};

#endif // BATTLE_H


