#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include "pacman.h"
#include "tictactoe.h"



int main(){
int game;

printf("    __________________________\n   |OFFo oON                  |\n   | .----------------------. |\n   | |  .----------------.  | |\n   | |  | CONSOLE  IN104 |  | |\n   | |))|                |  | |\n   | |  |   Quel jeu ?   |  | |\n   | |  |                |  | |\n   | |  |  [1] SUDOKU    |  | |\n   | |  |  [2] PACMAN    |  | |\n   | |  |  [3] TICTACTOE |  | |\n   | |  '----------------'  | |\n   | |__GAME BOY____________/ |\n   |          ________        |\n   |    .    (IN104_BOY)      |\n   |  _| |_              .-.  |\n   |-[_   _]-       .-. (   ) |\n   |   |_|         (   ) '-   |\n   |    '           '-    A   |\n   |                 B        |\n   |          ___   ___       |\n   |         (___) (___)  ,., |\n   |        select start ;:;: |\n   |                    ,;:;' /\n   |                   ,:;:' /\n   '-----------------------\n");

do{printf("Choix : ");scanf(" %d",&game);}
while (game != 1 && game!=2 && game!=3);

switch(game){
	case 1 :
	printf("Demarrage du SUDOKU\n");
		startSudoku();
		break;
	case 2 :
	printf("Demarrage de PACMAN\n");
		startPacman();
		break;
	case 3 :
	printf("Demarrage du TICTACTOE\n");
		startTictactoe();
		break;
}

}
