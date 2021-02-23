/*Title: Game.cpp
Author: Phil Wood
Date: 2/7/2020
Description: Game file
*/
#include <iostream> 
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>
#include "Material.h"
#include "Game.h"
using namespace std;

Game::Game()
{ 
    GameTitle();
    string DiverName;
    cout << "What is the name of your diver?" << endl;
    cin >> DiverName;
    m_myDiver.SetName(DiverName);
    LoadMaterials();
};

void Game::LoadMaterials()
{
    string name, type, material1, material2, space;
    int quantity = 0, depth, count = 0;

    ifstream file;
    
    file.open(PROJ2_DATA);

    for(int i=0; i<PROJ2_SIZE; i++)
    {
        space = "";

        getline(file, name, ',');
        getline(file, type, ',');
        getline(file, material1, ',');
        getline(file, material2, ',');
        file >> depth;
        getline(file, space); 

        m_materials[i] = Material(name, type, material1, material2, quantity, depth);
        m_myDiver.AddMaterial(m_materials[i]);

        count++;
    }
    file.close();

    cout << count << " materials loaded" << endl << endl;
}

void Game::StartGame()
{
    int depth = 0;

    while(depth<MAX_DEPTH)
    {
        switch(MainMenu())
        {
            case 1: cout << "Display Diver's Materials" << endl << endl;
                m_myDiver.DisplayMaterials();
                continue;
            case 2: cout << "Search for Raw Materials" << endl << endl;
                SearchMaterials();
                continue;
            case 3: cout << "Attempt to Merge Materials" << endl << endl;
                CombineMaterials();
                depth = m_myDiver.CalcDepth();
                continue;
            case 4: cout << "See Score" << endl << endl;
                CalcScore();
                continue;
            case 5: cout << "Quit" << endl << endl;
                depth = MAX_DEPTH;
        }
    }

    cout << "Congradulations, you won!" << endl << endl;
}

void Game::DisplayMaterials()
{
  for(int i=0; i<PROJ2_SIZE; i++)
  {
    cout << m_materials[i].m_name << ','
    << m_materials[i].m_type << ','
    << m_materials[i].m_material1 << ','
    << m_materials[i].m_material2 << ','
    << m_materials[i].m_quantity << ','
    << m_materials[i].m_depth << endl;
  }
}

int Game::MainMenu()
{
  int response;
  
  while(true)
  {
    cout << endl << "What would you like to do?" << endl
    << "1. Display your Diver's materials" << endl
    << "2. Search for Raw Materials" << endl
    << "3. Attempt to Merge Materials" << endl
    << "4. See Score" << endl
    << "5. Quit" << endl;

    cin >> response;

    if(response>0 && response<6)
      break;
    else
      continue;
  }

  return response;
}

// creates random number then increments 
void Game::SearchMaterials()
{
    int i = 0;
    i = rand() % NUM_OF_RAW;
    cout << m_materials[i].m_name << " found!" << endl << endl;
    m_myDiver.IncrementQuantity(m_materials[i]);
}

void Game::CombineMaterials()
{
    // used an array, should have used an int, whoops
    int choice[INDEXES] = {0};
    int foundIndex = 0;

    while(true)
    {
        RequestMaterial(*choice);
        
        if (m_myDiver.CheckQuantity(m_myDiver.GetMaterial(choice[0]), 
            m_myDiver.GetMaterial(choice[1])))
        {
            foundIndex = SearchRecipes(m_materials[choice[0]].m_name, 
                m_materials[choice[1]].m_name);

            if (foundIndex != 0)
            {
                if (m_materials[foundIndex].m_type == "unique" &&
                    m_myDiver.GetMaterial(foundIndex).m_quantity
                    == 0)
                {    
                    cout << endl << "You made " << 
                    m_materials[foundIndex].m_name << "!" << endl;
                    m_myDiver.IncrementQuantity(m_materials[foundIndex]);
                    m_myDiver.DecrementQuantity(m_materials[choice[0]]);
                    m_myDiver.DecrementQuantity(m_materials[choice[1]]);
                }
                else if (m_materials[foundIndex].m_type == "unique" &&
                    m_myDiver.GetMaterial(foundIndex).m_quantity != 0)
                { 
                    cout << endl <<
                    "Already have unique item " <<
                    m_materials[foundIndex].m_name << endl;

                    break;
                }
                else
                {
                    cout << endl << "You made " << 
                    m_materials[foundIndex].m_name << "!" << endl;
                    m_myDiver.IncrementQuantity(m_materials[foundIndex]);
                    m_myDiver.DecrementQuantity(m_materials[choice[0]]);
                    m_myDiver.DecrementQuantity(m_materials[choice[1]]);   
                }  
            }
            else
            {
                cout << endl << "No matches!" << endl;
                break;
            }
        }
        else
        {
            break;     
        }
    }
}

void Game::RequestMaterial(int &choice)
{
    int index_1, index_2 = 0;
    int *value = &choice;

    while(true)
    {   cout << "Which materials would you like to merge " <<
        "(Enter '-1' if you would like to see the menu): " 
        << endl;
        cin >> index_1;

        if (index_1 == -1)
    
            m_myDiver.DisplayMaterials();
        
        cout << "Which materials would you like to merge" << 
        "(Enter '-1' if you would like to see the menu): "
        << endl;
        cin >> index_2;

        if (index_2 == -1)
    
            m_myDiver.DisplayMaterials();

        if (index_1>0 && index_1<51 && index_2>0 && index_2<51)
        {   
            value[0] = index_1-1;
            value[1] = index_2-1;
            break;
        }
        else
        {
            cout << endl << "You must select a number 1-50 " 
            << "try again" << endl << endl;
        } 
    }
}

int Game::SearchRecipes(string mat_1, string mat_2)
{
    for (int i = 0; i < PROJ2_SIZE; i++)
    {
        if (m_materials[i].m_material1 == mat_1
            && m_materials[i].m_material2 == mat_2
            || m_materials[i].m_material1 == mat_2
            && m_materials[i].m_material2 == mat_1)
        {
            return i;
        }
    }
    return 0;
}

void Game::CalcScore()
{   
    cout << "***The Diver***" << endl;
    cout << "The Great Diver " << m_myDiver.GetName() << endl;
    cout << "Max Depth: " << MAX_DEPTH << endl;
    cout << "Current Depth: " << m_myDiver.CalcDepth() 
    << " meters" << endl;
}