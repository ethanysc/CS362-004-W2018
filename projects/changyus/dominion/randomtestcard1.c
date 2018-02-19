/*
 * Random Test Village (tested in Assignment 3)
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define NUM_TEST 100

// custom assert function
void assertTest(int a, int b, int* tf){
	if (a == b)
		printf("Test PASSED!!\n");
	else {
		printf("Test FAILED!!\n");
		*tf = 1;
	}
}

int main(){

	// print testing card
	printf("\n--- Random Test Card: Village ---\n");
	
	// static game variables
	int cards[] = {adventurer, council_room, gardens, mine, smithy,
					village, baron, great_hall, minion, ambassador};
	int tf = 0;
	srand(time(NULL));
	int i;

	// start testing loop
	for (i = 0; i < NUM_TEST; i++){

		printf("#Random Test Run %d\n", i);
		// initialize game variables
		struct gameState G, oldGameStatus;
		int player = rand() % 3 + 2;
		
		// initialize game 
		int gameInit = initializeGame(player, cards, rand(), &G);
		
		// initilize oldGameStatus for following random unit tests
		memcpy(&oldGameStatus, &G, sizeof(struct gameState));

		// call refactored village card method and make sure it doesn't crash
		printf("Case 1: Make sure refactored_village() method compiles and runs without error\n");
		assertTest(cardEffect(village, -1, -1, -1, &G, 0, 0), 0, &tf);

		// test if number of actions has increased by 2
		printf("Case 2: Number of actinos has increased by 2\n");
		assertTest(G.numActions, oldGameStatus.numActions+ 2, &tf);
	}

	if (tf == 0)
		printf("All test have been passed, test suite validates Village card\n\n");
	else
		printf("Random tests failed.\n\n");

	return 0;
}
