/***********************************************************************
* Header:
*    Go Fish
* Summary:
*    This will contains the prototypes for the functions to play go fish
* Author
*    Kenyon Bunker and Tim O'Barr
************************************************************************/

#ifndef GO_FISH_H
#define GO_FISH_H
#include "card.h"
#include "set.h"
using namespace custom;

//prototype functions
void goFish();                         //Main Game
void testCard(Card card, int round,
   set<Card> hand, int matches);       //Tests the card against the hand
set<Card> getHand();                   //gets the hand from file

#endif // GO_FISH_H

