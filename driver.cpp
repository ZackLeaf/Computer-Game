// CS1300 Fall 2021
// Author: Zack Leaf and Nathanael Lee
// Recitation: 212 - Nikhith Sannidhi (Zack) 213 - Jerome Gammie (Nathanael)
// Project 3
#include <unistd.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctype.h>
#include "bestBuy.h"
#include "Map.h"
#include "NPC.h"
#include "Inventory.h"
#include "Hackers.h"

using namespace std;

void displayLeaderboard() //this function displays the leaderboard
{
    fstream infile;
    string file = "results.txt"; //writing results to this file
    infile.open(file);
    string line = "";
    string currentname = "";
    string currentscore = "";
    vector<string> inputscore; //vectors that will get stuff added to them from text file
    vector<int> scores;
    vector<string> names;
    int counter2 = 0;
    int counter3 = -1;
    cout << "     Leaderboard:" << endl;
    cout << "Rank     Name, Score" << endl;
    cout << "--------------------" << endl;
    while (getline(infile, line))
    {
        int counter = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] != ',') // copied and pasted from previous function, I am now a wizard at writing split functions
            {
                if (counter == 0)
                {
                    currentname += line[i];
                }
                else
                {
                    currentscore += line[i];
                }
            }
            else
            {
                counter++;
            }
            //basic split function
        }
        names.push_back(currentname);//adding strings from split to string vectors
        inputscore.push_back(currentscore);
        currentscore = "";//important, you have to clear variablses so they dont keep getting stuff added to them
        currentname = "";
    }
    for (int i = 0; i < inputscore.size(); i++) //displaying leaderboard
    {
        if (i < 10)
        {
            cout << "  " << i + 1 << "      " << names[i] << ", " << inputscore[i] << endl;
        }
    }
}

void sort(string name, int moves) //this function updates the leaderboard
{
    fstream infile;//read and write
    string file = "results.txt";
    infile.open(file);
    string line = "";
    string currentname = "";
    string currentscore = "";
    vector<string> inputscore;
    vector<int> scores;
    vector<string> names;
    int counter2 = 0;
    int counter3 = -1;
    while (getline(infile, line))
    {
        int counter = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] != ',') // copied and pasted from previous function, I am now a wizard at writing split functions
            {
                if (counter == 0)
                {
                    currentname += line[i];
                }
                else
                {
                    currentscore += line[i];
                }
            }
            else
            {
                counter++;
            }
            //basic split function
        }
        names.push_back(currentname);
        inputscore.push_back(currentscore);
        counter2++;
        currentscore = "";
        currentname = "";
    }
    infile.close();
    for (int i = 0; i < inputscore.size(); i++)
    {
        scores.push_back(stoi(inputscore[i])); //changing stings to integers in vector so they can be sorted
    }
    for (int i = 0; i < inputscore.size(); i++) //sorting, finds index where the new player should be added
    {
        if (counter3 == -1)
        {
            if (moves < scores[i])
            {
                counter3 = i;
            }
        }
    }

    if (counter3 == -1) //if no larger value is found, counter 3 remains unchanged and the new information is put at the end.
    {
        inputscore.push_back(to_string(moves));
        names.push_back(name);
    }
    else //larger value is found, insert item at position
    {
        int index = counter3;
        inputscore.insert(inputscore.begin() + index, to_string(moves));
        names.insert(names.begin() + index, name);
    }
    infile.open("results.txt", std::ofstream::out | std::ofstream::trunc); //clears the file so we can add a new line in the spot it needs to be in
    infile.close();
    infile.open(file);
    for (int i = 0; i < inputscore.size(); i++)//re printing to file
    {
        infile << names[i] << "," << inputscore[i] << endl;
    }
}
int split(string text, char separator, string textarray[], int arraysize)
{
    if (text == "") //if there is a blank input, then return -1
    {
        return 0;
    }
    else
    {
        int position = 0;                            //this will be used to determine the number of positons in the new array
        for (int i = 0; i < int(text.length()); i++) //if there is an input, then check each character in the string to see if there is a separator
        {
            if (text[i] == separator) //if a separator is found, then move onto the next positon in the array.
            {
                position++;
                if (position >= arraysize) //if the number of positions in the array is found to be greater than the inputed arraysize, then return -1
                {
                    return -1;
                }
            }
            else
            {
                textarray[position] += text[i]; //as long as there is no separator, the function will continue adding the characters from the original string into the current array postion
            }
        }
        return position + 1; //because the for loop starts at 0, the returned value will need to be position+1
    }
}

void readHackers(Hackers hackerArray[20]) //reading from the list of hackers
{
    ifstream inFile1;
    string n = "hackers.txt";
    string a = "";
    char sep = ',';
    int max_words = 50;
    inFile1.open(n);
    int i = 0;
    while (getline(inFile1, a)) // spliting name and levels of hackers
    {
        string temparray[max_words];
        split(a, sep, temparray, max_words);
        hackerArray[i] = Hackers(temparray[0], stoi(temparray[1]));
        i++;
    }
}

int main() //used a switch statement to allow the user to choose from nine options
{
    system("clear");
    displayLeaderboard();
    cout << "Loading . . ." << endl;
    sleep(2);
    bestBuy bestbuy; //initializing objects from each class to be used in the function
    int movements = 0;
    NPC npc;
    Map map; // create object called map of type Map
    Inventory player;
    int hackercount = 0;
    Hackers hackerArray[20];
    NPC puzzles[10];
    npc.fillPuzzles(puzzles);
    int a = 0;
    readHackers(hackerArray);
    int currentroom = 1;
    int quit = 0;
    while (currentroom <= 5)
    {
        for (int room = 1; room <= 5; room++) //loop for each room
        {
            map.resetMap();
            srand(time(NULL)); //randomizing x and y values for spawing entities
            int x = 0;
            int y = 0;
            int x2 = 0;
            int y2 = 0;
            int x3 = 0;
            int y3 = 0;
            int x4 = 0;
            int y4 = 0;
            int x5 = 0;
            int y5 = 0;
            int x6 = 0;
            int y6 = 0;
            int x7 = 0;
            int y7 = 0;
            int hackersSpawn = rand() % 3 + 1; //random amount of hackers 1-3 and NPCs 1-3 will spawn in each room
            int NPCsSpawn = rand() % 3 + 1;

            do
            {
                x = rand() % 5; //randomizing values, checking they aren't on top of each other.  
                y = rand() % 9;
                x2 = rand() % 5;
                y2 = rand() % 9;
                x3 = rand() % 5;
                y3 = rand() % 9;
                x4 = rand() % 5;
                y4 = rand() % 9;
                x5 = rand() % 5;
                y5 = rand() % 9;
                x6 = rand() % 5;
                y6 = rand() % 9;
                x7 = rand() % 5;
                y7 = rand() % 9;
            } while (x == 0 && y == 0 || x2 == 0 && y2 == 0 || x3 == 0 && y3 == 0 || x4 == 0 && y4 == 0 || x5 == 0 && y5 == 0 || x6 == 0 && y6 == 0 || x7 == 0 && y7 == 0 || x == x2 && y == y2 || x == x3 && y == y3 || x == x4 && y == y4 || x == x5 && y == y5 || x == x6 && y == y6 || x == x7 && y == y7 || x2 == x3 && y2 == y3 || x2 == x4 && y2 == y4 || x2 == x5 && y2 == y5 || x2 == x6 && y2 == y6 || x2 == x7 && y2 == y7 || x3 == x4 && y3 == y4 || x3 == x5 && y3 == y5 || x3 == x6 && y3 == y6 || x3 == x7 && y3 == y7 || x4 == x5 && y4 == y5 || x4 == x6 && y4 == y6 || x4 == x7 && y4 == y7 || x5 == x6 && y5 == y6 || x5 == x7 && y5 == y7 || x6 == x7 && y6 == y7);

            if (hackersSpawn == 1)
            {
                map.spawnHacker(x5, y5);
                hackercount = 1;
            }
            else if (hackersSpawn == 2)
            {
                map.spawnHacker(x5, y5);
                map.spawnHacker(x6, y6);
                hackercount = 2;
            }
            else if (hackersSpawn == 3)
            {
                map.spawnHacker(x5, y5);
                map.spawnHacker(x6, y6);
                map.spawnHacker(x7, y7);
                hackercount = 3;
            }
            int value = 0;
            int value2 = 0;
            int value3 = 0;
            int value4 = 0;
            Hackers hackers[hackercount]; //hacker array of the hackers that spawn
            //cout << hackercount << endl;
            if (room == 1) //splitting into different rooms, because only want certain hackers to spawn based on the room number
            {
                srand(time(NULL));
                if (hackercount == 1)
                {
                    value = rand() % 4;
                    hackers[0].setName(hackerArray[value].getName());
                    hackers[0].setLevel(hackerArray[value].getLevel());
                }
                else if (hackercount == 2)
                {
                    do
                    {
                        value = rand() % 4;
                        value2 = rand() % 4;
                        hackers[0].setName(hackerArray[value].getName());
                        hackers[0].setLevel(hackerArray[value].getLevel());
                        hackers[1].setName(hackerArray[value2].getName());
                        hackers[1].setLevel(hackerArray[value2].getLevel());
                    } while (hackers[0].getName() == hackers[1].getName()); // keep going until the hackers are not the same name
                }
                else if (hackercount == 3)
                {
                    do
                    {
                        value = rand() % 4;
                        value2 = rand() % 4;
                        value3 = rand() % 4;
                        hackers[0].setName(hackerArray[value].getName());
                        hackers[0].setLevel(hackerArray[value].getLevel());
                        hackers[1].setName(hackerArray[value2].getName());
                        hackers[1].setLevel(hackerArray[value2].getLevel());
                        hackers[2].setName(hackerArray[value3].getName());
                        hackers[2].setLevel(hackerArray[value3].getLevel());
                    } while (hackers[0].getName() == hackers[1].getName() || hackers[0].getName() == hackers[2].getName() || hackers[1].getName() == hackers[2].getName());
                }
            }
            else if (room == 2)
            {
                srand(time(NULL));
                if (hackercount == 1)
                {
                    value = rand() % 4 + 4;
                    hackers[0].setName(hackerArray[value].getName());
                    hackers[0].setLevel(hackerArray[value].getLevel());
                }
                else if (hackercount == 2)
                {
                    do
                    {
                        value = rand() % 4 + 4;
                        value2 = rand() % 4 + 4;
                        hackers[0].setName(hackerArray[value].getName());
                        hackers[0].setLevel(hackerArray[value].getLevel());
                        hackers[1].setName(hackerArray[value2].getName());
                        hackers[1].setLevel(hackerArray[value2].getLevel());
                    } while (hackers[0].getName() == hackers[1].getName());
                }
                else if (hackercount == 3)
                {
                    do
                    {
                        value = rand() % 4 + 4;
                        value2 = rand() % 4 + 4;
                        value3 = rand() % 4 + 4;
                        hackers[0].setName(hackerArray[value].getName());
                        hackers[0].setLevel(hackerArray[value].getLevel());
                        hackers[1].setName(hackerArray[value2].getName());
                        hackers[1].setLevel(hackerArray[value2].getLevel());
                        hackers[2].setName(hackerArray[value3].getName());
                        hackers[2].setLevel(hackerArray[value3].getLevel());
                    } while (hackers[0].getName() == hackers[1].getName() || hackers[0].getName() == hackers[2].getName() || hackers[1].getName() == hackers[2].getName());
                }
            }
            else if (room == 3)
            {
                srand(time(NULL));
                if (hackercount == 1)
                {
                    value = rand() % 4 + 8;
                    hackers[0].setName(hackerArray[value].getName());
                    hackers[0].setLevel(hackerArray[value].getLevel());
                }
                else if (hackercount == 2)
                {
                    do
                    {
                        value = rand() % 4 + 8;
                        value2 = rand() % 4 + 8;
                        hackers[0].setName(hackerArray[value].getName());
                        hackers[0].setLevel(hackerArray[value].getLevel());
                        hackers[1].setName(hackerArray[value2].getName());
                        hackers[1].setLevel(hackerArray[value2].getLevel());
                    } while (hackers[0].getName() == hackers[1].getName());
                }
                else if (hackercount == 3)
                {
                    do
                    {
                        value = rand() % 4 + 8;
                        value2 = rand() % 4 + 8;
                        value3 = rand() % 4 + 8;
                        hackers[0].setName(hackerArray[value].getName());
                        hackers[0].setLevel(hackerArray[value].getLevel());
                        hackers[1].setName(hackerArray[value2].getName());
                        hackers[1].setLevel(hackerArray[value2].getLevel());
                        hackers[2].setName(hackerArray[value3].getName());
                        hackers[2].setLevel(hackerArray[value3].getLevel());
                    } while (hackers[0].getName() == hackers[1].getName() || hackers[0].getName() == hackers[2].getName() || hackers[1].getName() == hackers[2].getName());
                }
            }
            else if (room == 4)
            {
                srand(time(NULL));
                if (hackercount == 1)
                {
                    value = rand() % 4 + 12;
                    hackers[0].setName(hackerArray[value].getName());
                    hackers[0].setLevel(hackerArray[value].getLevel());
                }
                else if (hackercount == 2)
                {
                    do
                    {
                        value = rand() % 4 + 12;
                        value2 = rand() % 4 + 12;
                        hackers[0].setName(hackerArray[value].getName());
                        hackers[0].setLevel(hackerArray[value].getLevel());
                        hackers[1].setName(hackerArray[value2].getName());
                        hackers[1].setLevel(hackerArray[value2].getLevel());
                    } while (hackers[0].getName() == hackers[1].getName());
                }
                else if (hackercount == 3)
                {
                    do
                    {
                        value = rand() % 4 + 12;
                        value2 = rand() % 4 + 12;
                        value3 = rand() % 4 + 12;
                        hackers[0].setName(hackerArray[value].getName());
                        hackers[0].setLevel(hackerArray[value].getLevel());
                        hackers[1].setName(hackerArray[value2].getName());
                        hackers[1].setLevel(hackerArray[value2].getLevel());
                        hackers[2].setName(hackerArray[value3].getName());
                        hackers[2].setLevel(hackerArray[value3].getLevel());
                    } while (hackers[0].getName() == hackers[1].getName() || hackers[0].getName() == hackers[2].getName() || hackers[1].getName() == hackers[2].getName());
                }
            }
            else if (room == 5)
            {
                srand(time(NULL));
                if (hackercount == 1)
                {
                    value = rand() % 4 + 16;
                    hackers[0].setName(hackerArray[value].getName());
                    hackers[0].setLevel(hackerArray[value].getLevel());
                }
                else if (hackercount == 2)
                {
                    do
                    {
                        value = rand() % 4 + 16;
                        value2 = rand() % 4 + 16;
                        hackers[0].setName(hackerArray[value].getName());
                        hackers[0].setLevel(hackerArray[value].getLevel());
                        hackers[1].setName(hackerArray[value2].getName());
                        hackers[1].setLevel(hackerArray[value2].getLevel());
                    } while (hackers[0].getName() == hackers[1].getName());
                }
                else if (hackercount == 3)
                {
                    do
                    {
                        value = rand() % 4 + 16;
                        value2 = rand() % 4 + 16;
                        value3 = rand() % 4 + 16;
                        hackers[0].setName(hackerArray[value].getName());
                        hackers[0].setLevel(hackerArray[value].getLevel());
                        hackers[1].setName(hackerArray[value2].getName());
                        hackers[1].setLevel(hackerArray[value2].getLevel());
                        hackers[2].setName(hackerArray[value3].getName());
                        hackers[2].setLevel(hackerArray[value3].getLevel());
                    } while (hackers[0].getName() == hackers[1].getName() || hackers[0].getName() == hackers[2].getName() || hackers[1].getName() == hackers[2].getName());
                }
            }
            if (NPCsSpawn == 1)
            {
                map.spawnNPC(x2, y2);
            }
            else if (NPCsSpawn == 2)
            {
                map.spawnNPC(x2, y2);
                map.spawnNPC(x3, y3);
            }
            else if (NPCsSpawn == 3)
            {
                map.spawnNPC(x2, y2);
                map.spawnNPC(x3, y3);
                map.spawnNPC(x4, y4);
            }
            if (room == 1) //bestbuy should spawn at (0,0) if it is the first room
            {
                map.spawnBestBuy(0, 0);
            }
            else
            {
                map.spawnBestBuy(x, y);
            }

            char move; // for storing user input
            int set = 0;
            int set2 = 0;
            string RowColName[5][9] = { "" }; //this 2D array will be used to save the same hacker locations when they are randomized on the map
            int row = 0;
            int column = 0;
            string name = "";
            while (player.checkGameLost() != 1 && player.playerQuit(quit) != true && player.checkGameWin() != true && room == currentroom) //this is the main game loop, one loop is a move
            {
                map.displayMap(); // pretty print map_data in terminal
                if (map.isBestBuyLocation()) //check first if in a bestbuy, bestbuy should be first thing when you start in room 1
                {
                    cout << "You're in a Best Buy!" << endl;
                    sleep(0.5);
                    system("clear");
                    int option = 0;
                    int option2 = 0;
                    int option3 = 0;
                    double multiplyer = 0;
                    if (room == 1) //inflation
                    {
                        multiplyer = 1.0;
                    }
                    else if (room == 2)
                    {
                        multiplyer = 1.1;
                    }
                    else if (room == 3)
                    {
                        multiplyer = 1.2;
                    }
                    else if (room == 4)
                    {
                        multiplyer = 1.25;
                    }
                    else if (room == 5)
                    {
                        multiplyer = 1.3;
                    }
                    cout << endl;
                    cout << "You have 200 dogecoins, 1 computer and 1 VPN. You will need to spend the rest of your money on the following items: " << endl;
                    cout << endl;
                    cout << "- COMPUTER PARTS. If your computer breaks, you need 5 computer parts to make a new one." << endl;
                    cout << "- ANTIVIRUS SOFTWARE. If your computer is infected with a virus, use the antivirus software to get rid of it." << endl;
                    cout << "- VIRTUAL PRIVATE NETWORK (VPN). The more VPNs you have the harder it is for a hacker to infect your computer with" << endl;
                    cout << "- INTERNET PROVIDER. The better the internet provider, the more reliable your hacking will be." << endl;
                    cout << endl;
                    cout << "You can spend all of your money here before you start your journey, or you can save some to spend on a different\nelectronics site along the way. But beware, some of the websites online are shady, and they won’t always give you a\nfair price..." << endl;
                    cout << endl;
                    do
                    {
                        cout << "Select a category (1-4) to view parts and make a purchase, or select 5 to move onto the first server room" << endl;
                        cout << "1. Computer Parts \n2. Antivirus software \n3. Virtual Private Network (VPN) \n4. Internet Provider \n5. Exit Best Buy and enter the next server room " << endl;
                        if (cin >> option)
                        {
                            switch (option)
                            {
                            case 1:
                            {
                                do
                                {
                                    system("clear");
                                    cout << "Best Buy recommends that the player should purchase at least 1 of each computer part in case your main computer breaks." << endl;
                                    cout << "You can have a maximum of 3 of each computer part and 1 extra premade computer. Select which part you would like to purchase or press 8 to cancel:" << endl;
                                    cout << "1. CPU "
                                        << "(" << 10 * multiplyer << " Dogecoins)" << endl; //using inflation multiplyer
                                    cout << "2. GPU "
                                        << "(" << 20 * multiplyer << " Dogecoins)" << endl;
                                    cout << "3. Power Supply Unit "
                                        << "(" << 5 * multiplyer << " Dogecoins)" << endl;
                                    cout << "4. Computer Case "
                                        << "(" << 15 * multiplyer << " Dogecoins)" << endl;
                                    cout << "5. Internet card "
                                        << "(" << 5 * multiplyer << " Dogecoins)" << endl;
                                    cout << "6. Keyboard and mouse "
                                        << "(" << 10 * multiplyer << " Dogecoins)" << endl;
                                    cout << "7. Premade computer "
                                        << "(" << 100 * multiplyer << " Dogecoins)" << endl;
                                    cout << "8. Cancel" << endl;
                                    cin.clear();
                                    if (cin >> option2)
                                    {
                                        switch (option2)
                                        {
                                        case 1:
                                        {
                                            system("clear");
                                            cout << "How many CPUs would you like to purchase? " << endl;
                                            cin.clear();
                                            cin >> option2;
                                            if ((player.getCPUs() + option2) > 3) //keeping the number of a specific part in inventory under 3
                                            {
                                                cout << "You can not have more than three of each computer part in your inventory." << endl;
                                                cout << "You already have " << player.getCPUs() << " CPUs." << endl;
                                                sleep(3.5);
                                            }
                                            else
                                            {
                                                cout << "The total cost for " << option2 << " CPUs is " << option2 * bestbuy.getCPUCost() * multiplyer << " Dogecoin." << endl;
                                                if (player.getCoinBalance() >= option2 * bestbuy.getCPUCost() * multiplyer)
                                                {
                                                    player.setCPUs(player.getCPUs() + option2);
                                                    player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getCPUCost());
                                                    cout << "You now have " << player.getCPUs() << " CPUs in your Inventory." << endl;
                                                    cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "You don't have enough money to complete this purchase!" << endl;
                                                    cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                            }
                                            break;
                                        }
                                        case 2:
                                        {
                                            system("clear");
                                            cout << "How many GPUs would you like to purchase? " << endl;
                                            cin.clear();
                                            cin >> option2;
                                            if ((player.getGPUs() + option2) > 3)
                                            {
                                                cout << "You can not have more than three of each computer part in your inventory." << endl;
                                                cout << "You already have " << player.getGPUs() << " GPUs." << endl;
                                                sleep(3.5);
                                            }
                                            else
                                            {
                                                cout << "The total cost for " << option2 << " GPUs is " << option2 * bestbuy.getGPUCost() * multiplyer << " Dogecoin." << endl;
                                                if (player.getCoinBalance() >= option2 * bestbuy.getGPUCost() * multiplyer)
                                                {
                                                    player.setGPUs(player.getGPUs() + option2);
                                                    player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getGPUCost());
                                                    cout << "You now have " << player.getGPUs() << " GPUs in your Inventory." << endl;
                                                    cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "You don't have enough money to complete this purchase!" << endl;
                                                    cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                            }
                                            break;
                                        }
                                        case 3:
                                        {
                                            system("clear");
                                            cout << "How many Power Supply Units would you like to purchase? " << endl;
                                            cin.clear();
                                            cin >> option2;
                                            if ((player.getPowerSupplyUnits() + option2) > 3)
                                            {
                                                cout << "You can not have more than three of each computer part in your inventory." << endl;
                                                cout << "You already have " << player.getPowerSupplyUnits() << " Power Supply Units." << endl;
                                                sleep(3.5);
                                            }
                                            else
                                            {
                                                cout << "The total cost for " << option2 << " Power Supply Units is " << option2 * bestbuy.getPowerSupplyUnitCost() * multiplyer << " Dogecoin." << endl;
                                                if (player.getCoinBalance() >= option2 * bestbuy.getPowerSupplyUnitCost() * multiplyer)
                                                {
                                                    player.setPowerSupplyUnits(player.getPowerSupplyUnits() + option2);
                                                    player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getPowerSupplyUnitCost());
                                                    cout << "You now have " << player.getPowerSupplyUnits() << " Power Supply Units in your Inventory." << endl;
                                                    cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "You don't have enough money to complete this purchase!" << endl;
                                                    cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                            }
                                            break;
                                        }
                                        case 4:
                                        {
                                            system("clear");
                                            cout << "How many Computer Cases would you like to purchase? " << endl;
                                            cin.clear();
                                            cin >> option2;
                                            if ((player.getComputerCases() + option2) > 3)
                                            {
                                                cout << "You can not have more than three of each computer part in your inventory." << endl;
                                                cout << "You already have " << player.getComputerCases() << " Computer Cases." << endl;
                                                sleep(3.5);
                                            }
                                            else
                                            {
                                                cout << "The total cost for " << option2 << " Computer Cases is " << option2 * bestbuy.getComputerCaseCost() * multiplyer << " Dogecoin." << endl;
                                                if (player.getCoinBalance() >= option2 * bestbuy.getComputerCaseCost() * multiplyer)
                                                {
                                                    player.setComputerCases(player.getComputerCases() + option2);
                                                    player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getComputerCaseCost());
                                                    cout << "You now have " << player.getComputerCases() << " Computer Cases in your Inventory." << endl;
                                                    cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "You don't have enough money to complete this purchase!" << endl;
                                                    cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                            }
                                            break;
                                        }
                                        case 5:
                                        {
                                            system("clear");
                                            cout << "How many Internet cards would you like to purchase? " << endl;
                                            cin.clear();
                                            cin >> option2;
                                            if ((player.getInternetCards() + option2) > 3)
                                            {
                                                cout << "You can not have more than three of each computer part in your inventory." << endl;
                                                cout << "You already have " << player.getInternetCards() << " Internet cards." << endl;
                                                sleep(3.5);
                                            }
                                            else
                                            {
                                                cout << "The total cost for " << option2 << " Internet cards is " << option2 * bestbuy.getInternetCardCost() * multiplyer << " Dogecoin." << endl;
                                                if (player.getCoinBalance() >= option2 * bestbuy.getInternetCardCost() * multiplyer)
                                                {
                                                    player.setInternetCards(player.getInternetCards() + option2);
                                                    player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getInternetCardCost());
                                                    cout << "You now have " << player.getInternetCards() << " Internet cards in your Inventory." << endl;
                                                    cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "You don't have enough money to complete this purchase!" << endl;
                                                    cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                            }
                                            break;
                                        }
                                        case 6:
                                        {
                                            system("clear");
                                            cout << "How many Keyboard and mouse would you like to purchase? " << endl;
                                            cin.clear();
                                            cin >> option2;
                                            if ((player.getKeyboardAndMouse() + option2) > 3)
                                            {
                                                cout << "You can not have more than three of each computer part in your inventory." << endl;
                                                cout << "You already have " << player.getKeyboardAndMouse() << " Keyboard and mouse." << endl;
                                                sleep(3.5);
                                            }
                                            else
                                            {
                                                cout << "The total cost for " << option2 << " Keyboard and mouse is " << option2 * bestbuy.getKeyboardAndMouseCost() * multiplyer << " Dogecoin." << endl;
                                                if (player.getCoinBalance() >= option2 * bestbuy.getKeyboardAndMouseCost() * multiplyer)
                                                {
                                                    player.setKeyboardAndMouse(player.getKeyboardAndMouse() + option2);
                                                    player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getKeyboardAndMouseCost());
                                                    cout << "You now have " << player.getKeyboardAndMouse() << " Keyboard and mouse in your Inventory." << endl;
                                                    cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "You don't have enough money to complete this purchase!" << endl;
                                                    cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                            }
                                            break;
                                        }
                                        case 7:
                                        {
                                            system("clear");
                                            if ((player.getPremadeComputer()) > 1)
                                            {
                                                cout << "You can not have more than one premade computer in your inventory." << endl;
                                                cout << "You already have " << player.getPremadeComputer() << " premade computer." << endl;
                                                sleep(3.5);
                                            }
                                            else
                                            {
                                                cout << "The total cost for a premade computer is " << bestbuy.getPremadeComputerCost() * multiplyer << " Dogecoin." << endl;
                                                if (player.getCoinBalance() >= bestbuy.getPremadeComputerCost() * multiplyer)
                                                {
                                                    player.setPremadeComputer(player.getPremadeComputer() + 1);
                                                    player.setCoinBalance(player.getCoinBalance() - bestbuy.getPremadeComputerCost());
                                                    cout << "You now have " << player.getPremadeComputer() << " premade Computer in your Inventory." << endl;
                                                    cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "You don't have enough money to complete this purchase!" << endl;
                                                    cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                    sleep(3.5);
                                                }
                                            }
                                            break;
                                        }
                                        case 8:
                                        {
                                            system("clear");
                                            break;
                                        }
                                        default:
                                        {
                                            cout << "Please enter a valid option." << endl;
                                            sleep(1.5);
                                        }
                                        }
                                    }
                                    else // input failure: eg. the user entered a alpha character
                                    {
                                        cout << "Please enter a valid option. " << endl; // inform the user
                                        cin.clear();                                     // put the stream back into a good state
                                        cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                                        sleep(1.5);
                                    }
                                } while (option2 != 8);
                                break;
                            }
                            case 2:
                            {
                                system("clear");
                                cout << "One USB stick of antivirus software costs 10 Dogecoins and will give you a one-time use to get rid of any viruses on your computer." << endl;
                                cout << "How many USB sticks of antivirus software would you like to buy?" << endl;
                                if (cin >> option2)
                                {
                                    if ((player.getAntivirusSoftware() + option2) > 3)
                                    {
                                        cout << "You can not have more than three USB sticks of antivirus software in your inventory." << endl;
                                        cout << "You already have " << player.getAntivirusSoftware() << " USB sticks of antivirus software." << endl;
                                    }
                                    else
                                    {
                                        cout << "The total cost for " << option2 << " USB sticks of antivirus software is " << option2 * bestbuy.getAntivirusSoftwareCost() * multiplyer << " Dogecoin." << endl;
                                        if (player.getCoinBalance() >= bestbuy.getVPNCost() * multiplyer)
                                        {
                                            player.setAntivirusSoftware(player.getAntivirusSoftware() + option2);
                                            player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getAntivirusSoftwareCost());
                                            cout << "You now have " << player.getAntivirusSoftware() << " USB sticks of antivirus software in your Inventory." << endl;
                                            cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                        }
                                        else
                                        {
                                            cout << "You don't have enough money to complete this purchase!" << endl;
                                            cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                            sleep(3.5);
                                        }
                                    }
                                    break;
                                }
                                else // input failure: eg. the user entered a alpha character
                                {
                                    cout << "Please enter a valid option. " << endl; // inform the user
                                    cin.clear();                                     // put the stream back into a good state
                                    cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                                    sleep(1.5);
                                }
                                break;
                            }
                            case 3:
                            {
                                system("clear");
                                cout << "A VPN costs 20 Dogecoins each. VPNs reduce your chances of getting hacked by preventing hackers from tracking down your main computer." << endl;
                                cout << "The increase in security maxes out at 2 VPNs. " << endl;
                                cout << "How many VPNs would you like to buy?" << endl;
                                if (cin >> option2)
                                {
                                    if ((player.getVPN() + option2) > 3)
                                    {
                                        cout << "You can not have more than three VPNs in your inventory." << endl;
                                        cout << "You already have " << player.getVPN() << " VPNs." << endl;
                                    }
                                    else
                                    {
                                        cout << "The total cost for " << option2 << " VPNs is " << option2 * bestbuy.getVPNCost() * multiplyer << " Dogecoin." << endl;
                                        if (player.getCoinBalance() >= bestbuy.getVPNCost() * multiplyer)
                                        {
                                            player.setVPN(player.getVPN() + option2);
                                            player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getVPNCost());
                                            cout << "You now have " << player.getVPN() << " VPNs in your Inventory." << endl;
                                            cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                        }
                                        else
                                        {
                                            cout << "You don't have enough money to complete this purchase!" << endl;
                                            cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                            sleep(3.5);
                                        }
                                    }
                                    break;
                                }
                                else // input failure: eg. the user entered a alpha character
                                {
                                    cout << "Please enter a valid option. " << endl; // inform the user
                                    cin.clear();                                     // put the stream back into a good state
                                    cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                                    sleep(1.5);
                                }
                                break;
                            }
                            case 4:
                            {
                                system("clear");
                                cout << "Internet provider level 2 costs 10 Dogecoins. " << endl;
                                cout << "Internet provider level 3 costs 25 Dogecoins. " << endl;
                                cout << "Internet provider level 4 costs 40 Dogecoins. " << endl;
                                cout << "Internet provider level 5 costs 50 Dogecoins. " << endl;
                                cout << "What internet provider level would you like to buy? (Enter a level)" << endl;
                                int value = 0;
                                if (cin >> option2)
                                {
                                    if (option2 == 2)
                                    {
                                        value = 2;
                                        if (player.getCoinBalance() > 10 * multiplyer)
                                        {
                                            if (player.getInternetProviderLevel() < 2)
                                            {

                                                player.setInternetProviderLevel(value);
                                                cout << "You now have internet provider level " << player.getInternetProviderLevel() << "." << endl;
                                                player.setCoinBalance(player.getCoinBalance() - bestbuy.getInternetProvider2Cost());
                                                cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                sleep(3);
                                            }
                                            else
                                            {
                                                cout << "You already have internet provider level " << player.getInternetProviderLevel() << "!" << endl;
                                                sleep(2);
                                            }
                                        }
                                        else
                                        {
                                            cout << "You don't have enough money to complete this purchase!" << endl;
                                            cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                            sleep(3);
                                        }
                                    }
                                    else if (option2 == 3)
                                    {
                                        value = 3;
                                        if (player.getCoinBalance() > 25 * multiplyer)
                                        {
                                            if (player.getInternetProviderLevel() < 3)
                                            {
                                                player.setInternetProviderLevel(value);
                                                cout << "You now have internet provider level " << player.getInternetProviderLevel() << "." << endl;
                                                player.setCoinBalance(player.getCoinBalance() - bestbuy.getInternetProvider3Cost());
                                                cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                sleep(3);
                                            }
                                            else
                                            {
                                                cout << "You already have internet provider level " << player.getInternetProviderLevel() << "!" << endl;
                                                sleep(2);
                                            }
                                        }
                                        else
                                        {
                                            cout << "You don't have enough money to complete this purchase!" << endl;
                                            cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                            sleep(3);
                                        }
                                    }
                                    else if (option2 == 4)
                                    {
                                        value = 4;
                                        if (player.getCoinBalance() > 40 * multiplyer)
                                        {
                                            if (player.getInternetProviderLevel() < 4)
                                            {
                                                player.setInternetProviderLevel(value);
                                                cout << "You now have internet provider level " << player.getInternetProviderLevel() << "." << endl;
                                                player.setCoinBalance(player.getCoinBalance() - bestbuy.getInternetProvider4Cost());
                                                cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                sleep(3);
                                            }
                                            else
                                            {
                                                cout << "You already have internet provider level " << player.getInternetProviderLevel() << "!" << endl;
                                                sleep(2);
                                            }
                                        }
                                        else
                                        {
                                            cout << "You don't have enough money to complete this purchase!" << endl;
                                            cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                            sleep(3);
                                        }
                                    }
                                    else if (option2 == 5)
                                    {
                                        value = 5;
                                        if (player.getCoinBalance() > 50 * multiplyer)
                                        {
                                            if (player.getInternetProviderLevel() < 5)
                                            {
                                                player.setInternetProviderLevel(value);
                                                cout << "You now have internet provider level " << player.getInternetProviderLevel() << "." << endl;
                                                player.setCoinBalance(player.getCoinBalance() - bestbuy.getInternetProvider5Cost());
                                                cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                sleep(3);
                                            }
                                            else
                                            {
                                                cout << "You already have internet provider level " << player.getInternetProviderLevel() << "!" << endl;
                                                sleep(2);
                                            }
                                        }
                                        else
                                        {
                                            cout << "You don't have enough money to complete this purchase!" << endl;
                                            cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                            sleep(3);
                                        }
                                    }
                                    else
                                    {
                                        cout << "Please enter a valid internet provider level " << endl;
                                        sleep(1.5);
                                    }
                                }
                                else // input failure: eg. the user entered a alpha character
                                {
                                    cout << "Please enter a valid option. " << endl; // inform the user
                                    cin.clear();                                     // put the stream back into a good state
                                    cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                                    sleep(1.5);
                                }
                                break;
                            }
                            case 5:
                            {
                                break;
                            }
                            default:
                            {
                                cout << "Please enter a valid option." << endl;
                                sleep(1.5);
                            }
                            }
                        }
                        else // input failure: eg. the user entered a alpha character
                        {
                            cout << "Please enter a valid option. " << endl; // inform the user
                            cin.clear();                                     // put the stream back into a good state
                            cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                            sleep(1.5);
                        }
                    } while (option != 5); //repeat unless the user selects quit
                }
                system("clear");
                if (map.getHackerCount() == 0) // this menu will show when there are no more hackers on the map
                {
                    system("clear");
                    cout << "You have cleared the room of Carmen's Hackers!" << endl;
                    cout << "Would you like to move onto the next room?" << endl;
                    cout << "1. Yes" << endl;
                    cout << "2. No" << endl;
                    int option = 0;
                    if (cin >> option)
                    {
                        if (option == 1)
                        {
                            set = 1;
                        }
                        else if (option != 2 && option != 1)
                        {
                            cout << "Please enter a valid option. " << endl;
                        }
                        else
                        {
                            set = 0;
                        }
                    }
                    else
                    {
                        cout << "Please enter a valid option. " << endl; // inform the user
                        cin.clear();                                     // put the stream back into a good state
                        cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                        sleep(0.5);
                    }
                }
                if (set == 1) //if the user inputs to move on to the next room, this value is incremented so that the loop will not continue
                {
                    currentroom++;
                }
                else
                {
                    system("clear");
                    map.displayMap();
                    //cout << player.getInternetProviderLevel() << endl;
                    cout << "Valid moves are: " << endl;
                    map.displayMoves(); // give user a menu of valid moves to pick from

                    cout << "Input a move: ";
                    cin >> move;
                    cout << endl;
                    map.executeMove(move); // move the player on map based on user input
                    player.setCoinBalance(player.getCoinBalance() + 15); // player gets 15 coins with each move
                    if (player.checkGameLost() == -1) //this checks if the player's computer was destoryed, but they had a backup one
                    {
                        system("clear");
                        cout << "Your computer has been destoryed.  Good thing you have a backup one!" << endl;
                        player.setPremadeComputer(player.getPremadeComputer() - 1);
                        player.setViruses(0);
                        player.setPremadeComputer(0);
                        player.setComputerMaintenance(100);
                        sleep(3);
                    }
                    if (player.getViruses() >= 1) //computer maitenece will go down by 10 times however many viruses there are
                    {
                        player.setComputerMaintenance(player.getComputerMaintenance() - player.getViruses() * 10);
                    }
                    movements++; //checking number of moves that will be displayed in leaderboard

                    if (map.isBestBuyLocation())
                    {
                        cout << "You're in a Best Buy!" << endl;
                        sleep(0.5);
                        system("clear");
                        int option = 0;
                        int option2 = 0;
                        int option3 = 0;
                        double multiplyer = 0;
                        if (room == 1)
                        {
                            multiplyer = 1.0;
                        }
                        else if (room == 2)
                        {
                            multiplyer = 1.1;
                        }
                        else if (room == 3)
                        {
                            multiplyer = 1.2;
                        }
                        else if (room == 4)
                        {
                            multiplyer = 1.25;
                        }
                        else if (room == 5)
                        {
                            multiplyer = 1.3;
                        }
                        cout << endl;
                        cout << "You have 200 dogecoins, 1 computer and 1 VPN. You will need to spend the rest of your money on the following items: " << endl;
                        cout << endl;
                        cout << "- COMPUTER PARTS. If your computer breaks, you need 5 computer parts to make a new one." << endl;
                        cout << "- ANTIVIRUS SOFTWARE. If your computer is infected with a virus, use the antivirus software to get rid of it." << endl;
                        cout << "- VIRTUAL PRIVATE NETWORK (VPN). The more VPNs you have the harder it is for a hacker to infect your computer with" << endl;
                        cout << "- INTERNET PROVIDER. The better the internet provider, the more reliable your hacking will be." << endl;
                        cout << endl;
                        cout << "You can spend all of your money here before you start your journey, or you can save some to spend on a different\nelectronics site along the way. But beware, some of the websites online are shady, and they won’t always give you a\nfair price..." << endl;
                        cout << endl;
                        do
                        {
                            cout << "Select a category (1-4) to view parts and make a purchase, or select 5 to move onto the first server room" << endl;
                            cout << "1. Computer Parts \n2. Antivirus software \n3. Virtual Private Network (VPN) \n4. Internet Provider \n5. Exit Best Buy and enter the next server room " << endl;
                            if (cin >> option)
                            {
                                switch (option)
                                {
                                case 1:
                                {
                                    do
                                    {
                                        system("clear");
                                        cout << "Best Buy recommends that the player should purchase at least 1 of each computer part in case your main computer breaks." << endl;
                                        cout << "You can have a maximum of 3 of each computer part and 1 extra premade computer. Select which part you would like to purchase or press 8 to cancel:" << endl;
                                        cout << "1. CPU "
                                            << "(" << 10 * multiplyer << " Dogecoins)" << endl;
                                        cout << "2. GPU "
                                            << "(" << 20 * multiplyer << " Dogecoins)" << endl;
                                        cout << "3. Power Supply Unit "
                                            << "(" << 5 * multiplyer << " Dogecoins)" << endl;
                                        cout << "4. Computer Case "
                                            << "(" << 15 * multiplyer << " Dogecoins)" << endl;
                                        cout << "5. Internet card "
                                            << "(" << 5 * multiplyer << " Dogecoins)" << endl;
                                        cout << "6. Keyboard and mouse "
                                            << "(" << 10 * multiplyer << " Dogecoins)" << endl;
                                        cout << "7. Premade computer "
                                            << "(" << 100 * multiplyer << " Dogecoins)" << endl;
                                        cout << "8. Cancel" << endl;
                                        cin.clear();
                                        if (cin >> option2)
                                        {
                                            switch (option2)
                                            {
                                            case 1:
                                            {
                                                system("clear");
                                                cout << "How many CPUs would you like to purchase? " << endl;
                                                cin.clear();
                                                cin >> option2;
                                                if ((player.getCPUs() + option2) > 3)
                                                {
                                                    cout << "You can not have more than three of each computer part in your inventory." << endl;
                                                    cout << "You already have " << player.getCPUs() << " CPUs." << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "The total cost for " << option2 << " CPUs is " << option2 * bestbuy.getCPUCost() * multiplyer << " Dogecoin." << endl;
                                                    if (player.getCoinBalance() >= option2 * bestbuy.getCPUCost() * multiplyer)
                                                    {
                                                        player.setCPUs(player.getCPUs() + option2);
                                                        player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getCPUCost());
                                                        cout << "You now have " << player.getCPUs() << " CPUs in your Inventory." << endl;
                                                        cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                    else
                                                    {
                                                        cout << "You don't have enough money to complete this purchase!" << endl;
                                                        cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                }
                                                break;
                                            }
                                            case 2:
                                            {
                                                system("clear");
                                                cout << "How many GPUs would you like to purchase? " << endl;
                                                cin.clear();
                                                cin >> option2;
                                                if ((player.getGPUs() + option2) > 3)
                                                {
                                                    cout << "You can not have more than three of each computer part in your inventory." << endl;
                                                    cout << "You already have " << player.getGPUs() << " GPUs." << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "The total cost for " << option2 << " GPUs is " << option2 * bestbuy.getGPUCost() * multiplyer << " Dogecoin." << endl;
                                                    if (player.getCoinBalance() >= option2 * bestbuy.getGPUCost() * multiplyer)
                                                    {
                                                        player.setGPUs(player.getGPUs() + option2);
                                                        player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getGPUCost());
                                                        cout << "You now have " << player.getGPUs() << " GPUs in your Inventory." << endl;
                                                        cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                    else
                                                    {
                                                        cout << "You don't have enough money to complete this purchase!" << endl;
                                                        cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                }
                                                break;
                                            }
                                            case 3:
                                            {
                                                system("clear");
                                                cout << "How many Power Supply Units would you like to purchase? " << endl;
                                                cin.clear();
                                                cin >> option2;
                                                if ((player.getPowerSupplyUnits() + option2) > 3)
                                                {
                                                    cout << "You can not have more than three of each computer part in your inventory." << endl;
                                                    cout << "You already have " << player.getPowerSupplyUnits() << " Power Supply Units." << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "The total cost for " << option2 << " Power Supply Units is " << option2 * bestbuy.getPowerSupplyUnitCost() * multiplyer << " Dogecoin." << endl;
                                                    if (player.getCoinBalance() >= option2 * bestbuy.getPowerSupplyUnitCost() * multiplyer)
                                                    {
                                                        player.setPowerSupplyUnits(player.getPowerSupplyUnits() + option2);
                                                        player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getPowerSupplyUnitCost());
                                                        cout << "You now have " << player.getPowerSupplyUnits() << " Power Supply Units in your Inventory." << endl;
                                                        cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                    else
                                                    {
                                                        cout << "You don't have enough money to complete this purchase!" << endl;
                                                        cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                }
                                                break;
                                            }
                                            case 4:
                                            {
                                                system("clear");
                                                cout << "How many Computer Cases would you like to purchase? " << endl;
                                                cin.clear();
                                                cin >> option2;
                                                if ((player.getComputerCases() + option2) > 3)
                                                {
                                                    cout << "You can not have more than three of each computer part in your inventory." << endl;
                                                    cout << "You already have " << player.getComputerCases() << " Computer Cases." << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "The total cost for " << option2 << " Computer Cases is " << option2 * bestbuy.getComputerCaseCost() * multiplyer << " Dogecoin." << endl;
                                                    if (player.getCoinBalance() >= option2 * bestbuy.getComputerCaseCost() * multiplyer)
                                                    {
                                                        player.setComputerCases(player.getComputerCases() + option2);
                                                        player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getComputerCaseCost());
                                                        cout << "You now have " << player.getComputerCases() << " Computer Cases in your Inventory." << endl;
                                                        cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                    else
                                                    {
                                                        cout << "You don't have enough money to complete this purchase!" << endl;
                                                        cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                }
                                                break;
                                            }
                                            case 5:
                                            {
                                                system("clear");
                                                cout << "How many Internet cards would you like to purchase? " << endl;
                                                cin.clear();
                                                cin >> option2;
                                                if ((player.getInternetCards() + option2) > 3)
                                                {
                                                    cout << "You can not have more than three of each computer part in your inventory." << endl;
                                                    cout << "You already have " << player.getInternetCards() << " Internet cards." << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "The total cost for " << option2 << " Internet cards is " << option2 * bestbuy.getInternetCardCost() * multiplyer << " Dogecoin." << endl;
                                                    if (player.getCoinBalance() >= option2 * bestbuy.getInternetCardCost() * multiplyer)
                                                    {
                                                        player.setInternetCards(player.getInternetCards() + option2);
                                                        player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getInternetCardCost());
                                                        cout << "You now have " << player.getInternetCards() << " Internet cards in your Inventory." << endl;
                                                        cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                    else
                                                    {
                                                        cout << "You don't have enough money to complete this purchase!" << endl;
                                                        cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                }
                                                break;
                                            }
                                            case 6:
                                            {
                                                system("clear");
                                                cout << "How many Keyboard and mouse would you like to purchase? " << endl;
                                                cin.clear();
                                                cin >> option2;
                                                if ((player.getKeyboardAndMouse() + option2) > 3)
                                                {
                                                    cout << "You can not have more than three of each computer part in your inventory." << endl;
                                                    cout << "You already have " << player.getKeyboardAndMouse() << " Keyboard and mouse." << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "The total cost for " << option2 << " Keyboard and mouse is " << option2 * bestbuy.getKeyboardAndMouseCost() * multiplyer << " Dogecoin." << endl;
                                                    if (player.getCoinBalance() >= option2 * bestbuy.getKeyboardAndMouseCost() * multiplyer)
                                                    {
                                                        player.setKeyboardAndMouse(player.getKeyboardAndMouse() + option2);
                                                        player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getKeyboardAndMouseCost());
                                                        cout << "You now have " << player.getKeyboardAndMouse() << " Keyboard and mouse in your Inventory." << endl;
                                                        cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                    else
                                                    {
                                                        cout << "You don't have enough money to complete this purchase!" << endl;
                                                        cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                }
                                                break;
                                            }
                                            case 7:
                                            {
                                                system("clear");
                                                if ((player.getPremadeComputer()) > 1)
                                                {
                                                    cout << "You can not have more than one premade computer in your inventory." << endl;
                                                    cout << "You already have " << player.getPremadeComputer() << " premade computer." << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "The total cost for a premade computer is " << bestbuy.getPremadeComputerCost() * multiplyer << " Dogecoin." << endl;
                                                    if (player.getCoinBalance() >= bestbuy.getPremadeComputerCost() * multiplyer)
                                                    {
                                                        player.setPremadeComputer(player.getPremadeComputer() + 1);
                                                        player.setCoinBalance(player.getCoinBalance() - bestbuy.getPremadeComputerCost());
                                                        cout << "You now have " << player.getPremadeComputer() << " premade Computer in your Inventory." << endl;
                                                        cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                    else
                                                    {
                                                        cout << "You don't have enough money to complete this purchase!" << endl;
                                                        cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                        sleep(3.5);
                                                    }
                                                }
                                                break;
                                            }
                                            case 8:
                                            {
                                                system("clear");
                                                break;
                                            }
                                            default:
                                            {
                                                cout << "Please enter a valid option." << endl;
                                                sleep(1.5);
                                            }
                                            }
                                        }
                                        else // input failure: eg. the user entered a alpha character
                                        {
                                            cout << "Please enter a valid option. " << endl; // inform the user
                                            cin.clear();                                     // put the stream back into a good state
                                            cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                                            sleep(1.5);
                                        }
                                    } while (option2 != 8);
                                    break;
                                }
                                case 2:
                                {
                                    system("clear");
                                    cout << "One USB stick of antivirus software costs 10 Dogecoins and will give you a one-time use to get rid of any viruses on your computer." << endl;
                                    cout << "How many USB sticks of antivirus software would you like to buy?" << endl;
                                    if (cin >> option2)
                                    {
                                        if ((player.getAntivirusSoftware() + option2) > 3)
                                        {
                                            cout << "You can not have more than three USB sticks of antivirus software in your inventory." << endl;
                                            cout << "You already have " << player.getAntivirusSoftware() << " USB sticks of antivirus software." << endl;
                                        }
                                        else
                                        {
                                            cout << "The total cost for " << option2 << " USB sticks of antivirus software is " << option2 * bestbuy.getAntivirusSoftwareCost() * multiplyer << " Dogecoin." << endl;
                                            if (player.getCoinBalance() >= bestbuy.getVPNCost() * multiplyer)
                                            {
                                                player.setAntivirusSoftware(player.getAntivirusSoftware() + option2);
                                                player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getAntivirusSoftwareCost());
                                                cout << "You now have " << player.getAntivirusSoftware() << " USB sticks of antivirus software in your Inventory." << endl;
                                                cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                            }
                                            else
                                            {
                                                cout << "You don't have enough money to complete this purchase!" << endl;
                                                cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                sleep(3.5);
                                            }
                                        }
                                        break;
                                    }
                                    else // input failure: eg. the user entered a alpha character
                                    {
                                        cout << "Please enter a valid option. " << endl; // inform the user
                                        cin.clear();                                     // put the stream back into a good state
                                        cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                                        sleep(1.5);
                                    }
                                    break;
                                }
                                case 3:
                                {
                                    system("clear");
                                    cout << "A VPN costs 20 Dogecoins each. VPNs reduce your chances of getting hacked by preventing hackers from tracking down your main computer." << endl;
                                    cout << "The increase in security maxes out at 2 VPNs. " << endl;
                                    cout << "How many VPNs would you like to buy?" << endl;
                                    if (cin >> option2)
                                    {
                                        if ((player.getVPN() + option2) > 3)
                                        {
                                            cout << "You can not have more than three VPNs in your inventory." << endl;
                                            cout << "You already have " << player.getVPN() << " VPNs." << endl;
                                        }
                                        else
                                        {
                                            cout << "The total cost for " << option2 << " VPNs is " << option2 * bestbuy.getVPNCost() * multiplyer << " Dogecoin." << endl;
                                            if (player.getCoinBalance() >= bestbuy.getVPNCost() * multiplyer)
                                            {
                                                player.setVPN(player.getVPN() + option2);
                                                player.setCoinBalance(player.getCoinBalance() - option2 * bestbuy.getVPNCost());
                                                cout << "You now have " << player.getVPN() << " VPNs in your Inventory." << endl;
                                                cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                            }
                                            else
                                            {
                                                cout << "You don't have enough money to complete this purchase!" << endl;
                                                cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                sleep(3.5);
                                            }
                                        }
                                        break;
                                    }
                                    else // input failure: eg. the user entered a alpha character
                                    {
                                        cout << "Please enter a valid option. " << endl; // inform the user
                                        cin.clear();                                     // put the stream back into a good state
                                        cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                                        sleep(1.5);
                                    }
                                    break;
                                }
                                case 4:
                                {
                                    system("clear");
                                    cout << "Internet provider level 2 costs 10 Dogecoins. " << endl;
                                    cout << "Internet provider level 3 costs 25 Dogecoins. " << endl;
                                    cout << "Internet provider level 4 costs 40 Dogecoins. " << endl;
                                    cout << "Internet provider level 5 costs 50 Dogecoins. " << endl;
                                    cout << "What internet provider level would you like to buy? (Enter a level)" << endl;
                                    int value = 0;
                                    if (cin >> option)
                                    {
                                        if (option == 2)
                                        {
                                            value = 2;
                                            if (player.getCoinBalance() > 10 * multiplyer)
                                            {
                                                if (player.getInternetProviderLevel() < 2)
                                                {

                                                    player.setInternetProviderLevel(value);
                                                    cout << "You now have internet provider level " << player.getInternetProviderLevel() << "." << endl;
                                                    player.setCoinBalance(player.getCoinBalance() - bestbuy.getInternetProvider2Cost());
                                                    cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                }
                                                else
                                                {
                                                    cout << "You already have internet provider level " << player.getInternetProviderLevel() << "!" << endl;
                                                }
                                            }
                                            else
                                            {
                                                cout << "You don't have enough money to complete this purchase!" << endl;
                                                cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                sleep(3.5);
                                            }
                                        }
                                        else if (option == 3)
                                        {
                                            value = 3;
                                            if (player.getCoinBalance() > 25 * multiplyer)
                                            {
                                                if (player.getInternetProviderLevel() < 3)
                                                {
                                                    player.setInternetProviderLevel(value);
                                                    cout << "You now have internet provider level " << player.getInternetProviderLevel() << "." << endl;
                                                    player.setCoinBalance(player.getCoinBalance() - bestbuy.getInternetProvider3Cost());
                                                    cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                }
                                                else
                                                {
                                                    cout << "You already have internet provider level " << player.getInternetProviderLevel() << "!" << endl;
                                                }
                                            }
                                            else
                                            {
                                                cout << "You don't have enough money to complete this purchase!" << endl;
                                                cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                sleep(3.5);
                                            }
                                        }
                                        else if (option == 4)
                                        {
                                            value = 4;
                                            if (player.getCoinBalance() > 40 * multiplyer)
                                            {
                                                if (player.getInternetProviderLevel() < 4)
                                                {
                                                    player.setInternetProviderLevel(value);
                                                    cout << "You now have internet provider level " << player.getInternetProviderLevel() << "." << endl;
                                                    player.setCoinBalance(player.getCoinBalance() - bestbuy.getInternetProvider4Cost());
                                                    cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                }
                                                else
                                                {
                                                    cout << "You already have internet provider level " << player.getInternetProviderLevel() << "!" << endl;
                                                }
                                            }
                                            else
                                            {
                                                cout << "You don't have enough money to complete this purchase!" << endl;
                                                cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                sleep(3.5);
                                            }
                                        }
                                        else if (option == 5)
                                        {
                                            value = 5;
                                            if (player.getCoinBalance() > 50 * multiplyer)
                                            {
                                                if (player.getInternetProviderLevel() < 5)
                                                {
                                                    player.setInternetProviderLevel(value);
                                                    cout << "You now have internet provider level " << player.getInternetProviderLevel() << "." << endl;
                                                    player.setCoinBalance(player.getCoinBalance() - bestbuy.getInternetProvider5Cost());
                                                    cout << "Your coin balance is now " << player.getCoinBalance() << " Dogecoin" << endl;
                                                }
                                                else
                                                {
                                                    cout << "You already have internet provider level " << player.getInternetProviderLevel() << "!" << endl;
                                                }
                                            }
                                            else
                                            {
                                                cout << "You don't have enough money to complete this purchase!" << endl;
                                                cout << "Your balance is currently: " << player.getCoinBalance() << " Dogecoin" << endl;
                                                sleep(3.5);
                                            }
                                        }
                                        else
                                        {
                                            cout << "Please enter a valid internet provider level " << endl;
                                        }
                                    }
                                    else // input failure: eg. the user entered a alpha character
                                    {
                                        cout << "Please enter a valid option. " << endl; // inform the user
                                        cin.clear();                                     // put the stream back into a good state
                                        cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                                        sleep(1.5);
                                    }
                                    break;
                                }
                                case 5:
                                {
                                    break;
                                }
                                default:
                                {
                                    cout << "Please enter a valid option." << endl;
                                    sleep(1.5);
                                }
                                }
                            }
                            else // input failure: eg. the user entered a alpha character
                            {
                                cout << "Please enter a valid option. " << endl; // inform the user
                                cin.clear();                                     // put the stream back into a good state
                                cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                                sleep(1.5);
                            }
                        } while (option != 5); //repeat unless the user selects quit
                    }
                    else if (map.isHackerLocation())
                    {
                        row = map.getPlayerRowPosition(); //saving position of hacker
                        column = map.getPlayerColPosition();
                        cout << "You've encountered a Hacker!" << endl;
                        set2 = 0;
                        name = RowColName[row][column]; //setting the name to the specific location of the hacker.  If it is the players first time in that spot, the name assigned will be blank
                        //cout << RowColName[row][column] << endl;
                        if (name == "") //if its a blank string, (player vists for the first time)
                        {
                            // for (int i = 0; i < hackercount; i++)
                            // {
                            //     cout << hackers[i].getName() << endl;
                            //     cout << hackercount << endl;
                            // }
                            while (set2 == 0) //this checks to make sure that the name assigned to the spot has not been assigned to any other spots
                            {
                                int a = 0;
                                // cout << hackercount << endl;
                                //cout << RowColName[row][column] << endl;
                                for (int j = 0; j < 5; j++)
                                {
                                    for (int k = 0; k < 9; k++)
                                    {
                                        if (RowColName[row][column] == RowColName[j][k])
                                        {
                                            if (j != row)
                                            {
                                                if (k != column)
                                                {
                                                    a++;
                                                }
                                            }
                                        }
                                    }
                                }
                                if (a == 0)
                                {
                                    set2 = 1;
                                    break;
                                }
                                else //if a was incremented, then there has not been a name assigned to that spot and the name can be randomized
                                {
                                    value4 = rand() % hackercount;
                                    // cout << "the index is: " << value4 << endl;
                                    // cout << "grabbed this: " << hackers[value4].getName() << endl;
                                    RowColName[row][column] = hackers[value4].getName();
                                    name = RowColName[row][column];
                                    // cout << "stored this: " << RowColName[row][column] << endl;
                                    set2 = 0;
                                } //this will keep going until a name is assinged to this spot that hasnt been used in any other spots
                            }
                            if (set2 == 1) //once you find a name that hasn't been assigned to any other spots, then you can go through the hacker interaction
                            {
                                // int level;
                                // level = hackers[value4].getLevel();
                                int option = 0;
                                cout << "You just ran into " << name << ". Think you can beat this hacker’s skills?" << endl;
                                cout << "1. Attack" << endl;
                                cout << "2. Forefit" << endl;
                                if (cin >> option)
                                {
                                    switch (option)
                                    {
                                    case 1:
                                    {
                                        int row = map.getPlayerRowPosition();
                                        int column = map.getPlayerColPosition();
                                        int outcome = 0;
                                        srand(time(NULL));
                                        int r1 = rand() % 6 + 1;
                                        int r2 = rand() % 6 + 1;
                                        outcome = (r1 * player.getInternetProviderLevel()) - (r2 * room * (1 / player.getVPN())); //outcome for weather you win
                                        if (outcome > -1000)
                                        {
                                            cout << "You won the battle!" << endl;
                                            map.clearPosition(row, column); //clearing the position if you win the battle
                                            player.setCoinBalance(player.getCoinBalance() + 50);
                                            player.setHackersDefeated(player.getHackersDefeated() + 1); //hackers defeated will go up 1  
                                            sleep(1.5);
                                        }
                                        else
                                        {
                                            cout << "You lost the battle!" << endl;
                                            player.setComputerMaintenance(player.getComputerMaintenance() - 20);
                                            player.setCarmenProgress(player.getCarmenProgress() + 25);
                                            sleep(1.5);
                                            srand(time(NULL));
                                            int viruschance = rand() % 3 + 1; //1 in 3 chance of getting a virus
                                            if (viruschance == 1)
                                            {
                                                system("clear");
                                                cout << "Oh no!  Your computer has been infected with a virus!" << endl;
                                                cout << "Use antivirus software or your computer will lose 10 health for each virus you have each turn!" << endl;
                                                player.setViruses(player.getViruses() + 1);
                                                sleep(3);
                                            }
                                        }
                                        break;
                                    }
                                    case 2:
                                    {
                                        player.setCPUs(0);
                                        player.setGPUs(0);
                                        player.setPowerSupplyUnits(0);
                                        player.setComputerCases(0);
                                        player.setInternetCards(0);
                                        player.setKeyboardAndMouse(0);
                                        player.setPremadeComputer(0);
                                        cout << "You have lost all spare computer parts by forefitting. " << endl;
                                        sleep(1.5);
                                        break;
                                    }
                                    default:
                                    {
                                        cout << "Please enter a valid option." << endl;
                                        sleep(1.5);
                                    }
                                    }
                                }
                                else
                                {
                                    cout << "Please enter a valid option. " << endl; // inform the user
                                    cin.clear();                                     // put the stream back into a good state
                                    cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                                    sleep(1.5);
                                }
                            }
                        }
                        else
                        {
                            // for (int i = 0; i < hackercount; i++)
                            // {
                            //     cout << hackers[i].getName() << endl;
                            // }
                            //cout << "goal is: " << name << endl;
                            for (int i = 0; i < hackercount; i++)
                            {
                                //cout << hackers[i].getName() << endl;
                                if (hackers[i].getName() == name) //loop until find hacker name that has already been assigned
                                    ;
                                {
                                    //cout << name << endl;
                                    //cout << hackers[i].getName() << endl;
                                    //cout << i << endl;
                                    int option = 0;
                                    cout << "You just ran into " << name << ". Think you can beat this hacker’s skills?" << endl;
                                    cout << "1. Attack" << endl;
                                    cout << "2. Forefit" << endl;
                                    if (cin >> option)
                                    {
                                        switch (option)
                                        {
                                        case 1:
                                        {
                                            int row = map.getPlayerRowPosition();
                                            int column = map.getPlayerColPosition();
                                            int outcome = 0;
                                            srand(time(NULL));
                                            int r1 = rand() % 6 + 1;
                                            int r2 = rand() % 6 + 1;
                                            outcome = (r1 * player.getInternetProviderLevel()) - (r2 * room * (1 / player.getVPN()));
                                            if (outcome > -1000)
                                            {
                                                cout << "You won the battle!" << endl;
                                                map.clearPosition(row, column);
                                                player.setCoinBalance(player.getCoinBalance() + 50);
                                                player.setHackersDefeated(player.getHackersDefeated() + 1);
                                                sleep(1.5);
                                            }
                                            else
                                            {
                                                cout << "You lost the battle!" << endl;
                                                player.setComputerMaintenance(player.getComputerMaintenance() - 20);
                                                player.setCarmenProgress(player.getCarmenProgress() + 25);
                                                sleep(1.5);
                                                srand(time(NULL));
                                                int viruschance = rand() % 3 + 1;
                                                if (viruschance == 1)
                                                {
                                                    system("clear");
                                                    cout << "Oh no!  Your computer has been infected with a virus!" << endl;
                                                    cout << "Use antivirus software or your computer will lose 10 health for each virus you have each turn!" << endl;
                                                    player.setViruses(player.getViruses() + 1);
                                                    sleep(3);
                                                }
                                            }
                                            break;
                                        }
                                        case 2:
                                        {
                                            player.setCPUs(0);
                                            player.setGPUs(0);
                                            player.setPowerSupplyUnits(0);
                                            player.setComputerCases(0);
                                            player.setInternetCards(0);
                                            player.setKeyboardAndMouse(0);
                                            player.setPremadeComputer(0);
                                            cout << "You have lost all spare computer parts by forefitting. " << endl;
                                            sleep(1.5);
                                            break;
                                        }
                                        default:
                                        {
                                            cout << "Please enter a valid option." << endl;
                                            sleep(1.5);
                                        }
                                        }
                                    }
                                    else
                                    {
                                        cout << "Please enter a valid option. " << endl; // inform the user
                                        cin.clear();                                     // put the stream back into a good state
                                        cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                                        sleep(1.5);
                                    }
                                    break;
                                }
                            }
                        }
                        sleep(1.0);
                    }
                    else if (map.isNPCLocation())
                    {
                        system("clear");
                        cout << "You've encountered an NPC!" << endl;
                        sleep(1.5);
                        row = map.getPlayerRowPosition();
                        column = map.getPlayerColPosition();
                        map.clearPosition(row, column); // clearing npc after you land on it so that you can't exploit it
                        cout << "Would you like to complete a puzzle or take your chances?" << endl;
                        cout << "1. Puzzle   2. Take your chances" << endl;/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        int count = 0;
                        int cho = 0;
                        do {
                            cin >> cho;
                            if (cho == 1)
                            {
                                //a is defined at very top, puzzles is an array of npc/npc questions.  a advances with each npc encounter so that quesions aren't reused
                                //all randomized through npc class
                                cout << puzzles[a].getQuestion() << endl;
                                cout << puzzles[a].getAllAnswersAt(0) << endl;
                                cout << puzzles[a].getAllAnswersAt(1) << endl;
                                cout << puzzles[a].getAllAnswersAt(2) << endl;
                                cout << puzzles[a].getAllAnswersAt(3) << endl;
                                string answer;
                                cin >> answer;
                                if (answer == puzzles[a].getCorrectAnswer())
                                {
                                    system("clear");
                                    int give = rand() % 5; //random computer part to be given.  If you cant get the part, it will check if you can get the next part
                                    if (give == 0)
                                    {

                                        if (player.getCPUs() < 3) //if your inventory has enough space
                                        {
                                            player.setCPUs(player.getCPUs() + 1);
                                            cout << "Correct! The NPC gave you a CPU!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 1)
                                    {
                                        if (player.getGPUs() < 3)
                                        {
                                            player.setGPUs(player.getGPUs() + 1);
                                            cout << "Correct! The NPC gave you a GPU!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 2)
                                    {
                                        if (player.getPowerSupplyUnits() < 3)
                                        {
                                            player.setPowerSupplyUnits(player.getPowerSupplyUnits() + 1);
                                            cout << "Correct! The NPC gave you a Power Supply Unit!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 3)
                                    {
                                        if (player.getComputerCases() < 3)
                                        {
                                            player.setComputerCases(player.getComputerCases() + 1);
                                            cout << "Correct! The NPC gave you a Computer Case!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 4)
                                    {
                                        if (player.getInternetCards() < 3)
                                        {
                                            player.setInternetCards(player.getInternetCards() + 1);
                                            cout << "Correct! The NPC gave you a Internet Card!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 5)
                                    {
                                        if (player.getKeyboardAndMouse() < 3)
                                        {
                                            player.setKeyboardAndMouse(player.getKeyboardAndMouse() + 1);
                                            cout << "Correct! The NPC gave you a Keyboard and Mouse!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 6) // going through options again if give 5 is chosen.  "Clean up for give 5"
                                    {

                                        if (player.getCPUs() < 3)
                                        {
                                            player.setCPUs(player.getCPUs() + 1);
                                            cout << "Correct! The NPC gave you a CPU!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 7)
                                    {
                                        if (player.getGPUs() < 3)
                                        {
                                            player.setGPUs(player.getGPUs() + 1);
                                            cout << "Correct! The NPC gave you a GPU!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 8)
                                    {
                                        if (player.getPowerSupplyUnits() < 3)
                                        {
                                            player.setPowerSupplyUnits(player.getPowerSupplyUnits() + 1);
                                            cout << "Correct! The NPC gave you a Power Supply Unit!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 9)
                                    {
                                        if (player.getComputerCases() < 3)
                                        {
                                            player.setComputerCases(player.getComputerCases() + 1);
                                            cout << "Correct! The NPC gave you a Computer Case!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 10)
                                    {
                                        if (player.getInternetCards() < 3)
                                        {
                                            player.setInternetCards(player.getInternetCards() + 1);
                                            cout << "Correct! The NPC gave you a Internet Card!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 11)
                                    {
                                        cout << "Correct but your invetory is full and the NPC couldnt give you any computer parts!" << endl;
                                    }
                                }
                                else //if you get the quesion wrong this incrementer goes up 1.  If you get it wrong, you will be forced to take your chances
                                {
                                    system("clear");
                                    cho++;
                                    cout << "Incorrect, you will now be forced to take your chances: " << endl;
                                }
                                a++;
                            }
                            if (cho == 2) //taking your chances 
                            {
                                int chances = rand() % 3; //npc may give, take, or nothing
                                if (chances == 0)
                                {

                                    int lose = rand() % 5; // same as give, but checking that a part is availible to be taken
                                    if (lose == 0)
                                    {

                                        if (player.getCPUs() > 0)
                                        {
                                            player.setCPUs(player.getCPUs() - 1);
                                            cout << "The NPC stole a CPU from you!" << endl;
                                        }
                                        else
                                        {
                                            lose++;
                                        }
                                    }
                                    if (lose == 1)
                                    {
                                        if (player.getGPUs() > 0)
                                        {
                                            player.setGPUs(player.getGPUs() - 1);
                                            cout << "The NPC stole a GPU from you!" << endl;
                                        }
                                        else
                                        {
                                            lose++;
                                        }
                                    }
                                    if (lose == 2)
                                    {
                                        if (player.getPowerSupplyUnits() > 0)
                                        {
                                            player.setPowerSupplyUnits(player.getPowerSupplyUnits() - 1);
                                            cout << "The NPC stole a Power Supply Unit from you!" << endl;
                                        }
                                        else
                                        {
                                            lose++;
                                        }
                                    }
                                    if (lose == 3)
                                    {
                                        if (player.getComputerCases() > 0)
                                        {
                                            player.setComputerCases(player.getComputerCases() - 1);
                                            cout << "The NPC stole a Computer Case from you!" << endl;
                                        }
                                        else
                                        {
                                            lose++;
                                        }
                                    }
                                    if (lose == 4)
                                    {
                                        if (player.getInternetCards() > 0)
                                        {
                                            player.setInternetCards(player.getInternetCards() - 1);
                                            cout << "The NPC stole a Internet Card from you!" << endl;
                                        }
                                        else
                                        {
                                            lose++;
                                        }
                                    }
                                    if (lose == 5)
                                    {
                                        if (player.getKeyboardAndMouse() > 0)
                                        {
                                            player.setKeyboardAndMouse(player.getKeyboardAndMouse() - 1);
                                            cout << "The NPC stole a Keyboard and Mouse from you!" << endl;
                                        }
                                        else
                                        {
                                            lose++;
                                        }
                                    }
                                    if (lose == 6)
                                    {

                                        if (player.getCPUs() > 0)
                                        {
                                            player.setCPUs(player.getCPUs() - 1);
                                            cout << "The NPC stole a CPU from you!" << endl;
                                        }
                                        else
                                        {
                                            lose++;
                                        }
                                    }
                                    if (lose == 7)
                                    {
                                        if (player.getGPUs() > 0)
                                        {
                                            player.setGPUs(player.getGPUs() - 1);
                                            cout << "The NPC stole a GPU from you!" << endl;
                                        }
                                        else
                                        {
                                            lose++;
                                        }
                                    }
                                    if (lose == 8)
                                    {
                                        if (player.getPowerSupplyUnits() > 0)
                                        {
                                            player.setPowerSupplyUnits(player.getPowerSupplyUnits() - 1);
                                            cout << "The NPC stole a Power Supply Unit from you!" << endl;
                                        }
                                        else
                                        {
                                            lose++;
                                        }
                                    }
                                    if (lose == 9)
                                    {
                                        if (player.getComputerCases() > 0)
                                        {
                                            player.setComputerCases(player.getComputerCases() - 1);
                                            cout << "The NPC stole a Computer Case from you!" << endl;
                                        }
                                        else
                                        {
                                            lose++;
                                        }
                                    }
                                    if (lose == 10)
                                    {
                                        if (player.getInternetCards() > 0)
                                        {
                                            player.setInternetCards(player.getInternetCards() - 1);
                                            cout << "The NPC stole a Internet Card from you!" << endl;
                                        }
                                        else
                                        {
                                            lose++;
                                        }
                                    }
                                    if (lose == 11)
                                    {
                                        cout << "the NPC couldn't steal anything from you becuase you have no computer parts in your inventory." << endl;
                                    }
                                }
                                else if (chances == 1)
                                {
                                    cout << "The NPC didn't steal or give you a computer part" << endl;
                                }
                                else
                                {
                                    //same as give, npc gives a random part
                                    int give = rand() % 5;
                                    if (give == 0)
                                    {

                                        if (player.getCPUs() < 3)
                                        {
                                            player.setCPUs(player.getCPUs() + 1);
                                            cout << "The NPC gave you a CPU!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 1)
                                    {
                                        if (player.getGPUs() < 3)
                                        {
                                            player.setGPUs(player.getGPUs() + 1);
                                            cout << "The NPC gave you a GPU!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 2)
                                    {
                                        if (player.getPowerSupplyUnits() < 3)
                                        {
                                            player.setPowerSupplyUnits(player.getPowerSupplyUnits() + 1);
                                            cout << "The NPC gave you a Power Supply Unit!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 3)
                                    {
                                        if (player.getComputerCases() < 3)
                                        {
                                            player.setComputerCases(player.getComputerCases() + 1);
                                            cout << "The NPC gave you a Computer Case!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 4)
                                    {
                                        if (player.getInternetCards() < 3)
                                        {
                                            player.setInternetCards(player.getInternetCards() + 1);
                                            cout << "The NPC gave you a Internet Card!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 5)
                                    {
                                        if (player.getKeyboardAndMouse() < 3)
                                        {
                                            player.setKeyboardAndMouse(player.getKeyboardAndMouse() + 1);
                                            cout << "The NPC gave you a Keyboard and Mouse!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 6)
                                    {

                                        if (player.getCPUs() < 3)
                                        {
                                            player.setCPUs(player.getCPUs() + 1);
                                            cout << "The NPC gave you a CPU!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 7)
                                    {
                                        if (player.getGPUs() < 3)
                                        {
                                            player.setGPUs(player.getGPUs() + 1);
                                            cout << "The NPC gave you a GPU!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 8)
                                    {
                                        if (player.getPowerSupplyUnits() < 3)
                                        {
                                            player.setPowerSupplyUnits(player.getPowerSupplyUnits() + 1);
                                            cout << "The NPC gave you a Power Supply Unit!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 9)
                                    {
                                        if (player.getComputerCases() < 3)
                                        {
                                            player.setComputerCases(player.getComputerCases() + 1);
                                            cout << "The NPC gave you a Computer Case!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 10)
                                    {
                                        if (player.getInternetCards() < 3)
                                        {
                                            player.setInternetCards(player.getInternetCards() + 1);
                                            cout << "The NPC gave you a Internet Card!" << endl;
                                        }
                                        else
                                        {
                                            give++;
                                        }
                                    }
                                    if (give == 11)
                                    {
                                        cout << "Your invetory is full and the NPC couldnt give you any computer parts!" << endl;
                                    }
                                }
                            }
                            if (cho != 1 && cho != 2)
                            {
                                cout << "Invalid input, Please input a valid option." << endl;
                            }
                            sleep(4);
                        } while (cho != 1 && cho != 2);
                    }
                    else //if you are not on a hacker, npc, or bestbuy, you have a chance of misfortune
                    {
                        // map.displayMap();
                        sleep(0.5);
                        int option = 0;
                        srand(time(NULL));
                        int chanz = rand() % 20;
                        if (chanz <= 2)
                        {
                            if (chanz == 0)
                            {
                                cout << "OH NO! Your team was robbed by Carmen’s dastardly hackers!" << endl;
                                cout << "You have no computer parts/antivirus software left!" << endl;
                                player.setCPUs(0);
                                player.setGPUs(0);
                                player.setInternetCards(0);
                                player.setKeyboardAndMouse(0);
                                player.setComputerCases(0);
                                sleep(3);
                            }
                            if (chanz == 1)
                            {
                                cout << "OH NO! Your computer was damaged!" << endl;
                                player.setComputerMaintenance(player.getComputerMaintenance() - 10);
                                sleep(2);
                            }
                            if (chanz == 2)
                            {
                                cout << "OH NO! Why won’t my code work!!!!" << endl;
                                cout << "Your frustration level was increased." << endl;
                                player.setFrustration(player.getFrustration() + 10);
                                sleep(2);
                            }
                        }
                        do //this menu is displayed after each move
                        {
                            system("clear");
                            map.displayMap();
                            cout << "Select an action to do: " << endl;
                            cout << "1. Display Status \n2. Repair Computer \n3. Use antivirus software \n4. Browse StackOverflow \n5. Make your next move \n6.Quit Game(Forefit)" << endl;
                            if (cin >> option)
                            {
                                switch (option)
                                {
                                case 1: //displaying everything
                                {
                                    system("clear");
                                    player.setFrustration(player.getFrustration() + 2);
                                    cout << "Computer maintenance level: " << player.getComputerMaintenance() << endl;
                                    cout << "Computer viruses: " << player.getViruses() << endl;
                                    cout << "Computer parts: " << player.getCPUs() << " CPU(s), " << player.getGPUs() << " GPU(s), " << player.getPowerSupplyUnits() << " Power Supply Unit(s), " << player.getComputerCases() << " Computer Case(s), " << player.getInternetCards() << " Internet Card(s), " << player.getKeyboardAndMouse() << " Keyboard and Mouse, " << player.getPremadeComputer() << " extra pre-made computer." << endl;
                                    cout << "Antivirus sticks: " << player.getAntivirusSoftware() << endl;
                                    cout << "VPNs: " << player.getVPN() << endl;
                                    cout << "Internet provider level: " << player.getInternetProviderLevel() << endl;
                                    cout << "Dogecoin balance: " << player.getCoinBalance() << " Dogecoin" << endl;
                                    cout << "Frustration level (KEEP BELOW 100!): " << player.getFrustration() << endl;
                                    cout << "Carmen's progress (KEEP BELOW 100!): " << player.getCarmenProgress() << endl;
                                    cout << "Total hackers defeated: " << player.getHackersDefeated() << endl;
                                    cout << endl;
                                    cout << "Enter any key to continue." << endl;
                                    int option = 0;
                                    if (cin >> option)
                                    {
                                        if (option == 1)
                                        {
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        cout << "Please enter a key. " << endl; // inform the user
                                        cin.clear();                            // put the stream back into a good state
                                        cin.ignore(1000, '\n');                 // and remove the bad input remaining in the input buffer
                                        sleep(0.5);
                                    }
                                    break;
                                }
                                case 2: //getting total parts availible and then using them to repair
                                {
                                    int totcp = player.getCPUs() + player.getGPUs() + player.getKeyboardAndMouse() + player.getPowerSupplyUnits() + player.getComputerCases();
                                    system("clear");
                                    if (player.getComputerMaintenance() < 100)
                                    {
                                        player.setFrustration(player.getFrustration() + 2);
                                        cout << "Each computer part you use repairs your computer health by 20. " << endl;
                                        cout << "You may use a maximum of 5 computer parts to repair your computer." << endl;
                                        cout << "How many parts would you like to use to repair your computer?" << endl;
                                        int option = 0;
                                        cin.clear();
                                        if (cin >> option)
                                        {
                                            if (option <= 5 && option >= 1) //same as take in npc, random parts are taken
                                            {
                                                if (option < totcp)
                                                {

                                                    for (int i = 0; i < option; i++) //goes through how many times based on how many parts used in repairs
                                                    {
                                                        int lose = rand() % 5;
                                                        if (lose == 0)
                                                        {

                                                            if (player.getCPUs() > 0)
                                                            {
                                                                player.setCPUs(player.getCPUs() - 1);
                                                            }
                                                            else
                                                            {
                                                                lose++;
                                                            }
                                                        }
                                                        if (lose == 1)
                                                        {
                                                            if (player.getGPUs() > 0)
                                                            {
                                                                player.setGPUs(player.getGPUs() - 1);
                                                            }
                                                            else
                                                            {
                                                                lose++;
                                                            }
                                                        }
                                                        if (lose == 2)
                                                        {
                                                            if (player.getPowerSupplyUnits() > 0)
                                                            {
                                                                player.setPowerSupplyUnits(player.getPowerSupplyUnits() - 1);
                                                            }
                                                            else
                                                            {
                                                                lose++;
                                                            }
                                                        }
                                                        if (lose == 3)
                                                        {
                                                            if (player.getComputerCases() > 0)
                                                            {
                                                                player.setComputerCases(player.getComputerCases() - 1);
                                                            }
                                                            else
                                                            {
                                                                lose++;
                                                            }
                                                        }
                                                        if (lose == 4)
                                                        {
                                                            if (player.getInternetCards() > 0)
                                                            {
                                                                player.setInternetCards(player.getInternetCards() - 1);
                                                            }
                                                            else
                                                            {
                                                                lose++;
                                                            }
                                                        }
                                                        if (lose == 5)
                                                        {
                                                            if (player.getKeyboardAndMouse() > 0)
                                                            {
                                                                player.setKeyboardAndMouse(player.getKeyboardAndMouse() - 1);
                                                            }
                                                            else
                                                            {
                                                                lose++;
                                                            }
                                                        }
                                                        if (lose == 6)
                                                        {

                                                            if (player.getCPUs() > 0)
                                                            {
                                                                player.setCPUs(player.getCPUs() - 1);
                                                            }
                                                            else
                                                            {
                                                                lose++;
                                                            }
                                                        }
                                                        if (lose == 7)
                                                        {
                                                            if (player.getGPUs() > 0)
                                                            {
                                                                player.setGPUs(player.getGPUs() - 1);
                                                            }
                                                            else
                                                            {
                                                                lose++;
                                                            }
                                                        }
                                                        if (lose == 8)
                                                        {
                                                            if (player.getPowerSupplyUnits() > 0)
                                                            {
                                                                player.setPowerSupplyUnits(player.getPowerSupplyUnits() - 1);
                                                            }
                                                            else
                                                            {
                                                                lose++;
                                                            }
                                                        }
                                                        if (lose == 9)
                                                        {
                                                            if (player.getComputerCases() > 0)
                                                            {
                                                                player.setComputerCases(player.getComputerCases() - 1);
                                                            }
                                                            else
                                                            {
                                                                lose++;
                                                            }
                                                        }
                                                        if (lose == 10)
                                                        {
                                                            if (player.getInternetCards() > 0)
                                                            {
                                                                player.setInternetCards(player.getInternetCards() - 1);
                                                            }
                                                            else
                                                            {
                                                                lose++;
                                                            }
                                                        }
                                                    }
                                                    cout << "You have repaired your computer health by " << option * 20 << endl;
                                                    player.setComputerMaintenance(player.getComputerMaintenance() + option * 20);
                                                    cout << "Your computer's health is now " << player.getComputerMaintenance() << endl;
                                                    sleep(3.5);
                                                }
                                                else
                                                {
                                                    cout << "You do not have enough computer parts to repair your computer" << endl;
                                                }
                                            }
                                            else
                                            {
                                                cout << "Please enter a valid option. " << endl;
                                                sleep(1.5);
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            cout << "Please enter a key. " << endl; // inform the user
                                            cin.clear();                            // put the stream back into a good state
                                            cin.ignore(1000, '\n');                 // and remove the bad input remaining in the input buffer
                                            sleep(1.5);
                                        }
                                    }
                                    else
                                    {
                                        cout << "Your computer is already at full health!" << endl;
                                        sleep(2);
                                    }
                                    break;

                                }
                                case 3:
                                {
                                    system("clear");
                                    if (player.getViruses() > 0) //if you have a virus
                                    {
                                        if (player.getAntivirusSoftware() >= 1) //if you have software, then you can remove viruses
                                        {
                                            cout << "You have removed " << player.getViruses() << " from your computer!" << endl;
                                            player.setFrustration(player.getFrustration() + 2);
                                            player.setViruses(0);
                                        }
                                        else
                                        {
                                            cout << "You do not have any anti virus software!" << endl;
                                        }
                                    }
                                    else
                                    {
                                        cout << "Your computer is not infected with any viruses!" << endl;
                                    }
                                    break;
                                }
                                case 4:
                                {
                                    system("clear");
                                    srand(time(NULL));/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                    int computer = rand() % 3;
                                    cout << "Win a game of Rock-Paper-Scissors against the computer to reduce frostration!" << endl;
                                    cout << "Your options: (rock = r, paper = p, scissors = s)" << endl;
                                    cout << "Your choice:";
                                    int user1 = -1;
                                    do
                                    {
                                        char user;
                                        cin >> user;

                                        if (user == 'r') {
                                            user1 = 0;
                                        }
                                        else if (user == 'p') {
                                            user1 = 1;
                                        }
                                        else if (user == 's') {
                                            user1 = 2;
                                        }
                                        else {
                                            cout << "Invalid Input, Please enter a valid option." << endl;
                                        }

                                    } while (user1 != 1 && user1 != 2 && user1 != 0);
                                    string comp;
                                    if (computer == 0) {
                                        comp = "Rock";
                                    }
                                    if (computer == 1) {
                                        comp = "Paper";
                                    }
                                    if (computer == 2) {
                                        comp = "Scissors";
                                    }
                                    if (computer == user1) {
                                        cout << "The computer chose " << comp << " as well, You Tied!" << endl;
                                    }
                                    if (computer == 0 && user1 == 1) {
                                        cout << "The computer chose " << comp << ", You Won!" << endl;
                                        cout << "Your frustration went down by 10!" << endl;
                                        player.setFrustration(player.getFrustration() - 10);
                                    }
                                    if (computer == 1 && user1 == 2) {
                                        cout << "The computer chose " << comp << ", You Won!" << endl;
                                        cout << "Your frustration went down by 10!" << endl;
                                        player.setFrustration(player.getFrustration() - 10);
                                    }
                                    if (computer == 2 && user1 == 0) {
                                        cout << "The computer chose " << comp << ", You Won!" << endl;
                                        cout << "Your frustration went down by 10!" << endl;
                                        player.setFrustration(player.getFrustration() - 10);
                                    }

                                    if (computer == 2 && user1 == 1) {
                                        cout << "The computer chose " << comp << ", You Lost!" << endl;
                                        cout << "Your frustration went up by 2!" << endl;
                                        player.setFrustration(player.getFrustration() + 2);
                                    }
                                    if (computer == 1 && user1 == 0) {
                                        cout << "The computer chose " << comp << ", You Lost!" << endl;
                                        cout << "Your frustration went up by 2!" << endl;
                                        player.setFrustration(player.getFrustration() + 2);
                                    }
                                    if (computer == 0 && user1 == 2) {
                                        cout << "The computer chose " << comp << ", You Lost!" << endl;
                                        cout << "Your frustration went up by 2!" << endl;
                                        player.setFrustration(player.getFrustration() + 2);
                                    }
                                    sleep(4);


                                }
                                case 5:
                                {
                                    player.setFrustration(player.getFrustration() + 2);
                                    break;
                                }
                                case 6:
                                {
                                    quit = 1;
                                    player.playerQuit(quit); //quitting function
                                    break;
                                }
                                default:
                                    cout << "Please enter a valid option. " << endl;
                                }
                            }
                            else // input failure: eg. the user entered a alpha character
                            {
                                cout << "Please enter a valid option. " << endl; // inform the user
                                cin.clear();                                     // put the stream back into a good state
                                cin.ignore(1000, '\n');                          // and remove the bad input remaining in the input buffer
                                sleep(1.5);
                            }
                            if (player.getFrustration() < 0)
                            {
                                player.setFrustration(0);
                            }
                        } while (option != 5 && option != 6 && player.checkGameLost() != 1 && player.checkGameWin() != true); //repeat unless the user selects quit
                    }
                }
            }
        }
        if (player.checkGameLost() == 1 && player.getCarmenProgress() >= 100) //if you loose, checking how you lossed and print messages
        {
            system("clear");
            cout << "Carmen's Progress has reached 100!  You have failed to defeat her." << endl;
            return 0;
        }
        else if (player.checkGameLost() == 1 && player.getFrustration() >= 100)
        {
            system("clear");
            cout << "You have become too frustrated!  You rage quit." << endl;
            return 0;
        }
        else if (player.checkGameLost() == 1 && player.getComputerMaintenance() < 0)
        {
            system("clear");
            cout << "Your computer has been destroyed! You loose!" << endl;
            return 0;
        }
        else if (player.playerQuit(quit) == true) // if the player quits
        {
            system("clear");
            cout << "You have quit the game!" << endl;
            return 0;
        }
        else if (player.checkGameWin() == true) //if the player wins by defeating 8 hackers
        {
            system("clear");
            cout << "You have beaten 8 of Carmen's Hackers!  Carmen has now been defeated.  Great Work!" << endl;
            cout << "Input the name you want saved on the leaderboard! (without spaces)" << endl;
            string winnerName; //inputting name that will then be sorted into the leaderboard acording to the moves taken
            cin >> winnerName;
            sort(winnerName, movements);
            displayLeaderboard();
            sleep(5);
            return 0;
        }
    }
}
