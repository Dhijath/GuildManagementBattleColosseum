/*==============================================================================

   E‹ÆƒNƒ‰ƒX [job.h]
                                                         Author : Youhei Sato
                                                         Date   : 2025/10/28
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef JOB_H
#define JOB_H

#include <string>


class Job
{
private:
    const std::string m_names[4]{
        "•½–¯",
        "ím",
        "‘m—µ",
        "–‚–@g‚¢"
    };

    int m_id{ 0 };

public:
    Job() = default;
    Job(int id) : m_id(id) {}
    Job(const std::string& name);

    const std::string& GetName() const { return m_names[m_id]; }
};

#endif // 

