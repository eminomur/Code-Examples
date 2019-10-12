#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>

#define INIT 0

#define GO_UP 1
#define GO_DOWN 2
#define TRUE_ROW 3

#define GO_LEFT -1
#define GO_RIGHT -2
#define TRUE_COLUMN -3

#define GUESS_MARK 'G'
#define TARGET_MARK 'T'
#define CORRECT_MARK 'C'

pid_t process_to_choose_a_point;

int
main(void)
{
	int status;
	int real_row, guess_row;
	int real_column, guess_column;
	FILE *coor_inp_txt;
	FILE *prev_coor_outp_txt;
	int row_check, column_check;
	int i, j, ct_guess;
	int temp;

	/*
	 * A new process is created
	 */
	process_to_choose_a_point = fork();

	if (process_to_choose_a_point < 0) {
		printf("*** Error Creating The New Process ***\n");
		
		exit(EXIT_FAILURE);
	} else if (process_to_choose_a_point == 0) {
		/*
		 * This part includes child process' duty
		 * Just calling execl() function
		 *
		 * You should firstly compile "choose a point" program
		 * then delete "run_choose_a_point" parts and write your own
		 * program's name
		 */
		execl("run_choose_a_point", "run_choose_a_point", NULL);
	} else {
		/*
		 * This part is about parent process
		 *
		 * Thanks to wait() function parent process will wait
		 * until child process ends
		 */
		process_to_choose_a_point = wait(&status);

		coor_inp_txt = fopen("position.txt", "r");

		if (coor_inp_txt == NULL) {
			printf("*** Error Opening File ***\n");
			exit(EXIT_FAILURE);
		}

		fscanf(coor_inp_txt, "%d%d", &real_row, &real_column);

		fclose(coor_inp_txt);

		prev_coor_outp_txt = fopen("previous guesses.txt", "w");

		if (prev_coor_outp_txt == NULL) {
			printf("*** Error Opening File ***\n");
			exit(EXIT_FAILURE);
		}

		for (row_check = INIT, column_check = INIT, ct_guess = 1;
		     row_check != TRUE_ROW || column_check != TRUE_COLUMN;
		     ++ct_guess) {
#if defined (WIN32) || (WIN64)
			system("cls");
#elif defined (linux)
			system("clear");
#endif

			if (row_check == GO_UP) {
                guess_row = rand() % guess_row + 1;
			} else if (row_check == GO_DOWN) {
				guess_row = guess_row + (rand() % (30 - guess_row)) + 1;
			} else if (row_check == INIT) {
				guess_row = rand() % 30 + 1;
			}
			
			if (column_check == GO_LEFT) {
                guess_column = rand() % guess_column + 1;
			} else if (column_check == GO_RIGHT) {
				guess_column = guess_column + (rand() % (30 - guess_column)) + 1;
			} else if (column_check == INIT) {
				guess_column = rand() % 30 + 1;
			}

			for (i = 0; i < 32; ++i) {
				for (j = 0; j < 32; ++j) {
					if (i == 0 || i == 31 || j == 0 || j == 31) {
						printf("*");
					} else if ((guess_row == real_row && i == guess_row) &&
					   	   (guess_column == real_column && j == guess_column)) {
						printf("%c", CORRECT_MARK);
					} else if (i == real_row && j == real_column) {
						printf("%c", TARGET_MARK);
					} else if (i == guess_row && j == guess_column) {
						printf("%c", GUESS_MARK);
					} else {
						printf("%c", ' ');
					}
				}
				printf("\n");
			}

			fprintf(prev_coor_outp_txt, "Guess: %d\n", ct_guess);
			fprintf(prev_coor_outp_txt, "Row Guess: %d\n", guess_row);
			fprintf(prev_coor_outp_txt, "Column Guess: %d\n\n", guess_column);

			if ((guess_row == real_row) && (guess_column == real_column)) {
				row_check = TRUE_ROW;
				column_check = TRUE_COLUMN;

				printf("\n\nAfter %d guesses, row and column are correctly guessed.\n", ct_guess);

				continue;
			}

			if (guess_row < real_row) {
				row_check = GO_DOWN;
			} else if (guess_row > real_row) {
				row_check = GO_UP;
			} else {
				row_check = TRUE_ROW;
			}

			if (guess_column < real_column) {
				column_check = GO_RIGHT;
			} else if (guess_column > real_column) {
				column_check = GO_LEFT;
			} else {
				column_check = TRUE_COLUMN;
			}

			sleep(1);
		}

		fclose(prev_coor_outp_txt);
	}

	return (0);
}
