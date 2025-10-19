#include <cmath>
#include <iostream>
#include <windows.h>

const char BRICK = '#';
const char EMPTY_BOX = '-';
const char ENEMY = 'o';
const char FULL_BOX = '?';
const char MARIO = '@';
const char MONEY = '$';
const char WIN_BRICK = '+';

struct TObject {
    float x, y;
    float w, h;
    float vy;
    bool IsFLy;
    char type;
    float vx;
};

void check_mario_collision(
    TObject& mario, 
	TObject *&blocks, int& blocksCount, 
	TObject *&movings, int& movingsCount,
	const int current_level,
	const int monster_reward, const int coin_reward, int& score
);
void clear_map(char **map, int mapWidth, int mapHeight);
void create_level(
    const int lvl,
    TObject& mario,
    TObject*& block, int& blockCount,
    TObject*& moving, int& movingCount,
    int& score);
void delete_movings(TObject*& moving, int& movingCount, int i);
void hide_cursor();
void init_object(TObject* obj,
    float xPos, float yPos,
    float width, float height,
    char ctype);
bool is_collide(TObject *obj1, TObject *obj2);
bool is_on_map(int x, int y, int mapWidth, int mapHeight);
void move_map_horizontally(
    const float dx,
    TObject &mario,
    TObject *blocks, const int blocksCount,
    TObject *movings, int& movingsCount);
void move_objects_horizontally(
    TObject* obj,
    TObject& mario,
    TObject* blocks, int& blocksCount,
    TObject* movings, int& movingsCount,
    int& current_level,
    const int maxlvl,
    int& score,
    const float gravity
);
void move_objects_vertically(
    TObject* obj,
    TObject &mario,
    TObject *&blocks, int& blocksCount,
    TObject *&movings, int& movingsCount,
    int& current_level,
    const int maxlvl,
    int& score,
    const float gravity
);
void place_object(
    TObject* obj,
    char **map, const int mapWidth, const int mapHeight);
void player_die(
    TObject& mario,
    TObject *&blocks, int& blocksCount,
    TObject *&movings, int& movingsCount,
    const int current_level,
    int& score
);
void print_map(char **map, int mapHeight, int mapWidth);
void set_cursor_position(int x, int y);
void set_object_pos(TObject* obj, float xPos, float yPos);
void show_cursor();
void ShowScore(char **map,
    int score, int level, int mapWidth);


int main() {
    hide_cursor();
    
    const int mapWidth = 200;
    const int mapHeight = 25;

    const float gravity = 0.05;
    const float default_velocity = 0.2;
    const float jump_velocity = -1.0;
    const float player_velocity = 1.0;

    const int playerWidth = 3;
    const int playerHeight = 3;

    const int coin_reward = 100;
    const int monster_reward = 50;

    char **map = new char*[mapHeight];
    for (int i = 0; i < mapHeight; i++) {
        map[i] = new char[mapWidth + 1];
    }

    TObject mario;
    TObject *blocks = nullptr;
    int blocksCount;

    TObject *movings = nullptr;
    int movingsCount;

    int level = 1;
    const int maxlvl = 3;
    int score;

    create_level(
        level,
        mario,
        blocks, blocksCount,
        movings, movingsCount,
        score);

    do {
        clear_map(map, mapWidth, mapHeight);

        if ((GetKeyState(VK_SPACE) < 0) && (!mario.IsFLy)) {
            mario.vy = jump_velocity;
        }

        if ((GetKeyState(VK_LEFT) < 0) || (GetKeyState('A') < 0)) {
            move_map_horizontally(
                player_velocity,
                mario,
                blocks, blocksCount,
                movings, movingsCount
            );
        }
        if ((GetKeyState(VK_RIGHT) < 0) || (GetKeyState('D') < 0)) {
            move_map_horizontally(
                -player_velocity,
                mario,
                blocks, blocksCount,
                movings, movingsCount
            );
        }
        
        if (mario.y > mapHeight) {
            player_die(
                mario,
                blocks, blocksCount,
                movings, movingsCount,
                level,
                score);
        }

        move_objects_vertically(
            &mario, mario,
            blocks, blocksCount,
            movings, movingsCount,
            level, maxlvl,
            score,
            gravity
        );

        check_mario_collision(
            mario,
            blocks, blocksCount,
            movings, movingsCount,
            level,
            monster_reward, coin_reward, score
        );

        for (int i = 0; i < blocksCount; i++) {
            place_object(&blocks[i], map, mapWidth, mapHeight);
        }

        for (int i = 0; i < movingsCount; i++) {
            move_objects_vertically(
                &movings[i],
                mario,
                blocks, blocksCount,
                movings, movingsCount,
                level, maxlvl,
                score,
                gravity
            );
            move_objects_horizontally(
                &movings[i],
                mario,
                blocks, blocksCount,
                movings, movingsCount,
                level, maxlvl,
                score,
                gravity
            );
            if (movings[i].y > mapHeight) {
                delete_movings(movings, movingsCount, i);
                i--;
                continue;
            }
            place_object(&movings[i], map, mapWidth, mapHeight);
        }    

        place_object(&mario, map, mapWidth, mapHeight);
        ShowScore(map, score, level, mapWidth);

        set_cursor_position(0, 0);
        print_map(map, mapHeight, mapWidth);

        Sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);

    for (int i = 0; i < mapHeight; i++) {
        delete[] map[i];
    }

    delete[] map;
    delete[] blocks;
    delete[] movings;
    show_cursor();
    return 0;
}

void check_mario_collision(
    TObject& mario, 
	TObject *&blocks, int& blocksCount, 
	TObject *&movings, int& movingsCount,
	const int current_level,
	const int monster_reward, const int coin_reward, int& score
) {
    for (int i = 0; i < movingsCount; i++) {
        if (is_collide(&mario, &movings[i])) {
            if (movings[i].type == ENEMY) {
                if (mario.IsFLy && (mario.vy > 0) && 
            mario.y + mario.h < movings[i].y + movings[i].h / 2) {
                    score += monster_reward;
                    delete_movings(movings, movingsCount, i);
                    i--;
                    continue;
                }
                else {
                    player_die(
                        mario,
                        blocks, blocksCount,
                        movings, movingsCount, 
                        current_level, score);
                }
            }
            if (movings[i].type == MONEY) {
                score += coin_reward;
                delete_movings(movings, movingsCount, i);
                i--;
                continue;
            }
        }
    }
}

void clear_map(char **map, int mapWidth, int mapHeight) {
    for (int i = 0; i < mapWidth; i++) {
        map[0][i] = ' ';
    }
    map[0][mapWidth] = '\0';
    for (int j = 0; j < mapHeight; j++) {
        sprintf(map[j], map[0]);
    }
}

void create_level(
    const int lvl,
    TObject& mario,
    TObject*& blocks, int& blocksCount,
    TObject*& movings, int& movingsCount,
    int& score) {

    system("color 0B");

    delete[] blocks;
    blocks = nullptr;
    delete[] movings;
    movings = nullptr;
    blocksCount = 0;
    movingsCount = 0;

    init_object(&mario, 39, 10, 3, 3, '@');
    score = 0;

    switch (lvl) {
        case 1:
			blocksCount = 13;
			blocks = new TObject[blocksCount];
			
			init_object(&blocks[0], 20, 20, 40, 5, BRICK);
			
			init_object(&blocks[1], 30, 10, 5, 3, FULL_BOX);
			init_object(&blocks[2], 50, 10, 5, 3, FULL_BOX);
			
			init_object(&blocks[3], 60, 15, 40, 10, BRICK);
			
			init_object(&blocks[4], 60, 5, 10, 3, EMPTY_BOX);
			init_object(&blocks[5], 70, 5, 5, 3, FULL_BOX);
			init_object(&blocks[6], 75, 5, 5, 3, EMPTY_BOX);
			init_object(&blocks[7], 80, 5, 5, 3, FULL_BOX);
			init_object(&blocks[8], 85, 5, 10, 3, EMPTY_BOX);
			
			init_object(&blocks[9], 100, 20, 20, 5, BRICK);
			init_object(&blocks[10], 120, 15, 10, 10, BRICK);
			init_object(&blocks[11], 150, 20, 40, 5, BRICK);
			init_object(&blocks[12], 210, 15, 10, 10, WIN_BRICK);

			movingsCount = 2;
			movings = new TObject[movingsCount];

			init_object(&movings[0], 25, 10, 3, 2, ENEMY);
			init_object(&movings[1], 80, 10, 3, 2, ENEMY);
			break;
        case 2:
			blocksCount = 6;
			blocks = new TObject[blocksCount];
			
			init_object(&blocks[0], 20, 20, 40, 5, BRICK);
			init_object(&blocks[1], 60, 15, 10, 10, BRICK);
			init_object(&blocks[2], 80, 20, 20, 5, BRICK);
			init_object(&blocks[3], 120, 15, 10, 10, BRICK);
			init_object(&blocks[4], 150, 20, 40, 5, BRICK);
			init_object(&blocks[5], 210, 15, 10, 10, WIN_BRICK);

			movingsCount = 6;
			movings = new TObject[movingsCount];

			init_object(&movings[0], 25, 10, 3, 2, ENEMY);
			init_object(&movings[1], 80, 10, 3, 2, ENEMY);
			init_object(&movings[2], 65, 10, 3, 2, ENEMY);
			init_object(&movings[3], 120, 10, 3, 2, ENEMY);
			init_object(&movings[4], 160, 10, 3, 2, ENEMY);
			init_object(&movings[5], 175, 10, 3, 2, ENEMY);
			break;
        case 3:
			blocksCount = 4;
			blocks = new TObject[blocksCount];

			init_object(&blocks[0], 20, 20, 40, 5, BRICK);
			init_object(&blocks[1], 80, 20, 15, 5, BRICK);
			init_object(&blocks[2], 120, 15, 15, 10, BRICK);
			init_object(&blocks[3], 160, 10, 15, 15, WIN_BRICK);

			movingsCount = 6;
			movings = new TObject[movingsCount];

			init_object(&movings[0], 25, 10, 3, 2, ENEMY);
			init_object(&movings[1], 50, 10, 3, 2, ENEMY);
			init_object(&movings[2], 80, 10, 3, 2, ENEMY);
			init_object(&movings[3], 90, 10, 3, 2, ENEMY);
			init_object(&movings[4], 120, 10, 3, 2, ENEMY);
			init_object(&movings[5], 135, 10, 3, 2, ENEMY);
			break;
        default:
            break;
    }
}

void delete_movings(TObject*& movings, int& movingsCount, const int i) {
    movingsCount--;
    movings[i] = movings[movingsCount];
}

void hide_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void init_object(TObject* obj,
    float xPos, float yPos,
    float width, float height,
    char ctype) 
{
    set_object_pos(obj, xPos, yPos);
    obj->w = width;
    obj->h = height;
    obj->vy = 0;
    obj->vx = 0.2;
    obj->type = ctype;
}

bool is_collide(TObject* obj1, TObject* obj2) {
    return (
        obj1->x + obj1->w > obj2->x &&
        obj1->y + obj1->h > obj2->y &&
        obj1->x < obj2->x + obj2->w &&
        obj1->y < obj2->y + obj2->h
    );
}

bool is_on_map(const int x, const int y, const int mapWidth, const int mapHeight) {
    return x >= 0 && x < mapWidth && y >= 0 && y < mapHeight;
}

void move_map_horizontally(
    const float dx,
    TObject &mario,
    TObject *blocks, const int blocksCount,
    TObject *movings, int& movingsCount
) {
    mario.x -= dx;
    for (int i = 0; i < blocksCount; i++) {
        if (is_collide(&mario, &blocks[i])) {
            mario.x += dx;
            return;
        }
    }

    mario.x += dx;

    for (int i = 0; i < blocksCount; i++) {
        blocks[i].x += dx;
    }
    for (int i = 0; i < movingsCount; i++) {
        movings[i].x += dx;
    }
}

void move_objects_horizontally(
    TObject* obj,
    TObject& mario,
    TObject* blocks, int& blocksCount,
    TObject* movings, int& movingsCount,
    int& current_level,
    const int maxlvl,
    int& score,
    const float gravity
) {
    obj -> x += obj -> vx;

    for (int i = 0; i < blocksCount; i++) {
        if (is_collide(obj, &blocks[i])) {
            obj -> x -= obj -> vx;
            obj -> vx = -obj -> vx;
            return;
        }
    }

    if (obj ->type == ENEMY) {
        TObject temp = *obj;
        move_objects_vertically(
            &temp,
            mario,
            blocks, blocksCount,
            movings, movingsCount,
            current_level, maxlvl,
            score,
            gravity
        );
        if (temp.IsFLy) {
            obj->x -= obj->vx;
            obj->vx = -obj->vx;
        }
    }
}

void move_objects_vertically(
    TObject* obj,
    TObject &mario,
    TObject *&blocks, int& blocksCount,
    TObject *&movings, int& movingsCount,
    int& current_level,
    const int maxlvl,
    int& score,
    const float gravity
) {
    obj->vy += gravity;
    obj->IsFLy = true;
    set_object_pos(obj, obj->x, obj->y + obj->vy);

    for (int i = 0; i < blocksCount; i++) {
        if (is_collide(obj, &blocks[i])) {
            if (obj->vy > 0) {
                obj->IsFLy = false;
            }
            if (
                blocks[i].type == FULL_BOX && 
                obj->vy < 0 && 
                obj == &mario
            ) {
                blocks[i].type = EMPTY_BOX;

                movingsCount++;
                TObject* temp = new TObject[movingsCount];
                for (int j = 0; j < movingsCount - 1; j++) {
                    temp[j] = movings[j];
                }
                delete[] movings;
                movings = temp;
                init_object(
                    &movings[movingsCount - 1],
                    blocks[i].x, blocks[i].y - 3,
                    3, 2,
                    '$');
                movings[movingsCount - 1].vy = -0.7;
            }

            obj->y -= obj->vy;
            obj->vy = 0;

            if (blocks[i].type == WIN_BRICK) {
                current_level++;
                if (current_level > maxlvl) current_level = 1;

                system("color 2F");
                Sleep(500);
                create_level(
                    current_level,
                    mario,
                    blocks, blocksCount,
                    movings, movingsCount,
                    score);
            }
            break;
        }
    }       
}

void place_object(
    TObject *obj,
    char **map, const int mapWidth, const int mapHeight
) {
    int ix = (int) round(obj->x);
    int iy = (int) round(obj->y);
    int iw = (int) round(obj->w);
    int ih = (int) round(obj->h);

    for (int i = ix; i < ix + iw; i++) {
        for (int j = iy; j < iy + ih; j++) {
            if (is_on_map(i, j, mapWidth, mapHeight)) {
                map[j][i] = obj->type;
            }
        }
    }
}

void player_die(
    TObject& mario,
    TObject *&blocks, int& blocksCount,
    TObject *&movings, int& movingsCount,
    const int current_level,
    int& score
) {
    system("color 4F");
    Sleep(500);
    create_level(
        current_level,
        mario,
        blocks, blocksCount,
        movings, movingsCount,
        score);
}

void print_map(char **map, const int mapHeight, const int mapWidth) {
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

void ShowScore(char **map,
    int score, int level, int mapWidth) {
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







