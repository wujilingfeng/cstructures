#ifndef __INCLUDED_RBTREE_H__
#define __INCLUDED_RBTREE_H__



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <assert.h>
#include<stdio.h>
#include<string.h>

#if defined(__x86_64) && defined(_LP64)
#define _RB_USE_AUGMENTED_PTR
#endif



typedef struct RB_Tree_Node {
  
    struct RB_Tree_Node *left;

    
    struct RB_Tree_Node *right;

  
    struct RB_Tree_Node *parent;

  
    void* data;
    void *prop;

#ifndef _RB_USE_AUGMENTED_PTR 
  
    unsigned color;
#endif
} RB_Tree_Node;
static inline void rb_tree_node_init(RB_Tree_Node* node)
{
    node->left=NULL;
    node->right=NULL;
    node->parent=NULL;
    node->data=NULL;
    node->prop=NULL;
#ifndef _RB_USE_AUGMENTED_PTR
    node->color=0
#endif
}


typedef int (*rb_cmp_func_t)(const void *lhs, const void *rhs);



typedef struct RB_Tree {
    
    struct RB_Tree_Node *root;

    
    rb_cmp_func_t cmp;
    void * (*copy)(void*);
    void  (*del)(void*);

    void* (*find)(struct RB_Tree*,void*);
    void (*insert)(struct RB_Tree*,void*);
    void (*erase)(struct RB_Tree*,void*);

    struct RB_Tree_Trav*(*begin)(struct RB_Tree*);
    struct RB_Tree_Trav*(*rbegin)(struct RB_Tree*);

    void(*iterator_init)(struct RB_Tree_Trav*);  

    struct RB_Tree_Node *rightmost;

   
    unsigned int size;
    
    void* prop;
}RB_Tree;

typedef struct RB_Tree_Trav{
  RB_Tree* tree;
  RB_Tree_Node* it;
  void*(*next)(struct RB_Tree_Trav*);
  void*(*prev)(struct RB_Tree_Trav*);
  void*(*first)(struct RB_Tree_Trav*);
  void*(*second)(struct RB_Tree_Trav*); 
  void* prop;
}RB_Tree_Trav;

void * rb_tree_next(struct RB_Tree_Trav* trav);
void* rb_tree_prev(struct RB_Tree_Trav *trav);
static inline void rb_tree_trav_init(RB_Tree_Trav*it)
{
  it->tree=NULL;
  it->next=rb_tree_next;
  it->prev=rb_tree_prev;
  it->it=NULL;
  it->prop=NULL;
}



void rb_tree_free(struct RB_Tree *tree);


RB_Tree_Node* rb_tree_find(struct RB_Tree *tree,void *data);
void* rb_tree_findn(struct RB_Tree *tree,void *data);

void rb_tree_insert(struct RB_Tree *tree,void *data);


void rb_tree_delete_node(struct RB_Tree *tree,
                           struct RB_Tree_Node *node);

void rb_tree_delete_data(RB_Tree* tree,void* data);
/**
 * Find the minimum of the given tree/subtree rooted at the given node.
 */
RB_Tree_Node* __rb_tree_find_minimum(RB_Tree* tree);
/**
 * Find the maximum of the given tree/subtree rooted at the given node.
 */
RB_Tree_Node* __rb_tree_find_maximum(RB_Tree* tree);


RB_Tree_Node* rb_tree_successor(struct RB_Tree_Node *n);

RB_Tree_Node* rb_tree_predecessor(struct RB_Tree_Node *n);
/**@} rb_functions */
struct RB_Tree_Trav* rb_tree_begin(RB_Tree*);
struct RB_Tree_Trav* rb_tree_rbegin(RB_Tree*);
static inline void rb_tree_init(struct RB_Tree *tree)
{
#ifdef DEBUG
    RB_ASSERT_ARG(tree != NULL);
    RB_ASSERT_ARG(cmp != NULL);
#endif
    tree->root = NULL;
    tree->copy=NULL;
    tree->cmp = NULL;
    tree->del=NULL;
    tree->find=rb_tree_findn;
    tree->insert=rb_tree_insert;
    tree->erase=rb_tree_delete_data;
    tree->begin=rb_tree_begin;
    tree->rbegin=rb_tree_rbegin;
    tree->iterator_init=NULL;
    tree->rightmost = NULL;
    tree->size=0;
    tree->prop=NULL;

}





#define RB_Tree_func_declare(typevalue) typedef struct RB_##typevalue{typevalue key;void* value;void* prop;}RB_##typevalue;\
static inline void rb_init_##typevalue(RB_##typevalue* t)\
{\
t->value=NULL;\
t->prop=NULL;\
}\
int rb_cmp_##typevalue(const void*p1,const void*p2);\
void rb_tree_init_##typevalue(RB_Tree*);



#define RB_Tree_func(typevalue)  int rb_cmp_##typevalue(const void*p1,const void*p2)\
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
static  void* rb_copy_##typevalue(void* p)\
{\
    void* re=malloc(sizeof(RB_##typevalue));\
    memmove(re,p,sizeof(RB_##typevalue));\
    return re;\
}\
static void* get_key_##typevalue(RB_Tree_Trav*trav)\
{\
    return (void*)(&(((RB_##typevalue*)(trav->it->data))->key));\
}\
static  void* get_value_##typevalue(RB_Tree_Trav*trav)\
{\
    return ((RB_##typevalue*)(trav->it->data))->value;\
}\
static  void iter_init_##typevalue(RB_Tree_Trav*trav)\
{\
    trav->first=get_key_##typevalue;\
    trav->second=get_value_##typevalue;\
}\
static void default_free_##typevalue(void* data)\
{\
    free(data);\
}\
void rb_tree_init_##typevalue(RB_Tree* tree)\
{\
    rb_tree_init(tree);\
    tree->copy=rb_copy_##typevalue;\
    tree->cmp=rb_cmp_##typevalue;\
    tree->del=default_free_##typevalue;\
    tree->iterator_init=iter_init_##typevalue;\
}


RB_Tree_func_declare(int)


#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* __INCLUDED_RBTREE_H__ */

