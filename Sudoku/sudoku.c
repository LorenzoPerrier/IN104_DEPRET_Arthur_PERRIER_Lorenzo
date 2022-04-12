#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "prepareMatrix.h"

//#define	int matrix[9][9];

//Remplit une matrice aléatoire de taille 3x3
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

//Vérifie si une ligne n'a pas deux mêmes chiffres	
bool checkLine(int tab[9][9], int ligne) {
	for (int i=0; i<8; i++) {
		for (int j=i+1; j<9; j++) {
			if (tab[ligne][j] !=0) {
				if (tab[ligne][i] == tab[ligne][j]) {
					return false;
				}
			}
		}
	}
	return true;
}

//Vérifie si une colonne n'a pas deux mêmes chiffres	
bool checkColumn(int tab[9][9], int colonne) {
	for (int i=0; i<8; i++) {
		for (int j=i+1; j<9; j++) {
			if (tab[j][colonne] !=0) {
				if (tab[i][colonne] == tab[j][colonne]) {
					return false;
				}
			}
		}
	}
	return true;
}

//Vérifie si une matrice antisymétrique peut rentrer
bool checkMatrix(int tab[9][9], int x, int y) {
	for (int i=x; i<x+3; i++) {
		for (int j=y; j<y+3; j++) {
			if (checkColumn(tab, j) == false || checkLine(tab, i) == false) {
				return false;
			}
		}
	}
	return true;
}

//Créer les matrices antidiagonales et les met dans la grande
void fillAntiSymetric(int tab[9][9]) {
	int smallUp[3][3];
	int smallDown[3][3];

	fillGrid(smallUp);
	fillGrid(smallDown);

	for (int i=0; i<3; i++) {
		for (int j=6; j<9; j++) {
			tab[i][j] = smallUp[i][j-6];
		}
	}

	while (checkMatrix(tab, 0, 6) == false) {
		fillGrid(smallUp);
		for (int i=0; i<3; i++) {
			for (int j=6; j<9; j++) {
				tab[i][j] = smallUp[i][j-6];
			}
		}
	}

	for (int i=6; i<9; i++) {
		for (int j=0; j<3; j++) {
			tab[i][j] = smallDown[i-6][j];
		}
	}

	while (checkMatrix(tab, 6, 0) == false) {
		fillGrid(smallDown);
		for (int i=6; i<9; i++) {
			for (int j=0; j<3; j++) {
				tab[i][j] = smallDown[i-6][j];
			}
		}
	}
}

void fillOthers(int tab[9][9]) {
	int smallUp[3][3];
	int smallDown[3][3];
	int smallRight[3][3];
	int smallLeft[3][3];

	fillGrid(smallUp);
	fillGrid(smallDown);
	fillGrid(smallLeft);
	fillGrid(smallRight);

	for (int i=0; i<3; i++) {
		for (int j=3; j<6; j++) {
			tab[i][j] = smallUp[i][j-3];
		}
	}

	while (checkMatrix(tab, 0, 3) == false) {
		fillGrid(smallUp);
		for (int i=0; i<3; i++) {
			for (int j=3; j<6; j++) {
				tab[i][j] = smallUp[i][j-3];
			}
		}
	}

	for (int i=6; i<9; i++) {
		for (int j=3; j<6; j++) {
			tab[i][j] = smallDown[i-6][j-3];
		}
	}

	while (checkMatrix(tab, 6, 3) == false) {
		fillGrid(smallDown);
		for (int i=6; i<9; i++) {
			for (int j=3; j<6; j++) {
				tab[i][j] = smallDown[i-6][j-3];
			}
		}
	}

	for (int i=3; i<6; i++) {
		for (int j=0; j<3; j++) {
			tab[i][j] = smallLeft[i-3][j];
		}
	}

	while (checkMatrix(tab, 3, 0) == false) {
		fillGrid(smallLeft);
		for (int i=3; i<6; i++) {
			for (int j=0; j<3; j++) {
				tab[i][j] = smallLeft[i-3][j];
			}
		}
	}

	for (int i=3; i<6; i++) {
		for (int j=6; j<9; j++) {
			tab[i][j] = smallRight[i-3][j-6];
		}
	}

	while (checkMatrix(tab, 3, 6) == false) {
		fillGrid(smallRight);
		for (int i=3; i<6; i++) {
			for (int j=6; j<9; j++) {
				tab[i][j] = smallRight[i-3][j-6];
			}
		}
	}
}

//Affiche la matrice
void display(int tab[9][9]) {
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			printf("%d ", tab[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	srand(time(0));

	//Remplissage de la matrice principale
	int full[9][9];
	for (int i=0; i<9; i++) { 
		for (int j=0; j<9; j++) {
			full[i][j] = 0;
		}
	}

	//Création des matrices diagonales
	int up_left[3][3];
	int center[3][3];
	int down_right[3][3];
	fillGrid(up_left);
	fillGrid(center);
	fillGrid(down_right);

	//On les met dans la matrice principale
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			full[i][j] = up_left[i][j];
		}
	}
	for (int i=3; i<6; i++) {
		for (int j=3; j<6; j++) {
			full[i][j] = center[i-3][j-3];
		}
	}
	for (int i=6; i<9; i++) {
		for (int j=6; j<9; j++) {
			full[i][j] = down_right[i-6][j-6];
		}
	}

	fillAntiSymetric(full);
	fillOthers(full);
	display(full);

	removeNum(full, "easy");
	display(full);
}
