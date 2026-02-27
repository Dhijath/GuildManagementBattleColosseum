/*==============================================================================

   ímƒWƒ‡ƒu [Job_Warrior.h]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

   ESpecialF‹­‘ÅiMPÁ”ïj¨ 1.5”{UŒ‚i–hŒäŒvZ‚ ‚èj

==============================================================================*/
#ifndef JOB_WARRIOR_H
#define JOB_WARRIOR_H

#include "JobBase.h"

class Job_Warrior : public JobBase
{
public:
    void Attack(Fighter& self, Fighter& enemy) override;
    void Special(Fighter& self, Fighter& target) override;
    const char* GetJobName() const override { return "ím"; }
    int GetSpecialCost() const override { return 10; }
    SpecialTarget GetSpecialTarget() const override{return SpecialTarget::ENEMY;}



private:

    static constexpr int COST_POWER = 100;
};

#endif // JOB_WARRIOR_H
