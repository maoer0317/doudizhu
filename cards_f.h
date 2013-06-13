#ifndef CARDS_F_H
#define CARDS_F_H

#include "cards.h"

typedef struct f_node
{
  T_CARDS fk_cards;
  char fk_class;
  char fk_base;
  struct f_node *next;
}T_F_NODE;
//data structure of a functor:
//1. fk_cards represent the cards that are legally played 
//  by dizhu or nongmin according to the rule of the game.
//2. fk_class is the functor's class, which is represent by a type of char in the design doc and hence here it is char.
//3. fk_base is a char, representing the base of the class, for example: shunzi 345678, it's fk_base is '3' and fk_class is 'F'.
// fk_class and fk_base are redundant that can be deduced by fk_cards.
// But they are very useful when deducing the play back of dizhu or nongmi.

//all legal functors would be store in a linked table of nodes, which are ordered by the number of cards. 
//  (if 2 cards are equally numeric, the node produced first would be in the front of the table)
//each node in the table is different. There are not any 2 nodes whose fk_cards are equal. 
//each node is the type of T_F_NODE, whose fk_cards is a null terminated string. There is a particular functor whose fk_cards field is a "" string.
//this is legal, and this string cannot be calculated in any table function.
//it is added to the linked table as the last element in get_all_fks function which calls the add_f function.


//table functions:
void free_table(T_F_NODE **pp_head);
//free all elements of *pp_head, the rusult of *phead=NULL

int add_f(T_F_NODE **pp_head, const T_CARDS cards, char fk_class, char fk_base);
//add cards to the table whose head pointer is *pp_head 
//the table would be sorted by the number of cards: 
//  the node of max number cards is in the very beginning of the table
//  the node of min number cards is the last member in the table 
//  if the cards numbers of 2 nodes are equal, the node that is produced later is in the front.
//if cards is already in *pp_head, the cards would not be added and the return value is 0; otherwise return 1
//in temp functions fk_class and fk_base could be filled with non-meaning values
//but in the get_fks function, those 2 fields must be filled with actual values  

void link_tables(T_F_NODE **pp_head1, T_F_NODE *p_head2);
//add all elements of pp_head2 to pp_head1
//after called this function, the pp_head1 is changed to:
//*p_head1 is in the front, *p_head2 is in the back of the table

/*void multiple_tables(T_F_NODE **pp_head, 
					 const T_F_NODE *p_head1, 
					 const T_F_NODE *p_head2);
*/
//generates a fk table, each elements of which is consist of 2 carsd:
//one is from any element of p_head1, and the other is from any one of p_head2
//new element is add to the front of *pp_head
//if any one of p_head1 and p_head2 is null, *pp_head would be unchanged

void del_dup(T_F_NODE **pp_head);
//delete duplicate elemants in *pp_head

int in_table(const T_F_NODE *p_head, const T_CARDS cards);
//judge if the cards is already in the table p_head. If so, the function returns 1, otherwise returns 0.

void split_1234(T_F_NODE **pp_head, int n, const T_CARDS cards);
//generates a table of fks, each of which consists of n cards. Every card in n cards is all equal and each element in the table is different.

void get_n_cards(T_F_NODE **pp_head, const T_CARDS cards, int n);
//return a table of n cards from para cards, each element of the table is different 

void print_table(const T_F_NODE *p_head,char *str);
//print all elements of p_head

//below functions are used for producing fks
void get_all_fks(T_F_NODE **pp_head, const T_CARDS cards);
//get all fks, stored in *pp_head

void get_fks(T_F_NODE **pp_head, const T_CARDS cards, const char fk_class);
//get fks of some class, this is a big function using a big case statement
//some complex class of fks are defined as a standalone function

void get_3_1_fks(T_F_NODE **pp_head, const T_CARDS cards);
//get a triple with a single
void get_3_2_fks(T_F_NODE **pp_head, const T_CARDS cards);
//get a triple with a pair
void get_4_2_fks(T_F_NODE **pp_head, const T_CARDS cards);
//get a quad with 2 singles

int get_card_index_in_shunzi(const T_A_CARD card);
//return a_card's index in string of shunzi, -1 if not in
//used in get_shunzi, get_pairs, get_feiji

//void get_adjacent(T_F_NODE **pp_head,const T_CARDS cards,int number);
//get adjacent cards which have a number of para number
//this function would be used in below 3 functions 

void get_shunzi(T_F_NODE **pp_head, const T_CARDS cards);
//class F, shunzi
void get_adjacent_pairs(T_F_NODE **pp_head, const T_CARDS cards);
//class G, pair cards which are linking
void get_feiji(T_F_NODE **pp_head, const T_CARDS cards, const char fk_class);
//class H,I,J
#endif














