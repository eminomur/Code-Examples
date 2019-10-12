/*
 * Even append mode is added
 * When you need to run program again, delete old copies of created files
 * Even files are opened in write mode, there is not a preventation for conflict
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct moves {
	int row_pos;	/* Row position */
	int col_pos;	/* Column position */
};

void search_mode(void);
void look_at_previous_guesses(void);
void draw_table(char move_list[]);
void delete_old_files(void);

int
main(void)
{
	int choice,		/* User's choice */
		status;		/* scanf status */
	
	printf("Hello There!\n");
	printf("\tEnter 1 to search possible solution\n");
	printf("\tEnter 2 to search file (if exist)\n");
	printf("\tEnter 3 to delete old files (if exist)\n");
	printf("> ");
	
	status = scanf("%d", &choice);
	
	if (status != 1) {
		printf("\n\tYou entered Wrong Input %c\n", getchar());
		exit(EXIT_FAILURE);
	} else {
		if (choice == 1) {
			search_mode();
		} else if (choice == 2) {
			look_at_previous_guesses();
		} else if (choice == 3) {
			delete_old_files();
		} else {
			printf("\n\tYou entered Wrong Input %d\n", choice);
			exit(EXIT_FAILURE);
		}
	}
	
	return (0);
}

void
search_mode(void)
{
	FILE *log_outp,						/* Creates log file */
		 *move_outp;					/* Creates files for every single turn */
	int ct,								/* Just a counter */
		random_char,					/* Variable to choose 'W' 'A' 'S' 'D' */
		file_ct = 1;					/* To give files a name */
	char move_arr[8],					/* Array to save 8 moves */
		 def_sit[6] = "fail",			/* Default situation */
		 file_name[15];					/* String to keep file name */
	int row_pos,						/* Current row position */
		col_pos;						/* Current column position */
	
	srand(time(NULL));
	
	log_outp = fopen("log.txt", "r");
	
	if (log_outp == NULL) {
		 /*
		  * So file does not exist
		  * Open in write mode
		  */
		log_outp = fopen("log.txt", "w");
	} else {
		/* If file exist then open it in append mode */
		log_outp = fopen("log.txt", "a");
	}
	
	if (log_outp == NULL) {
		printf("Error Opening \"log.txt\"\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Search has begun. It may take some time.\n");
	while (strcmp(def_sit, "fail") == 0) {
		sprintf(file_name, "%d.txt", file_ct);
		
		move_outp = fopen(file_name, "w");
		if (move_outp == NULL) {
			printf("Error opening %s\n", file_name);
			exit(EXIT_FAILURE);
		}
		
		for (ct = 0, row_pos = 0, col_pos = 0; 
		     ct < 8;
		     ++ct) {
			random_char = rand() % 4;
			if (random_char == 0) {
				/* Up					*/
				move_arr[ct] = 'W';
			} else if (random_char == 1) {
				/* Left					*/
				move_arr[ct] = 'A';
			} else if (random_char == 2) {
				/* Down					*/
				move_arr[ct] = 'S';
			} else if (random_char == 3) {
				/* Right				*/
				move_arr[ct] = 'D';
			}
			
			if (random_char == 0) {
				if (row_pos == 0) {
					/* Do not do anything */
				} else {
					/* Decrement row_pos */
					--row_pos;
				}
			} else if (random_char == 1) {
				if (col_pos == 0) {
					/* Do not do anything */
				} else {
					/* Decrement col_pos */
					--col_pos;
				}
			} else if (random_char == 2) {
				if (row_pos == 4) {
					/* Do not do anything */
				} else {
					/* Increment row_pos */
					++row_pos;
				}
			} else if (random_char == 3) {
				if (col_pos == 4) {
					/* Do not do anything */
				} else {
					/* Increment col_pos */
					++col_pos;
				}
			}
			
			fprintf(move_outp, "%c", move_arr[ct]);
		}
		
		if (row_pos == 4 && col_pos == 4) {
		    /* 
		     * If all correct moves are guessed
			 * then make def_sit "found"
			 */
			strcpy(def_sit, "found");
		}
		
		fprintf(log_outp, "%-10d %s\n", file_ct, def_sit);
		
		fclose(move_outp);
		
		++file_ct;
	}
	
	fclose(log_outp);
}

void
look_at_previous_guesses(void)
{
	/* This function won't work if there isn't a log file */
	FILE *look_at_log_file_inp,					/* Indicates whether an appropriate solution is found or not */
		 *open_move_file_inp;					/*
		 										 * If an appropriate solution is found in log file then open file
		 										 * then open file named with it
		 										 */
	char file_name[15],							/* Variable for file name */
		 found_or_not[6] = "fail",				/* Found or not */
		 move_list[8];							/* Holds move list */
	int file_number,							/* Indicatas the file number */
		status,									/* It is used to make search in file */
		ct;										/* Just an ordinary counter variable */
	
	look_at_log_file_inp = fopen("log.txt", "r");
	
	if (look_at_log_file_inp == NULL) {
		printf("*** \"log.txt\" does not exist ***\n");
		exit(EXIT_FAILURE);
	} else {
		/*
		 * This will not look for every successful situation
		 * but will look for first successful guess
		 * This might be solved later
		 */
		for (status = fscanf(look_at_log_file_inp, "%d%s", &file_number, found_or_not);
			 status == 2;
			 status = fscanf(look_at_log_file_inp, "%d%s", &file_number, found_or_not)) {
			if (strcmp(found_or_not, "found") == 0) {
				/* Break the loop when first found marked guess is found */
				break;
			}
		}
		
		if (strcmp(found_or_not, "fail") == 0) {
			printf("Appropriate solution could not found\n");
		} else {
			sprintf(file_name, "%d.txt", file_number);
			
			open_move_file_inp = fopen(file_name, "r");
			
			if (open_move_file_inp == NULL) {
				printf("%s could not be opened\n", file_name);
				exit(EXIT_FAILURE);
			} else {
				/* Takes move order from file
				 *
				 * By the way, it is assumed that there are just 8 letters
				 * If there is an error in file, it will probably cause stack overflow
				 */
				for (ct = 0; ct < 8; ++ct) {
					move_list[ct] = fgetc(open_move_file_inp);
				}
				
				printf("\nAppropriate solution found is file %s\n", file_name);
				printf("Moves in order:\n");
				for (ct = 0; ct < 8; ++ct) {
					printf("%c ", move_list[ct]);
				}
				printf("\n");
				
				draw_table(move_list);
				 
				fclose(open_move_file_inp);
			}
		}
		fclose(look_at_log_file_inp);
	}
}

void
draw_table(char move_list[])
{
	struct moves move_arr[10];	/*
								 * 8 moves from file, 1 for first position, 1 for last position
								 */
	int ct,						/* An ordinary counter */
		i, j,					/* Used to draw table */
		flag;					/* Determines whether 'O' is printed or not */
	
	
	/*
	 * This code has some problems and easily cause stack overflow
	 * Just do not make any modifications on move_list array :)
	 */
	move_arr[0].row_pos = 0;
	move_arr[0].col_pos = 0;
	
	move_arr[9].row_pos = 4;
	move_arr[9].col_pos = 4;
	
	for (ct = 1; ct < 9; ++ct) {
		if (move_list[ct - 1] == 'W') {
			move_arr[ct].row_pos = move_arr[ct - 1].row_pos - 1;
			move_arr[ct].col_pos = move_arr[ct - 1].col_pos;
		} else if (move_list[ct - 1] == 'A') {
			move_arr[ct].col_pos = move_arr[ct - 1].col_pos - 1;
			move_arr[ct].row_pos = move_arr[ct - 1].row_pos;
		} else if (move_list[ct - 1] == 'S') {
			move_arr[ct].row_pos = move_arr[ct - 1].row_pos + 1;
			move_arr[ct].col_pos = move_arr[ct - 1].col_pos;
		} else if (move_list[ct - 1] == 'D') {
			move_arr[ct].col_pos = move_arr[ct - 1].col_pos + 1;
			move_arr[ct].row_pos = move_arr[ct - 1].row_pos;
		}
	}
	
	/*
	 * This part of function is used for drawing table
	 * 'X' for starting and end points, 'o' for other points
	 */
	printf(" ___________________\n");
	
	for (i = 0; i < 5; ++i) {
		printf("|   |   |   |   |   |\n|");
		
		for (j = 0; j < 5; ++j) {
			flag = 0;
			
			for (ct = 0; ct < 10; ++ct) {
				if (move_arr[ct].row_pos == i && move_arr[ct].col_pos == j) {
					if ((move_arr[ct].row_pos == 0 && move_arr[ct].col_pos == 0) ||
						(move_arr[ct].row_pos == 4 && move_arr[ct].col_pos == 4)) {
						printf(" X ");
					} else {
						printf(" o ");
					}
					flag = 1;
					break;
				}
			}
				
			if (!flag) {
				printf("   ");
			}
			
			printf("|");
		}
		
		printf("\n|   |   |   |   |   |\n");
		printf(" --------------------\n");
	}
}

void
delete_old_files(void)
{
	FILE *log_file_inp;		/* To open log file */
	char file_name[15],		/* File name variable */
		 situation[6];		/*
		 					 * Actually this array is not necessary in this function
		 					 * the only this it does is skipping found or fail strings
		 					 */
		 
	int file_num,			/* To find the number of last file */
		status,				/* To use take input from file */
		ct,					/* Just an ordinary counter */
		choice;				/* User's choice */
	
	log_file_inp = fopen("log.txt", "r");
	
	if (log_file_inp == NULL) {
		printf("Enter opening \"log.txt\"\n");
		exit(EXIT_FAILURE);
	} else {
		for (status = fscanf(log_file_inp, "%d%s", &file_num, situation);
			 status == 2;
			 status = fscanf(log_file_inp, "%d%s", &file_num, situation)) {
			/* Deliberately empty */
		}
		
		/* A loop to delete all files */
		for (ct = 1; ct <= file_num; ++ct) {
			sprintf(file_name, "%d.txt", ct);
			
			status = remove(file_name);
			
			if (status != 0) {
				printf("An error has occured while deleting old files\n");
				exit(EXIT_FAILURE);
			}
		}
		
		printf("All files are deleted.\n");
		printf("Do you want to delete \"log.txt\" too? (1 for yes, 2 for no)\n");
		printf("> ");
		
		status = scanf("%d", &choice);
		
		/* If an character (except number) is entered exit mechanism works */
		if (status != 1) {
			printf("\n\tYou entered Wrong Input %c\n", getchar());
			exit(EXIT_FAILURE);
		} else {
			if (choice == 1) {
				status = remove("log.txt");
				
				/* Checks whether remove function worked properly */
				if (status == 0) {
					printf("\"log.txt\" is successfully removed\n");
				} else {
					printf("An error has occure while deleting \"log.txt\"\n");
					exit(EXIT_FAILURE);
				}
			} else if (choice == 2) {
				printf("As you like\n");
			} else {
				printf("You entered Wrong Input %d\n", choice);
				exit(EXIT_FAILURE);
			}
		}
	}
}
