#ifndef CONSTANTS_H
#define CONSTANTS_H

int BOX_SIZE = 200;
int LEFT = 100;
int RIGHT = LEFT + BOX_SIZE;
int TOP = 100;
int BOTTOM = TOP + BOX_SIZE;
int BORDER_SIZE = 10;
int SNAKE_WIDTH = 10;
int DELAY_TIME_MS = 600;
int MAX_SIZE_OF_SNAKE = (BOX_SIZE * BOX_SIZE) / (SNAKE_WIDTH * SNAKE_WIDTH);
int UP_DIR = 72, DOWN_DIR = 80, LEFT_DIR = 75 , RIGHT_DIR = 77;

char WON_MESSAGE[8] = "You Won";
char LOST_MESSAGE[9] = "You Lost";
char TITLE_OF_APP[21] = "Snake Game by Rupesh";

#endif