
#include "curses.h"
#include "tetris.h"

void draw_board(WINDOW * w, tetris_game * tg) {
  int row, col;
  box(w, 0, 0);
  for(row = 0; row < tg->rows; row++) {
    wmove(w, row + 1, 1);
    for(col = 0; col < tg-> cols; col++) {
      if(get_block(tg, row, col) != E_BLOCK) {
        waddch(w, BLOCK|COLOR_PAIR(get_block(tg, row, col))|A_REVERSE);
        waddch(w, BLOCK|COLOR_PAIR(get_block(tg, row, col))|A_REVERSE);
      } else {
        waddch(w, EMPTY_BLOCK);
        waddch(w, EMPTY_BLOCK);
      }
    }
  }
}
void draw_piece(WINDOW * w, tetris_piece p) {
  int row, col;
  int index;
  for(index = 0; index < NUM_BLOCKS; index++) {
    row = p.location.row + TETROMINOS[p.type][p.orientation][index].row;
    col = p.location.col + TETROMINOS[p.type][p.orientation][index].col;
    wmove(w, row + 1, 2 * col + 1);
    waddch(w, BLOCK|COLOR_PAIR(p.type + 1)|A_REVERSE); 
    waddch(w, BLOCK|COLOR_PAIR(p.type + 1)|A_REVERSE); 
  }
}
void init_colors() {
  start_color();
  init_pair(I_BLOCK, COLOR_BLUE, COLOR_BLACK);
  init_pair(O_BLOCK, COLOR_YELLOW, COLOR_BLACK);
}
void init_screen() {
  initscr();
  init_colors();
  nocbreak();
  noecho();
  curs_set(0);  
}
void draw_game(WINDOW * w, tetris_game * tg) {
  wclear(w);
  draw_board(w, tg);
  draw_piece(w, tg->current);
  wrefresh(w);
} 