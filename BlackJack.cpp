#include <stdio.h>
#include <iostream>
#include <time.h>
#include <ctime>
#include <cstdlib>
//written by Jay Lim
//Date: 9/11/16
//initiate project
//implement a probability of busting on next draw

using namespace std;

//struct Cards(int x, int y){}
struct Hand{
string name;
int handValue;
int *cards
//constructor
	Hand(int i, string playerName){
	name = playerName;
	handValue=0;
	cards=NULL;
	}
//add to the hand

cards = &Cards[3][3];

}

class BlackJack {
public:



//initialize an array of pointers to Cards[][]
//Cards[][] PlayerV[];
int Suite, Face, totalTurn, totalPlayer, x, y, currPlayer;
//bool changePlayer; //multiplayer if yes, singleplayer if no
int Cards[4][13];

	//default constructor. Creates a two player game 
	BlackJack() {
		SuitesAndFaces();
		totalTurn= 0;
		totalPlayer=2;
		currPlayer=totalTurn % totalPlayer + 1;
		//Cards[][] *PlayerV[2];
	}


	//user inputs the number of players in the game
	BlackJack(int num_Players) {
		SuitesAndFaces();
		totalTurn=0;
		totalPlayer= num_Players;
		currPlayer=totalTurn % totalPlayer + 1;
	}

	//destructor
	~BlackJack() {
	
	}
	
//used to initialize Cards[][]
	void SuitesAndFaces() {
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				Cards[i][j] = 0;
			}
		}
	}

//helper function, called in DealwithIt()
	void changePlayer() {
		totalTurn++;
		currPlayer = totalTurn % totalPlayer + 1;
	}


//Deals cards
	void DealwithIt() {
		//srand(time(NULL));

		x = rand() % 4;
		y = rand() % 13;

		//use srand and rng to get a random x and y
		if (Cards[x][y] == 0)
		{
			Cards[x][y] = currPlayer;
			changePlayer();
			cout <<"x is: " << x << " and y is: "<< y << endl;
		}
		else {
			cout << "not this one.... x is: " << x << " and y is: " << y << endl;
			DealwithIt();
		}
	}

};

int main(void) {
	int num;
	cout<< "Enter Number of Players: ";
	scanf("%d", &num);
	BlackJack bj (num);
	srand(time(NULL));
	for(int i=0; i<num*2; i++)
		bj.DealwithIt();


}
