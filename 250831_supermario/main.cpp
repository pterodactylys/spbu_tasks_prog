#include <cmath>
#include <iostream>
#include <windows.h>


const int mapWidth = 120;
const int mapHeight = 30;
const int maxlvl = 3;

const float gravity = 0.05;
const float default_velocity = 0.2;
const float jump_velocity = -1.0;
const float player_velocity = 1.0;

const int playerWidth = 3;
const int playerHeight = 3;

const int coin_reward = 100;
const int monster_reward = 50;


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
TObject *block = nullptr;
int blockCount;

TObject *moving = nullptr;
int movingCount;

int level = 1;
int score;

TObject *add_new_block(TObject*& block, int& blockCount);
TObject *add_new_moving(TObject*& moving, int& movingCount);
void clear_map(char map[mapHeight][mapWidth + 1], int mapWidth, int mapHeight);
void create_level(int lvl, int mapWidth, int mapHeight, int playerWidth,
     int playerHeight, int maxlvl);
void delete_moving(TObject*& moving, int& movingCount, int i);
void hide_cursor();
void move_object_vertically(TObject* obj); // если добавить gravity то программа ломается
void move_map_horizontally(float dx, int blockCount, int movingCount);
void move_objects_horizontally(TObject* obj, TObject* block, int blockCount, float gravity);
void init_object(TObject* obj, float xPos, float yPos, float width, float height,
     char ctype, float defaultVelocity);
bool is_collide(TObject obj1, TObject obj2);
bool is_on_map(int x, int y, int mapWidth, int mapHeight);
//void check_mario_collision(int movingCount,
// int monsterReward, int coinReward); // программа начинает зависать при коллизии марио с объектами
void check_mario_collision();
void place_object(char map[mapHeight][mapWidth + 1], TObject obj, int mapWidth, int mapHeight);
void player_die(int level, int mapWidth, int mapHeight, int playerWidth, int playerHeight, int maxlvl);
void print_map(char map[mapHeight][mapWidth + 1], int mapHeight, int mapWidth);
void set_cursor_position(int x, int y);
void set_object_pos(TObject* obj, float xPos, float yPos);
void show_cursor();
void ShowScore(char map[mapHeight][mapWidth + 1], int score, int level, int mapWidth);



int main() {
    hide_cursor();
    create_level(level, mapWidth, mapHeight, playerWidth,
         playerHeight, maxlvl);

    do {
    clear_map(map, mapWidth, mapHeight);

    if ((GetKeyState(VK_SPACE) < 0) && (!mario.IsFLy)) {
        mario.vy = jump_velocity;
    }

    if ((GetKeyState(VK_LEFT) < 0) || (GetKeyState('A') < 0)) {
        move_map_horizontally(player_velocity, blockCount, movingCount);
    }
    if ((GetKeyState(VK_RIGHT) < 0) || (GetKeyState('D') < 0)) {
        move_map_horizontally(-player_velocity, blockCount, movingCount);
    }
    
    if (mario.y > mapHeight) {
        player_die(level, mapWidth, mapHeight, playerWidth, playerHeight, maxlvl);
    }

    move_object_vertically(&mario);
    check_mario_collision();

    for (int i = 0; i < blockCount; i++) {
        place_object(map, block[i], mapWidth, mapHeight);
    }
    for (int i = 0; i < movingCount; i++) {
        move_object_vertically(moving + i);
        move_objects_horizontally(moving + i, block, blockCount, gravity);
        if (moving[i].y < -10) {
            delete_moving(moving, movingCount, i);
            i--;
            continue;
        }
        place_object(map, moving[i], mapWidth, mapHeight);
    }    

    place_object(map, mario, mapWidth, mapHeight);
    ShowScore(map, score, level, mapWidth);
    set_cursor_position(0, 0);
    print_map(map, mapHeight, mapWidth);

    Sleep(10);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);
    show_cursor();
    
    delete[] block;
    delete[] moving;

    return 0;
}


TObject *add_new_block(TObject*& block, int& blockCount) {
    TObject* newBlock = new TObject[blockCount + 1];
    for (int i = 0; i < blockCount; i++) {
        newBlock[i] = block[i];
    }
    delete[] block;
    block = newBlock;
    blockCount++;
    return block + (blockCount - 1);
}

TObject *add_new_moving(TObject*& moving, int& movingCount) {
    TObject* newMoving = new TObject[movingCount + 1];
    for (int i = 0; i < movingCount; i++) {
        newMoving[i] = moving[i];
    }
    delete[] moving;
    moving = newMoving;
    movingCount++;
    return moving + (movingCount - 1);
}

void clear_map(char map[mapHeight][mapWidth + 1], int mapWidth, int mapHeight) {
    for (int i = 0; i < mapWidth; i++) {
        map[0][i] = ' ';
    }
    map[0][mapWidth] = '\0';
    for (int j = 0; j < mapHeight; j++) {
        sprintf(map[j], map[0]);
    }
}

void create_level(int lvl, int mapWidth, int mapHeight, int playerWidth,
     int playerHeight, int maxlvl) {

    system("color 0B");

    delete[] block;
    delete[] moving;

    blockCount = 0;
    block = nullptr;
    movingCount = 0;
    moving = nullptr;

    init_object(&mario, 39, 10, playerWidth, playerHeight, '@', default_velocity);
    score = 0;

    if (lvl == 1) {
        init_object(add_new_block(block, blockCount), 20, 20, 40, 5, '#', default_velocity);
            init_object(add_new_block(block, blockCount), 30, 10, 5, 3, '?', default_velocity);
            init_object(add_new_block(block, blockCount), 50, 10, 5, 3, '?', default_velocity);
        init_object(add_new_block(block, blockCount), 60, 15, 40, 10, '#', default_velocity);
            init_object(add_new_block(block, blockCount), 60, 5, 10, 3, '-', default_velocity);
            init_object(add_new_block(block, blockCount), 70, 5, 5, 3, '?', default_velocity);
            init_object(add_new_block(block, blockCount), 75, 5, 5, 3, '-', default_velocity);
            init_object(add_new_block(block, blockCount), 80, 5, 5, 3, '?', default_velocity);
            init_object(add_new_block(block, blockCount), 85, 5, 10, 3, '-', default_velocity);
        init_object(add_new_block(block, blockCount), 100, 20, 20, 5, '#', default_velocity);
        init_object(add_new_block(block, blockCount), 120, 15, 10, 10, '#', default_velocity);
        init_object(add_new_block(block, blockCount), 150, 20, 40, 5, '#', default_velocity);
        init_object(add_new_block(block, blockCount), 210, 15, 10, 10, '+', default_velocity);

        init_object(add_new_moving(moving, movingCount), 25, 10, 3, 2, 'o', default_velocity);
        init_object(add_new_moving(moving, movingCount), 80, 10, 3, 2, 'o', default_velocity);
    }

    else if (lvl == 2) {
        init_object(add_new_block(block, blockCount), 20, 20, 40, 5, '#', default_velocity);
        init_object(add_new_block(block, blockCount), 60, 15, 10, 10, '#', default_velocity);
        init_object(add_new_block(block, blockCount), 80, 20, 20, 5, '#', default_velocity);
        init_object(add_new_block(block, blockCount), 120, 15, 10, 10, '#', default_velocity);
        init_object(add_new_block(block, blockCount), 150, 20, 40, 5, '#', default_velocity);
        init_object(add_new_block(block, blockCount), 210, 15, 10, 10, '+', default_velocity);
        movingCount = 0;  
        init_object(add_new_moving(moving, movingCount), 25, 10, 3, 2, 'o', default_velocity);
        init_object(add_new_moving(moving, movingCount), 80, 10, 3, 2, 'o', default_velocity);
        init_object(add_new_moving(moving, movingCount), 65, 10, 3, 2, 'o', default_velocity);
        init_object(add_new_moving(moving, movingCount), 120, 10, 3, 2, 'o', default_velocity);
        init_object(add_new_moving(moving, movingCount), 160, 10, 3, 2, 'o', default_velocity);
        init_object(add_new_moving(moving, movingCount), 175, 10, 3, 2, 'o', default_velocity);
    
    }

    else if (lvl == 3) {
        init_object(add_new_block(block, blockCount), 20, 20, 40, 5, '#', default_velocity);
        init_object(add_new_block(block, blockCount), 80, 20, 15, 5, '#', default_velocity);
        init_object(add_new_block(block, blockCount), 120, 15, 10, 10, '#', default_velocity);
        init_object(add_new_block(block, blockCount), 160, 10, 15, 15, '#', default_velocity);
        init_object(add_new_block(block, blockCount), 200, 20, 20, 5, '#', default_velocity);
        init_object(add_new_block(block, blockCount), 240, 15, 10, 10, '+', default_velocity);
        movingCount = 0;
        init_object(add_new_moving(moving, movingCount), 25, 10, 3, 2, 'o', default_velocity);
        init_object(add_new_moving(moving, movingCount), 85, 10, 3, 2, 'o', default_velocity);
        init_object(add_new_moving(moving, movingCount), 130, 10, 3, 2, 'o', default_velocity);
        init_object(add_new_moving(moving, movingCount), 165, 5, 3, 2, 'o', default_velocity);
        init_object(add_new_moving(moving, movingCount), 180, 5, 3, 2, 'o', default_velocity);
        init_object(add_new_moving(moving, movingCount), 195, 5, 3, 2, 'o', default_velocity);
        init_object(add_new_moving(moving, movingCount), 210, 5, 3, 2, '+', default_velocity);

    }
}

void delete_moving(TObject*& moving, int& movingCount, int i) {
    movingCount--;
    moving[i] = moving[movingCount];
    if (movingCount == 0) {
        delete[] moving;
        moving = nullptr;
        return;
    } else {
        TObject* newMoving = new TObject[movingCount];
        for (int j = 0; j < movingCount; j++) {
            newMoving[j] = moving[j];
        }
        delete[] moving;
        moving = newMoving;
    }
}

void hide_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void move_map_horizontally(float dx, int blockCount, int movingCount) {
    mario.x -= dx;
    for (int i = 0; i < blockCount; i++) {
        if (is_collide(mario, block[i])) {
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

void move_objects_horizontally(TObject* obj, TObject* block, int blockCount, float gravity) {
    obj -> x += obj -> vx;
    for (int i = 0; i < blockCount; i++) {
        if (is_collide(*obj, block[i])) {
            obj -> x -= obj -> vx;
            obj -> vx = -obj -> vx;
            return;
        }
    }
    if (obj ->type == 'o') {
        TObject temp = *obj;
        move_object_vertically(&temp);
        if (temp.IsFLy) {
            obj -> x -= obj -> vx;
            obj -> vx = -obj -> vx;
        }
    }
}

void init_object(TObject* obj, float xPos, float yPos, float width, float height,
     char ctype, float defaultVelocity) {
    set_object_pos(obj, xPos, yPos);
    (obj -> w) = width;
    (obj -> h) = height;
    (obj -> vy) = 0;
    (obj -> type) = ctype;
    (obj -> IsFLy) = false;
    (obj -> vx) = default_velocity;
}

bool is_collide(TObject obj1, TObject obj2) {
    return (obj1.x < (obj2.x + obj2.w)) && ((obj1.x + obj1.w) > obj2.x) &&
           (obj1.y < (obj2.y + obj2.h)) && ((obj1.y + obj1.h) > obj2.y);
}

bool is_on_map(int x, int y, int mapWidth, int mapHeight) {
    return ( (x >= 0) && (x < mapWidth) && 
             (y >= 0) && (y < mapHeight) );
}


void check_mario_collision() {
    for (int i = 0; i < movingCount; i++) {
        if (is_collide(mario, moving[i])) {
            if (moving[i].type == 'o') {
                if (mario.IsFLy && (mario.vy > 0) && 
            mario.y + mario.h < moving[i].y + moving[i].h / 2) {
                    score += monster_reward;
                    delete_moving(moving, movingCount, i);
                    i--;
                    continue;
                }
                else {
                    player_die(level, mapWidth, mapHeight, playerWidth, playerHeight, maxlvl);
                }
            }
            if (moving[i].type == '$') {
                score += coin_reward;
                delete_moving(moving, movingCount, i);
                i--;
                continue;
            }
        }
    }
}

void place_object(char map[mapHeight][mapWidth + 1], TObject obj, int mapWidth, int mapHeight) {
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iw = (int)round(obj.w);
    int ih = (int)round(obj.h);

    for (int i = ix; i < (ix + iw); i++) {
        for (int j = iy; j < (iy + ih); j++) {
            if (is_on_map(i, j, mapWidth, mapHeight)) {
            map[j][i] = obj.type;
            }
        }
    }
}

void player_die(int level, int mapWidth, int mapHeight, int playerWidth, int playerHeight, int maxlvl) {
    system("color 4F");
    Sleep(500);
    create_level(level, mapWidth, mapHeight, playerWidth, playerHeight, maxlvl);
}

void print_map(char map[mapHeight][mapWidth + 1], int mapHeight, int mapWidth) {
    map[mapHeight - 1][mapWidth - 1] = '\0';
    for (int j = 0; j < mapHeight; j++) {
        std::cout << map[j];
    }
}

void set_cursor_position(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_object_pos(TObject* obj, float xPos, float yPos) {
    obj -> x = xPos;
    obj -> y = yPos;
}

void show_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo = {1, 1};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void ShowScore(char map[mapHeight][mapWidth + 1], int score, int level, int mapWidth) {
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

void move_object_vertically(TObject* obj) {
    obj -> vy += gravity;
    obj -> IsFLy = true;
    set_object_pos(obj, obj -> x, obj -> y + obj -> vy);

    for (int i = 0; i < blockCount; i++) {
        if (is_collide(*obj, block[i])) {
            if (obj -> vy > 0) {
                obj -> IsFLy = false;
            }
            if ((block[i].type == '?') && (obj -> vy < 0) && (obj == &mario)) {
                block[i].type = '-';
                init_object(add_new_moving(moving, movingCount), block[i].x, block[i].y - 3, 3, 2, '$', default_velocity);
                moving[movingCount - 1].vy = -0.7;
            }
            obj -> y -= obj -> vy;
            obj -> vy = 0;
            if (block[i].type == '+') {
                level++;
                if (level > maxlvl) level = 1;

                system("color 2F");
                Sleep(500);
                create_level(level, mapWidth, mapHeight, playerWidth, playerHeight, maxlvl);
            }
            break;
        }
    }       
}

