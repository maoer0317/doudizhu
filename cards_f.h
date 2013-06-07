#include "cards.h"

typedef struct f_node
{
  T_CARDS fk_cards;
  struct f_node *next;
}T_F_NODE;

//table functions:
void free_table(T_F_NODE **p_head);
//free all elements of *p_head, the rusult of *phead=NULL

int add_node(T_F_NODE **p_head, const T_CARDS cards);
//add cards to *p_head at the front of the table whose first element is p_head

void link_tables(T_F_NODE **p_head1, const T_F_NODE *p_head2);
//add all elements of p_head2 to p_head1
//after called this function, the p_head1 is changed to:
//all origin elements of *p_head2, after that are all the origin elements of *p_head1

void multiple_tables(T_F_NODE **p_head, 
					 const T_F_NODE *p_head1, 
					 const T_F_NODE *p_head2);
//generates a fk table, each elements of which is consist of 2 carsd:
//one is from any element of p_head1, and the other is from any one of p_head2

void del_dup(T_F_NODE **p_head);
//delete duplicate elemants in *p_head

int in_table(const T_F_NODE *p_head, const T_CARDS cards);
//judge if the cards is already in the table p_head. If so, the function returns 1, otherwise returns 0.

void get_n_cards(T_F_NODE **p_head, const T_CARDS cards, int n);
//return a table of n cards from para cards, each element of the table is different 

void print_table(T_F_NODE *p_head);
//print all elements of p_head

//below functions are used for producing fks
void split_1234(T_F_NODE **p_head, int n, const T_CARDS cards);
//generates a table of fks, each of which consists of n cards. Every card in n cards is all equal and each element in the table is different.

void get_fks(T_F_NODE **p_head, const T_CARDS cards, const char fk_class);
//get fks of some class, this is a big function using a big case statement
//some complex class of fks are defined as a standalone function

void get_shunzi(T_F_NODE **p_head, const T_CARDS cards);
//class F, shunzi
void get_pairs(T_F_NODE **p_head, const T_CARDS cards);
//class G, pair cards which are linking
void get_feiji(T_F_NODE **p_head, const T_CARDS cards, const char fk_class);
//class H,I,J

