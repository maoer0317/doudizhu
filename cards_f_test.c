#include <stdio.h>
#include <string.h>
#include "cards.h"
#include "cards_f.h"

int main(int argc, char *argv[])
{
  T_F_NODE *fks=NULL, *fks2=NULL,*fks3=NULL, 
	*fks4=NULL,*fks_shunzi=NULL,*fks_all=NULL;
  T_CARDS cards;

  strcpy(cards,"g2777");
  get_n_cards(&fks, cards,3);
  print_table (fks, cards);

  strcpy(cards,"Gg2222AAKQKQKJ078456");
  split_1234(&fks4, 3, cards);
  print_table(fks4,cards);

  strcpy(cards,"Gg2AKQJ087654");
  get_shunzi(&fks_shunzi,cards);
  print_table(fks_shunzi, cards);
  
  strcpy(cards,"KKQQJJ0008776655");
  get_adjacent_pairs(&fks_shunzi,cards);
  print_table(fks_shunzi,cards);

  free_table(&fks_all);
  //fks_all=NULL;
  strcpy(cards,"KKQQJJJJ000877665543");
  get_all_fks(&fks_all,cards);
  print_table(fks_all,cards);

  free_table(&fks);
  free_table(&fks2);
  free_table(&fks3);
  free_table(&fks4);
  free_table(&fks_all);
  //print_table(fks);

  return 0;
}
