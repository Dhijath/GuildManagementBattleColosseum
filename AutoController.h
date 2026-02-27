/*==============================================================================

   AIコントローラ [AutoController.h]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

   ・単純ルールでそれっぽく動かす
   ・判定はHP率/MP/ジョブtargetだけ
   ・行動の最終補正はBattleCore側でやる

==============================================================================*/
#ifndef AUTOCONTROLLER_H
#define AUTOCONTROLLER_H

#include "Interface_BattleController.h"

class AutoController : public Interface_BattleController
{
public:
    ActionDecision Decide(
        Fighter& actor,
        const std::vector<Fighter*>& allies,
        const std::vector<Fighter*>& enemies) override;
};

#endif // AUTOCONTROLLER_H
