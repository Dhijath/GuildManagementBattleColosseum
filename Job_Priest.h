/*==============================================================================

   僧侶ジョブ [Job_Priest.h]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

   ・Special：ヒール（MP消費）→ 対象（自分/味方）を回復

==============================================================================*/
#ifndef JOB_PRIEST_H
#define JOB_PRIEST_H

#include "JobBase.h"

class Job_Priest : public JobBase
{
public:
    void Attack(Fighter& self, Fighter& enemy) override;
    void Special(Fighter& self, Fighter& target) override;

    int GetSpecialCost() const override { return COST_HEAL; }
    SpecialTarget GetSpecialTarget() const override { return SpecialTarget::SELF_OR_ALLY; }


    const char* GetJobName() const override { return "僧侶"; }

private:
    static constexpr int COST_HEAL = 40;
    static constexpr int HEAL_VALUE = 60;
};


#endif // JOB_PRIEST_H

