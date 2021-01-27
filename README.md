#### CSTRUCTURES
* c语言的红黑数，和链表
* c++遍历接口

#### compiler

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

