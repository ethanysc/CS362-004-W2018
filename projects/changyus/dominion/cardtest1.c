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

	//Expected smithy variables
	int newCards = 3;
	int playedCard = 1;
	
	//Check if current player drew three more cards to his hand
	printf("Case 1: Make sure refactored_smithy() method compiles and runs without fail\n");
	assertTest(cardEffect(smithy, -1, -1, -1, &G, 0, 0), 0, &tf); 

	//Check for the correct card effect: +3 cards -1 played card
	printf("Case 2: Play smithy card, +3 cards and discard card from hand\n");
	assertTest(oldGameStatus.handCount[currentPlayer] + newCards - playedCard, G.handCount[currentPlayer], &tf);

	//Check if 2nd card in hand of oldGameStatus is the first card in hand right
	//now
	printf("Case 3: Current card in hand should be the last card in hand before smithy was played\n");
	assertTest(oldGameStatus.hand[currentPlayer][oldGameStatus.handCount[currentPlayer]-1], G.hand[currentPlayer][0], &tf);

	//Check if card discarded is smithy
	printf("Case 4: Top card on discard pile for player 1 should be smithy\n");
	assertTest(G.playedCards[G.playedCardCount], smithy, &tf);

	if (tf == 0)
		printf("All test have been passed, test suite validates updateCoins()\n\n");
	else
		printf("Unit tests failed.\n\n");
	

	return 0;
}
