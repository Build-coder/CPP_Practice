/*Title: class1.cpp
Author: CMSC 202
Date: 2/7/2020
Description: Diver
*/
#include "Diver.h"
#include <iostream> 
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>
#include "Material.h"
using namespace std;

//default constructor
Diver::Diver()
{
  m_myName = "Scuba Man";
  m_numMaterials = 0;
}

//actual constructor
Diver::Diver(string name)
{
  m_myName = name;
  m_numMaterials = 0;
}

string Diver::GetName()
{
  return m_myName;
}

void Diver::SetName(string name)
{
  m_myName = name;
}

void Diver::AddMaterial(Material item)
{
  m_myMaterials[m_numMaterials] = item;
  m_numMaterials++;
} 

void Diver::DisplayMaterials()
{
  int count = 1;

  for(int i=0; i<PROJ2_SIZE; i++)
  {
    cout << count << ".) " << m_myMaterials[i].m_name 
    << " " << m_myMaterials[i].m_quantity << endl;

    count++;
  }
}

int Diver::CheckMaterial(Material item)
{
  int i = 0;

  for (int i = 0; i < PROJ2_SIZE; i++)
  {
    if (item.m_name == m_myMaterials[i].m_name)
    {
      return i;
    }
  }

  return -1;
}

void Diver::IncrementQuantity(Material item)
{
  int i = CheckMaterial(item);
  m_myMaterials[i].m_quantity++;

}

bool Diver::DecrementQuantity(Material item)
{  
  int i = CheckMaterial(item);
  m_myMaterials[i].m_quantity--;

  return true;
}

bool Diver::CheckQuantity(Material mat_1, Material mat_2)
{
  if (mat_1.m_quantity > 0 && mat_2.m_quantity > 0)
  {
      return true;
  }
  else
  {
      cout << endl << "You don't have enough " << 
      mat_1.m_name << " or " << mat_2.m_name 
      << " to attempt that merge" << endl;

      return false;
  } 
}

Material Diver::GetMaterial(int i)
{ 
  return m_myMaterials[i];
}

int Diver::CalcDepth()
{
  int sum = 0;

  for (int i = 0; i < PROJ2_SIZE; i++)
  {
    if (m_myMaterials[i].m_quantity == 1)
    {
      sum += m_myMaterials[i].m_depth;
    }
  }
  
  return sum;
}


