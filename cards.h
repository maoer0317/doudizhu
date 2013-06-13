#ifndef CARDS_H
#define CARDS_H
 
typedef char T_A_CARD;
//one card is represented by a character in "Gg2AKQJ09876543"
//other is regarded as illegal
//'\0' cannot represent card, it could not be handled by T_CARDS
typedef char T_CARDS[21];
//20 is the maximum number of a hand of cards
//therefore I use a char[21] to represent a hand of cards
//this data strucure would be used as char * in the program

int sort_cards(T_CARDS cards);
//sort the cards. The regular sort is: Gg2AKQJ09876543.
//If sucess, return1; otherwise 0. Character which is not in above sequence would be discarded.

int in_cards(const T_CARDS cards, const T_CARDS cards_small);
//judge if the cards_small is in cards. The cards_small is not contiuously in the cards, so strstr cannot be used.  

int del_cards(T_CARDS cards, const T_CARDS cards_small);
//delete all cards in cards from cards_small. IF success, return 1 and cards stores the left cards, otherwise return 0, cards would be unchanged.

int cmp_2_card(const T_A_CARD c1, const T_A_CARD c2);
//compare 2 single cards. if c1 is big, return 1; if c1 is small, return -1; if equal, 0; cannot compare -10;
int get_card_index_in_order(const T_A_CARD card);
//return index in the "Gg2AKQJ09876543". The first index(card 'G') is 0. If card is not in, return -1. This function is used just by cmp_2_card function.

int del_card(T_CARDS cards, const T_A_CARD a_card);
//del a card from cards. If success, return 1; otherwise return 0

#endif

