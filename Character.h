#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "Job.h"

class Character
{
private:
    std::string m_name{ "名無し" };
    Job  m_job;
    int  m_age{ 0 };
    int  m_Lv{ 1 };
    int  m_HP{ 0 };
    int  m_MP{ 0 };
    int  m_ATK{ 0 };   // 攻撃力
    int  m_DEF{ 0 };   // 防御力



public:
    // ===== コンストラクタ／デストラクタ =====
    Character();
    Character(const std::string& name, int job_id, int age, int lv, int hp, int mp, int atk, int def);
    Character(const std::string& name, const std::string& job_name, int age, int lv, int hp, int mp, int atk, int def);





    ~Character();

    

    // ===== セッター =====
    void SetName(const std::string& name) { m_name = name; }
    void SetAge(int age) { m_age = age; }
    void SetLv(int lv) { m_Lv = lv; }
    void SetHP(int hp) { m_HP = hp; }
    void SetMP(int mp) { m_MP = mp; }
    void SetATK(int atk) { m_ATK = atk; }
    void SetDEF(int def) { m_DEF = def; }


    // ===== ゲッター =====
    const std::string& GetName() const { return m_name; }
    int GetAge()  const { return m_age; }
    int GetLv()   const { return m_Lv; }
    int GetHP()   const { return m_HP; }
    int GetMP()   const { return m_MP; }
    int GetATK()  const { return m_ATK; }
    int GetDEF()  const { return m_DEF; }
    const Job& GetJob() const { return m_job; }


};

#endif
