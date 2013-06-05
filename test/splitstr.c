#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct splited_str sp_table;

struct splited_str{
  char str_one[20];
  struct splited_str *next;
};

sp_table *SP_STR;

int find_str(const char *s)
{
  sp_table *ss=SP_STR;
  while(ss!=NULL){
    if (strcmp(ss->str_one,s)==0)
      return 1;
    ss=ss->next;
  }

  return 0;
}

void add_to_str(char *s)
{
  sp_table *snew;
    //add to SP_STR
  snew=(sp_table*)malloc(sizeof(sp_table));
  snew->next=SP_STR;
  strcpy(snew->str_one,s);
  SP_STR=snew;
}

void add_sp(sp_table *ss)
{
  sp_table *sp=ss;
  while(sp!=NULL)
	sp=sp->next;
  sp=SP_STR;
  SP_STR=ss;  
}

int is_pair(const char *s)
//class B
//judge if the string is a pair 
{
  char c1,c2;
  if(strlen(s)!=2)
    return 0;
  
  c1=*s;
  c2=*(s+1);
  //printf("%c,%c\n",c1,c2);
  if(c1!=c2)
    return 0;
  else 
    return 1;  
}

int is_triple(const char *s)
{
  //char c1,c2,c3;
  if(strlen(s)!=3)
	return 0;
  //printf ("%d\n",*s==*(s+1) && (*s==*(s+2)));
  if((*s==*(s+1)) && (*s==*(s+2)))
	 return 1;
  else 
	return 0;
}

int in_table(const char *s,  sp_table *sp)
{
  sp_table *ss=sp;
  while(ss!=NULL){
	if(strcmp(s,ss->str_one)==0)
	  return 1;
	ss=ss->next;
  }
  return 0;
}

void split_1234(const char *s, int n,sp_table **sp)
{
  //split to 1, class A
  char s1[20];
  sp_table *snew;
  int i;

  for(i=0;i<strlen(s)-n+1;i++){
    strncpy(s1,s+i,n);
    *(s1+n)='\0';
    if(!in_table(s1,*sp)){
	  snew=(sp_table *)malloc(sizeof(sp_table));
	  snew->next=*sp;
	  strcpy(snew->str_one,s1);
	  *sp=snew;
	}
	  
    //printf("%s\n",s1);
  }
}


void print_sp(sp_table *sp)
{
  sp_table *ss=sp;
  printf ("%s\n","temp str table:");
  while(ss!=NULL){
	printf("%s\n",ss->str_one);
	ss=ss->next;
  }
}

void str_split(const char *s)
{
  char s1[20];
  int i;
  sp_table *sp=NULL;
  
  split_1234(s,1,&sp);
  if(sp==NULL)
	printf ("%s\n","sp==NULL");
  print_sp(sp);
  add_sp(sp);
  
  //split to pairs, class B
  /*for(i=0;i<strlen(s)-1;i++){
    strncpy(s1,s+i,2);
    *(s1+2)='\0';
    //printf("%s,%d\n",s1,i);
    if(is_pair(s1) && !find_str(s1))
       add_to_str(s1);
  }

  //split to triple, class C
  for(i=0;i<strlen(s)-2;i++){
    strncpy(s1,s+i,3);
    *(s1+3)='\0';
    //printf("%s,%d\n",s1,i);
    if(is_triple(s1) && !find_str(s1))
       add_to_str(s1);
  }
  */
  //split to triple+one, class D
  

  printf("\n");
}

void print_split_str()
{
  struct splited_str *ss;
  ss=SP_STR;
  printf("%s\n","Below are the strings in str_table");
  while(ss!=NULL){
    printf("%s\n",ss->str_one);
    ss=ss->next;
  }
}

int main()
{
  char *s="Gg22AAAA876543";
  str_split(s);
  print_split_str();
  return 0;
}

