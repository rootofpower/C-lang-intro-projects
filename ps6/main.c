#include "Space_fighter.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please, select difficulty level. \n");
        return 0;
    }

    int difficult = atoi(argv[1]);
    if (difficult < 1 || difficult > 3) {
        printf("Please, select difficulty level. \n");
        return 0;
    }

    initscr();
    srand(time(NULL));
    curs_set(0);
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK), init_pair(2, COLOR_GREEN, COLOR_BLACK), init_pair(3, COLOR_BLUE, COLOR_BLACK),
    init_pair(4, COLOR_YELLOW, COLOR_BLACK), init_pair(5, COLOR_MAGENTA, COLOR_BLACK), init_pair(6, COLOR_CYAN, COLOR_BLACK),
    init_pair(7, COLOR_WHITE, COLOR_BLACK);

    int max_row, max_col;
    getmaxyx(stdscr, max_row, max_col);
    int countOfEnemyes = rand() % (max_col - 8) + 1;
    bool game_over;

    switch (difficult) {
        case 1:
            game_over = difficulty_lvl1(max_col, max_row, countOfEnemyes);
            break;
        case 2:
            game_over = difficulty_lvl2(max_col, max_row, countOfEnemyes);
            break;
        case 3:
            game_over = difficulty_lvl3(max_col, max_row, countOfEnemyes);
            break;
        default:
            printf("Please, reselect difficulty level. \n");
            return -1;
    }

    if (game_over) {
        sleep(1);
        get_frame(max_row, max_col);
        attron(COLOR_PAIR(2) | A_BOLD);
        mvprintw(max_row / 2, max_col / 2 - 5, "YOU WIN");
        attroff(COLOR_PAIR(2) | A_BOLD);
    }

    refresh();
    curs_set(1);
    nodelay(stdscr, FALSE);
    getch();
    endwin();

    return 0;
}
