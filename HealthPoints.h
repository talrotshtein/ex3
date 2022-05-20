//
// Created by Tal on 5/20/2022.
//

#ifndef EX3_HEALTHPOINTS_H
#define EX3_HEALTHPOINTS_H
#include <ostream>

class HealthPoints {
    int m_maxHP;
    int m_HP;
public:
    HealthPoints(int maxHP = 100);

    HealthPoints &operator-=(int HPtoRemove);

    HealthPoints &operator+=(int HPtoAdd);

    HealthPoints operator+(int HPtoAdd);

    HealthPoints operator-(int HPtoRemove);

    friend bool operator<(const HealthPoints &hp1, const HealthPoints &hp2);

    friend bool operator==(const HealthPoints &hp1, const HealthPoints &hp2);

    friend std::ostream& operator<<(std::ostream&, const HealthPoints&);
};

    bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2);

    bool operator>(const HealthPoints &hp1, const HealthPoints &hp2);

    bool operator<=(const HealthPoints &hp1, const HealthPoints &hp2);

    bool operator!=(const HealthPoints &hp1, const HealthPoints &hp2);



#endif //EX3_HEALTHPOINTS_H
