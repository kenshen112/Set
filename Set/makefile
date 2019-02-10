###############################################################
# Program:
#     Assignment 05, SET
#     Brother Kirby, CS235
# Author:
#     Kenyon Bunker
#     Tim O'Barr
# Summary:
#     Go fish game powered by a custom Set
# Time:
#     Paired: 8
#     Kenyon: 5
#     Tim:    5
# The hardest part:
#     Kenyon: I struggled with inserting onto the front. The
#        math and if statements for indexFront was difficult.
#     Tim: Same thing but just insert in general.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment05.o goFish.o card.o
	g++ -o a.out assignment05.o goFish.o card.o -std=c++11
	tar -cf assignment05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment05.o : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
assignment05.o: set.h goFish.h assignment05.cpp
	g++ -c assignment05.cpp -std=c++11

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -c goFish.cpp -std=c++11

card.o: card.h card.cpp
	g++ -c card.cpp  -std=c++11
