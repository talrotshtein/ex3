//
// Created by Tal on 5/20/2022.
//

#ifndef EX3_HEALTHPOINTS_H
#define EX3_HEALTHPOINTS_H
#include <ostream>//check about ostream

class HealthPoints {
    int m_maxHP;
    int m_HP;
public:
    HealthPoints(int maxHP = 100);

    HealthPoints(const HealthPoints& HP);

    HealthPoints& operator=(const HealthPoints&);

    HealthPoints &operator-=(int HPtoRemove);

    HealthPoints &operator+=(int HPtoAdd);

    friend bool operator<(const HealthPoints &hp1, const HealthPoints &hp2);

    friend bool operator==(const HealthPoints &hp1, const HealthPoints &hp2);

    friend std::ostream& operator<<(std::ostream&, const HealthPoints&);//check about ostream

    class InvalidArgument {};

};

    HealthPoints operator+(const HealthPoints& hp, int HPtoAdd);

    HealthPoints operator+(int HPtoAdd, const HealthPoints& hp);

    HealthPoints operator-(const HealthPoints& hp, int HpToRemove);

    bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2);

    bool operator>(const HealthPoints &hp1, const HealthPoints &hp2);

    bool operator<=(const HealthPoints &hp1, const HealthPoints &hp2);

    bool operator!=(const HealthPoints &hp1, const HealthPoints &hp2);



#endif //EX3_HEALTHPOINTS_H
