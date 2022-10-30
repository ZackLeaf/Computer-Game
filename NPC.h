// CS1300 Fall 2021
// Author: Zack Leaf and Nathanael Lee
// Recitation: 212 - Nikhith Sannidhi (Zack) 213 - Jerome Gammie (Nathanael)
// Project 3
#ifndef NPC_H
#define NPC_H

#include <fstream>
#include <iostream>
#include <ctype.h>

using namespace std;

class NPC
{//int cq, string questions, string allAnswers[], string correctAnswer


private:
  int numQuestionsStored = 10;
  int current;
  string question;
  string allAnswers[10];
  string correctAnswer;

  int pastQuestions[10];
  int sim = 0;

public:
  NPC();
  NPC(int current, string question, string allAnswers[10], string correctAnswer);
  void setcq(int);
  void setQuestion(string);
  void setAllAnswers(int, string);
  void setCorrectAnswer(string);
  int getcq();
  string getQuestion();
  string getAllAnswersAt(int);
  string getCorrectAnswer();
  void fillPuzzles(NPC puzzles[]);
  void stealGive();

};

#endif