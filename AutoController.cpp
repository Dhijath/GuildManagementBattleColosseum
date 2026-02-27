/*==============================================================================

   自動コントローラ [AutoController.cpp]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

   ・HP状況に応じてSPECIAL/NORMALを選ぶ
   ・target は返さず nullptr 固定（ターゲットは BattleCore が決める）

==============================================================================*/
#include "AutoController.h"
#include "Fighter.h"

namespace
{
    // 0.0～1.0
    float HpRate(const Fighter* f)
    {
        if (!f) return 1.0f;
        const int maxHp = f->GetMaxHP();
        if (maxHp <= 0) return 1.0f;
        return static_cast<float>(f->GetHP()) / static_cast<float>(maxHp);
    }

    float MinHpRate(const std::vector<Fighter*>& v)
    {
        float best = 1.0f;
        for (auto* f : v)
        {
            if (!f) continue;
            const float r = HpRate(f);
            if (r < best) best = r;
        }
        return best;
    }
}

ActionDecision AutoController::Decide(
    Fighter& actor,
    const std::vector<Fighter*>& allies,
    const std::vector<Fighter*>& enemies)
{
    ActionDecision d{};
    d.target = nullptr; // BattleCoreが選ぶ

    JobBase* job = actor.GetJob();
    if (!job)
    {
        d.action = ActionType::NORMAL;
        return d;
    }

    const int cost = job->GetSpecialCost();
    const bool canSpecial = (actor.GetMP() >= cost);

    // SPECIALできないなら通常
    if (!canSpecial)
    {
        d.action = ActionType::NORMAL;
        return d;
    }

    const SpecialTarget st = job->GetSpecialTarget();

    // ----------------------------
    // SELF_OR_ALLY（回復/バフ系）
    // ----------------------------
    if (st == SpecialTarget::SELF_OR_ALLY)
    {
        // 自分 or 味方のHPが一定以下ならSPECIAL
        // 目安：70%未満で使う、50%未満なら優先度高
        const float selfRate = HpRate(&actor);
        const float allyMin = MinHpRate(allies);
        const float needRate = (allyMin < selfRate) ? allyMin : selfRate;

        d.action = (needRate <= 0.70f) ? ActionType::SPECIAL : ActionType::NORMAL;
        return d;
    }

    // ----------------------------
    // ENEMY（攻撃系）
    // ----------------------------
    // 「敵が居ない」なら通常（BattleCore側で勝敗処理されるが保険）
    if (enemies.empty())
    {
        d.action = ActionType::NORMAL;
        return d;
    }

    // 目安：
    // ・自分がピンチならSPECIALで畳み掛け（攻撃職想定）
    // ・敵が弱っている（HP率が低い）ならSPECIALで落とす
    // ・それ以外は通常
    const float selfRate = HpRate(&actor);
    const float enemyMin = MinHpRate(enemies);

    const bool selfInDanger = (selfRate <= 0.40f);   // 自分40%以下
    const bool enemyLow = (enemyMin <= 0.50f);   // 敵50%以下
    const bool mpPlenty = (actor.GetMP() >= cost * 2); // MPに余裕

    if (selfInDanger || enemyLow || mpPlenty)
        d.action = ActionType::SPECIAL;
    else
        d.action = ActionType::NORMAL;

    return d;
}


