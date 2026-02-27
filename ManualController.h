/*==============================================================================

   手動コントローラ [ManualController.h]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

   ・入力で行動を決める
   ・ターゲット候補が複数なら選ばせる

==============================================================================*/
#ifndef MANUALCONTROLLER_H
#define MANUALCONTROLLER_H

#include "Interface_BattleController.h"

class ManualController : public Interface_BattleController
{
public:
    ActionDecision Decide(
        Fighter& actor,
        const std::vector<Fighter*>& allies,
        const std::vector<Fighter*>& enemies) override;
};

#endif // MANUALCONTROLLER_H
