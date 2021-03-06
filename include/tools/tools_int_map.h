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

			RB_Tree_free((this->tree));
		}
		this->tree=NULL;
	}
	void init()
	{
		this->tree=(RB_Tree*)malloc(sizeof(RB_Tree));
		RB_Tree_init_int((this->tree));
	}
	void clear()
	{
		RB_Tree_free(this->tree);
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
	RB_int* insert(int i,void*data)
	{
		RB_int rbt;
		rbt.key=i;
		rbt.value=data;
		return (RB_int*)this->tree->insert(this->tree,&rbt);

	}
	/*RB_int* operator[](int i)
	{
		RB_int rbt;
		rbt.key=i;
		return (RB_int*)this->tree->find(this->tree,&rbt);
	}*/
	RB_Trav begin()
	{	RB_Trav*it=this->tree->begin(this->tree);
		RB_Trav re=*it;
		free(it);
		return re;
	}
	RB_Trav rbegin()
	{	RB_Trav*it=this->tree->rbegin(this->tree);
		RB_Trav re=*it;
		free(it);
		return re;
	}
	RB_Trav end()
	{
		RB_Trav re;
		RB_Trav_init(&re);
		return re;
	}
	RB_Trav find(int i)
	{
		RB_Trav re;
		RB_Trav_init(&re);
		if(this->tree->iterator_init!=NULL)
		{
			this->tree->iterator_init(&re);
		}
		RB_int rbt;
		rbt.key=i;
		re.it=(RB_find1(this->tree,&rbt));	
		return re;
	}
	void erase(RB_Trav it)
	{
		this->tree->erase(this->tree,it.it->data);	
	}
	void print_self()
	{
		printf("size:%d\n",this->tree->size);
		for(auto it=this->begin();it!=this->end();it++)
		{

        	printf("%d   ",*((int*)it.first(&it)));
		}	


    	printf("\n");
	}	
	RB_Tree*tree;

};



#endif
