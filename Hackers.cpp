// CS1300 Fall 2021
// Author: Zack Leaf and Nathanael Lee
// Recitation: 212 - Nikhith Sannidhi (Zack) 213 - Jerome Gammie (Nathanael)
// Project 3
#include "Hackers.h"
#include <cmath>
#include <unistd.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include "Map.h"
#include "Inventory.h"
#include "bestBuy.h"

using namespace std;

Hackers::Hackers() //very simple class, nothing really to it. this will also be an object array though 
{
    name = "";
    level = 0;
}

Hackers::Hackers(string n, int l)
{
    name = n;
    level = l;
}
void Hackers::setLevel(int i) {
    level = i;
}
void Hackers::setName(string g) {
    name = g;
}
int Hackers::getLevel() {
    return level;
}
string Hackers::getName() {
    return name;
}