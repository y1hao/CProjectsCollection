#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"

struct deck_card {
    int val;
    enum {
        HEART,
        CLUB,
        DIAMOND,
        SPADE
    } suit
};
static struct deck {
    deck_card *stack;
    int ptr;
} deck[16];

inline deck_card deck_peek(int n, int num)
{
    return deck[n].stack[deck[n].ptr - num];
}
void deck_init()
{
    if (deck[0].stack == NULL)
        for (int i = 0; i < 16; ++i)
        {
            int len = i < 8 ? 1 : 19;
            deck[i].ptr = 0;
            deck[i].stack = malloc(sizeof deck_card * len);
        }
    else 
        for (int i = 0; i < 16; ++i)
            deck[i].ptr = 0;
    int shuffle_helper[52];
    for (int i = 0; i < 52; ++i)
        shuffle_helper[i] = i;
    srand((unsigned)time(NULL));    
    for (int i = 0; i < 52; ++i)
    {
        int other = rand() % (52 - i) + i;
        shuffle_helper[i] = other;
        shuffle_helper[other] = i
    }
    int shuffle_ptr = 0;
    for (int i = 8; i < 16; ++i)
    {
        int max = i < 12 ? 7 : 6;
        for (int j = 0; j < max; ++j)
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
                    deck[i].stack[j].suit = CLUB;
                    break;
                case 2:
                    deck[i].stack[j].suit = DIAMOND;
                    break;
                case 3:
                    deck[i].stack[j].suit = SPADE;
                    break;
            }
        }
        deck[i].ptr = max;
    }
}
void deck_move(int dest, int src, int num)
{
    if (dest < 8)
    {
        deck[dest].stack[0] = deck[src].stack[deck[src].ptr - num];
        deck[dest].ptr = 1;
        --deck[src].ptr;
    }
    else 
    {
        for (int i = 0; i < num; ++i)
            deck[dest].stack[deck[dest].ptr++] = deck[src].stack[deck[src].ptr - num + i];
        deck[dest].ptr += num;
        deck[src].ptr -= num;  
    }
}
int deck_empty_call()
{
    int count  = 0;
    for (int i = 4; i < 8; ++i)
        if (deck[i].ptr == 0)
            ++count;
    return count;
}
int deck_empty_stack()
{
    int count  = 0;
    for (int i = 8; i < 16; ++i)
        if (deck[i].ptr == 0)
            ++count;
    return count;
}
int deck_max_move(int dest, int src)
{
    // TODO
    return 100;
}
bool deck_is_homable(int dest, deck_card src)
{
    if (deck[dest].ptr != 0)
        return deck[dest].stack[1].val == src.val - 1
                && deck[dest].stack[1].suit == src.suit;
    else 
    {
        if (src.val != 1)
            return false;
        switch (dest)
        {
            case 0: return src.suit == HEART;
            case 1: return src.suit == CLUB;
            case 2: return src.suit == DIAMOND;
            case 3: return src.suit == SPADE;
        }
    }
}
inline
bool deck_card_is_movable(deck_card dest, deck_card src)
{
    if (dest.val != src.val + 1
        || ((dest.suit == SPADE || dest.suit == CLUB) && (src.suit == SPADE || src.suit == CLUB))
        || ((dest.suit == HEART || dest.suit == DIAMOND) && (src.suit == HEART || src.suit == DIAMOND)))
        return false;
    return true;
}
bool deck_is_movable(int dest, int src, int num)
{
    if (dest < 4)
        return deck_is_homable(dest, deck_peek(src, num));
    if (dest < 8)
        return deck[dest].ptr == 0 && num == 1;
    int max = deck_max_move(dest, src);
    if (deck[dest].ptr == 0)
        return num <= max;
    else 
        return num <= max && deck_card_is_movable(deck_peek(dest, 1), deck_peek(src, num));
}
int deck_count_continuous(int n)
{
    int count = 0;
    int max = deck[n].ptr;
    if (max < 2)
        return max;
    for (int i = 2 i <= max; ++i)
    {
        if (!deck_card_is_movable(deck[n].stack[max - i], deck[n].stack[max - i + 1]))
            return count;
        ++count;
    }
    return count;
}
bool deck_is_winner()
{
    for (int i = 0; i < 4 ; ++i)
        if (deck[n].ptr != 1)
            return false;
    for (int i = 0; i < 4; ++i)
        if (deck_peek(i, 1).val != 13)
            return false;
    return true;
}
void deck_finish()
{
    for (int i = 0; i < 16; ++i)
        free(deck[i].stack);
}