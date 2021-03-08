#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_
#ifdef __cplusplus
extern "C"{
#endif
#include<stdlib.h>

typedef struct AVL_Tree_Node{
    struct AVL_Tree_Node* left,*right,*parent;
    void* data,*prop;

}AVL_Tree_Node;

typedef struct  AVL_Tree{
    AVL_Tree_Node *root,*end;
    int (*cmp)(const void* p1,const void* p2);  
    void* (*copy)(void*); 
    void  (*del)(void*);  
    unsigned int size;

    void *(*find)(struct AVL_Tree*,void*);
//the follow two function' return  is different from rbtree
    void (*insert)(struct AVL_Tree*,void*);
    void (*erase)(struct AVL_Tree*,void*);
//the above two function' return  is different from rbtree
    struct AVL_Tree_Trav* (*begin)(struct AVL_Tree*);
    struct AVL_Tree_Trav*(*rbegin)(struct AVL_Tree*);
    void (*iterator_init)(struct AVL_Tree_Trav*); 
    void* prop;
}AVL_Tree;
static inline void avl_node_init(AVL_Tree_Node* an)
{
    an->left=NULL;
    an->right=NULL;
    an->parent=NULL;
    an->data=NULL;
    an->prop=NULL;
}



//input the end node of avl_tree
//output the next increasing node of avl_tree
//
//AVL_Tree_Node* avl_increase(AVL_Tree_Node* n);
//AVL_Tree_Node* avl_decrease(AVL_Tree_Node* n);
//AVL_Tree_Node* my_find(AVL_Tree* tree,void* data);
void* avl_findn(AVL_Tree* tree,void* data);


struct AVL_Tree_Trav* avl_tree_begin(AVL_Tree* tree);
struct AVL_Tree_Trav* avl_tree_rbegin(AVL_Tree* tree);

//AVL_Tree_Node* my_insert(AVL_Tree* tree,void* data);


AVL_Tree_Node* successor(AVL_Tree_Node* n);
AVL_Tree_Node* predecessor(AVL_Tree_Node* n);

void avl_insert(AVL_Tree* tree,void*data);
void avl_delete_node(AVL_Tree* tree,AVL_Tree_Node* n);
void avl_delete_data(AVL_Tree* tree,void* data);
void avl_tree_free(AVL_Tree* tree);
static inline void avl_tree_init(AVL_Tree* at)
{
    at->root=NULL;
    at->end=NULL;
    at->cmp=NULL;
    at->copy=NULL;
    at->del=NULL;
    at->size=0;
    at->find=avl_findn;
    at->insert=avl_insert;
    at->erase=avl_delete_data;
    
    at->begin=avl_tree_begin;
    at->rbegin=avl_tree_rbegin;

    at->iterator_init=NULL; 
    at->prop=NULL;
}
typedef struct AVL_Tree_Trav{
    AVL_Tree* tree;
    AVL_Tree_Node* it;
    void *(*next)(struct AVL_Tree_Trav*);
    void *(*prev)(struct AVL_Tree_Trav*); 
    void *(*first)(struct AVL_Tree_Trav*); 
    void *(*second)(struct AVL_Tree_Trav*); 
    void* prop;
    //void * (*)

}AVL_Tree_Trav;



void * avl_next(struct AVL_Tree_Trav* trav);
void* avl_prev(struct AVL_Tree_Trav *trav);


static inline void avl_trav_init(AVL_Tree_Trav* it)
{
    it->tree=NULL;
    it->next=avl_next;
    it->prev=avl_prev;
    it->it=NULL;
    it->prop=NULL;
}

#define AVL_Tree_func_declare(typevalue) typedef struct AVL_##typevalue{typevalue key;void* value;void* prop;}AVL_##typevalue;\
static inline  void avl_init_##typevalue(AVL_##typevalue* t)\
{\
    t->value=NULL;\
    t->prop=NULL;\
}\
int avl_cmp_##typevalue(const void*p1,const void*p2);\
void avl_tree_init_##typevalue(AVL_Tree*);


#define AVL_Tree_func(typevalue)   int avl_cmp_##typevalue(const void*p1,const void*p2)\
{\
    AVL_##typevalue *q1=(AVL_##typevalue*)p1,*q2=(AVL_##typevalue*)p2;\
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
static void* avl_copy_##typevalue(void* p)\
{\
    void* re=malloc(sizeof(AVL_##typevalue));\
    memmove(re,p,sizeof(AVL_##typevalue));\
    return re;\
}\
static  void * get_key_##typevalue(AVL_Tree_Trav* trav)\
{\
    return (void*)(&(((AVL_##typevalue*)(trav->it->data))->key));\
}\
static  void* get_value_##typevalue(AVL_Tree_Trav*trav)\
{\
    return ((AVL_##typevalue*)(trav->it->data))->value;\
}\
static  void iter_init_##typevalue(AVL_Tree_Trav*trav)\
{\
    trav->first=get_key_##typevalue;\
    trav->second=get_value_##typevalue;\
}\
static void default_free_##typevalue(void*data)\
{\
    free(data);\
}\
void avl_tree_init_##typevalue(AVL_Tree* tree)\
{\
    avl_tree_init(tree);\
    tree->del=default_free_##typevalue;\
    tree->copy=avl_copy_##typevalue;\
    tree->cmp=avl_cmp_##typevalue;\
    tree->iterator_init=iter_init_##typevalue;\
}\



AVL_Tree_func_declare(int)




#ifdef __cplusplus
}
#endif
#endif