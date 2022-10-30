// CS1300 Fall 2021
// Author: Zack Leaf and Nathanael Lee
// Recitation: 212 - Nikhith Sannidhi (Zack) 213 - Jerome Gammie (Nathanael)
// Project 3

#include "bestBuy.h"
#include "Inventory.h"
#include <unistd.h>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

Inventory::Inventory() //default constructor sets each item to their initial values
{
    coinBalance = 200;
    CPUAmount = 0;
    GPUAmount = 0;
    powerAmount = 0;
    computerCaseAmount = 0;
    internetCardAmount = 0;
    keyboardAndMouseAmount = 0;
    preComputerAmount = 0;
    antivirusAmount = 0;
    VPNAmount = 1;
    IPLevel = 1;
    computerMaintenance = 100;
    viruses = 0;
    frustration = 0;
    carmenProgress = 0;
    hackersDefeated = 0;
}

Inventory::Inventory(int c, int cpu, int gpu, int p, int cc, int ic, int km, int pc, int as, int vpn, int ip, int cm, int v, int f, int cp, int hd)
{
    coinBalance = c;
    CPUAmount = cpu;
    GPUAmount = gpu;
    powerAmount = p;
    computerCaseAmount = cc;
    internetCardAmount = ic;
    keyboardAndMouseAmount = km;
    preComputerAmount = pc;
    antivirusAmount = as;
    VPNAmount = vpn;
    IPLevel = ip;
    computerMaintenance = cm;
    viruses = v;
    frustration = f;
    carmenProgress = cp;
    hackersDefeated = hd;
}

void Inventory::setCoinBalance(int c)
{
    coinBalance = c;
}

int Inventory::getCoinBalance()
{
    return coinBalance;
}

void Inventory::setCPUs(int cpu)
{
    CPUAmount = cpu;
}

int Inventory::getCPUs()
{
    return CPUAmount;
}

void Inventory::setGPUs(int gpu)
{
    GPUAmount = gpu;
}

int Inventory::getGPUs()
{
    return GPUAmount;
}

void Inventory::setPowerSupplyUnits(int p)
{
    powerAmount = p;
}

int Inventory::getPowerSupplyUnits()
{
    return powerAmount;
}

void Inventory::setComputerCases(int cc)
{
    computerCaseAmount = cc;
}

int Inventory::getComputerCases()
{
    return computerCaseAmount;
}

void Inventory::setInternetCards(int ic)
{
    internetCardAmount = ic;
}

int Inventory::getInternetCards()
{
    return internetCardAmount;
}

void Inventory::setKeyboardAndMouse(int km)
{
    keyboardAndMouseAmount = km;
}

int Inventory::getKeyboardAndMouse()
{
    return keyboardAndMouseAmount;
}

void Inventory::setPremadeComputer(int pc)
{
    preComputerAmount = pc;
}

int Inventory::getPremadeComputer()
{
    return preComputerAmount;
}

void Inventory::setAntivirusSoftware(int as)
{
    antivirusAmount = as;
}

int Inventory::getAntivirusSoftware()
{
    return antivirusAmount;
}

void Inventory::setVPN(int vpn)
{
    VPNAmount = vpn;
}

int Inventory::getVPN()
{
    return VPNAmount;
}

void Inventory::setInternetProviderLevel(int ip) /////////////
{
    IPLevel = ip;
}

int Inventory::getInternetProviderLevel()
{
    return IPLevel;
}

void Inventory::setComputerMaintenance(int cm)
{
    computerMaintenance = cm;
}

int Inventory::getComputerMaintenance()
{
    return computerMaintenance;
}

void Inventory::setViruses(int v)
{
    viruses = v;
}

int Inventory::getViruses()
{
    return viruses;
}

void Inventory::setFrustration(int f)
{
    frustration = f;
}

int Inventory::getFrustration()
{
    return frustration;
}

void Inventory::setCarmenProgress(int cp)
{
    carmenProgress = cp;
}

int Inventory::getCarmenProgress()
{
    return carmenProgress;
}

void Inventory::setHackersDefeated(int hd)
{
    hackersDefeated = hd;
}

int Inventory::getHackersDefeated()
{
    return hackersDefeated;
}

int Inventory::checkGameLost() // these are all conditions for losing
{
    if (getCarmenProgress() >= 100)
    {
        return 1;
    }
    else if (getFrustration() >= 100)
    {
        return 1;
    }
    else if (getComputerMaintenance() < 0 && getPremadeComputer() < 1) 
    {
        return 1;
    }
    else if (getComputerMaintenance() < 0 && getPremadeComputer() >= 1) 
    {
        return -1;
    }
    return 0;
}

bool Inventory::checkGameWin() //this is the condition for winning
{
    if (getHackersDefeated() >= 8)
    {
        return true;
    }
    return false;
}

bool Inventory::playerQuit(int quit) //this is the condition for when the player quits
{
    if (quit == 1)
    {
        return true;
    }
    return false;
}
