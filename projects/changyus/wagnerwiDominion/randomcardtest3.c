#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "testHelpers.c"
#include "dominion.h"

int checkSmithy(struct gameState *game, struct gameState *save){
	
	// determine whether smithy has been played correctly
	int valid = 1;
	
	// test elements
	// one card played, player 0 has discards but no other players do
	valid =  valid ? equal(game->playedCardCount, 1) : valid;
	valid =  valid ? equal(game->discardCount[0], 1) : valid;
	for (int i = 1; i < game->numPlayers; i++){
		valid =  valid ? equal(game->discardCount[i], 0) : valid;
	}
	
	// current player receives 3 cards - hand is larger by 2
	valid =  valid ? equal(game->handCount[0], save->handCount[0] + 2) : valid;
	
	// 3 cards come from player's own pile
	valid =  valid ? equal(game->deckCount[0], save->deckCount[0] - 3) : valid;
	
	// other player's decks stay the same
	for (int i = 0; i < game->numPlayers; i++){
		if (i != game->whoseTurn){
			valid = valid ? equal(game->deckCount[i], save->deckCount[i]) : valid;
		}
	}
	
	// all general card piles stay the same
	for (int i = 0; i < NUM_CARDS; i++){
		valid =  valid ? equal(game->supplyCount[i], save->supplyCount[i]) : valid;
	}
	
	return valid;
}

int main(){
	int numTests = 1000;
	int (*checkFunc)(struct gameState *, struct gameState *) = checkSmithy;
	int passed = runTests(smithy, checkFunc, numTests);
	printf("Smithy passed %d/%d fuzzed attempts.\n", passed, numTests);
	
	return 0;
}