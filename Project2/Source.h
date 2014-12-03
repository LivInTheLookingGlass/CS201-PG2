//Header file for prototyping non-sense


#ifndef _HEAD_
#define _HEAD_
#include <string>
using namespace std;

int main();
void swap (int *D, int el1, int el2, int sz);
void genDeck(int *D, int sz);
void randomize (int *D, int sz);
string printCard(int card);
void sort (int *H, int sz);
string detect(int *H, int sz);
bool Full(int *H);

#endif
