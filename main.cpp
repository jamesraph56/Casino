/**

  * James & Almer

  *Program Name: Github-athon

  *Date 6/7/22

*/

#include "GetValid.h"
#include <array>
#include <bits/stdc++.h>
#include <cstdlib>
#include <ctype.h>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

struct casino {
  double balance, wager;
  string name, address;
  int mode, guess, actions = 0;
  vector <double> bets;
};

void guessingGame(casino &rich);
void highOrLow(casino &rich);
void BubbleSort(casino &rich, int &);
int binarySearch(casino rich,int, int, double);

int main() {
  casino rich;
  string dummy;
  int choice = 1;
  cout << "\nWELCOME TO THE TONKA TRAIN -- PLAY OUR GAME ON YOUR ROAD TO RICHES!";
  cout << "\nFUNDED BY VAMP NATION & TWIZZYTOPIA";

  // finding the name
  cout << "\nGreetings! What is your name?\n";
  getline(cin, rich.name);

  // finding the address
  cout << "\nWhat is your address (so we can track you down in case you try to run)?\n";
  getline(cin, rich.address);

  // getting the amount they have
  if (rich.name != "Savesta" && rich.name != "Kumalala") {
    do {
      cout << "\nHow much money are you bringing on the train?\n";
    } while ((!(getValidDouble(rich.balance)) || (rich.balance > 1000000) || (rich.balance <= 0)));
  } else if (rich.name == "Kumalala") {
    cout << "\nGET THE HECK OUTTA HERE WE DON'T ALLOW MID";
    return 0;
  } else if (rich.name == "Savesta") {
    cout << "\nWe weren't expecting gods to board the train 😳. Welcome to the"
            " VIP Section\n";
    rich.balance = 1000000;
  }

  // chossing which game they want to play
  while (choice != 4 && rich.balance > 0) {
    cout << "\n1. Guessing Game";
    cout << "\n2. Higher or Lower";
    cout << "\n3. Show Balance";
    cout << "\n4. Leave the train (only for wusses)";
    do {
      cout << "\nWhat would you like to do, " << rich.name << "?\n";
    } while ((!(getValidInt(choice)) || (choice > 4) || (choice < 1)));
    if (choice == 1) {
      guessingGame(rich);
    }
    if (choice == 2) {
      highOrLow(rich);
    }
    if (choice == 3)  {
      string verify;
      double transaction;
      int n = sizeof(rich.bets)/sizeof(rich.bets[0]);
      cout << "\nYour current balance is: " << rich.balance;
      cout << "\nWould you like to verify one of your transactions? (y/n)\n";
      cin >> verify;
      getline(cin,dummy);
      if (verify == "Y" || verify == "y") {
        do {
          cout << "\nWhich transaction would you like to verify (enter in numerical values)";
        } while ((!(getValidDouble(transaction))));
        BubbleSort(rich, rich.actions);
        int result = binarySearch(rich, 0, rich.actions - 1, transaction);
        cout << result;
        if (result == -1)
          cout << "\nTransaction not verified. You did not receive $" << transaction << " during your visit.";
        else
          cout << "\nTransaction verified. You have received $" << transaction << " during your visit.";

        cout << "\nAll transactions:";
        for (int i = 0; i < rich.actions; i++) {
          cout << "\n" << rich.bets[i];
        }
      }
      }
  }
  if (rich.balance <= 0) {
    cout << "\nIt smells like broke in here. GET OUTTA THE TRAIN";
    return 0;
  }
}

void BubbleSort(casino &rich, int &numLength)
  {
    int i, j, flag = 1; // set flag to 1 to start first pass
    double temp; // holding variable
    for(i = 1; (i <= numLength) && flag; i++)
       {
          flag = 0;
          for (j=0; j < (numLength -1); j++)
            {
              if (rich.bets[j+1] < rich.bets[j])// ascending order simply changes to <
                { 
                  temp = rich.bets[j];// swap elements
                  rich.bets[j] = rich.bets[j+1];
                  rich.bets[j+1] = temp;
                  flag = 1; // indicates that a swap occurred.
                }
            }
       }
  } 

int binarySearch(casino rich,int lower, int upper, double x)
  {
    if (upper >= lower) 
      {
        int mid = lower + (upper - lower) / 2;
 
        // If the element is present at the middle
        // itself
        if (rich.bets[mid] == x)
            return mid;
 
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (rich.bets[mid] > x)
            return binarySearch(rich, lower, mid - 1, x);
 
        // Else the element can only be present
        // in right subarray
        if (rich.bets[mid] < x)
            return binarySearch(rich, mid + 1, upper, x);
      }
 
    // We reach here when element is not
    // present in array
    return -1;
  }

// HIGHER OR LOWER
void highOrLow(casino &rich) {
  string HorL, round = "y", dummy;
while(rich.balance > 0 && (round == "y" || round == "Y")){
  cout << "\n\n\nTHIS IS HIGHER OR LOWER!!";
  cout << "\nIn this game you have to guess if the next number will be higher or lower than the previous number";
  cout << "\nThe numbers range from 1 - 21 and you can cash out whenever you want, but the longer you go the more money you get!";

  srand((unsigned)time(0));
  int card1 = (rand() % 21) + 1;
  int card2 = (rand() % 21) + 1;
  
  cout << "\nThe first number is: " << card1;
  cout << "\nH or L? ";
  cin >> HorL;

  if(HorL == "h"|| HorL == "H"){
    if(card1 < card2){
      cout << "\nYOU GOT IT RIGHT! CONGRATS!";
      cout << "\n$1000 has been added to your account.";
      rich.balance = rich.balance + 1000;
      rich.bets.push_back(1000);
      rich.actions++;
    }
    else if(card1 > card2){
      cout << "\nOh how unfortunate. You were wrong";
      cout << "\n$1000 has been taken out of your account.";
      rich.balance = rich.balance - 1000;
      rich.bets.push_back(-1000);
      rich.actions++;
    }
    else{
      cout << "\nThe two numbers are the same.";
      cout << "\nYou will be rewarded $500";
      cout << "\n$500 have been added to your account";
      rich.balance = rich.balance + 500;
      rich.bets.push_back(500);
      rich.actions++;
    }
  }
  else if(HorL == "l" || HorL == "L"){
    if(card1 > card2){
      cout << "\nYOU GOT IT RIGHT! CONGRATS!";
      cout << "\n$1000 has been added to your account.";
      rich.balance = rich.balance + 1000;
      rich.bets.push_back(1000);
      rich.actions++;
    }
    else if(card1 < card2){
      cout << "\nOh how unfortunate. You were wrong";
      cout << "\n$1000 has been taken out of your account.";
      rich.balance = rich.balance - 1000;
      rich.bets.push_back(-1000);
      rich.actions++;
    }
    else{
      cout << "\nThe two numbers are the same.";
      cout << "\nYou will be rewarded $500";
      cout << "\n$500 have been added to your account";
      rich.balance = rich.balance + 500;
      rich.bets.push_back(500);
      rich.actions++;
    }
  }
  else{
    cout << "\nAnswer with H,h,L, or l.";
  }

  cout << "\nWould you like to play another round? (y/n) ";
  cin >> round;
  getline(cin, dummy);
  }
  if (rich.balance <= 0)
  cout << "\nYou have run out of money. Bye Bye!";
}

// THE GUESSING GAME
void guessingGame(casino &rich) {
  srand((unsigned)time(0));
  string another = "y", dummy;
  double betWon;
  while ((another == "y" || another == "Y") && rich.balance > 0) {
    cout << "\n\n\nTHIS IS THE NUMBER GUESSING GAME!";
    int random1 = (rand() % 25) + 1;
    int random2 = (rand() % 50) + 1;
    int random3 = (rand() % 100) + 1;
    
    do {
      cout << "\nWhat would you like the range to be " << rich.name << "?";
      cout << "\n1.) 1-25 (1.5x)";
      cout << "\n2.) 1-50 (2x)";
      cout << "\n3.) 1-100 (3x)\n";
    } while ((!(getValidInt(rich.mode)) || (rich.mode > 3) || (rich.mode < 1)));

    if (rich.mode == 1) {
      cout << "\nOnly 1-25? Come on lets raise the stakes! Whatever.";
      do {
        cout << "\nHow much are you willing to bet? ";
      } while ((!(getValidDouble(rich.wager)) || (rich.wager > rich.balance) || (rich.wager < 1)));

      do {
        cout << "\nPick a number. ";
      } while ((!(getValidInt(rich.guess)) || (rich.guess > 25) ||
                (rich.guess < 1)));

      if (rich.guess == random1) {
        cout << "\nHOLY SMOKES! CONGRATULATIONS YOU HAVE WON!!";
        betWon = rich.wager * 1.5;
        rich.balance = rich.balance + (rich.wager * 1.5);
        cout << "\n$" << rich.wager * 1.5 << " has been added to your account. Wanna play another? (y/n) ";
        rich.bets.push_back(betWon);
        rich.actions++;
        cin >> another;
        getline(cin, dummy);
      } else{
        rich.balance = rich.balance - (rich.wager * 1.5);
      cout << "\nOh how unfortunate " << rich.name << ". You have lost. $"
           << rich.wager * 1.5
           << " has been removed from your account. Wanna play another? (y/n)";
        rich.bets.push_back(0 - (rich.wager * 1.5));
        rich.actions++;
      cin >> another;
      getline(cin, dummy);
      }
    } else if (rich.mode == 2) {
      cout
          << "\n1-50? I'll take it. I would've like for you to go higher though.";
      do {
        cout << "\nHow much are you willing to bet? ";
      } while ((!(getValidDouble(rich.wager)) || (rich.wager > rich.balance) || (rich.wager < 1)));

      do {
        cout << "\nPick a number.";
      } while ((!(getValidInt(rich.guess)) || (rich.guess > 50) || (rich.guess < 1)));

      if (rich.guess == random2) {
        cout << "\nHOLY SMOKES! CONGRATULATIONS YOU HAVE WON!!";
        rich.balance = rich.balance + (rich.wager * 2);
        cout << "\n$" << rich.wager * 2 << " has been added to your account. Wanna play another? (y/n) ";
        rich.bets.push_back(rich.wager * 2);
        rich.actions++;
      } else {
        rich.balance = rich.balance - (rich.wager * 2);
        cout
            << "\nChose the middle option as a mid player, " << rich.name << ". You have lost. $" << rich.wager * 2
            << " has been removed from your account. Wanna play another? (y/n)";
        rich.bets.push_back(0 - (rich.wager * 2));
        rich.actions++;
        cin >> another;
        getline(cin, dummy);
      }

    } else if (rich.mode == 3) {
      cout << "\n1-100! Thats what I'm talking about!";
      do {
        cout << "\nHow much are you willing to bet? ";
      } while ((!(getValidDouble(rich.wager)) || (rich.wager > rich.balance) || (rich.wager < 1)));

      do {
        cout << "\nPick a number.";
      } while ((!(getValidInt(rich.guess)) || (rich.guess > 100) ||
                (rich.guess < 1)));

      if (rich.guess == random3) {
        cout << "\nBY THE NAME OF JAH! CONGRATULATIONS YOU HAVE WON!!";
        rich.balance = rich.balance + (rich.wager * 3);
        cout << "\n$" << rich.wager * 3 << " has been added to your account.";
        rich.bets.push_back(rich.wager * 3);
        rich.actions++;
      } else {
        rich.balance = rich.balance - (rich.wager * 3);
        cout
            << "\nI mean did you really not see this coming, " << rich.name << "? You have lost. $"
            << rich.wager * 3
            << " has been removed from your account. Wanna play another? (y/n) ";
        rich.bets.push_back(0 - (rich.wager * 3));
        rich.actions++;
        cin >> another;
        getline(cin, dummy);
      }
    }
  } 
  if (rich.balance <= 0)
  cout << "\nYou have run out of money. Bye Bye!";
}