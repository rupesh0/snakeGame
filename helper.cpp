#include <graphics.h>
#include <vector>
#include "constants.h"


void drawBoundary(){
    //Borders
    rectangle(LEFT - BORDER_SIZE, TOP, LEFT, BOTTOM); // Left border
    rectangle(LEFT - BORDER_SIZE, TOP - BORDER_SIZE, RIGHT + BORDER_SIZE, TOP);  // Top border
    rectangle(RIGHT, TOP, RIGHT + BORDER_SIZE, BOTTOM); // Right border
    rectangle(LEFT - BORDER_SIZE, BOTTOM, RIGHT + BORDER_SIZE, BOTTOM + BORDER_SIZE); // Bottom border

    // Color borders
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(TOP - 1, LEFT - 1, WHITE); // Top rectangle
    floodfill(BOTTOM + 1, RIGHT + 1, WHITE); // Bottom rectangle
    floodfill(TOP - 1, RIGHT - 1 , WHITE); // Left rectangle
    floodfill(BOTTOM + 1,LEFT + 1 , WHITE); // Right rectangle

}


void drawLocationToEat(int currentLocationToEat[]){
    int x = currentLocationToEat[0];
    int y = currentLocationToEat[1];

    rectangle(x, y, x+ SNAKE_WIDTH, y + SNAKE_WIDTH);
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(x+ 1, y + 1, WHITE);      
}

void drawSnake(std::vector<std::vector<int>> visited){
    for(int i = visited.size() - 1; i >= 0; i--) {
        int x = visited[i][0];
        int y = visited[i][1];

        rectangle(x, y, x+ SNAKE_WIDTH, y + SNAKE_WIDTH);
        setfillstyle(SOLID_FILL, i == 0 ? BLUE : LIGHTBLUE);
        floodfill(x+ 1, y + 1, WHITE);
    }
}

void drawScore(int score) {
    char scoreStr[30] = "Score: ";
    char integerString[32];
    sprintf(integerString, "%d", score);
    strcat(scoreStr, integerString); 
    settextstyle(4, 0, 3);
    outtextxy( RIGHT + 40, (TOP + BOTTOM)/2, scoreStr); 
}

void setExitScreen(char* text) {
    setactivepage(2);
    settextstyle(8, 0, 5);
    outtextxy((LEFT + RIGHT)/2, (TOP + BOTTOM)/2, text); 
    setvisualpage(2);
    getch();
    exit(0);
}


void setLocationToEat(int locationToEat[], std::vector<std::vector<int>> visited) {
    while(1) {
            int x = rand() % BOX_SIZE + LEFT;
            int y = rand() % BOX_SIZE + TOP;
            x = x / 10;
            x = x * 10;
            y = y / 10;
            y = y * 10;

            bool isOverlap = false;
            for(int i = 0; i < visited.size(); i++) {
                if(visited[i][0] == x && visited[i][1] == y) {
                    isOverlap = true;
                    break;
                }
            }

            if(!isOverlap) {
                locationToEat[0] = x;
                locationToEat[1] = y;
                break;
            }   
        }
}

std::vector<int> getNextLocToVisit(std::vector<int> currLoc, int direction){
    std::vector<int> nextLoc {currLoc[0], currLoc[1]};

    if(direction == UP_DIR) {
        nextLoc[1] = nextLoc[1] - SNAKE_WIDTH;
    } else if(direction == DOWN_DIR) {
        nextLoc[1] = nextLoc[1] + SNAKE_WIDTH;
    } else if(direction == LEFT_DIR) {
        nextLoc[0] = nextLoc[0] - SNAKE_WIDTH;
    } else if(direction == RIGHT_DIR) {
        nextLoc[0] = nextLoc[0] + SNAKE_WIDTH;
    }
    return nextLoc;
}


bool isGameOver(std::vector<std::vector<int>> visited){
    int minX = visited[0][0];
    int maxX = minX + SNAKE_WIDTH;
    int minY = visited[0][1];
    int maxY = minY + SNAKE_WIDTH;

    // Border touch
    if(minX < LEFT || maxX > RIGHT || minY < TOP || maxY > BOTTOM) {
        return true;
    }

    // There is no posibility to bit himself with size of 4.
    if(visited.size() <= 4) {
        return false;
    }

    // Snake bite himself
    for(int i = 0; i < visited.size(); i++) {
        for(int j = i + 1; j < visited.size(); j++) {
            if(visited[i][0] == visited[j][0]  && visited[i][1] == visited[j][1] ) {
                return true;
            }
        }
    }
    return false;
}

bool isValidMove(int direction, int tempDir) {
    return !(
        (direction == UP_DIR && tempDir == DOWN_DIR)   || 
        (direction == DOWN_DIR && tempDir == UP_DIR)   || 
        (direction == LEFT_DIR && tempDir == RIGHT_DIR)||
        (direction == RIGHT_DIR && tempDir == LEFT_DIR)
    );
}

