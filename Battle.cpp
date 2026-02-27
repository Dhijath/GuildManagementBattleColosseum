/*==============================================================================

   戦闘システム [Battle.cpp]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "Battle.h"
#include <iostream>
#include <limits>



// ターンのHP職業の表示をまとめておく
static void PrintStatus(const char* teamName, const Fighter* f)
{
    if (!f)
    {
        std::cout << teamName << " (null fighter)\n";
        return;
    }

    const char* job = (f->GetJob()) ? f->GetJob()->GetJobName() : "？";

    std::cout
        << "[" << teamName << "] "
        << f->GetName()
        << " [Lv." << f->GetLv()
        << " / " << job << "] "
        << "HP:" << f->GetHP()
        << " MP:" << f->GetMP()
        << "\n";
}



bool Battle::Fight()
{
    const int atk = m_TurnCount % 2;
    const int def = (m_TurnCount + 1) % 2;

    Fighter* pA = m_pFighter[atk];
    Fighter* pB = m_pFighter[def];

    std::cout << "\n===== Turn " << (m_TurnCount + 1) << " =====\n";
    PrintStatus("A", pA);
    PrintStatus("B", pB);

    std::cout << "\n" << pA->GetName() << " の行動\n";
    std::cout << " 1. 通常攻撃\n";
    std::cout << " 2. 特殊能力（MP不足なら通常攻撃）\n";
    std::cout << "番号 > ";

    int cmd = 1;
    std::cin >> cmd;

    if (cmd == 2)
    {
        pA->UseSpecialOrNormal(*pB);
    }
    else
    {
        pA->NormalAttack(*pB);
    }

    if (pB->IsKnockOut())
    {
        std::cout << "\n" << pB->GetName() << " は倒れた...\n";
        std::cout << "勝者： " << pA->GetName() << "\n";
        return true;
    }

    std::cout << "\n(Enterで次のターンへ)";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    ++m_TurnCount;



    return false;
}

