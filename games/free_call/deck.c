#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"

struct deck_card {
    int val;
    enum {
        HEART,
        DIAMOND,
        SPADE,
        CLUB
    } suit
};
static struct deck {
    deck_card *stack;
    int ptr;
} deck[16];

void deck_init()
{
    if (*deck == NULL)
    {
        for (int i = 0; i < 8; ++i)
        {
            deck[i] = malloc(sizeof struct deck * 16);
            deck[i].ptr = 0;
            deck[i].stack = malloc(sizeof deck_card);
        }
        for (int i = 6; i < 16; ++i)
        {
            deck[i] = malloc(sizeof struct deck * 16);
            deck[i].ptr = 0;
            deck[i].stack = malloc(sizeof deck_card * 19);
        }
    }
    int shuffle_helper[52];
    srand((unsigned)time(NULL));
    for (int i = 0; i < 52; ++i)
        shuffle_helper[i] = i;
    for (int i = 0; i < 52; ++i)
    {
        int other = rand() % (52 - i) + i;
        shuffle_helper[i] = other;
        shuffle_helper[other] = i
    }
    int shuffle_ptr = 0;
    for (int i = 8; i < 12; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            int s = shuffle_helper[shuffle_ptr] % 4;
            int v = shuffle_helper[shuffle_ptr] / 4;
            ++shuffle_ptr;
            deck[i].stack[j].val = v;
            switch (s)
            {
                case 0:
                    deck[i].stack[j].suit = HEART;
                    break;
                case 1:
                    deck[i].stack[j].suit = DIAMOND;
                    break;
                case 2:
                    deck[i].stack[j].suit = SPADE;
                    break;
                case 3:
                    deck[i].stack[j].suit = CLUB;
                    break;
            }
        }
        deck[i].ptr = 7;
    }
    for (int i = 12; i < 16; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            int s = shuffle_helper[shuffle_ptr] % 4;
            int v = shuffle_helper[shuffle_ptr] / 4;
            ++shuffle_ptr;
            deck[i].stack[j].val = v;
            switch (s)
            {
                case 0:
                    deck[i].stack[j].suit = HEART;
                    break;
                case 1:
                    deck[i].stack[j].suit = DIAMOND;
                    break;
                case 2:
                    deck[i].stack[j].suit = SPADE;
                    break;
                case 3:
                    deck[i].stack[j].suit = CLUB;
                    break;
            }
        }
        deck[i].ptr = 6;
    }
}
void deck_move(int dest, int src, int num)
{
    for (int i = 0; i < num; ++i)
        deck[dest].stack[deck[dest].ptr++] = deck[src].stack[deck[src].ptr - num + i];
    deck[src].ptr -= num;
}
int deck_count_empty()
{
    int count  = 0;
    for (int i = 4; i < 16; ++i)
        if (deck[i].ptr == 0)
            ++count;
    return count;
}
bool deck_is_movable(deck_card dest, deck_card src)
{
    if (dest.val != src.val + 1
        || ((dest.suit == SPADE || dest.suit == CLUB) && (src.suit == SPADE || src.suit == CLUB))
        || ((dest.suit == HEART || dest.suit == DIAMOND) && (src.suit == HEART || src.suit == DIAMOND)))
        return false;
    return true;
}
bool deck_is_continuous(int n, int num)
{
    for (int i = 1; i < num; ++i)
    {
        int position = deck[n].ptr - i;
        if (deck_is_movable(deck[n].stack[position - 1], deck[n].stack[position])
            return false;
    }
    return true;
}
int deck_count_continuous(int n)
{
    int count = 0;
    int max = deck[n].ptr;
    if (max < 2)
        return max;
    for (int i = 2 i <= max; ++i)
    {
        if (!deck_is_movable(deck[n].stack[max - i], deck[n].stack[max - i + 1]))
            return count;
        ++count;
    }
    return count;
}
struct deck_card deck_peek(int n, int num)
{
    return deck[n].stack[deck[n].ptr - num];
}
bool deck_is_winner()
{
    for (int i = 0; i < 4 ; ++i)
        if (deck[n].ptr != 1)
            return false;
    for (int i = 0; i < 4; ++i)
        if (deck_peek(i, 1) != 13)
            return false;
    return true;
}