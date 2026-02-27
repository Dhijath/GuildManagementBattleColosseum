/*==============================================================================

   戦闘コア 実装 [BattleCore.cpp]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------
 
==============================================================================*/
#include "BattleCore.h"
#include "Interface_BattleController.h"
#include "Fighter.h"
#include "JobBase.h"

#include <algorithm>
#include <iostream>
#include <string>

namespace
{
    float HpRate(const Fighter* f)
    {
        if (!f) return 1.0f;
        const int maxHp = f->GetMaxHP();
        if (maxHp <= 0) return 1.0f;
        return static_cast<float>(f->GetHP()) / static_cast<float>(maxHp);
    }

    void PrintStatusLine(const char* teamName, const Fighter* f)
    {
        if (!f)
        {
            std::cout << "[" << teamName << "] (null fighter)\n";
            return;
        }

        const char* job = (f->GetJob()) ? f->GetJob()->GetJobName() : "？";

        std::cout
            << "[" << teamName << "] "
            << f->GetName()
            << " [Lv." << f->GetLv()
            << " / " << job << "] "
            << "HP:" << f->GetHP() << "/" << f->GetMaxHP()
            << " MP:" << f->GetMP()
            << "\n";
    }


    bool Contains(const std::vector<Fighter*>& v, const Fighter* p)
    {
        return std::find(v.begin(), v.end(), p) != v.end();
    }
}

BattleCore::BattleCore(const std::vector<Fighter*>& teamA,
    const std::vector<Fighter*>& teamB)
    : m_teamA(teamA)
    , m_teamB(teamB)
{
}

void BattleCore::SetController(TeamId team, Interface_BattleController* ctrl)
{
    if (team == TeamId::A) m_ctrlA = ctrl;
    else m_ctrlB = ctrl;
}

bool BattleCore::IsTeamAlive(const std::vector<Fighter*>& team) const
{
    for (auto* f : team)
    {
        if (f && !f->IsKnockOut()) return true;
    }
    return false;
}

std::vector<Fighter*> BattleCore::BuildTurnOrder() const
{
    std::vector<Fighter*> order;
    order.reserve(m_teamA.size() + m_teamB.size());

    for (auto* f : m_teamA) if (f && !f->IsKnockOut() && !Contains(order, f)) order.push_back(f);
    for (auto* f : m_teamB) if (f && !f->IsKnockOut() && !Contains(order, f)) order.push_back(f);

    std::sort(order.begin(), order.end(),
        [](Fighter* a, Fighter* b)
        {
            if (a->GetLv() != b->GetLv()) return a->GetLv() > b->GetLv();
            if (a->GetHP() != b->GetHP()) return a->GetHP() > b->GetHP();
            return a->GetName() < b->GetName();
        });

    return order;
}

TeamId BattleCore::GetTeamOf(const Fighter* actor) const
{
    for (auto* f : m_teamA) if (f == actor) return TeamId::A;
    return TeamId::B;
}

Interface_BattleController* BattleCore::GetControllerOf(const Fighter* actor) const
{
    return (GetTeamOf(actor) == TeamId::A) ? m_ctrlA : m_ctrlB;
}

std::vector<Fighter*> BattleCore::BuildAllies(const Fighter* actor) const
{
    const auto& team = (GetTeamOf(actor) == TeamId::A) ? m_teamA : m_teamB;

    std::vector<Fighter*> allies;
    allies.reserve(team.size());

    for (auto* f : team)
    {
        if (!f) continue;
        if (f == actor) continue;          // 　自分は allies から除外（自分対象は別ルールで処理）
        if (f->IsKnockOut()) continue;
        if (Contains(allies, f)) continue;
        allies.push_back(f);
    }
    return allies;
}

std::vector<Fighter*> BattleCore::BuildEnemies(const Fighter* actor) const
{
    const auto& team = (GetTeamOf(actor) == TeamId::A) ? m_teamB : m_teamA;

    std::vector<Fighter*> enemies;
    enemies.reserve(team.size());

    for (auto* f : team)
    {
        if (!f) continue;
        if (f == actor) continue;          // 　絶対に入れない
        if (f->IsKnockOut()) continue;
        if (Contains(enemies, f)) continue;
        enemies.push_back(f);
    }
    return enemies;
}

Fighter* BattleCore::PickDefaultEnemy(const Fighter* actor, const std::vector<Fighter*>& enemies) const
{
    // 「HP率が低い敵」優先（落とし切り）
    Fighter* best = nullptr;
    float bestRate = 1.0f;

    for (auto* e : enemies)
    {
        if (!e) continue;
        if (e == actor) continue;
        if (e->IsKnockOut()) continue;

        const float r = HpRate(e);
        if (!best || r < bestRate)
        {
            best = e;
            bestRate = r;
        }
    }
    return best;
}

Fighter* BattleCore::PickLowestHpRate(const Fighter* actor, const std::vector<Fighter*>& team) const
{
    Fighter* best = nullptr;
    float bestRate = 1.0f;

    for (auto* f : team)
    {
        if (!f) continue;
        if (f == actor) continue;
        if (f->IsKnockOut()) continue;

        const float r = HpRate(f);
        if (!best || r < bestRate)
        {
            best = f;
            bestRate = r;
        }
    }
    return best;
}

void BattleCore::ExecuteAction(Fighter& actor,
    const std::vector<Fighter*>& allies,
    const std::vector<Fighter*>& enemies,
    int choiceNormalOrSpecial)
{
    Fighter* defaultEnemy = PickDefaultEnemy(&actor, enemies);
    if (!defaultEnemy) return;

    // NORMAL：必ず敵
    if (choiceNormalOrSpecial == 1)
    {
        actor.NormalAttack(*defaultEnemy);
        return;
    }

    // SPECIAL：job無しなら通常攻撃
    JobBase* job = actor.GetJob();
    if (!job)
    {
        actor.NormalAttack(*defaultEnemy);
        return;
    }

    Fighter* target = nullptr;

    if (job->GetSpecialTarget() == SpecialTarget::SELF_OR_ALLY)
    {
        // alliesが居ればHP率が低い味方、居なければ自分
        Fighter* ally = PickLowestHpRate(&actor, allies);
        target = ally ? ally : &actor;
    }
    else
    {
        // ENEMY：必ず敵
        target = defaultEnemy;
    }

    const int cost = job->GetSpecialCost();
    if (!actor.ConsumeMP(cost))
    {
        actor.NormalAttack(*defaultEnemy);
        return;
    }

    job->Special(actor, *target);
}

void BattleCore::PrintRoundHeader() const
{
    std::cout << "\n==============================\n";
    std::cout << " Turn " << (m_turnCount + 1) << "\n";
    std::cout << "==============================\n";
}

bool BattleCore::Step(TeamId& outWinner)
{
    if (!IsTeamAlive(m_teamA)) { outWinner = TeamId::B; return true; }
    if (!IsTeamAlive(m_teamB)) { outWinner = TeamId::A; return true; }

    PrintRoundHeader();

    for (auto* f : m_teamA)
        if (f) PrintStatusLine("A", f);

    for (auto* f : m_teamB)
        if (f) PrintStatusLine("B", f);


    auto order = BuildTurnOrder();
    for (auto* actor : order)
    {
        if (!actor || actor->IsKnockOut()) continue;

        auto allies = BuildAllies(actor);
        auto enemies = BuildEnemies(actor);

        Fighter* defaultEnemy = PickDefaultEnemy(actor, enemies);
        if (!defaultEnemy)
        {
            outWinner = GetTeamOf(actor);
            return true;
        }

        Interface_BattleController* ctrl = GetControllerOf(actor);

        int choice = 1; // default NORMAL
        if (ctrl)
        {
            ActionDecision d = ctrl->Decide(*actor, allies, enemies);
            choice = (d.action == ActionType::SPECIAL) ? 2 : 1;
        }

        ExecuteAction(*actor, allies, enemies, choice);

        if (!IsTeamAlive(m_teamA)) { outWinner = TeamId::B; return true; }
        if (!IsTeamAlive(m_teamB)) { outWinner = TeamId::A; return true; }
    }


    ++m_turnCount;

    // 1ラウンド（Turn）ごとに Enter 待ち
    std::cout << "\n(Enterで次のターンへ)";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string dummy;
    std::getline(std::cin, dummy);

    return false;

}

TeamId BattleCore::Run()
{
    TeamId winner = TeamId::A;
    while (!Step(winner)) {}
    return winner;
}
