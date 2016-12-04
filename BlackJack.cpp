#include <stdio.h>
#include <iostream>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <Python.h>
#include <boost/python.hpp>

//written by Jay Lim
//Last Edited: 12/2/16
//Multiplayer blackjack game(against dealer)
//Last Edit: Use structs to create objects of each player's hands


using namespace std;

struct Player{
	int HandValue = 0;
	int numCards = 0;
	int Hand[2][11] = {{ 0 }};
	
};


class BlackJack {
public:
	Player *Player1 = new Player;
	Player *Player2 = new Player;
	Player *Player3 = new Player;
	Player *Player4 = new Player;
	Player *P_Array[4] = {Player1, Player2, Player3, Player4};


//the maxiumum number of cards one can hold without busting is 11
//two columns to store a card's suite(diamonds, hearts, clubs, ace) and face value(Ace, 2, 3, ...)

//int Dealer[2][11]={{ 0 }};	//dealer's hand
//int Player1[2][11]={{ 0 }};	//player 1's hand
//int Player2[2][11]={{ 0 }};	//player 2's hand
//int Player3[2][11]={{ 0 }};	//player 3's hand

//HandValue[3] is the dealer's hand
//int HandValue[4]={ 0 };
	
	int totalTurn, totalPlayer;
//int P1_num, P2_num, P3_num, D_num;	//number of cards in each hand

	int Cards[4][13]={{ 0 }};	//deck of cards

	double percentage;

	//default constructor. Creates a two player game 
	BlackJack() {		
		totalTurn= 0;
		totalPlayer=2;
		//P1_num = 0;
		//P2_num = 0;
		//P3_num = 0;
		//D_num=0;
		srand(time(NULL));
	}

	//user inputs the number of players in the game
	BlackJack(int num_Players) {
		totalTurn=0;
		totalPlayer= num_Players;
		//P1_num=0;
		//P2_num=0;
		//P3_num=0;
		//D_num=0;
		srand(time(NULL));
	}

	//no destructor required
	~BlackJack() {
	delete Player1;
	delete Player2;
	delete Player3;
	delete Player4;
	};

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
				getchar();
				//cin.clear();
				//cin.ignore(INT_MAX);
				if(temp ==1)
					return 1;
				else if(temp==11)
					return 11;
				else cout << "Enter a valid number!" << endl;
			}
		}
		else if(unit > 8)	//unit 9 translates to a 10, unit 10 into Jack, etc
			return 10;
		else return (unit+1);
	}

/*
Method: getSuit
Parameters: integer i
Description: converts an integer(0-3) into a suit.
Returns: string (one of four suite)
*/
	string getSuit(int i){
		if(i==0)
			return "spades";
		else if (i==1)
			return "hearts";
		else if (i==2)
			return "clubs";
		else return "diamonds";
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
				return "ace";
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
				return "jack";
				break;
			case 11:
				return "queen";
				break;
			default:
				return "king";
				break;
		}
	}

	
	int getHandValue(int playerID){
		//cout << "playerID : 0 - \t" << P_Array[0]->HandValue << endl;
		//cout << "playerID : 1 - \t" << P_Array[1]->HandValue << endl;
		//cout << "playerID : 2 - \t" << P_Array[2]->HandValue << endl;
		//cout << "playerID : 3 - \t" << P_Array[3]->HandValue << endl;		
		return P_Array[playerID-1]->HandValue;
	}


	int getNumCards(int playerID){
		//cout << "playerID: 0 -\t" << P_Array[0]->numCards << endl;
		//cout << "playerID: 1 -\t" << P_Array[1]->numCards << endl;
		//cout << "playerID: 2 -\t" << P_Array[2]->numCards << endl;
		//cout << "playerID: 3 -\t" << P_Array[3]->numCards << endl;
		return P_Array[playerID-1]->numCards;
	}

/*
Method: update
Parameters: integer x, integer y, int playerID
Description: helper method, called in DealwithIt().
Returns: void; updates the player/dealer's hand with the latest draw. 
*/
	string update(int x, int y, int playerID) {
		//playerID = 1 --> Player 1's turn
		//PlayerID = ......
		//playerID = totalPlayer --> Dealer's turn
		string temp= "";
		if(playerID == 1){
			cout << "Player 1's Turn: " << endl;
			Player1->Hand[0][Player1->numCards] = x;
			Player1->Hand[1][Player1->numCards] = y;
			Player1->HandValue +=getValue(y);
			Player1->numCards++;
			if(Player1->HandValue ==21){
				cout << "21!" << endl;
			}
			else if(Player1->HandValue > 21){
				cout << "Player 1 busts!" << endl;
			}
			cout << "Player 1 has "<< getFace(y) <<" of " << getSuit(x) << endl;
			cout <<"Player 1's Hand Value: " <<Player1->HandValue<< endl;
			temp = getFace(y)+"_of_"+getSuit(x)+".png";
		}
		else if(playerID == 2 && playerID != totalPlayer){
			cout << "Player 2's Turn: " << endl;
			Player2->Hand[0][Player2->numCards]=x;
			Player2->Hand[1][Player2->numCards]=y;
			Player2->HandValue += getValue(y);
			Player2->numCards++;
			if(Player2->HandValue ==21){
				cout << "21!" << endl;
			}
			else if(Player2->HandValue > 21){
				cout << "Player 2 busts!" << endl;
			}
			cout << "Player 2 has "<< getFace(y) <<" of " << getSuit(x) << endl;
			cout <<"Player 2's Hand Value: " << Player2->HandValue << endl;
			temp = getFace(y)+"_of_"+getSuit(x)+".png";
		}
		else if(playerID == 3 && playerID != totalPlayer){
			cout << "Player 3's Turn: " << endl;
			Player3->Hand[0][Player3->numCards]=x;
			Player3->Hand[1][Player3->numCards]=y;
			Player3->HandValue += getValue(y);
			Player3->numCards++;
			if(Player3->HandValue ==21){
				cout << "21!" << endl;
			}
			else if(Player3->HandValue > 21){
				cout << "Player 3 busts!" << endl;
			}
			cout << "Player 3 has "<< getFace(y) <<" of " << getSuit(x) << endl;
			cout <<"Player 3's Hand Value: " << Player3->HandValue << endl;
			temp = getFace(y)+"_of_"+getSuit(x)+".png";
		}
		else{
			cout << "Dealer's Turn: " << endl;
			Player4->Hand[0][Player4->numCards]=x;
			Player4->Hand[1][Player4->numCards]=y;
			Player4->HandValue +=getValue(y);
			Player4->numCards++;
			if(Player4->HandValue == 21){
				cout << "Dealer wins!" << endl;			
			}
			else if(Player4->HandValue > 21){
				cout << "Dealer busts!" << endl;
			}
			cout << "Dealer has "<< getFace(y) <<" of " << getSuit(x) << endl;
			cout <<"DealerValue: " << Player4->HandValue << endl;
			temp = getFace(y)+"_of_"+getSuit(x)+".png";
		}	
		totalTurn++;
		return temp;
	}

/*
Method: DealwithIt
Parameters: int playerID
Description: uses RNG to generate a "random" next card. Puts that card into either Dealer/Player's hand.
Returns: void
*/
	string DealwithIt(int playerID){
		//playerID 0 = player 1
		//playerID 1 = player 2
		//playerID 2 = player 3
		//playerID 3 = dealer
		sleep(1);
		int value = rand() % 52;
		int x = value/13;
		int y = value%13;

		//use srand and rng to get a random x and y
		if (Cards[x][y] == 0){
			Cards[x][y] = 1;
			return update(x,y, playerID);
		}
		else{	//duplicate card - reroll
			return DealwithIt(playerID);
		}
	}

/*
Method: soWhoWins
Parameters: void
Description: Method called just prior to end of the game. Used to determine the winners & losers
Returns: void
*/
	void soWhoWins(){
		int x[4];
		for(int i=0; i<4; i++)
		{
			if(P_Array[i]->HandValue<=21)
				x[i]=P_Array[i]->HandValue;
			else 
				x[0]=0;
		}
		if(x[3]==0)	//dealer bust
			cout << "Dealer has busted! Players win!" << endl;
		else if(x[3] >= x[0] && 
			x[3] >= x[1] && x[3] >= x[2]){
			cout << "Dealer wins!" << endl;
		}
		else{
			for(int i=0; i<totalPlayer-1; i++){
				if(x[i] > x[3] && x[i] != 0)
					cout << "Player " << i+1 << " wins!" << endl;
			}	
		}
	}

/*
Method: bustPercentage
Parameters: int playerID
Description: Calculates the percentage of busting using the remaining cards left in the deck. 
Returns: void
*/
	void bustPercentage(int playerID){
		int p_counter = 0;
		if(P_Array[playerID-1]->HandValue==21)
			cout <<"Percentage of busting: 100%" << endl;
		else if(P_Array[playerID-1]->HandValue > 11){
			int magic_num = 21 - P_Array[playerID-1]->HandValue;
			for(int j =0; j < 4 ; j++){
				for(int i=0; i<magic_num; i++){
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


using namespace boost::python;
BOOST_PYTHON_MODULE(bj){
//using namespace boost::python;
	class_<BlackJack>("BlackJack", init<int>())
		.def("DealwithIt", &BlackJack::DealwithIt)
		.def("getHandValue", &BlackJack::getHandValue)
		.def("bustPercentage", &BlackJack::bustPercentage)
		.def("soWhoWins", &BlackJack::soWhoWins)
		.def("getNumCards", &BlackJack::getNumCards)
	;
}

int main(){

return 0;
}

/*
extern "C" {
	BlackJack* bj_new(int num){ 
		//srand(time(NULL));
		return new BlackJack(num);
		
	}
	string DealCard(BlackJack *bj, int num){
		cout << num << endl;
		return bj->DealwithIt(0);
	}

}



int main(void) {
	int numPlayers;
	cout << "Enter the number of players:(2-4) ";
	cin >>numPlayers;
	cout << "" << endl;
	BlackJack bj(numPlayers);
	
	srand(time(NULL));

	while (bj.totalTurn < numPlayers * 2){
		bj.DealwithIt((bj.totalTurn % numPlayers) + 1);
		if(bj.totalTurn==numPlayers)
			cout << "****************************************\n"<<endl;
	}
	
	char hit;
	//players hit until they choose to stay
	for(int i=1; i < numPlayers; i++){
		cout << "Player " << i << "'s turn."<<endl;
		cout << "Player has " << bj.HandValue[i-1] << endl;
		bj.bustPercentage(i);
		cout << "Hit? Type 'Y'/'y' for 'yes' or anything else for 'no': ";
		cin >> hit;
		cout << "" << endl;
		while(bj.HandValue[i-1] < 21 && (hit =='Y' ||hit =='y') ){
			bj.DealwithIt(i);
			if(bj.HandValue[i-1] < 21){ 
				bj.bustPercentage(i);
				cout << "Hit? Type 'Y'/'y' for 'yes' or anything else for 'no': ";
				cin >> hit;
				cout << "" << endl;
			}
		}
	}
	//Dealer must stand with a hand value greater than or equal to 17.
	while(bj.HandValue[3] < 17){
		cout <<"********************************************\n" << endl;
		cout << "Dealer has "<< bj.HandValue[3] << endl;
		bj.DealwithIt(numPlayers);
	}
	bj.soWhoWins();
}
*/

