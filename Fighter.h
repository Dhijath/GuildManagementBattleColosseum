/*==============================================================================

   ファイター管理 [Fighter.h]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

   ・GetName() を値返しに統一（ダングリング参照防止）

==============================================================================*/
#ifndef FIGHTER_H
#define FIGHTER_H

#include "Character.h"
#include "JobBase.h"
#include <string>

class Fighter
{
private:
    Character* m_pCharacter{ nullptr };

    int m_Hp{ 0 };
    int m_MaxHp{ 0 };
    int m_Mp{ 0 };

    JobBase* m_pJob{ nullptr };
    bool m_DefBuffNextHit{ false };

public:
    explicit Fighter(Character* pCharacter);

    void SetJob(JobBase* pJob) { m_pJob = pJob; }
    JobBase* GetJob() const { return m_pJob; }

    std::string GetName() const;
    int GetLv() const;

    int GetHP() const { return m_Hp; }
    int GetMaxHP() const { return m_MaxHp; }
    int GetMP() const { return m_Mp; }

    int GetATK() const;
    int GetBaseDEF() const;

    bool IsKnockOut() const { return m_Hp <= 0; }

    void NormalAttack(Fighter& enemy);

    // 1v1用（Battle.cppで使う）
    void UseSpecialOrNormal(Fighter& enemy);

    void Damage(int damage);
    void Heal(int value);
    bool ConsumeMP(int cost);

    void ApplyDefBuffNextHit();
    int ConsumeEffectiveDEFForHit();
};

#endif // FIGHTER_H
