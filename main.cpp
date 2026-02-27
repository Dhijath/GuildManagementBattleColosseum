#include <iostream>
#include "character.h"

int main()
{

    Character* pl2 = new Character("イングリット", "戦士", 25, 1, 120, 20, 40, 100);



    const int MAX_CHARACTER = 4;

    //馴染みがあるのでプレイヤーはplに変更
    Character* pl = new Character[MAX_CHARACTER]
    {
        Character("リュウ", "戦士", 25, 1, 120, 20, 40, 100),
        Character("ジュリ", "平民", 18, 1, 80,  5, 10,  50),
        Character("ケン",  "戦士", 23, 1, 110, 15, 45, 70),
        Character("サガット", "僧侶", 19, 1, 70, 40, 8,  80)
    };


    //　plからキャラを選出

    Character& ryu = pl[0];//リュウケンを番号ではなく名前で指定してやりやすくしておこう

    Character& ken = pl[2];

    //　ステータス紹介

    std::cout << "------------------------\n";
    std::cout << "リュウのステータス\n";
    std::cout << "名前 : " << ryu.GetName() << '\n';
    std::cout << "職業 : " << ryu.GetJob().GetName() << '\n';
    std::cout << "年齢 : " << ryu.GetAge() << "歳\n";
    std::cout << "LV   : " << ryu.GetLv() << '\n';
    std::cout << "HP   : " << ryu.GetHP() << '\n';
    std::cout << "MP   : " << ryu.GetMP() << '\n';
    std::cout << "ATK  : " << ryu.GetATK() << '\n';
    std::cout << "DEF  : " << ryu.GetDEF() << '\n';

    std::cout << "------------------------\n";
    std::cout << "ケンのステータス\n";
    std::cout << "名前 : " << ken.GetName() << '\n';
    std::cout << "職業 : " << ken.GetJob().GetName() << '\n';
    std::cout << "年齢 : " << ken.GetAge() << "歳\n";
    std::cout << "LV   : " << ken.GetLv() << '\n';
    std::cout << "HP   : " << ken.GetHP() << '\n';
    std::cout << "MP   : " << ken.GetMP() << '\n';
    std::cout << "ATK  : " << ken.GetATK() << '\n';
    std::cout << "DEF  : " << ken.GetDEF() << '\n';
    std::cout << "------------------------\n";


    // ダメージ計算（リュウがケンに攻撃される）



    int rawDamage = ken.GetATK() - (ryu.GetDEF() * 0.3f); //与ダメ計算

    if (rawDamage < 0) rawDamage = 0;//防御が攻撃を超過時に0ダメ(与ダメが0未満になった場合)

    // HPを下回らないように
    if (rawDamage > ryu.GetHP())
        rawDamage = ryu.GetHP();

    ryu.SetHP(ryu.GetHP() - rawDamage);

    //＝＝＝メモ＝＝＝
    // 
    //今回はダメをHPに合わせたけど、この後にダメージが0未満になった時のif文を書く方法もありそうだなぁ
    //
    //



    std::cout << "\nラウンド1！！！\n";
    std::cout << "ケンの攻撃！ リュウに " << rawDamage << " のダメージ！\n";
    std::cout << "リュウの残りHP: " << ryu.GetHP() << "\n";


    delete pl2;
    delete[] pl;
    return 0;
}
