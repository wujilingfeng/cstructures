#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<tools_rbtree.h>
#include<tools_avltree.h>
#include <tools/tools_int_map.h>

int memery_leak_from_RB_Tree_compute;
int memery_leak_from_RB_Tree_compute_f;
/*typedef struct rb_t
{
    int key;
    void *value;

}rb_t;
static void*t_copy(void* p)
{
    void* dup_p=LB_malloc(sizeof(rb_t));
    memmove(dup_p,p,sizeof(rb_t));
    return dup_p;
}
static int t_cmp(const void* p1,const void* p2)
{
   rb_t* q1=(rb_t*)p1,*q2=(rb_t*)p2;
   if(q1->key>q2->key)
   {
        return 1;
   }
   else if(q1->key<q2->key)
   {
        return -1;
   }
   return 0;
}
*/

void test_rb()
{
    RB_Tree*tree=(RB_Tree*)malloc(sizeof(RB_Tree));
    rb_tree_init_int(tree);
    RB_int rbt,*rbt1;
    for(int i=0;i<99;i++)
    {
        rbt.key=i;
        tree->insert(tree,&rbt);
    }
   // print_self(tree);
    rbt.key=240;
    rbt1=(RB_int*)(tree->find(tree,&rbt));
    tree->insert(tree,&rbt);
   // print_self(tree);
    if(rbt1==NULL)
    {
        printf("dfsdfdn\n");
    }
    rb_tree_free(tree);

   /* RB_Tree* tree=(RB_Tree*)LB_malloc(sizeof(RB_Tree));
    RB_Tree_init(tree);
    tree->cmp=t_cmp;
    tree->copy=t_copy;
    rb_t t1;
    t1.key=3;
    tree->insert(tree,&t1);
    t1.key=2;
    tree->insert(tree,&t1);
    t1.key=-3;
    tree->insert(tree,&t1);
    t1.key=0;
    tree->insert(tree,&t1);
    t1.key=99;
    tree->insert(tree,&t1);
    t1.key=-82;
    tree->insert(tree,&t1);
    for(int i=0;i<34;i++)
    {
        t1.key=i;
        tree->insert(tree,&t1);
    }  
    print_self(tree);
    t1.key=20;
    tree->erase(tree,&t1);
    t1.key=-100;
    tree->erase(tree,&t1);
    print_self(tree);*/
}
int cmp_int(void *a,void* b)
{
    int *a1=(int*)a,* b1=(int*)b;
    if(*a1==*b1)
    {
        return 0;
    } 
    else if(*a1>*b1)
    {
        return 1;
    }
    else
    {
        return -1;
    }

}
void test_bub()
{
    Node* node=NULL;
    int * value=(int*)malloc(sizeof(int));
    *value=8;

    node=node_overlying(node,value);
    value=(int*)malloc(sizeof(int));
    *value=3;
    
    node=node_overlying(node,value);


    value=(int*)malloc(sizeof(int));
    *value=5;
    node=node_overlying(node,value);
    
    value=(int*)malloc(sizeof(int));
    *value=-1;
    
    node=node_overlying(node,value);

    for(Node* nit=node;nit!=NULL;nit=(Node*)(nit->Next))
    {
        printf("v:%d ",*((int*)(nit->value)));
    }
    printf("\n");
    node=node_bub_sortn(node,cmp_int);
    printf("end\n");
    for(Node* nit=node;nit!=NULL;nit=(Node*)(nit->Next))
    {
        printf("v:%d ",*((int*)(nit->value)));
    }
    printf("\n");



}

void test_avltree()
{
    AVL_Tree * tree=(AVL_Tree*)malloc(sizeof(AVL_Tree));
    avl_tree_init_int(tree);
    AVL_int at,*at1;
    at.key=-18;tree->insert(tree,&at);

    //printf("tree size:%d\n",tree->size);
    at.key=5;tree->insert(tree,&at);
    at.key=7;tree->insert(tree,&at);
    at.key=-9;tree->insert(tree,&at);
    at.key=0;tree->insert(tree,&at);
    at.key=-50;tree->insert(tree,&at);
    at.key=3;tree->insert(tree,&at);
    at.key=8;tree->insert(tree,&at);

    at.key=100;tree->insert(tree,&at);
    at.key=-100;tree->insert(tree,&at);
    at.key=50;tree->insert(tree,&at);
    at.key=26;tree->insert(tree,&at);
    at.key=75;tree->insert(tree,&at);
    at.key=0;tree->erase(tree,&at);
    at.key=26;tree->erase(tree,&at);
    at.key=50;tree->erase(tree,&at);
    at.key=3;
    //printf("tree size:%d\n",tree->size);
    at1=(AVL_int*)(tree->find(tree,&at));
    if(at1!=NULL)
    {
        printf("chenggong:%d\n",at1->key);
    } 
    avl_tree_free(tree);
}
int main(int argc,char**argv)
{   
    memery_leak_from_RB_Tree_compute=0;
    memery_leak_from_RB_Tree_compute_f=0;
    RB_INT_MAP rim;
    rim.insert(-18,NULL); 
    rim.insert(5,NULL);
    rim.insert(7,NULL);
    rim.insert(-9,NULL);
    rim.insert(0,NULL);
    rim.insert(-50,NULL);
    rim.insert(3,NULL);
    rim.insert(8,NULL);
    rim.insert(100,NULL);
    rim.insert(-100,NULL);
    rim.insert(50,NULL);
    rim.insert(26,NULL);
    rim.insert(75,NULL);
    rim.insert(35,NULL);
    rim.insert(80,NULL);
    rim.insert(20,NULL);
    rim.insert(90,NULL);
    rim.insert(-95,NULL);
    rim.insert(-36,NULL);
    rim.insert(-77,NULL);
    rim.insert(45,NULL);
    rim.insert(101,NULL);
    rim.insert(103,NULL);
    rim.insert(107,NULL);
    rim.insert(110,NULL);
    rim.insert(111,NULL);
    rim.insert(112,NULL);
    rim.insert(113,NULL);
    RB_int rbt;rbt.key=107;
    rim.tree->erase(rim.tree,&rbt);
    rbt.key=0;
    rim.tree->erase(rim.tree,&rbt);
    rbt.key=80; 

    rim.tree->erase(rim.tree,&rbt);
            //printf("fdfdsfds\n") rim.tree->erase(rim.tree,&rbt);;

    rim.print_self();
    rim.find(113);
    rim.clear();

    Node* n1=NULL,*n2=NULL;
    Node* n3=node_union(n1,n2);
    n3=node_intersection(n1,n2); 
    test_bub();

    //AVL_Tree * at=(AVL_Tree*)malloc(sizeof(AVL_Tree));
    //avl_tree_init(at);
    
    //printf("fdsfdsfsdfffffffffffff\n");
    // AVL_Node* an1=(AVL_Node*)malloc(sizeof(AVL_Node));
    // avl_node_init(an1);
    // if(NULL)
    // {
    //     printf("shi\n");
    // }
    // else
    // {
    //     printf("fdsfdsf\n");
    // }
   /// node_bub_sortn(Node* n,int (*cmp)(void* a,void* b));

   // rbt1=(RB_int*)(tree->find(tree,&rbt));
   // printf("find:%d\n",rbt1->key);
    /*printf("size:%d\n",tree->size);
    t1.key=30;
    tree->erase(tree,&t1);
    printf("size:%d\n",tree->size);*/
   //printf("size:%d\n",tree->size);
   // printf("%ld\n",tree->size);

  //  RB_Tree_free(tree);

    //RB_Tree_free(tree);
    test_avltree();
    printf("end\nleak m :%d,leak f:%d\n",memery_leak_from_RB_Tree_compute,memery_leak_from_RB_Tree_compute_f);
    return 0;
}
