#ifndef TETRIS_H
#define TETRIS_H

#define NUM_BLOCKS 4
#define NUM_ORIENTATIONS 4
#define NUM_TYPES 2

#define GRID_COLS 10
#define GRID_ROWS 20

#define GRAVITY 20
#define EMPTY_BLOCK ' ';

typedef struct {
  int row;
  int col;
} location;
typedef struct {
  location location;
  int type;
  int orientation;
} tetris_piece;
typedef struct {
  int score;

  int rows;
  int cols;  
  char * grid;

  tetris_piece current;
  
  int ticks_till_gravity;
  int current_gravity;

} tetris_game;
typedef enum {
  I_TYPE, O_TYPE
} types;
typedef enum {
  E_TYPE, I_TYPE, O_TYPE
} block_types;
typedef enum {
  MOVE_LEFT, MOVE_RIGHT
} moves;
#endif