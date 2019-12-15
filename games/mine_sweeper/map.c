#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "map.h"
static struct {
    int val;
    bool digged;
    bool flagged;
} map[ROW][COL];
inline 
void inc(int r, int c)
{
    if (r < 0 || r >= ROW || c < 0 || c >= COL || map[r][c].val == -1)
        return;
    map[r][c].val += 1;
}
void map_init(int n)
{
    for (int r = 0; r < ROW; ++r)
        for (int c = 0; c < COL; ++c)
        {
            map[r][c].val = 0;
            map[r][c].digged = false;
            map[r][c].flagged = false;
        }
    srand((unsigned)time(NULL));
    int rand_helper[ROW * COL];
    for (int i = 0; i < ROW * COL; ++i)
        rand_helper[i] = i;
    for (int i = 0; i < n; ++i)
    {
        int other = rand() % (n - i) + i;
        int temp = rand_helper[i];
        rand_helper[i] = rand_helper[other];
        rand_helper[other] = temp;
    }
    for (int i = 0; i < n; ++i)
    {
        int row = rand_helper[i] / COL;
        int col = rand_helper[i] % COL;
        map[row][col].val = -1;
        inc(row - 1, col - 1);
        inc(row - 1, col);
        inc(row - 1, col + 1);
        inc(row, col - 1);
        inc(row, col + 1);
        inc(row + 1, col - 1);
        inc(row + 1, col);
        inc(row + 1, col + 1);
    }
}
inline
int map_get(int r, int c)
{
    if (r < 0 || r >= ROW || c < 0 || c >= COL)
        return 0;
    return map[r][c].val;
}
inline
bool map_digged(int r, int c)
{
    if (r < 0 || r >= ROW || c < 0 || c >= COL)
        return true;
    return map[r][c].digged;
}
inline
void map_dig(int r, int c)
{
    if (r < 0 || r >= ROW || c < 0 || c >= COL)
        return;
    map[r][c].digged = true;
}
inline
bool map_flagged(int r, int c)
{
    if (r < 0 || r >= ROW || c < 0 || c >= COL)
        return false;
    return map[r][c].flagged;
}
inline
void map_flag(int r, int c)
{
    if (r < 0 || r >= ROW || c < 0 || c >= COL)
        return;
    map[r][c].flagged = !map[r][c].flagged;
}