#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	sleep(5);
	for (int i = 0; i < 10; i++) {
		printf("num is %d", i);
	}
	return 0;
}
