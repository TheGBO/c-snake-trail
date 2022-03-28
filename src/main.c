#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define mapW 30
#define mapH 115
#define snake '*'

#define background 32
#define wall 219

int alive = 1;
char map[mapW][mapH];
int snakeX = -1, snakeY = 1;
int obstacles[250][250];
int fruits[500][500];
int score = 0;


void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void updateScore(){
    gotoxy(0,0);
    printf("Score: %d", score);
}

void renderMap(){
    for (int x = 0; x < mapW; x++)
    {
        for (int y = 0; y < mapH; y++)
        {
            printf("%c",map[x][y]);
        }
        printf("\n");
    }
}

void gameOver(){
    alive = 0;
    system("cls");
    printf("Game Over, Your final score was: %d \n", score);
    system("pause");
    system("cls");
    exit(0);
}

int main(){
    system("color 0a");
    //map logic
    for (int x = 0; x < mapW; x++)
    {
        for (int y = 0; y < mapH; y++)
        {
            if(x == mapW -1 || x == 0 || y == mapH -1){
                map[x][y] = wall;
            }else{
                map[x][y] = background;
                if(rand() % 100 > 97){
                    map[x][y] = wall;
                    obstacles[y][x] = 1;
                }
                if(rand() % 100 > 95){
                    fruits[y][x] = 1;
                    obstacles[y][x] = 0;
                }
            }
        }
    }
    //map rendering

    char pressedKey = 'd';
    renderMap();
    //game loop
    for (int x = 0; x < mapW; x++)
    {
        for (int y = 0; y < mapH; y++)
        {
            if(fruits[y][x] == 1){
                gotoxy(y,x);
                printf("A");
            }
        }
    }
    while(alive){
        updateScore();
        obstacles[snakeX][snakeY] = 1;
        if(pressedKey == 'd'){
            snakeX++;
        }
        else if(pressedKey == 'a'){
            snakeX--;
        }
        else if(pressedKey == 's'){
            snakeY++;
        }
        else if(pressedKey == 'w'){
            snakeY--;
        }
        if(kbhit()){
            pressedKey = getch();
        }
        gotoxy(snakeX, snakeY);
        printf("%c", snake);
        Sleep(150);
        if(snakeX == -1 || snakeX == mapH -1 || snakeY == 0 || snakeY == mapW -1 || obstacles[snakeX][snakeY] == 1){
            gameOver();
        }
        if(fruits[snakeX][snakeY] == 1){
            fruits[snakeY][snakeX] == 0;
            score++;
        }
    }
    return 0;
}