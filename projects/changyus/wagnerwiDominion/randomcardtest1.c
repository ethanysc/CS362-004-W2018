#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "testHelpers.c"

int checkAdventurer(struct gameState *game, struct gameState *save){
	
	// determine whether adventurer has been played correctly
	int valid = 1;
	
	// test elements
	valid =  valid ? equal(game->playedCardCount, save->playedCardCount + 1) : valid;
	valid =  valid ? equal(game->discardCount[game->whoseTurn], save->discardCount[game->whoseTurn] + 2) : valid;
	for (int i = 0; i < game->numPlayers; i++){
		if (i != game->whoseTurn){
			valid =  valid ? equal(game->discardCount[i], save->discardCount[i]) : valid;
		}
	}
	
	// current player hand is larger by 1 after drawing 2 more copper
	valid =  valid ? equal(game->handCount[0], save->handCount[0] - 1) : valid;
	
	// Deck is empty because it hasn't needed shuffling
	valid =  valid ? equal(game->deckCount[0], 0) : valid;
	
	// other player's decks stay the same
	for (int i = 1; i < game->numPlayers; i++){
		valid =  valid ? equal(game->deckCount[i], save->deckCount[i]) : valid;
	}
	
	// all general card piles stay the same
	for (int i = 0; i < NUM_CARDS; i++){
		valid = valid ? equal(game->supplyCount[i], save->supplyCount[i]) : valid;
	}
	
	return valid;
}

int main(){
	int numTests = 100000;
	int (*checkFunc)(struct gameState *, struct gameState *) = checkAdventurer;
	int passed = runTests(adventurer, checkFunc, numTests);
	printf("Adventurer passed %d/%d fuzzed attempts.\n", passed, numTests);
	
	return 0;
}