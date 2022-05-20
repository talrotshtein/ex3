//
// Created by Tal on 5/20/2022.
//

#ifndef EX3_HEALTHPOINTS_H
#define EX3_HEALTHPOINTS_H

class HealthPoints {
    int m_maxHP;
    int m_HP;
public:
    HealthPoints(int maxHP = 100);

    HealthPoints &operator-=(int HPtoRemove);

    HealthPoints &operator+=(int HPtoAdd);

    HealthPoints &operator+(int HPtoAdd);

    HealthPoints &operator-(int HPtoRemove);

    bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2) const;

    bool operator>(const HealthPoints& hp1 , const HealthPoints& hp2) const;

    bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2) const;

    bool operator<(const HealthPoints& hp1 , const HealthPoints& hp2) const;

    bool operator==(const HealthPoints& hp1 , const HealthPoints& hp2) const;

    bool operator!=(const HealthPoints& hp1 , const HealthPoints& hp2) const;

    friend ostream& operator<<(ostream&, const HealthPoints&);
}

#endif //EX3_HEALTHPOINTS_H
