#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

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

//Vérifie si un chiffre peut rentrer dans une ligne
bool notinLine(int tab[9][9], int ligne, int num) {
	for (int j=0; j<8; j++) {
		if (tab[ligne][j] == num) {
			return false;
			}
		}
	return true;
}

//Vérifie si un chiffre peut rentrer dans une colonne
bool notinColumn(int tab[9][9], int colonne, int num) {
	for (int i=0; i<8; i++) {
		if (tab[i][colonne] == num) {
			return false;
		}
	}
	return true;
}

//Vérifie si un chiffre n'est pas dans une matrice 3x3
bool notinMatrix(int tab[9][9], int x , int y, int num) {
	for (int i=x; i<x+3; i++) {
		for (int j=y; j<y+3; j++) {
			if (tab[i][j] == num) {
				return false;
			}
		}
	}
	return true;
}

//Vérifie si uun chiffre peut se mettre à cette place
bool checkPosition(int tab[9][9], int i, int j, int num) {
	if (notinMatrix(tab, i, j, num) && notinColumn(tab, j, num) && notinLine(tab, i, num)) {
		return true;
	}
	return false;
}


bool fillOthers(int tab[9][9], int i, int j) {
	//On a balayé toute la matrice
	if (i>=9 && j>=9) {
		return true;
	}

	//On arrive au bout de la ligne => ligne suivante et colonne 1
	if (j>=9 && i<8) {
		i++;
		j = 0;
	}

	//On est dans la matrice en haut à gauche déjà remplie => on va dans la matrice d'à côté
	if (i<3) {
		if (j<3) {
			j = 3;
		}
	}

	//On est dans la matrice du centre déjà remplie => on va à droite
	else if (i<6) {
		if (j == 3) {
			j = j + 3;
		}
	}

	//On est dans la matrice en bas à droite déjà remplie => on retourne à la ligne sauf si on est sur la dernière
	else {
		if (j == 6) {
			i++;
			j = 0;
			if (i>=9) {
				return true;
			}
		}
	}

	//On met un numéro qui rentre dans la case (i,j) et on passe à la suivante
	//Si on en a pas trouvé, on arrête de remplir et on renvoie false
	for (int num=1; num<=9; num++) {
		if (checkPosition(tab, i, j, num)) {
			tab[i][j] = num;
			if (fillOthers(tab, i, j+1)) {
				return true;
			}
			tab[i][j] = 0;
		}
	}
	return false;
}

void removeNum(int matrix[9][9], char* difficulty){
	int N;
	int choice;
	if (strcmp(difficulty, "easy") == 0) {
		choice = 1;
	}
	if (strcmp(difficulty, "medium") == 0) {
		choice = 2;
	}
	if (strcmp(difficulty, "hard") == 0) {
		choice = 3;
	}
	else {
		choice = 4;
	}

switch (choice) {
	case 1 :
		N = 27;
	break;

	case 2:
		N = 40;
	break;

	case 3 :
		N = 56;
	break;

	default : 
		printf("No Difficulty recognized --> going for HARD HAHAHA\n");
		N = 56;
	}

	int i = 0;
	int j = 0;
	for (int k =0; k<N; ++k){ 
		 i = rand()%81;
		 j = rand()%81;
		 
		 while(matrix[i][j] == 0){
			 i = rand()%81;
			 j = rand()%81;
		 }
	 
		 matrix[i][j] = 0;
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
	display(full);
	while (fillOthers(full, 0, 3) == false) {
			fillOthers(full, 0, 3);
		}
	display(full);
	removeNum(full, "easy");
	display(full);

}
