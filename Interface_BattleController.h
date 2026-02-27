/*==============================================================================

   戦闘操作インターフェース [Interface_BattleController.h]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

   ・手動/AIの分離ポイント

==============================================================================*/
#ifndef IBATTLECONTROLLER_H
#define IBATTLECONTROLLER_H

#include <vector>

class Fighter;

enum class ActionType
{
    NORMAL,
    SPECIAL
};

struct ActionDecision
{
    ActionType action{ ActionType::NORMAL };


    Fighter* target{ nullptr };
};

class Interface_BattleController
{
public:
    virtual ~Interface_BattleController() = default;

    // actorの行動を決める
    // allies/enemies は「生存者だけ」を渡す
    virtual ActionDecision Decide(
        Fighter& actor,
        const std::vector<Fighter*>& allies,
        const std::vector<Fighter*>& enemies) = 0;
};

#endif // IBATTLECONTROLLER_H
