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
int score;
int maxlvl;

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

void CreateLevel(int lvl);

void PlayerDeath() {
    system("color 4F");
    Sleep(500);
    CreateLevel(level);
}

bool IsCollide(TObject obj1, TObject obj2);
TObject *AddNewMoving();

void VerticalMove(TObject* obj) {
    (*obj).vy += 0.05;
    (*obj).IsFLy = true;
    SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vy);

    for (int i = 0; i < blockCount; i++) {
        if (IsCollide(*obj, block[i])) {
            if (obj[0].vy > 0) {
                obj[0].IsFLy = false;
            }
            if ((block[i].type == '?') && (obj[0].vy < 0) && (obj == &mario)) {
                block[i].type = '-';
                InitObject(AddNewMoving(), block[i].x, block[i].y - 3, 3, 2, '$');
                moving[movingCount - 1].vy = -0.7;
            }
            (*obj).y -= ((*obj).vy);
            (*obj).vy = 0;
            if (block[i].type == '+') {
                level++;
                if (level > maxlvl) level = 1;

                system("color 2F");
                Sleep(500);
                CreateLevel(level);
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
            if (moving[i].type == 'o') {
                if (mario.IsFLy && (mario.vy > 0) && 
            mario.y + mario.h < moving[i].y + moving[i].h / 2) {
                    score += 50;
                    DeleteMoving(i);
                    i--;
                    continue;
                }
                else {
                    PlayerDeath();
                }
            }
            if (moving[i].type == '$') {
                score += 100;
                DeleteMoving(i);
                i--;
                continue;
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
    if (obj[0].type == 'o') {
        TObject temp = *obj;
        VerticalMove(&temp);
        if (temp.IsFLy) {
            obj[0].x -= obj[0].vx;
            obj[0].vx = -obj[0].vx;
        }
    }
}

bool IsOnMap(TObject obj) {
    return ((obj.y + obj.h) < mapHeight) && (obj.y >= 0) && ((obj.x + obj.w) < mapWidth) &&
           (obj.x >= 0);
}

bool IsCollide(TObject obj1, TObject obj2) {
    return (obj1.x < (obj2.x + obj2.w)) && ((obj1.x + obj1.w) > obj2.x) &&
           (obj1.y < (obj2.y + obj2.h)) && ((obj1.y + obj1.h) > obj2.y);
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

void ShowScore() {
    char c[30];
    char s[10];
    sprintf(c, "Score: %d", score);
    sprintf(s, "Lvl: %d", level);
    int len_c = strlen(c);
    int len_s = strlen(s);
    for (int i = 0; i < len_c; i++) {
        map[1][i + 5] = c[i];
    }
    for (int i = 0; i < len_s; i++) {
        map[1][mapWidth - len_s - 5 + i] = s[i];
    }
}

void CreateLevel(int lvl) {

    system("color 0B");

    blockCount = 0;
    block = (TObject*)realloc(block, blockCount * sizeof(TObject));
    movingCount = 0;
    moving = (TObject*)realloc(moving, movingCount * sizeof(TObject));

    InitObject(&mario, 39, 10, 3, 3, '@');
    score = 0;

    if (lvl == 1) {
        InitObject(AddNewBlock(), 20, 20, 40, 5, '#');
            InitObject(AddNewBlock(), 30, 10, 5, 3, '?');
            InitObject(AddNewBlock(), 50, 10, 5, 3, '?');
        InitObject(AddNewBlock(), 60, 15, 40, 10, '#');
            InitObject(AddNewBlock(), 60, 5, 10, 3, '-');
            InitObject(AddNewBlock(), 70, 5, 5, 3, '?');
            InitObject(AddNewBlock(), 75, 5, 5, 3, '-');
            InitObject(AddNewBlock(), 80, 5, 5, 3, '?');
            InitObject(AddNewBlock(), 85, 5, 10, 3, '-');
        InitObject(AddNewBlock(), 100, 20, 20, 5, '#');
        InitObject(AddNewBlock(), 120, 15, 10, 10, '#');
        InitObject(AddNewBlock(), 150, 20, 40, 5, '#');
        InitObject(AddNewBlock(), 210, 15, 10, 10, '+');

        InitObject(AddNewMoving(), 25, 10, 3, 2, 'o');
        InitObject(AddNewMoving(), 80, 10, 3, 2, 'o');
    }

    if (lvl == 2) {
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

    if (lvl == 3) {
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
    maxlvl = 3;
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
        PlayerDeath();
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
    ShowScore();
    setCursorPosition(0, 0);
    PrintMap();

    Sleep(10);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}