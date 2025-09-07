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
    float vx;
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;
TObject *block = NULL;
int blockCount;

TObject *moving = NULL;
int movingCount;

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
    (*obj).IsFLy = false;
    (*obj).vx = 0.2;
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

void DeleteMoving(int i) {
    movingCount--;
    moving[i] = moving[movingCount];
    moving = (TObject*)realloc(moving, movingCount * sizeof(TObject));
}

void MarioCollision() {
    for (int i = 0; i < movingCount; i++) {
        if (IsCollide(mario, moving[i])) {
            if (mario.IsFLy && (mario.vy > 0) && 
        mario.y + mario.h < moving[i].y + moving[i].h / 2) {
                DeleteMoving(i);
                i--;
                continue;
            }
            else {
                CreateLevel(level);
            }
        }
    }
}

void HorizontalMove(TObject* obj) {
    obj[0].x += obj[0].vx;
    for (int i = 0; i < blockCount; i++) {
        if (IsCollide(*obj, block[i])) {
            obj[0].x -= obj[0].vx;
            obj[0].vx = -obj[0].vx;
            return;
        }
    }
    TObject temp = *obj;
    VerticalMove(&temp);
    if (temp.IsFLy) {
        obj[0].x -= obj[0].vx;
        obj[0].vx = -obj[0].vx;
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

TObject *AddNewBlock() {
    blockCount++;
    block = (TObject*)realloc(block, blockCount * sizeof(TObject));
    return block + (blockCount - 1);
}

TObject *AddNewMoving() {
    movingCount++;
    moving = (TObject*)realloc(moving, movingCount * sizeof(TObject));
    return moving + (movingCount - 1);
}

void CreateLevel(int lvl) {
    if (lvl == 1) {
    InitObject(&mario, 39, 10, 3, 3, '@');
    
    blockCount = 0;
    InitObject(AddNewBlock(), 20, 20, 40, 5, '#');
    InitObject(AddNewBlock(), 60, 15, 10, 10, '#');
    InitObject(AddNewBlock(), 80, 20, 20, 5, '#');
    InitObject(AddNewBlock(), 120, 15, 10, 10, '#');
    InitObject(AddNewBlock(), 150, 20, 40, 5, '#');
    InitObject(AddNewBlock(), 210, 15, 10, 10, '+');
    movingCount = 0;  
    InitObject(AddNewMoving(), 25, 10, 3, 2, 'o');
    InitObject(AddNewMoving(), 80, 10, 3, 2, 'o');
    InitObject(AddNewMoving(), 65, 10, 3, 2, 'o');
    InitObject(AddNewMoving(), 120, 10, 3, 2, 'o');
    InitObject(AddNewMoving(), 160, 10, 3, 2, 'o');
    InitObject(AddNewMoving(), 175, 10, 3, 2, 'o');
    
    }

    if (lvl == 2) {
    InitObject(&mario, 39, 10, 3, 3, '@');

    blockCount = 0;
    InitObject(AddNewBlock(), 20, 20, 40, 5, '#');
    InitObject(AddNewBlock(), 80, 20, 15, 5, '#');
    InitObject(AddNewBlock(), 120, 15, 10, 10, '#');
    InitObject(AddNewBlock(), 160, 10, 15, 15, '#');
    InitObject(AddNewBlock(), 200, 20, 20, 5, '#');
    InitObject(AddNewBlock(), 240, 15, 10, 10, '+');
    movingCount = 0;
    InitObject(AddNewMoving(), 25, 10, 3, 2, 'o');
    InitObject(AddNewMoving(), 85, 10, 3, 2, 'o');
    InitObject(AddNewMoving(), 130, 10, 3, 2, 'o');
    InitObject(AddNewMoving(), 165, 5, 3, 2, 'o');
    InitObject(AddNewMoving(), 180, 5, 3, 2, 'o');
    InitObject(AddNewMoving(), 195, 5, 3, 2, 'o');
    InitObject(AddNewMoving(), 210, 5, 3, 2, '+');

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
    for (int i = 0; i < movingCount; i++) {
        moving[i].x += dx;
    }
}

int main() {
    CreateLevel(level);
    system("color 0B");

    do {
    ClearMap();

    if ((GetKeyState(VK_SPACE) < 0) && (!mario.IsFLy)) {
        mario.vy = -1.2;
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
    MarioCollision();

    for (int i = 0; i < blockCount; i++) {
        PlaceObject(block[i]);
    }
    for (int i = 0; i < movingCount; i++) {
        VerticalMove(moving + i);
        HorizontalMove(moving + i);
        if (moving[i].y < 0) {
            DeleteMoving(i);
            i--;
            continue;
        }
        PlaceObject(moving[i]);
    }    

    PlaceObject(mario);
    setCursorPosition(0, 0);
    PrintMap();

    Sleep(10);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}