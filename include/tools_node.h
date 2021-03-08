#ifndef _NODE_CONTAINER_H
#define _NODE_CONTAINER_H
#ifdef __cplusplus
extern "C"{
#endif
#include<stdlib.h>




#if defined(offsetof)
  #undef offsetof
  #define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#else 
  #define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif
#if defined(container_of)
  #undef container_of
  #define container_of(ptr, type, member) ({            \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})
#else
  #define container_of(ptr, type, member) ({            \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

typedef struct Node
{
    void* Prev;
    void* value;
    void*  Next;
    void* traits;

}Node;


static inline void Node_init(Node*node)
{

    node->Prev=NULL;
    node->Next=NULL;
    node->value=NULL;
    node->traits=NULL;
}
//void Node_init(Node*);
void free_node(Node*);
void free_node_value(Node*);
Node* node_find(Node*,void*);
Node* node_copy(Node*);
int node_size(Node*);
Node* node_overlying(Node*,void*);
Node* node_reverse(Node*);
Node* node_pushback(Node*,void*);
//remove node from list
void node_eliminate(Node*);
//given a value,find the node and remove it from list
Node *node_delete_value(Node*,void*);
Node* node_splicing(Node*n1,Node*n2);

Node* node_union(Node*n1,Node*n2);

Node* node_intersection(Node* n1,Node* n2);

Node* node_minus(Node* n1,Node* n2);
Node* node_bub_sort(Node* n,int (*cmp)(void* a,void* b));
/***    由大到小排列**/
Node* node_bub_sortn(Node* n,int (*cmp)(void* a,void* b));
Node* node_filter_condition(Node* n,int (*filter_condition)(void* a));
#ifdef __cplusplus
}
#endif
#endif
