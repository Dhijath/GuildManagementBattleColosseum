/*==============================================================================

   ジョブ基底クラス 実装 [JobBase.h]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef JOBBASE_H
#define JOBBASE_H

class Fighter;

// Special の対象種別
// SELF_OR_ALLY : 自分 or 味方（平民・僧侶）
// ENEMY        : 敵（戦士・魔法使い）
enum class SpecialTarget
{
    SELF_OR_ALLY,
    ENEMY
};

class JobBase
{
public:
    virtual ~JobBase() = default;

    // 通常攻撃（各ジョブ共通だが差し替え可能にしている）
    virtual void Attack(Fighter& self, Fighter& enemy) = 0;

    // Special の MP コスト
    virtual int GetSpecialCost() const = 0;

    // Special の対象種別
    virtual SpecialTarget GetSpecialTarget() const = 0;

    // Special 本体（MPは呼び出し側で消費）
    virtual void Special(Fighter& self, Fighter& target) = 0;

    // 表示用
    virtual const char* GetJobName() const = 0;
};

#endif // JOBBASE_H

