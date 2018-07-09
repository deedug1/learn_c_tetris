#ifndef TETRIS_H
#define TETRIS_H

#define NUM_BLOCKS 4
#define NUM_ORIENTATIONS 4
#define NUM_TYPES 2

#define GRID_WIDTH 10
#define GRID_HEIGHT 20

typedef struct {
  int score;
  char grid[GRID_WIDTH][GRID_HEIGHT];
  tetris_piece current_piece;
  tetris_piece hold_piece;

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