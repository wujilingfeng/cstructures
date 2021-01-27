#### CSTRUCTURES
* c语言的红黑数，和链表
* c++遍历接口

#### COMPILER

本库使用xmake编译，在根目录执行

xmake for windows mingw(假设你已配置好mingw)

```bash
xmake f -p mingw -a arm64
make -v
```

xmake for windows cl(vs的编译器)

```bash
xmake 
```

xmake for cmake

```bash
xmake f -p mingw -a arm64
xmake project -k cmake
```

xmake for vs

```bash
xmake project -k vsxmake -m release
```

xmake for linux

```
xmake
```

#### TUTORIAL

##### Node

一下当节点Node* n表示链表时，均表示以当前节点n为开始节点并向下遍历。

| 接口                                                         | 意义                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| node_init(Node*)                                             | 初始化节点                                                   |
| free_node_value(Node*)                                       | 释放节点链表所有的value内存(以当前节点为开始节点，向下遍历)  |
| free_node(Node*)                                             | 释放节点链表的内存(以当前节点为开始节点，向下遍历)           |
| node_find(Node\*n,void\*value)                               | 返回当前链表中值等于value的节点(以n节点为开始节点，向下遍历)，没有找到时返回NULL |
| Node\*node_copy(Node\*)                                      | 复制当前链表并返回                                           |
| int node_size(Node*)                                         | 返回链表的长度                                               |
| Node\*node_overlying(Node\*n,void\*v)                        | 给当前链表n向前插入值为v的节点，返回链表的开始节点(请确保n是链表开端) |
| Node\*node_pushback(Node\*n,void\*v)                         | 给当前链表n向后插入值为v的节点，返回链表的末端节点(请确保n时链表末端) |
| Node\* node_reverse(Node\*)                                  | 输入链表的开端或末端，返回链表的末端或开端                   |
| void node_eliminate(Node\*n)                                 | 假设n时某链表的节点，从链表中删除并释放节点n                 |
| Node\*node_delete_value(Node\*n,void\*v)                     | 删除并释放链表n中值等于v的节点，返回链表的开端               |
| Node\*node_splicing(Node\*,Node\*)                           | 复制两个链表，并拼接它们，返回拼接后的链表                   |
| Node\* node_union(Node\*n1,Node\*n2)                         | 返回两个链表的并（返回的链表的内存和n1,n2无关）              |
| Node\* node_intersection(Node\* n1,Node* n2)                 | 返回两个链表的交                                             |
| Node\*node_minus(Node\* n1,Node\* n2)                        | 返回链表n1-n2的集合                                          |
| Node\* node_bub_sortn(Node\*n,int(\*cmp)(void\* a,void\* b)) | 对链表进行冒泡排序(从大到小)，返回排序后的链表。cmp返回1表示大于，0表示等于,-1表示小于 |
| Node\* node_filter_condition(Node\*n,int (\*filter_condition)(void\*,)) | 从链表中删除filter_condition=1的节点，返回的链表和n无内存关联 |
|                                                              |                                                              |
|                                                              |                                                              |

在上面的接口中除了node_delete_value,node_bub_sortn,node_reverse,node_overlying, node_pushback返回的链表的内存和输入链表相关，其他的均无关。

##### RB_Tree

红黑树的接口采用宏进行类似c++的模板扩展，比如:如果你想要获得适配int类型的接口，你需要在头文件中加入一行RB_Tree_func_declare(int),那么就会在头文件展开int类型接口的声明，并在源文件.c中加入一行RB_Tree_func(int),那么就会在源文件中展开定义。

此时你就可以调用RB_Tree_init_int()就会初始化红黑树的内部函数指针为适配int的函数指针。然后你就可以对这颗红黑树操作了。

以下时RB_Tree内部成员的意义

| 接口                                          | 意义                                               |
| --------------------------------------------- | -------------------------------------------------- |
| size                                          | 树的节点数                                         |
| int (\*cmp)(const void\* ,const void\*)       | 值的比较函数，1表示大于，0表示等于，-1表示小于     |
| void\* (* copy)(void\*)                       | 树的复制j节点data的函数                            |
| void (\* del)(void\*)                         | 树 的释放节点内部data的函数                        |
| void\* (\*find)(struct  RB_Tree\*,void\*v)    | 查找树值为v的节点                                  |
| void\*(\* insert)(strcut RB_Tree\*,void\*v)   | 插入树以copy(v)为值的节点,copy正是上面的从copy函数 |
| int(\* erase)(RB_Tree\* tree,void\* data)     | 释放树以data为值的节点,释放函数时上面的del函数     |
| struct RB_Trav\*(\* begin)(struct RB_Tree\*)  | 返回树的遍历结构体，RB_Trav指向开端                |
| struct RB_Trav\*(\* rbegin)(struct RB_Tree\*) | 返回树的遍历结构体，RB_Trav指向末端                |
| void(\iterator_init)(struct RB_Trav\*)        | 初始化RB_Trav的函数                                |

一般来说，上面的函数只有size ,find ,insert,erase,begin,rbegin是用户用到的。

RB_Trav的接口:

| 接口                               | 意义                                 |
| ---------------------------------- | ------------------------------------ |
| tree                               | 指向的树                             |
| it                                 | 当前迭代器指向的节点                 |
| void\*(\*next)(struct RB_Trav\*)   | 使it指向下一个节点，然后返回it的data |
| void\*(\*prev)(struct RB_Trav\*)   | 使it指向上一个节点，然后返回it的data |
| void\*(\*first)(struct RB_Trav\*)  | 仿std::map接口，返回data的key部分    |
| void\*(\*second)(struct RB_Trav\*) | 仿std::map接口，返回data的value部分  |
|                                    |                                      |

##### c++ iterator

库也提供了非常简单的c++的迭代器，

```c
for(Node it=*n;*nit!=NULL;nit++)
{}
for(RB_Trav it=*rt;it.it!=NULL;it++)
{
    
}

```





