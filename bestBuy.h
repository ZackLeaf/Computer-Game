// CS1300 Fall 2021
// Author: Zack Leaf and Nathanael Lee
// Recitation: 212 - Nikhith Sannidhi (Zack) 213 - Jerome Gammie (Nathanael)
// Project 3 

#ifndef BESTBUY_H
#define BESTBUY_H

#include <iostream>
#include <string>
#include <iomanip>
#include "Inventory.h"
using namespace std;

class bestBuy //this class is used for the items availible in the bestbuy stores
{
private:
    int CPUCost;
    int GPUCost;
    int powerCost;
    int computerCaseCost;
    int internetCardCost;
    int keyboardAndMouseCost;
    int preComputerCost;
    int antivirusCost;
    int VPNCost;
    int IPCost2;
    int IPCost3;
    int IPCost4;
    int IPCost5;

public:

    bestBuy(); //default constructor
    bestBuy(int cpu, int gpu, int p, int cc, int ic, int km, int pc, int as, int vpn, int ip2, int ip3, int ip4, int ip5); //parametarized constructor

    void setCPUCost(int cpu);
    int getCPUCost();
    void setGPUCost(int gpu);
    int getGPUCost();
    void setPowerSupplyUnitCost(int p);
    int getPowerSupplyUnitCost();
    void setComputerCaseCost(int cc);
    int getComputerCaseCost();
    void setInternetCardCost(int ic);
    int getInternetCardCost();
    void setKeyboardAndMouseCost(int km);
    int getKeyboardAndMouseCost();
    void setPremadeComputerCost(int pc);
    int getPremadeComputerCost();
    void setAntivirusSoftwareCost(int as);
    int getAntivirusSoftwareCost();
    void setVPNCost(int vpn);
    int getVPNCost();
    void setInternetProvider2Cost(int ip2);
    int getInternetProvider2Cost();
    void setInternetProvider3Cost(int ip3);
    int getInternetProvider3Cost();
    void setInternetProvider4Cost(int ip4);
    int getInternetProvider4Cost();
    void setInternetProvider5Cost(int ip5);
    int getInternetProvider5Cost();
};

#endif


