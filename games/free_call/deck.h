#ifndef FREE_CALL_DECK_H
#define FREE_CALL_DECK_H
struct deck_card;
extern void deck_init();
extern void deck_move(int dest, int src, int num);
extern int deck_count_empty();
extern int deck_count_continuous(int stack);
extern bool deck_is_continuous(int stack, int num);
extern bool deck_is_movable(struct deck_card dest, struct deck_card src);
extern struct deck_card deck_peek(int stack, int num);
extern bool deck_is_winner();
#endif