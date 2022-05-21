#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"

int* creer_grille(){

int* tab = malloc(10*3);

return tab;

}

void afficher(int* grille){
int cpt = 0;
for (int k =0; k<9;k+=1){
if (grille[k]==0){printf(".");}
if (grille[k]==1){printf("x");}
if (grille[k]==2){printf("o");}
if (cpt == 2 || cpt == 5 || cpt ==8){printf("\n");}
if (cpt == 2 || cpt == 5) {printf("----------\n");}
if(cpt !=2 && cpt!= 5 && cpt!= 8) {printf(" | ");}

cpt+=1;

}
}

void test_affichage(int * tab){

afficher(tab);
tab[3]=1;
tab[8]=2;
afficher(tab);
}

void placer(int* grille, int chiffre, int joueur){
grille[chiffre]=joueur;
}

void placer_alea(int* grille, int joueur){
int test = 0;
while (test == 0){
int rd = rand()%9;
if (grille[rd] == 0){test = 1;
placer(grille, rd, joueur);
}
}
}

int a_gagne(int* grille, int joueur){

if (grille[0] == joueur && grille[1]==joueur && grille[2]==joueur){return 1;}

if (grille[3] == joueur && grille[4]==joueur && grille[5]==joueur){return 1;}

if (grille[6] == joueur && grille[7]==joueur && grille[8]==joueur){return 1;}

if (grille[0] == joueur && grille[3]==joueur && grille[6]==joueur){return 1;}

if (grille[2] == joueur && grille[5]==joueur && grille[8]==joueur){return 1;}

if (grille[0] == joueur && grille[4]==joueur && grille[8]==joueur){return 1;}

if (grille[1] == joueur && grille[4]==joueur && grille[7]==joueur){return 1;}

if (grille[2] == joueur && grille[4]==joueur && grille[6]==joueur){return 1;}
return 0;
}




int startTictactoe(){
srand(time(0));


int * tab = creer_grille();

//test_affichage(tab);



int joueur;
int nombre_de_tour = 0; 
while (a_gagne(tab,1)==0 && a_gagne(tab,2)==0 && nombre_de_tour <5){   // comme c'est a nous de commencer, il y a au maximum 5 tours, si on depasse cela, on quitte la boucle. Si personne ne gagne, alors il y a match nul
afficher(tab);
joueur = 1;
printf("A vous de jouer !Ou mettre la croix ?\n(case allant de 1 à 9)\n");

int chiffre;
scanf(" %d", &chiffre); 
chiffre--;
while(tab[chiffre] != 0){
printf("recommencez, choisissez une case non prise !\n(case allant de 1 à 9)\n");
scanf(" %d", &chiffre); 
chiffre--;
}

placer(tab,chiffre,joueur);
if (a_gagne(tab,joueur)==1){afficher(tab);return printf("Vous avez gagné\n");} //test pour voir si l'action du joueur lui permet de gagner directement
nombre_de_tour +=1;

joueur = 2;
if(nombre_de_tour != 5){
placer_alea(tab, joueur);}

}
afficher(tab);

if (a_gagne(tab,1)==1){printf("Vous avez gagné\n");}
if (a_gagne(tab,2)==1){printf("L'ordi a gagné\n");}
if (nombre_de_tour >=5){printf("match nul\n");}


free(tab);

}
/*
int main(){
startTictactoe();
}
*/
