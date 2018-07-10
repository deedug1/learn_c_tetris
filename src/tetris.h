#ifndef TETRIS_H
#define TETRIS_H

#define NUM_BLOCKS 4
#define NUM_ORIENTATIONS 4
#define NUM_TYPES 2

#define GRID_WIDTH 10
#define GRID_HEIGHT 20

#define GRAVITY 20

typedef struct {
  int score;

  int rows;
  int cols;  
  char * grid;

  tetris_piece current;
  tetris_piece hold;
  tetris_piece next;
  
  int ticks_till_gravity;
  int current_gravity;

} tetris_game;
typedef struct {
  int x;
  int y;
} point;
typedef struct {
  point * location;
  int type;
  int orientation;
} tetris_piece;
#endif