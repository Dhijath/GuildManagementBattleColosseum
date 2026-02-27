#include <string>


class JK
{
private:
    int m_age;
    std::string m_name;

public:
    // デフォルトコンストラクタ（JK(16, "不明") を呼ぶ）
    JK()
        : JK(16, "不明")
    {
    }

    // 引数ありコンストラクタ
    JK(int age, std::string name)
        : m_age(age), m_name(name)
    {
    }
};

