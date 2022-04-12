#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define	int matrix[9][9];

void fillGrid(int tab[3][3]) {
	int Numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // Tableau des valeurs possibles
	int random;

	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			random = rand()%9;
			while (Numbers[random] == 0) {
				random = rand()%9;
				}
			tab[i][j] = Numbers[random];
			Numbers[random] = 0;
			}
		}
	}
	

void display(int tab[3][3]) {
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			printf("%d", tab[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	srand(time(0));
	int up_right[3][3];
	int up_left[3][3];
	int down_right[3][3];
	int down_left[3][3];
	fillGrid(up_left);
	fillGrid(up_right);
	fillGrid(down_right);
	fillGrid(down_left);
	display(matrix);
}
