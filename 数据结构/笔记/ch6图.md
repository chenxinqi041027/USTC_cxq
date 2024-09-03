# <center>ch6图</center>

> 图形结构，多个对多个
>
> Graph = (V,E)

## 概念

+ 完全图：任意两个点都有一条边相连
+ 稀疏图，稠密图
+ 网：边/弧带权的图
+ 邻接，关联
+ 路径，路径长度，回路
+ 简单路径，非简单路径（只有路径起点个终点可以相同/相同）
+ 连通图
  + 极大连通子图：加入顶点->不连通
  + 极小连通子图：删除边->不连通
  + 生成树：包含无向图G的所有顶点的极小连通子图

> 约定不允许有反身边（环），不允许有平行边（圈）

+ 存储结构
  + 顺序存储（数组表示，邻接矩阵）
  + 链式存储（邻接表，邻接多重表，十字链表）



## 存储结构

### 邻接矩阵

> 相邻为1，不相邻为0
>
> 自己和自己不相邻（对角元素为0）

性质：

+ 无向图邻接矩阵对称
+ 有向图邻接矩阵可能不对称（列表示入度边）
  + 出度=第i行元素之和
  + 入度=第i列元素之和
  + 度=行，列元素之和
+ 网邻接矩阵的表示
  + 相邻，用边权表示
  + 不相邻用无穷

> 优点：容易实现操作
>
> 缺点：n个顶点需要n*n个单元存储边，空间效率为O(n^2)，浪费空间







### 邻接链表（链式表示）

> 头结点：  data  firstarc
>
> 表结点：  adjvex  nextarc  info//邻接点域，链域，数据域

> 无向图：空间效率为O(n+2e)
>
> 有向图：空间效率为O(n+e)

> 优点：空间效率高
>
> 缺点：判断是否有弧或者边，没有邻接矩阵方便

> 区别：
>
> 邻接表不唯一，邻接矩阵唯一
>
> 邻接矩阵用于稠密图，邻接表用于稀疏图

```cpp
#define MVNum 100                        	//最大顶点数 
typedef struct ArcNode{                		//边结点 
    int adjvex;                          		//该边所指向的顶点的位置 
    struct ArcNode * nextarc;          	//指向下一条边的指针 
    OtherInfo info;                      	              //和边相关的信息 
}ArcNode; 
typedef struct VNode{ 
    VerTexType data;                    	//顶点信息 
    ArcNode * firstarc;                	//指向第一条依附该顶点的边的指针 
}VNode, AdjList[MVNum];               	//AdjList表示邻接表类型 
typedef struct{ 
    AdjList vertices;                 		//邻接表 
    int vexnum, arcnum;              		//图的当前顶点数和边数 
}ALGraph; 
```





### 十字链表

> 用于有向图



## 遍历

### 深度优先 DFS

> 一条路走到尽头

+ 访问起始点
+ 第1个未访问的邻接点，深度遍历此邻接点
+ 访问过则再找第2个

#### 递归算法实现

+ 邻接矩阵

```cpp
void DFS(AMGraph G, int v){        		//图G为邻接矩阵类型 
  cout<<v;  visited[v] = true;  		//访问第v个顶点
  for(w = 0; w< G.vexnum; w++)  	//依次检查邻接矩阵v所在的行  
        if((G.arcs[v][w]!=0)&& (!visited[w]))  
            DFS(G, w); 
      //w是v的邻接点，如果w未访问，则递归调用DFS 
} 
```

+ 邻接链表

```cpp
void DFS(ALGraph G, int v){        		//图G为邻接表类型 
  cout<<v;  visited[v] = true;    		//访问第v个顶点
  p= G.vertices[v].firstarc;     //p指向v的边链表的第一个边结点 
while(p!=NULL){              	//边结点非空 
  w=p->adjvex;               	//表示w是v的邻接点 
  if(!visited[w])  DFS(G, w); 	//如果w未访问，则递归调用DFS 
  p=p->nextarc;                	//p指向下一个边结点 
 } 
} 
```

+ 效率分析
  + 邻接矩阵：时间复杂度O(n^2)
  + 邻接表：时间复杂度O(n+e)
  + 稠密图，邻接矩阵深度遍历，稀疏图邻接表深度遍历











### 广度优先 BFS

> 层次搜索

+ 从顶点出发，访问v，将v入队
+ 队列不空则
  + 队头顶点出队
  + 检查队头顶点的所有未访问的邻接点并入队



#### 队列实现广度优先

```cpp
void BFS (Graph G, int v){ 
    //按广度优先非递归遍历连通图G 
    cout<<v; visited[v] = true;     		//访问第v个顶点
    InitQueue(Q);              			//辅助队列Q初始化，置空         
    EnQueue(Q, v);            			//v进队 
    while(!QueueEmpty(Q)){   		//队列非空 
       DeQueue(Q, u);        			//队头元素出队并置为u 
       for(w = FirstAdjVex(G, u); w>=0; w = NextAdjVex(G, u, w)) 
       if(!visited[w]){               	//w为u的尚未访问的邻接顶点 
             	cout<<w; visited[w] = true;	
		EnQueue(Q, w); //w进队 
          }//if 
    }//while 
}//BFS 
```

+ 效率分析
  + 邻接矩阵：O(n^2)
  + 邻接表：O(n+e)



## 最小生成树

> 在多个生成树中，寻找一个各边权值之和最小的生成树

### Prim算法

> 归并顶点，与边数无关

+ 构造顶点集
+ 在连接红（已经访问过）白（未访问过）点集的紫边中选择最轻的一边，直至U=V



> 时间复杂度为O(n^2)



### Kruskal算法

> 归并边





## 最短路径

### Dijkstra算法——单源最短路径







### Floyd算法——所有顶点之间的最短路径









### 有向无环图及其应用

+ AOV图——用顶点表示活动的网络
+ AOE图——用边表示活动的网络



#### 拓扑排序

+ 无前驱结点的顶点优先

```cpp
NonPreFirstTopSort（G）{
          while( G中有入度为0的顶点 ) do {
                 从G中选1个入度为0的顶点v输出之；
                 从G中删v及其出边，出边终点的入度减1；
          }
          if ( 输出的顶点数 < | V(G) | ) then
                 Error ( “G有环，排序失败” );
     }
```



> 时间分析：
>
> 排序成功时最大：初始化O(n+e),每个边表结点被检查1次，O(n+e)



+ 无后继结点的顶点优先（输出逆拓扑排序）

```cpp
NonSuccFirstTopSort（G）{ //应选G的逆邻接表
          while( G中有出度为0的顶点 ) do {
                 从G中选1个出度为0的顶点v输出之；
                 从G中删v及其入边，入边起点的出度减1；
          }
          if ( 输出的顶点数 < | V(G) | ) then
                 Error ( “G有环，排序失败” );
     }
```





+ dfs遍历（输出逆拓扑排序）

```cpp
DFSTopSort（G，i，T）{  //在DFSTraverse中调用此算法，T是栈
                 visited[i]=TRUE; //访问i
                 for (所有i的邻接点j）//即< i, j> ∈E(G)
                        if ( !visited[j] )
                                DFSTopSort(G,j,T)；
                 Push（&T, i）//从i出发的搜索已完成，输出i
     }
```



+ 应用
  + 最早发生时间：最长路径——e(ai) = Ve(j)
  + 最迟发生时间：必须发生的时刻——l(ai) = Vl(k) - dut(j,k)
  + 关键活动：最早开始时间等于最迟开始时间的活动
  + 关键路径：源点到收点的最长路径，或者全部由关键活动构成的路径

ve(j) = Max{ve(i) + dut(<i,j>)},<i,j>在T中

vl(i) = Min{vl(j) - dut(<i,j>)},<i,j>在S中

**?????????????????????????????????????????**





































