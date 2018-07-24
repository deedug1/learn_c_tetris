
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tetris.h"
/* Tetris piece data */
location TETROMINOS[NUM_TYPES][NUM_ORIENTATIONS][NUM_BLOCKS] = {
 { // I
   {{0,0}, {0,1}, {0,2}, {0,3}},
   {{0,0}, {1,0}, {2,0}, {3,0}},
   {{0,0}, {0,1}, {0,2}, {0,3}},
   {{0,0}, {1,0}, {2,0}, {3,0}},
  },
  { // O
   {{0,0}, {0,1}, {1,0}, {1,1}},
   {{0,0}, {0,1}, {1,0}, {1,1}},
   {{0,0}, {0,1}, {1,0}, {1,1}},
   {{0,0}, {0,1}, {1,0}, {1,1}},
  },
  { // Z
   {{0,0}, {0,1}, {1,1}, {1,2}},
   {{0,0}, {0,1}, {1,1}, {1,2}},
   {{0,1}, {1,1}, {1,0}, {2,0}},
   {{0,1}, {1,1}, {1,0}, {2,0}},
  },
  { // T
   {{0,1}, {1,0}, {1,1}, {1,2}},
   {{0,0}, {1,0}, {1,1}, {2,0}},
   {{0,0}, {0,1}, {0,2}, {1,1}},
   {{0,1}, {1,1}, {1,0}, {2,1}},
  },
  { // S
   {{1,0}, {1,1}, {0,1}, {0,2}},
   {{0,0}, {1,0}, {1,1}, {2,1}},
   {{1,0}, {1,1}, {0,1}, {0,2}},
   {{0,0}, {1,0}, {1,1}, {2,1}},
  },
  { // J
   {{0,0}, {1,0}, {1,1}, {1,2}},
   {{0,1}, {1,1}, {2,1}, {2,0}},
   {{0,0}, {0,1}, {0,2}, {1,2}},
   {{0,0}, {0,1}, {1,0}, {2,0}},
  },
  { // L
   {{1,0}, {1,1}, {1,2}, {0,2}},
   {{0,0}, {0,1}, {1,1}, {2,1}},
   {{0,0}, {1,0}, {0,1}, {0,2}},
   {{0,0}, {1,0}, {2,0}, {2,1}},
  }
};
/* Tetris game functions */
/**
 * Creates a new tetris_game
 */
tetris_game * create_tg(int rows, int cols) {
  tetris_game * tg = (tetris_game *)malloc(sizeof(tetris_game));
  tg->grid = (char *)malloc(sizeof(char) * cols * rows);
  memset(tg->grid, E_BLOCK, cols * rows);
  tg->rows = rows;
  tg->cols = cols;
  tg->score = 0;
  tg->current_gravity = GRAVITY;
  tg->ticks_till_gravity = GRAVITY;
  new_current_piece(tg);
  new_current_piece(tg);
  return tg;
}
/** 
 * Generates a new current piece for the tetris_game
 */
void new_current_piece(tetris_game * tg) {
  tg->current = tg->next;
  tg->current.location.col = tg->cols / 2;
  tg->next.type = rand() % NUM_TYPES;
  tg->next.location.row = 0;
  tg->next.location.col = 0;
  tg->next.orientation = 0;
}
/**
 * Gets a single block from the tetris_game board
 */
char get_block(tetris_game * tg, int row, int col) {
  return tg->grid[tg->cols * row + col];
}
/**
 * Sets a single block the the tetris_game board
 */
void set_block(tetris_game * tg, int row, int col, char c) {
  tg->grid[tg->cols * row + col] = c;
}
/**
 * Places a tetris_piece on the tetris_game board
 */
void put_piece(tetris_game * tg, tetris_piece p) {
  int index, row, col;
  for(index = 0; index < NUM_BLOCKS; index++) {
    row = p.location.row + TETROMINOS[p.type][p.orientation][index].row;
    col = p.location.col + TETROMINOS[p.type][p.orientation][index].col;
    set_block(tg, row, col, p.type + 1);
  }
}
/**
 * Checks to see if a row is full
 */
bool is_row_full(tetris_game * tg, int row) {
  int col;
  for(col = 0; col < tg->cols; col++){
    if(get_block(tg, row, col) == E_BLOCK) {
      return false;
    }
  }
  return true;
}
/**
 * shifts every row down one starting at row + 1
 */
void shift_rows(tetris_game * tg, int row) {
  int col;
  for(row = row - 1; row >= 0; row--) {
    for(col = 0; col < tg->cols; col++) {
      set_block(tg, row + 1, col, get_block(tg, row, col));
      set_block(tg, row, col, E_BLOCK);
    }
  }
}
/**
 * Rotates a piece in {direction}
 */
void rotate_piece(tetris_piece * p, int direction) {
  p->orientation += direction;
  if(p->orientation < 0) {
    p->orientation += NUM_ORIENTATIONS;
  }
  p->orientation %= NUM_ORIENTATIONS;
}


/**
 * Checks to see if a block is within the bounds of the
 *  tetris_game board
 */
bool is_inbounds(tetris_game * tg, int row, int col) {
  return row < tg->rows &&
         row >= 0 &&
         col < tg->cols &&
         col >= 0;
}
/** 
 * Checks to see if a block can fit in the game board
 *  at the pieces location within the tetris_game board
 */
bool piece_fits(tetris_game * tg, tetris_piece p) {
  int index, row, col;
  for(index = 0; index < NUM_BLOCKS; index++) {
    row = p.location.row + TETROMINOS[p.type][p.orientation][index].row;
    col = p.location.col + TETROMINOS[p.type][p.orientation][index].col;
    if(!is_inbounds(tg, row, col) || get_block(tg, row, col) != E_BLOCK) {
      return false;
    }
  }
  return true;
}
/**
 * Ticks gravity once and performs gravity logic
 */
void step_gravity(tetris_game * tg) {
  tg->ticks_till_gravity--;
  if(tg->ticks_till_gravity <= 0) {
    tg->ticks_till_gravity = tg->current_gravity;
    tg->current.location.row++;
    if(piece_fits(tg, tg->current)) {
    } else {
      tg->current.location.row--;
      put_piece(tg, tg->current);
      new_current_piece(tg);
    } 
  }
}
/**
 * Applys user input to the tetris_game
 */
void handle_input(tetris_game * tg, int input) {
  switch(input) {
    case MOVE_LEFT:
    tg->current.location.col--;
    if(!piece_fits(tg, tg->current)) {tg->current.location.col++;}
    break;
    case MOVE_RIGHT:
    tg->current.location.col++;
    if(!piece_fits(tg, tg->current)) {tg->current.location.col--;}
    break;
    case MOVE_DOWN:
      tg->current.location.row++;
      if(!piece_fits(tg, tg->current)) {tg->current.location.row--;}
    break;
    case MOVE_ROTATE_CLOCK:
      rotate_piece(&tg->current, 1);
      break;
    case MOVE_ROTATE_COUNTER:
      rotate_piece(&tg->current, -1);
      break;
    default: // no input do nothing
    break;
  }
}
/**
 * Scans the tetris_game board for any lines
 *  that need to be cleared and clears them
 */
int clear_lines(tetris_game * tg) {
  int row;
  int lines_cleared = 0;
  for(row = tg->rows; row >= 0; row--) {
    if(is_row_full(tg, row)) {
      shift_rows(tg, row);
      row++;
      lines_cleared++;
    }
  }
  return lines_cleared;
}
/**
 * Update the games score
 */
void update_score(tetris_game * tg, int lines_cleared) {
  tg->score += lines_cleared * 10;
}
/**
 * TODO
 * Checks the tetris_game to see if the game is over
 */
bool is_game_over(tetris_game * tg) {
  return true;
}
/**
 * Steps one frame of the tetris_game
 * 1. Check and apply gravity
 * 2. Apply user input
 * 3. Check and clear lines
 * 4. Update score
 * 5. Check gameover
 */
bool step_game(tetris_game * tg, int input) {
  int lines_cleared;
  step_gravity(tg);
  handle_input(tg, input);
  lines_cleared = clear_lines(tg);
  update_score(tg, lines_cleared);
  return is_game_over(tg);

} 
