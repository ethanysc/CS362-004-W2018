/*
 * This unit test examines the updateCoins method in dominion.c
 * Function header as such:
 * int updateCoins(int player, struct gameState *state, int bonus);
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
	int cards[] = {adventurer, council_room, gardens, mine, smithy,
				village, baron, great_hall, minion, ambassador};
	int playerCount = 2;
	int playerIndex = 0;
	int bonus = 0;
	initializeGame(playerCount, cards, seed, &G);
	int tf = 0;
	
	// run tests
	printf("Testing updateCoins()\n");
	printf("Case 1: Updating coins right after initialized game, Should have less than 16 coins\n");
	// highest possible: 16 coins = 5 cards * 3 gold value = 15
	assertTest(updateCoins(playerIndex, &G, bonus), 0, &tf);

	printf("Case 2: Updating coins when player 1 adds 1 gold, 1 silver, and 1 copper, and 1 bonus\n");
	G.hand[playerIndex][0] = gold;
	G.hand[playerIndex][1] = silver;
	G.hand[playerIndex][2] = copper;
	G.hand[playerIndex][3] = adventurer;
	G.hand[playerIndex][4] = baron;
	bonus = 1;
	assertTest(updateCoins(playerIndex, &G, bonus), 7, &tf);

	if (tf == 0)
		printf("All test have been passed, test suite validates updateCoins()\n\n");
	else
		printf("Unit tests failed.\n\n");
	
	return 0;
}
