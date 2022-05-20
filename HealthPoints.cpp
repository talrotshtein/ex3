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

HealthPoints& HealthPoints::operator+=(int HPtoAdd)
{
    if (this->m_HP + HPtoAdd > this->m_maxHP)
    {
        this->m_HP = this->m_maxHP;
        return HealthPoints;
    }
    else if (this->m_HP + HPtoAdd <=0)
    {
        this->m_HP = 0;
        return HealthPoints;
    }
    this->m_HP = this->m_HP + HPtoAdd;
    return HealthPoints;
}

HealthPoints& HealthPoints::operator-(HealthPoints& currentHp , int HpToRemove)
{
    if (currentHp->m_HP - HPtoRemove > currentHp->m_maxHP)
    {
        currentHp->m_HP = currentHp->m_maxHP;
        return currentHp;
    }
    else if (currentHp->m_HP - HPtoRemove <=0)
    {
        currentHp->m_HP = 0;
        return currentHp;
    }
    currentHp->m_HP = currentHp->m_HP - HPtoRemove;
    return currentHp;
}

HealthPoints& HealthPoints::operator-=(int HPtoRemove)
{
    if (this->m_HP - HPtoRemove > this->m_maxHP)
    {
        this->m_HP = this->m_maxHP;
        return HealthPoints;
    }
    else if (this->m_HP - HPtoRemove <=0)
    {
        this->m_HP = 0;
        return HealthPoints;
    }
    this->m_HP = this->m_HP - HPtoRemove;
    return HealthPoints;
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
