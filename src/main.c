#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"
#include "display.h"

#define GAME_ROWS 20
#define GAME_COLS 10

#define BOARD_HEIGHT GAME_ROWS + 2
#define BOARD_WIDTH 2 * GAME_COLS + 2
#define BOARD_ROW 0
#define BOARD_COL COLS / 2 - (BOARD_WIDTH / 2)

#define NEXT_HEIGHT 5
#define NEXT_WIDTH 8
#define NEXT_ROW 0
#define NEXT_COL BOARD_COL + BOARD_WIDTH + 4 

int main() {
  int input = MOVE_DONT;
  init_screen();
  tetris_game * tg = create_tg(GAME_ROWS, GAME_COLS);
  BOARD = newwin(BOARD_HEIGHT, BOARD_WIDTH, BOARD_ROW, BOARD_COL);
  NEXT = newwin(NEXT_HEIGHT, NEXT_WIDTH, NEXT_ROW, NEXT_COL);

  // Game loop
  while(1) {
    step_game(tg, input);
    draw_game(tg);
    input = poll_input();
    move(0,0);
    addch(input | 0x30);
    sleep(50);
  }
}


