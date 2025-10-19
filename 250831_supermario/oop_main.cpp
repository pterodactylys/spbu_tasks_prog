#include <cmath>
#include <iostream>
#include <windows.h>

const char BRICK = '#';
const char EMPTY_BOX = '-';
const char ENEMY = 'o';
const char FULL_BOX = '?';
const char PLAYER = '@';
const char MONEY = '$';
const char WIN_BRICK = '+';


namespace console_tool {
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
    bool is_active;
    char display_char;
public:
    GameObject(float x, float y, float w, float h, char sym) {
        position = Vector2(x, y);
        size = Vector2(w, h);
        velocity = Vector2(0, 0);
        display_char = sym;
        is_flying = false;
        is_active = true;
    }
    virtual ~GameObject() = default;

    virtual void update(float dt, const int map_height) {}
    virtual void render(char** screen, const int map_width, const int map_height) const;

    virtual void onCollision(const GameObject& other) {}
    Vector2 get_position() const { return position; }
    Vector2 get_size() const { return size; }
    Vector2 get_velocity() const { return velocity; }
    void set_display_char(char sym) { display_char = sym; }
    void set_flying(bool flying) { is_flying = flying; }
    void set_position(Vector2 pos) { position = pos; }
    void set_velocity(Vector2 vel) { velocity = vel; }
    void set_is_active(bool active) { is_active = active; }
    char get_display_char() const { return display_char; }
    bool get_is_flying() const { return is_flying; }
    bool get_is_active() const { return is_active; }
};

bool is_collide(const GameObject* a, const GameObject* b);

class Level;
class Player : public GameObject {
private:
    Level* level;
    int* score;
public:
    Player(float x, float y, Level* lvl, int* scr) 
    : GameObject(x, y, 3, 3, PLAYER), level(lvl), score(scr) {}

    void jump();

    void move_left(float speed);

    void move_right(float speed);

    void update(float dt, const int map_height) override;
    void die();
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

    void update(float dt, const int map_height) override;
};

class Coin : public GameObject {
public:
    Coin(float x, float y) : GameObject(x, y, 2, 2, MONEY) {}
    
    void update(float dt, const int map_height) override;
};

class Level {
private:
    GameObject** objects;
    int object_capacity;
    int object_count;
    Player* player;
    int level_number;
    int* score;
    const int max_level = 3;
public:
    Level(int level, int* scr) : level_number(level), score(scr), object_capacity(50), object_count(0) {
        objects = new GameObject*[object_capacity];
        for (int i = 0; i < object_capacity; ++i) {
            objects[i] = nullptr;
        }
        load();
    }

    ~Level();

    void add_object(GameObject* object);

    void check_mario_collisions(const int enemy_reward, const int money_reward);

    void resolve_mario_collisions(Player& mario, GameObject* other, const int enemy_reward, const int money_reward);

    void spawn_coin(float x, float y);

    void load();

    void reload();

    void update(float dt, const int map_height);

    void render(const int score, const int level, const int map_width, const int map_height);
    
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
        console_tool::hide_cursor();
        level = new Level(current_level, &score);
    }

    ~Game();

    void run(const int map_width, const int map_height);

    void process_input();

    void update(const int map_height);

    void render(const int map_width, const int map_height);
};

int main() {
    const int map_width = 200;
    const int map_height = 25;

    const int enemy_reward = 100;
    const int money_reward = 50;

    Game game;
    game.run(map_width, map_height);
    return 0;
}

void GameObject::render(char** screen, const int map_width, const int map_height) const {
    int ix = (int)round(position.x);
    int iy = (int)round(position.y);
    int iw = (int)round(size.x);
    int ih = (int)round(size.y);

    for (int i = 0; i < ih && (iy + i) < map_height; ++i) {
        for (int j = 0; j < iw && (ix + j) < map_width; ++j) {
            if (ix + j >= 0 && iy + i >= 0) {
                screen[iy + i][ix + j] = display_char;
            }
        }
    }
}

bool is_collide(const GameObject* a, const GameObject* b) {
    Vector2 a_pos = a->get_position();
    Vector2 a_size = a->get_size();
    Vector2 b_pos = b->get_position();
    Vector2 b_size = b->get_size();

    return (a_pos.x < b_pos.x + b_size.x &&
            a_pos.x + a_size.x > b_pos.x &&
            a_pos.y < b_pos.y + b_size.y &&
            a_pos.y + a_size.y > b_pos.y);
}

void Player::jump() {
    if (!is_flying) {
        velocity.y = -1.0f;
        is_flying = true;
    }
}

void Player::move_left(float speed) {
    position.x -= speed;
}

void Player::move_right(float speed) {
    position.x += speed;
}

void Player::update(float dt, const int map_height) {
    velocity.y += 0.05f;
    position.y += velocity.y * dt;

    if (position.y > map_height - 3) {
        position.y = map_height - 3;
        velocity.y = 0;
        is_flying = false;
    }
}

void Player::die() {
    system("color 4F");
    Sleep(1000);
    if (level) level->reload();
    *score = 0;
}

void Enemy::update(float dt, const int map_height) {
    position.x += velocity.x * dt;
}

void Coin::update(float dt, const int map_height) {
    position.y += velocity.y * dt;
    velocity.y += 0.05f;
}

Level::~Level() {
    for (int i = 0; i < object_count; ++i) {
        delete objects[i];
    }
    delete[] objects;
    }

void Level::add_object(GameObject* object) {
    if (object_count < object_capacity) {
        objects[object_count++] = object;
    }
}

void Level::check_mario_collisions(const int enemy_reward, const int money_reward) {
    player = get_player();
    for (int i = 0; i < object_count; ++i) {
        if (is_collide(objects[i], player)) {
            resolve_mario_collisions(*player, objects[i], enemy_reward, money_reward);
        }
    }
}

void Level::resolve_mario_collisions(Player& mario, GameObject* other, const int enemy_reward, const int money_reward) {
    char other_type = other->get_display_char();

    if (other_type == BRICK || other_type == FULL_BOX || other_type == EMPTY_BOX) {
        Vector2 mpos = mario.get_position();
        Vector2 msize = mario.get_size();
        Vector2 opos = other->get_position();
        Vector2 osize = other->get_size();

        float mario_bottom = mpos.y + msize.y;
        float mario_top = mpos.y;
        float block_top = opos.y;
        float block_bottom = opos.y + osize.y;

        if (mario.get_velocity().y > 0 && mario_bottom > block_top && mario_top < block_top) {
            mario.set_position({ mpos.x, block_top - msize.y });
            mario.set_velocity({ mario.get_velocity().x, 0 });
            mario.set_flying(false);
        }
        else if (mario.get_velocity().y < 0 && mario_top < block_bottom && mario_bottom > block_bottom) {
            mario.set_velocity({ mario.get_velocity().x, 0 });
            if (other_type == FULL_BOX) {
                other->set_display_char(EMPTY_BOX);
                spawn_coin(opos.x, opos.y - 3);
                (*score) += 50;
            }
        }
        return;
    }

    if (other_type == ENEMY) {
        if (mario.get_is_flying() &&
            (mario.get_position().y + mario.get_size().y) <
            (other->get_position().y + other->get_size().y / 2)) {
            (*score) += enemy_reward;
            mario.set_velocity({ mario.get_velocity().x, -0.7f });
            other->set_is_active(false);
        } else {
            mario.die();
        }
        return;
    }

    if (other_type == MONEY) {
        (*score) += money_reward;
        other->set_is_active(false);
        return;
    }

    if (other_type == WIN_BRICK) {
        (*score) += 100;
        level_number++;
        if (level_number > max_level) level_number = 1;
        system("color 2F");
        Sleep(1000);
        load();
        return;
    }
}

void Level::spawn_coin(float x, float y) {
    Coin* coin = new Coin(x, y);
    add_object(coin);
}

void Level::load() {
    for (int i = 0; i < object_count; ++i) {
        delete objects[i];
        objects[i] = nullptr;
    }
    object_count = 0;

    player = new Player(39, 10, this, score);
    add_object(player);

    add_object(new Block(20, 20, 40, 5, BRICK));
    add_object(new Block(60, 15, 40, 10, BRICK));
    add_object(new Block(80, 8, 5, 3, FULL_BOX));
    add_object(new Block(110, 10, 10, 15, WIN_BRICK));

    add_object(new Enemy(25, 10));
    add_object(new Enemy(90, 10));
}

void Level::reload() {
    load();
}

void Level::update(float dt, const int map_height) {
    for (int i = 0; i < object_count; ++i) {
        if (objects[i]) {
            objects[i]->update(dt, map_height);
        }
    }
    check_mario_collisions(100, 50);

    for (int i = 0; i < object_count; ++i) {
        if (objects[i] && !objects[i]->get_is_active()) {
            delete objects[i];
            for (int j = i; j < object_count - 1; ++j)
                objects[j] = objects[j + 1];
            --object_count;
            --i;
        }
    }
}

void Level::render(const int score, const int level, const int map_width, const int map_height) {
    char** screen = new char*[map_height];
    for (int i = 0; i < map_height; ++i) {
        screen[i] = new char[map_width + 1];
        for (int j = 0; j < map_width; ++j) {
            screen[i][j] = ' ';
        }
        screen[i][map_width] = '\0';
    }
    
    for (int i = 0; i < object_count; ++i) {
        if (objects[i]) {
            objects[i]->render(screen, map_width, map_height);
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
        screen[1][map_width - len_s - 5 + i] = s[i];
    }
    
    console_tool::set_cursor_position(0, 0);
    for (int i = 0; i < map_height; ++i) {
        std::cout << screen[i] << std::endl;
    }

    for (int i = 0; i < map_height; ++i) {
        delete[] screen[i];
    }
    delete[] screen;
}

Game::~Game() {
    delete level;
    console_tool::show_cursor();
}


void Game::run(const int map_width, const int map_height) {
    while (is_running) {
        process_input();
        update(map_height);
        render(map_width, map_height);
        Sleep(5);
    }
}

void Game::process_input() {
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

void Game::update(const int map_height) {
    level->update(1.0f, map_height);
}

void Game::render(const int map_width, const int map_height) {
    level->render(score, current_level, map_width, map_height);
}