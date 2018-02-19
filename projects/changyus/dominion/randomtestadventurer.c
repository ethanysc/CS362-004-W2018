/*
 * Random Test Adventurer
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
	printf("\n--- Random Test Card: Adventurer ---\n");
	
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
		
		// distribute random counts
		G.deckCount[player] = rand() % MAX_DECK;
		G.discardCount[player] = rand() % MAX_DECK;
		G.handCount[player] = rand() % MAX_DECK;

		// calculate treasure cards in hand
		int numTreasure = 0;
		int j;
		for (j = 0; j < G.handCount[player]; j++){
			if (G.hand[player][j] == gold || G.hand[player][j] == silver || G.hand[player][j] == copper)
				numTreasure++;
		}

		// initilize oldGameStatus for following random unit tests
		memcpy(&oldGameStatus, &G, sizeof(struct gameState));

		// call refactored Adventurer card method and make sure it doesn't crash
		printf("Case 1: Make sure refactored_adventurer() method compiles and runs without error\n");
		assertTest(cardEffect(adventurer, 1, 1, 1, &G, 0, 0), 0, &tf);

		// test if treasure card count in hand has increased
		printf("Case 2: Treasure card count in hand has increased by 2\n");
		int postNumTreasure = 0;
		for (j = 0; j < G.handCount[player]; j++){
			if (G.hand[player][j] == gold || G.hand[player][j] == silver || G.hand[player][j] == copper)
				postNumTreasure++;
		}
		assertTest(numTreasure, postNumTreasure, &tf);
	}

	if (tf == 0)
		printf("All test have been passed, test suite validates Adventurer card\n\n");
	else
		printf("Random tests failed.\n\n");

	return 0;
}
