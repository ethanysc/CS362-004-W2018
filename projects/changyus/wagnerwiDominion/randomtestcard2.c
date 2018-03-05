/*
 * Random Test Salvager
 * */
 
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
	printf("\n--- Random Test Card: Salvager ---\n");
	
	// static game variables
	int cards[] = {adventurer, council_room, gardens, mine, smithy,
					village, baron, great_hall, minion, salvager};
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

		// call refactored Adventurer card method and make sure it doesn't crash
		printf("Case 1: Make sure refactored_salvager() method compiles and runs without error\n");
		assertTest(cardEffect(salvager, 1, -1, -1, &G, 0, 0), 0, &tf);

		// if choice 1 = 1, test if coins has increased by value of discarded
		// card
		printf("Case 2: Choice 1 = 1, gain coin value of discarded card\n");
		assertTest(G.coins, oldGameStatus.coins + getCost(handCard(1, &oldGameStatus)), &tf);

		// if choice 1 = 1, test if numBuys increased by 1
		printf("Case 3: Choice 1 = 1, NumBuys increased by 1\n");
		assertTest(G.numBuys, oldGameStatus.numBuys + 1, &tf);

		// if choice 1 = 0, test if coins stayed the same
		memcpy(&oldGameStatus, &G, sizeof(struct gameState));
		cardEffect(salvager, 0, -1, -1, &G, 0, 0);
		printf("Case 4: Choice 1 = 0, coins remained the same\n");
		assertTest(G.coins, oldGameStatus.coins, &tf);
		
		// if choice 1 = 0, test if numBuys increased by 1
		printf("Case 5: Choice 1 = 0, NumBuys increased by 1\n");
		assertTest(G.numBuys, oldGameStatus.numBuys + 1, &tf);

	}

	if (tf == 0)
		printf("All test have been passed, test suite validates Village card\n\n");
	else
		printf("Random tests failed.\n\n");

	return 0;
}
