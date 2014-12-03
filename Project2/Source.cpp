//Gabe Appleton, CS201
//This is the main file for the program which finds poker hand. It was designed in a way where you could use it
//for non-5-card hands (with the exception of Full House detection).


#include "Source.h"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

//It's the main, what do you expect?
int main()
{
	srand(time (NULL));
	int sz = 52;
	int *D = new int[52];
	genDeck(D,sz);
	randomize(D,sz);
	int *H = new int[5];
	for (int i = 0; i < sz/5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			H[j] = D[i*5+j];
		}
		for (int j = 0; j < 5; j++)
			cout << printCard(H[j]) << endl;
		sort(H,5);
		cout << endl << endl;
		cout << detect(H, 5);

		cout << endl << endl << endl;
	}/*
	int *A  = new int[5];
	A[0] = 6;
	A[1] = 6;
	A[2] = 6;
	A[3] = 19;
	A[4] = 19;
	cout << detect(A, 5)<< endl;
	cout << endl;*/

	
	/*for (int i = 0; i < sz; i++)
		cout << printCard(D[i]) << endl;*/

	//system ("pause");
	return 0;
}

//Detects combinations of cards using an ungodly awful if-then-else structure, which I hate
string detect(int *H, int sz)
{
	bool pair = false, three = false, four = false, full = false, two = false;
	for (int i = 0; i < sz; i++)
	{
		if (i < sz - 1)
			if (H[i] / 4 == H[i+1] / 4)
				if (i < sz - 2)
					if (H[i] / 4 == H[i+2] / 4)
						if (i < sz - 3)
							if (H[i] / 4 == H[i+3] / 4)
								four = true;
							else
								if (pair)
								{
									pair = false;
									full = true;
									i++;
								}
								else
								{
									three = true;
									i++;
								}
						else
							if (pair)
							{
								pair = false;
								full = true;
								i++;
							}
							else
							{
								three = true;
								i++;
							}
					else
						if (pair)
						{
							pair = false; 
							two = true;
						}
						else if (three)
						{
							three = false;
							full = true;
						}
						else
						{
							pair = true;
						}
				else
				{
					pair = true;
				}
	}
	full = Full(H);
	string s;
	if (four)
		s = "Four of a kind";
	else if (full)
		s = "Full House";
	else if (two)
		s = "Two Pairs";
	else if (three)
		s = "Three of a kind";
	else if (pair)
		s = "Pair";
	else
	{
		int high = H[0];
		for (int i = 1; i < sz && high / 4 != 1; i ++)
			if (H[i] / 4 == 1)
				high = H[i];
			else if (H[i] / 4 == 0)
				high = H[i];
			else
				if (H[i] / 4 > high / 4 && high / 4 != 0)
					high = H[i];
		s = "High Card: " + printCard(high);
	}
	return s;
}

//checks for a full house; the only method which cannot be used for a non-five-card hand
bool Full(int *H)
{
	if (H[0]/4 == H[1]/4 && H[0]/4 == H[2]/4 && H[3]/4 == H[4]/4)
		return true;
	else if (H[0]/4 == H[1]/4 && H[3]/4 == H[2]/4 && H[3]/4 == H[4]/4)
		return true;
	else
		return false;
}

//sorts the card in an order which the program can comprehend
void sort (int *H, int sz)
{
	for (int i = 0; i < sz; i++)
		for (int j = 0; j < i; j++)
			if (H[i] / 4 < H[j] / 4)
				swap(H,i,j,sz);
}

//shuffles the deck
void randomize (int *D, int sz)
{
	for (int i = 1; i < sz; i++)
	{
		swap(D,rand()%(i+1),i,sz);
	}
}

//swaps any two integers in an array (in this case cards)
void swap (int *D, int el1, int el2, int sz)
{
	if (el1 < sz && el2 < sz)
	{
		D[el2] = D[el1] + D[el2];
		D[el1] = D[el2] - D[el1];
		D[el2] = D[el2] - D[el1];
	}
}

//generates the initial deck before shuffling
void genDeck (int *D, int sz)
{
	for (int i = 0; i < sz; i++)
	{
		D[i] = i;
	}
}

//presents a card in a string-readable form
string printCard(int card)
{
	string a, b, c;
	if (card %4 == 0)
		b = " of Spades";
	else if (card % 4 == 1)
		b = " of Clubs";
	else if (card % 4 == 2)
		b = " of Hearts";
	else
		b = " of Diamonds";
	if (card / 4 == 0)
		a = "King";
	else if (card / 4 == 1)
		a = "Ace";
	else if (card / 4 == 11)
		a = "Jack";
	else if (card / 4 == 12)
		a = "Queen";
	else
		a = std::to_string(long long(card / 4));
	c = a + b;

	return c;
}
