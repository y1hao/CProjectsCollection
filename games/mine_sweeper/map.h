#ifndef MINE_SWEEPER_MAP_H
#define MINE_SWEEPER_MAP_H
#define ROW 10
#define COL 30
extern void map_init(int);
extern int map_get(int, int);
extern bool map_digged(int, int);
extern void map_dig(int, int);
extern bool map_flagged(int, int);
extern void map_flag(int, int);
#endif