/* tested platform: windows10 + clang */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <Windows.h>

#define MAX_ROW 15
#define MAX_COL 20
#define DEFAULT_WIDTH 10
#define DEFAULT_HEIGHT 10
#define LOWER 2
#define UPPER 3
#define SYM "*"
#define PAUSE 500

HANDLE handle;
enum status 
{
    INIT,
    EXAMPLE,
    SET_SIZE,
    SET_SEEDS,
    PLAY,
    EXIT
} status = INIT;
struct 
{
    int width;
    int height;
    long long round;
    bool *life;
} map = 
{
    .width = DEFAULT_WIDTH, 
    .height = DEFAULT_HEIGHT, 
    .round = 0LL,
    .life = NULL
};
bool buf1[MAX_ROW * MAX_COL];
bool buf2[MAX_ROW * MAX_COL];

enum status user_info();
enum status show_example();
enum status set_size();
enum status set_seeds();
enum status play();
void init_map();
bool compute();
/* the params for draw, draw_content and show_round are the row from which to print */
void draw(int);
void draw_content(int);
void show_round(int);
void set(bool *, int, int, bool);
int get(bool *, int, int);

int main()
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    while (status != EXIT)
    {
        switch (status)
        {
            case INIT:
                status = user_info();
                break;
            case EXAMPLE:
                status = show_example();
                break;
            case SET_SIZE:
                status = set_size();
                break;
            case SET_SEEDS:
                status = set_seeds();
                break;
            case PLAY:
                status = play();
                break;
            default:
                break;
        }
    }
    system("cls");
    printf("\n\n\tThank you for playing!");
    printf("\n\n\tAuthor: Yihao Wang, 22/11/2019");
    Sleep(2000);
    system("cls");
}

enum status user_info()
{
    system("cls");
    static char info[] = 
    "\n\tConway's Game of Life\n\n"
    "\tWelcome!\n\n"
    "\tThe Game of Life, also known simply as Life,\n"
    "\tis a cellular automaton devised by the British mathematician John Horton Conway in 1970.\n"
    "\tThe game is a zero-player game, \n"
    "\tmeaning that its evolution is determined by its initial state, requiring no further input.\n"
    "\tOne interacts with the Game of Life by creating an initial configuration\n"
    "\tand observing how it evolves.\n\n"
    "\tThe game is represented on a board of cells. Each cell has two possible states: living and dead\n"
    "\t1. Any live cell with two or three neighbors survives.\n"
    "\t2. Any dead cell with three live neighbors becomes a live cell.\n"
    "\t3. All other live cells die in the next generation. Similarly, all other dead cells stay dead.\n\n"
    "\tPress 'x' to view an example\n\n"
    "\tPress 's' to set and play your own game\n\n"
    "\tPress 'q' to quit the game\n\t";
    printf("%s", info);
    switch (_getch())
    {
        case 'q':
            return EXIT;
        case 'x':
            return EXAMPLE;
        case 's':
            return SET_SIZE;
        default:
            return INIT;
    }
}

enum status show_example()
{
    init_map();
    int row[] = {5,5,6,6,7,2,2,3,5,6,7,8};
    int col[] = {5,4,6,7,7,8,9,5,3,3,3,4};
    for (int i = 0; i < sizeof row / sizeof *row; ++i)
        set(map.life, row[i], col[i], true);
    return PLAY;
}

enum status set_size()
{
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    system("cls");
    printf("\n\tNow let's set the size of the board\n\n");
    while (true)
    {
        printf("\n\tPlease input an integer representing the board width (at most %d):\n\n\t", MAX_COL);
        if (scanf_s("%d", &width) == 1 && width >= 0 && width <= MAX_COL)
            break;
        printf("\n\tInvalid input, try again!\n");
        Sleep(1000);
        fflush(stdin);
    }
    while (true)
    {
        printf("\n\tPlease input an integer representing the board height (at most %d):\n\n\t", MAX_ROW);
        if (scanf_s("%d", &height) == 1 && height >= 0 && height <= MAX_ROW)
            break;
        printf("\n\tInvalid input, try again!\n");
        Sleep(1000);
        fflush(stdin);
    }
    map.width = width;
    map.height = height;
    return SET_SEEDS;
}

enum status set_seeds()
{
    int row, col, c;
    init_map();
    while (true)
    {
        system("cls");
        printf("\n\tNow let's set some seeds:\n\n");
        draw(3); /* 3 is begining row to draw the board, update this if the above printed information changes */
        draw_content(5); /* the row from which to print the content is alway 2 more than that in draw, representing the border */
        printf("\n\tSet a coordinate here \n\t(e.g. 'g' and then '5' changes the status of the cell 'g5')\n");
        printf("\tEnter the column index (e.g. 'g', at most '%c'):\n", map.width + 'a' - 1);
        printf("\t\t(press 'Q' if you are done)\n\t");
        if ((col = _getch()) != 'Q'
            && col - 'a' >= 0
            && col - 'a' < map.width)
        {
            printf("%c\n\n", col);
            col = col - 'a';
        } 
        else if (col == 'Q')
            return PLAY;
        else
        {
            printf("\tInvalid input, try again!\n");
            Sleep(1000);
            continue;
        }    
        printf("\tEnter the row index (e.g. '5', at most %d):\n\t", map.height);
        if (scanf_s("%d", &row) == 1
            && row > 0
            && row <= map.height)
            row -= 1;
        else
        {
            printf("\tInvalid input, try again!\n");
            Sleep(1000);
            continue;
        }   
        set(map.life, row, col, 
            get(map.life, row, col) ? false : true);
    }
}

enum status play()
{ 
    CONSOLE_CURSOR_INFO show_cursor;
    GetConsoleCursorInfo(handle, &show_cursor);
    CONSOLE_CURSOR_INFO hide_cursor = {.bVisible = false, .dwSize = 1};
    SetConsoleCursorInfo(handle, &hide_cursor);
    system("cls");
    printf("\n\tConway's Game of Live\n\n\twidth:\t%d\theight:\t%d\n\n"
        , map.width, map.height);
    show_round(5); /* update this if the above printed information changes */
    printf("\tPress 's' to set a new game\n");
    printf("\tPress 'q' to quit the game\n\n");
    draw(10); /* update this if the above printed information changes */
    bool terminate = false;
    while (!terminate)
    {
        draw_content(12); /* always 2 more than in draw*/
        show_round(5); /* update this */
        if (_kbhit())
        {
            switch (_getch())
            {
            case 's':
                return SET_SIZE;
            case 'q':
                return EXIT;
            default:
                break;
            }
        }
        terminate = compute();
        Sleep(PAUSE);
    }
    COORD cur = {0, 10 + map.height + 3};
    SetConsoleCursorPosition(handle, cur);
    printf("\n\tNo cell is alive in the next round, the game terminates!\n\n");
    printf("\tPress 's' to set a new game\n");
    printf("\tPress 'q' to quit the game\n\n\t");
    SetConsoleCursorInfo(handle, &show_cursor);
    while (true)
    {
        switch (_getch())
        {
        case 's':
            return SET_SIZE;
        case 'q':
            return EXIT;
        default:
            break;
        }
    }
}

bool compute()
{
    bool *cur = map.life, *next;
    bool alive = false;
    if (cur == buf1)
        next = buf2;
    else
        next = buf1;
    int count;
    for (int i = 0; i < map.height; ++i)
    {
        for (int j = 0; j < map.width; ++j)
        {
            count = get(cur, i - 1, j - 1)
                + get(cur, i - 1, j)
                + get(cur, i - 1, j + 1)
                + get(cur, i, j - 1)
                + get(cur, i, j + 1)
                + get(cur, i + 1, j - 1)
                + get(cur, i + 1, j)
                + get(cur, i + 1, j + 1);
            if ((get(cur, i, j) && (count == 2 || count == 3))
                || (!get(cur, i, j) && count == 3))
            {
                set(next, i, j, true);
                alive = true;
            }   
            else 
                set(next, i, j, false);
        }
    }
    map.life = next;
    ++map.round;
    return !alive || map.round < 0;
}

void draw(int row)
{
    COORD coord = {0, row};
    SetConsoleCursorPosition(handle, coord);
    int col_index = 'a';
    int row_index = 1;
    /* column index */
    printf("\t   ");
    for (int i = 0; i < map.width; ++i)
        printf("%2c", col_index++);
    printf("\n");
    /* upper border */
    printf("\t  ");
    for (int i = 0; i < 2 * map.width + 3; ++i)
        printf("#");
    printf("\n");
    /* content */
    for (int i = 0; i < map.height; ++i)
    {
        /* row index */
        printf("\t%2d# ", row_index++);
        for (int j = 0; j < map.width; ++j)
            printf("  ");
        printf("#\n");
    }
    /* lower border */      
    printf("\t  ");
    for (int i = 0; i < 2 * map.width + 3; ++i)
        printf("#");
    printf("\n");
}

void draw_content(int row)
{
    COORD coord = {12, row}; /* 12 = 8 for tabs + 2 for index + 2 for left border */
    for (int i = 0; i < map.height; ++i)
    {
        SetConsoleCursorPosition(handle, coord);
        for (int j = 0; j < map.width; ++j)
        {
            printf("%s ", get(map.life, i, j) ? SYM : " ");
        }
        ++coord.Y;
    }
    ++coord.Y;
    SetConsoleCursorPosition(handle, coord);
}

void show_round(int row)
{
    COORD coord = {0, row};
    SetConsoleCursorPosition(handle, coord);
    printf("\tround: %lld\n\n", map.round);
}

inline
void init_map()
{
    for (int i = 0; i < MAX_ROW * MAX_COL; ++i)
        buf1[i] = buf2[i] = false;
    map.life = buf1;
    map.round = 0;
}

inline
void set(bool *buf, int row, int col, bool val)
{
    buf[row * map.width + col] = val;
}

inline
int get(bool *buf, int row, int col)
{
    if (row < 0 
        || row >= map.height
        || col < 0
        || col >= map.width)
        return 0;
    return buf[row * map.width + col] ? 1 : 0;
}