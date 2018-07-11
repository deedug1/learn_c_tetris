
#include "curses.h"
#include "tetris.h"

void draw_board(WINDOW * w, tetris_game * tg) {
  int row, col;
  box(w, 0, 0);
  for(row = 0; row < tg->rows; row++) {
    wmove(w, row, 0);
    for(col = 0; col < tg-> cols; col++) {
      if(get_block(tg, row, col) != E_TYPE) {
        waddch(w, BLOCK|COLOR_PAIR(get_block(tg, row, col) + 1)|A_REVERSE);
      } else {
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
    col = p.location.row + TETROMINOS[p.type][p.orientation][index].col;
    wmove(w, row, col);
    waddch(w, BLOCK|COLOR_PAIR(p.type + 1)|A_REVERSE); 
  }
}
void init_colors() {
  init_pair(I_TYPE, COLOR_BLUE, COLOR_BLACK);
  init_pair(O_TYPE, COLOR_YELLOW, COLOR_BLACK);
}
void draw_game(WINDOW * w, tetris_game * tg) {
  draw_board(w, tg);
  draw_piece(w, tg->current);
} 