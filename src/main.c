#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"
#include "display.h"
int main() {
  int input = MOVE_DONT;

  init_screen();
  tetris_game * tg = create_tg();
  WINDOW * w = newwin(tg->rows + 2, 2*tg->cols + 2, 0, 30);
  while(1) {
    step_game(tg, input);
    draw_game(w, tg);
    sleep(50);
    input = poll_input();
  }
}


