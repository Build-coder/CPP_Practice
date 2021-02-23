//Title: PokemonList.cpp
//Author: Phil Wood/Yangyin Xu/Jeremy Dixon
//Date: 3/9/2020
//Description: This is the PokemonList cpp for the PokemonList class

#include <iostream>
#include <string>
#include "PokemonList.h"

using namespace std;

// const
int ENEMY_FAINTED = 1;
int USER_FAINTED = 2;
int DRAW = 0;

// constuct
PokemonList::PokemonList() 
{
    m_head = nullptr;
    m_size = 0;
};

// destruct
PokemonList::~PokemonList() 
{
  Pokemon *curr = m_head;
  while(m_head != nullptr)
  {
    // move tracker to next node
    curr = m_head->GetNext();
    // delete prev node
    delete m_head;
    // set head to curr node
    m_head = curr;
  }

  m_head = nullptr;
  m_size = 0;
};

void PokemonList::InsertEnd(Pokemon* pokemon)
{
    // instructions to place first node in list
    if (m_head == nullptr)
    { 
        m_head = pokemon; 
        m_size = 1; 
        m_head->SetNext(nullptr); 
    } 
    else
    {   // always keep m_head pointing at first node in list
        Pokemon* curr = m_head; 

        // instructions to place all other nodes in list
        while (curr->GetNext() != nullptr)
        {
            curr = curr->GetNext(); 
        }

        m_size++;
        curr->SetNext(pokemon); 
        pokemon->SetNext(nullptr); 
    }   
}

void PokemonList::Display()
{
  if(m_size==0) //Checks to see if the linked list is empty
  { 
    cout << "The linked list is empty" << endl; //Output if it is empty
  }
  else
  {
    Pokemon *curr = m_head; //Creates a new pointer to iterate over list

    while(curr != nullptr)
    {
      cout << *curr << endl;
      curr = curr->GetNext(); //Moves to m_next node
    }
    cout << "END" << endl; //Indicates the end of the linked list
  }
}

void PokemonList::Transfer(int i, PokemonList* listPtr)
{
    Pokemon* curr = m_head; // create temp pointer

        while ((curr->GetIndex() != i) && (curr != nullptr))
        {
            curr = curr->GetNext();
        }

        // create pokemon node
        Pokemon* node = new Pokemon(curr->GetIndex(), 
        curr->GetName(),curr->GetType(), 
        curr->GetStrong()); 

        // set health of 9 for each pokemon
        node->SetHealth(MAX_HEALTH);

        // insert each pokemon in list
        listPtr->InsertEnd(node);
        Remove(i);
}

void PokemonList::Remove(int i)
{
    Pokemon* prev = m_head; // create pointer to prev node
    Pokemon* curr = m_head; // create pointer to curr node

    if (curr->GetIndex() == i)
    {
        // reset m_head to be the next in the list
        // so have m_head point to next node in list
        m_head = curr->GetNext();
        
    }
    
    else
    {
        while ((curr->GetIndex() != i) && (curr != nullptr))
        {
            prev = curr;
            curr = curr->GetNext();
        }
        prev->SetNext(curr->GetNext());
    }

    delete curr;
}

int PokemonList::GetSize()
{
    return m_size;
}

Pokemon* PokemonList::GetHead()
{
    return m_head;
}

int PokemonList::Attack(PokemonList* enemyPocket)
{
    string userType = m_head->GetType();
    string enemyType = enemyPocket->GetHead()->GetType();
    string userStrong = m_head->GetStrong();
    string enemyStrong = enemyPocket->GetHead()->GetStrong();

    // if enemy pokemon vulnerable
    if (userStrong == enemyType)
    {
        // enemy pokemon health set to (current health - 5)
        enemyPocket->GetHead()->SetHealth(enemyPocket->GetHead()->GetHealth()
        -STRONG_DAMAGE);
        cout << endl << "Critical hit! CPU's pokemon took 5 damage!" << endl;
    }
    // if enemy pokemon fainted
    if (enemyPocket->GetHead()->GetHealth() <= 0)
    {
        return ENEMY_FAINTED;
    }
    // if enemy pokemon not vulnerable
    if (userStrong != enemyType)
    {
        // enemy pokemon health set to (current health - 2)
        enemyPocket->GetHead()->SetHealth(enemyPocket->GetHead()
        ->GetHealth()-DAMAGE2ENEMY);
        cout << "CPU's pokemon took 2 damage" << endl;
    }  
    // if enemy pokemon fainted
    if (enemyPocket->GetHead()->GetHealth() <= 0)
    {
        return ENEMY_FAINTED;
    }
    // if user pokemon is vulnerable
    if (enemyStrong == userType)
    {
        // user pokemon health set to (current health - 5)
        m_head->SetHealth(m_head->GetHealth()-STRONG_DAMAGE);
        cout << endl << "Critical hit! User's pokemon took 5 damage!" << endl;
    }
    // if user pokemon fainted
    if (m_head->GetHealth() <= 0)
    {
        return USER_FAINTED;
    }
    // if user pokemon not vulnerable
    if (enemyStrong != userType)
    {
        // user health set to (current health - 3)
        m_head->SetHealth(m_head->GetHealth()-DAMAGE2USER);
        cout << "User's pokemon took 3 damage" << endl;
    }
    // if user pokemon fainted
    if (m_head->GetHealth() <= 0)
    {
        return USER_FAINTED;
    }
    // if neither pokemon faint
    return DRAW;
}

void PokemonList::SwapPokemon()
{
    // allows user to move a Pokemon from any position into the first position
    // user selects a Pokemon and that Pokemon is moved into the first position

    int i = 0;
    bool found = false;
    Pokemon* curr = m_head; 
    Pokemon* prev = m_head;
    Pokemon* nextNode = m_head;
    
    cout << "Enter the index you'd like to swap: ";
    cin >> i;

    // if index is already the index of starting pokemon
    if (curr->GetIndex() == i)
    {
        cout << endl << curr->GetName() << " is already starting. Try again." << endl;
    }

    else
    {
        while (curr != nullptr)
        {
            // search for index
            if (curr->GetIndex() != i)
            {
                prev = curr;
                curr = curr->GetNext();
            }
            // index is found, swap occurs
            else
            {
                found = true;
                // set prev next to head
                prev->SetNext(m_head);
                // save next node
                nextNode = curr->GetNext();
                // set curr next to head next
                curr->SetNext(m_head->GetNext());
                // set head next to last node
                m_head->SetNext(nextNode);
                // set curr to head
                m_head = curr;
                break;
            }
        }
        // if index isn't found
        if (found == false)
        {
            cout << endl << "ERROR: Selected index matches" 
            << " no indices in pocket. Try again." << endl;
        }
    }
}


bool PokemonList::Exist(int i)
{
    Pokemon* curr = m_head;

    while (curr->GetIndex() != i)
    {
        curr = curr->GetNext();

        // if index not found
        if (curr == nullptr)
        {
            return false;
        } 
    }
    
    // index found
    return true;
}

