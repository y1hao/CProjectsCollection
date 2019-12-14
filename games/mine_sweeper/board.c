#include <stdbool.h>
#include <Windows.h>
#include "board.h"
#include "map.h"
#define getcol(c) (((c)+2)*10)
#define getrow(r) ((r)+12)
static CONSOLE_CURSOR_INFO default_info;
static char frame[] =
/*  0 */ "        \n"
/*  1 */ "        \n"
/*  2 */ "        Welcome to Mine Sweeper!\n"
/*  3 */ "        \n"
/*  4 */ "        Use left, up, right and down arrows to switch positions\n"
/*  5 */ "        Press 'f' to flag a mine\n"
/*  6 */ "        Press 'd' to dig a mine\n"
/*  7 */ "        Press 'q' to quit game\n"
/*  8 */ "        Press 'n' to start a new game\n"
/*  9 */ "        \n"
/* 10 */ "        \n"
/*                  11111111112222222222333333333344444444445555555555666666666 */
/*        012345678901234567890123456789012345678901234567890123456789012345678 */
/*                  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 */
/* 11 */ "        ###############################################################\n"
/* 12 */ "        # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . #\n"  /* 0 */
/* 13 */ "        # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . #\n"  /* 1 */
/* 14 */ "        # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . #\n"  /* 2 */
/* 15 */ "        # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . #\n"  /* 3 */
/* 16 */ "        # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . #\n"  /* 4 */
/* 17 */ "        # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . #\n"  /* 5 */
/* 18 */ "        # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . #\n"  /* 6 */
/* 19 */ "        # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . #\n"  /* 7 */
/* 20 */ "        # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . #\n"  /* 8 */
/* 21 */ "        # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . #\n"  /* 9 */
/* 22 */ "        ###############################################################\n"
/* 23 */ "        \n"
/*                  11111111112 */
/*        012345678901234567890 */
/* 24 */ "        Total:\n"
/* 25 */ "        Flagged:\n"
inline
void show_c(char c, int col, int row, unsigned color)
{

}
inline
void show_s(char *s, int len, int col, int row, unsigned color)
{
    
}
void hide_cursor()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(handle, &default_info);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(handle, &info);
}
void show_cursor()
{
    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &default_info);
}
void show_frame()
{
    system("cls");
    printf(frame);
}
void show_stats(int total, int flagged)
{

}
void show_map()
{

}
void show_fail()
{

}
void show_info(char *s1, char *s2, char *s3)
{

}
void show_position(int r, int c)
{

}
void hide_position(int r, int c)
{

}
void show_content(int r, int c)
{

}
void show_flag(int r, int c)
{

}