#ifndef TOOLS_INT_MAP_H_
#define TOOLS_INT_MAP_H_
#include "../tools_rbtree.h"
#include "../iterator/cstruct_iterator.h"
#define second_v(it) ((template_v*)(it.second(&it)))
#define second_c(it) ((template_c*)(it.second(&it)))
#define second_f(it) ((template_f*)(it.second(&it)))
#define second_hf(it) ((template_hf*)(it.second(&it)))

class RB_INT_MAP
{
public:
	RB_INT_MAP()
	{
	
		this->init();
	}
	~RB_INT_MAP()
	{
		if(this->tree!=NULL)
		{

			rb_tree_free((this->tree));
		}
		this->tree=NULL;
	
	}
	void init()
	{
		this->tree=(RB_Tree*)malloc(sizeof(RB_Tree));
		rb_tree_init_int((this->tree));
	}
	void clear()
	{
		rb_tree_free(this->tree);
		this->tree=NULL;
	}
	unsigned int size()
	{
		if(this->tree==NULL)
		{
			return 0;
		}
		return tree->size;
	}
	void insert(int i,void*data)
	{
		RB_int rbt;
		rbt.key=i;
		rbt.value=data;
		(this->tree->insert(this->tree,&rbt));

	}
	/*RB_int* operator[](int i)
	{
		RB_int rbt;
		rbt.key=i;
		return (RB_int*)this->tree->find(this->tree,&rbt);
	}*/
	RB_Tree_Trav begin()
	{	RB_Tree_Trav*it=this->tree->begin(this->tree);
		RB_Tree_Trav re=*it;
		free(it);
		return re;
	}
	RB_Tree_Trav rbegin()
	{	RB_Tree_Trav*it=this->tree->rbegin(this->tree);
		RB_Tree_Trav re=*it;
		free(it);
		return re;
	}
	RB_Tree_Trav end()
	{
		RB_Tree_Trav re;
		rb_tree_trav_init(&re);
		return re;
	}
	RB_Tree_Trav find(int i)
	{
		RB_Tree_Trav re;
		rb_tree_trav_init(&re);
		if(this->tree->iterator_init!=NULL)
		{
			this->tree->iterator_init(&re);
		}
		RB_int rbt;
		rbt.key=i;
		re.it=(rb_tree_find(this->tree,&rbt));	
		return re;
	}
	void erase(RB_Tree_Trav it)
	{
		this->tree->erase(this->tree,it.it->data);	
	}
	void print_self()
	{
		printf("size:%d\n",this->tree->size);
		int i=0;
		for(auto it=this->begin();it!=this->end();it++)
		{
			i++;
        	printf("%d   ",*((int*)it.first(&it)));
		}	


    	printf("end size :%d\n",i);
	}	
	RB_Tree*tree;

};



#endif
