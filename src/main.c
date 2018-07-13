#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"
#include "display.h"
int main() {
  int input = MOVE_DONT;
  init_screen();
  tetris_game * tg = create_tg();
  BOARD = newwin(tg->rows + 2, 2*tg->cols + 2, 0, 50);
  NEXT = newwin(5, 10, 0, 50 + 2*tg->cols + 5);
  while(1) {
    step_game(tg, input);
    draw_game(tg);
    sleep(50);
    input = poll_input();
  }
}


