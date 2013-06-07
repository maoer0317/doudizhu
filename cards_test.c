#include <stdio.h>
#include "cards.h"

int main(int argc, char *argv[])
{
  T_CARDS cards="gG235KJ890A4446Q",new_cards="444g209";
  int ret;

  sort_cards(cards);
  printf("%s\n",cards);
  ret=del_card(cards, 'A');
  printf("%s,%d\n",cards,ret);
  printf ("%d\n",in_cards(cards,new_cards));
  del_cards(cards,new_cards);
  printf ("%s\n",cards);
  return 0;
}
