/*
//  CS 202
//  Provided Main Program
//  Assignment #2 - Game of Twenty Six
//  C++ program to implement game of twenty six.
*/

// ***********************************************************************
//  Includes and prototypes

#include <cstdlib>
#include <iostream>
#include <string>

#include "twentySix.h"

void displayGameSummary(twentySix, int);

using namespace std;


// ***********************************************************************
//  Main program to test the twentySix object in a variety
//		of different ways.  Includes both iteractive and non-interactive
//		uses of the object.  Also includes error checking for various
//		invalid values.

int main()
{

// ----------------------------------------------------------------------
//  Initializations and declarations

	twentySix	myGame;					// create game object
	bool		keepPlaying = true;		// continue playing (yes/no)
	string		stars(60,'*');

// ----------------------------------------------------------------------
//  Start interactive session

	system("clear");

	cout << endl;
	cout << stars << endl;
	cout << "Welcome to the CS 202 Game of Twenty Six" << endl << endl;

	myGame.readInitialBankAmount();
	myGame.setDisplayMode(true);

	while (keepPlaying) 
	{
		myGame.playRound();
		if (myGame.getBankAmount() <= 0) 
		{
			cout << "Sorry, you have lost.  :-(" << endl;
			break;
		}
		keepPlaying = myGame.playOn();
	}

		cout << endl;
		cout << stars << endl;
		cout << " Interactive Summary:" << endl;
		cout << "   Initial Bank: "     << myGame.getInitialBankAmount() << endl;
		cout << "   Final Bank: "       << myGame.getBankAmount()        << endl;

		if (myGame.getBankAmount() >= myGame.getInitialBankAmount())
			{ cout << "   Your a WINNER!!   Yeah!!" << endl; }
		
		cout << endl;
		cout << stars << endl;
		cout << endl << endl;


// ----------------------------------------------------------------------
//  Perform a series of non-interactive simulations.
//  Various simulations use different stragegies.

	twentySix	game1;			// create game object 1
	twentySix	game2;			// create game object 2
	twentySix	game3;			// create game object 3
	twentySix	game4(100);		// create game object 4
	twentySix	game5(200);		// create game object 5
	twentySix	game6(200);		// create game object 6
	twentySix	game7(300);		// should show error message...
	int	        startAmt, endAmt;

	game6.setInitialBankAmount(500);	// error testing...

	// ----------------------------------------
	//  Strategy: keep playing until bank is lost or until the
	//	initial bank is doubled.
	//	Also, asks user if they want to see the games...

	game1.setInitialBankAmount(30);
	cout << endl;
	cout << stars << endl;
	cout << "Non-interactive game simulation." << endl;
	game1.readDisplayMode();
	keepPlaying = true;
	while (keepPlaying) 
	{
		game1.playRound();
		if (game1.getBankAmount() <= 0) break;
		if (game1.getBankAmount() > (game1.getInitialBankAmount()*2))
			keepPlaying = false;
	}

	// ----------------------------------------
	//  Strategy: keep playing until bank is lost or until the initial
	//	bank is doubled.  But, this time, start with max bank!

	game2.setInitialBankAmount(200);
	game2.setDisplayMode(false);
	keepPlaying = true;
	while (keepPlaying) 
	{
		game2.playRound();
		if (game2.getBankAmount() <= 0) break;
		if (game2.getBankAmount() > (game2.getInitialBankAmount()*2)) 
			keepPlaying = false;
	}

	// ----------------------------------------
	//  Strategy: keep playing until bank is lost or until up 50% (x 1.5)

	startAmt = 200;
	endAmt   = 300;
	game3.setInitialBankAmount(startAmt);
	game3.setDisplayMode(false);
	keepPlaying = true;
	while (keepPlaying) 
	{
		game3.playRound();
		if (game3.getBankAmount() <= 0)
			break;
		if (game3.getBankAmount() > endAmt)
			keepPlaying = false;
	}

	// ----------------------------------------
	//  Strategy: keep playing until bank is lost or until up 50% (x 1.5)
	//	But, starts with small initial bank (100).
	//	Note, initial bank set via constructor.

	endAmt = 300;
	game4.setDisplayMode(false);
	keepPlaying = true;
	while (keepPlaying) {
		game4.playRound();
		if (game4.getBankAmount() <= 0)
			break;
		if (game4.getBankAmount() > endAmt)
			keepPlaying = false;
	}

	// ----------------------------------------
	//  Strategy: keep playing until bank is lost or until up 50% (x 1.75)

	startAmt = 200;
	endAmt = 350;
	game5.setInitialBankAmount(startAmt);
	game5.setDisplayMode(false);
	keepPlaying = true;
	while (keepPlaying) 
	{
		game5.playRound();
		if (game5.getBankAmount() <= 0)
			break;
		if (game5.getBankAmount() > endAmt)
			keepPlaying = false;
	}

	// ----------------------------------------
	//  Display simulation results...

	cout << endl;
	cout << stars << endl;
	cout << " Simulation Summary:" << endl << endl;

	displayGameSummary(game1, 1);
	displayGameSummary(game2, 2);
	displayGameSummary(game3, 3);
	displayGameSummary(game4, 4);
	displayGameSummary(game5, 5);

	cout << endl << endl;

	return	EXIT_SUCCESS;
	cout << endl << endl;
}

// ***********************************************************************

void displayGameSummary(twentySix thisGame, int gameNumber)
{
	string bars;
	bars.append(50, '-');

	cout << bars << endl;
	cout << "   Results, Game (" << gameNumber << "):" << endl;
	cout << "   Initial Bank: " << thisGame.getInitialBankAmount() << endl;
	cout << "   Final Bank: " << thisGame.getBankAmount();

	if (thisGame.getBankAmount() > thisGame.getInitialBankAmount())
		cout << "   Winning strategy!!" << endl;
	else
		cout << "   Losing strategy..." << endl;
	cout << endl;

}

// ***********************************************************************
