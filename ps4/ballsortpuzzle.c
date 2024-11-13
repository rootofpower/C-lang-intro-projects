#include <stdio.h>
#include <stdlib.h> 
#include "ballsortpuzzle.h"
#include <time.h>
#include <string.h>
#include <ncurses.h>



char* get_rand_column(char balls[], const int columns);
int get_color_number(char ball);

void generator(const int rows, const int columns, char field[rows][columns]){
    
    srand(time(NULL));
    int counter[columns - 2];
    memset(counter, 0, (columns - 2)*sizeof(int));
    char balls[] = {'&', '>', '#', '%', '=', '+', '@'};
    for (int i = 0; i < columns; i++) 
    for(int i = 0; i < rows; i++){
        get_rand_column(field[i], columns);
    }
    for(int j = 0; j < rows; j++){
        for(int i = 0; i < columns; i++){
            if(field[j][i] == '1'){
                field[j][i] = ' ';
            }
            else if(field[j][i] == '0'){
                int index = rand() % (columns - 2);
                for(int k = 0; k < 500; k++){
                    if (counter[index] < rows) {
                        field[j][i] = balls[index];
                        counter[index]++;
                        break;
                    } else {
                        index = rand() % (columns - 2);
                        continue;
                    }
                }
                
            }
        }
    }

    
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y){
    if(x < 1 || x > columns || y < 1 || y > columns){
        attron(COLOR_PAIR(1) | A_BOLD);
        printw("Invalid column. Try again!\n");
        attroff(COLOR_PAIR(1) | A_BOLD);
        return;
    }
    if (x == y){
        attron(COLOR_PAIR(1) | A_BOLD);
        printw("Columns are same! Try again!\n");
        attroff(COLOR_PAIR(1) | A_BOLD);
        return;
    }
    char ball = 0;
    int i = 0, check = 0;
    for(i = 0; i < rows; i++){
        if(field[i][x - 1] != ' '){
            ball = field[i][x - 1];
            field[i][x - 1] = ' ';
            check = i;
            break;
        }

    }
    if(ball == 0){
        attron(COLOR_PAIR(1) | A_BOLD);
        printw("There is no ball in column %d. Please, try again!\n", x);
        attroff(COLOR_PAIR(1) | A_BOLD);
        return ;
    }
    else{
        if(field[0][y - 1] != ' '){
                attron(COLOR_PAIR(1) | A_BOLD);
                printw("Column %d is full.\n", y);
                attroff(COLOR_PAIR(1) | A_BOLD);
                field[check][x - 1] = ball;
                return;
            }

        for(i = rows - 1; i >= 0; i--){
            if(field[i][ y - 1] == ' ' && i != rows - 1){
                if(field[i + 1][y - 1] == ball){
                    field[i][y - 1] = ball;
                    break;
                }
                else{
                    attron(COLOR_PAIR(1) | A_BOLD);
                    printw("Symbols are not the same!\n");
                    attroff(COLOR_PAIR(1) | A_BOLD);
                    field[check][x - 1] = ball;
                    break;
                }
            }
            else if(field[i][y-1] == ' '){
                field[i][y - 1] = ball;
                break;
            }
        }   
    }
}


bool check(const int rows, const int columns, char field[rows][columns]){
    for(int i = 0; i < columns; i++){
        char temp = field[0][i];
        for(int j = 0; j < rows; j++){
            if(field[j][i] != temp){
                return false;
            }
        }
    }
    return true;
}

void game_field(const int rows, const int columns, char field[rows][columns]){
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK), init_pair(2, COLOR_BLUE, COLOR_BLACK),
    init_pair(3, COLOR_YELLOW, COLOR_BLACK), init_pair(4, COLOR_GREEN, COLOR_BLACK),
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK), init_pair(6, COLOR_WHITE, COLOR_BLACK),
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
    int i;
    move(0, ((columns * 4) - 8) / 2);
    attron(A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
    printw("BALL SORT PUZZLE");
    attroff(A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
    for(i = 0; i < rows; i++){
        move(i+2, 0);
        attron(A_BOLD);
        printw(" %d ", i + 1);
        attroff(A_BOLD);
        for(int j = 0; j < columns; j++){
            attron(A_BOLD);
            printw("|");
            attroff(A_BOLD);
            attron(COLOR_PAIR(get_color_number(field[i][j])) | A_BOLD);
            printw(" %c ", field[i][j]);
            attroff(COLOR_PAIR(get_color_number(field[i][j])) | A_BOLD);
        }
    }
    for(int j = 0; j < rows; j++){
        move(j + 2, columns * 4 + 3);
        attron(A_BOLD);
        printw("|");
        attroff(A_BOLD);
    }
    move(rows + 2, 4);
    for(int j = 0; j < columns; j++){
        attron(A_BOLD);
        printw("--- ");
        attroff(A_BOLD);   
    }
    move(rows + 3, 4);
    for(int j = 0; j < columns; j++){
        attron(A_BOLD);
        printw(" %d  ", j + 1);
        attroff(A_BOLD);
    }
    refresh();
}


void ball_sort_puzzle(){
    keypad(stdscr, TRUE);
    int rows = 4;
    int columns = 6;
    char field[rows][columns];
    initscr();
    generator(rows, columns, field);
    game_field(rows, columns, field);
    int x, y;
    
    while(!check(rows, columns, field)){
        move(rows + 4, 0);
        clrtoeol();
        attron(COLOR_PAIR(5) | A_BOLD);
        printw("Enter column number from (For exit press Q/q): ");
        attroff(COLOR_PAIR(5) | A_BOLD);
        x = getch() - 48;
        if(x == 65 || x == 33){
            break;
        }
        if(x > columns || x < 1){
            move(rows + 5, 0);
            clrtoeol();
            attron(COLOR_PAIR(1) | A_BOLD);
            printw("Invalid value. Try again!\n");
            attroff(COLOR_PAIR(1) | A_BOLD);
            continue;
        }
        
        move(rows + 6, 0);
        clrtoeol();
        move(rows + 5, 0);
        clrtoeol();
        attron(COLOR_PAIR(5) | A_BOLD);
        printw("Enter column number where: ");
        attroff(COLOR_PAIR(5) | A_BOLD);
        y = getch() - 48;
        if(y == 65 || y == 33){
            break;
        }
        if(y > columns || y < 1){
            move(rows + 5, 0);
            clrtoeol();
            attron(COLOR_PAIR(1) | A_BOLD);
            printw("Invalid value. Try again!\n");
            attroff(COLOR_PAIR(1) | A_BOLD);
            continue;
        }
        move(rows + 6, 0);
        down_possible(rows, columns, field, x, y);
        game_field(rows, columns, field);
    }
    move(rows + 6, 0);
    if(check(rows, columns, field)){
        attron(COLOR_PAIR(4) | A_BOLD);
        printw("Good job, you win!\n");
        attroff(COLOR_PAIR(4) | A_BOLD);
    }
    else{
        attron(COLOR_PAIR(1) | A_BOLD);
        printw("Good bye! Thanks for the game!\n");
        attroff(COLOR_PAIR(1) | A_BOLD);
    }
    getch();
    endwin();
}



//function, that will return columns, that will be filled with "balls"
char* get_rand_column(char balls[] ,const int columns){
    char balls_array[columns];
    memset(balls_array, '0', columns*sizeof(char));

    srand(time(NULL));
    // creatind 2 indexes, where will be empty columns
    int index1 = rand() % columns, index2 = rand() % columns;
    //checking whether the indexes are different
    while(index1 == index2) index1 = rand() % columns; 

    balls_array[index1] = '1', balls_array[index2] = '1';

    for(int i = 0; i < columns; i++){
        balls[i] = balls_array[i];
    }

    return balls;
}

int get_color_number( char ball){
    char balls[] = {'&', '>', '#', '%', '=', '+', '@'};
    short size = strlen(balls);
    for(int i = 0; i < size; i++){
        if(ball == balls[i]) return i + 1;
    }
    return -1;
}
