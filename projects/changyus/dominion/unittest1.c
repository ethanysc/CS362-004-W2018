/*
 * This unit test examines the isGameOver method in dominion.c
 * Function header as such:
 * int isGameOver(struct gameState *state);
 * */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"

// assert function
void assertTest(int a, int b, int* tf){
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
	int pileCount = 25;

	// initialize all supply piles to 0 
	int i;
	for(i = 0; i < pileCount; i++)
		G.supplyCount[i] = 0;

	// run tests
	int tf = 0;
	printf("Testing isGameOver()\n");
	printf("Case 1: If Province card stack is empty\n");
	G.supplyCount[province] = 0;
	assertTest(isGameOver(&G), 1, &tf);

	printf("Case 2: If there's a Province card and all card piles have 1 card\n");
	for(i = 0; i < pileCount; i++)
		G.supplyCount[i] = 1;
	assertTest(isGameOver(&G), 0, &tf);

	printf("Case 3: If less than 3 piles are empty\n");
	G.supplyCount[0] = 0;
	G.supplyCount[1] = 0;
	assertTest(isGameOver(&G), 0, &tf);

	printf("Case 4: If 3 or more piles are empty\n");
	G.supplyCount[2] = 0;
	assertTest(isGameOver(&G), 1, &tf);

	if (tf == 0)
		printf("All test have been passed, test suite validates isGameOver()\n\n");
	else
		printf("Unit tests failed.\n\n");
	
	return 0;
}
