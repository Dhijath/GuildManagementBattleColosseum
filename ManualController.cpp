/*==============================================================================

   手動コントローラ 実装 [ManualController.cpp]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "ManualController.h"
#include "Fighter.h"
#include "JobBase.h"

#include <iostream>
#include <limits>

namespace
{
    bool ReadIntSafe(int& out)
    {
        std::cin >> out;
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        return true;
    }

    Fighter* SelectFrom(const std::vector<Fighter*>& list, const char* label)
    {
        if (list.empty()) return nullptr;
        if (list.size() == 1) return list[0];

        std::cout << label << " を選ぶ\n";
        for (size_t i = 0; i < list.size(); ++i)
        {
            std::cout << " " << (i + 1) << ". " << list[i]->GetName()
                << " (HP:" << list[i]->GetHP() << " MP:" << list[i]->GetMP() << ")\n";
        }

        int n = 1;
        std::cout << "番号 > ";
        if (!ReadIntSafe(n)) return list[0];

        if (n < 1 || n >(int)list.size()) return list[0];
        return list[(size_t)(n - 1)];
    }
}

ActionDecision ManualController::Decide(
    Fighter& actor,
    const std::vector<Fighter*>& allies,
    const std::vector<Fighter*>& enemies)
{
    ActionDecision d{};

    std::cout << "\n--- INPUT ---\n";
    std::cout << actor.GetName()
        << " [Lv." << actor.GetLv()
        << " / " << (actor.GetJob() ? actor.GetJob()->GetJobName() : "？")
        << "] "
        << "HP:" << actor.GetHP() << "/" << actor.GetMaxHP()
        << " MP:" << actor.GetMP()
        << "\n";

    std::cout << " 1. 通常攻撃\n";
    std::cout << " 2. 特殊能力（MP不足なら通常攻撃）\n";
    std::cout << "番号 > ";

    int cmd = 1;
    if (!ReadIntSafe(cmd)) cmd = 1;

    if (cmd != 2 || !actor.GetJob())
    {
        d.action = ActionType::NORMAL;
        d.target = SelectFrom(enemies, "攻撃対象");
        return d;
    }

    // SPECIALを選ぶ
    d.action = ActionType::SPECIAL;

    // target種別で候補を分ける
    const SpecialTarget st = actor.GetJob()->GetSpecialTarget();
    if (st == SpecialTarget::SELF_OR_ALLY)
    {
        d.target = SelectFrom(allies, "対象（味方）");
    }
    else
    {
        d.target = SelectFrom(enemies, "対象（敵）");
    }

    return d;
}

