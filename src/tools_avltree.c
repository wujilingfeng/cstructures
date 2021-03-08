#include<tools_avltree.h>


//return the newly added node
static AVL_Tree_Node* avl_increase(AVL_Tree_Node* n)
{
    AVL_Tree_Node* nn=(AVL_Tree_Node*)malloc(sizeof(AVL_Tree_Node));
    avl_node_init(nn);
    // if n=null,which means there is no node
    if(n==NULL)
    {
        return nn;
    }
    AVL_Tree_Node* root=n;

    //recursion 
    while(root->parent!=NULL&&root->parent->right==root)
    {
        root=root->parent;
    } 
    if(root->parent!=NULL)
    {

        if(root->parent->right==NULL)
        {
            root=root->parent;
            root->right=nn;
            nn->parent=root;
        }
        else
        {
            root=root->parent->right;
            while(root->left!=NULL)
            {
                root=root->left;
            }
            root->left=nn;
            nn->parent=root;
        }

    }
    else
    {
    //if the node of root is a root of avltree
        while(root->left!=NULL)
        {
            root=root->left;
        }
        root->left=nn;
        nn->parent=root;

    }

    return nn;

}

//return last added node
static AVL_Tree_Node* avl_decrease(AVL_Tree_Node* n)
{
    if(n==NULL||n->parent==NULL)
    {
        return NULL;
    }
    AVL_Tree_Node* root=n;
    while(root->parent!=NULL&&root->parent->left==root)
    {
        root=root->parent;
    } 
    if(root->parent!=NULL)
    {
        root=root->parent->left;
        while(root->right!=NULL)
        {
            root=root->right;
        }
        return root;
    }
    else
    {
        while(root->right!=NULL)
        {
            root=root->right;
        }
        return root;
    }

}

//find the node which vale equals data
//or find the node which is " closest  to data  "
static AVL_Tree_Node* my_find(AVL_Tree* tree,void* data)
{
    if(tree==NULL)
    {
        return NULL;
    } 
    AVL_Tree_Node*n=tree->root;
    if(n==NULL)
    {
        return NULL;
    }
    int cmp_i=0;
    while((cmp_i=tree->cmp(data,n->data))!=0)
    {
        if(n->left==NULL&&cmp_i<0)
        {
           return n; 
        }
        if(n->right==NULL&&cmp_i>0)
        {
            return n;
        }
        if(n->left==NULL&&n->right==NULL)
        {
            return n;
        }
        if(cmp_i>0)
        {
            n=n->right;
        }
        else
        {
            n=n->left;
        }

    }

    return n;
}

static inline AVL_Tree_Node* avl_find(AVL_Tree* tree,void* data)
{
    AVL_Tree_Node* n=my_find(tree,data);
    if(tree->cmp(data,n->data)==0)
    {
        return n;
    }

    return NULL;
}

void* avl_findn(AVL_Tree* tree,void* data)
{
    AVL_Tree_Node* n=avl_find(tree,data);
    if(n!=NULL)
    {
        return n->data;
    }
    return NULL;
}
//
static AVL_Tree_Node* avl_node_overlying(AVL_Tree_Node* an,void* v)
{
    AVL_Tree_Node* n1=(AVL_Tree_Node*)malloc(sizeof(AVL_Tree_Node));
    avl_node_init(n1);
    n1->data=v;
    n1->right=an;
    if(an!=NULL)
    {
        an->left=n1;
    }
    return n1;

}
//return n1> n2 ?
static int compare_two_node(AVL_Tree_Node* n1,AVL_Tree_Node* n2)
{
 
    if(n1==NULL||n2==NULL)
    {
        return -1;
    }
    if(n1==n2)
    {
        return 0;
    }
    AVL_Tree_Node* temp=n1,*node1=NULL,*node2=NULL;
    int i=0;
    while(temp!=NULL)
    {
        node1=avl_node_overlying(node1,temp);
        temp=temp->parent;
        i++;
    }
    temp=n2;
    int j=0;
    while(temp!=NULL)
    {
        node2=avl_node_overlying(node2,temp);
        temp=temp->parent;
        j++;
    }
    AVL_Tree_Node*nit=NULL,*nit1=NULL;
    if(j>i)
    {
        nit=node2;nit1=node1;
        while(nit!=NULL)
        {   
            if(nit1==NULL||nit->data!=nit1->data)
            {
                if(((AVL_Tree_Node*)(nit->data))->parent->left==nit->data)
                {

                    return 1;
                }
                else
                {
                    return -1;
                }
            }
            nit=nit->right;
            nit1=nit1->right;
        }
    } 
    else
    {
        nit=node1;nit1=node2;
        while(nit!=NULL)
        {   
            if(nit1==NULL||nit->data!=nit1->data)
            {
                if(((AVL_Tree_Node*)(nit->data))->parent->left==nit->data)
                {

                    return -1;
                }
                else
                {
                    return 1;
                }
            }
            nit=nit->right;
            nit1=nit1->right;
        }
    }

    return 0;
}

//next node which greater than n
AVL_Tree_Node* successor(AVL_Tree_Node* n)
{

    if(n==NULL)
    {
        return NULL;
    }
    AVL_Tree_Node* x=n,*node=NULL;
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
        node=x->parent;
        while(node!=NULL&&(x==node->right))
        {
            x=node;
            node=node->parent;
        }
        return node;

    }
    return node;
}
AVL_Tree_Node* predecessor(AVL_Tree_Node* n)
{ 
    if(n==NULL)
    {
        return NULL;
    } 
    AVL_Tree_Node* x=n,*node=NULL;
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
        node=x->parent;
        while((node!=NULL)&&(x==node->left))
        {
            x=node;
            node=node->parent;
        }
        return node;
    }
    return node;
}
//
void avl_insert(AVL_Tree* tree,void*data)
{
    //printf("begin insert\n");
    AVL_Tree_Node* n=my_find(tree,data);
    //printf("here1\n");
    if(n==NULL)
    {
        AVL_Tree_Node* nn=avl_increase(tree->end);
        nn->data=tree->copy(data);
        tree->size++;
        tree->end=nn;
        tree->root=nn;
        return;
    } 
     //printf("here2\n");  
    int cmp_i=0;
    if((cmp_i=tree->cmp(data,n->data))==0)
    {
        tree->del(n->data);
        n->data=tree->copy(data);
    } 
    else
    {
        //printf("hree3\n");
        AVL_Tree_Node* nn=avl_increase(tree->end);
        tree->size++;
        tree->end=nn;
        if(nn->parent==n&&((n->left==nn&&cmp_i<0)||(n->right==nn&&cmp_i>0)))
        {
            tree->del(nn->data);
            nn->data=tree->copy(data);
        }
        else
        {
        //printf("hree4\n");
            AVL_Tree_Node* temp=nn,*temp1=NULL;
            void*temp_data=NULL;
            if(compare_two_node(nn,n)>=0)
            {
               // printf("end comp1\n");
                while(temp!=n)
                {
                    temp1=predecessor(temp);
                    temp_data=temp->data;temp->data=temp1->data;temp1->data=temp_data;
                
                    temp=temp1;
                }
            } 
            else
            {
              //  printf("end comp2\n");
                while(temp!=n)
                {
                    temp1=successor(temp);
                    temp_data=temp->data;temp->data=temp1->data;temp1->data=temp_data;

                    temp=temp1;
                }
            //    printf("end end\n");
            }
            n->data=tree->copy(data);
          //  printf("ennnnd\n");
        }
    }
}
//remove and release n from tree
void avl_delete_node(AVL_Tree* tree,AVL_Tree_Node* n)
{
    if(n==NULL||tree==NULL||tree->end==NULL)
    {
        return ;
    }
    AVL_Tree_Node* nn=avl_decrease(tree->end),*nn1=tree->end;
    tree->end=nn;
    if(nn1!=n)
    {
        AVL_Tree_Node* temp=n,*temp1=NULL;
        void* data=NULL;
        if(compare_two_node(nn1,n)>0)
        {
           
            while(temp!=nn1)
            {
                temp1=successor(temp);
                data=temp->data;
                temp->data=temp1->data;
                temp1->data=data;
                temp=temp1;

            } 
        }
        else
        {
            while(temp!=nn1)
            {
                temp1=predecessor(temp);
                data=temp->data;
                temp->data=temp1->data;
                temp1->data=data;
                temp=temp1;

            } 
        }
    } 
    AVL_Tree_Node* r=nn1->parent;
    if(r==NULL)
    {
        tree->root=NULL;
    } 
    else
    {
        if(r->left==nn1)
        {
            r->left=NULL;
        }
        else
        {
            r->right=NULL;
        }
        nn1->parent=NULL;
    }

   
    tree->del(nn1->data);
    free(nn1);

}

void avl_delete_data(AVL_Tree* tree,void* data)
{

     AVL_Tree_Node* n= my_find(tree,data);
     if(tree->cmp(n->data,data)==0&&n!=NULL)
     {
         avl_delete_node(tree,n);
     }

 }
static void  avl_tree_free_one_node(AVL_Tree* tree,AVL_Tree_Node*n)
{
    if(n==NULL||tree==NULL)
    {
        return;
    }
    if(n->left!=NULL)
    {
        avl_tree_free_one_node(tree,n->left);
    }
    if(n->right!=NULL)
    {
        avl_tree_free_one_node(tree,n->right);
    }
    tree->del(n->data);
    free(n);


}
void avl_tree_free(AVL_Tree* tree)
{
    if(tree==NULL)
    {
        return ;
    }
    avl_tree_free_one_node(tree,tree->root);
    free(tree);
}
void * avl_next(struct AVL_Tree_Trav* trav)
{
    if(trav->it==NULL)
    {
        return NULL;
    }
    AVL_Tree_Node* node=successor(trav->it);

    trav->it=node;
    if(node!=NULL)
    {
        return node->data;
    }
    return NULL;
}
void* avl_prev(struct AVL_Tree_Trav *trav)
{
    if(trav->it==NULL)
    {
        return NULL;
    }
    AVL_Tree_Node* node=predecessor(trav->it);
    trav->it=node;
    if(node!=NULL)
    {
        return node->data;
    }
    return NULL;
}

AVL_Tree_Node* avltree_minimum(AVL_Tree* tree)
{
    AVL_Tree_Node *node=NULL;

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

    return NULL;
}
static AVL_Tree_Node* avltree_maximum(AVL_Tree *tree)
{
    AVL_Tree_Node *node=NULL;

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
    return NULL;
}

AVL_Tree_Trav* avl_tree_begin(AVL_Tree* tree)
{
   AVL_Tree_Trav*re=(AVL_Tree_Trav*)malloc(sizeof(AVL_Tree_Trav));
   avl_trav_init(re);
   if(tree->iterator_init!=NULL)
   {
        tree->iterator_init(re);
   }

   re->it=avltree_minimum(tree); 
   return re;
}
AVL_Tree_Trav* avl_tree_rbegin(AVL_Tree* tree)
{
   AVL_Tree_Trav*re=(AVL_Tree_Trav*)malloc(sizeof(AVL_Tree_Trav));
   avl_trav_init(re);
   if(tree->iterator_init!=NULL)
   {
        tree->iterator_init(re);
   }
   re->it=avltree_maximum(tree);
   return re;
}
AVL_Tree_func(int)