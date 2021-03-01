#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_
#ifdef __cplusplus
extern "C"{
#endif
#include<stdlib.h>
typedef struct AVL_Node{
    struct AVL_Node* left,*right,*parent;
    void* data,*prop;

}AVL_Node;

typedef struct  AVL_Tree{
    AVL_Node *root,*end;
    int (*cmp)(const void* p1,const void* p2);  
    void* (*copy)(void*); 
    void  (*del)(void*);  
    unsigned int size;
    void* prop;
}AVL_Tree;

// typedef struct RB_Trav{
//     RB_Tree*tree;
//     RB_Node* it;
//     void*(*next)(struct RB_Trav*);
//     void*(*prev)(struct RB_Trav*);
//     void*(*first)(struct RB_Trav*);
//     void*(*second)(struct RB_Trav*);
//     void*prop;

// }RB_Trav;
// void RB_Trav_init(RB_Trav*);


void avl_node_init(AVL_Node* an);

void avl_tree_init(AVL_Tree* at);
//input the end node of avl_tree
//output the next increasing node of avl_tree
//
AVL_Node* avl_increase(AVL_Node* n);

AVL_Node* my_find(AVL_Tree* tree,void* data);

AVL_Node* my_insert(AVL_Tree* tree,void* data);


AVL_Node* successor(AVL_Node* n);
AVL_Node* predecessor(AVL_Node* n);

void avl_insert(AVL_Tree* tree,void*data);



#define AVL_Tree_func_declare(typevalue) typedef struct AVL_##typevalue{typevalue key;void* value;void* prop;}AVL_##typevalue;\
void AVL_init_##typevalue(AVL_##typevalue*);\
int AVL_cmp_##typevalue(const void*p1,const void*p2 );\
void AVL_Tree_init_##typevalue(AVL_Tree*);


#define AVL_Tree_func(typevalue)  int AVL_cmp_##typevalue(const void*p1,const void*p2)\
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
static void* AVL_copy_##typevalue(void* p)\
{\
    void* re=malloc(sizeof(AVL_##typevalue));\
    memmove(re,p,sizeof(AVL_##typevalue));\
    return re;\
}\
static void * get_key_##typevalue(RB_Trav* trav)\
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
void RB_init_##typevalue(RB_##typevalue* t)\
{\
t->value=NULL;\
t->prop=NULL;\
}






#ifdef __cplusplus
}
#endif
#endif