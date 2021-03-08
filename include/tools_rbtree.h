#ifndef __INCLUDED_RBTREE_H__
#define __INCLUDED_RBTREE_H__

/** \file rbtree.h
 * Declaration of associated structures and functions for a simple, intrusive
 * red-black tree implementation.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <assert.h>
#include<stdio.h>
#include<string.h>
/*
 * Determine if we should use decorated pointers instead of a flag field in the node
 */
#if defined(__x86_64) && defined(_LP64)
#define _RB_USE_AUGMENTED_PTR
#endif

/** \defgroup rb_tree_compiler_prims Compiler Abstractions
 * Primitives used to abstract compiler-specific syntax for common details used in
 * providing hints to the compiler for optimization or linker details.
 * @{
 */

/**
 * Macro to check if a given assertion about an argument is true
 */


/** \defgroup rb_tree_state State Structures
 * Structures that are used to represent state of a red-black tree, including the
 * state of the tree itself, comparison functions used to determine how the tree
 * is to be traversed, and representations of red-black tree nodes themselves.
 * @{
 */

/**
 * Structure that represents a node in a red-black tree. Embed this in your own
 * structure in order to add your structure to the given red-black tree.
 * Users of the RB_Tree_Node would embed it something like
 * \code{.c}
    struct my_sample_struct {
        char *name;
        int data;
        struct RB_Tree_Node rnode;
    };
 * \endcode
 *
 * \note No user of `struct RB_Tree_Node` should ever modify or inspect any
 *       members of the structure.
 */
typedef struct RB_Tree_Node {
    /**
     * The left child (`NULL` if empty)
     */
    struct RB_Tree_Node *left;

    /** 
     * The right child (`NULL` if empty)
     */
    struct RB_Tree_Node *right;

    /**
     * The parent of this node (`NULL` if at root). Note that this is not a
     * raw pointer, but also doubles as the storage of the current node
     * color, if _RB_USE_AUGMENTED_PTR is set at compile time.
     */
    struct RB_Tree_Node *parent;

    /**
     * The key for this node
     */
    void* data;
    void *prop;

#ifndef _RB_USE_AUGMENTED_PTR /* Not using augmented pointer; i.e. a 32-bit platform */
    /**
     * The color of this node
     */
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

/**
 * Pointer to a function to cmp two keys, and returns as follows:
 *  - (0, +inf] if lhs > rhs
 *  - 0 if lhs == rhs
 *  - [-inf, 0) if lhs < rhs
 */
typedef int (*rb_cmp_func_t)(const void *lhs, const void *rhs);


/**
 * Structure representing an RB tree's associated state. Contains all
 * the information needed to manage the lifecycle of a RB tree.
 * \note Typically users should not directly manipulate the structure,
 *       but rather use the provided accessor functions.
 */
typedef struct RB_Tree {
    /**
     * The root of the tree
     */
    struct RB_Tree_Node *root;

    /**
     * Predicate used for traversing the tree
     */
    rb_cmp_func_t cmp;
    void * (*copy)(void*);
    void  (*del)(void*);

    void* (*find)(struct RB_Tree*,void*);
    void (*insert)(struct RB_Tree*,void*);
    void (*erase)(struct RB_Tree*,void*);

    struct RB_Tree_Trav*(*begin)(struct RB_Tree*);
    struct RB_Tree_Trav*(*rbegin)(struct RB_Tree*);

    void(*iterator_init)(struct RB_Tree_Trav*);  

    /**
     * The right-most node of the rb-tree
     */
    struct RB_Tree_Node *rightmost;

    /**
     * Private state that can be used by the rb-tree owner
     */
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
/**@} rb_tree_state */

/** \defgroup rb_result Function Results and Error Handling
 * @{
 */
/** \typedef rb_result_t
 * Value of a returned result code from a red-black tree function.
 */


/**@} rb_result_code */
/**@} rb_result */

/** \brief Helper to get a pointer to a containing structure.
 * Given a pointer to an RB_Tree_Node, a target type and a member name,
 * return a pointer to the structure containing the `struct RB_Tree_Node`.
 * \code{.c}
    struct sample {
        const char *name;
        struct RB_Tree_Node node;
    };

    void test(void)
    {
        struct sample samp = { .name = "Test 123" };
        struct RB_Tree_Node *samp_node = &(samp.node);
        struct sample *samp2 = RB_CONTAINER_OF(samp_node, struct sample, node);

        assert(&samp == samp2);
    }
 * \endcode
 * \param x The pointer to the node
 * \param type The type of the containing structure
 * \param memb The name of the `struct RB_Tree_Node` in the containing structure
 * \return Pointer to the containing structure of the specified type
 */


/** \defgroup rb_functions Functions for Manipulating Red-Black Trees
 * All functions associated with manipulating Red-Black trees using `struct RB_Tree`,
 * inluding lifecycle functions and member manipulation and state checking functions.
 * @{
 */

/**
 * \brief Construct a new, empty red-black tree, with extended state
 * Given a region of memory at least the size of a struct RB_Tree to
 * store the red-black tree metadata, update it to contain an initialized, empty
 * red-black tree, with given private state.
 * \param tree Pointer to the new tree.
 * \param cmp Function used to traverse the tree.
 * \param state The private state to be passed to the cmp function
 * \return RB_OK on success, an error code otherwise
 */
//rb_result_t rb_tree_init_ex(struct RB_Tree *tree, rb_cmp_func_ex_t cmp, void *state);

/**
 * \brief Construct a new, empty red-black tree.
 * Given a region of memory at least the size of a struct RB_Tree to
 * store the red-black tree metadata, update it to contain an initialized, empty
 * red-black tree.
 * \param tree Pointer to the new tree.
 * \param cmp Function used to traverse the tree.
 * \return RB_OK on success, an error code otherwise
 */




/**
 * \brief Destroy a Red-Black tree.
 * Clean up the state structure, clearing out the state of the tree
 * so that it no longer can be used.
 * \note Assumes that external callers will deallocate all nodes through
 *       some application-specific mechanism.
 * \param tree The reference to the pointer to the tree itself.
 * \return RB_OK on success, an error code otherwise
 */
void rb_tree_free(struct RB_Tree *tree);

/**
 * \brief Find a node in the Red-Black tree given the specified key.
 * Given a key, search the RB-tree iteratively until the specified key is found.
 * This traversal is in O(log n) time, per the properties of a binary search tree.
 * \param tree The RB-tree to search
 * \param key The key to search for
 * \param value a reference to a pointer to receive the pointer to the RB_Tree_Node if key is found
 * \return RB_OK on success, an error code otherwise
 */
RB_Tree_Node* rb_tree_find(struct RB_Tree *tree,void *data);
void* rb_tree_findn(struct RB_Tree *tree,void *data);
/**
 * \brief Insert a node into the tree.
 * Given a node and key, insert the node into the red-black tree and rebalance
 * the tree if appropriate. Insertion is O(log n) time, with two tree traversals
 * possible -- one for insertion (guaranteed) and one for rebalancing.
 * \param tree the RB tree to insert the node into
 * \param key The key for the node (must live as long as the node itself is in the tree)
 * \param node the node to be inserted into the tree
 * \return RB_OK on sucess, an error code otherwise
 */
//rb_result_t rb_tree_insert(struct RB_Tree *tree,void *data);
void rb_tree_insert(struct RB_Tree *tree,void *data);

/**
 * \brief Remove the specified node from the Red-Black tree.
 * Given a pointer to the node, splice the node out of the tree, then, if applicable
 * rebalance the tree so the Red-Black properties are maintained.
 * \param tree The tree we want to remove the node from
 * \param node The the node we want to remove
 * \return RB_OK on success, an error code otherwise
 */
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


/**
 * Find the successor (greater than, relative to predicate) node of the given node.
 */
RB_Tree_Node* rb_tree_successor(struct RB_Tree_Node *n);
/**
 * Find the predecessor (less than, relative to predicate) node of the given node.
 */
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

