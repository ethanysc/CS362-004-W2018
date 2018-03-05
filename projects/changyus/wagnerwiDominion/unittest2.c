/*
 * This unit test examines the getCost() method in dominion.c
 * Function header as such:
 * int getCost(int cardNumber);
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

	// run tests
	int tf = 0;
	printf("Testing getCost()\n");
	printf("Case 1: cardNumber = 0 ");
	assertTest(getCost(0), 0, &tf);
	printf("Case 2: cardNumber = 1 ");
	assertTest(getCost(1), 2, &tf);
	printf("Case 3: cardNumber = 2 ");
	assertTest(getCost(2), 5, &tf);
	printf("Case 4: cardNumber = 3 ");
	assertTest(getCost(3), 8, &tf);
	printf("Case 5: cardNumber = 4 ");
	assertTest(getCost(4), 0, &tf);
	printf("Case 6: cardNumber = 5 ");
	assertTest(getCost(5), 3, &tf);
	printf("Case 7: cardNumber = 6 ");
	assertTest(getCost(6), 6, &tf);
	printf("Case 8: cardNumber = 7 ");
	assertTest(getCost(7), 6, &tf);
	printf("Case 9: cardNumber = 8 ");
	assertTest(getCost(8), 5, &tf);
	printf("Case 10: cardNumber = 9 ");
	assertTest(getCost(9), 4, &tf);
	printf("Case 11: cardNumber = 10 ");
	assertTest(getCost(10), 4, &tf);
	printf("Case 12: cardNumber = 11 ");
	assertTest(getCost(11), 5, &tf);
	printf("Case 13: cardNumber = 12 ");
	assertTest(getCost(12), 4, &tf);
	printf("Case 14: cardNumber = 13 ");
	assertTest(getCost(13), 4, &tf);
	printf("Case 15: cardNumber = 14 ");
	assertTest(getCost(14), 3, &tf);
	printf("Case 16: cardNumber = 15 ");
	assertTest(getCost(15), 4, &tf);
	printf("Case 17: cardNumber = 16 ");
	assertTest(getCost(16), 3, &tf);
	printf("Case 18: cardNumber = 17 ");
	assertTest(getCost(17), 5, &tf);
	printf("Case 19: cardNumber = 18 ");
	assertTest(getCost(18), 3, &tf);
	printf("Case 20: cardNumber = 19 ");
	assertTest(getCost(19), 5, &tf);
	printf("Case 21: cardNumber = 20 ");
	assertTest(getCost(20), 3, &tf);
	printf("Case 22: cardNumber = 21 ");
	assertTest(getCost(21), 4, &tf);
	printf("Case 23: cardNumber = 22 ");
	assertTest(getCost(22), 2, &tf);
	printf("Case 24: cardNumber = 23 ");
	assertTest(getCost(23), 5, &tf);
	printf("Case 25: cardNumber = 24 ");
	assertTest(getCost(24), 4, &tf);
	printf("Case 26: cardNumber = 25 ");
	assertTest(getCost(25), 4, &tf);
	printf("Case 27: cardNumber = 26 ");
	assertTest(getCost(26), 4, &tf);

	if (tf == 0)
		printf("All test have been passed, test suite validates getCost()\n\n");
else
		printf("Unit tests failed.\n\n");
	
	return 0;
}
