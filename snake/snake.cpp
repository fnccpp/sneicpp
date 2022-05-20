#include <iostream>
#include "windows.h"
#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include <conio.h>
using namespace std;

bool gameover;
const int dim = 30;
char mat[dim][dim];
int x, y, vx, vy; //posiz e veloc
int xF, yF; //pos frutta
struct coda {
    int xC[300];
    int yC[300];
    int lunghezza;
} c;

void setup();
void draw();
void input();
void update();

int main()
{
    while (1) {
        setup();
        while (!gameover) {
            draw();
            input();
            update();
            Sleep(0);
        }
        system("cls");
        cout << "GAME OVER";
        _getch();
    }

   
}

void setup() {
    gameover = 0;
    c.lunghezza = 1; //il primo pezzo della coda è uno spazio
    //pos iniziale
    srand(time(NULL));
    x = rand() % (dim - 2) + 1; //da 1 a 29
    y = rand() % (dim - 2) + 1;
    //veloc iniziale (y = giu, x = destra)
    vx = 0;
    vy = 0;
    //pos iniziale frutta
    xF = rand() % (dim - 2) + 1; 
    yF = rand() % (dim - 2) + 1;
    //mappa iniziale
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (i == 0 || i == dim - 1 || j == 0 || j == dim - 1) {
                mat[i][j] = '#';
            }
            else mat[i][j] = ' ';
        }
    };
    mat[yF][xF] = 'F';
};

void draw() {
    system("cls");
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            cout << mat[i][j];
        }
        cout << endl;
    }
};
 
void input() { 
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': 
            if (!(vx == 1 && c.lunghezza > 0)) { //non si puo invertire direz quando la coda è >0
                vx = -1;
                vy = 0;
            }
            break;
        case 'w':
            if (!(vy == 1 && c.lunghezza > 0)) {
                vx = 0;
                vy = -1;
            }
            break;
        case 's':
            if (!(vy == -1 && c.lunghezza > 0)) {
                vx = 0;
                vy = 1;
            }            
            break;
        case 'd':
            if (!(vx == -1 && c.lunghezza > 0)) {
                vx = 1;
                vy = 0;
            }            
            break;
        }
    }
};

void update() {
    mat[y][x] = ' ';
    //coda (inizialmente è uno spazio)
    c.yC[0] = y; 
    c.xC[0] = x;
    for (int i = c.lunghezza; i > 0; i--) {
        c.yC[i] = c.yC[i - 1];
        c.xC[i] = c.xC[i - 1];            
    }
    for (int i = 0; i < c.lunghezza; i++) {
        mat[c.yC[i]][c.xC[i]] = 'x';
    }
    mat[c.yC[c.lunghezza]][c.xC[c.lunghezza]] = ' ';
    
    //update pos
    
    x += vx;
    y += vy;
    mat[y][x] = 'O';
    //pos frutta, da aggiornare solo quando è presa
    //non c'è bisogno di farla sparire perche viene sovrascritta da O
    if (x==xF && y==yF) { //condizione di frutta presa
        xF = rand() % (dim - 2) + 1;
        yF = rand() % (dim - 2) + 1;
        mat[yF][xF] = 'F';
        c.lunghezza ++;
    }
    //cond di gameover
    if (x == 0 || x == dim-1 || y == 0 || y == dim-1) {
        gameover = 1;
    }
    for (int i = 2; i < c.lunghezza; i++) { //parte da due perche non puo collidere con i primi 2 pezzi della coda
        if (x == c.xC[i] && y == c.yC[i]) {
            gameover = 1;
        }
    }
};