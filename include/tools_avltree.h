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
void avl_node_init(AVL_Node* an)
{
    an->left=NULL;
    an->right=NULL;
    an->parent=NULL;
    an->data=NULL;
    an->prop=NULL;
}
void avl_tree_init(AVL_Tree* at)
{
    at->root=NULL;
    at->end=NULL;
    at->cmp=NULL;
    at->copy=NULL;
    at->del=NULL;
    at->size=0;
    at->prop=NULL;
}
//input the end node of avl_tree
//output the next increasing node of avl_tree
//
AVL_Node* avl_increase(AVL_Node* n);

AVL_Node* my_find(AVL_Tree* tree,void* data);

AVL_Node* my_insert(AVL_Tree* tree,void* data);


AVL_Node* successor(AVL_Node* n);
AVL_Node* predecessor(AVL_Node* n);

void avl_insert(AVL_Tree* tree,void*data);



#ifdef __cplusplus
}
#endif
#endif