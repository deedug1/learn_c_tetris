#include <curses.h>
#include "tetris.h"
#ifndef DISPLAY_H
#define DISPLAY_H

WINDOW * BOARD;
WINDOW * NEXT; 
void init_screen();
void init_colors();
void draw_game(tetris_game * tg);
void draw_board(WINDOW * w, tetris_game * tg);
void draw_piece(WINDOW * w, tetris_piece tp);
int poll_input();
void sleep(int ms);
#endif