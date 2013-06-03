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

int is_pair(char *s)
{
  char c1,c2;
  if(strlen(s)!=2)
    return 0;
  
  c1=*s;
  c2=*(s+1);
  printf("%c,%c\n",c1,c2);
  if(c1!=c2)
    return 0;
  else 
    return 1;  
}

void str_split(const char *s)
{
  char s1[20];
  int i;
  //split to 1
  for(i=0;i<strlen(s);i++){
    strncpy(s1,s+i,1);
    *(s1+1)='\0';
    if (!find_str(s1))
      add_to_str(s1);
    //printf("%s\n",s1);
  }
  //split to 2
  for(i=0;i<strlen(s)-1;i++){
    strncpy(s1,s+i,2);
    *(s1+2)='\0';
    //printf("%s,%d\n",s1,i);
    if(is_pair(s1) && !find_str(s1))
       add_to_str(s1);
  }
  printf("\n");
}

void print_split_str()
{
  struct splited_str *ss;
  ss=SP_STR;
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
