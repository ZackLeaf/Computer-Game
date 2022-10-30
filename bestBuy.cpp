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

bestBuy::bestBuy() //default constructor sets each item to their initial values
{
    CPUCost = 10;
    GPUCost = 20;
    powerCost = 5;
    computerCaseCost = 15;
    internetCardCost = 5;
    keyboardAndMouseCost = 10;
    preComputerCost = 100;
    antivirusCost = 10;
    VPNCost = 20;
    IPCost2 = 10;
    IPCost3 = 25;
    IPCost4 = 40;
    IPCost5 = 50;
}

bestBuy::bestBuy(int cpu, int gpu, int p, int cc, int ic, int km, int pc, int as, int vpn, int ip2, int ip3, int ip4, int ip5)
{
    CPUCost = cpu;
    GPUCost = gpu;
    powerCost = p;
    computerCaseCost = cc;
    internetCardCost = ic;
    keyboardAndMouseCost = km;
    preComputerCost = pc;
    antivirusCost = as;
    VPNCost = vpn;
    IPCost2 = ip2;
    IPCost3 = ip3;
    IPCost4 = ip4;
    IPCost5 = ip5;
}

void bestBuy::setCPUCost(int cpu)
{
    CPUCost = cpu;
}

int bestBuy::getCPUCost()
{
    return CPUCost;
}

void bestBuy::setGPUCost(int gpu)
{
    GPUCost = gpu;
}

int bestBuy::getGPUCost()
{
    return GPUCost;
}

void bestBuy::setPowerSupplyUnitCost(int p)
{
    powerCost = p;
}

int bestBuy::getPowerSupplyUnitCost()
{
    return powerCost;
}

void bestBuy::setComputerCaseCost(int cc)
{
    computerCaseCost = cc;
}

int bestBuy::getComputerCaseCost()
{
    return computerCaseCost;
}

void bestBuy::setInternetCardCost(int ic)
{
    internetCardCost = ic;
}

int bestBuy::getInternetCardCost()
{
    return internetCardCost;
}

void bestBuy::setKeyboardAndMouseCost(int km)
{
    keyboardAndMouseCost = km;
}

int bestBuy::getKeyboardAndMouseCost()
{
    return keyboardAndMouseCost;
}

void bestBuy::setPremadeComputerCost(int pc)
{
    preComputerCost = pc;
}

int bestBuy::getPremadeComputerCost()
{
    return preComputerCost;
}

void bestBuy::setAntivirusSoftwareCost(int as)
{
    antivirusCost = as;
}

int bestBuy::getAntivirusSoftwareCost()
{
    return antivirusCost;
}

void bestBuy::setVPNCost(int vpn)
{
    VPNCost = vpn;
}

int bestBuy::getVPNCost()
{
    return VPNCost;
}

void bestBuy::setInternetProvider2Cost(int ip2)
{
    IPCost2 = ip2;
}

int bestBuy::getInternetProvider2Cost()
{
    return IPCost2;
}

void bestBuy::setInternetProvider3Cost(int ip3)
{
    IPCost3 = ip3;
}

int bestBuy::getInternetProvider3Cost()
{
    return IPCost3;
}

void bestBuy::setInternetProvider4Cost(int ip4)
{
    IPCost4 = ip4;
}

int bestBuy::getInternetProvider4Cost()
{
    return IPCost4;
}

void bestBuy::setInternetProvider5Cost(int ip5)
{
    IPCost5 = ip5;
}

int bestBuy::getInternetProvider5Cost()
{
    return IPCost5;
}
