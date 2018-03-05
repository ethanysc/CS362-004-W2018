#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

// assert function
void assertTest(int a, int b, int* tf){
	if (a == b)
		printf("Test PASSED!!\n");
	else{
		printf("Test FAILED!!\n");
		*tf = 1;
	}
}

int main(){
	
	//Set up game and variables
	struct gameState G, oldGameStatus;
	int playerCount = 2;
	int currentPlayer = 0;
	int seed = 52;
	int cards[] = {adventurer, council_room, gardens, mine, smithy,
					village, baron, great_hall, minion, ambassador};
	int tf = 0;
	initializeGame(playerCount, cards, seed, &G);
	oldGameStatus = G;

	//Expected village variables
	int newCards = 1;
	int playedCard = 1;
	int actionInc = 2;
	
	//Check if current player drew three more cards to his hand
	printf("Case 1: Make sure refactored_village() method compiles and runs without fail\n");
	assertTest(cardEffect(village, -1, -1, -1, &G, 0, 0), 0, &tf); 

	//Check for the correct card drawing +1 and discarding -1
	printf("Case 2: Play village card, +1 card and discard card -1 from hand\n");
	assertTest(oldGameStatus.handCount[currentPlayer] + newCards - playedCard, G.handCount[currentPlayer], &tf);

	//Check if number of actions has been added +2
	printf("Case 3: Village card should +2 to the number of actions\n");
	assertTest(oldGameStatus.numActions + actionInc, G.numActions, &tf);

	//Check if card discarded is village
	printf("Case 4: Top card on discard pile for player 1 should be village\n");
	assertTest(G.playedCards[0], village, &tf);

	if (tf == 0)
		printf("All test have been passed, test suite validates updateCoins()\n\n");
	else
		printf("Unit tests failed.\n\n");
	

	return 0;
}
