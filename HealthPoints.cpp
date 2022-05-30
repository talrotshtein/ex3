//
// Created by Tal on 5/20/2022.
//
#include "HealthPoints.h"

HealthPoints::HealthPoints(int maxHP){
    if(maxHP <= 0)
    {
        throw InvalidArgument();
    }
    this->m_maxHP = maxHP;
    this->m_HP = maxHP;
}

HealthPoints::HealthPoints(const HealthPoints& HP){
    this->m_HP = HP.m_HP;
    this->m_maxHP = HP.m_maxHP;
}

HealthPoints& HealthPoints::operator=(const HealthPoints& HP) {
    if(this == &HP){
        return *this;
    }
    this->m_HP = HP.m_HP;
    this->m_maxHP = HP.m_maxHP;
    return *this;
}

HealthPoints& HealthPoints::operator+=(int HPToAdd)
{
    if (this->m_HP + HPToAdd > this->m_maxHP)
    {
        this->m_HP = this->m_maxHP;
        return *this;
    }
    else if (this->m_HP + HPToAdd <=0)
    {
        this->m_HP = 0;
        return *this;
    }
    this->m_HP = this->m_HP + HPToAdd;
    return *this;
}

HealthPoints operator+(const HealthPoints& hp, int HPToAdd){
    HealthPoints hpToReturn = hp;
    hpToReturn += HPToAdd;
    return hpToReturn;
}

HealthPoints operator+(int HPToAdd, const HealthPoints& hp) {
    HealthPoints hpToReturn = hp;
    hpToReturn += HPToAdd;
    return hpToReturn;
}

HealthPoints operator-(const HealthPoints& hp, int HPToRemove)
{
    HealthPoints hpToReturn = hp;
    hpToReturn -= HPToRemove;
    return hpToReturn;
    /*
    if (this->m_HP - HPToRemove > this->m_maxHP)
    {
        this->m_HP = this->m_maxHP;
        return *this;
    }
    else if (this->m_HP - HPToRemove <= 0)
    {
        this->m_HP = 0;
        return *this;
    }
    this->m_HP = this->m_HP - HPToRemove;
    return *this;
     */
}

HealthPoints& HealthPoints::operator-=(int HPToRemove)
{
    if (this->m_HP - HPToRemove > this->m_maxHP)
    {
        this->m_HP = this->m_maxHP;
        return *this;
    }
    else if (this->m_HP - HPToRemove <=0)
    {
        this->m_HP = 0;
        return *this;
    }
    this->m_HP = this->m_HP - HPToRemove;
    return *this;
}

bool operator==(const HealthPoints& hp1, const HealthPoints& hp2){
    return hp1.m_HP == hp2.m_HP;
}

bool operator<(const HealthPoints& hp1, const HealthPoints& hp2){
    return hp1.m_HP < hp2.m_HP;
}

bool operator<=(const HealthPoints& hp1, const HealthPoints& hp2){
    return !(hp2 < hp1);
}

bool operator>=(const HealthPoints& hp1, const HealthPoints& hp2){
    return !(hp1 < hp2);
}

bool operator>(const HealthPoints& hp1, const HealthPoints& hp2){
    return hp2<hp1;
}

bool operator!=(const HealthPoints& hp1, const HealthPoints& hp2){
    return !(hp2 == hp1);
}

std::ostream& operator<<(std::ostream& os, const HealthPoints& HP){
    return os<<HP.m_HP<<"("<<HP.m_maxHP<<")";
}
