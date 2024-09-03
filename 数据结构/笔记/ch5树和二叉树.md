# <center>ch5树和二叉树</center>

> 学习树形结构

## 树

> 定义：
>
> 1. 有且仅有一个称之为根的结点
>
> 2. 除根结点之外的其余结点可分为m个互不相交的有限子集，其中每一个子集又是一棵树，并称为根的子树
>
> 树是n个结点的有限集，可以用嵌套集合，凹入表示和广义表表示

## 二叉树

> m = 2
>
> 结点度数小于等于2

### 二叉树性质

1. 二叉树第i层至多有$2^{i-1}$个结点
2. 深度为k的二叉树至多有$2^{k}-1$个结点

3. 任意一棵二叉树度数为2的结点数有$n_2$个，叶子数$n_0$必定为$n_2+1$

​	**$$n_0 = n_2 + 1$$**

4. 具有n个结点的完全二叉树的深度为$\lfloor log_2n\rfloor + 1$（向下取整，不大于它的最大整数）

+ 满二叉树：深度为k，有$2^{k}-1$的结点的二叉树（叶子一个也不少）
+ 完全二叉树：只有最后一层叶子不满，且全部集中在左边（前n-1层是满的）

5. 完全二叉树，从上到下，从左到右编号，编号为i的结点，左孩子必为2i，右孩子编号为2i+1，双亲的编号必为i/2

### 二叉树的顺序存储

+ 实现：按照满二叉树的结点摆好，依次存放二叉树中的数据元素==补图==
+ 特点：结点间关系蕴含在其存储位置中，浪费空间，适用于存满二叉树和完全满二叉树

### 二叉树的链式存储

+ lchild data rchild
+ lchild data parent rchild

### 二叉链表

+ 结构定义

```cpp
typedef struct BiNode{
   TElemType   data;
   struct  BiNode   *lchild,*rchild; //左右孩子指针
}BiNode,*BiTree; 
```

> n个结点的二叉链表中，有n+1个空指针域

==左孩子，右兄弟==



### 三叉链表

+ 结构定义

```cpp
typedef struct TriTNode{  
	TelemType data;
	struct TriTNode *lchild,*parent,*rchild;
}TriTNode,*TriTree;
```



### 遍历二叉树

+ 先序遍历：DLR，先根再左再右

```cpp
Status PreOrderTraverse(BiTree T){
  if(T==NULL) return OK; //空二叉树
  else{    
     cout<<T->data; //访问根结点
     PreOrderTraverse(T->lchild); //递归遍历左子树
     PreOrderTraverse(T->rchild); //递归遍历右子树
    }
}
```



+ 中序遍历：LDR，先左再根再右

```cpp
Status InOrderTraverse(BiTree T){
  if(T==NULL) return OK; //空二叉树
  else{    
     InOrderTraverse(T->lchild); //递归遍历左子树
  	cout<<T->data; //访问根结点
     InOrderTraverse(T->rchild); //递归遍历右子树
    }
}
```





+ 后序遍历：LRD，先左再右再根

```cpp
Status PostOrderTraverse(BiTree T){
  if(T==NULL) return OK; //空二叉树
  else{    
     PostOrderTraverse(T->lchild); //递归遍历左子树
     PostOrderTraverse(T->rchild); //递归遍历右子树
     cout<<T->data; //访问根结点
    }
}
```





+ 遍历算法的分析

  + 时间效率：O(n)
  + 空间效率：O(n)

  

+ 层序遍历：逐层遍历



+ 二叉树遍历算法的应用

  + 计算二叉树的结点总数

  ```cpp
  int NodeCount(BiTree T){
    if(T == NULL ) return 0;  			    else return NodeCount(T->lchild)+NodeCount(T->rchild)+1;
  } 
  ```

  + 二叉树叶子结点总数

  ```cpp
  int LeadCount(BiTree T){
   	if(T==NULL) 	//如果是空树返回0
  		return 0;
  	if (T->lchild == NULL && T->rchild == NULL)
  		return 1; //如果是叶子结点返回1
  	else return LeafCount(T->lchild) + LeafCount(T->rchild);
  }
  ```

  + 计算二叉树深度

  > 如果是空树，则深度为0
  >
  > 递归计算左子树的深度，右子树的深度，二叉树深度是m与n较大者加1



> 重要结论：
>
> 前序序列和中序序列/后序序列和中序序列均能唯一的确定一棵二叉树
>
> 前序序列和后序序列不能唯一的确定一棵二叉树



### 建立二叉树

+ 先序遍历

```cpp
void CreateBiTree(BiTree &T）{
cin>>ch;
if (ch==’#’)   T=NULL;  	//递归结束，建空树
else{
    T=new BiTNode;    T-＞data=ch;                                  	//生成根结点
    CreateBiTree(T-＞lchild);  //递归创建左子树
    CreateBiTree(T-＞rchild); //递归创建右子树
  }												
}		
```



+ 中序遍历



+ 后序遍历





### 线索化二叉树

>解决直接前驱和直接后继只能在遍历中获得的问题，通过第一个结点开始很快就可以遍历整个树
>
>解决方法：增加两个域：fwd和bwd；利用空链表；

+ 方法

  + 有左子树，lchild指向其左孩子，否则，lchild指向其直接前驱（线索）

  + 有右子树，rchild指向其右孩子，否则，rchild指向其直接后继（线索）

  + LTag：若LTag = 0，lchild域指向左孩子，若LTag = 1,lchild域指向前驱

  + RTag：若RTag = 0，rchild域指向右孩子，若RTag = 1,rchild域指向后继

    > lchild LTag data RTag rchild

+ 先序线索二叉树（根左右）

LTag=0, lchild域指向左孩子
LTag=1, lchild域指向其前驱

RTag=0, rchild域指向右孩子
RTag=1,rchild域指向其后继
（左指向前驱，右指向后继）

+ 中序线索二叉树（左根右）
+ 后序线索二叉树（左右根）

+ 补充：指针域是否为空
  + 中序线索树中必有两个指针域为空
  + 先序线索树终端结点的右指针必为空，仅当只有一个根节点或者左子树为空时有两个空指针
  + 后序线索树开始结点的左指针必为空，仅当只有一个根结点或根结点的右子树为空有两个空指针

+ 判断结点是否是叶子节点：ltag = rtag = 1

+ 线索化二叉树，遍历线索二叉树



### 树和森林





### 哈夫曼树

> 设计**长度不等的编码**，使任一字符的编码都不是另一个字符的编码的前缀——**前缀码**
>
> 译码过程：遇0向左，遇1向右；一旦到达叶子节点，译出一个字符，反复由根节点出发，直到译码完成（**左0右1**）

**哈夫曼树构造**

+ 路径：一个节点到另一个结点间的分支构成
+ 路径长度：路径上的分支数目
+ 带权路径长度：结点到根的路径长度*节点上的权
+ 树的带权路径长度：

$$WPL = \sum\limits^n_{k=1} w_k I_k$$

**哈夫曼树是带权路径长度最小的树**

>  总是合并当前值最小的两个
>
> 概率大的用短码，概率小的用长码
>
> **一个有n个叶子节点的Huffman树有2n-1个结点**
>
> 没有度为1的结点











