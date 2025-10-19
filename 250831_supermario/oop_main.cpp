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

const int MAP_WIDTH = 200;
const int MAP_HEIGHT = 25;

void set_cursor_position(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hide_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void show_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo = {1, 1};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

struct Vector2 {
    float x, y;
    Vector2(float x = 0, float y = 0) : x(x), y(y) {}
};

class GameObject {
protected:
    Vector2 position;
    Vector2 size;
    Vector2 velocity;
    bool is_flying;
    char display_char;
public:
    GameObject(float x, float y, float w, float h, char sym) {
        position = Vector2(x, y);
        size = Vector2(w, h);
        velocity = Vector2(0, 0);
        display_char = sym;
        is_flying = false;
    }
    virtual ~GameObject() = default;

    virtual void update(float dt) {}
    virtual void render(char** screen) const {
        int ix = (int)round(position.x);
        int iy = (int)round(position.y);
        int iw = (int)round(size.x);
        int ih = (int)round(size.y);
        
        for (int i = 0; i < ih && (iy + i) < MAP_HEIGHT; ++i) {
            for (int j = 0; j < iw && (ix + j) < MAP_WIDTH; ++j) {
                if (ix + j >= 0 && iy + i >= 0) {
                    screen[iy + i][ix + j] = display_char;
                }
            }
        }
    }

    virtual void onCollision(const GameObject& other) {}

    Vector2 get_position() const { return position; }
    Vector2 get_size() const { return size; }
    Vector2 get_velocity() const { return velocity; }
    void set_position(Vector2 pos) { position = pos; }
    char get_display_char() const { return display_char; }
    bool get_is_flying() const { return is_flying; }
};

class Player : public GameObject {
public:
    Player(float x, float y) : GameObject(x, y, 3, 3, MARIO) {}
    
    void jump() {
        if (!is_flying) {
            velocity.y = -1.0f;
            is_flying = true;
        }
    }

    void move_left(float speed) {
        position.x -= speed;
    }

    void move_right(float speed) {
        position.x += speed;
    }

    void update(float dt) override {
        velocity.y += 0.05f;
        position.y += velocity.y * dt;

        if (position.y > MAP_HEIGHT - 3) {
            position.y = MAP_HEIGHT - 3;
            velocity.y = 0;
            is_flying = false;
        }
    }
};

class Block : public GameObject {
public:
    Block(float x, float y, float w, float h, char type) : GameObject(x, y, w, h, type) {}
};

class Enemy : public GameObject {
public:
    Enemy(float x, float y) : GameObject(x, y, 3, 2, ENEMY) {
        velocity.x = 0.2f;
    }

    void update(float dt) override {
        position.x += velocity.x * dt;
    }
};

class Coin : public GameObject {
public:
    Coin(float x, float y) : GameObject(x, y, 2, 2, MONEY) {}
    
    void update(float dt) override {
        position.y += velocity.y * dt;
        velocity.y += 0.05f;
    }
};

class Level {
private:
    GameObject** objects;
    int object_capacity;
    int object_count;
    Player* player;
    int level_number;
public:
    Level(int level = 1) : level_number(level), object_capacity(50), object_count(0) {
        objects = new GameObject*[object_capacity];
        for (int i = 0; i < object_capacity; ++i) {
            objects[i] = nullptr;
        }
        load();
    }

    ~Level() {
        for (int i = 0; i < object_count; ++i) {
            delete objects[i];
        }
        delete[] objects;
    }

    void load() {
        // Clear existing objects
        for (int i = 0; i < object_count; ++i) {
            delete objects[i];
            objects[i] = nullptr;
        }
        object_count = 0;

        // Create player
        player = new Player(39, 10);
        add_object(player);

        // Add some blocks
        add_object(new Block(20, 20, 40, 5, BRICK));
        add_object(new Block(30, 10, 5, 3, FULL_BOX));
        add_object(new Block(50, 10, 5, 3, FULL_BOX));
        
        // Add enemies
        add_object(new Enemy(25, 10));
        add_object(new Enemy(80, 10));
    }

    void add_object(GameObject* obj) {
        if (object_count < object_capacity) {
            objects[object_count++] = obj;
        }
    }

    void update(float dt) {
        for (int i = 0; i < object_count; ++i) {
            if (objects[i]) {
                objects[i]->update(dt);
            }
        }
    }

    void render(const int score, const int level) {
        char** screen = new char*[MAP_HEIGHT];
        for (int i = 0; i < MAP_HEIGHT; ++i) {
            screen[i] = new char[MAP_WIDTH + 1];
            for (int j = 0; j < MAP_WIDTH; ++j) {
                screen[i][j] = ' ';
            }
            screen[i][MAP_WIDTH] = '\0';
        }
        
        for (int i = 0; i < object_count; ++i) {
            if (objects[i]) {
                objects[i]->render(screen);
            }
        }

        char c[30];
        char s[10];
        sprintf(c, "Score: %d", score);
        sprintf(s, "Lvl: %d", level);
        int len_c = strlen(c);
        int len_s = strlen(s);
        for (int i = 0; i < len_c; i++) {
            screen[1][i + 5] = c[i];
        }
        for (int i = 0; i < len_s; i++) {
            screen[1][MAP_WIDTH - len_s - 5 + i] = s[i];
        }
        
        set_cursor_position(0, 0);
        for (int i = 0; i < MAP_HEIGHT; ++i) {
            std::cout << screen[i] << std::endl;
        }
        
        // Clean up screen memory
        for (int i = 0; i < MAP_HEIGHT; ++i) {
            delete[] screen[i];
        }
        delete[] screen;
    }
    
    Player* get_player() const { return player; }
};

class Game {
private:
    Level *level;
    int score;
    int current_level;
    bool is_running;
public:
    Game() : is_running(true), score(0), current_level(1) {
        hide_cursor();
        level = new Level();
    }

    ~Game() {
        delete level;
        show_cursor();
    }

    void run() {
        while (is_running) {
            process_input();
            update();
            render();
            Sleep(5);  // Roughly 60 FPS
        }
    }

    void process_input() {
        if (GetKeyState(VK_ESCAPE) < 0) is_running = false;

        auto player = level->get_player();
        if (player) {
            if (GetKeyState(VK_SPACE) < 0) player->jump();

            if ((GetKeyState(VK_LEFT) < 0) || (GetKeyState('A') < 0)) {
                player->move_left(1.0f);
            }
            if ((GetKeyState(VK_RIGHT) < 0) || (GetKeyState('D') < 0)) {
                player->move_right(1.0f);
            }
        }
    }

    void update() {
        level->update(1.0f);
    }

    void render() {
        level->render(score, current_level);
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}