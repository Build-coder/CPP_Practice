//Title: Project 2 for Spring 2020
//Author: Jeremy Dixon
//Date: 2/24/2020
//Description: This is main for project 2

#include <iostream>
#include <fstream>
#include <string>
#include "proj2.h"
#include "Material.h"
#include "Game.h"
#include "Diver.h"
#include "Diver.cpp"
#include "Game.cpp"
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
  srand(time(NULL));
  Game game;
  game.StartGame();

  return 0;
}

