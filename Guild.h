/*==============================================================================

  ギルド管理ヘッダー [Guild.h]
														 Author : 51106
														 Date   : 2025/11/11
--------------------------------------------------------------------------------

==============================================================================*/

//・キャラクターの追加
//・キャラクターの削除
//・管理キャラクターのリスト表示
//・キャラクターの詳細表示

#ifndef GUILD_H
#define GUILD_H

#include "Character.h"
#include "MenuSort.h"


class Guild
{
	//ここパブリックとプライベート逆じゃないと評価順でエラー発生する
public:
	static constexpr int MAX_ADVENTURERS = 100;
	Guild() = default;
	~Guild();
	Guild(const std::string& filename);

	void Joining( Character* Adventurers) ;//ギルドキャラクター作成

	void Whithdrawal(int index);//ギルドから削除

	void Display_List();//ギルドリスト作成

	void DisplayDetailed(int index);//詳細表示

	Character** GetMembers() { return m_Adventurers; }

	void SortMembers(MenuSort::SortType type);

private:

	Character* m_Adventurers[MAX_ADVENTURERS]{};


};












#endif
