// CS1300 Fall 2021
// Author: Zack Leaf and Nathanael Lee
// Recitation: 212 - Nikhith Sannidhi (Zack) 213 - Jerome Gammie (Nathanael)
// Project 3

#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include <iomanip>
#include "bestBuy.h"
using namespace std;

class Inventory //this class contains all the items in the player's inventory
{
private:
    
    int coinBalance;
    int CPUAmount;
    int GPUAmount;
    int powerAmount;
    int computerCaseAmount;
    int internetCardAmount;
    int keyboardAndMouseAmount;
    int preComputerAmount;
    int antivirusAmount;
    int VPNAmount;
    int IPLevel;
    int computerMaintenance;
    int viruses;
    int frustration;
    int carmenProgress;
    int hackersDefeated;

public:

    Inventory(); //default constructor
    Inventory(int c, int cpu, int gpu, int p, int cc, int ic, int km, int pc, int as, int vpn, int ip, int cm, int v, int f, int cp, int hd); //parametarized constructor

    void setCoinBalance(int c);
    int getCoinBalance();
    void setCPUs(int cpu);
    int getCPUs();
    void setGPUs(int gpu);
    int getGPUs();
    void setPowerSupplyUnits(int p);
    int getPowerSupplyUnits();
    void setComputerCases(int cc);
    int getComputerCases();
    void setInternetCards(int ic);
    int getInternetCards();
    void setKeyboardAndMouse(int km);
    int getKeyboardAndMouse();
    void setPremadeComputer(int pc);
    int getPremadeComputer();
    void setAntivirusSoftware(int as);
    int getAntivirusSoftware();
    void setVPN(int vpn);
    int getVPN();
    void setInternetProviderLevel(int ip);
    int getInternetProviderLevel();
    void setComputerMaintenance(int cm);
    int getComputerMaintenance();
    void setViruses(int v);
    int getViruses();
    void setFrustration(int f);
    int getFrustration();
    void setCarmenProgress(int cp);
    int getCarmenProgress();
    void setHackersDefeated(int hd);
    int getHackersDefeated();
    void mainMenu();
    int checkGameLost();
    bool checkGameWin();
    bool playerQuit(int);
};

#endif
