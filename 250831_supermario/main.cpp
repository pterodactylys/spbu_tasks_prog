#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <windows.h>

#define mapWidth 120
#define mapHeight 30

typedef struct SObject {
    float x, y;
    float w, h;
    float vy;
    bool IsFLy;
    char type;
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;
TObject *block = NULL;
int blockCount;
int level = 1;

void ClearMap() {
    for (int i = 0; i < mapWidth; i++) {
        map[0][i] = ' ';
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

void InitObject(TObject* obj, float xPos, float yPos, float width,
                float height, char ctype) {
    SetObjectPos(obj, xPos, yPos);
    (*obj).w = width;
    (*obj).h = height;
    (*obj).vy = 0;
    (*obj).type = ctype;
}

bool IsCollide(TObject obj1, TObject obj2);
void CreateLevel(int lvl);

void VerticalMove(TObject* obj) {
    (*obj).vy += 0.05;
    (*obj).IsFLy = true;
    SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vy);

    for (int i = 0; i < blockCount; i++) {
        if (IsCollide(*obj, block[i])) {
            (*obj).y -= ((*obj).vy);
            (*obj).vy = 0;
            (*obj).IsFLy = false;
            if (block[i].type == '+') {
                if (level == 1) {
                    level = 2;
                }
                else {
                    level = 1;
                }
                CreateLevel(level);
                Sleep(1000);
            }
            break;
        }
    }       
}

bool IsOnMap(TObject obj) {
    return ((obj.y + obj.h) < mapHeight) && (obj.y >= 0) && ((obj.x + obj.w) < mapWidth) &&
           (obj.x >= 0);
}

bool IsCollide(TObject obj1, TObject obj2) {
    return !((obj1.x + obj1.w <= obj2.x) || (obj1.x >= obj2.x + obj2.w) ||
             (obj1.y + obj1.h <= obj2.y) || (obj1.y >= obj2.y + obj2.h));
}

void CreateLevel(int lvl) {
    if (lvl == 1) {
    InitObject(&mario, 39, 10, 3, 3, '@');
    
    blockCount = 6;
    block = (TObject*)realloc(block, blockCount * sizeof(TObject));
    InitObject(block+0, 20, 20, 40, 5, '#');
    InitObject(block+1, 60, 15, 10, 10, '#');
    InitObject(block+2, 80, 20, 20, 5, '#');
    InitObject(block+3, 120, 15, 10, 10, '#');
    InitObject(block+4, 150, 20, 40, 5, '#');
    InitObject(block+5, 210, 15, 10, 10, '+');
    }

    if (lvl == 2) {
    InitObject(&mario, 39, 10, 3, 3, '@');

    blockCount = 8;
    block = (TObject*)realloc(block, blockCount * sizeof(TObject));
    InitObject(block+0, 20, 20, 40, 5, '#');
    InitObject(block+1, 60, 15, 10, 10, '#');
    InitObject(block+2, 80, 20, 20, 5, '#');
    InitObject(block+3, 120, 15, 10, 10, '#');
    InitObject(block+4, 150, 20, 40, 5, '#');
    InitObject(block+5, 210, 15, 10, 10, '#');
    InitObject(block+6, 240, 10, 10, 10, '#');
    InitObject(block+7, 270, 5, 10, 10, '+');
    }
}

void PlaceObject(TObject obj) {
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iw = (int)round(obj.w);
    int ih = (int)round(obj.h);

    for (int i = ix; i < (ix + iw); i++) {
        for (int j = iy; j < (iy + ih); j++) {
            if (IsOnMap(obj)) {
            map[j][i] = obj.type;
            }
        }
    }
}

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void HorizontalMapMove(float dx) {
    mario.x -= dx;
    for (int i = 0; i < blockCount; i++) {
        if (IsCollide(mario, block[i])) {
            mario.x += dx;
            return;
        }
    }
    mario.x += dx;
    for (int i = 0; i < blockCount; i++) {
        block[i].x += dx;
    }
}

int main() {
    CreateLevel(level);
    system("color 0B");

    do {
    ClearMap();

    if ((GetKeyState(VK_SPACE) < 0) && (!mario.IsFLy)) {
        mario.vy = -0.8;
    }

    if (GetKeyState(VK_LEFT) < 0) {
        HorizontalMapMove(1);
    }
    if (GetKeyState(VK_RIGHT) < 0) {
        HorizontalMapMove(-1);
    }
    
    if (mario.y > mapHeight) {
        CreateLevel(level);
    }

    VerticalMove(&mario);
    for (int i = 0; i < blockCount; i++) {
        PlaceObject(block[i]);
    }
    PlaceObject(mario);
    setCursorPosition(0, 0);
    PrintMap();

    Sleep(10);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}