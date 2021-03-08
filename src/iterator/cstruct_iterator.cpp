#include<iterator/cstruct_iterator.h>
bool operator==(const Node& node1,const Node& node2)
{

    return (node1.value==node2.value);

}
bool operator!=(const Node& node1,const Node& node2)
{
	if(node1.value!=node2.value)
	{
		return true;
	}
	return false;

}
Node operator++(Node& node)
{
    if(node.Next==NULL)
    {
        Node node2;
        Node_init(&node2);
        node=node2;
        return node2;
    }

    node=*((Node*)node.Next);
    return node;
}
Node operator++(Node &node,int)
{
    Node node1=node;
    if(node.Next==NULL)
    {
        Node node2;
        Node_init(&node2);
        node=node2;
        return node1;
    }

    node=*((Node*)node.Next);
    return node1;
}
Node operator--(Node&node)
{
    if(node.Prev==NULL)
    {
        Node node2;
        Node_init(&node2);
        node=node2;
        return node2;
    }

    node=*((Node*)node.Prev);
    return node;

}
Node operator--(Node&node,int)
{
    Node node1=node;
    if(node.Prev==NULL)
    {
        Node node2;
        Node_init(&node2);
        node=node2;
        return node1;
    }

    node=*((Node*)node.Prev);
    return node1;


}
void* operator*(Node& node)
{
    return node.value;

}
bool operator==(const RB_Tree_Trav&it1,const RB_Tree_Trav&it2)
{
    return it1.it==it2.it;
}
bool operator!=(const RB_Tree_Trav&it1,const RB_Tree_Trav&it2)
{
    return it1.it!=it2.it;
}

RB_Tree_Trav operator++(RB_Tree_Trav&it)
{
    it.next(&it);
    return it;
}
RB_Tree_Trav operator++(RB_Tree_Trav&it,int)
{
    RB_Tree_Trav re=it;
    it.next(&it);
    return re;
}
RB_Tree_Trav operator--(RB_Tree_Trav&it)
{
    it.prev(&it);
    return it;
}
RB_Tree_Trav operator--(RB_Tree_Trav&it,int)
{
    RB_Tree_Trav re=it;
    it.prev(&it);
    return re;
}
void* operator*(RB_Tree_Trav&it)
{
    return it.it->data;
}



bool operator==(const AVL_Tree_Trav&it1,const AVL_Tree_Trav&it2)
{
    return it1.it==it2.it;
}
bool operator!=(const AVL_Tree_Trav&it1,const AVL_Tree_Trav&it2)
{
    return it1.it!=it2.it;
}




AVL_Tree_Trav operator++(AVL_Tree_Trav&it)
{
    it.next(&it);
    return it;
}
AVL_Tree_Trav operator++(AVL_Tree_Trav&it,int)
{
    AVL_Tree_Trav re=it;
    it.next(&it);
    return re;
}
AVL_Tree_Trav operator--(AVL_Tree_Trav&it)
{
    it.prev(&it);
    return it;
}
AVL_Tree_Trav operator--(AVL_Tree_Trav&it,int)
{
    AVL_Tree_Trav re=it;
    it.prev(&it);
    return re;
}
void* operator*(AVL_Tree_Trav&it)
{
    return it.it->data;
}