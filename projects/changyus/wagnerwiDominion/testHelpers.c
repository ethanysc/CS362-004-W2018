#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "dominion.h"

// set true to get more detailed debugging output
int VERBOSE = 1;

int NUM_CARDS = treasure_map + 1;

void printCards(struct gameState *game, int player){
	printf("Player %d's hand is: ", player);
	for (int i = 0; i < game->handCount[player]; i++){
		int card = game->hand[player][i];
		switch(card){
			case curse:
				printf("curse, ");
			break;
			case estate:
				printf("estate, ");
			break;
			case duchy:
				printf("duchy, ");
			break;
			case province:
				printf("province, ");
			break;
			case copper:
				printf("copper, ");
			break;
			case silver:
				printf("silver, ");
			break;
			case gold:
				printf("gold, ");
			break;
			case adventurer:
				printf("adventurer, ");
			break;
			case council_room:
				printf("council_room, ");
			break;
			case feast:
				printf("feast, ");
			break;
			case gardens:
				printf("gardens, ");
			break;
			case mine:
				printf("mine, ");
			break; 
			case remodel:
				printf("remodel, ");
			break;
			case smithy:
				printf("smithy, ");
			break;
			case village:
				printf("village, ");
			break;
			case baron:
				printf("baron, ");
			break;
			case great_hall:
				printf("great_hall, ");
			break;
			case minion:
				printf("minion, ");
			break;
			case steward:
				printf("steward, ");
			break;
			case tribute:
				printf("tribute, ");
			break;
			case ambassador:
				printf("ambassador, ");
			break;
			case cutpurse:
				printf("cutpurse, ");
			break;
			case embargo:
				printf("embargo, ");
			break;
			case outpost:
				printf("outpost, ");
			break;
			case salvager:
				printf("salvager, ");
			break;
			case sea_hag:
				printf("sea_hag, ");
			break;
			case treasure_map:
				printf("treasure_map, ");
			break;
		}
	}
	printf(".\n");
}

void copyArray(int *current, int *new, int len){
	for (int i = 0; i < len; i++){
		new[i] = current[i];
	}
}

void copyGameState(struct gameState *game, struct gameState *save){
	save->numPlayers = game->numPlayers;
	copyArray(game->supplyCount, save->supplyCount, NUM_CARDS);
	copyArray(save->embargoTokens, game->embargoTokens, NUM_CARDS);
	save->outpostPlayed = game->outpostPlayed;
	save->outpostTurn = game->outpostTurn;
	save->whoseTurn = game->whoseTurn;
	save->phase = game->phase;
	save->numActions = game->numActions;
	save->coins = game->coins;
	save->numBuys = game->numBuys;
	copyArray(game->handCount, save->handCount, game->numPlayers);
	copyArray(game->deckCount, save->deckCount, game->numPlayers);
	copyArray(game->discardCount, save->discardCount, game->numPlayers);
	copyArray(game->playedCards, save->playedCards, MAX_DECK);
	save->playedCardCount = game->playedCardCount;
	
	for (int i = 0; i < game->numPlayers; i++){
		copyArray(game->hand[i], save->hand[i], MAX_HAND);
		copyArray(game->discard[i], save->discard[i], MAX_DECK);
		copyArray(game->deck[i], save->deck[i], MAX_DECK);
	}
}

void assertEqual(int x, int y, char *message){
	if (x != y){
		printf("%s", message);
	}
}

int equal(int x, int y){
	if (x != y){
		return 0;
	}
	return 1;
}

int setupRandomPlayerWithCard(struct gameState *game, int card){
	// sets a random player as current turn, and puts the card at a random position in their hand.
	int player = rand() % game->numPlayers;
	game->whoseTurn = player;
	for (; game->handCount[player] < 5; ){
		drawCard(player, game);
	}
	int handPosition = rand() % game->handCount[player];
	game->handCount[player]++;
	for (int i = game->handCount[player] - 1; i > handPosition; i--){
		game->hand[player][i] = game->hand[player][i-1];
	}
	game->hand[player][handPosition] = card;
	
	return handPosition;
}

void assertTrue(int val, char *message){
	if (!val){
		printf("%s", message);
	}
}

void randomKingdomCards(int *cards){
	int maxKingdoms = 10;
	int assigned;
	int curCard = (int) rand() % NUM_CARDS;
	for (assigned = 0; assigned < maxKingdoms && curCard < NUM_CARDS; assigned++, curCard++){
		cards[assigned] = curCard;
	}
	if (assigned < maxKingdoms){
		for (curCard = 0; assigned < maxKingdoms && curCard < NUM_CARDS; assigned++, curCard++){
			cards[assigned] = curCard;
		}
	}
}

void randomizeGameState(struct gameState *game, int seed){
	// NOTE: call srand BEFORE this function and pass it any game
	// Setup an initial game
	int numPlayers = (rand() % (MAX_PLAYERS - 2)) + 2; // minimum of 2 players
	int numKingdomCards = 10;
	int kingdomCards[numKingdomCards];
	randomKingdomCards( (int *) kingdomCards);
	initializeGame(numPlayers, kingdomCards, seed, game);
	
	// created a weighted value for trash and discards for deciding where to put cards
	int discardWeight = 1.0;
	int discardCount = (int) round(discardWeight * game->numPlayers);
	int trashWeight = 1.0;
	int trashCount = (int) round(trashWeight * game->numPlayers);
	int totalCount = game->numPlayers + discardCount + trashCount;
	
	// spread a random selection of kingdom cards across player hands, discards and trash
	for (int i = 0; i < numKingdomCards; i++){
		
		int currentCard = kingdomCards[i];
		int countCurrentCard = game->supplyCount[currentCard];
		int cardsToPlay = rand() % countCurrentCard;
		game->supplyCount[currentCard] -= cardsToPlay;
		
		// randomize this particular card across hands, discards, and trash
		for (int j = 0; j < cardsToPlay; j++){
			int placement = rand() % totalCount;
			int player = rand() % game->numPlayers;
			
			if (placement < game->numPlayers){
				// place in player hand
				game->hand[player][game->handCount[player]] = currentCard;
				game->handCount[player]++;
			}
			else if (placement >= game->numPlayers && placement < game->numPlayers + discardWeight){
				// place in player discard
				game->discard[player][game->discardCount[player]] = currentCard;
				game->discardCount[player]++;
			}
			// else placement >= game->numPlayers + discardWeight and it just disappears
		}
	}
	
	// set current turn to a random player
	game->whoseTurn = rand() % game->numPlayers;
	
	// possible additions: randomize numActions, numBuys
}

void printArray(int *arr, int size){
	if (!VERBOSE) return;
	for (int i = 0; i < size; i++){
		printf("%d, ", arr[i]);
	}
	printf("\n");
}

int runTests(int card, int (*checkFunction)(struct gameState *, struct gameState *), int numTests){
	int passed = 0;
	//int testSeeds[numTests];
	
	for (int i = 0; i < numTests; i++){
		// test adventurer
		int seed = time(NULL);
		//testSeeds[i] = seed;
		srand(seed);
		
		// create a new randomized game state
		struct gameState game; 
		randomizeGameState(&game, seed);
		
		// give a player the card 
		int handPosition = setupRandomPlayerWithCard(&game, card);
		
		// save game state
		struct gameState save;
		copyGameState(&game, &save);
		
		// play the card
		cardEffect(card, 0, 0, 0, &game, handPosition, 0);
		
		// check on adventurer
		if (checkFunction(&game, &save)){
			passed += 1;
		}
	}
	
	return passed;
}