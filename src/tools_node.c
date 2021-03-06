#include<tools_node.h>
#include<stdio.h>
int node_size(Node* node)
{
    if(node==NULL)
    {
        return 0;
    }
	Node*node1=(Node*)(node->Prev);
	int i=0;
    while(node!=NULL)
    {
        node=(Node*)node->Next;
        i++;
    }
	int j=0;
	while(node1!=0)
	{
		node1=(Node*)(node1->Prev);
		j++;
	}
    return i+j;
}

void free_node(Node *node)
{	
	if(node==NULL)
	{return;}

    Node* node1=node->Next,*node2=node->Prev,*iter;
    while(node1!=NULL)
    {
	iter=node1->Next;
        free(node1);
        node1=iter;
    }
	while(node2!=NULL)
	{
		iter=node2->Prev;
		free(node2);
		node2=iter;
	}
	free(node);

	

}
void free_node_value(Node *node)
{
 	if(node==0)
	{return;}

    Node* node1=node->Next,*node2=node->Prev,*iter;
    while(node1!=NULL)
    {
	iter=node1->Next;
        free(node1->value);
        node1=iter;
    }
	while(node2!=0)
	{
		iter=node2->Prev;
		free(node2->value);
		node2=iter;
	}
	free(node->value);

}
Node* node_find(Node* node,void* value)
{
	Node* re=node;
    while(re!=NULL)
    {
        if(re->value==value)
        {break;}
        re=(Node*)(re->Next);
    }
    return re;
}
//
Node* node_copy(Node* node)
{
	if(node==NULL)
	{
	return NULL;
	}
	Node* node1=(Node*)malloc(sizeof(Node));
	Node* node2=node1;
	Node_init(node1);
    while(node!=NULL)
    {
	    node2->value=node->value;
	    node=(Node*)node->Next;
	    if(node==NULL)
	    {
	        break;
	    }
        Node* node3=(Node*)malloc(sizeof(Node));
	    Node_init(node3);
	    node2->Next=(void*)node3;
	    node3->Prev=(void*)node2;
	    node2=node3;
    }

    return node1;
}

Node* node_overlying(Node*node,void *value)
{
    Node* node1=(Node*)malloc(sizeof(Node));
    Node_init(node1);
    node1->value=value;
    node1->Next=node;
    if(node!=NULL)
    {
        node->Prev=node1;

    }
    return node1;

}
Node* node_pushback(Node* node,void* value)
{
    Node* node1=(Node*)malloc(sizeof(Node));
    Node_init(node1);
    node1->value=value;
    node1->Prev=node;
    if(node!=0)
    {
        node->Next=node1;
    }
    return node1;

}
Node* node_reverse(Node*node)
{
	if(node==NULL)
	{return NULL;}
	else
	{
		if(node->Next!=0)
		{
			while(node->Next!=NULL)
			{
				node=(Node*)node->Next;

			}
			return node;

		}
		else
		{
			while(node->Prev!=0)
			{
				node=(Node*)node->Prev;

			}
			return node;
		}

		
	}

}
void node_eliminate(Node* node)
{
    if(node==NULL)
    {
        return;
    }
    Node* node1=(Node*)node->Prev,*node2=(Node*)node->Next;
    if(node1!=NULL)
    {
        node1->Next=(void*)node2;
    }
    if(node2!=NULL)
    {
        node2->Prev=(void*)node1;
    }
    free(node);
    node=NULL;

}

Node* node_delete_value(Node* node,void* value)
{

    Node* node1=node_find(node,value);

    Node* re=node;
	if(node1==NULL)
	{	
		return re;
	}
    if(node1->Prev==NULL)
    {
        re=(Node*)node1->Next;
    }

    node_eliminate(node1);

    return re;
}

Node* node_splicing(Node*n1,Node*n2)
{

	Node* l1=node_copy(n1);
	Node* l2=node_copy(n2);
	Node* l3=node_reverse(l1);
	if(l1==NULL)
	{return l2;}
	else if(l2==NULL)
	{
		return l1;
	}
	else
	{
		l3->Next=(void*)l2;
		l2->Prev=(void*)l3;
		return l1;
	}
	return NULL;
}
Node* node_union(Node*n1,Node*n2)
{
    Node* re=node_copy(n1); 
    for(Node* nit=n2;nit!=NULL;nit=(Node*)(nit->Next)) 
    {
        if(node_find(re,nit->value)==NULL) 
        {
            re=node_overlying(re,nit->value); 
        } 
    } 
    return re;

}
Node* node_intersection(Node* n1,Node* n2)
{
    Node* re=NULL;
    for(Node* nit=n2;nit!=NULL;nit=(Node*)(nit->Next))
    {
        if(node_find(n1,nit->value)!=NULL)
        {
            re=node_overlying(re,nit->value);
        }
    }
    return re;

}
Node* node_minus(Node* n1,Node* n2)
{
    Node* re=node_copy(n1);

    for(Node* nit=n2;nit!=NULL;nit=(Node*)(nit->Next))
    {
        re=node_delete_value(re,nit->value);
    }
    
    return re;
}
Node* node_bub_sort(Node* n,int (*cmp)(void* a,void* b))
{
    Node* nit=node_reverse(n);
    while(nit!=n)
    {
        Node* nit1=(Node*)(nit->Prev);

        void* v1=nit->value,*v2=nit1->value;
        if(cmp(nit->value,nit1->value)==1)
        {
            nit->value=v2;
            nit1->value=v1;     
        }

        nit=nit1;
    }

    return nit;

}
Node* node_bub_sortn(Node* n,int (*cmp)(void* a,void* b))
{
	Node* re=n;
	int flag=0;
	do{
		flag=0;
       // printf("once\n");
		Node* nit=re;
		while(nit!=NULL&&nit->Next!=NULL)
		{
			Node* nit1=(Node*)(nit->Next);
			if(cmp(nit1->value,nit->value)==1)
			{
               // printf("here\n");
				if(nit==re)
				{
					re=nit1;
				}
				nit1->Prev=nit->Prev;
				if(nit->Prev!=NULL)
				{
					((Node*)(nit->Prev))->Next=nit1;
				}
                nit->Next=nit1->Next;
                if(nit1->Next!=NULL)
                {
                    ((Node*)(nit1->Next))->Prev=nit;
                }
				nit1->Next=nit;
				nit->Prev=nit1;
				
				
				flag=1;

			}
            else
            {
                nit=nit1;
            }
		}
	}while(flag==1);
	return re;
}

Node* node_filter_condition(Node* n,int (*filter_condition)(void* a))
{

    Node*re=node_copy(n);
    Node* nit=re;
    while(nit!=NULL)
    {
        
        if(filter_condition(nit->value)==1)
        {
            if(nit==re)
            {
                re=(Node*)(re->Next);
            }
            Node* temp_nit=nit;
            nit=(Node*)(nit->Next);
            if(temp_nit->Prev!=NULL)
            {
                ((Node*)(temp_nit->Prev))->Next=nit;
            }
            if(nit!=NULL)
            {
                nit->Prev=temp_nit->Prev;
            }
            free(temp_nit);
        }
        else
        {
            nit=(Node*)(nit->Next);
        }
    }

    return re;
   
}
