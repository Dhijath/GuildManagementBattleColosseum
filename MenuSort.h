/*==============================================================================

   メニュー整列用クラス [MenuSort.ｈ]
                                                         Author : 51106
                                                         Date   : 2025/12/02
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef MENUSORT_H
#define MENUSORT_H

#include "Character.h"

class MenuSort {
public:
    enum class SortType {
        LEVEL,
        HP,
        MP,
        ATK,
        DEF
    };

    static void Sort(Character* arr[], int size, SortType type);
};

#endif

