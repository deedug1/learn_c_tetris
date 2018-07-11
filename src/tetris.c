
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
char get_block(tetris_game * tg, int row, int col) {
  return tg->grid[tg->cols * row + col];
}
void set_block(tetris_game * tg, int row, int col, char c) {
  tg->grid[tg->cols * row + col] = c;
}
void put_piece(tetris_game * tg, tetris_piece p) {
  int index, row, col;
  for(index = 0; index < NUM_BLOCKS; index++) {
    row = p.location.row + TETROMINOS[p.type][p.orientation][index].row;
    col = p.location.row + TETROMINOS[p.type][p.orientation][index].col;
    set_block(tg, row, col, p.type + 1);
  }
}
void remove_piece(tetris_game * tg, tetris_piece p) {

}
// Shift all rows above code{row} down one
void shift_rows(tetris_game * tg, int row) {
  int col;
  for(row = row - 1; row >= 0; row--) {
    for(col = 0; col < tg->cols; col++) {
      set_block(tg, row + 1, col, get_block(tg, row, col));
      set_block(tg, row, col, E_TYPE);
    }
  }
}
bool is_row_full(tetris_game * tg, int row) {
  int col;
  for(col = 0; col < tg->cols; col++){
    if(get_block(tg, row, col) == E_TYPE) {
      return false;
    }
  }
  return true;
}
bool is_inbounds(tetris_game * tg, int row, int col) {
  return row >= tg->rows ||
         row < 0 ||
         col >= tg-> cols ||
         col < 0;
}
bool piece_fits(tetris_game * tg, tetris_piece p) {
  int index, row, col;
  for(index = 0; index < NUM_BLOCKS; index++) {
    row = p.location.row + TETROMINOS[p.type][p.orientation][index].row;
    col = p.location.col + TETROMINOS[p.type][p.orientation][index].col;
    if(!is_inbounds(tg, row, col) || get_block(tg, row, col) != E_TYPE) {
      return false;
    }
  }
  return true;
}
void step_gravity(tetris_game * tg) {
  tg->ticks_till_gravity--;
  if(tg->ticks_till_gravity <= 0) {
    tg->current.location.row++;
    if(piece_fits(tg, tg->current)) {
      tg->ticks_till_gravity = tg->current_gravity;
    } else {
      tg->current.location.row--;
      put_piece(tg, tg->current);
      new_current_piece(tg);
    } 
  }
}
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
    default: // no input do nothing
    break;
  }
}
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
void update_score(tetris_game * tg, int lines_cleared) {
  tg->score += lines_cleared * 10;
}
bool is_game_over(tetris_game * tg) {
  return true; //TODO
}
bool step_game(tetris_game * tg, int input) {
  int lines_cleared;
  step_gravity(tg);
  handle_input(tg, input);
  lines_cleared = clear_lines(tg);
  update_score(tg, lines_cleared);
  return is_game_over(tg);

} 
