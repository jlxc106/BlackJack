#include <stdio.h>
#include <iostream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <unistd.h>

//written by Jay Lim
//Last Edited: 10/06/16
//Simple one player blackjack game(against dealer)
//Last Edit: clean global variables & make code reader-friendly
//To Do: implement a multiplayer option & GUI

using namespace std;

class BlackJack {
public:

//the maxiumum number of cards one can hold without busting is 11
int Dealer[2][11];	//dealer's hand
int Player[2][11];	//player's hand

int Suite, Face, totalTurn, totalPlayer, value;
int PlayerValue, DealerValue;
int P_num, D_num;	//number of cards in each hand(used to update each player's hand)

int Cards[4][13];	//deck of cards

int p_counter;		//counts the number of next draw options that don't result in a bust
double percentage;

bool GameOn;

	//default constructor. Creates a two player game 
	BlackJack() {		
		SuitesAndFaces();
		totalTurn= 0;
		totalPlayer=2;
		PlayerValue = 0;
		DealerValue = 0;
		P_num =0;
		D_num=0;
		GameOn = true;
		p_counter = 0;
	}


	//user inputs the number of players in the game
	BlackJack(int num_Players) {
		SuitesAndFaces();
		totalTurn=0;
		totalPlayer= num_Players;
		PlayerValue = 0;
		DealerValue=0;
		P_num=0;
		D_num=0;
		GameOn=true;
		p_counter = 0;
	}

	//destructor
	~BlackJack() {
		
	}

/*
Method: SuitesAndFaces
Parameters: void
Description: helper method used to initialize the three multidimensional arrays(Cards, Dealer, & Player)
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
			for(int y=0; y<11; y++){
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
			int temp=0;
			while(temp !=1 || temp !=11){
				cout << "Choose a value: 11 or 1?";
				cin >> temp;
				if(temp ==1)
					return 1;
				else if(temp==11)
					return 11;
				else cout << "Enter a valid number!" << endl;
			}
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



	void setup(int numPlayers){
		while(GameOn == true && totalTurn < (numPlayers * 2)){
			DealwithIt(totalTurn%2+1);
			usleep(750000);			//sleep for .75 seconds
		}
	}

/*
Method: update
Parameters: integer x, integer y, int playerID
Description: helper method, called in DealwithIt().
Returns: void; updates the player/dealer's hand with the latest draw. 
*/
	void update(int x, int y, int playerID) {
		//playerID =1 --> Player's turn
		//playerID =2 --> Dealer's turn
		if(playerID == 1)
		{
			Player[0][P_num]=x;
			Player[1][P_num]=y;
			PlayerValue += getValue(y);
			P_num++;
			if(PlayerValue ==21){
				GameOn = false;
				cout << "WINNER WINNER CHICKEN DINNER!" << endl;
				cout << "Player wins!" << endl;
			}
			else if(PlayerValue > 21)
			{
				GameOn = false;
				cout << "Player busts! Dealer wins!" << endl;
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
			else if(DealerValue > 21)
			{
				GameOn = false;
				cout << "Dealer busts! Player wins!" << endl;
			}
			cout << "Dealer has "<< getFace(y) <<" of " << getSuit(x) << endl;
			cout <<"DealerValue: " << DealerValue << "\n"<< endl;
		}	
		totalTurn++;
	}

/*
Method: DealwithIt
Parameters: void
Description: uses RNG to generate a "random" next card. Puts that card into either Dealer/Player's hand.
Returns: void
*/
	void DealwithIt(int playerID) {
		value = rand() % 52;
		int x = value/13;
		int y = value%13;

		//use srand and rng to get a random x and y
		if (Cards[x][y] == 0)
		{
			Cards[x][y] = playerID;
			//cout <<"x is: " << x << " and y is: "<< y << endl;			
			update(x,y, playerID);
		}
		else {
			cout << "not this one.... x is: " << x << " and y is: " << y << endl;
			DealwithIt(playerID);
		}
	}

/*
Method: isThisDEnd
Parameters: void
Description: Assess the hand to see if Player/Dealer has flopped
Returns: void
	void isThisDEnd()
	{
	if(PlayerValue ==21 || DealerValue ==21)
	{
		GameOn=false;
	}
	else if(PlayerValue > 21)
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
*/

/*
Method: soWhoWins
Parameters: void
Description: Helper method that is called only if both player and dealer don't bust. 
		Prints out the winner.
Returns: void
*/
	void soWhoWins()
	{
		cout << "Entered soWhoWins: " << endl;
		if(PlayerValue > DealerValue)	//Player must beat the dealer to wina
		{
			cout << "Player wins!" << endl;
		}
		else if(PlayerValue == DealerValue)
		{
			cout << "Tied! Dealer wins!" << endl;
		}
		else
		{
			cout << "Dealer wins!" << endl;
		}
		GameOn = false;
	}


/*
Method: bustPercentage
Parameters: void
Description: Calculates the percentage of busting using the remaining cards left in the deck. 
Returns: void
*/
	void bustPercentage()
	{
		p_counter = 0;
		if(PlayerValue > 11)
		{
			int magic_num = 21 - PlayerValue;
			for(int j =0; j < 4 ; j++)
			{
				for(int i=0; i<magic_num; i++)
				{
					if(Cards[j][i]==0)
						p_counter++;
				}
			}
			percentage = 100 - 100*((double)p_counter/(52-totalTurn));
			cout << "Percentage of busting: " << percentage << endl;
		}
		else
			cout << "no chance of busting! I recommend that you take another card" << endl;
	}

};

/*
int main(void) {
	BlackJack bj(2);	//initialize object
	srand(time(NULL));
	while (bj.GameOn == true && bj.totalTurn <4)
		bj.DealwithIt(bj.totalTurn%2 + 1);
	//ASK PLAYER IF YOU WANT TO HIT
	int hit;
	if(bj.GameOn == true)
	{
		printf("Player's turn.\n");
		bj.bustPercentage();
		printf("Hit? Type 1 for 'yes' or anything else for 'no': ");
		scanf("%d", &hit);
		while(bj.GameOn == true && hit ==1)
		{
			bj.DealwithIt(1); //player keeps hitting
			bj.isThisDEnd();
			//method that calculates likelihood of busting on next draw
			if(bj.GameOn==true)
			{	
				bj.bustPercentage();
				printf("Hit? Type 1 for 'yes' or anything else for 'no': ");
				scanf("%d", &hit);
			}
		}	
		//while loop for dealer
		while(bj.GameOn == true && bj.DealerValue < bj.PlayerValue)
		{
			bj.DealwithIt(2);
			bj.isThisDEnd();
		}
		//if user stopped hitting before game is over
		if(bj.GameOn == true)
		{
			bj.soWhoWins();
		}
	}
}


*/
