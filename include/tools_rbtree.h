#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#ifdef __cplusplus
extern "C"{
#endif

#define RED        0    
#define BLACK    1   
typedef struct RB_Node{
    unsigned char color;        
    struct RB_Node *left;    
    struct RB_Node *right;    
    struct RB_Node *parent;    
    void* data;
    void *prop;
}RB_Node;


static inline void lb_default_free(void *p)
{
    free(p);
}
//static inline void RB_Node_init(RB_Node*);

typedef struct RB_Tree{
    RB_Node *root;
    int (*cmp)(const void* p1,const void* p2);  
    //copy the data member of RB_Node

  void* (*copy)(void*); 
  //free the data memeber of RB_Node
  void  (*del)(void*);  
  unsigned int  size; 
	void *(*find)(struct RB_Tree*,void*);
	void* (*insert)(struct RB_Tree*,void*);
	int (*erase)(struct RB_Tree*,void*);
	struct RB_Trav* (*begin)(struct RB_Tree*);
	struct RB_Trav*(*rbegin)(struct RB_Tree*);
	void (*iterator_init)(struct RB_Trav*);
	
    void* prop;
}RB_Tree;

//void RB_Tree_init(RB_Tree*);


typedef struct RB_Trav{
	RB_Tree*tree;
	RB_Node* it;
	void*(*next)(struct RB_Trav*);
	void*(*prev)(struct RB_Trav*);
	void*(*first)(struct RB_Trav*);
	void*(*second)(struct RB_Trav*);
	void*prop;

}RB_Trav;

void RB_Tree_free(RB_Tree*tree);

void* RB_insert(RB_Tree *, void *data);
RB_Trav* RB_begin(RB_Tree*tree);
RB_Trav* RB_rbegin(RB_Tree*tree);
void* RB_next(RB_Trav*it);
void* RB_prev(RB_Trav*it);

//RB_Node* rbtree_minimum(RB_Tree *);
//RB_Node* rbtree_maximum(RB_Tree *);
//RB_Node* rbtree_successor(RB_Node *x);
//RB_Node* rbtree_predecessor(RB_Node *x);

RB_Node* RB_find1(RB_Tree* tree,void*data);
void* RB_find(RB_Tree *tree, void*data);
int RB_erase(RB_Tree*,void*);
static inline void RB_Node_init(RB_Node*node)
{
    node->color=RED;
    node->parent=NULL;
    node->left=NULL;
    node->right=NULL;

    node->data=NULL;
    node->prop=NULL;
}
static inline void RB_Tree_init(RB_Tree* tree)
{
    tree->root=NULL;
    tree->cmp=NULL;
    tree->copy=NULL;
    tree->del=lb_default_free;
    tree->size=0;
    tree->find=RB_find;
    tree->insert=RB_insert;
    tree->erase=RB_erase;
    tree->begin=RB_begin;
    tree->rbegin=RB_rbegin;
    tree->iterator_init=NULL;
    tree->prop=NULL;
}
static inline void RB_Trav_init(RB_Trav* it)
{
    it->tree=NULL;
    it->next=RB_next;
    it->prev=RB_prev;
    it->it=NULL;
    it->prop=NULL;
}

#define RB_Tree_func_declare(typevalue) typedef struct RB_##typevalue{typevalue key;void* value;void* prop;}RB_##typevalue;\
static void RB_init_##typevalue(RB_##typevalue* t)\
{\
t->value=NULL;\
t->prop=NULL;\
}\
int RB_cmp_##typevalue(const void*p1,const void*p2);\
void RB_Tree_init_##typevalue(RB_Tree*);


#define RB_Tree_func(typevalue)  int RB_cmp_##typevalue(const void*p1,const void*p2)\
{\
RB_##typevalue *q1=(RB_##typevalue*)p1,*q2=(RB_##typevalue*)p2;\
    if(q1->key>q2->key)\
    {\
        return 1;\
    }\
    else if(q1->key<q2->key)\
    {\
        return -1;\
    }\
    return 0;\
}\
static  void* RB_copy_##typevalue(void* p)\
{\
	void* re=malloc(sizeof(RB_##typevalue));\
	memmove(re,p,sizeof(RB_##typevalue));\
	return re;\
}\
static  void * get_key_##typevalue(RB_Trav* trav)\
{\
	return (void*)(&(((RB_##typevalue*)(trav->it->data))->key));\
}\
static void* get_value_##typevalue(RB_Trav*trav)\
{\
	return ((RB_##typevalue*)(trav->it->data))->value;\
}\
static void iter_init_##typevalue(RB_Trav*trav)\
{\
	trav->first=get_key_##typevalue;\
	trav->second=get_value_##typevalue;\
}\
void RB_Tree_init_##typevalue(RB_Tree* tree)\
{\
	RB_Tree_init(tree);\
	tree->copy=RB_copy_##typevalue;\
	tree->cmp=RB_cmp_##typevalue;\
	tree->iterator_init=iter_init_##typevalue;\
}\


RB_Tree_func_declare(int)
RB_Tree_func_declare(double)

#undef RED
#undef BLACK
#ifdef __cplusplus
}
#endif

#endif
