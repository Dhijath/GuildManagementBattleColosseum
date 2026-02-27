/*==============================================================================

   戦闘コア [BattleCore.h]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

   ・1v1/2v2共通で回せるコア
   ・行動選択は Controller に委譲（ただしターゲット選択は Core が統一）
   ・行動順は Lv降順 → 現在HP降順 → 名前（ブレ防止）

==============================================================================*/
#ifndef BATTLECORE_H
#define BATTLECORE_H

#include <vector>

class Fighter;
class Interface_BattleController;

enum class TeamId
{
    A = 0,
    B = 1
};

class BattleCore
{
private:
    std::vector<Fighter*> m_teamA;
    std::vector<Fighter*> m_teamB;

    Interface_BattleController* m_ctrlA{ nullptr };
    Interface_BattleController* m_ctrlB{ nullptr };

    int m_turnCount{ 0 };

public:
    BattleCore(const std::vector<Fighter*>& teamA,
        const std::vector<Fighter*>& teamB);

    void SetController(TeamId team, Interface_BattleController* ctrl);

    bool Step(TeamId& outWinner);
    TeamId Run();

private:
    bool IsTeamAlive(const std::vector<Fighter*>& team) const;

    std::vector<Fighter*> BuildTurnOrder() const;

    Interface_BattleController* GetControllerOf(const Fighter* actor) const;
    TeamId GetTeamOf(const Fighter* actor) const;

    std::vector<Fighter*> BuildAllies(const Fighter* actor) const;
    std::vector<Fighter*> BuildEnemies(const Fighter* actor) const;

    Fighter* PickDefaultEnemy(const Fighter* actor, const std::vector<Fighter*>& enemies) const;
    Fighter* PickLowestHpRate(const Fighter* actor, const std::vector<Fighter*>& team) const;

    void ExecuteAction(Fighter& actor,
        const std::vector<Fighter*>& allies,
        const std::vector<Fighter*>& enemies,
        int choiceNormalOrSpecial);

    void PrintRoundHeader() const;
};

#endif // BATTLECORE_H


