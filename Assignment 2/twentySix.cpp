/*
    Name: Thien Nguyen - Revision on 3/29/2022
    Description: This program simulates a game known as Twenty-Six, it will ask the user for an initial bank value,
                 then go through a bunch of automated games until it reaches 26 or the user decides to stop.
    Input: Initial bank values and yes or no options.
    Output: Output of the game.
*/

#include "twentySix.h"

using namespace std;

/*
    function identifier: constructor that initializes initialBank to a given number if it's in range,
                        and 0 if it's not, as well as initialize all other values to 0 and true.
    parameters: initialBank value
    return value: N/A
*/

twentySix::twentySix(int x)
{
    initialBank   = x;
    currentBank   = 0;
    displayGame   = true;
    pointValue    = 0;
    currentScore  = 0;
    currentPayout = 0;
    // loops through array and initializes all values to 0
    for (int i = 0; i < 13; i++)
    {          
        for (int j = 0; j < 10; j++)
        {
            diceRolls[i][j] = 0;
        }
    }

    // checks if its in range
    if (initialBank >= MIN_BANK && initialBank <= MAX_BANK)
    { 
        currentBank = initialBank;
    }
    else
    {
        cout << "Error, invalid bank amount.\n";
        initialBank = 0;
        currentBank = 0;
    }
}

/*
    function identifier: checks if the initial bank value is in range, and if it's not it'll
                        repeat until it is.
    parameters: N/A
    return value: N/A
*/
void twentySix::readInitialBankAmount()
{
    do
    {
        cout << "Initial Bank amount must be between 10 and 200\n"
             << "Enter Initial Bank Amount: ";
        cin >> initialBank;
        if(initialBank < MIN_BANK || initialBank > MAX_BANK){
            cout << "Error, invalid bank amount, please re-enter.\n";
            cin.clear();
            cin.ignore(40,'\n');
        }
    // runs while its not in range
    } while (initialBank < MIN_BANK || initialBank > MAX_BANK); 
    currentBank = initialBank;
}

/*
    function identifier: sets initialBank and currentBank 
    values to given int if it's in range
    parameters: initialBank value
    return value: N/A
*/

void twentySix::setInitialBankAmount(int x)
{
    if(x >= MIN_BANK && x <= MAX_BANK){
        initialBank = x;
        currentBank = initialBank;
    }
    else{
        cout << "Error, invalid initial bank amount value.\n"
             << "No changes made.\n";
    }
}

/*
    function identifier: returns initialBank value
    parameters: N/A
    return value: N/A
*/
int twentySix::getInitialBankAmount() const
{
    return initialBank;
}

/*
    function identifier: returns currentBank value
    parameters: N/A
    return value: N/A
*/
int twentySix::getBankAmount() const
{
    return currentBank;
}

/*
    function identifier: sets displayGame to passed value
    parameters: bool value
    return value: N/A
*/
void twentySix::setDisplayMode(bool x)
{
    displayGame = x;
}

/*
    function identifier: Asks user if they want to display game details, and will display if they say true it will.
    parameters: N/A
    return value: N/A
*/
void twentySix::readDisplayMode()
{
    // flag control
    bool temp = yesOrNo("Display Game Details? (Y/y/N/n): ");

    if      (temp == true)   displayGame = true;
    else if (temp == false)  displayGame = false;
}

/*
    function identifier: Asks user if they want to play another round, and will simulate another round if they say yes.
    parameters: N/A
    return value: N/A
*/
bool twentySix::playOn() const
{
    // calls the yesOrNo function with the prompt
    bool temp = yesOrNo("Play Another Round? (Y/y/N/n): "); 
    
    if (temp == true)
        return true;
    else
        return false;
}

/*
function identifier: Simulates 1 round of 26 of the game. If the bank is < or = to 0 it'll end the game,
                     otherwise the current bank decrements by 1 and a random point is established, the array values
                     are randomized, and it'll loop through the array to see if the randomized point value matches any
                     of the random values in the array. Afterwards it'll calculate and score based on the rules.
parameters: N/A
return value: N/A
*/
void twentySix::playRound()
{
    if (currentBank <= 0)
        return;
    else
    {
        currentScore = 0;
        currentBank--;
        pointValue = rand() % 6 + 1;    // rolls the dice (random 1-6)
        for(int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 10; j++)
            {
            // sets the values of the array to random numbers (1-6)
                diceRolls[i][j] = rand() % 6+1;     
            // checks if the value given matches any of the values
                if (diceRolls[i][j] == pointValue)  
                // in the array
                    currentScore++;                 
            }   
        }
        //Point calculation
        if      (currentScore <= 10) currentPayout = 10;
        else if (currentScore == 13) currentPayout = 5;
        else if (currentScore == 26) currentPayout = 4;
        else if (currentScore == 27) currentPayout = 5;
        else if (currentScore == 28) currentPayout = 6;
        else if (currentScore == 29) currentPayout = 8;
        else if (currentScore == 30) currentPayout = 10;
        else                         currentPayout = 0;

        currentBank = currentBank + currentPayout;
    }
    
    if (displayGame == true)
        showGame();
}

/*
    function identifier: Checks for user input for Yes or No.
    parameters: the string of the question
    return value: true/false
*/

bool twentySix::yesOrNo(string x) const
{
    bool tF;
    string userInput;

    do
    {
        cout << x;
        cin >> userInput;
        if (userInput == "Y" || userInput =="y")
            tF = true;
        else if (userInput == "N" || userInput == "n")
            tF = false;
        else {
            cout << "Error, must respond 'Y', 'y', 'N', or 'N'.\n"
                 << "Please try again.\n";
            cin.clear();  // clears the wrong input
            cin.ignore(40,'\n');
        }
    } while ((userInput != "Y" && userInput != "y") && (userInput != "N" && userInput != "n"));

    return tF;
}

/*
    function identifier: Outputs the content of the game
    parameters: N/A
    return value: N/A
*/

void twentySix::showGame() const
{
    cout << endl << "*********************************" << endl;
    cout << "Twenty-Six Game - Round Results: " << endl;
    cout << "Dice Rolls: " << endl;
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 10; j++)
            cout << "   " << diceRolls[i][j];
            cout << endl;
        }
        cout << endl;
        cout << "Initial Bank:   "  << initialBank  << endl;
        cout << "Point Value:    "  << pointValue   << endl;
        cout << "Score:          "  << currentScore << endl;
        cout << "Payout Amount:  "  << currentPayout;
        if (currentPayout > 0) cout << "     You won!  :-)"  << endl;
        else                   cout << "     You lost.  :-(" << endl;
                               cout << "Current Bank:   "    << currentBank << "\n\n";

}