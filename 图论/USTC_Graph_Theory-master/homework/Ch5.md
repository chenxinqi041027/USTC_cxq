# Ch5

## 1
> 分别求出$K_{2n}$和$K_{n,n}$中不同完美匹配的个数。

$K_{2n}$的完备匹配个数等于将$2n$个元素划分成$n$个大小为2的集合，个数为$\frac{\prod_{i=0}^{n-1} \binom{2n-2i}{2}}{n!}=(2n-1)!!$
$K_{n,n}$的完备匹配可以对第一部分标号，第二部分与第一部分的匹配可以看成全排列，个数为$n!$.





## 2
>树至多有一个完备匹配

证明：
假设存在两个完备匹配$M$和$M'$，设$S=\{e|e \in M, e \notin M \cap M'\}，T=\{e|e \in M', e \notin M \cap M'\}$，$S$与$T$的顶点集合相同，任取一个顶点$u$，在$S$与$T$中各有一个与其相连的边，设这两条边的另一个顶点为$u_1, v_1$. 在$T$中有一条与$u_1$相连的边，在$S$中有一条与$v_1$相连的边，若这两条边的另一个顶点相同，设这个顶点为$v$，则$uu_1vv_1u$为圈，与树中无圈矛盾。若这两条边的顶点不同，设为$u_2, v_2$，以此类推，必然会出现顶点相同的情况，$uu_1u_2...u_kvv_k...v_2v_1u$为圈，与树中无圈矛盾。
故树至多有一个完备匹配。





## 7
>证明：二分图有完备匹配的充要条件是，对任意$S \in V\{G\}$，都有$\mid N(S) \mid \geq \mid S \mid$。这个条件对一般图是否成立？

证明：
设$V(G)=X \cup Y, X \cap Y=\emptyset, S_X=S \cap X, S_Y=S \cap Y$,
则$|S|=|S_X|+|S_Y|, |N(S)|=|N(S_X)|+|N(S_Y)|$.
（必要性）：
因为二分图$G$有完备匹配，所以$X$中的顶点都被许配。
由$Hall$定理，有$|N(S_X)| \geq |S_X|$. 同理，$|N(S_Y)| \geq |S_Y|$.
$|N(S)|=|N(S_X)|+|N(S_Y)| \geq |S_X|+|S_Y|=|S|$
（充分性）：
不妨设$|X| \geq |Y|$，取$S \subset X$，由$Hall$定理，存在匹配$M$，使得$X$中的顶点都被匹配。
$\because |X| \geq |Y|$
$\therefore Y$中的顶点也相应地都被匹配。所以匹配$M$即为二分图$G$的完备匹配。
对一般图不成立，例如$K_3$满足$|N(S)| \geq S$，但是没有完备匹配。





## 9

>矩阵的一行或一列称为矩阵的一条线。证明：0-1矩阵中包含所有1所需的最少线数等于没有两个1在同一条线上的1的最大个数

证明：对0-1矩阵$M$,构造相应的二分图G,$M_{ij}=1$指第i行代表的顶点与第j列代表的顶点相邻
则包含所有1的最小线数等价于二分图G的最小覆盖，不在同一线上的1的最大个数等价于二分图G的最大匹配
由二分图最小覆盖等于最大匹配得，这两者相等





## 13
>用$Tutte$定理来证明$Hall$定理。

$Tutte$定理：图$G$（G为一般图，不一定是二分图）由完备匹配$\Leftrightarrow \forall S \subseteq V(G)$，都有$o(G-S) \leq |S|$.
$Hall$定理：二分图$G, V(G)=X \bigcup Y$，且$X \bigcap Y=\emptyset$，存在将$X$中的顶点都许配的匹配$\Leftrightarrow \forall S \subseteq X$都有$|N(S)| \geq |S|$，其中$N(S)$为$S$的邻顶集合。
证明：
对二分图$G=(X,Y,E)$，当$v$为偶数时，加一些边使得$Y$为完全图；当$v$时奇数时，加一些边和顶点$y_0$使得$Y \bigcup y_0$是完全图。图$G$变成完全图$H$，$G$中存在将$X$中所有顶点都许配的匹配的充要条件是$H$有完备匹配。此时$Hall$定理等价于$H$有完备匹配的充要条件是$\forall S \subseteq X, |N_H(S)| \geq |S|$.
（必要性）：
$\forall S \subseteq X$, 由$Tutte$定理，$o(H-N_H(S)) \leq |N_H(S)|$
在$H-N_H(S)$中，$S$中点都是孤立点，所以$|S| \leq o(H-N_H(S))$
$\therefore |N_H(S)| \geq |S|$.
（充分性）：
对$\forall S \subseteq V(H)$，并设$S=S_1 \bigcup S_2$，且$S_1 \bigcup X, S_2 \bigcup Y$.
因为$Y$是一个完全图，则在$H$中删去$S_1$不会增加连通片个数，且最多产生一个奇片. 删去$S_2$可能会使得$X$中有孤立顶点，设此时$X$中的孤立顶点为$S_3$，则$|N(S_3)| \leq |S_2|$，则有$|S_3| \leq |N(S_3)| \leq |S_2|$
若$|S_3|=|S_2|$，则$o(H-S_2)=|S_3|=|S_2|$；
若$|S_3| \leq |S_2|-1$，则$o(H-S_2) \leq |S_3|+1 \leq |S_2|$；
若$|S_1|$为偶数，则$o(H-S)=o(H-S_2) \leq |S_2| \leq |S|$；
若$|S_1|$为奇数，则$o(H-S)=o(H-S_2)+1 \leq |S_2|+1 \leq |S|$；
综上，对$\forall S \subseteq V(H)$，都有$o(H-S) \leq |S|$. 由$Tutte$定理，$H$为有完备匹配的图。





## 14

> 证明：若$G$是$k-1$边连通图的$k$度正则图，且$\nu(G)$是偶数，则$G$有完全匹配。

**证明**：设$S \subseteq V(G) $，$G_1,G_2,\dots,G_n$是$G-S$中的奇片，$m_i$是$G_i$与$S$间的边数。因为图$G$是$k-1$边连通图，则有
$$
m_i \geq k-1
$$
并且通过
$$
m_i = k|V(G_i)|-2|E(G_i)|
$$
可以得到$m_i$和$k$同奇偶，所以有
$$
m_i \geq k
$$

由此我们可以得出
$$
k|S| \geq \sum_{i=1}^n m_i \geq nk
$$
即
$$
|S| \geq n = o(G-S)
$$
所以由$Tutte$定理可得$G$有完全匹配。



## 15
>证明：树$T$有完备匹配，当且仅当对任意$v \in V(T)$，都有$o(T-v)=1$。

**证明**：
（1）必要性：
树T有完备匹配，由$Tutte$定理，$\forall S \subseteq V(T)$, 都有$o(T-S) \leq |S|$。令$S=\{v\}$，则$o(T-v) \leq 1$。
由于树T由完备匹配，即$|T|$为偶数，则$|T-v|$为奇数，所以$o(T-v) \geq 1$。
综上，$o(T-v)=1$。



（2）充分性：
$\forall v \subseteq V(T)$，都有$o(T-v)=1$，则$V(T)$为偶数。
删去$v$后，树$T$被划分成若干个连通片，且只有一个连通片为奇片，设奇片中与$v$相连的顶点为$u$，在树$T$中，确定一个$v$后，由于$o(T-v)=1$，所以$u$被唯一确定，并且$e=uv$也是被唯一确定的。

并且这个性质是由对称性的，可以，当删去$u$后，$v$所在的连通片变成了奇片，且他们的连接被唯一确定。

因为$v$是任意的，所以对于树中的每个顶点都有一个配对，这就是$T$中的完备匹配。



## 16

> 由a,b,c,d,e,f六个人组成检查团，检查5个单位的工作。若某单位与某人有过工作联系，则不能选派此人到该单位去检查工作。已知第一单位与b,v,d有过联系，第二单位与a,e,f，第三单位与a,b,e,f，第四单位与a,b,d,f,第五单位与a,b,c有过联系，请列出去各个单位进行检查的人员名单。

根据题意可以得到匹配问题的模型

![Ch5-16](/Users/sakura/USTC_Graph_Theory/homework/images/ch5-16-1.png)

取初始匹配$M=\empty$

（1）选择未匹配节点$y_1$，得到可增广轨道$\{y_1a\}$, $M=\{y_1a\}$

![Ch5-16](/Users/sakura/USTC_Graph_Theory/homework/images/ch5-16-2.png)



（2）选择未匹配节点$y_2$，得到可增广轨道$\{y_2b\}$, $M=\{y_1a,y_2b\}$

![Ch5-16](/Users/sakura/USTC_Graph_Theory/homework/images/ch5-16-3.png)

（3）选择未匹配节点$y_3$，得到可增广轨道$\{y_3c\}$, $M=\{y_1a,y_2b,y_3c\}$

![Ch5-16](/Users/sakura/USTC_Graph_Theory/homework/images/ch5-16-4.png)

（4）选择未匹配节点$y_4$，得到可增广轨道$\{y_4e\}$, $M=\{y_1a,y_2b,y_3c,y_4e\}$

![Ch5-16](/Users/sakura/USTC_Graph_Theory/homework/images/ch5-16-5.png)

（5）选择未匹配节点$y_5$，得到可增广轨道$\{y_5f\}$, $M=\{y_1a,y_2b,y_3c,y_4e,y_5f\}$

![Ch5-16](/Users/sakura/USTC_Graph_Theory/homework/images/ch5-16-6.png)

此时所有节点都被许配，算法停止。可以得到一种匹配方式为$M=\{y_1a,y_2b,y_3c,y_4e,y_5f\}$





## 17

>设有四个人（行）$A, B, C, D$，有四分工作（列）$a, b, c, d$，每个人做某份工作的效率如下面的矩阵所示，试求最佳的工作分配方案。
>$$
>\begin{pmatrix}
>  99 & 6 & 59 & 73  \\
>  79& 15 &93 &87  \\
>67 &93 &13 &81 \\
>  16&79 &86 &26 \\
>
>  \end{pmatrix}
>$$
>

按照$Kuhn-Munkreas$算法一步步计算即可。
构造相等子图$G_l$
![Ch5-17-2](./images/Ch5-17-2.png)
$G_l$无完备匹配，取D为未被许配的点，可得：
$Z=\{B, D, c\}$
$S=\{B, D\}$
$T=\{c\}$
$\alpha_l=6$，重新构造相等子图：
![Ch5-17-3](./images/Ch5-17-3.png)
最佳分配方案为：$A-a, B-d, C-b, D-c, \omega=99+87+93+86=365$.







## 19
>证明：$Kuhn-Munkreas$算法中修改顶标后，$\widehat{l}$仍然是可行顶标。

证明：
修改的可行顶标
$$
\widehat{l}=
\begin{cases}
l(v)-\alpha_l& \text{v ∈ S}\\
l(v)+\alpha_l& \text{v ∈ T}\\
l(v)& \text{其他}
\end{cases}
$$
$\alpha_l = min_{x \in S, y \notin T}\{l(x) + l(y) - \omega(x,y)\}$

对$\forall v \in S, u \in Y$,
(1) 若$u \in T$
$$
\widehat{l}(v)+\widehat{l}(u)=l(v)-\alpha_l+l(u)+\alpha_l=l(v)+l(u) \geq \omega(u,v)
$$
(2) 若$u \in Y $并且$ u \notin T$， 因为有$\alpha_l \leq l(v) + l(u) - \omega(u,v)$
$$
\widehat{l}(v)+\widehat{l}(u)=l(v)-\alpha_l+l(u) \geq l(v)+l(u)-(l(v)+l(u)-\omega(u,v)) \geq \omega(u,v)
$$
(3) 若对$\forall v \notin S, u \in Y$
$$
\widehat{l}(v)+\widehat{l}(u) =l(v)+\widehat{l}(u) \geq l(v)+l(u) =  \omega(u,v)
$$
综上，$Kuhn-Munkreas$算法修改顶标后，$\widehat{l}$仍然是可行顶标。

