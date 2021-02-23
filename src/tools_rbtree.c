


#include "tools_rbtree.h"
#define RED        0    
#define BLACK    1   
#define LB_malloc malloc
#define LB_free free
static void default_free(void *p)
{

    LB_free(p);
}

void RB_Node_init(RB_Node*node)
{
    node->color=RED;
    node->parent=NULL;
    node->left=NULL;
    node->right=NULL;

    node->data=NULL;
    node->prop=NULL;
}
void RB_Tree_init(RB_Tree* tree)
{
    tree->root=NULL;
    tree->cmp=NULL;
    tree->copy=NULL;
    tree->del=default_free;
    tree->size=0;
    tree->find=RB_find;
    tree->insert=RB_insert;
    tree->erase=RB_erase;
    tree->begin=RB_begin;
    tree->rbegin=RB_rbegin;
    tree->iterator_init=NULL;
    tree->prop=NULL;
}
void RB_Trav_init(RB_Trav* it)
{
    it->tree=NULL;
    it->next=RB_next;
    it->prev=RB_prev;
    it->it=NULL;
    it->prop=NULL;
}
static void RB_Tree_Node_free(RB_Tree*tree,RB_Node* node)
{
    if(node==NULL)
    {
        return; 
    }
    if(node->left!=NULL)
    {
        RB_Tree_Node_free(tree,node->left);
    }
    if(node->right!=NULL)
    {
        RB_Tree_Node_free(tree,node->right);
    }
    if(node->data!=NULL)
    {
        tree->del(node->data);
       // free(node->data);
    }
    //printf("hre");
    LB_free(node);
}
void RB_Tree_free(RB_Tree *tree)
{
    if(tree==NULL)
    {
        return ;
    }
    RB_Node* node=tree->root;
    if (node != NULL&&tree->size>=1)
    {
        RB_Tree_Node_free(tree,node);
    }
    tree->size=0;

    LB_free(tree);
}


static RB_Node* rbtree_successor(RB_Node *x)
{
    RB_Node* node=NULL;

    if (x->right != NULL)
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
        node = x->parent;
        while ((node!=NULL) && (x==node->right))
        {
            x = node;
            node = node->parent;
        }
    }
    return node;
}
 

static RB_Node* rbtree_predecessor(RB_Node *x)
{
    RB_Node* node=NULL;
 
    if (x->left != NULL)
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

        node = x->parent;
        while ((node!=NULL) && (x==node->left))
        {
            x = node;
            node = node->parent;
        }
    }
    return node;
}
static void rbtree_right_rotate(RB_Tree *tree, RB_Node *y)
{
   
    RB_Node *x = y->left;

    
    y->left = x->right;
    if (x->right != NULL)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == NULL) 
    {

        tree->root = x;           
    }
    else
    {
        if (y == y->parent->right)
        {
            y->parent->right = x;    
        }
        else
        {
            y->parent->left = x;    
        }
    }

    
    x->right = y; 
    y->parent = x;
}

static void rbtree_left_rotate(RB_Tree *tree, RB_Node *x)
{
   
    RB_Node *y = x->right; 
    x->right = y->left;
    if (y->left != NULL)
    {
        y->left->parent = x;
    }
 
    y->parent = x->parent;

    if (x->parent == NULL)
    {
      
        tree->root = y;            
    }
    else
    {
        if (x->parent->left == x)
        {
            x->parent->left = y;    
        }
        else
        {
            x->parent->right = y;    
        }
    }
    

    y->left = x;

    x->parent = y;
}

static void rbtree_insert_fixup(RB_Tree *tree, RB_Node *node)
{
    RB_Node *parent, *gparent;

  //  printf("fdfdsfds\n");
    parent=node->parent;
    while (parent!=NULL&&parent->color==RED) 
    {

        gparent = parent->parent;
        if (parent == gparent->left)
        {
            RB_Node *uncle = gparent->right;
            if (uncle!=NULL&&uncle->color==RED)
            {
                //printf("cunzai dfsd \n");
                uncle->color=BLACK;
                parent->color=BLACK;
                gparent->color=RED;
                node = gparent;
                continue;
            }
            if (parent->right == node)
            {
                rbtree_left_rotate(tree, parent);
                RB_Node*tmp = parent;
                parent = node;
                node = tmp;
            }
            parent->color=BLACK;
            gparent->color=RED;
            rbtree_right_rotate(tree, gparent);
        } 
        else
        { 
            RB_Node *uncle = gparent->left;
            if (uncle!=NULL && uncle->color==RED)
            {
                //printf("cunzai dfsd \n");
                uncle->color=BLACK;
                parent->color=BLACK;
                gparent->color=RED;
                node = gparent;
                continue;
            }
            if (parent->left == node)
            {
                rbtree_right_rotate(tree, parent);
                RB_Node*tmp = parent;
                parent = node;
                node = tmp;
            } 
            parent->color=BLACK;
            gparent->color=RED;
            rbtree_left_rotate(tree, gparent);
        }
        parent=node->parent;
    }

    tree->root->color=BLACK;
}

void* RB_insert(RB_Tree *tree ,void* data)
{
    RB_Node *y = NULL;
    RB_Node *x = tree->root;
    RB_Node*node=(RB_Node*)LB_malloc(sizeof(RB_Node));
    RB_Node_init(node);
    node->data=tree->copy(data); 
    int re=0;
    RB_Node* node1=node;
    tree->size++;

    while (x != NULL)
    {
        y = x;
        re=tree->cmp(x->data,data);
        if (re>0)
        {

            x = x->left;
            if(x==NULL)
            {
                node->parent=y;
                y->left=node;
                break;
            }
        }
        else if(re<0)
        {
            x = x->right;
            if(x==NULL)
            {
                node->parent=y;
                y->right=node;
                break;
            }
        }
        else
        {
            tree->del(x->data); 
            x->data=node->data;
            LB_free(node);
            tree->size--;
            return x->data;
        }
    }
    if(y==NULL)
    {
        tree->root = node;         
    }
    node1->color = RED; 
    rbtree_insert_fixup(tree, node1);
    return node1->data;
}
RB_Trav* RB_begin(RB_Tree*tree)
{
   RB_Trav*re=(RB_Trav*)LB_malloc(sizeof(RB_Trav));
   RB_Trav_init(re);
   if(tree->iterator_init!=NULL)
   {
        tree->iterator_init(re);
   }
   re->it=rbtree_minimum(tree);
   return re; 
}
RB_Trav* RB_rbegin(RB_Tree*tree)
{
    RB_Trav*re=(RB_Trav*)LB_malloc(sizeof(RB_Trav));
    RB_Trav_init(re);
    if(tree->iterator_init!=NULL)
    {
        tree->iterator_init(re);
    }
    re->it=rbtree_maximum(tree);
    return re; 
}
void* RB_next(RB_Trav*it)
{
    if(it->it==NULL)
    {
        return NULL;
    }
    RB_Node* node=rbtree_successor(it->it);
    if(node==NULL)
    {
        it->it=NULL;
        return NULL;
    }
    else
    {
        it->it=node;
        return node->data;
    }
}
void* RB_prev(RB_Trav*it)
{
    if(it->it==NULL)
    {
        return NULL;
    }
   RB_Node* node=rbtree_predecessor(it->it);
   if(node==NULL)
   {
        it->it=NULL;
        return NULL;
   }
   else
   {    it->it=node;
       return node->data; 
   } 

}
RB_Node* rbtree_minimum(RB_Tree *tree)
{
    RB_Node *node=NULL;

    if (tree!=NULL)
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

    if (node == NULL)
    {
        return NULL;
    }

    return NULL;
}

RB_Node* rbtree_maximum(RB_Tree *tree)
{
    RB_Node *node=NULL;

    if (tree!=NULL)
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

    if (node == NULL)
    {
        return NULL;
    }
    return NULL;
}


RB_Node* RB_find1(RB_Tree* tree,void*data)
{
     RB_Node* node=tree->root;
    int re=0;
    //int ceng=0;
    while(node!=NULL)
    {
        re=tree->cmp(data,node->data);
        if(re>0)
        {
            node=node->right;
        }
        else if(re<0)
        {
            node=node->left;
        }
        else
        {
           // printf("ceng:%d\n",ceng);
            return node;
        }
        //ceng++;
    }
    return NULL;
}
void* RB_find(RB_Tree *tree, void*data)
{
    RB_Node* node=RB_find1(tree,data);
    if(node!=NULL)
    {
        return node->data;
    }
    return NULL;

}


static void rbtree_delete_fixup(RB_Tree *tree, RB_Node *node, RB_Node *parent)
{
    RB_Node *other=NULL;

    while ((!node ||node->color==BLACK) && node != tree->root)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (other->color==RED)
            {
          
                other->color=BLACK; 
                parent->color=RED;
                rbtree_left_rotate(tree, parent);
                other = parent->right;
            }
            if ((!other->left || other->left->color==BLACK) &&
                (!other->right || other->right->color==BLACK))
            {
 
                other->color=RED;  
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->right || other->right->color==BLACK)
                {
           
                    other->left->color=BLACK;
                    other->color=RED;
                    rbtree_right_rotate(tree, other);
                    other = parent->right;
                }
            
                other->color=parent->color;
                parent->color=BLACK;
                other->right->color=BLACK;
                rbtree_left_rotate(tree, parent);
                node = tree->root;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (other->color==RED)
            {
  
                other->color=BLACK; 
                
                parent->color=RED;
                rbtree_right_rotate(tree, parent);
                other = parent->left;
            }
            if ((!other->left || other->left->color==BLACK) &&
                (!other->right || other->right->color==BLACK))
            {
    
                other->color=RED;  
                
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->left || other->left->color  ==BLACK)
                {
            
                    other->right->color=BLACK;
                    other->color=RED;
                    rbtree_left_rotate(tree, other);
                    other = parent->left;
                }
  
                other->color=parent->color;
                parent->color=BLACK;
                other->left->color=BLACK;
                rbtree_right_rotate(tree, parent);
                node = tree->root;
                break;
            }
        }
    }
    if (node)
    {
        node->color=BLACK;
    }
}

int RB_erase(RB_Tree*tree,void*data)
{
    RB_Node*node=RB_find1(tree,data);
    if(node==NULL)
    {
        return 0;
    }
    tree->size--; 
    RB_Node *child, *parent;
    int color;


    if ( (node->left!=NULL) && (node->right!=NULL) ) 
    {
    
        RB_Node *replace = node;

 
        replace = replace->right;
        while (replace->left != NULL)
        {
            replace = replace->left;
        }

 
        if (node->parent)
        {
            if (node->left == node)
            {
                node->parent->left = replace;
            }
            else
            {
                node->parent->right = replace;
            }
        } 
        else
        { 
   
            tree->root=replace;
        }

        child = replace->right;
        parent = replace->parent;

        color = replace->color;

      
        if (parent == node)
        {
            parent = replace;
        } 
        else
        {

            if (child)
            {
                child->parent=parent;
            }
            parent->left = child;

            replace->right = node->right;
            node->right=replace;
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
        {
            rbtree_delete_fixup(tree, child, parent);
        }
    //    printf("hre\n");
        tree->del(node->data);
        LB_free(node);

        return 1;
    }

    if (node->left !=NULL)
    {
        child = node->left;
    }
    else
    { 
        child = node->right;
    }   
    parent = node->parent;
 
    color = node->color;

    if (child)
    {
        child->parent = parent;
    }


    if (parent)
    {
        if (parent->left == node)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }
    }
    else
    {
        tree->root = child;
    }

    if (color == BLACK)
    {
        rbtree_delete_fixup(tree, child, parent);
    }
    tree->del(node->data);
    LB_free(node);
    
   // printf("hre\n");
    return 1;
}
RB_Tree_func(int)
RB_Tree_func(double)

#undef RED
#undef BLACK
#undef LB_free
#undef LB_malloc
