/*==============================================================================

   メニュー管理 [Menu.h]
                                                         Author : 51106
                                                         Date   : 2025/12/16
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef MENU_H
#define MENU_H

#include "Guild.h"

class Menu
{
private:
    Guild& m_guild;

public:
    Menu(Guild& guild);

    void Show();
    void Run();

private:
    void CmdJoin();            // 1. 加入
    void CmdLeave();           // 2. 脱退
    void CmdManageMembers();   // 3. メンバー管理（一覧・詳細・並び替え）
    void CmdBattle();          // 4. バトル（後で）
};

#endif // MENU_H
