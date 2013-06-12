#include <stdio.h>
#include "cards_f.h"

int main(int argc, char *argv[])
{
  T_F_NODE *fks=NULL, *fks2=NULL,*fks3=NULL, 
	*fks4=NULL,*fks_shunzi=NULL,*fks_all=NULL;
  /*add_f(&fks, "76543");
  add_f(&fks, "22");
  add_f(&fks, "AAA");
  //add_f(&fks, "888999000345");
  add_f(&fks, "K");
  add_f(&fks, "");*/
  print_table(fks);
  
  add_f(&fks2,"33");
  add_f(&fks2,"33");
  add_f(&fks2,"444");
  add_f(&fks2,"444");
  add_f(&fks2,"33");
  print_table(fks2);
  //del_dup(&fks2);
  print_table(fks2);

  link_tables(&fks,fks2);
  print_table(fks);

  //multiple_tables(&fks3,fks,fks2);
  //print_table(fks3);
  
  //free_table(&fks);
  get_n_cards(&fks4, "g2777",3);
  print_table (fks4);

  split_1234(&fks4, 3, "Gg2222AAKQKQKJ078456");
  print_table(fks4);

  
  get_shunzi(&fks_shunzi, "Gg2AKQJ087654");
  print_table(fks_shunzi);
  get_adjacent_pairs(&fks_shunzi,"KKQQJJ0008776655");
  print_table(fks_shunzi);
  
  get_all_fks(&fks_all,"Gg22AAAKKKQQJ08876543");
  print_table(fks_all);

  free_table(&fks);
  free_table(&fks2);
  free_table(&fks3);
  free_table(&fks4);
  free_table(&fks_all);
  //print_table(fks);

  return 0;
}
