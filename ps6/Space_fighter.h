#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_STARS 100
#define ENEMY_SHOOT_COOLDOWN 100
typedef struct {
    int result;
    int max_result;
} Score;

typedef struct {
    int x, y;
    bool active;
} Bullet;

typedef struct {
    int x, y, hp, lvl, damage, direction, shootCooldown, shootDelay;
    bool alive, canShoot;
    Bullet bullet;
} Enemy;

typedef struct {
    int x;
    int y;
} Star;



void get_frame(int row, int col);
void move_ship(int *x, int *y, int max_row, int max_col, int ch);
void write_ship(int x, int y);
void shoot(int x, int y, Enemy enemies[], int countOfEnemyes, Score score[]);
void draw_enemies(Enemy enemies[], int countOfEnemyes, int max_col, int max_row);
void draw_stars(Star stars[]);
void update_stars(Star stars[], int max_row, int max_col);
int count_alive_enemies(Enemy enemies[], int countOfEnemyes);
void update_enemies_position(Enemy enemies[], int countOfEnemyes, int max_col);
bool difficulty_lvl1(int max_col, int max_row, int countOfEnemyes);
bool difficulty_lvl2(int max_col, int max_row, int countOfEnemyes);
bool difficulty_lvl3(int max_col, int max_row, int countOfEnemyes);
void init_enemy_shooting(Enemy enemies[], int countOfEnemyes);
void update_enemy_shooting(Enemy enemies[], int countOfEnemyes, int max_row);
void draw_enemy_bullet(Bullet bullet);
void move_enemy_bullet(Bullet *bullet, int max_row);
bool check_collision(int player_x, int player_y, Enemy enemies[], int countOfEnemies);
void update_game(int player_x, int player_y, Enemy enemies[], int countOfEnemies, bool* game_over);
