
#include "curses.h"
#include "tetris.h"
#include <time.h>
void draw_board(WINDOW * w, tetris_game * tg) {
  int row, col;
  box(w, 0, 0);
  for(row = 0; row < tg->rows; row++) {
    wmove(w, row, 0);
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
    wmove(w, row, 2 * col);
    waddch(w, BLOCK|COLOR_PAIR(p.type + 1)|A_REVERSE); 
    waddch(w, BLOCK|COLOR_PAIR(p.type + 1)|A_REVERSE); 
  }
}
void draw_game(WINDOW * w, tetris_game * tg) {
  wclear(w);
  draw_board(w, tg);
  draw_piece(w, tg->current);
  wrefresh(w);
}
int poll_input() {
  char input = getch();
  switch(input) {
    case 'a': return MOVE_LEFT;
    case 'd': return MOVE_RIGHT;
    case 's': return MOVE_DOWN;
    case 'r': return MOVE_ROTATE_CLOCK;
    case 't': return MOVE_ROTATE_COUNTER;
    case ' ': return MOVE_HOLD;
    default: return MOVE_DONT;
  }

}
void sleep(int ms) {
  struct timespec t;
  t.tv_nsec = ms * 1000 * 1000;
  t.tv_sec = 0;
  nanosleep(&t, NULL);
}
 
void init_colors() {
  start_color();
  init_pair(I_BLOCK, COLOR_BLUE, COLOR_BLACK);
  init_pair(O_BLOCK, COLOR_YELLOW, COLOR_BLACK);
}
void init_screen() {
  initscr();      // Open a screen
  init_colors();  // Initialize color pairs
  cbreak();     // ???
  noecho();       // Don't echo key presses
  curs_set(0);    // Don't show the cursor
  timeout(0);     // Don't wait for a key to be pressed
}
