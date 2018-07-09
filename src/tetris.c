
#include "tetris.h"

point TETROMINOS[NUM_TYPES][NUM_ORIENTATIONS][NUM_BLOCKS] = {
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


  void move_down(tetris_piece *piece) {
    piece->location->y += 1;
  }
  void move_left(tetris_piece *piece) {
    piece->location->x -= 1;
  }
  void move_right(tetris_piece *piece) {
    piece->location->x += 1;
  }
  


