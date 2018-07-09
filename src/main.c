#include <curses.h>
#include <stdio.h>
#include <stdlib.h>


// Testing
typedef struct {
  int rows;
  int cols;
  char * grid;
} board;

board * create_board(int rows, int cols) {
  board * brd = malloc(sizeof(board));
  brd->rows = rows;
  brd->cols = cols;
  brd->grid = malloc(rows * cols);
  return brd;
}
void set_boardch(board * brd, char ch, int row, int col){
  brd->grid[brd->cols * row + col] = ch;
}
char get_boardch(board *brd, int row, int col) {
  return brd->grid[brd->cols * row + col];
}
void fill_board(board * brd) {
  int row, col;
  for(row = 0; row < brd->rows; row++) {
    for(col = 0; col < brd->cols; col++) {
      if(col > 3  && col < 6) {
        set_boardch(brd, '%', row, col);
      } else {
        set_boardch(brd, '+', row, col);
      }
    }
  }
}
void draw_board(WINDOW * w, board * brd) {
  int row, col;
  box(w, 0, 0);
  for(row = 0; row < brd->rows; row++) {
    wmove(w, row + 1, 1);
    for(col = 0; col < brd->cols; col++) {
      if(get_boardch(brd, row, col) == '+') {
        waddch(w, ' ' | A_REVERSE);
      } else {
        waddch(w, ' ');
      }
    }
  }
  wnoutrefresh(w);
}
int main() {
  board * main_board;
  WINDOW * board_window;
  int rows = 20;
  int cols = 10;
  initscr();
  noecho();
  curs_set(0);
  main_board = create_board(rows, cols);
  board_window = newwin(main_board->rows + 2, main_board->cols + 2, 2, 50);
  fill_board(main_board);
  draw_board(board_window, main_board);
  wgetch(board_window);
  delwin(board_window);
  endwin();
  return 0;
}


