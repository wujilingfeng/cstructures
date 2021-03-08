#ifndef CSTRUCT_ITERATOR_H
#define CSTRUCT_ITERATOR_H
#include "../tools_node.h"
#include "../tools_rbtree.h"
#include "../tools_avltree.h"
bool operator==(const Node&,const Node&);
bool operator!=(const Node&,const Node&);

Node operator++(Node&);
Node operator++(Node&,int);
Node operator--(Node&);
Node operator--(Node&,int);
void* operator*(Node&);

bool operator==(const RB_Tree_Trav&,const RB_Tree_Trav&);
bool operator!=(const RB_Tree_Trav&,const RB_Tree_Trav&);
RB_Tree_Trav operator++(RB_Tree_Trav&);
RB_Tree_Trav operator++(RB_Tree_Trav&,int);
RB_Tree_Trav operator--(RB_Tree_Trav&);
RB_Tree_Trav operator--(RB_Tree_Trav&,int);
void* operator*(RB_Tree_Trav&);



AVL_Tree_Trav operator++(AVL_Tree_Trav&it);
AVL_Tree_Trav operator++(AVL_Tree_Trav&it,int);
AVL_Tree_Trav operator--(AVL_Tree_Trav&it);

AVL_Tree_Trav operator--(AVL_Tree_Trav&it,int);
void* operator*(AVL_Tree_Trav&it);







#endif

