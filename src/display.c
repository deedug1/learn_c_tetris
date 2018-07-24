
#include "curses.h"
#include "tetris.h"
#include "display.h"
#include <time.h>

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
/**
 * Draws the tetris board corresponding to the given tetris game.
 * Uses the WINDOW * BOARD to draw and returns if BOARD is not defined
 */
void draw_board(tetris_game * tg) {
  int row, col;
  if(!BOARD) { 
    printf("Board is not defined\n");
    return; 
  }
  wclear(BOARD);
  box(BOARD, 0, 0);
  for(row = 0; row < tg->rows; row++) {
    wmove(BOARD, row + 1, 1);
    for(col = 0; col < tg->cols; col++) {
      if(get_block(tg, row, col) != E_BLOCK) {
        waddch(BOARD, BLOCK|COLOR_PAIR(get_block(tg, row, col))|A_REVERSE);
        waddch(BOARD, BLOCK|COLOR_PAIR(get_block(tg, row, col))|A_REVERSE);
      } else {
        waddch(BOARD, EMPTY_BLOCK);
        waddch(BOARD, EMPTY_BLOCK);
      }
    }
  }
  draw_piece(BOARD, tg->current);
  wrefresh(BOARD);
}


/**
 * Draws the tetris board corresponding to the given tetris game.
 * Uses WINDOW * NEXT to draw and returns if NEXT is not defined
 */
void draw_next(tetris_piece next_piece) {
  if(!NEXT) {
    printf("NEXT is not defined\n");
    return;
  }
  wclear(NEXT);
  box(NEXT, 0, 0);
  draw_piece(NEXT, next_piece);
  wrefresh(NEXT);

}
/**
 * Draws the tetris game
 */
void draw_game(tetris_game * tg) {
  draw_board(tg);
  draw_next(tg->next);
}

int poll_input() {
  char input = getch();
  switch(lower(input)) {
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
/**
 * Converts a character to it's lowercase form
 */
char lower(char c) {
  if( c <= 'Z' && c >= 'A') { return c + 0x20; }
  return c;
}
/**
 * Initializes the color pairs for all the blocks
 */
void init_colors() {
  start_color();
  init_pair(I_BLOCK, COLOR_BLUE, COLOR_BLACK);
  init_pair(O_BLOCK, COLOR_YELLOW, COLOR_BLACK);
  init_pair(T_BLOCK, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(Z_BLOCK, COLOR_RED, COLOR_BLACK);
  init_pair(S_BLOCK, COLOR_GREEN, COLOR_BLACK);
  init_pair(J_BLOCK, COLOR_CYAN, COLOR_BLACK);
  init_pair(L_BLOCK, COLOR_WHITE, COLOR_BLACK);
}
/**
 * Initializes the screen for curses
 */
void init_screen() {
  initscr();      // Open a screen
  init_colors();  // Initialize color pairs
  cbreak();     // ???
  noecho();       // Don't echo key presses
  curs_set(0);    // Don't show the cursor
  timeout(0);     // Don't wait for a key to be pressed
}
