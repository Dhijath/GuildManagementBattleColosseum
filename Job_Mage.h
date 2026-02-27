/*==============================================================================

   魔法使いジョブ [Job_Mage.h]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

   ・Special：貫通魔法（MP消費）→ DEFの影響を軽減（DEF/4）

==============================================================================*/
#ifndef JOB_MAGE_H
#define JOB_MAGE_H

#include "JobBase.h"

class Job_Mage : public JobBase
{
public:
    void Attack(Fighter& self, Fighter& enemy) override;
    void Special(Fighter& self, Fighter& target) override;
    const char* GetJobName() const override { return "魔法使い"; }
    int GetSpecialCost() const override { return 12; }
    SpecialTarget GetSpecialTarget() const override { return SpecialTarget::ENEMY; }


private:
    static constexpr int COST_PIERCE = 120;
};

#endif // JOB_MAGE_H
