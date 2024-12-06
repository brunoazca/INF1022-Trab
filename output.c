#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int resultado = 1.800000;
	if(	resultado	) {
		for (int i = 0; i < 9; i++) {
			resultado *= 2.900000;
		}
	}
	printf("Mostrando resultado: %d\n", resultado);

	return 0;
}