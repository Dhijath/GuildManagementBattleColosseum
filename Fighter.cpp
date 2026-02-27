/*==============================================================================

   ファイター管理 [Fighter.cpp]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "Fighter.h"
#include <iostream>

Fighter::Fighter(Character* pCharacter)
    : m_pCharacter(pCharacter)
{
    if (!m_pCharacter)
    {
        m_Hp = 0; m_MaxHp = 0; m_Mp = 0;
        return;
    }
    m_Hp = m_pCharacter->GetHP();
    m_MaxHp = m_pCharacter->GetHP();
    m_Mp = m_pCharacter->GetMP();
}

std::string Fighter::GetName() const
{
    return m_pCharacter ? m_pCharacter->GetName() : "null";
}

int Fighter::GetLv() const
{
    return m_pCharacter ? m_pCharacter->GetLv() : 0;
}

int Fighter::GetATK() const
{
    return m_pCharacter ? m_pCharacter->GetATK() : 0;
}

int Fighter::GetBaseDEF() const
{
    return m_pCharacter ? m_pCharacter->GetDEF() : 0;
}

bool Fighter::ConsumeMP(int cost)
{
    if (cost < 0) cost = 0;
    if (m_Mp < cost) return false;
    m_Mp -= cost;
    return true;
}

void Fighter::Heal(int value)
{
    if (value < 0) value = 0;
    m_Hp += value;
    if (m_Hp > m_MaxHp) m_Hp = m_MaxHp;
}

void Fighter::Damage(int damage)
{
    if (damage < 1) damage = 1;
    m_Hp -= damage;
    if (m_Hp < 0) m_Hp = 0;
}

void Fighter::ApplyDefBuffNextHit()
{
    m_DefBuffNextHit = true;
}

int Fighter::ConsumeEffectiveDEFForHit()
{
    int def = GetBaseDEF();
    if (m_DefBuffNextHit)
    {
        def *= 2;
        m_DefBuffNextHit = false;
    }
    return def;
}

void Fighter::NormalAttack(Fighter& enemy)
{
    const int def = enemy.ConsumeEffectiveDEFForHit();
    int damage = GetATK() - (def / 2);
    if (damage < 1) damage = 1;

    enemy.Damage(damage);

    std::cout << GetName() << " の通常攻撃！ "
        << "ダメージ：" << damage
        << " / " << enemy.GetName() << " 残りHP：" << enemy.GetHP()
        << "\n";
}

void Fighter::UseSpecialOrNormal(Fighter& enemy)
{
    if (!m_pJob)
    {
        NormalAttack(enemy);
        return;
    }

    const int cost = m_pJob->GetSpecialCost();
    if (!ConsumeMP(cost))
    {
        std::cout << GetName() << " はMPが足りない！ → 通常攻撃へ\n";
        NormalAttack(enemy);
        return;
    }

    Fighter& target =
        (m_pJob->GetSpecialTarget() == SpecialTarget::SELF_OR_ALLY) ? *this : enemy;

    std::cout << GetName() << " は " << m_pJob->GetJobName() << " の特殊能力！\n";
    m_pJob->Special(*this, target);
}
