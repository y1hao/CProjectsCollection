#ifndef MINE_SWEEPER_BOARD_H
#define MINE_SWEEPER_BOARD_H
#include <stdbool.h>
extern void hide_cursor();
extern void show_cursor(int, int);
extern void show_frame();
extern void show_stats(int, int);
extern void show_map();
extern void show_fail();
extern void show_info(char *, char *, char *);
extern void show_position(int, int, bool);
extern void hide_position(int, int);
extern void show_content(int, int, int);
extern void show_flag(int, int, bool);
#endif