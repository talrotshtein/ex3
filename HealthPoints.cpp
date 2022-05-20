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
