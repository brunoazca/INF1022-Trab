#include <stdio.h>
#include <stdlib.h>

int main(void) {
	if (1) {
	int X = 10;
	}
	printf("Mostrando X: %d\n", X);
	for (int i = 0; i < 5; i++) {
	X *= X;
	}
	
	return 0;
}