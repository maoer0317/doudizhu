#include <stdio.h>
#include <string.h>
#include "cards.h"

int sort_cards(T_CARDS cards)
{
  T_CARDS cs;
  int i=0,j,k,ret;
  T_A_CARD c1,c2;

  strcpy(cs,cards);
  
  cards[0]='\0';
  //find index of char in sorted para "cards"
  while((c1=*(cs+i++))){
	j=0;
	while((c2=*(cards+j))){
	  ret=cmp_2_card(c1,c2);
	  //if the char in cs is illegal, skip this char
	  if(ret==-10)
		continue;
	  //if the char in cs is less than the one in cards,
	  //move to next char of cards
	  if(ret==-1)
		++j;
	  else
		break;
	}
	//cards:  ############\0
	//           j
	//result: ###j#########\0
	for(k=strlen(cards);k>=j;k--)
	  *(cards+k+1)=*(cards+k);
	*(cards+j)=c1;
  }	
  return 1;
}
  
int in_cards(const T_CARDS cards, const T_CARDS cards_small)
{
  T_CARDS cs;
  
  strcpy(cs,cards);
  return(del_cards(cs,cards_small));
}

int del_cards(T_CARDS cards, const T_CARDS cards_small)
{
  T_A_CARD c;
  T_CARDS cs;
  int i=0;

  strcpy(cs,cards);
  while((c=*(cards_small+i++))){
	if(!del_card(cs,c))
	  return 0;
  }
  strcpy(cards,cs);
  return 1;
}

int cmp_2_card(const T_A_CARD c1, const T_A_CARD c2)
{
  int i1,i2;

  i1=get_card_index_in_order(c1);
  i2=get_card_index_in_order(c2);

  if(i1==-1 || i2==-1)
	return -10;
  if(i1==i2)
	return 0;
  if(i1>i2) 
	return -1;
  else
	return 1;
}

int get_card_index_in_order(const T_A_CARD card)
{
  const T_CARDS cards_sort="Gg2AKQJ09876543";
  T_A_CARD a_card;
  int index=0;

  while((a_card=*(cards_sort+index))){
	if(a_card==card)
	  return index;
	else
	  ++index;
  }
  return -1;
}

int del_card(T_CARDS cards, const T_A_CARD a_card)
{
  int i=0;
  T_A_CARD c;

  while((c=*(cards+i)) && c!=a_card){
	++i;
  }
  
  if(!c)
	return 0;
  while(*(cards+i)){
	*(cards+i)=*(cards+i+1);
	i++;
  }
  *(cards+i)='\0';
  return 1;
}

