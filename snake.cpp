#include <graphics.h>
#include <stdio.h>
#include <vector>
#include "constants.h"
#include "helper.cpp"
using namespace std;

int main() {

    initwindow(getmaxwidth()/2, getmaxheight()/2);

    vector<vector<int>> visited { vector<int>{(TOP + BOTTOM)/2, (TOP + BOTTOM)/2}};
    int direction = RIGHT_DIR, tempDir;
    int locationToEat[2];
    vector<int> nextLocToVisit;
    setLocationToEat(locationToEat, visited);

 
    while (1) {
        setactivepage(0);
        cleardevice();
        drawBoundary();
        drawScore(visited.size());
        drawLocationToEat(locationToEat);
        setvisualpage(0);

        if(kbhit()) {
            getch();

            tempDir = int(getch());
            if(isValidMove(direction, tempDir)) {
                direction = tempDir;
            } 
        }
        nextLocToVisit = getNextLocToVisit(visited[0], direction);
        visited.insert(visited.begin(), nextLocToVisit);

        if(locationToEat[0] == nextLocToVisit[0] && locationToEat[1] == nextLocToVisit[1]) {
            if(visited.size() == MAX_SIZE_OF_SNAKE) {
                setExitScreen(WON_MESSAGE);
            }
            setLocationToEat(locationToEat, visited); 
        } else {
            visited.pop_back();
            
        }

        setactivepage(1);
        cleardevice();
        drawBoundary();
        drawLocationToEat(locationToEat);
        drawScore(visited.size());
        drawSnake(visited);
        setvisualpage(1);

        if(isGameOver(visited)) {
            setExitScreen(LOST_MESSAGE);
        }
        delay(DELAY_TIME_MS);         
    }
    return 0;
}