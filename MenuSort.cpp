/*==============================================================================

   メニュー整列用クラス [MenuSort.cpp]
                                                         Author : 51106
                                                         Date   : 2025/12/02
--------------------------------------------------------------------------------

==============================================================================*/
#include "MenuSort.h"
#include <algorithm>
#include <vector>

void MenuSort::Sort(Character* arr[], int size, SortType type) {
    std::vector<Character*> temp;
    for (int i = 0; i < size; ++i) {
        if (arr[i]) temp.push_back(arr[i]);
    }

    switch (type) {
    case SortType::LEVEL:
        std::sort(temp.begin(), temp.end(), [](Character* a, Character* b) {
            return a->GetLv() > b->GetLv();
            });
        break;
    case SortType::HP:
        std::sort(temp.begin(), temp.end(), [](Character* a, Character* b) {
            return a->GetHP() > b->GetHP();
            });
        break;
    case SortType::MP:
        std::sort(temp.begin(), temp.end(), [](Character* a, Character* b) {
            return a->GetMP() > b->GetMP();
            });
        break;
    case SortType::ATK:
        std::sort(temp.begin(), temp.end(), [](Character* a, Character* b) {
            return a->GetATK() > b->GetATK();
            });
        break;
    case SortType::DEF:
        std::sort(temp.begin(), temp.end(), [](Character* a, Character* b) {
            return a->GetDEF() > b->GetDEF();
            });
        break;
    }

    for (int i = 0; i < size; ++i) arr[i] = nullptr;
    for (size_t i = 0; i < temp.size(); ++i) arr[i] = temp[i];
}
