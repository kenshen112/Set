/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>

//#include "set.h"
#include <set>
#include "card.h"
#include "goFish.h"
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
using std::set;  //For testing goFish. DIsable before submition
using std::ifstream;

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   //Card
   Card card;

   //Hand
   set<Card> hand = getHand();

   //counts the rounds
   int round = 0;

   //matches
   int matches = 0;

   //start prompt display
   cout << "We will play 5 rounds of Go Fish. Guess the card in the hand\n";
   do
   {
      cout << "round " << round + 1 << ": ";
      cin >> card;
      cout << endl;
      round++;
      testCard(card, round, hand, matches);
   } while (round < 5);
   return ;
}

/**********************************************************************
* GO FISH : testCard
* Pulls in the hand. checks to see if the card is in there
***********************************************************************/
void testCard(Card card, int round, set<Card> hand, int matches)
{
   set<Card>::iterator it = hand.find(card); //Searches hand for card

   if (it != hand.end())
   {
      cout << "You got a match!\n";
      hand.erase(it);
      matches++;
   }
   else
   {
      cout << "Go Fish!\n";
   }

   if (round >= 5)
   {
      set<Card>::iterator it2 = hand.begin();
      cout << "You have " << matches << " matches!\n";
      cout << "The remaining card: ";
      while (it2 != hand.end())
      {
         cout << (*it2) << ", ";
         it2++;
      }
      cout << endl;
   }
}

/**********************************************************************
* GO FISH : getHand
* Gets the hand from file
***********************************************************************/
set<Card> getHand()
{
   set <Card> hand;
   Card card;

   ifstream inputFile("hand.txt");        // Input file stream object
   if (inputFile.good())
   {
      //input to from file to card. insert to hand.
      while (inputFile >> card)
      {
         hand.insert(card);
      }
      // Close the file.
      inputFile.close();
   }
   //Error
   else
   {
      cout << "ERROR: Reading file error.";
   }
   return hand;
}
