/***********************************************************************
* Header:
*    Go Fish
* Summary:
*    This will contain just the prototype for the goFish() function
* Author
*    <your names here>
************************************************************************/

#ifndef GO_FISH_H
#define GO_FISH_H
#include "card.h"
#include <set>
using std::set;  //For testing goFish. DIsable before submition

//prototype functions
void goFish();                         //Main Game
void testCard(Card card, int round,
   set<Card> hand, int matches);       //Tests the card against the hand
set<Card> getHand();                   //gets the hand from file

#endif // GO_FISH_H

