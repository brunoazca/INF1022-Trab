#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int X = 10;
	if(	X	) {
		X = 30;
	}
	X = 10;
	for (int i = 0; i < 3; i++) {
		X = 100;
		if(	X	) {
			X = 30;
			X = 10;
			X = 30;
			X = 10;
		}
		printf("Mostrando 10\n");
	}

	return 0;
}