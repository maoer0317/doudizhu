#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards_f.h"

const T_CARDS CARDS_SHUNZI="AKQJ09876543";

//table functions:
void free_table(T_F_NODE **pp_head)
{
  T_F_NODE *p=*pp_head;

  while(*pp_head){
	p=(*pp_head)->next;
	free(*pp_head);
	*pp_head=p;
  }
}

int add_f(T_F_NODE **pp_head, const T_CARDS cards, char fk_class, char fk_base)
//this function must deal with the situation the parameter cards is ""
{
  T_F_NODE *p_new,*p_current=*pp_head,*p_head=*pp_head;
  int n=strlen(cards);

  //here use the most compact but not easy to understand way to move pointer
  //see "Pointers on C", Chinese version Page 244
  while((p_current=*pp_head) && n<strlen(p_current->fk_cards))
	pp_head=&p_current->next;

  if(!in_table(p_head, cards)){
	p_new=(T_F_NODE *)malloc(sizeof(T_F_NODE));
	strcpy(p_new->fk_cards,cards);
	p_new->next=p_current;
	p_new->fk_class=fk_class;
	p_new->fk_base=fk_base;
	*pp_head=p_new;
	return 1;
  }else
	return 0;
}

void link_tables(T_F_NODE **pp_head1, T_F_NODE *p_head2)
{
  T_F_NODE *p=*pp_head1;

  if(*pp_head1==NULL) 
	*pp_head1=p_head2;
  else{
	while(p->next!=NULL)
	  p=p->next;
	p->next=p_head2;
  }
}

/*
void multiple_tables(T_F_NODE **pp_head, 
					 const T_F_NODE *p_head1, 
					 const T_F_NODE *p_head2)
{
  T_CARDS new_cards;
  const T_F_NODE *p;
  
  if(p_head1==NULL || p_head2==NULL)
	return;
  while(p_head1){
	p=p_head2;
	while(p){
	  strcpy(new_cards,p_head1->fk_cards);
	  strcat(new_cards,p->fk_cards);
	  sort_cards(new_cards);
	  add_f(pp_head, new_cards);
	  p=p->next;
	}
	p_head1=p_head1->next;
  }
}
*/

void del_dup(T_F_NODE **pp_head)
//used in function get_n_cards
{
  T_F_NODE *p_previuous,*p_current,*p_node=*pp_head;
  int n;
  
  while(p_node!=NULL){
	//get a node from table
	p_current=*pp_head;
	p_previuous=p_current;
	n=0;
	while(p_current!=NULL){
	  if(strcmp(p_current->fk_cards,p_node->fk_cards)==0){
		//the first equal of 2 node is one node actually, do nothing 
		++n;
		if(n>1){
		  //if find 2 fks_cards is duplicated
		  p_previuous->next=p_current->next;
		  free(p_current);
		  p_current=p_previuous->next;
		}else{//if(n>1)
		  p_previuous=p_current;
		  p_current=p_current->next;
		}
	  }else{//not equal
		p_previuous=p_current;
		p_current=p_current->next;
	  }//if
	}//while

	p_node=p_node->next;
  }//while
}

int in_table(const T_F_NODE *p_head, const T_CARDS cards)
{
  while(p_head!=NULL){
	if(strcmp(p_head->fk_cards,cards)==0)
	  return 1;
	p_head=p_head->next;
  }	  
  return 0;
}

void get_n_cards(T_F_NODE **pp_head, const T_CARDS cards, int n)
//this function must recursively run:
// if cards' length<n, return with pp_head unchanged; 
//                 =n, return with a table in which there is only one element, the whole cards;
// above is 2 particular situation. below is the recurse
// n =1, return with a table that is split to one card element each 
// n >1, 
//     1)split the cards into a table of one card, each element in the table is different 
//     2)for each different card(named c), call get_n_cards(p_head, cards - c, n-1);
//     3)catenate c and all the cards in return table; 
{
  T_F_NODE *pn=NULL,*pn_1=NULL,*p1=NULL,*p_cat;
  int cards_num;
  T_CARDS cs, cs1;

  strcpy(cs,cards);
  cards_num=strlen(cs);
  if(cards_num<n)
	return;
  if(cards_num==n){
	add_f(&pn,cards,'z','z');
	*pp_head=pn;
	return;
  }

  if(n==1){
	split_1234(&pn,1,cs);
  }else{
	split_1234(&p1,1,cs);
	while(p1!=NULL){
	  strcpy(cs1,cards); 
	  del_cards(cs1,p1->fk_cards);
	  get_n_cards(&pn_1,cs1,n-1);
	  //catenate
	  p_cat=pn_1;
	  while(p_cat!=NULL){
		strcat(p_cat->fk_cards,p1->fk_cards);
		sort_cards(p_cat->fk_cards);
		p_cat=p_cat->next;
	  }
	  link_tables(&pn,pn_1);
	  del_dup(&pn);
	  
	  p1=p1->next;
	}//while
  }//else
  *pp_head=pn;
}

void print_table(const T_F_NODE *p_head,char *str)
{
  const T_F_NODE *fks=p_head;
  T_CARDS cs;

  printf ("The fks of \"%s\" are:\n",str);
  while(fks){
	strcpy(cs,fks->fk_cards);
	//printf("%s ",cs);
	if(strlen(cs)!=0)
	  printf ("(%s,%c,%c)  ",cs,fks->fk_class, fks->fk_base);
	else
	  printf ("(%s,%c,%c)  ","NoCard",fks->fk_class, fks->fk_base);
	fks=fks->next;
  }
  printf("\n\n");
}

//below functions are used for producing fks
void get_all_fks(T_F_NODE **pp_head, const T_CARDS cards)
//at the end of this function, call add_f(**pp_head,"")
{
  char ch;
  for(ch='A';ch<='N';ch++)
	get_fks(pp_head,cards,ch);
}

void split_1234(T_F_NODE **pp_head, int n, const T_CARDS cards)
{
  T_CARDS cs,cs_split;
  int i,j,all_equal;
  char fk_class,fk_base;

  strcpy(cs,cards);
  sort_cards(cs);
  if(n==4)
	fk_class='M';
  else
	fk_class='A'+n-1;
  for(i=0;i<strlen(cs)-n+1;i++){
	strncpy(cs_split,cs+i,n);
	*(cs_split+n)='\0';
	all_equal=1;
	for(j=0;j<n-1;j++){
	  if(*cs_split!=*(cs_split+j+1)){ 
		all_equal=0;
		break;
	  }//if
	}//for j
	if(all_equal){
	  fk_base=*cs_split;
	  add_f(pp_head,cs_split,fk_class,fk_base);
	}
  }//for i
}

void get_fks(T_F_NODE **pp_head, const T_CARDS cards, const char fk_class)
{
  //a huge switch, each of which represents a fk_class
  switch(fk_class){
  case 'A':
	split_1234(pp_head,1,cards);	break;
  case 'B':
	split_1234(pp_head,2,cards);	break;
  case 'C':
	split_1234(pp_head,3,cards); break;
  case 'D':
	get_3_1_fks(pp_head,cards);	break;
  case 'E':
	//not used in the problem
	//get_3_2_fks(&p,cards);
	break;
  case 'F':
	get_shunzi(pp_head,cards); break;
  case 'G':
	get_adjacent_pairs(pp_head,cards); break;
  case 'H':
	get_feiji(pp_head,cards,'H'); break;
  case 'I':
	get_feiji(pp_head,cards,'I');  break;
  case 'J':
	//not used in the problem
	break;
  case 'K':
	get_4_2_fks(pp_head,cards); break;
  case 'L':
	//not used in the problem
	break;
  case 'M':
	split_1234(pp_head,4,cards);  break;
  case 'N':
	if(in_cards(cards,"Gg"))
	  add_f(pp_head,"Gg",'N','G');
  }//switch
}

void get_3_1_fks(T_F_NODE **pp_head, const T_CARDS cards)
{
  T_F_NODE *p_triple=NULL,*p_single=NULL,*p1,*p2;
  T_CARDS cs_left,cs_cat;
  char fk_base;

  split_1234(&p_triple,3,cards);
  p1=p_triple;
  while(p1!=NULL){
	strcpy(cs_left,cards);
	del_cards(cs_left,p1->fk_cards);
	fk_base=*(p1->fk_cards);
	split_1234(&p_single,1,cs_left);
	p2=p_single;
	while(p2!=NULL){
	  if(*(p2->fk_cards)!=*(p1->fk_cards)){
		//if equals, there is a M class--bomb
		strcpy(cs_cat, p1->fk_cards);
		strcat(cs_cat, p2->fk_cards);
		sort_cards(cs_cat);
		add_f(pp_head,cs_cat,'D',fk_base);
	  }//if 
	  p2=p2->next;
	}//while p2
	p1=p1->next;
  }//while p1
  free_table(&p_triple);
  free_table(&p_single);
}

void get_3_2_fks(T_F_NODE **pp_head, const T_CARDS cards)
{
  T_F_NODE *p_triple=NULL,*p_pair=NULL,*p1,*p2;
  T_CARDS cs_left,cs_cat;
  char fk_base;

  split_1234(&p_triple,3,cards);
  p1=p_triple;
  while(p1!=NULL){
	strcpy(cs_left,cards);
	del_cards(cs_left,p1->fk_cards);

	fk_base=*(p1->fk_cards);
	split_1234(&p_pair,2,cs_left);
	p2=p_pair;
	while(p2!=NULL){
	  strcpy(cs_cat, p1->fk_cards);
	  strcat(cs_cat, p2->fk_cards);
	  sort_cards(cs_cat);
	  add_f(pp_head,cs_cat,'E',fk_base);
	  
	  p2=p2->next;
	}//while p2
	p1=p1->next;
  }//while p1
  free_table(&p_triple);
  free_table(&p_pair);
}

void get_4_2_fks(T_F_NODE **pp_head, const T_CARDS cards)
{
  T_F_NODE *p_quad=NULL,*p_2_singles=NULL,*p1,*p2;
  T_CARDS cs_left,cs_cat;
  char fk_base;

  split_1234(&p_quad,4,cards);
  strcpy(cs_left,cards);
  p1=p_quad;
  while(p1!=NULL){
	del_cards(cs_left,p1->fk_cards);
	fk_base=*(p1->fk_cards);
	get_n_cards(&p_2_singles,cs_left,2);
	p2=p_2_singles;
	while(p2!=NULL){
	  strcpy(cs_cat, p1->fk_cards);
	  strcat(cs_cat, p2->fk_cards);
	  sort_cards(cs_cat);
	  add_f(pp_head,cs_cat,'K',fk_base);
	  
	  p2=p2->next;
	}//while p2
	p1=p1->next;
  }//while p1
  free_table(&p_quad);
  free_table(&p_2_singles);
}

//void get_adjacent(T_F_NODE **pp_head,const T_CARDS cards,int number)

int get_card_index_in_shunzi(const T_A_CARD card)
{
  T_A_CARD a_card;
  int index=0;

  while((a_card=*(CARDS_SHUNZI+index))){
	if(a_card==card)
	  return index;
	else
	  ++index;
  }
  return -1;  
}

void get_shunzi(T_F_NODE **pp_head, const T_CARDS cards)
//class F, shunzi
{
  int n,pos[12],i,ret,a_shunzi,j,k;
  T_F_NODE *p_1=NULL,*p;
  T_CARDS cs;
  T_A_CARD ch;
  char fk_base;
  
  for(i=0;i<12;i++)
	pos[i]=0;
  split_1234(&p_1,1,cards);
  p=p_1;
  while(p!=NULL){
	ch=*(p->fk_cards);
	if((ret=get_card_index_in_shunzi(ch))!=-1)
	  pos[ret]=1;
	p=p->next;
  }

  n=0;  
  a_shunzi=0;
  for(i=0;i<12;i++){
	if(pos[i]==0 || i==11){
	  if(a_shunzi){
		//if get a shunzi, add all sub-shunzi to pp_head
		//the length of sub-shunzi begins at 5, up to n
		for(j=5;j<=n;j++){
		  //pos: 00111 11111 00
		  //                 i=10 n=8
		  //sub-shunzi's first place is: i-n and  last place is: n-j
		  for(k=0;k<n-j+1;k++){
			strncpy(cs,CARDS_SHUNZI+i-n+k,j);
			fk_base=*(cs+j-1);
			*(cs+j)='\0';
			add_f(pp_head,cs,'F',fk_base);
		  }//for k
		}//for j
		a_shunzi=0;
	  }//if shunzi
	  n=0; 
	}else{
	  ++n;
	  if(n>=5)
		a_shunzi=1;
	}
  }//for i
  free_table(&p_1);
}

void get_adjacent_pairs(T_F_NODE **pp_head, const T_CARDS cards)
//class G, pair cards which are linking
{
  int n,pos[12],i,ret,a_pairs,j,k;
  T_F_NODE *p_2=NULL,*p;
  T_CARDS cs,cs_pairs;
  T_A_CARD ch;
  char fk_base;

  for(i=0;i<12;i++)
	pos[i]=0;
  split_1234(&p_2,2,cards);
  p=p_2;
  while(p!=NULL){
	ch=*(p->fk_cards);
	if((ret=get_card_index_in_shunzi(ch))!=-1)
	  pos[ret]=1;
	p=p->next;
  }

  n=0;  
  a_pairs=0;
  for(i=0;i<12;i++){
	if(pos[i]==0 || i==11){
	  if(a_pairs){
		//if get a pairs, add all sub-pairs to pp_head
		//the length of sub-pairs begins at 3, up to n(actually n<=10)
		for(j=3;j<=n;j++){
		  //sub-pair's first place is: i-n and  last place is: n-j
		  for(k=0;k<n-j+1;k++){
			strncpy(cs,CARDS_SHUNZI+i-n+k,j);
			*(cs+j)='\0';
			fk_base=*(cs+j-1);
			strcpy(cs_pairs,cs);
			strcat(cs_pairs,cs);
			sort_cards(cs_pairs);
			add_f(pp_head,cs_pairs,'G',fk_base);
		  }//for k
		}//for j
		a_pairs=0;
	  }//if adjacent pairs
	  n=0; 
	}else{
	  ++n;
	  if(n>=3)
		a_pairs=1;
	}
  }//for i
  free_table(&p_2);
}

void get_feiji(T_F_NODE **pp_head, const T_CARDS cards, const char fk_class)
//class H,I,J
//Methods:
//1. get all triples
//2. if there are some triples are adjacent;
//3. get any n cards from the left cards(cards-all triples that are adjacent)
//4. catenate triples and the n cards
//5. add to table
{
  int n,pos[12],i,ret,a_triple,j,k;
  T_F_NODE *p_3=NULL,*p;
  T_CARDS cs,cs_triples;
  T_A_CARD ch;
  char fk_base;

  for(i=0;i<12;i++)
	pos[i]=0;
  split_1234(&p_3,3,cards);
  p=p_3;
  while(p!=NULL){
	ch=*(p->fk_cards);
	if((ret=get_card_index_in_shunzi(ch))!=-1)
	  pos[ret]=1;
	p=p->next;
  }

  n=0;  
  a_triple=0;
  for(i=0;i<12;i++){
	if(pos[i]==0 || i==11){
	  if(a_triple){
		//if get a triple, add all sub-triples to pp_head
		//the length of sub-triples begins at 2, up to n(actually n<=6)
		for(j=2;j<=n;j++){
		  //sub-triple's first place is: i-n and  last place is: n-j
		  for(k=0;k<n-j+1;k++){
			strncpy(cs,CARDS_SHUNZI+i-n+k,j);
			*(cs+j)='\0';
			fk_base=*(cs+j-1);
			strcpy(cs_triples,cs);
			strcat(cs_triples,cs);
			strcat(cs_triples,cs);
			sort_cards(cs_triples);
			if(fk_class=='H')   //feiji without wings
			  add_f(pp_head,cs_triples,fk_class,fk_base);
			else
			  if(fk_class=='I'){   //feiji with a single card each
				T_F_NODE *card_any_n=NULL;
				T_CARDS cs_left;
				strcpy(cs_left,cards);
				del_cards(cs_left,cs_triples);
				get_n_cards(&card_any_n,cs_left,n);
				p=card_any_n;
				while(p!=NULL){
				  T_CARDS triples_singles;
				  strcpy(triples_singles,cs_triples);
				  strcat(triples_singles, p->fk_cards);
				  sort_cards(triples_singles);
				  add_f(pp_head,triples_singles,fk_class,fk_base);
				  p=p->next;
				}//while
				free_table(&card_any_n);
			  }//if "I"
			  else
				if(fk_class=='J'){}//not used in the problem
		  }//for k
		}//for j
		a_triple=0;
	  }//if is a triple
	  n=0; 
	}//pos[i]==1
	else{
	  ++n;
	  if(n>=2)
		a_triple=1;
	}//else
  }//for i
  free_table(&p_3);  
}

