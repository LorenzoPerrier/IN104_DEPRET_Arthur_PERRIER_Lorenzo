#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <prepareMatrix.h>


int** removeNum(int** matrix, char* difficulty){

srand(time(0));

switch (difficulty)
{
case "easy" :

int i = 0;
int j = 0;

for (int k =0,k<27,++k){
 
 i = rand()%81;
 j = rand()%81;
 
 while(matrix[i][j] ==0){
 i = rand()%81;
 j = rand()%81;
 }
 
 matrix[i][j] = 0;
 
}



break;
case "medium":
int i = 0;
int j = 0;

for (int k =0,k<40,++k){
 
 i = rand()%81;
 j = rand()%81;
 
 while(matrix[i][j] ==0){
 i = rand()%81;
 j = rand()%81;
 }
 
 matrix[i][j] = 0;
 
}



break;
case "hard" :

int i = 0;
int j = 0;

for (int k =0,k<56,++k){
 
 i = rand()%81;
 j = rand()%81;
 
 while(matrix[i][j] ==0){
 i = rand()%81;
 j = rand()%81;
 }
 
 matrix[i][j] = 0;
 
}

break;

default : 
printf("No Difficulty recognized --> going for HARD HAHAHA");

int i = 0;
int j = 0;

for (int k =0,k<56,++k){
 
 i = rand()%81;
 j = rand()%81;
 
 while(matrix[i][j] ==0){
 i = rand()%81;
 j = rand()%81;
 }
 
 matrix[i][j] = 0;
}

}

return matrix;

}
