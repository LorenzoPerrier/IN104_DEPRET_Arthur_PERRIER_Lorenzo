#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define LENGTH 23
#define WIDTH 55
#define NR_GHOSTS 5
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

struct coordinates{
	int x;
	int y;
};

struct PacMan{
	struct coordinates position;
	int nx;
	int ny;
	int lifes;
	int food;
	bool chasing;
};

struct Ghost{
	struct coordinates position;
	int nx;
	int ny;
	bool chasing;
};

//On place les fantômes aléatoirement sur la map
void initGhosts(struct Ghost *allGhosts[NR_GHOSTS], char area [LENGTH][WIDTH]) {
    for (int k=0; k<NR_GHOSTS; k++) {
        struct Ghost *g = allGhosts[k];
        g->chasing = true;
        int i = rand()%LENGTH;
        int j = rand()%WIDTH;
        while (area[i][j]=='#') {
            i = rand()%LENGTH;
            j = rand()%WIDTH; 
        }
        g->position.x = i;
        g->position.y = j;
        area[i][j] = 'G';
    }
}

//On place la nourriture partout où il y a des espaces
void initFood(char area [LENGTH][WIDTH]) {
    for (int i=0; i<LENGTH; i++) {
        for (int j=0; j<WIDTH; j++) {
            if (area[i][j] == ' ') {
                area[i][j] = '.';
            }
        }
    }
}

//On met le joueur en (1,1)
void initPlayer(struct PacMan player, char area[LENGTH][WIDTH]) {
    area[player.position.x][player.position.y] = 'P';
}

//On déplace les fantômes aléatoirement d'un cran à chaque tour
void moveGhost(struct Ghost *g, char area[LENGTH][WIDTH]) {
    int index1;
    int index2;
    int random[2];
    int list[2] = {-1, 1};
    index1 = rand()%2 ;
    index2 = rand()%2 ;
    random[index1] = 0;
    random[1-index1] = list[index2];
    while (area[g->position.x + random[0]][g->position.y + random[1]] == '#' || area[g->position.x + random[0]][g->position.y + random[1]] == 'G') {
        index1 = rand()%2 ;
        index2 = rand()%2 ;
        random[index1] = 0;
        random[1-index1] = list[index2];
    }
    area[g->position.x][g->position.y] = '.';
    g->position.x = g->position.x + random[0];
    g->position.y = g->position.y + random[1];
    area[g->position.x][g->position.y] = 'G';
}
    


//On récupère l'entrée du player et on oriente la direction du pacman 
void inputPlayer(char input, struct PacMan *player) {
    if (input == 'z') {
        player->ny = -1;
        player->nx = 0;
    }
    if (input == 'w') {
        player->ny = 1;
        player->nx = 0;
    }
    if (input == 'd') {
        player->nx = 1;
        player->ny = 0;
    }
    if (input == 'q') {
        player->nx = -1;
        player->ny = 0;
    }
}

//On bouge le pacman dans la direction demandée en enlevant une vie si collision et en rajoutant de la nourriture s'il y en a
void movePlayer(struct PacMan *player, char area[LENGTH][WIDTH]) {
    area[player->position.x][player->position.y] = ' ';
    //Si on rencontre un fantôme
    if (area[player->position.x + player->ny][player->position.y + player->nx] == 'G') {
        player->lifes--;
        player->position.x = 1;
        player->position.y = 1;
        area[player->position.x][player->position.y] = 'P';
    }
    //Si on rencontre un mur
    if (area[player->position.x + player->ny][player->position.y + player->nx] == '#') {
        player->lifes--;
        area[player->position.x][player->position.y] = 'P';
    }
    else {
        if (area[player->position.x + player->ny][player->position.y + player->nx] == '.') {
            player->food++;
        }
        player->position.x = player->position.x + player->ny;
        player->position.y = player->position.y + player->nx;
        area[player->position.x][player->position.y] = 'P';
        if (area[player->position.x][player->position.y] == '.') {
            player->food++;
        } 
    }
}

//Fonction valeur absolue
int abs(int x) {
    if (x<0) {
        return -x;
    }
    else {
        return x;
    }
}

//Si un fantôme arrive près du joueur, il le suit, sinon il se déplace aléatoirement
void follow(struct PacMan *p, struct Ghost *allGhosts[NR_GHOSTS], char area[LENGTH][WIDTH]) {
    struct Ghost *g;
    float distance;
    for (int i=0; i<NR_GHOSTS; i++) {
        g = allGhosts[i];
        area[g->position.x][g->position.y] = '.';
        int px = p->position.x;
        int py = p->position.y;
        int gx = g->position.x;
        int gy = g->position.y;
        distance = sqrt(pow(gx-px,2) + pow(gy-py,2));

        if (distance < 10) {
            if (abs(px-gx)>abs(gy-py)) {
                if (gx>px && area[gx-1][gy]!='#' && area[gx-1][gy]!='G') {
                    g->position.x--;
                }
                if (gx<px && area[gx+1][gy]!='#' && area[gx+1][gy]!='G') {
                    g->position.x++;
                }
            }
            if (abs(px-gx)<abs(gy-py)) {
                if (gy>py && area[gx][gy-1]!='#' && area[gx][gy-1]!='G') {
                    g->position.y--;
                }
                if (gy<py && area[gx][gy+1]!='#' && area[gx][gy+1]!='G') {
                    g->position.y++;
                }
            }
        if (area[g->position.x][g->position.y] == 'P') {
            p->lifes--;
            p->position.x = 1;
            p->position.y = 1;
            area[p->position.x][p->position.y] = 'P';

        }
        area[g->position.x][g->position.y] = 'G';
        }
        else {
            moveGhost(g, area);
        }
    }
}

//On affiche la map
void display(char area[LENGTH][WIDTH]) {
    for (int i=0; i<LENGTH; i++) {
      for (int j=0; j<WIDTH; j++) {
        if (area[i][j] == 'P') {
            printf(YEL "%c" RESET, area[i][j]);
        }
        if (area[i][j] == 'G') {
            printf(RED "%c" RESET, area[i][j]);
        }
        if (area[i][j] == '#') {
            printf(GRN "%c" RESET, area[i][j]);
        }
        if (area[i][j] == '.') {
            printf(BLU "%c" RESET, area[i][j]);
        }
        if (area[i][j] == ' ') {
            printf("%c" , area[i][j]);
        }
        }
        printf("\n");
    }
}


int main() {
    srand(time(NULL));
	struct Ghost ghost1;
	struct Ghost ghost2;
    struct Ghost ghost3;
    struct Ghost ghost4;
    struct Ghost ghost5;
	struct Ghost *allGhosts[NR_GHOSTS];
	allGhosts[0] = &ghost1;
	allGhosts[1] = &ghost2;
    allGhosts[2] = &ghost3;
    allGhosts[3] = &ghost4;
    allGhosts[4] = &ghost5;
	struct PacMan player;
	char area[LENGTH][WIDTH] = {
   { "#######################################################" },
   { "#                                                     #" },
   { "#     # # # # # #           #           # # # # # #   #" },
   { "#     #         #          # #          #             #" },
   { "#     #         #         #   #         #             #" },
   { "#     #         #        #     #        #             #" },
   { "#     # # # # # #       # # # # #       #             #" },
   { "#     #                #         #      #             #" },
   { "#     #               #           #     #             #" },
   { "#     #              #             #    #             #" },
   { "#     #             #               #   # # # # # #   #" },
   { "#                                                     #" },
   { "#     ##        ##           #          ##        #   #" },
   { "#     # #      # #          # #         # #       #   #" },
   { "#     #  #    #  #         #   #        #  #      #   #" },
   { "#     #    # #   #        #     #       #   #     #   #" },
   { "#     #     #    #       # # # # #      #    #    #   #" },
   { "#     #          #      #         #     #     #   #   #" },
   { "#     #          #     #           #    #      #  #   #" },
   { "#     #          #    #             #   #       # #   #" },
   { "#     #          #   #               #  #        ##   #" },
   { "#                                                     #" },
   { "#######################################################" }
};


   //Initialisation du joueur
   player.position.x = 1;
   player.position.y = 1;
   player.lifes = 3;
   player.chasing = false;
   player.nx = 0;
   player.ny = 0;
   player.food = 0;

   //Initialisation de la map
   initGhosts(allGhosts, area);
   initFood(area);
   initPlayer(player, area);
   display(area);

   char input;
   while (player.lifes>0) {
        printf("What is your next move ?\n");
        scanf(" %c",&input);
        inputPlayer(input, &player);
        movePlayer(&player, area);
        follow(&player, allGhosts, area);
        display(area);
        printf("Lifes : %d\n", player.lifes);
        printf("Points : %d\n", player.food);
   }
   printf("GAME OVER\n");

   return(0);

}



