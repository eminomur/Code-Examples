/*
 * This program chooses a random point
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main(void)
{
	int row, column;
	FILE *out_txt;

	srand(time(NULL));

	row = rand() % 30 + 1;
	column = rand() % 30 + 1;

	out_txt = fopen("position.txt", "w");

	if (out_txt == NULL) {
		printf("*** Error creating file ***\n");
		exit(EXIT_FAILURE);
	}

	fprintf(out_txt, "%d\n%d", row, column);

	fclose(out_txt);

	return (0);
}
