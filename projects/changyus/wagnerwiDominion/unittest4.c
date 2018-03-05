/*
 * This unit test examines the numHandCards method in dominion.c
 * Function header as such:
 * int numHandCards(strcut gameState *state);
 * */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"

// assert function
void assertTest(int a, int b, int *tf){
	if (a == b)
		printf("Test PASSED!!\n");
	else{
		printf("Test FAILED!!\n");
		*tf = 1;
	}
}

// test suite
int main(){

	// initialize random game variables
	struct gameState G;
	int seed = 52;
	int k[] = {adventurer, council_room, gardens, mine, smithy,
				village, baron, great_hall, minion, ambassador};
	int playerCount = 2;
	initializeGame(playerCount, k, seed, &G);
	int tf = 0;
	
	// run tests
	printf("Testing numHandCards()\n");
	printf("Case 1: After initializing game, player should have 5 cards on hand\n");
	assertTest(numHandCards(&G), 5, &tf);

	printf("Case 2: Add one to player handCount, player should have 6 cards on hand\n");
	G.handCount[0]++;
	assertTest(numHandCards(&G), 6, &tf);

	if (tf == 0)
		printf("All test have been passed, test suite validates numHandCards()\n\n");
	else
		printf("Unit tests failed.\n\n");
	
	return 0;
}
