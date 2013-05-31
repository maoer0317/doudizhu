#include<stdio.h>

int main(){
  FILE *fp;
  char s[5];
  int n;
  fp=fopen("txt.dat","r+");
  n=sprintf(s,"%d",10);
  printf("%s\n",s);
  fprintf(fp,"%d ",11);
  fclose(fp);
  return 0;
}
