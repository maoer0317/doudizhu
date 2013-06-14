#ifndef AND_OR_TREE_H
#define AND_OR_TREE_H

#include "cards.h"
#include "cards_f.h"

typedef enum{
  DiZhu, NonMing
}T_XIANSHOU;

typedef enum{
  Must_Go,May_Not_Go
}T_MUSTGO;

typedef enum{
  NODE_AND, NODE_OR
}T_ANDOR;

typedef enum{
  SOLVED, NON_SOLVED, NOT_MARK
}T_YN;

typedef struct node_state{
  T_CARDS cs_dizhu;
  T_CARDS cs_nongmin;
  T_XIANSHOU xianshou; 
  T_MUSTGO m_go;
}T_NODE_STATE;

typedef struct tree_node{
  int n_no;
  int n_father;
  T_NODE_STATE sj;
  T_F_NODE fk;
  T_ANDOR and_or;
  T_YN node_mark;
  //int hj;   //not used
  int pj;   //not used;
  char node_note[32];  
  struct tree_node *next;
}T_TREE_NODE;

#endif
