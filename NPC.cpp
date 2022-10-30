#include "NPC.h"
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
using namespace std;

NPC::NPC()
{
    int sim = 0;
    int numQuestionsStored = 10;
}

NPC::NPC(int cq, string initialQuestion, string allInitialAnswers[], string initialCorrectAnswer)
{
    current = cq;
    question = initialQuestion;
    for (int i = 0; i < 4; i++)
    {
        allAnswers[i] = allInitialAnswers[i]; //this goes trhough the array inside of the array, it is currently set to the]
    }
    correctAnswer = initialCorrectAnswer;// to a max of 5 answers but it could be easily changed
}
void NPC::setcq(int c)
{
    current = c;
}
void NPC::setQuestion(string q){
question=q;
}
void NPC::setAllAnswers(int p, string a){
    allAnswers[p]=a;  //same as Listener.cpp, you have to give array index as well as the input string
}
void NPC::setCorrectAnswer(string c){
    correctAnswer=c;
}
int NPC::getcq(){
return current;
}
string NPC::getQuestion(){
return question;
}
string NPC::getAllAnswersAt(int q){
return allAnswers[q];//you have to give array index same as Listener.cpp,
}
string NPC::getCorrectAnswer(){
return correctAnswer;
}
void NPC::fillPuzzles(NPC puzzles[]){
    srand(time(NULL));
    int first= rand() % 10; //this randomizes the order of the ten questions.
    if (first==0){
        string answers[]={"1.World Web Window","2.World Wide Web","3.Window Wide Web", "4.West Web Window"};
        string answers1[]={"1.Fear of Lizards","2.Fear of Other Peoples Anger","3.Fear of Dogs", "4.Fear of Toilet Paper"};
        string empty[]={"","","",""};
        string answers2[]={"1.Six","2.Ten","3.Twelve", "4.Sixteen"};
        string answers3[]={"1.Atlantic","2.Artic","3.Indian", "4.Pacific"};
        string answers4[]={"1.blue","2.yellow","3.brown", "4.green"};
        string answers5[]={"1.Switzerland","2.Germany","3.United States", "4.Saudi Arabia"};
        string answers6[]={"1.Dr. Pepper","2.Coca-Cola","3.Pepsi", "4.Sprite"};
        string answers7[]={"1.Honey","2.Cotton Candy","3.Peanut Butter", "4.Soup"};
        string answers8[]={"1.Italy","2.England","3.Germany", "4.China"};
puzzles[0]=NPC(0,"What does the www stand for in web browsers?",answers, "2");
puzzles[1]=NPC(1,"What geometric shape is used on Yield signs? (write answer in all lower case)",empty, "triangle");
puzzles[2]=NPC(2, "What is Cynophobia?",answers1, "3");
puzzles[3]=NPC(3, "How may languages are written from right to left?",answers2, "3");
puzzles[4]=NPC(4, "What is the name of the largest ocean on earth?",answers3, "4");
puzzles[5]=NPC(5, "What is the rarest M&M color?",answers4, "3");
puzzles[6]=NPC(6, "Which country consumes the most chocolate per capita?",answers5, "1");
puzzles[7]=NPC(7, "What was the first soft drink in Space?",answers6, "2");
puzzles[8]=NPC(8, "Which is the only edible food that never goes bad?",answers7, "1");
puzzles[9]=NPC(9, "Which Country invented Ice cream?",answers8, "4");


    }
    if (first==1){
string answers[]={"1.World Web Window","2.World Wide Web","3.Window Wide Web"};
        string answers1[]={"1.Fear of Lizards","2.Fear of Other Peoples Anger","3.Fear of Dogs", "4.Fear of Toilet Paper"};
        string empty[]={""};
        string answers2[]={"1.Six","2.Ten","3.Twelve", "4.Sixteen"};
        string answers3[]={"1.Atlantic","2.Artic","3.Indian", "4.Pacific"};
        string answers4[]={"1.blue","2.yellow","3.brown", "4.green"};
        string answers5[]={"1.Switzerland","2.Germany","3.United States", "4.Saudi Arabia"};
        string answers6[]={"1.Dr. Pepper","2.Coca-Cola","3.Pepsi", "4.Sprite"};
        string answers7[]={"1.Honey","2.Cotton Candy","3.Peanut Butter", "4.Soup"};
        string answers8[]={"1.Italy","2.England","3.Germany", "4.China"};
puzzles[3]=NPC(3,"What does the www stand for in web browsers?",answers, "2");
puzzles[5]=NPC(5,"What geometric shape is used on Yield signs? (write answer in all lower case)",empty, "triangle");
puzzles[1]=NPC(1, "What is Cynophobia?",answers1, "3");
puzzles[2]=NPC(2, "How may languages are written from right to left?",answers2, "3");
puzzles[4]=NPC(4, "What is the name of the largest ocean on earth?",answers3, "4");
puzzles[8]=NPC(8, "What is the rarest M&M color?",answers4, "3");
puzzles[6]=NPC(6, "Which country consumes the most chocolate per capita?",answers5, "1");
puzzles[7]=NPC(7, "What was the first soft drink in Space?",answers6, "2");
puzzles[0]=NPC(0, "Which is the only edible food that never goes bad?",answers7, "1");
puzzles[9]=NPC(9, "Which Country invented Ice cream?",answers8, "4");


    }
    if (first==2){
string answers[]={"1.World Web Window","2.World Wide Web","3.Window Wide Web"};
        string answers1[]={"1.Fear of Lizards","2.Fear of Other Peoples Anger","3.Fear of Dogs", "4.Fear of Toilet Paper"};
        string empty[]={""};
        string answers2[]={"1.Six","2.Ten","3.Twelve", "4.Sixteen"};
        string answers3[]={"1.Atlantic","2.Artic","3.Indian", "4.Pacific"};
        string answers4[]={"1.blue","2.yellow","3.brown", "4.green"};
        string answers5[]={"1.Switzerland","2.Germany","3.United States", "4.Saudi Arabia"};
        string answers6[]={"1.Dr. Pepper","2.Coca-Cola","3.Pepsi", "4.Sprite"};
        string answers7[]={"1.Honey","2.Cotton Candy","3.Peanut Butter", "4.Soup"};
        string answers8[]={"1.Italy","2.England","3.Germany", "4.China"};
puzzles[9]=NPC(9,"What does the www stand for in web browsers?",answers, "2");
puzzles[8]=NPC(8,"What geometric shape is used on Yield signs? (write answer in all lower case)",empty, "triangle");
puzzles[6]=NPC(6, "What is Cynophobia?",answers1, "3");
puzzles[7]=NPC(7, "How may languages are written from right to left?",answers2, "3");
puzzles[5]=NPC(5, "What is the name of the largest ocean on earth?",answers3, "4");
puzzles[4]=NPC(4, "What is the rarest M&M color?",answers4, "3");
puzzles[2]=NPC(2, "Which country consumes the most chocolate per capita?",answers5, "1");
puzzles[3]=NPC(3, "What was the first soft drink in Space?",answers6, "2");
puzzles[1]=NPC(1, "Which is the only edible food that never goes bad?",answers7, "1");
puzzles[0]=NPC(0, "Which Country invented Ice cream?",answers8, "4");


    }
    if (first==3){
string answers[]={"1.World Web Window","2.World Wide Web","3.Window Wide Web"};
        string answers1[]={"1.Fear of Lizards","2.Fear of Other Peoples Anger","3.Fear of Dogs", "4.Fear of Toilet Paper"};
        string empty[]={""};
        string answers2[]={"1.Six","2.Ten","3.Twelve", "4.Sixteen"};
        string answers3[]={"1.Atlantic","2.Artic","3.Indian", "4.Pacific"};
        string answers4[]={"1.blue","2.yellow","3.brown", "4.green"};
        string answers5[]={"1.Switzerland","2.Germany","3.United States", "4.Saudi Arabia"};
        string answers6[]={"1.Dr. Pepper","2.Coca-Cola","3.Pepsi", "4.Sprite"};
        string answers7[]={"1.Honey","2.Cotton Candy","3.Peanut Butter", "4.Soup"};
        string answers8[]={"1.Italy","2.England","3.Germany", "4.China"};
puzzles[5]=NPC(5,"What does the www stand for in web browsers?",answers, "2");
puzzles[8]=NPC(8,"What geometric shape is used on Yield signs? (write answer in all lower case)",empty, "triangle");
puzzles[3]=NPC(3, "What is Cynophobia?",answers1, "3");
puzzles[7]=NPC(7, "How may languages are written from right to left?",answers2, "3");
puzzles[0]=NPC(0, "What is the name of the largest ocean on earth?",answers3, "4");
puzzles[1]=NPC(1, "What is the rarest M&M color?",answers4, "3");
puzzles[4]=NPC(4, "Which country consumes the most chocolate per capita?",answers5, "1");
puzzles[2]=NPC(2, "What was the first soft drink in Space?",answers6, "2");
puzzles[6]=NPC(6, "Which is the only edible food that never goes bad?",answers7, "1");
puzzles[9]=NPC(9, "Which Country invented Ice cream?",answers8, "4");


    }
    if (first==4){
string answers[]={"1.World Web Window","2.World Wide Web","3.Window Wide Web"};
        string answers1[]={"1.Fear of Lizards","2.Fear of Other Peoples Anger","3.Fear of Dogs", "4.Fear of Toilet Paper"};
        string empty[]={""};
        string answers2[]={"1.Six","2.Ten","3.Twelve", "4.Sixteen"};
        string answers3[]={"1.Atlantic","2.Artic","3.Indian", "4.Pacific"};
        string answers4[]={"1.blue","2.yellow","3.brown", "4.green"};
        string answers5[]={"1.Switzerland","2.Germany","3.United States", "4.Saudi Arabia"};
        string answers6[]={"1.Dr. Pepper","2.Coca-Cola","3.Pepsi", "4.Sprite"};
        string answers7[]={"1.Honey","2.Cotton Candy","3.Peanut Butter", "4.Soup"};
        string answers8[]={"1.Italy","2.England","3.Germany", "4.China"};
puzzles[4]=NPC(4,"What does the www stand for in web browsers?",answers, "2");
puzzles[6]=NPC(6,"What geometric shape is used on Yield signs? (write answer in all lower case)",empty, "triangle");
puzzles[8]=NPC(8, "What is Cynophobia?",answers1, "3");
puzzles[2]=NPC(2, "How may languages are written from right to left?",answers2, "3");
puzzles[0]=NPC(0, "What is the name of the largest ocean on earth?",answers3, "4");
puzzles[1]=NPC(1, "What is the rarest M&M color?",answers4, "3");
puzzles[3]=NPC(3, "Which country consumes the most chocolate per capita?",answers5, "1");
puzzles[7]=NPC(7, "What was the first soft drink in Space?",answers6, "2");
puzzles[5]=NPC(5, "Which is the only edible food that never goes bad?",answers7, "1");
puzzles[9]=NPC(9, "Which Country invented Ice cream?",answers8, "4");


    }
    if (first==5){
string answers[]={"1.World Web Window","2.World Wide Web","3.Window Wide Web"};
        string answers1[]={"1.Fear of Lizards","2.Fear of Other Peoples Anger","3.Fear of Dogs", "4.Fear of Toilet Paper"};
        string empty[]={""};
        string answers2[]={"1.Six","2.Ten","3.Twelve", "4.Sixteen"};
        string answers3[]={"1.Atlantic","2.Artic","3.Indian", "4.Pacific"};
        string answers4[]={"1.blue","2.yellow","3.brown", "4.green"};
        string answers5[]={"1.Switzerland","2.Germany","3.United States", "4.Saudi Arabia"};
        string answers6[]={"1.Dr. Pepper","2.Coca-Cola","3.Pepsi", "4.Sprite"};
        string answers7[]={"1.Honey","2.Cotton Candy","3.Peanut Butter", "4.Soup"};
        string answers8[]={"1.Italy","2.England","3.Germany", "4.China"};
puzzles[2]=NPC(2,"What does the www stand for in web browsers?",answers, "2");
puzzles[5]=NPC(5,"What geometric shape is used on Yield signs? (write answer in all lower case)",empty, "triangle");
puzzles[8]=NPC(8, "What is Cynophobia?",answers1, "3");
puzzles[1]=NPC(1, "How may languages are written from right to left?",answers2, "3");
puzzles[4]=NPC(4, "What is the name of the largest ocean on earth?",answers3, "4");
puzzles[7]=NPC(7, "What is the rarest M&M color?",answers4, "3");
puzzles[0]=NPC(0, "Which country consumes the most chocolate per capita?",answers5, "1");
puzzles[3]=NPC(3, "What was the first soft drink in Space?",answers6, "2");
puzzles[6]=NPC(6, "Which is the only edible food that never goes bad?",answers7, "1");
puzzles[9]=NPC(9, "Which Country invented Ice cream?",answers8, "4");


    }
    if (first==6){
string answers[]={"1.World Web Window","2.World Wide Web","3.Window Wide Web"};
        string answers1[]={"1.Fear of Lizards","2.Fear of Other Peoples Anger","3.Fear of Dogs", "4.Fear of Toilet Paper"};
        string empty[]={""};
        string answers2[]={"1.Six","2.Ten","3.Twelve", "4.Sixteen"};
        string answers3[]={"1.Atlantic","2.Artic","3.Indian", "4.Pacific"};
        string answers4[]={"1.blue","2.yellow","3.brown", "4.green"};
        string answers5[]={"1.Switzerland","2.Germany","3.United States", "4.Saudi Arabia"};
        string answers6[]={"1.Dr. Pepper","2.Coca-Cola","3.Pepsi", "4.Sprite"};
        string answers7[]={"1.Honey","2.Cotton Candy","3.Peanut Butter", "4.Soup"};
        string answers8[]={"1.Italy","2.England","3.Germany", "4.China"};
puzzles[6]=NPC(6,"What does the www stand for in web browsers?",answers, "2");
puzzles[5]=NPC(5,"What geometric shape is used on Yield signs? (write answer in all lower case)",empty, "triangle");
puzzles[7]=NPC(7, "What is Cynophobia?",answers1, "3");
puzzles[4]=NPC(4, "How may languages are written from right to left?",answers2, "3");
puzzles[8]=NPC(8, "What is the name of the largest ocean on earth?",answers3, "4");
puzzles[3]=NPC(3, "What is the rarest M&M color?",answers4, "3");
puzzles[9]=NPC(9, "Which country consumes the most chocolate per capita?",answers5, "1");
puzzles[0]=NPC(0, "What was the first soft drink in Space?",answers6, "2");
puzzles[1]=NPC(1, "Which is the only edible food that never goes bad?",answers7, "1");
puzzles[2]=NPC(2, "Which Country invented Ice cream?",answers8, "4");
    }
    if (first==7){
string answers[]={"1.World Web Window","2.World Wide Web","3.Window Wide Web"};
        string answers1[]={"1.Fear of Lizards","2.Fear of Other Peoples Anger","3.Fear of Dogs", "4.Fear of Toilet Paper"};
        string empty[]={""};
        string answers2[]={"1.Six","2.Ten","3.Twelve", "4.Sixteen"};
        string answers3[]={"1.Atlantic","2.Artic","3.Indian", "4.Pacific"};
        string answers4[]={"1.blue","2.yellow","3.brown", "4.green"};
        string answers5[]={"1.Switzerland","2.Germany","3.United States", "4.Saudi Arabia"};
        string answers6[]={"1.Dr. Pepper","2.Coca-Cola","3.Pepsi", "4.Sprite"};
        string answers7[]={"1.Honey","2.Cotton Candy","3.Peanut Butter", "4.Soup"};
        string answers8[]={"1.Italy","2.England","3.Germany", "4.China"};
puzzles[9]=NPC(9,"What does the www stand for in web browsers?",answers, "2");
puzzles[1]=NPC(1,"What geometric shape is used on Yield signs? (write answer in all lower case)",empty, "triangle");
puzzles[8]=NPC(8, "What is Cynophobia?",answers1, "3");
puzzles[2]=NPC(2, "How may languages are written from right to left?",answers2, "3");
puzzles[7]=NPC(7, "What is the name of the largest ocean on earth?",answers3, "4");
puzzles[3]=NPC(3, "What is the rarest M&M color?",answers4, "3");
puzzles[6]=NPC(6, "Which country consumes the most chocolate per capita?",answers5, "1");
puzzles[4]=NPC(4, "What was the first soft drink in Space?",answers6, "2");
puzzles[5]=NPC(5, "Which is the only edible food that never goes bad?",answers7, "1");
puzzles[0]=NPC(0, "Which Country invented Ice cream?",answers8, "4");
    }
    if (first==8){
string answers[]={"1.World Web Window","2.World Wide Web","3.Window Wide Web"};
        string answers1[]={"1.Fear of Lizards","2.Fear of Other Peoples Anger","3.Fear of Dogs", "4.Fear of Toilet Paper"};
        string empty[]={""};
        string answers2[]={"1.Six","2.Ten","3.Twelve", "4.Sixteen"};
        string answers3[]={"1.Atlantic","2.Artic","3.Indian", "4.Pacific"};
        string answers4[]={"1.blue","2.yellow","3.brown", "4.green"};
        string answers5[]={"1.Switzerland","2.Germany","3.United States", "4.Saudi Arabia"};
        string answers6[]={"1.Dr. Pepper","2.Coca-Cola","3.Pepsi", "4.Sprite"};
        string answers7[]={"1.Honey","2.Cotton Candy","3.Peanut Butter", "4.Soup"};
        string answers8[]={"1.Italy","2.England","3.Germany", "4.China"};
puzzles[2]=NPC(2,"What does the www stand for in web browsers?",answers, "2");
puzzles[3]=NPC(3,"What geometric shape is used on Yield signs? (write answer in all lower case)",empty, "triangle");
puzzles[5]=NPC(5, "What is Cynophobia?",answers1, "3");
puzzles[6]=NPC(6, "How may languages are written from right to left?",answers2, "3");
puzzles[8]=NPC(8, "What is the name of the largest ocean on earth?",answers3, "4");
puzzles[0]=NPC(0, "What is the rarest M&M color?",answers4, "3");
puzzles[1]=NPC(1, "Which country consumes the most chocolate per capita?",answers5, "1");
puzzles[4]=NPC(4, "What was the first soft drink in Space?",answers6, "2");
puzzles[9]=NPC(9, "Which is the only edible food that never goes bad?",answers7, "1");
puzzles[7]=NPC(7, "Which Country invented Ice cream?",answers8, "4");
    }
    if (first==9){
string answers[]={"1.World Web Window","2.World Wide Web","3.Window Wide Web"};
        string answers1[]={"1.Fear of Lizards","2.Fear of Other Peoples Anger","3.Fear of Dogs", "4.Fear of Toilet Paper"};
        string empty[]={""};
        string answers2[]={"1.Six","2.Ten","3.Twelve", "4.Sixteen"};
        string answers3[]={"1.Atlantic","2.Artic","3.Indian", "4.Pacific"};
        string answers4[]={"1.blue","2.yellow","3.brown", "4.green"};
        string answers5[]={"1.Switzerland","2.Germany","3.United States", "4.Saudi Arabia"};
        string answers6[]={"1.Dr. Pepper","2.Coca-Cola","3.Pepsi", "4.Sprite"};
        string answers7[]={"1.Honey","2.Cotton Candy","3.Peanut Butter", "4.Soup"};
        string answers8[]={"1.Italy","2.England","3.Germany", "4.China"};
puzzles[3]=NPC(3,"What does the www stand for in web browsers?",answers, "2");
puzzles[1]=NPC(1,"What geometric shape is used on Yield signs? (write answer in all lower case)",empty, "triangle");
puzzles[2]=NPC(2, "What is Cynophobia?",answers1, "3");
puzzles[4]=NPC(4, "How may languages are written from right to left?",answers2, "3");
puzzles[6]=NPC(6, "What is the name of the largest ocean on earth?",answers3, "4");
puzzles[9]=NPC(9, "What is the rarest M&M color?",answers4, "3");
puzzles[7]=NPC(7, "Which country consumes the most chocolate per capita?",answers5, "1");
puzzles[5]=NPC(5, "What was the first soft drink in Space?",answers6, "2");
puzzles[8]=NPC(8, "Which is the only edible food that never goes bad?",answers7, "1");
puzzles[0]=NPC(0, "Which Country invented Ice cream?",answers8, "4");
    }

}
/*void NPC::stealGive(){
     int chances = rand() % 3;
                    if (chances == 0)
                    {
                        cout << "The NPC stole a ";
                        int lose = rand() % 5;
                        if (lose == 0)
                        {
                            
                            if (player.getCPUs() > 0)
                            {
                                player.setCPUs(player.getCPUs() - 1);
                                cout << "CPU from you!" << endl;
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
                                cout << "GPU from you!" << endl;
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
                                cout << "Power Supply Unit from you!" << endl;
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
                                cout << "Computer Case from you!" << endl;
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
                                cout << "Internet Card from you!" << endl;
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
                                cout << "Keyboard and Mouse from you!" << endl;
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
                                cout << "CPU from you!" << endl;
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
                                cout << "GPU from you!" << endl;
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
                                cout << "Power Supply Unit from you!" << endl;
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
                                cout << "Computer Case from you!" << endl;
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
                                cout << "Internet Card from you!" << endl;
                            }
                            else
                            {
                                lose++;
                            }
                        }
                        if(lose == 11){
                           cout<< "the NPC couldn't steal anything from you becuase you have no computer parts in your inventory."<<endl;
                        }
                    }
                    else if (chances==1){
                        cout<<"The NPC didn't steal or give you a computer part"<<endl;
                    }
                    else {
                             cout << "The NPC gave you a ";
                        int give = rand() % 5;
                        if (give == 0)
                        {
                            
                            if (player.getCPUs() < 3)
                            {
                                player.setCPUs(player.getCPUs() + 1);
                                cout << "CPU!" << endl;
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
                                cout << "GPU!" << endl;
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
                                cout << "Power Supply Unit!" << endl;
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
                                cout << "Computer Case!" << endl;
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
                                cout << "Internet Card!" << endl;
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
                                cout << "Keyboard and Mouse!" << endl;
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
                                cout << "CPU!" << endl;
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
                                cout << "GPU!" << endl;
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
                                cout << "Power Supply Unit!" << endl;
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
                                cout << "Computer Case!" << endl;
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
                                cout << "Internet Card!" << endl;
                            }
                            else
                            {
                                give++;
                            }
                        }
                        if (give == 11){
                            cout<<"Your invetory is full and the NPC couldnt give you any computer parts!"<<endl;
                        }
}
*/
