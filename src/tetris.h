#ifndef TETRIS_H
#define TETRIS_H

#define NUM_BLOCKS 4
#define NUM_ORIENTATIONS 4
#define NUM_TYPES 7

#define GRID_COLS 10
#define GRID_ROWS 20

#define GRAVITY 25
#define EMPTY_BLOCK ' '
#define BLOCK ' '

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

  tetris_piece next;
  tetris_piece current;
  
  int ticks_till_gravity;
  int current_gravity;

} tetris_game;
typedef enum {
  I_TYPE, O_TYPE, Z_TYPE, T_TYPE, S_TYPE, J_TYPE, L_TYPE
} types;
typedef enum {
  E_BLOCK, I_BLOCK, O_BLOCK, Z_BLOCK, T_BLOCK, S_BLOCK, J_BLOCK, L_BLOCK
} block_types;
typedef enum {
  MOVE_DONT, MOVE_LEFT, MOVE_RIGHT, MOVE_DOWN, MOVE_HOLD, MOVE_ROTATE_CLOCK, MOVE_ROTATE_COUNTER
} moves;

location TETROMINOS[NUM_TYPES][NUM_ORIENTATIONS][NUM_BLOCKS];
void set_block(tetris_game * tg, int row, int col, char c);
char get_block(tetris_game * tg, int row, int col);
tetris_game * create_tg();
void new_current_piece(tetris_game * tg);
void put_piece(tetris_game * tg, tetris_piece p);
void shift_rows(tetris_game * tg, int row);
bool is_row_full(tetris_game * tg, int row);
bool is_inbounds(tetris_game * tg, int row, int col);
bool piece_fits(tetris_game * tg, tetris_piece p);
void step_gravity(tetris_game * tg);
void handle_input(tetris_game * tg, int input);
int clear_lines(tetris_game * tg);
void update_score(tetris_game * tg, int lines_cleared);
bool is_game_over(tetris_game * tg);
bool step_game(tetris_game * tg, int input);

#endif