#include <iostream>
using namespace std;

#ifndef DRIVER01_H
#define DRIVER01_H

class Rectangle {

  private:
    int width, height;
  public:
    void set_values (int,int);
    int area() {return width*height;}
};

void Rectangle::set_values (int x, int y) {
  width = x;
  height = y;
}

#endif