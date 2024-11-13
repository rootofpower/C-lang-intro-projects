#include "Space_fighter.h"

void get_frame(int row, int col) {
    move(0, 1);
    hline(ACS_HLINE, col - 2);
    move(1, 0);
    vline(ACS_VLINE, row - 2);
    move(row - 1, 1);
    hline(ACS_HLINE, col - 2);
    move(1, col - 1);
    vline(ACS_VLINE, row - 2);
}

void move_ship(int *x, int *y, int max_row, int max_col, int ch) {
    switch (ch) {
        case KEY_UP:
            if (*y > 1)
                *y -= 1;
            break;
        case KEY_DOWN:
            if (*y < max_row - 4)
                *y += 1;
            break;
        case KEY_LEFT:
            if (*x > 1)
                *x -= 1;
            break;
        case KEY_RIGHT:
            if (*x < max_col - 6)
                *x += 1;
            break;
    }
}

void write_ship(int x, int y) {
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(y, x, "  ^  ");
    attroff(COLOR_PAIR(2) | A_BOLD);
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(y + 1, x, " /+\\ ");
    attroff(COLOR_PAIR(3) | A_BOLD);
    attron(COLOR_PAIR(4) | A_BOLD);
    mvprintw(y + 2, x, "<+-+>");
    attroff(COLOR_PAIR(4) | A_BOLD);
}

void shoot(int x, int y, Enemy enemies[], int countOfEnemyes, Score *score) {
    if (y != 0) {
        attron(COLOR_PAIR(1) | A_BOLD);
        mvaddch(y, x, '|');
        attroff(COLOR_PAIR(1) | A_BOLD);
        y--;
        shoot(x, y, enemies, countOfEnemyes, score);
    }
    for (int i = 0; i < countOfEnemyes; i++) {
        if (enemies[i].alive &&
                   enemies[i].lvl == 1 &&
                   enemies[i].y == y &&
                   enemies[i].x == x) {
            enemies[i].alive = false;
            score->result += 10;
                   }
        else if (enemies[i].alive &&
            enemies[i].lvl == 2 &&
            enemies[i].y == y &&
            (enemies[i].x <= x && x <= enemies[i].x + 2)) {
            if (enemies[i].hp > 0) {
                enemies[i].hp--;  
                if (enemies[i].hp == 0) {
                    enemies[i].alive = false;
                    score->result += 20;
                }
            }
        } else if (enemies[i].alive &&
            enemies[i].lvl == 3 &&
            enemies[i].y == y &&
            (enemies[i].x <= x && x <= enemies[i].x + 2)) {
            if (enemies[i].hp > 0) {
                enemies[i].hp--;  
                if (enemies[i].hp == 0) {
                    enemies[i].alive = false;
                    score->result += 30;
                }
            }
        }
    }
}

void draw_enemies(Enemy enemies[], int countOfEnemyes, int max_col, int max_row) {
    for (int i = 0; i < countOfEnemyes; i++) {
        if (enemies[i].alive && enemies[i].lvl == 1) {
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(enemies[i].y, enemies[i].x, "#");
            attroff(COLOR_PAIR(3) | A_BOLD);
        } else if (enemies[i].alive && enemies[i].lvl == 2) {
            mvprintw(enemies[i].y, enemies[i].x - enemies[i].direction, "   ");
            attron(COLOR_PAIR(4) | A_BOLD);
            mvprintw(enemies[i].y, enemies[i].x, "@-@");
            attroff(COLOR_PAIR(4) | A_BOLD);
        } else if (enemies[i].alive && enemies[i].lvl == 3) {
            mvprintw(enemies[i].y, enemies[i].x - enemies[i].direction, "   ");
            attron(COLOR_PAIR(6) | A_BOLD);
            mvprintw(enemies[i].y, enemies[i].x, "&|&");
            attroff(COLOR_PAIR(6) | A_BOLD);
        }
    }
}

void draw_stars(Star stars[]) {
    for (int i = 0; i < MAX_STARS; i++) {
        mvaddch(stars[i].y, stars[i].x, '*');
    }
}

void update_stars(Star stars[], int max_row, int max_col) {
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].y += 1;
        if (stars[i].y >= max_row) {
            stars[i].y = 1;
            stars[i].x = rand() % (max_col - 2) + 1;
        }
    }
}

int count_alive_enemies(Enemy enemies[], int countOfEnemyes) {
    int count = 0;
    for (int i = 0; i < countOfEnemyes; i++) {
        if (enemies[i].alive) {
            count++;
        }
    }
    return count;
}

void update_enemies_position(Enemy enemies[], int countOfEnemyes, int max_col) {
    for (int i = 0; i < countOfEnemyes; i++) {
        if ((enemies[i].lvl == 2 || enemies[i].lvl == 3) && enemies[i].alive) {
            if (enemies[i].direction == 1) {
                if (enemies[i].x < max_col - 4) {
                    enemies[i].x += 1;
                } else {
                    enemies[i].direction = -1;
                }
            } else {
                if (enemies[i].x > 1) {
                    enemies[i].x -= 1;
                } else {
                    enemies[i].direction = 1;
                }
            }
        }
    }
}

bool difficulty_lvl1(int max_col, int max_row, int countOfEnemyes) {
    time_t start_time = time(NULL);
    int x = max_col / 2, y = max_row / 2;
    int ch;
    Enemy enemies[countOfEnemyes];
    Score score;
    score.result = 0;
    get_frame(max_row, max_col);
    for (int i = 0; i < countOfEnemyes; i++) {
        enemies[i].x = rand() % (max_col - 8) + 4;
        enemies[i].y = 1;
        enemies[i].alive = true;
        enemies[i].hp = 1;
        enemies[i].lvl = 1;
    }
    Star stars[MAX_STARS];
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].x = rand() % (max_col - 2) + 1;
        stars[i].y = rand() % (max_row - 2) + 1;
    }
    bool game_over = false;
    while ((ch = getch()) != 27 && !game_over) {
        time_t current_time = time(NULL);
        double elapsed_time = difftime(current_time, start_time);
        clear();
        get_frame(max_row, max_col);
        update_stars(stars, max_row, max_col);
        draw_stars(stars);
        draw_enemies(enemies, countOfEnemyes, max_col, max_row);
        move_ship(&x, &y, max_row, max_col, ch);
        attron(COLOR_PAIR(2) | A_BOLD);
        if (elapsed_time >= 300) {
        game_over = true;
        }
        mvprintw(max_row - 2, 1, "Score: %d", score.result);
        mvprintw(max_row - 2, 15, "Enemyes: %d", count_alive_enemies(enemies, countOfEnemyes));
        mvprintw(max_row - 2, 35, "Time: %d", (int) elapsed_time);
        mvprintw(max_row - 2, max_col - 30, "Max score: %d", score.max_result);
        mvprintw(max_row - 2, max_col - 15, "Difficulty: %d", 1);

        attroff(COLOR_PAIR(2) | A_BOLD);
        if (ch == ' ') {
            shoot(x + 2, y - 1, enemies, countOfEnemyes, &score);
        }
        if (count_alive_enemies(enemies, countOfEnemyes) == 0) {
            game_over = true;
        }
        if (check_collision(x, y, enemies, countOfEnemyes)) {
            ch = 27;
        }
        update_game(x, y, enemies, countOfEnemyes, &game_over);
        write_ship(x, y);
        sleep(1);
        refresh();
    }
    clear();
    get_frame(max_row, max_col);
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(max_row / 2, max_col / 2 - 5, "GAME OVER");
    attroff(COLOR_PAIR(1) | A_BOLD);
    refresh();
    sleep(1);
    return game_over;
}

bool difficulty_lvl2(int max_col, int max_row, int countOfEnemyes) {
    time_t start_time = time(NULL);
    int x = max_col / 2, y = max_row / 2;
    int ch;
    Score score;
    score.result = 0;
    Enemy enemies[countOfEnemyes];
    get_frame(max_row, max_col);
    for (int i = 0; i < countOfEnemyes; i++) {
        enemies[i].x = rand() % (max_col - 8) + 4;
        enemies[i].y = rand() % 2 + 1;
        enemies[i].alive = true;
        enemies[i].hp = 2;
        enemies[i].lvl = 2;
        enemies[i].direction = 1;
    }
    Star stars[MAX_STARS];
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].x = rand() % (max_col - 2) + 1;
        stars[i].y = rand() % (max_row - 2) + 1;
    }
    bool game_over = false;
    while ((ch = getch()) != 27 && !game_over) {
        time_t current_time = time(NULL);
        double elapsed_time = difftime(current_time, start_time);
        clear();
        get_frame(max_row, max_col);
        update_stars(stars, max_row, max_col);
        draw_stars(stars);
        move_ship(&x, &y, max_row, max_col, ch);
        attron(COLOR_PAIR(2) | A_BOLD);
        if (elapsed_time >= 300) {
        game_over = true;
        }
        mvprintw(max_row - 2, 1, "Score: %d", score.result);
        mvprintw(max_row - 2, 15, "Enemyes: %d", count_alive_enemies(enemies, countOfEnemyes));
        mvprintw(max_row - 2, 35, "Time: %d", (int) elapsed_time);
        mvprintw(max_row - 2, max_col - 30, "Max score: %d", score.max_result);
        mvprintw(max_row - 2, max_col - 15, "Difficulty: %d", 2);
        attroff(COLOR_PAIR(2) | A_BOLD);
        if (ch == ' ') {
            shoot(x + 2, y - 1, enemies, countOfEnemyes, &score);
        }
        update_enemies_position(enemies, countOfEnemyes, max_col);
        draw_enemies(enemies, countOfEnemyes, max_col, max_row);
        if (count_alive_enemies(enemies, countOfEnemyes) == 0) {
            game_over = true;
        }
        if (check_collision(x, y, enemies, countOfEnemyes)) {
            ch = 27;
        }
        update_game(x, y, enemies, countOfEnemyes, &game_over);
        write_ship(x, y);
        sleep(1);
        refresh();
    }
    clear();
    return game_over;
}

bool difficulty_lvl3(int max_col, int max_row, int countOfEnemyes) {
    time_t start_time = time(NULL);
    int x = max_col / 2, y = max_row / 2;
    int ch;
    Enemy enemies[countOfEnemyes];
    Score score;
    score.result = 0;
    init_enemy_shooting(enemies, countOfEnemyes);

    get_frame(max_row, max_col);

    for (int i = 0; i < countOfEnemyes; i++) {
        enemies[i].x = rand() % (max_col - 8) + 4;
        enemies[i].y = rand() % 3 + 1;
        enemies[i].alive = true;
        enemies[i].hp = 1;
        enemies[i].lvl = 3;
        enemies[i].direction = (rand() % 2 == 0) ? 1 : -1;
    }

    Star stars[MAX_STARS];
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].x = rand() % (max_col - 2) + 1;
        stars[i].y = rand() % (max_row - 2) + 1;
    }

    bool game_over = false;

    while ((ch = getch()) != 27 && !game_over) {
        time_t current_time = time(NULL);
        double elapsed_time = difftime(current_time, start_time);
        clear();
        get_frame(max_row, max_col);
        update_stars(stars, max_row, max_col);
        draw_stars(stars);
        update_enemy_shooting(enemies, countOfEnemyes, max_row);
        update_enemies_position(enemies, countOfEnemyes, max_col);
        draw_enemies(enemies, countOfEnemyes, max_col, max_row);
        move_ship(&x, &y, max_row, max_col, ch);
        if (elapsed_time >= 300) {
        game_over = true;
        }
        attron(COLOR_PAIR(2) | A_BOLD);
        mvprintw(max_row - 2, 1, "Score: %d", score.result);
        mvprintw(max_row - 2, 15, "Enemyes: %d", count_alive_enemies(enemies, countOfEnemyes));
        mvprintw(max_row - 2, 35, "Time: %d", (int) elapsed_time);
        mvprintw(max_row - 2, max_col - 30, "Max score: %d", score.max_result);
        mvprintw(max_row - 2, max_col - 15, "Difficulty: %d", 3);
        attroff(COLOR_PAIR(2) | A_BOLD);
        if (ch == ' ') {
            shoot(x + 2, y - 1, enemies, countOfEnemyes, &score);
        }

        if (count_alive_enemies(enemies, countOfEnemyes) == 0) {
            game_over = true;
        }
        if (check_collision(x, y, enemies, countOfEnemyes)) {
            ch = 27;
        }
        update_game(x, y, enemies, countOfEnemyes, &game_over);
        write_ship(x, y);
        sleep(1);
        refresh();
    }

    clear();
    return game_over;
}



void init_enemy_shooting(Enemy enemies[], int countOfEnemyes) {
    for (int i = 0; i < countOfEnemyes; i++) {
        enemies[i].canShoot = true;
        enemies[i].bullet.active = false;
        enemies[i].shootDelay = rand() % ENEMY_SHOOT_COOLDOWN;
    }
}

void update_enemy_shooting(Enemy enemies[], int countOfEnemies, int max_row) {
    for (int i = 0; i < countOfEnemies; i++) {
        if (enemies[i].alive && enemies[i].lvl == 3) {
            if (enemies[i].shootDelay > 0) {
                enemies[i].shootDelay--;
        } else if (enemies[i].canShoot){
                enemies[i].bullet.active = true;
                enemies[i].bullet.x = enemies[i].x;
                enemies[i].bullet.y = enemies[i].y - 1;
                enemies[i].canShoot = false;
            }
        }

        if (enemies[i].bullet.active) {
            draw_enemy_bullet(enemies[i].bullet);
            move_enemy_bullet(&enemies[i].bullet, max_row);
        }

        if (!enemies[i].canShoot) {
            enemies[i].shootCooldown++;
            if (enemies[i].shootCooldown >= ENEMY_SHOOT_COOLDOWN) {
                enemies[i].canShoot = true;
                enemies[i].shootCooldown = 0;
            }
        }
    }
}

void draw_enemy_bullet(Bullet bullet) {
    attron(COLOR_PAIR(3) | A_BOLD);
    mvaddch(bullet.y, bullet.x, '.');
    attroff(COLOR_PAIR(3) | A_BOLD);
}

void move_enemy_bullet(Bullet *bullet, int max_row) {
    if (bullet->active) {
        mvaddch(bullet->y, bullet->x, ' '); // Clear previous position
        bullet->y++;
        if (bullet->y >= max_row - 1) {
            bullet->active = false;
        } else {
            attron(COLOR_PAIR(3) | A_BOLD);
            mvaddch(bullet->y, bullet->x, '.'); // Draw the bullet at the new position
            attroff(COLOR_PAIR(3) | A_BOLD);
        }
    }
}

bool check_collision(int player_x, int player_y, Enemy enemies[], int countOfEnemies) {
    for (int i = 0; i < countOfEnemies; i++) {
        if (enemies[i].alive) {
            if (player_x == enemies[i].x && player_y == enemies[i].y) {
                return true; // Collision with enemy
            }
            if (enemies[i].bullet.active && player_x == enemies[i].bullet.x && player_y == enemies[i].bullet.y) {
                return true; // Collision with bullet
            }
        }
    }
    return false;
}

void update_game(int player_x, int player_y, Enemy enemies[], int countOfEnemies, bool* game_over) {
    for (int i = 0; i < countOfEnemies; i++) {
        if (enemies[i].alive && enemies[i].x == player_x && enemies[i].y == player_y) {
            *game_over = true;
            return;
        }
    }
}