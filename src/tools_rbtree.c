

#include <tools_rbtree.h>

#include <stdlib.h>
#include <string.h>


#define COLOR_BLACK                     0x0ull


#define COLOR_RED                       0x1ull


#ifdef _RB_USE_AUGMENTED_PTR /* Should we augment the pointer with the color metadata */

#define RB_TREE_COLOR_SHIFT                         63 /* TODO: parameterize me */


#define RB_TREE_PARENT_PTR_MASK                     ((1ull << RB_TREE_COLOR_SHIFT) - 1)

#define _RB_TREE_GET_PARENT_COLOR_MASK(__node)      (((size_t)(__node)->parent) & ~RB_TREE_PARENT_PTR_MASK)

#define RB_TREE_NODE_GET_COLOR(_node)               ((((size_t)(_node)->parent) >> RB_TREE_COLOR_SHIFT) & 1)

#define RB_TREE_NODE_SET_COLOR(_node, _color)       do { (_node)->parent = (struct RB_Tree_Node *)((((size_t)(_node)->parent) & RB_TREE_PARENT_PTR_MASK) | ((_color) << RB_TREE_COLOR_SHIFT)); } while (0)


#define RB_TREE_NODE_GET_PARENT(_node)              ((struct RB_Tree_Node *)(((size_t)(_node)->parent) & RB_TREE_PARENT_PTR_MASK))


#define RB_TREE_NODE_SET_PARENT(_node, _parent)     do { (_node)->parent = (struct RB_Tree_Node *)((size_t)(_parent) | _RB_TREE_GET_PARENT_COLOR_MASK((_node))); } while (0)

#else
#define RB_TREE_NODE_GET_COLOR(_node)               ((_node)->color)
#define RB_TREE_NODE_SET_COLOR(_node, _color)       do { ((_node)->color = (_color)); } while (0)
#define RB_TREE_NODE_GET_PARENT(_node)              ((_node)->parent)
#define RB_TREE_NODE_SET_PARENT(_node, _parent)     do { ((_node)->parent = (_parent)); } while (0)

#endif 


static void rb_tree_free_one_node(struct RB_Tree*tree,struct RB_Tree_Node*n)
{
    if(n==NULL||tree==NULL)
    {
        return;
    }
   if(n->left!=NULL)
   {
        rb_tree_free_one_node(tree,n->left);
   } 
   if(n->right!=NULL)
   {
        rb_tree_free_one_node(tree,n->right);
   }
   tree->del(n->data);
   free(n);
}
void rb_tree_free(struct RB_Tree *tree)
{
    if(tree==NULL)
    {
        return ;
    }

    rb_tree_free_one_node(tree,tree->root);
    free(tree);
}



RB_Tree_Node* rb_tree_find(struct RB_Tree *tree,void *data)
{
    if (tree==NULL||(tree->root == NULL)) {
        return NULL;
    }
    struct RB_Tree_Node *node = tree->root;

    while (node != NULL) {
        int cmp = tree->cmp(data, node->data);

        if (cmp < 0) {
           // printf("once1\n");
            node = node->left;
        } else if (cmp == 0) {
            break; /* We found our node */
        } else {
           // printf("once\n");
            /* Otherwise, we want the right node, and continue iteration */
            node = node->right;
        }
    }
    return node;
}
void* rb_tree_findn(struct RB_Tree *tree,void *data)
{
    RB_Tree_Node* node=rb_tree_find(tree,data);
    if(node!=NULL)
    {
        return node->data;
    }
    return NULL;
}
/* Helper function to get a node's sibling */
static inline struct RB_Tree_Node *__helper_get_sibling(struct RB_Tree_Node *node)
{
    struct RB_Tree_Node *parent = RB_TREE_NODE_GET_PARENT(node);

    if (parent == NULL) {
        return NULL;
    }

    if (node == parent->left) {
        return parent->right;
    } else {
        return parent->left;
    }
}

/* Helper function to get a node's grandparent */
static inline struct RB_Tree_Node *__helper_get_grandparent(struct RB_Tree_Node *node)
{
    struct RB_Tree_Node *parent_node = RB_TREE_NODE_GET_PARENT(node);

    if (parent_node == NULL) {
        return NULL;
    }

    return RB_TREE_NODE_GET_PARENT(parent_node);
}

/* Helper function to get a node's uncle */
static inline struct RB_Tree_Node *__helper_get_uncle(struct RB_Tree_Node *node)
{
    struct RB_Tree_Node *grandparent = __helper_get_grandparent(node);

    if (grandparent == NULL) {
        return NULL;
    }

    if (RB_TREE_NODE_GET_PARENT(node) == grandparent->left) {
        return grandparent->right;
    } else {
        return grandparent->left;
    }
}

/* Helper function to do a left rotation of a given node */
static inline void __helper_rotate_left(struct RB_Tree *tree,
                          struct RB_Tree_Node *node)
{
    struct RB_Tree_Node *x = node;
    struct RB_Tree_Node *y = x->right;

    x->right = y->left;

    if (y->left != NULL) {
        struct RB_Tree_Node *yleft = y->left;
        RB_TREE_NODE_SET_PARENT(yleft, x);
    }

    RB_TREE_NODE_SET_PARENT(y, RB_TREE_NODE_GET_PARENT(x));

    if (RB_TREE_NODE_GET_PARENT(x) == NULL) {
        tree->root = y;
    } else {
        struct RB_Tree_Node *xp = RB_TREE_NODE_GET_PARENT(x);
        if (x == xp->left) {
            xp->left = y;
        } else {
            xp->right = y;
        }
    }

    y->left = x;
    RB_TREE_NODE_SET_PARENT(x, y);
}

/* Helper function to do a right rotation of a given node */
static inline void __helper_rotate_right(struct RB_Tree *tree,
                           struct RB_Tree_Node *node)
{
    struct RB_Tree_Node *x = node;
    struct RB_Tree_Node *y = x->left;

    x->left = y->right;

    if (y->right != NULL) {
        struct RB_Tree_Node *yright = y->right;
        RB_TREE_NODE_SET_PARENT(yright, x);
    }

    RB_TREE_NODE_SET_PARENT(y, RB_TREE_NODE_GET_PARENT(x));

    if (RB_TREE_NODE_GET_PARENT(x) == NULL) {
        tree->root = y;
    } else {
        struct RB_Tree_Node *xp = RB_TREE_NODE_GET_PARENT(x);
        if (x == xp->left) {
            xp->left = y;
        } else {
            xp->right = y;
        }
    }

    y->right = x;
    RB_TREE_NODE_SET_PARENT(x, y);
}

/* Function to perform a RB tree rebalancing after an insertion */
static void __helper_rb_tree_insert_rebalance(struct RB_Tree *tree,
                                       struct RB_Tree_Node *node)
{
    struct RB_Tree_Node *new_node_parent = RB_TREE_NODE_GET_PARENT(node);

    if (new_node_parent != NULL && RB_TREE_NODE_GET_COLOR(new_node_parent) != COLOR_BLACK) {
        struct RB_Tree_Node *pnode = node;

        /* Iterate until we're at the root (which we just color black) or
         * until we the parent node is no longer red.
         */
        while ((tree->root != pnode) && (RB_TREE_NODE_GET_PARENT(pnode) != NULL) &&
                    (RB_TREE_NODE_GET_COLOR(
                            RB_TREE_NODE_GET_PARENT(pnode)) == COLOR_RED))
        {
            struct RB_Tree_Node *parent = RB_TREE_NODE_GET_PARENT(pnode);
            struct RB_Tree_Node *grandparent = __helper_get_grandparent(pnode);
            struct RB_Tree_Node *uncle = NULL;
            int uncle_is_left;

            assert(RB_TREE_NODE_GET_COLOR(pnode) == COLOR_RED);

            if (parent == grandparent->left) {
                uncle_is_left = 0;
                uncle = grandparent->right;
            } else {
                uncle_is_left = 1;
                uncle = grandparent->left;
            }

            /* Case 1: Uncle is not black */
            if (uncle && RB_TREE_NODE_GET_COLOR(uncle) == COLOR_RED) {
                /* Color parent and uncle black */
                RB_TREE_NODE_SET_COLOR(parent, COLOR_BLACK);
                RB_TREE_NODE_SET_COLOR(uncle, COLOR_BLACK);

                /* Color Grandparent as Red */
                RB_TREE_NODE_SET_COLOR(grandparent, COLOR_RED);
                pnode = grandparent;
                /* Continue iteration, processing grandparent */
            } else {
                /* Case 2 - node's parent is red, but uncle is black */
                if (!uncle_is_left && parent->right == pnode) {
                    pnode = RB_TREE_NODE_GET_PARENT(pnode);
                    __helper_rotate_left(tree, pnode);
                } else if (uncle_is_left && parent->left == pnode) {
                    pnode = RB_TREE_NODE_GET_PARENT(pnode);
                    __helper_rotate_right(tree, pnode);
                }

                /* Case 3 - Recolor and rotate*/
                parent = RB_TREE_NODE_GET_PARENT(pnode);
                RB_TREE_NODE_SET_COLOR(parent, COLOR_BLACK);

                grandparent = __helper_get_grandparent(pnode);
                RB_TREE_NODE_SET_COLOR(grandparent, COLOR_RED);
                if (!uncle_is_left) {
                    __helper_rotate_right(tree, grandparent);
                } else {
                    __helper_rotate_left(tree, grandparent);
                }
            }
        }

        /* Make sure the tree root is black (Case 1: Continued) */
        struct RB_Tree_Node *tree_root = tree->root;
        RB_TREE_NODE_SET_COLOR(tree_root, COLOR_BLACK);
    }
}


void rb_tree_insert(struct RB_Tree *tree,void *data)
{
    tree->size++;
    int rightmost = 1;
    struct RB_Tree_Node *nd = NULL;

    RB_Tree_Node* node=(RB_Tree_Node*)malloc(sizeof(RB_Tree_Node));
    rb_tree_node_init(node);
    node->data=tree->copy(data);

    /* Case 1: Simplest case -- tree is empty */
    if (tree->root == NULL) {
        tree->root = node;
        tree->rightmost = node;
        RB_TREE_NODE_SET_COLOR(node, COLOR_BLACK);
        return ;
    }

    /* Otherwise, insert the node as you would typically in a BST */
    nd = tree->root;
    RB_TREE_NODE_SET_COLOR(node, COLOR_RED);

    rightmost = 1;

    /* Insert a node into the tree as you normally would */
    while (nd != NULL) {
        int cmp = tree->cmp(data, nd->data);

        if (cmp == 0) {
            tree->del(nd->data);
            nd->data=node->data;
            free(node);
            tree->size--; 
            return;
        }

        if (cmp < 0) {
            rightmost = 0;
            if (nd->left == NULL) {
                nd->left = node;
                break;
            } else {
                nd = nd->left;
            }
        } else {
            if (nd->right == NULL) {
                nd->right = node;
                break;
            } else {
                nd = nd->right;
            }
        }
    }

    RB_TREE_NODE_SET_PARENT(node, nd);
    if (1 == rightmost) {
        tree->rightmost = node;
    }

    /* Rebalance the tree about the node we just added */
    __helper_rb_tree_insert_rebalance(tree, node);

}


/**
 * Find the minimum of the subtree starting at node
 */



/* Replace x with y, inserting y where x previously was */
static void __helper_rb_tree_swap_node(struct RB_Tree *tree,
                                struct RB_Tree_Node *x,
                                struct RB_Tree_Node *y)
{
    struct RB_Tree_Node *left = x->left;
    struct RB_Tree_Node *right = x->right;
    struct RB_Tree_Node *parent = RB_TREE_NODE_GET_PARENT(x);

    RB_TREE_NODE_SET_PARENT(y, parent);

    if (parent != NULL) {
        if (parent->left == x) {
            parent->left = y;
        } else {
            parent->right = y;
        }
    } else {
        if (tree->root == x) {
            tree->root = y;
        }
    }

    y->right = right;
    if (right != NULL) {
        RB_TREE_NODE_SET_PARENT(right, y);
    }
    x->right = NULL;

    y->left = left;
    if (left != NULL) {
        RB_TREE_NODE_SET_PARENT(left, y);
    }
    x->left = NULL;

    RB_TREE_NODE_SET_COLOR(y, RB_TREE_NODE_GET_COLOR(x));
    x->parent = NULL;
}

static void __helper_rb_tree_delete_rebalance(struct RB_Tree *tree,
                                       struct RB_Tree_Node *node,
                                       struct RB_Tree_Node *parent,
                                       int node_is_left)
{
    struct RB_Tree_Node *x = node;
    struct RB_Tree_Node *xp = parent;
    int is_left = node_is_left;

    while (x != tree->root && (x == NULL || RB_TREE_NODE_GET_COLOR(x) == COLOR_BLACK)) {
        struct RB_Tree_Node *w = is_left ? xp->right : xp->left;    /* Sibling */

        if (w != NULL && RB_TREE_NODE_GET_COLOR(w) == COLOR_RED) {
            /* Case 1: */
            RB_TREE_NODE_SET_COLOR(w, COLOR_BLACK);
            RB_TREE_NODE_SET_COLOR(xp, COLOR_RED);
            if (is_left) {
                __helper_rotate_left(tree, xp);
            } else {
                __helper_rotate_right(tree, xp);
            }
            w = is_left ? xp->right : xp->left;
        }

        struct RB_Tree_Node *wleft = w != NULL ? w->left : NULL;
        struct RB_Tree_Node *wright = w != NULL ? w->right : NULL;
        if ( (wleft == NULL || RB_TREE_NODE_GET_COLOR(wleft) == COLOR_BLACK) &&
             (wright == NULL || RB_TREE_NODE_GET_COLOR(wright) == COLOR_BLACK) )
        {
            /* Case 2: */
            if (w != NULL) {
                RB_TREE_NODE_SET_COLOR(w, COLOR_RED);
            }
            x = xp;
            xp = RB_TREE_NODE_GET_PARENT(x);
            is_left = xp && (x == xp->left);
        } else {
            if (is_left && (wright == NULL || RB_TREE_NODE_GET_COLOR(wright) == COLOR_BLACK)) {
                /* Case 3a: */
                RB_TREE_NODE_SET_COLOR(w, COLOR_RED);
                if (wleft) {
                    RB_TREE_NODE_SET_COLOR(wleft, COLOR_BLACK);
                }
                __helper_rotate_right(tree, w);
                w = xp->right;
            } else if (!is_left && (wleft == NULL || RB_TREE_NODE_GET_COLOR(wleft) == COLOR_BLACK)) {
                /* Case 3b: */
                RB_TREE_NODE_SET_COLOR(w, COLOR_RED);
                if (wright) {
                    RB_TREE_NODE_SET_COLOR(wright, COLOR_BLACK);
                }
                __helper_rotate_left(tree, w);
                w = xp->left;
            }

            /* Case 4: */
            wleft = w->left;
            wright = w->right;

            RB_TREE_NODE_SET_COLOR(w, RB_TREE_NODE_GET_COLOR(xp));
            RB_TREE_NODE_SET_COLOR(xp, COLOR_BLACK);

            if (is_left && wright != NULL) {
                RB_TREE_NODE_SET_COLOR(wright, COLOR_BLACK);
                __helper_rotate_left(tree, xp);
            } else if (!is_left && wleft != NULL) {
                RB_TREE_NODE_SET_COLOR(wleft, COLOR_BLACK);
                __helper_rotate_right(tree, xp);
            }
            x = tree->root;
        }
    }

    if (x != NULL) {
        RB_TREE_NODE_SET_COLOR(x, COLOR_BLACK);
    }
}

void rb_tree_delete_node(struct RB_Tree *tree,
                           struct RB_Tree_Node *node)
{

    if(node==NULL||tree==NULL)
    {
        return;
    }
    struct RB_Tree_Node *y;
    tree->size--;

    if (node->left == NULL || node->right == NULL) {
        y = node;
        if (node == tree->rightmost) {
            /* The new rightmost item is our successor */
            tree->rightmost = rb_tree_predecessor(node);
        }
    } else {
        
        y = rb_tree_successor(node);
    }

    struct RB_Tree_Node *x, *xp;

    if (y->left != NULL) {
        x = y->left;
    } else {
        x = y->right;
    }

    if (x != NULL) {
        RB_TREE_NODE_SET_PARENT(x, RB_TREE_NODE_GET_PARENT(y));
        xp = RB_TREE_NODE_GET_PARENT(x);
    } else {
        xp = RB_TREE_NODE_GET_PARENT(y);
    }

    int is_left = 0;
    if (RB_TREE_NODE_GET_PARENT(y) == NULL) {
        tree->root = x;
        xp = NULL;
    } else {
        struct RB_Tree_Node *yp = RB_TREE_NODE_GET_PARENT(y);
        if (y == yp->left) {
            yp->left = x;
            is_left = 1;
        } else {
            yp->right = x;
            is_left = 0;
        }
    }

    int y_color = RB_TREE_NODE_GET_COLOR(y);

    /* Swap in the node */
    if (y != node) {
        __helper_rb_tree_swap_node(tree, node, y);
        if (xp == node) {
            xp = y;
        }
    }

    if (y_color == COLOR_BLACK) {
        __helper_rb_tree_delete_rebalance(tree, x, xp, is_left);
    }
    tree->del(node->data);
    free(node);

}
void rb_tree_delete_data(RB_Tree* tree,void* data)
{
     RB_Tree_Node* n= rb_tree_find(tree,data);
     if(n!=NULL)
     {
        rb_tree_delete_node(tree,n);
     }
 }

RB_Tree_Node* __rb_tree_find_minimum(RB_Tree* tree)
{

    RB_Tree_Node* node=NULL;
    if(tree!=NULL)
    {
        if(tree->root==NULL)
        {
            return NULL;
        }
        node=tree->root;
        while(node->left!=NULL)
        {
          node=node->left;
        }
        return node;
    }

    return NULL;
}

RB_Tree_Node* __rb_tree_find_maximum(RB_Tree* tree)
{
  RB_Tree_Node* node=NULL;
  if(tree!=NULL)
  {
    if(tree->root==NULL)
    {
      return NULL;
    }
    node=tree->root;
    while(node->right!=NULL)
    {
      node=node->right;
    }
    return node;
  }

  return NULL;
}

struct RB_Tree_Trav* rb_tree_begin(RB_Tree*tree)
{
   RB_Tree_Trav*re=(RB_Tree_Trav*)malloc(sizeof(RB_Tree_Trav));
   rb_tree_trav_init(re);
   if(tree->iterator_init!=NULL)
   {
        tree->iterator_init(re);
   } 
   re->it=__rb_tree_find_minimum(tree);
   return re;
}
struct RB_Tree_Trav* rb_tree_rbegin(RB_Tree*tree)
{
    RB_Tree_Trav*re=(RB_Tree_Trav*)malloc(sizeof(RB_Tree_Trav));
    rb_tree_trav_init(re);
    if(tree->iterator_init!=NULL)
    {
        tree->iterator_init(re);
    } 
    re->it=__rb_tree_find_maximum(tree);
    return re;
}
RB_Tree_Node* rb_tree_successor(struct RB_Tree_Node *n)
{
  if(n==NULL)
  {
    return NULL;
  }
  RB_Tree_Node*x=n,*node=NULL;
  if(x->right!=NULL)
  {
      node=x->right;
      while(node->left!=NULL)
      {
        node=node->left;
      }
      return node;
  }
  else
  {
    node=RB_TREE_NODE_GET_PARENT(x);

    while(node!=NULL&&(x==node->right))
    {
      x=node;
      node=RB_TREE_NODE_GET_PARENT(node);
    }
    //printf("sdd\n");
    return node;
  }


  return node;
}
RB_Tree_Node* rb_tree_predecessor(struct RB_Tree_Node *n)
{
  if(n==NULL)
  {
    return NULL;
  }  
  RB_Tree_Node* x=n,*node=NULL;
  if(x->left!=NULL)
  {
    node=x->left;
    while(node->right!=NULL)
    {
      node=node->right;
    }
    return node;
  }
  else
  {
    node=RB_TREE_NODE_GET_PARENT(x);
    //node=x->parent;

    while((node!=NULL)&&(x==node->left))
    {
      x=node;
      node=RB_TREE_NODE_GET_PARENT(node);
    }

    return node;

  }
  return node;
}


void * rb_tree_next(struct RB_Tree_Trav* trav)
{
    if(trav->it==NULL)
    {
        return NULL;
    }
    RB_Tree_Node* node=rb_tree_successor(trav->it);

    trav->it=node;
    if(node!=NULL)
    {
        return node->data;
    }
    return NULL;
}
void* rb_tree_prev(struct RB_Tree_Trav *trav)
{
    if(trav->it==NULL)
    {
        return NULL;
    }
    RB_Tree_Node* node=rb_tree_predecessor(trav->it);
    trav->it=node;
    if(node!=NULL)
    {
        return node->data;
    }
    return NULL;
}



RB_Tree_func(int)
