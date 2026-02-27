/*==============================================================================

  ギルド管理 [Guild.cpp]
														 Author : 51106
														 Date   : 2025/11/11
--------------------------------------------------------------------------------

==============================================================================*/


#include "Guild.h"
#include <iostream>
#include "MenuSort.h"



Guild::~Guild()//デストラクタ
{

	for (Character* Pl : m_Adventurers){delete Pl;}

}

//＝＝参加
void Guild::Joining( Character* Adventurers)
{

	//リストの中から空いている場所を探す
	for (int i = 0;i < MAX_ADVENTURERS;i++)
	{
		if (!m_Adventurers[i])
		{
			m_Adventurers[i] = Adventurers;
			break;//ここをリターンにしてリターン失敗の処理が必要となる(登録できなかった)
		}

		
	}


}



Guild::Guild(const std::string& filename)
{


}



void Guild::Whithdrawal(int index)
{

	delete m_Adventurers[index];
	m_Adventurers[index] = nullptr;

}

void Guild::Display_List()
{

	for (int guildnum = 0;guildnum < MAX_ADVENTURERS;guildnum++)
	{
		if (!m_Adventurers[guildnum])continue;
		std::cout << "No." << guildnum+1  << ":" << m_Adventurers[guildnum]->GetName();
        std::cout << m_Adventurers[guildnum]->GetJob().GetName();
		std::cout << "《Lv." << m_Adventurers[guildnum]->GetLv() << "》";
		std::cout << m_Adventurers[guildnum]->GetJob().GetName() << std::endl;

	}

}

void Guild::DisplayDetailed(int index)
{
    // 範囲外チェック
    if (index < 0 || index >= MAX_ADVENTURERS)
    {
        std::cout << "指定された番号は範囲外です。\n";
        return;
    }

    // 該当スロットにキャラがいない場合
    if (!m_Adventurers[index])
    {
        std::cout << "その番号にはキャラクターが登録されていません。\n";
        return;
    }

    // ここまで来たらキャラが存在する！
    Character* Pl = m_Adventurers[index];

    std::cout << "------------------------\n";
    std::cout << Pl->GetName() << " のステータス\n";
    std::cout << "名前 : " << Pl->GetName() << '\n';
    std::cout << "職業 : " << Pl->GetJob().GetName() << '\n';
    std::cout << "年齢 : " << Pl->GetAge() << "歳\n";
    std::cout << "LV   : " << Pl->GetLv() << '\n';
    std::cout << "HP   : " << Pl->GetHP() << '\n';
    std::cout << "MP   : " << Pl->GetMP() << '\n';
    std::cout << "ATK  : " << Pl->GetATK() << '\n';
    std::cout << "DEF  : " << Pl->GetDEF() << '\n';
    std::cout << "------------------------\n";
}



void Guild::SortMembers(MenuSort::SortType type)
{
    MenuSort::Sort(m_Adventurers, MAX_ADVENTURERS, type);
}
