/*==============================================================================

   平民ジョブ [Job_Commoner.h]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

   ・Special：守護（MP消費）→ 対象の「次の被弾まで DEF×2」

==============================================================================*/
#ifndef JOB_COMMONER_H
#define JOB_COMMONER_H

#include "JobBase.h"


class Job_Commoner : public JobBase
{
public:
    void Attack(Fighter& self, Fighter& enemy) override;
    void Special(Fighter& self, Fighter& target) override;
    const char* GetJobName() const override { return "平民"; }
    int GetSpecialCost() const override { return 6; }
    SpecialTarget GetSpecialTarget() const override { return SpecialTarget::SELF_OR_ALLY; }



private:
    static constexpr int COST_GUARD = 60;

};

#endif // JOB_COMMONER_H
