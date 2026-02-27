/*==============================================================================

   ジョブ生成 [JobFactory.h]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

   ・職業名（文字列）から JobBase を返す
   ・インスタンスは static にしてリークを避ける（状態を持たない設計前提）

==============================================================================*/
#ifndef JOBFACTORY_H
#define JOBFACTORY_H

#include <string>

class JobBase;

class JobFactory
{
public:
    static JobBase* CreateFromName(const std::string& jobName);
};

#endif // JOBFACTORY_H
