//Title: Game.cpp
//Author: Phil Wood/Yangyin Xu/Jeremy Dixon
//Date: 3/9/2020
//Description: This is Game cpp for the Game class

#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"

using namespace std;

// const
int TOTAL_POKEMON = 150;
int USER_WON = 1;
int ENEMY_WON = 2;
int CONTINUE, ERROR = 0;

// construct
Game::Game(string file) 
{
    m_filename = file;
    m_list = new PokemonList;
    m_userPocket =  new PokemonList;
    m_enemyPocket = new PokemonList;
};

// destruct
Game::~Game() 
{
    delete m_list;
    m_list = nullptr;
    delete m_enemyPocket;
    m_enemyPocket = nullptr;
    delete m_userPocket;
    m_userPocket = nullptr;
};

void Game::LoadFile()
{
    string name, type, strength;
    int index;

    ifstream file;
    
    file.open(m_filename);

    for(int i=0; i<TOTAL_POKEMON; i++)
    {
        file >> index;
        file.ignore();
        getline(file, name, ',');
        getline(file, type, ',');
        getline(file, strength, '\n');

        Pokemon* node = new Pokemon(index, name, type, strength);
        node->SetHealth(MAX_HEALTH);
        m_list->InsertEnd(node);
    }

    file.close();
}

void Game::ChooseTeam()
{
    int index, count, random = 0;
    int left = NUM_TEAM; // num of entires left to make
    bool originalEntry = false; // check for original entry

    while (count < NUM_TEAM)
    {
        cout << endl;
        m_list->Display(); 
        cout << "User Pocket: " << endl;
        m_userPocket->Display();
        cout << endl;
        cout << "Enemy Pocket: " << endl;
        m_enemyPocket->Display();
        cout << endl;
        cout << "Pick a Pokemon by entering the index: ("
        << left << " left): ";
        cin >> index;
        random = rand() % TOTAL_POKEMON + 1;

        // check if entry is original
        originalEntry = m_list->Exist(index);
        
        // transfer selected Pokemon to their respective lists
        if (index > 0 && index < (TOTAL_POKEMON+1)
        && originalEntry)
        {
            m_list->Transfer(index, m_userPocket);
            m_list->Transfer(random, m_enemyPocket);
            count++;
            left--;
        }
    }

    cout << "User Pocket: " << endl;
    m_userPocket->Display();
    cout << "Enemy Pocket: " << endl;
    m_enemyPocket->Display();
}

int Game::Menu()
{
    int choice = 0;

    cout << 
    "----------------------------" 
    << endl
    << "Menu:" << endl
    << "1. Attack" << endl
    << "2. Swap" << endl
    << "3. Forfeit" << endl;

    cin >> choice;
    cout << endl;
    
    return choice;
}

int Game::Battle()
{
    int result = 0;

    /// user attacks enemy
    result = m_userPocket->Attack(m_enemyPocket);

    // if enemy pokemon faints
    if (m_enemyPocket->GetHead()->GetHealth() <= 0)
    {
        cout << endl << "CPU's pokemon fainted. CPU has new starting pokeon" << endl;
        // remove enemy pokemon that fainted
        m_enemyPocket->Remove(m_enemyPocket->GetHead()->GetIndex());

        // if all pokemon in a pocket faint
        if (m_enemyPocket->GetHead() == nullptr
        || m_userPocket->GetHead() == nullptr)
        {
            // end battle, return result of battle
            return result;
        }
    }
    // if user pokemon faints
    if (m_userPocket->GetHead()->GetHealth() <= 0)
    {
        // remove pokemon that fainted
        m_userPocket->Remove(m_userPocket->GetHead()->GetIndex());

        // if all pokemon in a pocket faint
        if (m_enemyPocket->GetHead() == nullptr
        || m_userPocket->GetHead() == nullptr)
        {   
            // end battle, return result of battle
            return result;
        }
        cout << endl;
        m_userPocket->Display();
        cout << endl << "Your Pokemon fainted, select a new starter Pokemon" << endl
        << endl << "(If the Pokemon you select is not in the list, your 2nd Pokemon will"
        << " become your starter)" << endl << endl;
        // user selects new starter pokemon to replact fainted pokemon
        m_userPocket->SwapPokemon();
    }

    // if no conditions above are met, continue the battle
    return CONTINUE;
}

int Game::Start()
{
    LoadFile();
    ChooseTeam();

    bool go = true; // bool to exit while loop
    int count = 1; // count the rounds
    int result = 0; // save the result of the battle

    while (go)
    {
        cout << endl << "Round " << count << ":" 
        << endl << "CPU'S Pokemon: " 
        << m_enemyPocket->GetHead()->GetName() 
        << " (" << m_enemyPocket->GetHead()->GetType() 
        << ":" << m_enemyPocket->GetHead()->GetHealth() 
        << " health)" << endl << "Your Pokemon: "
        << m_userPocket->GetHead()->GetName() << " (" 
        << m_userPocket->GetHead()->GetType() << ":"
        << m_userPocket->GetHead()->GetHealth() << " health)" 
        << endl; 

        switch (Menu())
        {
        case 1:
            result = Battle();
            if (result == USER_WON)
            {
                go = false;
                return USER_WON;
            }
            else if (result == ENEMY_WON)
            {
                go = false;
                return ENEMY_WON;
            }
            else
            {
                count++;
                break;
            }

        case 2:
            m_userPocket->Display();
            m_userPocket->SwapPokemon();
            break;
    
        default:
            go = false;
            break;
        }
    }

    return ERROR;
}



