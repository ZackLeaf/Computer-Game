// CS1300 Fall 2021
// Author: Zack Leaf and Nathanael Lee
// Recitation: 212 - Nikhith Sannidhi (Zack) 213 - Jerome Gammie (Nathanael)
// Project 3
#ifndef Hackers_H
#define Hackers_H

#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include "Map.h"
#include "Inventory.h"

using namespace std;

class Hackers
{

private:

  string name;
  int level;

public:

  Hackers();
  Hackers(string name, int level);
  void setLevel(int);
  void setName(string);
  int getLevel();
  string getName();
};
#endif
