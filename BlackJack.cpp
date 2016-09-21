#include <stdio.h>
#include <iostream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <string>
//written by Jay Lim
//Start Date: 9/11/16
//implement a probability of busting on next draw

using namespace std;

class BlackJack {
public:

//the maxiumum number of cards one can hold without busting is 11
int Dealer[2][11];
int Player[2][11];

//initialize an array of pointers to Cards[][]
int Suite, Face, totalTurn, totalPlayer, value, x, y, currPlayer;
int PlayerValue, DealerValue;
int temp;
int P_num, D_num;
int Cards[4][13];

	//default constructor. Creates a two player game 
	BlackJack() {		
		SuitesAndFaces();
		totalTurn= 0;
		totalPlayer=2;
		currPlayer=totalTurn % totalPlayer + 1;
		PlayerValue = 0;
		DealerValue = 0;
		P_num =0;
		D_num=0;
	}


	//user inputs the number of players in the game
	BlackJack(int num_Players) {
		SuitesAndFaces();
		totalTurn=0;
		totalPlayer= num_Players;
		currPlayer=totalTurn % totalPlayer + 1;
		PlayerValue = 0;
		DealerValue=0;
		P_num=0;
		D_num=0;
	}

	//destructor
	~BlackJack() {
	
	}
	
//used to initialize Cards, Dealer, and Player
	void SuitesAndFaces() {
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				Cards[i][j]=0;
			}
		}
		for(int x=0; x<2; x++){
			for(y=0; y<11; y++){
				Dealer[x][y]=0;
				Player[x][y]=0;
			}
		}
	}

	int getValue(int unit){
		if(unit==0){
			cout << "Choose a value: 11 or 1?" << endl;
			scanf("%d", &temp);
			if(temp ==1)
				return 1;
			else return 11;
		}
		else if(unit > 8)
			return 10;
		else return unit+1;
	}

/*
Method: getSuit
Parameters: integer i
Description: converts an integer(0-3) into a suit.
Returns: string (one of four suite)
*/
	string getSuit(int i){
		if(i==0)
			return "Spades";
		else if (i==1)
			return "Hearts";
		else if (i==2)
			return "Spades";
		else return "Diamonds";
	}

	string getFace(int j){
		switch(j){
			case 0:
				return "Ace";
				break;
			case 1: 
				return "2";
				break;
			case 2:
				return "3";
				break;
			case 3:
				return "4";
				break;
			case 4:
				return "5";
				break;
			case 5:
				return "6";
				break;
			case 6:
				return "7";
				break;
			case 7:
				return "8";
				break;
			case 8:
				return "9";
				break;
			case 9:
				return "10";
				break;
			case 10:
				return "Jack";
				break;
			case 11:
				return "Queen";
				break;
			default:
				return "King";
				break;
		}
	}



//helper function, called in DealwithIt()
	void update(int x, int y) {
		//currPlayer =1 --> Player's turn
		//currPlayer =2 --> Dealer's turn
		if(currPlayer==1)
		{
			Player[0][P_num]=x;
			Player[1][P_num]=y;
			PlayerValue +=getValue(y);
			P_num++;
			cout << "Player has "<< getFace(y) <<" of " << getSuit(x) << endl;
			cout <<"PlayerValue: " <<PlayerValue<< "\n" << endl;
		}
		else
		{
			Dealer[0][D_num]=x;
			Dealer[1][D_num]=y;
			DealerValue +=getValue(y);
			D_num++;
			cout << "Dealer has "<< getFace(y) <<" of " << getSuit(x) << endl;
			cout << "D_num: " << D_num <<" DealerValue: " << DealerValue << "\n"<< endl;
		}	
		totalTurn++;
		currPlayer = totalTurn % totalPlayer + 1;
	}


//Deals cards
	void DealwithIt() {
//		srand(time(NULL));
		value = rand() % 52;
		x = value/13;
		y = value%13;

		//use srand and rng to get a random x and y
		if (Cards[x][y] == 0)
		{
			Cards[x][y] = currPlayer;
			cout <<"x is: " << x << " and y is: "<< y << endl;			
			update(x,y);
		}
		else {
			cout << "not this one.... x is: " << x << " and y is: " << y << endl;
			DealwithIt();
		}
	}

	void status(){}; //prints out the current state of the game. What cards each player currently has.

};

int main(void) {
//	int num;
//	cout<< "Enter Number of Players(2-4): ";
//	scanf("%d", &num);
	BlackJack bj (2);

/*
	for(int i =0; i< 4; i++)
	{
		for(int j=0; j<13; j++)
		{
			cout << bj.Cards[i][j] << endl;
		}
	}

*/

//	for(int i=0; i< 2; i++)
//	{
//		for(int j=0; j<11 ; j++)
//			cout << bj.Player[i][j] << endl;
//
//	}


	srand(time(NULL));
//	if(num > 1 && num < 5){
//		for(int i=0; i<num*2; i++)
//			bj.DealwithIt();
//	}
//	else {
//		cout << "Invalid number of players! Preparing game for two." << endl;
		for(int j=0; j< 4; j++)
			bj.DealwithIt();
//	}
	
	

	//ASK IF YOU WANT TO HIT
}



