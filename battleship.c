#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
//functions
void initial();//player's board initialization
void cp_initial();//cp's board initialization
void position();//player's ship positioning. Only horizontally and vertically
void cp_position();//65=aircraft carrier, 66=battleship, 68=destroyer, 83=submarine, 80=patrol boat
void print_board();//prints the player's board
void cp_print_board();//prints the cp's board
void attack();//Player's attack
void cp_attack();//Cp's attack. 120=hit, 46=miss
int attack_check(int row, int column);//checks if the point is attacked, missed or new from the pc's board
int cp_attack_check(int row, int column);//checks if the point is attacked, missed or new from the player's board
int rand_num(int high); //random number below the given number
int victory_check();//checks if player won
int cp_victory_check();//checks if cp won
void ship_coordinates();//goes through the board and records the player's ship coordinates
int distance_check(int a, int b,int num);//checks if the boat coordinates are valid: 1=yes 0=no

//global variables
int board[10][10];
int cp_board[10][10];
int A[5][2];
int B[4][2];
int D[3][2];
int S[3][2];
int P[2][2];
int HIT=0,row,column;
char SHIP;
char state[6];//tells if cp's attack hit or missed

int main() {	
	printf("\n\n\n\n\n\n\n\n");
	printf("XXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX  XXXXX XX  XX XX XXXX\n");
	printf("XX  XX XX  XX   XX     XX   XX     XX     XX     XX  XX XX XX  XX\n");
	printf("XXXXX  XX  XX   XX     XX   XX     XXXX    XXXX  XXXXXX XX XXXX\n");
	printf("XX  XX XXXXXX   XX     XX   XX     XX         XX XX  XX XX XX\n");
	printf("XXXXX  XX  XX   XX     XX   XXXXXX XXXXXX XXXXX  XX  XX XX XX\n");
	printf("\n\n\n\n\n\n");
	system("pause");
	int turn_count=1;
	//player
	initial();	
	position();
	ship_coordinates();
	//pc
	cp_initial();
	cp_position();
	system("cls");
	while (1) {
		//player's turn		
		printf("Player's turn %d:\n\n", turn_count);
		cp_print_board();
		attack();		
		if (victory_check() == 0)//checks if boats are left
			break;
		
		//cp's turn
		cp_attack();
		system("cls");
		printf("CP's turn %d: (%d,%d) %s \n\n",turn_count, (row+1), (column+1), state);
		print_board();
		if (cp_victory_check() == 0)//checks if boats are left
			break;
		turn_count++;
	}	
	if (victory_check() == 0) {
		printf("\nYou won!! Congratulations!\n");
		system("pause");
	}
	else if (cp_victory_check() == 0) {
		printf("\nYou lost! Good luck next time!\n");
		system("pause");
	}
	return 0;
}
int victory_check() {
	int i, j, boats_left = 0;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (cp_board[i][j] == 65 || cp_board[i][j] == 66 || cp_board[i][j] == 68 
				|| cp_board[i][j] == 83 || cp_board[i][j] == 80) {
				boats_left += 1;
			}

		}
	}
	return boats_left;//if no boats left returns 0

}
int cp_victory_check() {
	int i, j, boats_left=0;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (board[i][j] == 65 || board[i][j] == 66 || board[i][j] == 68
				|| board[i][j] == 83 || board[i][j] == 80) {
				boats_left += 1;
			}
		}
	}
	return boats_left;//if no boats left returns 0

}
void initial() {
	int i, j;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			board[i][j] = 126;
}
void cp_initial() {
	int i, j;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			cp_board[i][j] = 126;
}
void print_board() {
	int i, j, k;
	for (k = 0; k < 11; k++) {
		if (k == 0)
			printf("   ");
		else
			printf("%3d", k);
	}
	printf("\n");
	for (i = 0; i < 10; i++) {
		printf("%3d", (i + 1));
		for (j = 0; j < 10; j++) {
			printf("%3c", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void cp_print_board() {
	int i, j, k;
	for (k = 0; k < 11; k++) {
		if (k == 0)
			printf("   ");
		else
			printf("%3d", k);
	}
	printf("\n");
	for (i = 0; i < 10; i++) {
		printf("%3d", (i + 1));
		for (j = 0; j < 10; j++) {
			switch (cp_board[i][j]) {
			case 65:
			case 66:
			case 68:
			case 83:
			case 80:
				printf("%3c", 126);
				break;
			case 120:
			case 126:
			case 46:
				printf("%3c", cp_board[i][j]);
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
}
int distance_check(int a, int b,int num) {
	int temp;
	if (b > a) {//a is always bigger so changes a and b's place if needed
		temp = b;
		b = a;
		a = temp;
	}
	if ((a - b) == (num-1)) 
		return 1;	//returns 1 if the value is ok
	else
		return 0;//returns 0 if the value is not ok
}
void position() {
	
	int column, row, column2, row2,i,found,dist1,dist2;
	
		//Aircraft carrier
		system("cls");
		printf("\tShip positioning\n\n");
		print_board();
		do {
		printf("Your (A)ircraft carrier's starting point (5 points)\n");						
		do {
			printf("Row: ");
			scanf_s("%d", &row);
		} while (row < 1 || row>10);
		do{
			printf("Column: ");
			scanf_s("%d", &column);	
		} while (column < 1 || column>10);
		printf("Your (A)ircraft carrier's ending point\n");		
		do {
			printf("Row: ");
			scanf_s("%d", &row2);
		} while (row2 < 1 || row2>10);
		do {
			printf("Column: ");
			scanf_s("%d", &column2);
		} while (column2 < 1 || column2>10);
			dist1 = distance_check(row, row2, 5);//vertical
			dist2 = distance_check(column, column2, 5);//horizontal
			found = 0;
			if (dist1 == 1) {//if the ship is placed vertically
				if (row > row2) {
					for (i = 0; i < 5; i++) {
						if(board[row-1 - i][column-1]!=126)
						found++;
					}
				}
				else if (row2 > row) {
					for (i = 0; i < 5; i++) {
						if(board[row-1 + i][column-1]!=126)
						found++;
					}
				}
			}
			else if (dist2 == 1) {//if the ship is placed horizontally
				if (column > column2) {
					for (i = 0; i < 5; i++) {
						if(board[row-1][column-1 - i]!=126)
						found++;
					}
				}
				else if (column2 > column) {
					for (i = 0; i < 5; i++) {
						if (board[row-1][column-1 + i] != 126)
						found++;
					}
				}
			}
			if ((dist1 == 0 && dist2 == 0) || (dist1 == 1 && dist2 == 1) || found > 0) {
				system("cls");
				printf("\tShip positioning\n\n");
				print_board();
				printf("Input the coordinates again\n\n");
			}
		} while ((dist1 == 0 && dist2 == 0) || (dist1 == 1 && dist2 == 1) || found > 0);
		if (dist1 == 1) {//if the ship is placed vertically
			if (row > row2) {
				for (i = 0; i < 5; i++) {
					board[row-1 - i][column-1] = 65;
				}
			}
			else if (row2 > row) {
				for (i = 0; i < 5; i++) {
					board[row-1 + i][column-1] = 65;
				}
			}
		}
		else if (dist2 == 1) {//if the ship is placed horizontally
			if (column > column2) {
				for (i = 0; i < 5; i++) {
					board[row-1][column-1 - i] = 65;
				}
			}
			else if (column2 > column) {
				for (i = 0; i < 5; i++) {
					board[row-1][column-1 + i] = 65;
				}
			}
		}
		//Battleship
		system("cls");
		printf("\tShip positioning\n\n");
		print_board();
		do {
			printf("Your (B)attleship's starting point (4 points)\n");
			do {
				printf("Row: ");
				scanf_s("%d", &row);
			} while (row < 1 || row>10);
			do {
				printf("Column: ");
				scanf_s("%d", &column);
			} while (column < 1 || column>10);
			printf("Your (B)attleship's ending point\n");
			do {
				printf("Row: ");
				scanf_s("%d", &row2);
			} while (row2 < 1 || row2>10);
			do {
				printf("Column: ");
				scanf_s("%d", &column2);
			} while (column2 < 1 || column2>10);
			dist1 = distance_check(row, row2,4);//vertical
			dist2 = distance_check(column, column2,4);//horizontal
			found = 0;
			if (dist1 == 1) {//if the ship is placed vertically
				if (row > row2) {
					for (i = 0; i < 4; i++) {
						if (board[row - 1 - i][column - 1] != 126)
							found++;
					}
				}
				else if (row2 > row) {
					for (i = 0; i < 4; i++) {
						if (board[row - 1 + i][column - 1] != 126)
							found++;
					}
				}
			}
			else if (dist2 == 1) {//if the ship is placed horizontally
				if (column > column2) {
					for (i = 0; i < 4; i++) {
						if (board[row - 1][column - 1 - i] != 126)
							found++;
					}
				}
				else if (column2 > column) {
					for (i = 0; i < 4; i++) {
						if (board[row - 1][column - 1 + i] != 126)
							found++;
					}
				}
			}
			if ((dist1 == 0 && dist2 == 0) || (dist1 == 1 && dist2 == 1) || found > 0) {
				system("cls");
				printf("\tShip positioning\n\n");
				print_board();
				printf("Input the coordinates again\n\n");
			}
		} while ((dist1 == 0 && dist2 == 0) || (dist1 == 1 && dist2 == 1) || found > 0);
		if (dist1 == 1) {//if the ship is placed vertically
			if (row > row2) {
				for (i = 0; i < 4; i++) {
					board[row - 1 - i][column - 1] = 66;
				}
			}
			else if (row2 > row) {
				for (i = 0; i < 4; i++) {
					board[row - 1 + i][column - 1] = 66;
				}
			}
		}
		else if (dist2 == 1) {//if the ship is placed horizontally
			if (column > column2) {
				for (i = 0; i < 4; i++) {
					board[row - 1][column - 1 - i] = 66;
				}
			}
			else if (column2 > column) {
				for (i = 0; i < 4; i++) {
					board[row - 1][column - 1 + i] = 66;
				}
			}
		}
		//Destroyer
		system("cls");
		printf("\tShip positioning\n\n");
		print_board();
		do {
			printf("Your (D)estroyer's starting point (3 points)\n");
			do {
				printf("Row: ");
				scanf_s("%d", &row);
			} while (row < 1 || row>10);
			do {
				printf("Column: ");
				scanf_s("%d", &column);
			} while (column < 1 || column>10);
			printf("Your (D)estroyer' ending point\n");
			do {
				printf("Row: ");
				scanf_s("%d", &row2);
			} while (row2 < 1 || row2>10);
			do {
				printf("Column: ");
				scanf_s("%d", &column2);
			} while (column2 < 1 || column2>10);
			dist1 = distance_check(row, row2,3);//vertical
			dist2 = distance_check(column, column2,3);//horizontal
			found = 0;
			if (dist1 == 1) {//if the ship is placed vertically
				if (row > row2) {
					for (i = 0; i < 3; i++) {
						if (board[row - 1 - i][column - 1] != 126)
							found++;
					}
				}
				else if (row2 > row) {
					for (i = 0; i < 3; i++) {
						if (board[row - 1 + i][column - 1] != 126)
							found++;
					}
				}
			}
			else if (dist2 == 1) {//if the ship is placed horizontally
				if (column > column2) {
					for (i = 0; i < 3; i++) {
						if (board[row - 1][column - 1 - i] != 126)
							found++;
					}
				}
				else if (column2 > column) {
					for (i = 0; i < 3; i++) {
						if (board[row - 1][column - 1 + i] != 126)
							found++;
					}
				}
			}
			if ((dist1 == 0 && dist2 == 0) || (dist1 == 1 && dist2 == 1) || found > 0) {
				system("cls");
				printf("\tShip positioning\n\n");
				print_board();
				printf("Input the coordinates again\n\n");
			}
		} while ((dist1 == 0 && dist2 == 0) || (dist1 == 1 && dist2 == 1) || found > 0);
		if (dist1 == 1) {//if the ship is placed vertically
			if (row > row2) {
				for (i = 0; i < 3; i++) {
					board[row - 1 - i][column - 1] = 68;
				}
			}
			else if (row2 > row) {
				for (i = 0; i < 3; i++) {
					board[row - 1 + i][column - 1] = 68;
				}
			}
		}
		else if (dist2 == 1) {//if the ship is placed horizontally
			if (column > column2) {
				for (i = 0; i < 3; i++) {
					board[row - 1][column - 1 - i] = 68;
				}
			}
			else if (column2 > column) {
				for (i = 0; i < 3; i++) {
					board[row - 1][column - 1 + i] = 68;
				}
			}
		}
		//Submarine
		system("cls");
		printf("\tShip positioning\n\n");
		print_board();
		do {
			printf("Your (S)ubmarine's starting point (3 points)\n");
			do {
				printf("Row: ");
				scanf_s("%d", &row);
			} while (row < 1 || row>10);
			do {
				printf("Column: ");
				scanf_s("%d", &column);
			} while (column < 1 || column>10);
			printf("Your (S)ubmarine's ending point\n");
			do {
				printf("Row: ");
				scanf_s("%d", &row2);
			} while (row2 < 1 || row2>10);
			do {
				printf("Column: ");
				scanf_s("%d", &column2);
			} while (column2 < 1 || column2>10);
			dist1 = distance_check(row, row2,3);//vertical
			dist2 = distance_check(column, column2,3);//horizontal
			found = 0;
			if (dist1 == 1) {//if the ship is placed vertically
				if (row > row2) {
					for (i = 0; i < 3; i++) {
						if (board[row - 1 - i][column - 1] != 126)
							found++;
					}
				}
				else if (row2 > row) {
					for (i = 0; i < 3; i++) {
						if (board[row - 1 + i][column - 1] != 126)
							found++;
					}
				}
			}
			else if (dist2 == 1) {//if the ship is placed horizontally
				if (column > column2) {
					for (i = 0; i < 3; i++) {
						if (board[row - 1][column - 1 - i] != 126)
							found++;
					}
				}
				else if (column2 > column) {
					for (i = 0; i < 3; i++) {
						if (board[row - 1][column - 1 + i] != 126)
							found++;
					}
				}
			}
			if ((dist1 == 0 && dist2 == 0) || (dist1 == 1 && dist2 == 1) || found > 0) {
				system("cls");
				printf("\tShip positioning\n\n");
				print_board();
				printf("Input the coordinates again\n\n");
			}
		} while ((dist1 == 0 && dist2 == 0) || (dist1 == 1 && dist2 == 1) || found > 0);
		if (dist1 == 1) {//if the ship is placed vertically
			if (row > row2) {
				for (i = 0; i < 3; i++) {
					board[row - 1 - i][column - 1] = 83;
				}
			}
			else if (row2 > row) {
				for (i = 0; i < 3; i++) {
					board[row - 1 + i][column - 1] = 83;
				}
			}
		}
		else if (dist2 == 1) {//if the ship is placed horizontally
			if (column > column2) {
				for (i = 0; i < 3; i++) {
					board[row - 1][column - 1 - i] = 83;
				}
			}
			else if (column2 > column) {
				for (i = 0; i < 3; i++) {
					board[row - 1][column - 1 + i] = 83;
				}
			}
		}
		//Patrol boat
		system("cls");
		printf("\tShip positioning\n\n");
		print_board();
		do {
			printf("Your (P)atrol boat's starting point (2 points)\n");
			do {
				printf("Row: ");
				scanf_s("%d", &row);
			} while (row < 1 || row>10);
			do {
				printf("Column: ");
				scanf_s("%d", &column);
			} while (column < 1 || column>10);
			printf("Your (P)atrol boat's ending point\n");
			do {
				printf("Row: ");
				scanf_s("%d", &row2);
			} while (row2 < 1 || row2>10);
			do {
				printf("Column: ");
				scanf_s("%d", &column2);
			} while (column2 < 1 || column2>10);
			dist1 = distance_check(row, row2,2);//vertical
			dist2 = distance_check(column, column2,2);//horizontal
			found = 0;
			if (dist1 == 1) {//if the ship is placed vertically
				if (row > row2) {
					for (i = 0; i < 2; i++) {
						if (board[row - 1 - i][column - 1] != 126)
							found++;
					}
				}
				else if (row2 > row) {
					for (i = 0; i < 2; i++) {
						if (board[row - 1 + i][column - 1] != 126)
							found++;
					}
				}
			}
			else if (dist2 == 1) {//if the ship is placed horizontally
				if (column > column2) {
					for (i = 0; i < 2; i++) {
						if (board[row - 1][column - 1 - i] != 126)
							found++;
					}
				}
				else if (column2 > column) {
					for (i = 0; i < 2; i++) {
						if (board[row - 1][column - 1 + i] != 126)
							found++;
					}
				}
			}
			if ((dist1 == 0 && dist2 == 0) || (dist1 == 1 && dist2 == 1) || found > 0) {
				system("cls");
				printf("\tShip positioning\n\n");
				print_board();
				printf("Input the coordinates again\n\n");
			}
		} while ((dist1 == 0 && dist2 == 0) || (dist1 == 1 && dist2 == 1) || found > 0);
		if (dist1 == 1) {//if the ship is placed vertically
			if (row > row2) {
				for (i = 0; i < 2; i++) {
					board[row - 1 - i][column - 1] = 80;
				}
			}
			else if (row2 > row) {
				for (i = 0; i < 2; i++) {
					board[row - 1 + i][column - 1] = 80;
				}
			}
		}
		else if (dist2 == 1) {//if the ship is placed horizontally
			if (column > column2) {
				for (i = 0; i < 2; i++) {
					board[row - 1][column - 1 - i] = 80;
				}
			}
			else if (column2 > column) {
				for (i = 0; i < 2; i++) {
					board[row - 1][column - 1 + i] = 80;
				}
			}
		}
		system("cls");
		print_board();
		system("pause");
}
int rand_num(int high) {
	srand(time(NULL));
	int r;
	do {
		r = rand();
	} while (r >= high);

	return r;
}
void cp_position() {

	int battleship, aircraft, destroyer, patrol, submarine;
	int column, row, direction, check;
	int array[10] = { 0 };//records which row or columns have been used
	aircraft = 5;
	battleship = 4;
	destroyer = 3;
	submarine = 3;
	patrol = 2;

	direction = rand_num(2);//choosing the direction of the boats


	if (direction == 0) {//horizontally
		//aircraft
		row = rand_num(10);
		array[row] = 1;//registers which row has been used
		column = rand_num(6);
		while (aircraft > 0) {//lays the ship horizontally 
			cp_board[row][column] = 65;
			column++;
			aircraft--;
		}
		//battleship
		do {
			check = 0;
			row = rand_num(10);
			if (array[row] == 1)
				check = 1;
		} while (check == 1);//checks whether the row has been used
		array[row] = 1;
		column = rand_num(7);
		while (battleship > 0) {
			cp_board[row][column] = 66;
			column++;
			battleship--;
		}
		//destroyer
		do {
			check = 0;
			row = rand_num(10);
			if (array[row] == 1)
				check = 1;
		} while (check == 1);
		array[row] = 1;
		column = rand_num(8);
		while (destroyer > 0) {
			cp_board[row][column] = 68;
			column++;
			destroyer--;
		}
		//submarine
		do {
			check = 0;
			row = rand_num(10);
			if (array[row] == 1)
				check = 1;
		} while (check == 1);
		array[row] = 1;
		column = rand_num(8);
		while (submarine > 0) {
			cp_board[row][column] = 83;
			column++;
			submarine--;
		}
		//patrol
		do {
			check = 0;
			row = rand_num(10);
			if (array[row] == 1)
				check = 1;
		} while (check == 1);
		array[row] = 1;
		column = rand_num(9);
		while (patrol > 0) {
			cp_board[row][column] = 80;
			column++;
			patrol--;
		}
	}
	else if (direction == 1) {
		//aircraft
		column = rand_num(10);
		array[column] = 1;
		row = rand_num(6);
		while (aircraft > 0) {
			cp_board[row][column] = 65;
			row++;
			aircraft--;
		}
		//battleship
		do {
			check = 0;
			column = rand_num(10);
			if (array[column] == 1)
				check = 1;
		} while (check == 1);
		array[column] = 1;
		row = rand_num(7);
		while (battleship > 0) {
			cp_board[row][column] = 66;
			row++;
			battleship--;
		}
		//destroyer
		do {
			check = 0;
			column = rand_num(10);
			if (array[column] == 1)
				check = 1;
		} while (check == 1);
		array[column] = 1;
		row = rand_num(8);
		while (destroyer > 0) {
			cp_board[row][column] = 68;
			row++;
			destroyer--;
		}
		//submarine
		do {
			check = 0;
			column = rand_num(10);
			if (array[column] == 1)
				check = 1;
		} while (check == 1);
		array[column] = 1;
		row = rand_num(8);
		while (submarine > 0) {
			cp_board[row][column] = 83;
			row++;
			submarine--;
		}
		//patrol
		do {
			check = 0;
			column = rand_num(10);
			if (array[column] == 1)
				check = 1;
		} while (check == 1);
		array[column] = 1;
		row = rand_num(9);
		while (patrol > 0) {
			cp_board[row][column] = 80;
			row++;
			patrol--;
		}
	}
}
int cp_attack_check(int row, int column) {
	int result;
	if ((board[row][column]) == 120 || (board[row][column]) == 46)
		result = 1;//attacked point
	else if ((board[row][column]) == 46)
		result = 2;//missed point
	else
		result = 0;//new point
	return result;
}
int attack_check(int row, int column) {
	int result;
	if ((cp_board[row][column]) == 120 || (cp_board[row][column]) == 46)
		result = 1;//attacked point
	else if ((cp_board[row][column]) == 46)
		result = 2;//missed point
	else
		result = 0;//new point
	return result;
}
void ship_coordinates() {
	int i, j, k=0;
	for (i = 0; i < 10; i++) {//goes through the board and puts the ship's coordinates
		for (j = 0; j < 10; j++) {
			if (board[i][j] == 65) {
				A[k][0] = i;
				A[k][1] = j;
				k++;
			}			
		}
	}
	k = 0;
	for (i = 0; i < 10; i++) {//goes through the board and puts the ship's coordinates
		for (j = 0; j < 10; j++) {
			if (board[i][j] == 66) {
				B[k][0] = i;
				B[k][1] = j;
				k++;
			}
		}
	}
	k = 0;
	for (i = 0; i < 10; i++) {//goes through the board and puts the ship's coordinates
		for (j = 0; j < 10; j++) {
			if (board[i][j] == 68) {
				D[k][0] = i;
				D[k][1] = j;
				k++;
			}
		}
	}
	k = 0;
	for (i = 0; i < 10; i++) {//goes through the board and puts the ship's coordinates
		for (j = 0; j < 10; j++) {
			if (board[i][j] == 83) {
				S[k][0] = i;
				S[k][1] = j;
				k++;
			}
		}
	}
	k = 0;
	for (i = 0; i < 10; i++) {//goes through the board and puts the ship's coordinates
		for (j = 0; j < 10; j++) {
			if (board[i][j] == 80) {
				P[k][0] = i;
				P[k][1] = j;
				k++;
			}
		}
	}	
}
void cp_attack(){
	int i;	
		
	switch (HIT) {
		
	case 0://when not hit
		do {
			row = rand_num(10);
			column = rand_num(10);
		} while (cp_attack_check(row, column) == 1 || cp_attack_check(row, column) == 2);//checks whether the point has been used
		switch (board[row][column]) {
		case 65://aircraft carrier
			HIT = 1;
			strcpy_s(state,4, "Hit");
			SHIP = 'A';
			board[row][column] = 120;
			for (i = 0; i < 5; i++) {
				if ((A[i][0] == row)&&(A[i][1] == column)) {
					A[i][0] = -1;
					A[i][1] = -1;
				}
			}
			break;
		case 66://battleship
			HIT = 1;
			strcpy_s(state,4, "Hit");
			SHIP = 'B';
			board[row][column] = 120;
			for (i = 0; i < 4; i++) {
				if ((B[i][0] == row) && (B[i][1] == column)) {
					B[i][0] = -1;
					B[i][1] = -1;
				}
			}
			break;
		case 68://destroyer
			HIT = 1;
			strcpy_s(state, 4, "Hit");
			SHIP = 'D';
			board[row][column] = 120;
			for (i = 0; i < 3; i++) {
				if ((D[i][0] == row) && (D[i][1] == column)) {
					D[i][0] = -1;
					D[i][1] = -1;
				}
			}
			break;
		case 83://submarine
			HIT = 1;
			strcpy_s(state, 4, "Hit");
			SHIP = 'S';
			board[row][column] = 120;
			for (i = 0; i < 3; i++) {
				if ((S[i][0] == row) && (S[i][1] == column)) {
					S[i][0] = -1;
					S[i][1] = -1;
				}
			}
			break;
		case 80://patrol boat
			HIT = 1;
			strcpy_s(state, 4, "Hit");
			SHIP = 'P';
			board[row][column] = 120;
			for (i = 0; i < 2; i++) {
				if ((P[i][0] == row) && (P[i][1] == column)) {
					P[i][0] = -1;
					P[i][1] = -1;
				}
			}
			break;
		case 126:
			board[row][column] = 46;
			strcpy_s(state, 5, "Miss");
			break;
		}
		break;
	case 1:
	case 2:
	case 3:
	case 4://when hit
		switch (SHIP) {
		case 'A':
			HIT++;//increase the hit
			strcpy_s(state, 4, "Hit");
			for (i = 0; i < 5; i++) {//searches for the remaining ship coordinate and attacks it
				if ((A[i][0] != -1) && (A[i][1] != -1)) {
					board[A[i][0]][A[i][1]] = 120;//changes the value in the board
					A[i][0] = -1;//removes the ship coordinate
					A[i][1] = -1;//removes the ship coordinate
					break;
				}
			}
			if (HIT == 5) {//if the ship is destroyed resets the counter
				HIT = 0;
			}
			break;
		case 'B':
			HIT++;//increase the hit
			strcpy_s(state, 4, "Hit");
			for (i = 0; i < 4; i++) {//searches for the remaining ship coordinate and attacks it
				if ((B[i][0] != -1) && (B[i][1] != -1)) {
					board[B[i][0]][B[i][1]] = 120;//changes the value in the board
					B[i][0] = -1;//removes the ship coordinate
					B[i][1] = -1;//removes the ship coordinate
					break;
				}
			}
			if (HIT == 4) {//if the ship is destroyed resets the counter
				HIT = 0;
			}
			break;
		case 'D':
			HIT++;//increase the hit
			strcpy_s(state, 4, "Hit");
			for (i = 0; i < 3; i++) {//searches for the remaining ship coordinate and attacks it
				if ((D[i][0] != -1) && (D[i][1] != -1)) {
					board[D[i][0]][D[i][1]] = 120;//changes the value in the board
					D[i][0] = -1;//removes the ship coordinate
					D[i][1] = -1;//removes the ship coordinate
					break;
				}
			}
			if (HIT == 3) {//if the ship is destroyed resets the counter
				HIT = 0;
			}
			break;
		case 'S':
			strcpy_s(state, 4, "Hit");
			HIT++;//increase the hit
			for (i = 0; i < 3; i++) {//searches for the remaining ship coordinate and attacks it
				if ((S[i][0] != -1) && (S[i][1] != -1)) {
					board[S[i][0]][S[i][1]] = 120;//changes the value in the board
					S[i][0] = -1;//removes the ship coordinate
					S[i][1] = -1;//removes the ship coordinate
					break;
				}
			}
			if (HIT == 3) {//if the ship is destroyed resets the counter
				HIT = 0;
			}
			break;
		case 'P':
			strcpy_s(state, 4, "Hit");
			HIT++;//increase the hit
			for (i = 0; i < 2; i++) {//searches for the remaining ship coordinate and attacks it
				if ((P[i][0] != -1) && (P[i][1] != -1)) {
					board[P[i][0]][P[i][1]] = 120;//changes the value in the board
					P[i][0] = -1;//removes the ship coordinate
					P[i][1] = -1;//removes the ship coordinate
					break;
				}
			}
			if (HIT == 2) {//if the ship is destroyed resets the counter
				HIT = 0;
			}
			break;
		}
	}	
}
void attack() {
		
	do {
		printf("Your turn to attack:\n");
		do {
			printf("Row: ");
			scanf_s("%d", &row);
		} while (row < 1 || row>10);
		do {
			printf("Column: ");
			scanf_s("%d", &column);
		} while (column < 1 || column>10);
		if (attack_check((row - 1), (column - 1)) == 1 || attack_check((row - 1), (column - 1)) == 2) {
			printf("Input the coordinates again\n\n");
		}
	} while (attack_check((row-1), (column-1)) == 1 || attack_check((row - 1), (column - 1)) == 2);//checks whether the point has been used
	
	switch (cp_board[row-1][column-1]) {

	case 65:		
	case 66:
	case 68:
	case 83:
	case 80:
		cp_board[row-1][column-1] = 120;
		strcpy_s(state, 4, "Hit");
		break;
	case 126:
		cp_board[row-1][column-1] = 46;
		strcpy_s(state, 5, "Miss");
		break;
	}
}