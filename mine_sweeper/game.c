#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include "map.h"
#include "board.h"
void move(int *cur_r, int *cur_c, int next_r, int next_c)
{
    if (next_r < 0 || next_r >= ROW || next_c < 0 || next_c >= COL)
        return;
    hide_position(*cur_r, *cur_c);
    *cur_r = next_r;
    *cur_c = next_c;
    show_position(next_r, next_c);
}
bool dig(int r, int c, int *left)
{
    if (r < 0 || r >= ROW || c < 0 || c >= COL || map_flagged(r, c) || map_digged(r, c))
        return true;
    int content = map_get(r, c);
    if (content == -1)
        return false;
     map_dig(r, c);
    show_content(r, c);
    --*left;
    if (content == 0)
    {
        dig(r - 1, c, left);
        dig(r - 1, c - 1, left);
        dig(r - 1, c + 1, left);
        dig(r, c - 1, left);
        dig(r, c + 1, left);
        dig(r + 1, c - 1, left);
        dig(r + 1, c, left);
        dig(r + 1, c + 1, left);
    }
    return true;
}
void flag(int r, int c, int *flagged)
{
    if (map_digged(r, c))
        return;
    map_flag(r, c);
    if (map_flagged(r, c))
        ++*flagged;
    else
        --*flagged;
    show_content(r, c);
}
int get_total()
{
    show_info("Please choose a level", "(1 = easiest, 5 = hardest)", "1    2    3    4    5");
    int level;
    while ((level = _getch()) < '1' || level > '5')
        ;
    return 30 * (level - '0');
}
bool win()
{
    show_info("You win! Congratulations!", "Press 'q' to end game", "Press 'n' to start a new game");
    int c;
    while ((c = _getch()) != 'n' && c != 'q')
        ;
    return c == 'n';
}
bool fail()
{
    show_fail();
    int c;
    while ((c = _getch()) != 'n' && c != 'q')
        ;
    return c == 'n';
}
bool play()
{
    show_frame();
    int total = get_total();
    int row = 0, col = 0, flagged = 0, left = COL * ROW;
    map_init(total);
    clear_map();
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            show_content(i, j);
    show_position(row, col);
    show_stats(total, flagged);
    int c;
    while ((c = _getch()) != 'q' && c != 'n')
    {
        switch (c)
        {
            case 'f':
                flag(row, col, &flagged);
                show_position(row, col);
                break;
            case 'd':
                if (!dig(row, col, &left))
                    return fail();
                else
                    show_position(row, col);
                break;
            case 72:
                move(&row, &col, row - 1, col);
                break;
            case 75:
                move(&row, &col, row, col - 1);
                break;
            case 80:
                move(&row, &col, row + 1, col);
                break;
            case 77:
                move(&row, &col, row, col + 1);
                break;
            default:
                break;
        }
        show_stats(total, flagged);
        if (flagged == total && left == total)
            return win();
    }
    return c == 'n';
}
int main()
{
    hide_cursor();
    while (play())
        ;
    show_info("Thank you for playing!", "Author: Yihao Wang", "14/12/2019");
    show_cursor();
}