#ifndef FREE_CALL_DECK_H
#define FREE_CALL_DECK_H
typedef struct deck_card deck_card;
extern void deck_init();
extern bool deck_is_movable(deck_card dest, deck_card src);
extern void deck_move(int dest, int src, int num);
extern int  deck_count_continuous(int n);
extern bool deck_is_winner();
extern void deck_finish();
#endif