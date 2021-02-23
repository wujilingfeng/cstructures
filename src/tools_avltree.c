#include<tools_avltree.h>



AVL_Node* avl_increase(AVL_Node* n)
{
    AVL_Node* nn=(AVL_Node*)malloc(sizeof(AVL_Node));
    avl_node_init(nn);
    if(n==NULL)
    {
        return nn;
    }
    AVL_Node* root=n;
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
        while(root->left!=NULL)
        {
            root=root->left;
        }
        root->left=nn;
        nn->parent=root;

    }

    return nn;

}
AVL_Node* my_find(AVL_Tree* tree,void* data)
{
    AVL_Node*n=tree->root;
    if(n==NULL)
    {
        return NULL;
    }
    while(tree->cmp(n->data,data)==0)
    {
        if(n->left==NULL&&tree->cmp(data,n->data)<0)
        {
           return n; 
        }
        if(n->right==NULL&&tree->cmp(data,n->data)>0)
        {
            return n;
        }
        if(n->left==NULL&&n->right==NULL)
        {
            return n;
        }
        if(tree->cmp(data,n->data)>0)
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

AVL_Node* my_insert(AVL_Tree* tree,void* data)
{
    if(tree==NULL)
    {
        return NULL;
    }
    return my_find(tree,data);
}
static AVL_Node* avl_node_overlying(AVL_Node* an,void* v)
{
    AVL_Node* n1=(AVL_Node*)malloc(sizeof(AVL_Node));
    avl_node_init(n1);
    n1->data=v;
    n1->right=an;
    if(an!=NULL)
    {
        an->left=n1;
    }
    return n1;

}
static int compare_two_node(AVL_Node* n1,AVL_Node* n2)
{
    if(n1==NULL||n2==NULL)
    {
        return -1;
    } 
    AVL_Node* temp=n1,*node1=NULL,*node2=NULL;
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
    AVL_Node*nit=NULL,*nit1=NULL;
    if(j>i)
    {
        nit=node2;nit1=node1;
        while(nit!=NULL)
        {   
            if(nit1==NULL||nit->data!=nit1->data)
            {
                if(((AVL_Node*)(nit->data))->parent->left==nit->data)
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
                if(((AVL_Node*)(nit->data))->parent->left==nit->data)
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


AVL_Node* successor(AVL_Node* n)
{
    if(n==NULL)
    {
        return NULL;
    }
    AVL_Node* x=n,*node=NULL;
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
AVL_Node* predecessor(AVL_Node* n)
{ 
    AVL_Node* node=NULL;
    if(n==NULL)
    {
        return NULL;
    } 
    AVL_Node* x=n;
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

void avl_insert(AVL_Tree* tree,void*data)
{
    AVL_Node* n=my_insert(tree,data);
    if(n==NULL)
    {
        AVL_Node* nn=avl_increase(tree->end);
        nn->data=tree->copy(data);
        tree->size++;
        tree->end=nn;
        tree->root=nn;
    } 

    if(tree->cmp(data,n->data)==0)
    {
        tree->del(n->data);
        n->data=tree->copy(data);
    } 
    else
    {
        AVL_Node* nn=avl_increase(tree->end);
        tree->size++;
        tree->end=nn;
        if(nn->parent==n&&((n->left==n&&tree->cmp(data,n->data)<0)||(n->right==nn&&tree->cmp(data,n->data)>0)))
        {
            tree->del(nn->data);
            nn->data=tree->copy(data);
        }
        else
        {
            if(compare_two_node(nn,n)>=0)
            {
                AVL_Node* temp=nn,*temp1=NULL;
                void*data=NULL;
                while(temp!=n)
                {
                    temp1=predecessor(temp);
                    data=temp->data;temp->data=temp1->data;temp1->data=data;
                
                    temp=temp1;
                }
            } 
            else
            {
                AVL_Node*temp=nn,*temp1=NULL;
                void* data=NULL;
                while(temp!=n)
                {
                    temp1=successor(temp);
                    data=temp->data;temp->data=temp1->data;temp1->data=data;

                    temp=temp1;
                }
            }
            n->data=tree->copy(data);
        }
    }
}

