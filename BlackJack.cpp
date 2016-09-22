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
bool GameOn;

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
		GameOn = true;
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
		GameOn=true;
	}

	//destructor
	~BlackJack() {
	
	}


/*
Method: SuitesAndFaces
Parameters: void
Description: initialize the three multidimensional arrays(Cards, Dealer, & Player)
Returns: void
*/
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


/*
Method: getValue
Parameters: integer unit
Description: Converts the Face of the card into its respective value(A -> 1/11, King, Queen, Jack & 10 -> 10)
Returns: integer; game value of each card
*/
	int getValue(int unit){
		if(unit==0){
			cout << "Choose a value: 11 or 1?" << endl;
			scanf("%d", &temp);
			if(temp ==1)
				return 1;
			else return 11;
		}
		else if(unit > 8)//unit 9 translates to a 10, unit 10 into Jack, etc
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


/*
Method: getFace
Parameters: integer j
Description: converts an integer(0-12) into a suit.(a value of 12 is replaced with default case)
Returns: string(Face value/name of card)
*/
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




/*
Method: update
Parameters: integer x, integer y
Description: helper method, called in DealwithIt().
Returns: void; updates the player/dealer's hand with the latest draw. 
*/
	void update(int x, int y) {
		//currPlayer =1 --> Player's turn
		//currPlayer =2 --> Dealer's turn
		if(currPlayer==1)
		{
			Player[0][P_num]=x;
			Player[1][P_num]=y;
			PlayerValue +=getValue(y);
			P_num++;
			if(PlayerValue ==21){
				GameOn = false;
				cout << "WINNER WINNER CHICKEN DINNER!" << endl;
				cout << "Player wins!" << endl;
			}
			cout << "Player has "<< getFace(y) <<" of " << getSuit(x) << endl;
			cout <<"PlayerValue: " <<PlayerValue<< "\n" << endl;
		}
		else
		{
			Dealer[0][D_num]=x;
			Dealer[1][D_num]=y;
			DealerValue +=getValue(y);
			D_num++;
			if(DealerValue == 21){
				GameOn = false;
				cout << "Dealer wins!" << endl;			
			}
			cout << "Dealer has "<< getFace(y) <<" of " << getSuit(x) << endl;
			cout <<" DealerValue: " << DealerValue << "\n"<< endl;
		}	
		totalTurn++;
		currPlayer = totalTurn % totalPlayer + 1;
	}


/*
Method: DealwithIt
Parameters: void
Description: uses RNG to generate a "random" next card. Puts that card into either Dealer/Player's hand.
Returns: void
*/

//need to add integer parameter so Player can keep hitting without hitting dealer
	void DealwithIt() {
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

//	void status(){}; //prints out the current state of the game. What cards each player currently has.


/*
Method: isThisDEnd
Parameters: 
Description: Assess the Board to see if Player/Dealer has flopped
Returns: 
*/

	void isThisDEnd()
	{
	if(PlayerValue > 21)
	{
		GameOn = false;
		cout << "Player busts! Dealer wins!" << endl;
	}
	else if(DealerValue > 21)
	{
		GameOn = false;
		cout << "Dealer busts! Player wins!" << endl;
	}
	else
		GameOn = true;
	}

/*
Method: soWhoWins
Parameters:
Description:
Returns:
*/
	void soWhoWins()
	{
		cout << "Entered soWhoWins: " << endl;
		if(PlayerValue > DealerValue)	//Player must beat the dealer to win
			cout << "Player wins!" << endl;
		else
			cout << "Dealer wins!" << endl;
	}



};


int main(void) {

BlackJack bj(2);	//initialize object
srand(time(NULL));
for(int j=0; j<4; j++)	//deal 4 cards total(2 per player)
	bj.DealwithIt();
//ASK PLAYER IF YOU WANT TO HIT
int hit;

if(bj.GameOn == true)
{
	printf("Hit? Type 1 for 'yes' or anything else for 'no': ");
	scanf("%d", &hit);
	while(bj.GameOn == true && hit ==1)
	{
		bj.DealwithIt();
		bj.isThisDEnd();
		//cout << "GAME ON: " << bj.GameOn<< endl;
		if(bj.GameOn==true)
		{
			printf("Hit? Type 1 for 'yes' or anything else for 'no': ");
			scanf("%d", &hit);
		}
	}
	//if user stopped hitting before game is over
	if(bj.GameOn == true)
	{
		bj.soWhoWins();
	}
}


}



