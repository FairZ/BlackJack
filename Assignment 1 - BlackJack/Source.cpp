#include <iostream>					//inclusion of necessary libraries
#include <Windows.h>
#include <time.h>

using namespace std;				//removes the need for std::

struct Card									//decleration of the card structure, used to store data such as value and name
{
	int m_value;
	char m_suit[9];
	char m_name[6];
};

void Game();								//prototyping of functions
int DrawCard(int &card, int &draw, int &playerTotal, Card (&Deck)[52]);
int DealerDraw(int &card, int &draw, int &dealerTotal, Card (&Deck)[52], Card &Hole);
void ShuffleDeck(Card (&Deck)[52]);

int main()
{

	int menuChoice = 0;				//initialization of necessary variables for this function
	bool errorCheck = 0;
	bool quit = 0;

	do
	{
		
		errorCheck = 0;					//prevents and infinite loop
		system("cls");					//clears screan
		cout << "Please enter a value corresponding to option you wish to pick:\n";				//displays message to user to chose an option.
		cout << "1.Play\n2.Quit\n";																								
		do
		{
			cin >> menuChoice;		//accepts user's input
			switch (menuChoice)		//evaluates the outcome based on the user's input
			{
			case 1 :
				{
				Game();							//runs the game if 1 is entered
				quit = 1;						//quits after game is finished
				break;
				}
			case 2 :
				{
				quit = 1;						//quits the game if 2 is entered
				break;
				}
			default :							//any other value will output an error message and repeat the loop
				{
				cout << "The value entered was invalid please reselect an option\n";
				errorCheck = 1;
				break;
				}
			}

		}while (errorCheck);		//loop repeats if an invalid value was entered

	}while (quit == false);

	return 0;
}

void Game()
{

	bool exit = false;

	///deck initialization, originally written by Andrew Watson
	Card Deck[52] = {0};
	for (int suit = 0; suit < 52; suit += 13)						//changes suit every 13 cards
	{
		for ( int card = 0; card < 13 ; card++ )					//loops in sets of 13
		{
			if (card > 9)																		//if the card is 10 or above give it a value of 10
			{
				Deck[suit + card].m_value = 10;
			}
			else																						//otherwise set the card's value as its position plus 1 (since it starts from 0)
			{
				Deck[suit + card].m_value = card + 1;
			}

			switch (suit)																		//assign the correct suit name to each card
			{
			case 0:
				{
				strcpy(Deck[suit + card].m_suit,"Hearts");
				break;
				}
			case 13:
				{
				strcpy(Deck[suit + card].m_suit,"Spades");
				break;
				}
			case 26:
				{
				strcpy(Deck[suit + card].m_suit,"Diamonds");
				break;
				}
			case 39:
				{
				strcpy(Deck[suit + card].m_suit,"Clubs");
				break;
				}
			}

			switch (card)																		//assign the correct name to each card
			{
			case 0:
				{
				strcpy(Deck[suit + card].m_name,"Ace");
				break;
				}
			case 1:
				{
				strcpy(Deck[suit + card].m_name,"Two");
				break;
				}
			case 2:
				{
				strcpy(Deck[suit + card].m_name,"Three");
				break;
				}
			case 3:
				{
				strcpy(Deck[suit + card].m_name,"Four");
				break;
				}
			case 4:
				{
				strcpy(Deck[suit + card].m_name,"Five");
				break;
				}
			case 5:
				{
				strcpy(Deck[suit + card].m_name,"Six");
				break;
				}
			case 6:
				{
				strcpy(Deck[suit + card].m_name,"Seven");
				break;
				}
			case 7:
				{
				strcpy(Deck[suit + card].m_name,"Eight");
				break;
				}
			case 8:
				{
				strcpy(Deck[suit + card].m_name,"Nine");
				break;
				}
			case 9:
				{
				strcpy(Deck[suit + card].m_name,"Ten");
				break;
				}
			case 10:
				{
				strcpy(Deck[suit + card].m_name,"Jack");
				break;
				}
			case 11:
				{
				strcpy(Deck[suit + card].m_name,"Queen");
				break;
				}
			case 12:
				{
				strcpy(Deck[suit + card].m_name,"King");
				break;
				}
			}
		}
	}						
	///end of citation

	do
	{
		int cardNumber = 0;					//initialization of variables used in this function and functions called by this one
		exit = false;
		int dealerHand = 0;
		int dealerDraw = 0;
		Card dealerHole = {0};			
		int money = 1000;
		int playerHand = 0;
		int playerDraw = 0;
		int lose = 0;
		int quit = 0;
		int bet = 0;
		bool betCheck = false;
		int play = 0;

		system("cls");							//clear the menu from the screen

		cout << "The aim of this game is to get a hand worth as close to 21 as possible without going over.\n";						//print out to the user the rules of blackjack and how to play the game
		cout << "At the start of each round you must bet any amount of chips (as long as you have that many).\n";
		cout << "If you get a value over 21 or lower than the dealer you will lose your bet money,\n";
		cout << "however if you get closer to 21 you will double your money and if you get a blackjack\n";
		cout << "(21 with just 2 cards) you will earn an extra half of your bet amount.\n";
		cout << "After recieving your two cards you will be asked to stick or twist,\n";
		cout << "twist will give you an extra card and stick will reveal who one the game.\n";
		cout << "You will start with 1000 chips and you will lose if you lose them all,\n";
		cout << "you can also quit the game after any round.\n";
		Sleep(40000);								//wait for 40 seconds to allow the user time to read the instructions
		ShuffleDeck(Deck);					//shuffles the cards in the deck

		do
		{
			system("cls");						//clears away the instructions
			playerHand = 0;						//resets the values of both variables at the start of each round to avoid incorrect values
			dealerHand = 0;
			play = 0;
			if (cardNumber > 40)			//reshuffles the deck and resets the position in the deck when getting close to 52
			{
				cardNumber = 0;
				ShuffleDeck(Deck);
			}

			cout << "You have " << money << " chips for betting\n";			//displays the amount the player has for betting

			do
			{
				betCheck = false;																								//stops an inifinite loop
				cout << "enter how much you would like to bet: ";								//asks the user for input of how much they wish to spend
				cin >> bet;

				if (bet > money)
				{
					cout << "You cannot bet more than you have.\nPlease ";				//stops the user from betting more than they have and displays an error if they do
					betCheck = true;																							//causes the loop to repeat
				}
				if (bet <= 0)																										//stops the user from betting no money or negative money and displays an error if they do
				{
					cout << "You must enter a value greater than 0.\nPlease ";
					betCheck = true;																							//repeats the loop
				}

			}while(betCheck == true);																					//will loop if error is found

			system("cls");																										//clears away bet placement

			lose = DealerDraw(cardNumber, dealerDraw, dealerHand, Deck, dealerHole);	//runs the DealerDraw functions with various inputs and assigns the returned value to the lose variable
			money -= bet;																											//removes the bet amount from the total amount of money
			
			if (lose != (2||1))																								//if the value returned from the DealerDraw function is not either 2 or 1 do the following statements
			{
				play = 1;																												//allows further if statements later based on the situation

				cout << "Your bet is " << bet << " chips.\n";										//displays the placed bet
				
				lose = DrawCard(cardNumber, playerDraw, playerHand, Deck);			//runs the DrawCard function and assigns the returned value to lose

				if (lose != 1)																									//if lose is not equal to 1 then do the following statement
				{
					cout << "The dealer's facedown card was the " << dealerHole.m_name << " of " << dealerHole.m_suit << " for a total of: " << dealerHand << endl;
				}																																//displays the dealer's face down card

				if ((lose == 0)&&(playerHand < dealerHand))											//if the user has a lower value hand than the dealer the round is lost and a message is displayed
				{
					cout << "Oh no you lost, better luck next time!\n";
				}
				if ((lose == 0)&&(playerHand > dealerHand))											//if the user has a higher value hand than the dealer the round is won, a message is displayed and the bet is returned doubled
				{
					cout << "Well done you won, here's your bet back and doubled\n";
					money += (bet*2);
				}
				if (((lose == 0)||(lose == 2))&&(playerHand = dealerHand))			//if the user got the same value of the dealer a message is displayed and money returned in a accordance with how many cards were drawn
				{
					if (playerDraw > dealerDraw)																	
					{
						cout << "The dealer got the same as you but with less cards so he wins and you lose your bet.\n";
					}
					if (playerDraw < dealerDraw) 
					{
						cout << "You got the same as the dealer but with less cards so you win and double your bet.\n";
						money += (bet*2);
					}
					else
					{
						cout << "You got the same value as the dealer in the same number of cards, it's a draw!\nYour money is returned to you.\n";
						money += bet;
					}
				}
				if (lose == 1)									//if you got a blackjack the user's bet is returned doubled plus half
				{
					money += ((bet*2)+(bet/2));
				}
			}
			if ((play != 1)&&(lose == 2))			//if the dealer went bust the user's bet is returned doubled
			{
				money += (bet*2);
			}
			if (money > 0)										//if the user still has money left, ask if they wish to play again or quit
			{
				cout << "Do you want to try again? (enter 0 to play another round or any other value to quit)\n";
				cin >> quit;
				if (quit != 0)
				{
					exit = true;
				}
			}
			if (money <= 0)										//if the user has run out of money, ask if they wish to restart the game or quit
			{
				cout << "You've run out of money do you want to restart the game? (enter 0 to play again or any other integer to quit)\n";
				cin >> exit;
				if (exit = 0)
				{
					quit = 1;
					exit = false;
				}
			}
		}while(quit == 0);			//re-runs loop if the user wishes to play again without restarting the whole game
	}while(exit == false);		//re-runs the game if the user wishes to restart the game
}

void ShuffleDeck(Card (&Deck)[52])		//function to shuffle the cards of the addressed deck
{
	srand(time(NULL));									//random seed is set to the current time
	Card temp = {0};										//a card structure is created to store temporary values
	int random = 0;											
	for (int i = 0 ; i < 52 ; i++)			//iterates through each card individually
	{
		random = rand() % 52;							//assigns a random number
		temp = Deck[i];										//the current card is copied to the temp card
		Deck[i] = Deck[random];						//a random card is assigned to the current card
		Deck[random] = temp;							//the random card is given the current cards value from the temp card
	}
}

int DealerDraw(int &card, int &draw, int &dealerTotal, Card (&Deck)[52], Card &Hole)		//function to run the dealer's draws using many addressed parameters
{
	draw = 0;																	//initializes and zeroes varaibles used for this function
	bool repeatDraw = false;
	int win = 0;
	do
	{
		repeatDraw = false;											//prevents an endless loop
		dealerTotal += Deck[card].m_value;			//a card is drawn and it's value assigned to the dealer's hand

		if (draw == 0)													//if it is the first draw assign the card to the dealer's hole (aka face down card)
		{
			Hole = Deck[card];
		}
		if ((Deck[card].m_value == 1) && ((dealerTotal + 10) <= 21))		//if the card is an ace and using tthe high value will not cause a bust, use the high value
		{
			dealerTotal += 10;
		}
		if (draw == 1)																									//on the second draw the user is told what the second card is
		{
			cout << "The dealer has one face down card as well as the " << Deck[card].m_name << " of " << Deck[card].m_suit << endl;
		}
		if (repeatDraw == true)																					//if more than two cards have to be drawn show the extra cards names
		{
			cout << "and the " << Deck[card].m_name << " of " << Deck[card].m_suit << endl;
		}
		if (dealerTotal < 17)																						//if the dealer's hand value is less than 17 they must draw another card
		{
			repeatDraw = true;
		}
		if ((dealerTotal == 21)&&(draw < 2))														//if the dealer got a blackjack the user loses and the appropriate value for win is assigned
		{
			cout << "The dealer got a blackjack!! You lose.\n";
			win = 1;
		}
		if (dealerTotal > 21)																						//if the dealer goes over 21 the user wins and the appropriate value of win is assigned
		{
			cout << "The dealer has gone bust, you won!\n";
			win = 2;
		}
		draw++;																													//increase the value for draw and step through the deck by one each draw
		card++;
	}while(draw < 2 || repeatDraw == true);														//if there has only been 1 draw or another card must be drawn the loop is repeated
	return win;																												//return the value for win
} 

int DrawCard(int &card, int &draw, int &playerTotal, Card (&Deck)[52])	//function to run the user's card draws using multiple addressed parameters
{
	draw = 0;								//initializes and zeroes the variables used in this function
	int repeatDraw = 0;
	int win = 0;
	do
	{
		repeatDraw = 0;													//prevents an inifinite loop
		playerTotal += Deck[card].m_value;			//adds the value of the drawn card to the player's hand

		if (draw == 0)													//if it is the first draw display the name of the card drawn and make the loop repeat
		{
			cout << "You have drawn the " << Deck[card].m_name << " of " << Deck[card].m_suit << endl;
			repeatDraw = 1;
		}
		if (draw > 0 )													//if it is past the first draw display the name of the card drawn
		{
			cout << "You have drawn the " << Deck[card].m_name << " of " << Deck[card].m_suit << endl;
		}
		if (Deck[card].m_value == 1)						//if the card is an ace ask the user if they wish to use the high or low value for ace and adjust the hand total appropriately
		{
			cout << "Do you want the value of the ace to be 1 or 11? (please enter either 1 or 11)\n";
			bool errorCheck = false;
			int choice = 1;
			do
			{
				errorCheck = false;
				cin >> choice;
				if (choice != (1 || 11))
				{
					cout << "The number entered was invalid please choose either 1 or 11: ";
					errorCheck = true;
				}
			}while (errorCheck = true);
			if (choice == 11)
			{
				playerTotal += 10;
			}
		}
		if ((playerTotal == 21) && (draw == 1))						//if the user got a blackjack they win and the appropriate value for win is assigned
		{
			cout << "Well done, you got a blackjack!!! you win back your money plus half extra!"<<endl;
			win = 1;
		}
		if ((draw > 0)&&(playerTotal < 21))								//if the player has less than 21 and it is past the first draw, ask if they wish to draw another card
		{
			cout << "Your hand value is " << playerTotal << endl;
			cout << "Do you want to Stick or Twist? (enter 0 to stick or any other integer to twist)\n";
			cin >> repeatDraw;
		}
		if ((playerTotal == 21) && (draw > 1))						//if the player has 21 but in more than 2 cards assign the correct value for win
		{
			cout << "Your hand value is 21, well done let's see what the dealer got.\n";
			win = 2;
		}
		if (playerTotal > 21)															//if the player has more than 21 they went bust and the correct value for win is assigned
		{
			cout << "Oh no, you went bust and lost your money.\n";
			win = 3;
		}
		draw++;						//increase the draw number and card position byt 1 each turn
		card++;
	}while (repeatDraw != 0);	//repeat the loop if repeatDraw is not equal to 0
	return win;								//return the value of win
}