#include <iostream>
#include "Character.h"



// デフォルト → 名前版コンストラクタに委譲
Character::Character()
    : Character("名無し", "平民", 1, 1, 50, 10, 10, 5)
{
   // std::cout << "デフォルトコンストラクタ\n";
}

// 職業IDで渡す版
Character::Character(const std::string& name,
    int job_id,
    int age,
    int lv,
    int hp,
    int mp,
    int atk,
    int def)
    : m_name(name)
    , m_job(job_id)   // Job(int id) を使う
    , m_age(age)
    , m_Lv(lv)
    , m_HP(hp)
    , m_MP(mp)
    , m_ATK(atk)
    , m_DEF(def)
{
    //std::cout << "引数コンストラクタ(ID版)\n";
}

// 職業名で渡す版
Character::Character(const std::string& name,
    const std::string& job_name,
    int age,
    int lv,
    int hp,
    int mp,
    int atk,
    int def)
    : m_name(name)
    , m_job(job_name) // Job(const std::string&) を使う
    , m_age(age)
    , m_Lv(lv)
    , m_HP(hp)
    , m_MP(mp)
    , m_ATK(atk)
    , m_DEF(def)
{
   // std::cout << "引数コンストラクタ(職業名版)\n";
}

Character::~Character()
{
   // std::cout << "デストラクタ\n";
}


// ===== セッター =====


//// ===== ゲッター =====
//std::string Character::GetName() { return m_name; }
//int Character::GetAge() { return m_age; }
//int Character::GetLv() { return m_Lv; }
//int Character::GetHP() { return m_HP; }
//int Character::GetMP() { return m_MP; }
//int Character::GetATK() { return m_ATK; }
//int Character::GetDEF() { return m_DEF; }
//Job Character::GetJob() { return m_job; }


// ===== ゲッター =====


