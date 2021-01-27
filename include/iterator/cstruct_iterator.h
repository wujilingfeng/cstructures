#ifndef CSTRUCT_ITERATOR_H
#define CSTRUCT_ITERATOR_H
#include "../tools_node.h"
#include "../tools_rbtree.h"
bool operator==(const Node&,const Node&);
bool operator!=(const Node&,const Node&);

Node operator++(Node&);
Node operator++(Node&,int);
Node operator--(Node&);
Node operator--(Node&,int);
void* operator*(Node&);

bool operator==(const RB_Trav&,const RB_Trav&);
bool operator!=(const RB_Trav&,const RB_Trav&);
RB_Trav operator++(RB_Trav&);
RB_Trav operator++(RB_Trav&,int);
RB_Trav operator--(RB_Trav&);
RB_Trav operator--(RB_Trav&,int);
void* operator*(RB_Trav&);

#endif

