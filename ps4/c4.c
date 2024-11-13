#include <stdio.h>
#include "c4.h"
#include <ncurses.h>
/*
void game();

int main(int argc, char* argv[]){
    initscr();
    game();
    return 0;
}
*/
void initialize_board(int rows, int cols, char board[rows][cols]){
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            board[i][j] = '.';
        }
    }
}
void print_board(int rows, int cols, const char board[rows][cols]){
    for (int i = 0; i < rows; i++){
        move(i + 3, 1);
        for(int j = 0; j < cols; j++){
            attron(COLOR_PAIR(6) | A_BOLD);
            printw("|");
            attroff(COLOR_PAIR(6) | A_BOLD);
            if(board[i][j] == 'X'){
                attron(COLOR_PAIR(2) | A_BOLD);
                printw(" %c ", board[i][j]);
                attroff(COLOR_PAIR(2) | A_BOLD);
            }
            else if(board[i][j] == 'O'){
                attron(COLOR_PAIR(3) | A_BOLD);
                printw(" %c ", board[i][j]);
                attroff(COLOR_PAIR(3) | A_BOLD);
            }
            else if(board[i][j] == '.'){
                attron(COLOR_PAIR(7) | A_BOLD);
                printw(" %c ", board[i][j]);
                attroff(COLOR_PAIR(7) | A_BOLD);
            }
            
        }
        attron(COLOR_PAIR(6) | A_BOLD);
        printw("|");
        attroff(COLOR_PAIR(6) | A_BOLD);
        
    }
}
int is_valid_move(int rows, int cols, const char board[rows][cols], int col){
    if (col > cols || col < 1) return 0;
    for(int i = 0; i < cols; i++){
        if(board[0][col - 1] != '.') return 0;
    }
    return 1;
    
}
int drop_piece(int rows, int cols, char board[rows][cols], int col, char player_piece){
    if(is_valid_move(rows, cols, board, col)){
        int i = 0;
        while(board[i][col - 1] == '.' && i < rows - 1){
            i++;
        }
        if(board[i][col - 1] != '.') i--;
        board[i][col - 1] = player_piece;
        return i;
    }
    return 0;
}

int check_win(int rows, int cols, const char board[rows][cols], int row, int col, char player_piece) {
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    for (int i = 0; i < 4; i++) {
        int count = 1;
        for (int j = 1; j < 4; j++) {
            int x = row + j * directions[i][0];
            int y = col + j * directions[i][1];
            if (x >= 0 && x < rows && y >= 0 && y < cols && board[x][y] == player_piece) {
                count++;
            } else {
                break;
            }
        }
        for (int j = 1; j < 4; j++) {
            int x = row - j * directions[i][0];
            int y = col - j * directions[i][1];
            if (x >= 0 && x < rows && y >= 0 && y < cols && board[x][y] == player_piece) {
                count++;
            } else {
                break;
            }
        }
        if (count >= 4) {
            return 1;
        }
    }
    return 0;
}
int is_board_full(int rows, int cols, const char board[rows][cols]){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(board[i][j] == '.') return 0;
        }
    }
    return 1;
}
/*
void game(){
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK), init_pair(2, COLOR_BLUE, COLOR_BLACK),
    init_pair(3, COLOR_GREEN, COLOR_BLACK), init_pair(4, COLOR_YELLOW, COLOR_BLACK),
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK), init_pair(6, COLOR_CYAN, COLOR_BLACK),
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    const int rows = 6;
    const int cols = 6;
    char board[rows][cols];
    initialize_board(rows, cols, board);
    move(1, 1);
    attron(COLOR_PAIR(4) | A_BOLD);
    printw("Welcome to Connect 4!\n");
    attroff(COLOR_PAIR(4) | A_BOLD);
    int next = 1, player_flag = 1;
    while(next){
        move(2, 0);
        print_board(rows, cols, board);
        move(rows + 3, 1);
        attron(COLOR_PAIR(5) | A_BOLD);
	hline(ACS_HLINE, (cols * 4) + 1);
        attroff(COLOR_PAIR(5) | A_BOLD);
        move(rows + 4, 1);
        attron(COLOR_PAIR(5) | A_BOLD);
        for(int i = 0; i < cols; i++){
            printw("  %d ", i + 1);
        }
        attroff(COLOR_PAIR(5) | A_BOLD);
        move(rows + 5, 1);
        if(player_flag){
            clrtoeol();
            attron(COLOR_PAIR(1) | A_BOLD);
            printw("Player 1, enter your move (1 - %d)(Enter Q/q for exit): ", cols);
            attroff(COLOR_PAIR(1) | A_BOLD);
            int col = getch() - 48;
            if(col == 65 || col == 33){
                move(rows + 6, 1);
                attron(COLOR_PAIR(1) | A_BOLD);
                printw("Player 1 has left the game!\n");
                attroff(COLOR_PAIR(1) | A_BOLD);
                break;
            } int f = 1;
            while(!is_valid_move(rows, cols, board, col)){
                move(rows + 6, 1);
                attron(COLOR_PAIR(1) | A_BOLD);
                printw("Invalid move. Please, try again: ");
                attroff(COLOR_PAIR(1) | A_BOLD);
                col = getch() - 48;
                if(col == 65 || col == 33){
                    move(rows + 6, 1);
                    attron(COLOR_PAIR(1) | A_BOLD);
                    printw("Player 1 has left the game!\n");
                    attroff(COLOR_PAIR(1) | A_BOLD);
                    f = 0;
                    break;
                }
                move(rows + 6, 0);
                clrtoeol();
            }
            if(!f) break;//for exit

            attron(COLOR_PAIR(2) | A_BOLD);
            int row = drop_piece(rows, cols, board, col, 'X');
            attroff(COLOR_PAIR(2) | A_BOLD);
            if(check_win(rows, cols, board, row, col - 1, 'X')){
                move(rows + 6, 1);
                clrtoeol();
                attron(COLOR_PAIR(3) | A_BOLD);
                printw("Player 1 wins!\n");
                attroff(COLOR_PAIR(3) | A_BOLD);
                next = 0;
            }
            else if(is_board_full(rows, cols, board)){
                move(rows + 6, 1);
                attron(COLOR_PAIR(7) | A_BOLD);
                clrtoeol();
                printw("It's a tie!\n");
                attroff(COLOR_PAIR(7) | A_BOLD);
                next = 0;
            }
            player_flag = 0;
        }
        else{
            clrtoeol();
            attron(COLOR_PAIR(2) | A_BOLD);
            printw("Player 2, enter your move (1 - %d)(Enter Q/q for exit): ", cols);
            attroff(COLOR_PAIR(2) | A_BOLD);
            int col = getch() - 48;
            if(col == 65 || col == 33){
                move(rows + 6, 1);
                attron(COLOR_PAIR(1) | A_BOLD);
                printw("Player 2 has left the game!\n");
                attroff(COLOR_PAIR(1) | A_BOLD);
                break;
            }
            int f = 1;
            while(!is_valid_move(rows, cols, board, col)){
                move(rows + 6, 1);
                attron(COLOR_PAIR(2) | A_BOLD);
                printw("Invalid move. Please, try again: ");
                attroff(COLOR_PAIR(2) | A_BOLD);
                col = getch() - 48;
                if(col == 65 || col == 33){
                    move(rows + 6, 1);
                    attron(COLOR_PAIR(1) | A_BOLD);
                    printw("Player 2 has left the game!\n");
                    attroff(COLOR_PAIR(1) | A_BOLD);
                    f = 0;
                    break;
                }
                move(rows + 6, 0);
                clrtoeol();
            }
            if(!f) break;//for exit

            attron(COLOR_PAIR(3) | A_BOLD);
            int row = drop_piece(rows, cols, board, col, 'O');
            attroff(COLOR_PAIR(3) | A_BOLD);
            if(check_win(rows, cols, board, row, col - 1, 'O')){
                move(rows + 6, 1);
                clrtoeol();
                attron(COLOR_PAIR(3) | A_BOLD);
                printw("Player 2 wins!\n");
                attroff(COLOR_PAIR(3) | A_BOLD);
                next = 0;
            }
            else if(is_board_full(rows, cols, board)){
                move(rows + 6, 1);
                clrtoeol();
                attron(COLOR_PAIR(7) | A_BOLD);
                printw("It's a tie!\n");
                attroff(COLOR_PAIR(7) | A_BOLD);
                next = 0;
                break;
            }
            player_flag = 1;
        }
    }
    print_board(rows, cols, board);
    move(rows + 7, 1);
    refresh();
    getch();
    endwin();
}*/

