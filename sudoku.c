#include <stdio.h>
#include <stdlib.h>


#define int matrice[9][9];


bool check_num(int *tab, int i, int num)
{
	for (int k = 0; k<i;i++)
	{
		if tab[i]==num {return true;}
	}
return false;
}

int ** create_matrice_diag()
{
	int matrice3[9];

	matrice3[0] = rand()%9 +1;

	for (int i = 1; i<9;i++)
	{ 
		do {int num = rand()%9 +1;}
		while {check_num(matrice3,i,num)}
		matrice3[i]=num;		
		}
	}

	

}