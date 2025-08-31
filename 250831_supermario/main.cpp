#include <iostream>

#define mapWidth 80
#define mapHeight 25

char map[mapHeight][mapWidth + 1];

void ClearMap() {
    for (int y = 0; y < mapHeight; y++) {
        map[y][0] = '#';
        for (int x = 1; x < mapWidth; x++) {
            map[y][x] = '.';
        }
        map[y][mapWidth - 1] = '#';
    }
}

void PrintMap() {
    for (int y = 0; y < mapHeight; y++) {
        map[y][mapWidth] = '\0'; // Null-terminate each row
        std::cout << map[y] << std::endl;
    }
}

int main() {
    ClearMap();
    PrintMap();
    return 0;
}