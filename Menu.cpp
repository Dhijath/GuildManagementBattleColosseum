/*==============================================================================

   メニュー管理 [Menu.cpp]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "Menu.h"
#include "MenuSort.h"
#include "Character.h"
#include "Guild.h"
#include "Battle.h"


#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include "JobFactory.h"
#include "BattleCore.h"
#include "ManualController.h"
#include "AutoController.h"





//==============================================================================
// 入力補助
//==============================================================================
namespace
{
    bool ReadInt(int& out)
    {
        std::cin >> out;
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        return true;
    }

    void WaitEnter()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enterで戻る > ";
        std::cin.get();
    }

    //==========================================================================
    // ギルドの現在状態から「表示順（配列番号）」を作る（No固定）
    //==========================================================================
    std::vector<int> BuildDefaultOrder(Guild& guild, int maxSize)
    {
        std::vector<int> order;
        Character** members = guild.GetMembers();

        for (int i = 0; i < maxSize; ++i)
        {
            if (members[i]) order.push_back(i);
        }
        return order;
    }

    //==========================================================================
    // Guild::Display_List と同等の1行表示（順番だけ order に従う）
    //==========================================================================
    void PrintListLikeGuild(Guild& guild, const std::vector<int>& order)
    {
        Character** members = guild.GetMembers();

        for (int idx : order)
        {
            Character* p = members[idx];
            if (!p) continue;

            std::cout << "No." << idx + 1 << ":" << p->GetName();
            std::cout << p->GetJob().GetName();
            std::cout << "《Lv." << p->GetLv() << "》";
            std::cout << p->GetJob().GetName() << std::endl;
        }
    }

    //==========================================================================
    // 並び替え種類選択（※重複しない名前）
    //==========================================================================
    bool SelectSortType_Manage(MenuSort::SortType& outType)
    {
        std::cout << "\n--- 並び替え---\n";
        std::cout << " 1. Lv\n";
        std::cout << " 2. HP\n";
        std::cout << " 3. MP\n";
        std::cout << " 4. ATK\n";
        std::cout << " 5. DEF\n";
        std::cout << " 0. キャンセル\n";
        std::cout << "番号 > ";

        int s = -1;
        if (!ReadInt(s)) return false;

        switch (s)
        {
        case 0: return false;
        case 1: outType = MenuSort::SortType::LEVEL; break;
        case 2: outType = MenuSort::SortType::HP;    break;
        case 3: outType = MenuSort::SortType::MP;    break;
        case 4: outType = MenuSort::SortType::ATK;   break;
        case 5: outType = MenuSort::SortType::DEF;   break;
        default:
            std::cout << "0～5 を選んでね。\n";
            return false;
        }
        return true;
    }
}

//==============================================================================
// Menu 本体
//==============================================================================
Menu::Menu(Guild& guild)
    : m_guild(guild)
{
}

void Menu::Show()
{
    std::cout << "\n==============================\n";
    std::cout << "        ギルドメニュー\n";
    std::cout << "==============================\n";
    std::cout << " 1. 加入\n";
    std::cout << " 2. 脱退\n";
    std::cout << " 3. メンバー管理（一覧・詳細・並び替え）\n";
    std::cout << " 4. バトルコロシアム《1v1or2v2》\n";
    std::cout << " 0. 終了\n";
    std::cout << "------------------------------\n";
    std::cout << "番号 > ";
}

void Menu::Run()
{
    int cmd = -1;

    while (true)
    {
        Show();

        if (!ReadInt(cmd))
        {
            std::cout << "数字を入力してね。\n";
            continue;
        }

        switch (cmd)
        {
        case 0: return;
        case 1: CmdJoin(); break;
        case 2: CmdLeave(); break;
        case 3: CmdManageMembers(); break;
        case 4: CmdBattle(); break;
        default:
            std::cout << "0～4 を選んでね。\n";
            break;
        }
    }
}



//==============================================================================
// 1) 加入
//==============================================================================
void Menu::CmdJoin()
{
    std::string name, job;
    int age, lv, hp, mp, atk, def;

    std::cout << "名前: ";
    std::cin >> name;

    std::cout << "職業名: ";
    std::cin >> job;

    std::cout << "年齢: ";
    if (!ReadInt(age)) return;

    std::cout << "Lv: ";
    if (!ReadInt(lv)) return;

    std::cout << "HP: ";
    if (!ReadInt(hp)) return;

    std::cout << "MP: ";
    if (!ReadInt(mp)) return;

    std::cout << "ATK: ";
    if (!ReadInt(atk)) return;

    std::cout << "DEF: ";
    if (!ReadInt(def)) return;

    m_guild.Joining(new Character(name, job, age, lv, hp, mp, atk, def));
    std::cout << name << " を加入させました。\n";
}

//==============================================================================
// 2) 脱退（No＝配列番号+1で固定）
//==============================================================================
void Menu::CmdLeave()
{
    int no = -1;
    std::cout << "脱退させたい No.(1～) > ";
    if (!ReadInt(no)) return;

    // Guild側が 0始まりで受け取る仕様なら -1 して渡す
    m_guild.Whithdrawal(no - 1);
    std::cout << "脱退処理を行いました。\n";
}

//==============================================================================
// 3) メンバー管理（一覧・詳細・並び替え）
//==============================================================================
void Menu::CmdManageMembers()
{
    static constexpr int MAX = 100;

    std::vector<int> order = BuildDefaultOrder(m_guild, MAX);

    while (true)
    {
        std::cout << "\n=== メンバー管理 ===\n";
        PrintListLikeGuild(m_guild, order);

        std::cout << "\n 1. 詳細を見る（No固定）\n";
        std::cout << " 2. 並び替え（表示順のみ）\n";
        std::cout << " 3. 元の順に戻す\n";
        std::cout << " 0. 戻る\n";
        std::cout << "番号 > ";

        int cmd = -1;
        if (!ReadInt(cmd)) continue;

        if (cmd == 0)
        {
            return;
        }
        else if (cmd == 1)
        {
            std::cout << "詳細を見る No. > ";
            int no = -1;
            if (!ReadInt(no)) continue;

            int idx = no - 1;
            if (idx < 0 || idx >= MAX || !m_guild.GetMembers()[idx])
            {
                std::cout << "そのNoは存在しません。\n";
                continue;
            }

            Character* p = m_guild.GetMembers()[idx];

            std::cout << "\n------------------------\n";
            std::cout << "名前 : " << p->GetName() << "\n";
            std::cout << "職業 : " << p->GetJob().GetName() << "\n";
            std::cout << "年齢 : " << p->GetAge() << "\n";
            std::cout << "Lv   : " << p->GetLv() << "\n";
            std::cout << "HP   : " << p->GetHP() << "\n";
            std::cout << "MP   : " << p->GetMP() << "\n";
            std::cout << "ATK  : " << p->GetATK() << "\n";
            std::cout << "DEF  : " << p->GetDEF() << "\n";
            std::cout << "------------------------\n";

            WaitEnter();
        }
        else if (cmd == 2)
        {
            MenuSort::SortType type{};
            if (!SelectSortType_Manage(type)) continue;

            Character** members = m_guild.GetMembers();

            auto key = [&](int idx)
                {
                    Character* p = members[idx];
                    switch (type)
                    {
                    case MenuSort::SortType::LEVEL: return p->GetLv();
                    case MenuSort::SortType::HP:    return p->GetHP();
                    case MenuSort::SortType::MP:    return p->GetMP();
                    case MenuSort::SortType::ATK:   return p->GetATK();
                    case MenuSort::SortType::DEF:   return p->GetDEF();
                    default: return 0;
                    }
                };

            //ソートする値(主キー)が同値だった場合の処理
            //return ka > kbだとランダムになるから団員のナンバーになるように設定

            std::sort(order.begin(), order.end(),
                [&](int a, int b)
                {
                    int ka = key(a);
                    int kb = key(b);

                    if (ka != kb)
                    {
                        return ka > kb;   // 主キー：ATKなど
                    }
                    return a < b;         // 副キー：No（スロット番号）基本A免除でやったとこだ！！！
                });

        }
        else if (cmd == 3)
        {
            order = BuildDefaultOrder(m_guild, MAX);
        }
        else
        {
            std::cout << "0～3 を選んでね。\n";
        }
    }
}

//==============================================================================
// 4) バトル(課題部分)
//==============================================================================

void Menu::CmdBattle()
{


    const int max = Guild::MAX_ADVENTURERS;

    std::cout << "\n=== バトル ===\n";
    std::cout << "形式を選ぶ\n";
    std::cout << " 1. 1v1\n";
    std::cout << " 2. 2v2\n";
    std::cout << "番号 > ";

    int mode = 1;
    if (!ReadInt(mode)) return;
    if (mode != 2) mode = 1;

    std::cout << "\n操作を選ぶ（チームごと）\n";
    std::cout << " 1. 手動\n";
    std::cout << " 2. オート\n";

    int ctrlA = 1, ctrlB = 2;
    std::cout << "Team A > ";
    if (!ReadInt(ctrlA)) return;
    std::cout << "Team B > ";
    if (!ReadInt(ctrlB)) return;

    if (ctrlA != 2) ctrlA = 1;
    if (ctrlB != 2) ctrlB = 1;



    auto isValidNo = [&](int no) -> bool
        {
            int idx = no - 1;
            if (idx < 0 || idx >= max) return false;
            if (!m_guild.GetMembers()[idx]) return false;
            return true;
        };

    auto ReadValidNo = [&](const char* prompt, int& outNo) -> bool
        {
            while (true)
            {
                std::cout << prompt;
                if (!ReadInt(outNo)) return false;

                if (!isValidNo(outNo))
                {
                    std::cout << "Noが不正です。もう一度。\n";
                    continue;
                }
                return true;
            }
        };



    auto getCharByNo = [&](int no) -> Character*
        {
            return m_guild.GetMembers()[no - 1];
        };

    // 入力受付（No固定）
    int a1 = -1, a2 = -1, b1 = -1, b2 = -1;

    if (mode == 1)
    {
        std::cout << "\n--- 1v1 ---\n";

        if (!ReadValidNo("Team A No > ", a1)) return;
        if (!ReadValidNo("Team B No > ", b1)) return;

        if (a1 == b1)
        {
            std::cout << "同じNo同士では戦えません。\n";
            return;
        }

        Character* pA = getCharByNo(a1);
        Character* pB = getCharByNo(b1);

        Fighter fa(pA);
        Fighter fb(pB);

        fa.SetJob(JobFactory::CreateFromName(pA->GetJob().GetName()));
        fb.SetJob(JobFactory::CreateFromName(pB->GetJob().GetName()));

        std::vector<Fighter*> teamA{ &fa };
        std::vector<Fighter*> teamB{ &fb };

        BattleCore core(teamA, teamB);

        ManualController manualA;
        ManualController manualB;
        AutoController aiA;
        AutoController aiB;

        core.SetController(TeamId::A, (ctrlA == 1) ? (Interface_BattleController*)&manualA : (Interface_BattleController*)&aiA);
        core.SetController(TeamId::B, (ctrlB == 1) ? (Interface_BattleController*)&manualB : (Interface_BattleController*)&aiB);

        TeamId winner = core.Run();

        std::cout << "\n=== 結果 ===\n";
        std::cout << "勝者：Team " << ((winner == TeamId::A) ? "A" : "B") << "\n";
        WaitEnter();
        return;
    }

    std::cout << "\n--- 2v2 ---\n";

   
    
    if (!ReadValidNo("Team A No1 > ", a1)) return;
    if (!ReadValidNo("Team A No2 > ", a2)) return;
    if (a1 == a2)
    {
        std::cout << "同じNoが含まれています。\n";
        return;
    }

    if (!ReadValidNo("Team B No1 > ", b1)) return;
    if (!ReadValidNo("Team B No2 > ", b2)) return;
    if (b1 == b2)
    {
        std::cout << "同じNoが含まれています。\n";
        return;

    }



    // チーム跨ぎ重複チェック
    if (a1 == b1 || a1 == b2 || a2 == b1 || a2 == b2)
    {
        std::cout << "同じNoが含まれています。\n";
        return;
    }

    Character* pA1 = getCharByNo(a1);
    Character* pA2 = getCharByNo(a2);
    Character* pB1 = getCharByNo(b1);
    Character* pB2 = getCharByNo(b2);

    Fighter fa1(pA1);
    Fighter fa2(pA2);
    Fighter fb1(pB1);
    Fighter fb2(pB2);

    fa1.SetJob(JobFactory::CreateFromName(pA1->GetJob().GetName()));
    fa2.SetJob(JobFactory::CreateFromName(pA2->GetJob().GetName()));
    fb1.SetJob(JobFactory::CreateFromName(pB1->GetJob().GetName()));
    fb2.SetJob(JobFactory::CreateFromName(pB2->GetJob().GetName()));

    std::vector<Fighter*> teamA{ &fa1, &fa2 };
    std::vector<Fighter*> teamB{ &fb1, &fb2 };

    BattleCore core(teamA, teamB);

    ManualController manualA;
    ManualController manualB;
    AutoController aiA;
    AutoController aiB;

    core.SetController(TeamId::A, (ctrlA == 1) ? (Interface_BattleController*)&manualA : (Interface_BattleController*)&aiA);
    core.SetController(TeamId::B, (ctrlB == 1) ? (Interface_BattleController*)&manualB : (Interface_BattleController*)&aiB);

    TeamId winner = core.Run();

    std::cout << "\n=== 結果 ===\n";
    std::cout << "勝者：Team " << ((winner == TeamId::A) ? "A" : "B") << "\n";
    WaitEnter();
}

