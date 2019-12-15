#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include "board.h"
#include "map.h"
#define getcol(c) ((c)*2+10)
#define getrow(r) ((r)+12)
#define TOTAL_R 30
#define TOTAL_C 20
#define FLAGGED_R 31
#define FLAGGED_C 20
#define BOARD_R 12
#define BOARD_C 9
#define S_C (BOARD_C+8)
#define S1_R (BOARD_R+4)
#define S2_R (BOARD_R+7)
#define S3_R (BOARD_R+10)
#define END_R 31
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
/* 12 */ "        #                                                             #\n"  /*  0 */
/* 13 */ "        #                                                             #\n"  /*  1 */
/* 14 */ "        #                                                             #\n"  /*  2 */
/* 15 */ "        #                                                             #\n"  /*  3 */
/* 16 */ "        #                                                             #\n"  /*  4 */
/* 17 */ "        #                                                             #\n"  /*  5 */
/* 18 */ "        #                                                             #\n"  /*  6 */
/* 19 */ "        #                                                             #\n"  /*  7 */
/* 20 */ "        #                                                             #\n"  /*  8 */
/* 21 */ "        #                                                             #\n"  /*  9 */
/* 22 */ "        #                                                             #\n"  /* 10 */
/* 23 */ "        #                                                             #\n"  /* 11 */
/* 24 */ "        #                                                             #\n"  /* 12 */
/* 25 */ "        #                                                             #\n"  /* 13 */
/* 26 */ "        #                                                             #\n"  /* 14 */
/* 27 */ "        #                                                             #\n"  /* 15 */
/* 28 */ "        ###############################################################\n"
/* 29 */ "        \n"
/*                  11111111112 */
/*        012345678901234567890 */
/* 30 */ "        Total:\n"
/* 31 */ "        Flagged:\n"
;
inline
void show_c(int c, int col, int row, WORD color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    WORD old = info.wAttributes;
    WORD new = (old & ~0xf) | color;
    SetConsoleTextAttribute(handle, new);
    COORD coord = {col, row};
    SetConsoleCursorPosition(handle, coord);
    putchar(c);
    SetConsoleTextAttribute(handle, old);
}
inline
void show_s(char *s, int col, int row, WORD color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    WORD old = info.wAttributes;
    WORD new = (old & ~0xf) | color;
    SetConsoleTextAttribute(handle, new);
    COORD coord = {col, row};
    SetConsoleCursorPosition(handle, coord);
    puts(s);
    SetConsoleTextAttribute(handle, old);
}
void clear_map()
{
    for (int r = 0; r < ROW; ++r)
        show_s("                                                             ",
        BOARD_C, getrow(r), 0);
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
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &default_info);
}
void show_frame()
{
    system("cls");
    printf("%s", frame);
}
void show_stats(int total, int flagged)
{
    char buf[5];
    _itoa_s(total, buf, sizeof buf / sizeof *buf, 10);
    show_s(buf, TOTAL_C, TOTAL_R, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    _itoa_s(flagged, buf, sizeof buf / sizeof *buf, 10);
    show_s(buf, FLAGGED_C, FLAGGED_R, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void show_map(int c)
{
    for (int row = 0; row < ROW; ++row)
        for (int col = 0; col < COL; ++col)
            show_c(c, getcol(col), getrow(row), FOREGROUND_INTENSITY);
}
void show_fail()
{
    for (int r = 0; r < ROW; ++r)
        for (int c = 0; c < COL; ++c)
        {
            int content = map_get(r, c);
            if (map_flagged(r, c))
                map_flag(r, c);
            if (!map_digged(r, c))
                map_dig(r, c);
            show_content(r, c);
        }
}
void show_info(char *s1, char *s2, char *s3)
{
    clear_map();
    show_s(s1, S_C, S1_R, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    show_s(s2, S_C, S2_R, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    show_s(s3, S_C, S3_R, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    show_s("", 0, END_R, 0);
}
void show_position(int r, int c)
{
    unsigned color;
    if (map_digged(r, c) || map_flagged(r, c))
        color = FOREGROUND_INTENSITY;
    else
        color = FOREGROUND_GREEN;
    show_c('[', getcol(c) - 1, getrow(r), color);
    show_c(']', getcol(c) + 1, getrow(r), color);
}
void hide_position(int r, int c)
{
    show_c(' ', getcol(c) - 1, getrow(r), 0);
    show_c(' ', getcol(c) + 1, getrow(r), 0);
}
void show_content(int r, int c)
{
    int content = map_get(r, c);
    if (map_flagged(r, c))
        show_c('F', getcol(c), getrow(r), FOREGROUND_RED | FOREGROUND_INTENSITY);
    else if (!map_digged(r, c))
        show_c('.', getcol(c), getrow(r), FOREGROUND_INTENSITY);
    else
        switch (content)
        {
            case -1:
                show_c('*', getcol(c), getrow(r), FOREGROUND_RED);
                break;
            case 0:
                show_c(' ', getcol(c), getrow(r), FOREGROUND_INTENSITY);
                break;
            case 1:
                show_c(content + '0', getcol(c), getrow(r), FOREGROUND_INTENSITY);
                break;
            case 2:
                show_c(content + '0', getcol(c), getrow(r), FOREGROUND_GREEN);
                break;
            case 3:
                show_c(content + '0', getcol(c), getrow(r), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;
            case 4:
                show_c(content + '0', getcol(c), getrow(r), FOREGROUND_BLUE | FOREGROUND_GREEN);
                break;
            case 5:
                show_c(content + '0', getcol(c), getrow(r), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;
            case 6:
                show_c(content + '0', getcol(c), getrow(r), FOREGROUND_RED | FOREGROUND_GREEN);
                break;
            case 7:
                show_c(content + '0', getcol(c), getrow(r), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;
            case 8:
                show_c(content + '0', getcol(c), getrow(r), FOREGROUND_RED | FOREGROUND_BLUE);
                break;
            default:
                break;
        }
}