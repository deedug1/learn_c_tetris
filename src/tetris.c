
#include <stdio.h>
#include <stdlib.h>
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