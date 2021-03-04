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


    void *(*find)(struct AVL_Tree*,void*);
    void* (*insert)(struct AVL_Tree*,void*);
    int (*erase)(struct AVL_Tree*,void*);
    struct AVL_Trav* (*begin)(struct AVL_Tree*);
    struct AVL_Trav*(*rbegin)(struct AVL_Tree*);
    void (*iterator_init)(struct AVL_Trav*); 
    void* prop;
}AVL_Tree;


void avl_node_init(AVL_Node* an);

void avl_tree_init(AVL_Tree* at);
//input the end node of avl_tree
//output the next increasing node of avl_tree
//
AVL_Node* avl_increase(AVL_Node* n);
AVL_Node* avl_decrease(AVL_Node* n);
//AVL_Node* my_find(AVL_Tree* tree,void* data);
AVL_Node* avl_find(AVL_Tree* tree,void* data);
struct AVL_Trav* avl_tree_begin(AVL_Tree* tree);
struct AVL_Trav* avl_tree_rbegin(AVL_Tree* tree);

//AVL_Node* my_insert(AVL_Tree* tree,void* data);


AVL_Node* successor(AVL_Node* n);
AVL_Node* predecessor(AVL_Node* n);

void avl_insert(AVL_Tree* tree,void*data);
void avl_delete_node(AVL_Tree* tree,AVL_Node* n);
void avl_delete_data(AVL_Tree* tree,void* data);

typedef struct AVL_Trav{
    AVL_Tree* tree;
    AVL_Node* it;
    void *(*next)(struct AVL_Trav*);
    void *(*prev)(struct AVL_Trav*); 
    void *(*first)(struct AVL_Trav*); 
    void *(*second)(struct AVL_Trav*); 
    void* prop;
    //void * (*)

}AVL_Trav;


void avl_trav_init(AVL_Trav*);
void * avl_next(struct AVL_Trav* trav);
void* avl_prev(struct AVL_Trav *trav);




#define AVL_Tree_func_declare(typevalue) typedef struct AVL_##typevalue{typevalue key;void* value;void* prop;}AVL_##typevalue;\
void avl_init_##typevalue(AVL_##typevalue*);\
int avl_cmp_##typevalue(const void*p1,const void*p2 );\
void avl_tree_init_##typevalue(AVL_Tree*);


// #define AVL_Tree_func(typevalue)  int AVL_cmp_##typevalue(const void*p1,const void*p2)\
// {\
// AVL_##typevalue *q1=(AVL_##typevalue*)p1,*q2=(AVL_##typevalue*)p2;\
//     if(q1->key>q2->key)\
//     {\
//         return 1;\
//     }\
//     else if(q1->key<q2->key)\
//     {\
//         return -1;\
//     }\
//     return 0;\
// }\
// static void* AVL_copy_##typevalue(void* p)\
// {\
//     void* re=malloc(sizeof(AVL_##typevalue));\
//     memmove(re,p,sizeof(AVL_##typevalue));\
//     return re;\
// }\
// static void * get_key_##typevalue(AVL_Trav* trav)\
// {\
//     return (void*)(&(((AVL_##typevalue*)(trav->it->data))->key));\
// }\
// static void* get_value_##typevalue(AVL_Trav*trav)\
// {\
//     return ((AVL_##typevalue*)(trav->it->data))->value;\
// }\
// static void iter_init_##typevalue(AVL_Trav*trav)\
// {\
//     trav->first=get_key_##typevalue;\
//     trav->second=get_value_##typevalue;\
// }\
// void avl_tree_init_##typevalue(AVL_Tree* tree)\
// {\
//     avl_tree_init(tree);\
//     tree->copy=AVL_copy_##typevalue;\
//     tree->cmp=AVL_cmp_##typevalue;\
//     tree->iterator_init=iter_init_##typevalue;\
// }\
// void AVL_init_##typevalue(AVL_##typevalue* t)\
// {\
//     t->value=NULL;\
//     t->prop=NULL;\
// }






#ifdef __cplusplus
}
#endif
#endif