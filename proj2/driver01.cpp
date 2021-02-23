#include <iostream>
#include "driver01.h"
using namespace std;



int main () {

  //object created
  Rectangle rect;

  //call set values 
  rect.set_values (5,6);
  cout << "area: " << rect.area() << endl;
  return 0;
}