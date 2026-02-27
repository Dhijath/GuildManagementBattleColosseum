/*==============================================================================

   ジョブ生成 実装 [JobFactory.cpp]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "JobFactory.h"
#include "JobBase.h"
#include "Job_Commoner.h"
#include "Job_Warrior.h"
#include "Job_Priest.h"
#include "Job_Mage.h"

JobBase* JobFactory::CreateFromName(const std::string& jobName)
{
    static Job_Commoner s_commoner;
    static Job_Warrior  s_warrior;
    static Job_Priest   s_priest;
    static Job_Mage     s_mage;

    if (jobName == "平民") return &s_commoner;
    if (jobName == "戦士") return &s_warrior;
    if (jobName == "僧侶") return &s_priest;
    if (jobName == "魔法使い") return &s_mage;

    // 未知は平民扱い（保険）
    return &s_commoner;
}

