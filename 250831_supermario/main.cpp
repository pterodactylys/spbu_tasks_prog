#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#define mapWidth 120
#define mapHeight 30

typedef struct SObject {
    float x, y;
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;

void ClearMap() {
    for (int i = 0; i < mapWidth; i++) {
        map[0][i] = '.';
    }
    map[0][mapWidth] = '\0';
    for (int j = 0; j < mapHeight; j++) {
        sprintf(map[j], map[0]);
    }
}

void PrintMap() {
    map[mapHeight - 1][mapWidth - 1] = '\0';
    for (int j = 0; j < mapHeight; j++) {
        printf("%s", map[j]);
    }
}

void SetObjectPos(TObject* obj, float xPos, float yPos) {
    (*obj).x = xPos;
    (*obj).y = yPos;
}

void PlaceObject(TObject obj) {
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    map[iy][ix] = 'M';
}

int main() {
    SetObjectPos(&mario, 20, 10);
    ClearMap();
    PlaceObject(mario);
    PrintMap();
    return 0;
}