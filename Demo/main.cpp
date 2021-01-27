#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<tools_rbtree.h>

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
    RB_Tree*tree=(RB_Tree*)LB_malloc(sizeof(RB_Tree));
    RB_Tree_init_int(tree);
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
    RB_Tree_free(tree);

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
int main(int argc,char**argv)
{   
    memery_leak_from_RB_Tree_compute=0;
    memery_leak_from_RB_Tree_compute_f=0;
    RB_INT_MAP rim;
    rim.insert(3,NULL); 
    
    rim.print_self();
    rim.clear();

    Node* n1=NULL,*n2=NULL;
    Node* n3=node_union(n1,n2);
    n3=node_intersection(n1,n2); 
    test_bub();


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
    printf("end\nleak m :%d,leak f:%d\n",memery_leak_from_RB_Tree_compute,memery_leak_from_RB_Tree_compute_f);
    return 0;
}
