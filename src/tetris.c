
#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"
location TETROMINOS[NUM_TYPES][NUM_ORIENTATIONS][NUM_BLOCKS] = {
 {
   {{0,0}, {0,1}, {0,2}, {0,3}},
   {{0,0}, {1,0}, {2,0}, {3,0}},
   {{0,0}, {0,1}, {0,2}, {0,3}},
   {{0,0}, {1,0}, {2,0}, {3,0}},
  },
  {
   {{0,0}, {0,1}, {1,0}, {1,1}},
   {{0,0}, {0,1}, {1,0}, {1,1}},
   {{0,0}, {0,1}, {1,0}, {1,1}},
   {{0,0}, {0,1}, {1,0}, {1,1}},
  }
  };

  tetris_game * create_tg() {
    tetris_game * tg = (tetris_game *)malloc(sizeof(tetris_game));
    tg->grid = (char *)malloc(sizeof(char) * GRID_COLS * GRID_ROWS);
    tg->rows = GRID_ROWS;
    tg->cols = GRID_COLS;
    tg->score = 0;
    new_current_piece(tg);
    return tg;
  }
  void new_current_piece(tetris_game * tg) {
    tg->current.location.row = 0;
    tg->current.location.col = tg->cols / 2;
    tg->current.type = rand() % NUM_TYPES;
    tg->current.orientation = 0;
  }
