#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "sudoku.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"


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
	for (int j=0; j<9; j++) {
		if (tab[ligne][j] == num) {
			return false;
			}
		}
	return true;
}

//Vérifie si un chiffre peut rentrer dans une colonne
bool notinColumn(int tab[9][9], int colonne, int num) {
	for (int i=0; i<9; i++) {
		if (tab[i][colonne] == num) {
			return false;
		}
	}
	return true;
}

//Vérifie si un chiffre n'est pas dans une matrice 3x3
bool notinMatrix(int tab[9][9], int i , int j, int num) {
	int x = i;
	int y = j;
	while (x%3 != 0) {
		x--;
	}
	while (y%3 != 0) {
		y--;
	}
	for (int k=x; k<x+3; k++) {
		for (int l=y; l<y+3; l++) {
			if (tab[k][l] == num) {
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

int** removeNum(int matrix[9][9], int choice){
	int N;

	switch (choice) {
		case 1 :
			N = 27;
			printf("facile\n");
		break;

		case 2:
			N = 40;
			printf("moyen\n");
		break;

		case 3 :
			N = 56;
			printf("Difficile\n");
		break;

		default : 
			printf("No Difficulty recognized --> going for HARD HAHAHA\n");
			N = 56;
		}
		
		int i;
		int j;
		int** tab_index = malloc(N*sizeof(int*));
		for (int g = 0; g<N;g++)
		{
		tab_index[g] = malloc(2*sizeof(int));
		}
		
		for (int k =0; k<N; ++k){ 
			 i = rand()%9;
			 j = rand()%9;
			 
			 
			 while(matrix[i][j] == 0){
				 i = rand()%9;
				 j = rand()%9;
			 }
			 
			 matrix[i][j] = 0;
			 tab_index[k][1]=i;
			 tab_index[k][2]=j;
			 
		}
		return tab_index;

}

void freeTab(int** tab_index, int difficulty)
{
int N;
switch (difficulty) {
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
			
			N = 56;
		}
		
for (int k=0; k<N;k++)
{
free(tab_index[k]);
}
free(tab_index);

}
bool checkIfFull(int matrix[9][9]) {
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (matrix[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}
bool checkListIndex(int** tab_index, int difficulty, int i, int j)
{
int N;
switch (difficulty) {
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
			
			N = 56;
		}
		
for (int k=0; k<N;k++)
{
if (tab_index[k][1] == i && tab_index[k][2]==j){return true;}

}
return false;
}
void askPlayer(int matrix[9][9], int** tab_index, int difficulty) {
	int i;
	int j;
	int number;
	printf("Quelle case voulez vous remplir ?\n");
	printf("Ligne ?");
	scanf("%d",&i);
	printf("\n");
	printf("Colonne ?");
	scanf("%d",&j);
	printf("\n");
	i--;
	j--;
	while (!checkListIndex(tab_index,difficulty,i,j)) {
		printf("Joue pas au con avec moi, choisis une case modifiable.\n");
		printf("Ligne ?");
		scanf("%d",&i);
		printf("\n");
		printf("Colonne ?");
		scanf("%d",&j);
		printf("\n");
		i--;
		j--;
	}
	printf("Nombre à mettre dans la case ?");
	scanf("%d",&number);
	printf("\n");
	while (checkPosition(matrix, i, j, number) == false) {
		printf("T'es nul, rejoue\n");
		printf("Nombre à mettre dans la case ?");
		scanf("%d",&number);
		printf("\n");
	}
	matrix[i][j] = number;
}

//Affiche la matrice
void display(int tab[9][9],int** tab_index, int difficulty) {
	for (int i=0; i<9; i++) {
	if(i == 3 || i==6)
	{
	for (int k =0; k<11; k++){
	printf("--");
	}
	printf("\n");
	}
	
		for (int j=0; j<9; j++) {
		
			if (checkListIndex(tab_index,difficulty,i,j))
			{
			
			printf(ANSI_COLOR_RED "%d " ANSI_COLOR_RESET, tab[i][j]);
			
			}
			else{
			printf("%d ", tab[i][j]);
			}
			
			if (j==2 || j==5){
			printf("| ");
			}
		}
		printf("\n");
	
	}
	printf("\n");
}

/*************************************MAIN***********************************************/

int startSudoku() {
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
	
	fillOthers(full, 0, 3);

	//display(full);
	int difficulty = 1;
	printf("Quelle difficulté voulez-vous ?\n[1]Facile\n[2]Moyen\n[3]Difficile\n");
	scanf(" %d", &difficulty);
	int ** tab_index = removeNum(full, difficulty);
	display(full,tab_index,difficulty);

	while (checkIfFull(full) == false) {
		askPlayer(full,tab_index, difficulty);
		display(full,tab_index,difficulty);
	}
	printf("Bravo, c'est gagné ! \n");
	
	freeTab(tab_index,difficulty);
	return(0); 

}

int main(){
startSudoku();
}

