/*
    Name: Thien Nguyen - Revision on 3/29/2022
    Description: This program simulates a game known as Twenty-Six, it will ask the user for an initial bank value,
                 then go through a bunch of automated games until it reaches 26 or the user decides to stop.
    Input: Initial bank values and yes or no options.
    Output: Output of the game.
*/

#include <iostream>
#include <string>
using namespace std;

class twentySix{
private:
    const int   MAX_BANK = 200;
    const int   MIN_BANK = 10;
          int   initialBank;
          int   currentBank;
          int   pointValue;
          int   currentScore;
          int   currentPayout;
          int   diceRolls[13][10];
          bool  displayGame;
          bool  yesOrNo(string) const;
          void  showGame() const;
public:
                twentySix(int=10);
          int   getBankAmount() const;
          int   getInitialBankAmount() const;
          bool  playOn() const;
          void  readInitialBankAmount();
          void  setInitialBankAmount(int);
          void  setDisplayMode(bool);
          void  readDisplayMode();
          void  playRound();
};
