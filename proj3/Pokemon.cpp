//Title: Pokemon.cpp
//Author: Phil Wood/Yangyin Xu/Jeremy Dixon
//Date: 3/9/2020
//Description: This is the Pokemon cpp for the Pokemon class

#include <iostream>
#include <string>
#include <iomanip>
#include "Pokemon.h"

using namespace std;

// construct
Pokemon::Pokemon() {};

Pokemon::Pokemon(int index, string name, string type,
    string strong)
{
    m_index = index;
    m_name = name;
    m_type = type;
    m_strong = strong;
};

Pokemon* Pokemon::GetNext()
{
    return m_next;
}

string Pokemon::GetName()
{
    return m_name;
}

int Pokemon::GetIndex()
{
    return m_index;
}

string Pokemon::GetType()
{
    return m_type;
}

int Pokemon::GetHealth()
{
    return m_health;
}

string Pokemon::GetStrong()
{
    return m_strong;
}

void Pokemon::SetHealth(int hp)
{
    m_health = hp;
}

void Pokemon::SetNext(Pokemon* pocketMonster)
{
    m_next = pocketMonster;
}

ostream &operator<<( ostream &output, Pokemon &P)
{
    output << "Index: " << P.GetIndex()
    << "\tName: " << setw(10) << P.GetName()
    << "\tType: " << setw(10) << P.GetType() 
    << "\tStrength: " << setw(10) << P.GetStrong() 
    << "\tHealth: " << P.GetHealth();

    return output;
}
