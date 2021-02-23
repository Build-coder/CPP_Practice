#include <iostream>
using namespace std;

#ifndef PROJ2_H
#define PROJ2_H

class Rectangle 
{
  private:
    int width, height;
  public:
    void set_values (int,int);
    int area() {return width*height;}
};

void Rectangle::set_values (int x, int y) 
{
  width = x;
  height = y;
}

#endif