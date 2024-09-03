# 作业8nd

## 四.1 证明：$K_5$与$K_{3,3}$删去一条边后都是平面图

- ### $K_5$：

    - 对于$K_{5}$的任一极大平面子图$G'$，有$\varepsilon(G')=3\nu(G')-6=9$
    - 即$G'$由删除$K_5$中某一条边得到
    - 由于完全图$K_5$的对称性，删除其中任意一条边得到的图$G''$均与$G'$同构，为平面图

- $K_{3,3}$中的所有边亦具有对称性，证明同理

## 四.4 设连通平面图$G$是有$8$个顶点的$4-$正则图，则它的平面嵌入把平面分成多少个面？

- $2\varepsilon=4\nu$，$\varepsilon=16$
- $\phi=2-\nu+\varepsilon=10$

## 四.6 设$G$是连通的简单平面图, 面数$\phi<12$，最小度$\delta\geq3$

1. ### 证明$G$中存在度数小于等于$4$的面

    - 由于$\delta\geq3$，故$2\varepsilon\geq3\nu$，$\nu\leq\frac{2}{3}\varepsilon$
    - 由于$\phi<12$，故$2=\nu-\varepsilon+\phi<\nu-\varepsilon+12\leq\frac{2}{3}\varepsilon-\varepsilon+12$，$\varepsilon<30$
    - 若$G$中所有面度数均大于$4$，则$2\varepsilon=\displaystyle\sum_{f\in F(G)}deg(f)\geq5\phi$，$\phi\leq\frac{2}{5}\varepsilon$
    - $2=\nu-\varepsilon+\phi\leq\frac{2}{3}\varepsilon-\varepsilon+\frac{2}{5}\varepsilon=\frac{1}{15}\varepsilon$，$\varepsilon\geq30$，矛盾
    - 故$G$中存在度数小于等于$4$的面

2. ### 举例说明当$\phi=12$时，其他条件不变，$(1)$的结论不成立

    - 若$\phi=12$，则$\varepsilon=30$，$\nu=20$
    - ![image-20221025225107496](C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221025225107496.png)

## 四.7 设$G$是$\nu$个顶点$\varepsilon$条边的简单平面图，$\varepsilon<30$，证明存在顶点$v\in V(G)$，使得$\deg(v)\leq4$

- 若$\forall v\in V(G)$，均有$\deg(v)>4$
- 则$2\varepsilon=\displaystyle\sum_{v\in V(G)}deg(v)\geq5\nu$，$\nu\leq\frac{2}{5}\varepsilon$
- 则$\varepsilon\leq3\nu-6\leq\frac{6}{5}\varepsilon-6$，$\varepsilon\geq30$，矛盾
- 故$\exist v\in V(G)$，使得$\deg(v)\leq4$

## 五.2 证明：树至多有一个完备匹配

- 若树$T$存在完备匹配$M$
- 对于树$T$上任意一点$u$，将其删除将得到若干连通片，且有$o(G-\{u\})=1$，否则无法完备匹配
- 不妨设$u$在$M$中与$v$相配，则$v$将处在唯一的奇片中，且$uv\in E(T)$
- 对于任意完备匹配$M'$，$u$和$v$必然相配，推广可得树至多只有一个完备匹配

## 五.4 两个人在图$G$上博弈，交替选择不同的顶点$v_0,v_1,v_2,\cdots$，使得当$i>0$时，$v_i$与$v_i−1$相邻，直到不能选到顶点为止，谁最后能选到一个顶点谁赢。证明：第一个选顶点的人有必胜的策略，当且仅当$G$中无完备匹配，并给出一个必胜的策略

- #### 充分性：

    - 若$G$中存在完备匹配$M$，则划分$G=X\cup Y$，且$X\cap Y=\emptyset$，满足$|X|=|Y|$且$M\in\{uv|u\in V(X),v\in V(Y)\}$
    - 记$n=|X|=|Y|=\frac{|G|}{2}$
    - 设$X=\{x_1,x_2,\cdots,x_n\}$，$Y=\{y_1,y_2,\cdots,y_n\}$且$x_i$和$y_i$在$M$中相配，$i=1,2,\cdots,n$
    - 不妨假设先手最先取了$x_1$，则令后手取$y_1$
    - 分别在$X$、$Y$、$M$中删除$x_1$、$y_1$、$x_1y_1$得到$X'$、$Y'$、$M'$
    - 此时不管先手取$X'$或$Y'$中的点$u$，令后手取在$M$中与$u$相配的点即可
    - 若干次操作后，先手将无点可取，即不存在必胜策略
    - 故存在必胜策略时$G$中无完备匹配

- #### 必要性：

    - 若$G$中无完美匹配，设存在最大匹配$M$
    - 记$G$中被$M$许配的点的集合为$S$
    - 划分$S=X\cup Y$，且$X\cap Y=\emptyset$，满足$|X|=|Y|$且$M\in\{uv|u\in V(X),v\in V(Y)\}$
    - 则令先手取$G-S$中的任意一点$u_0$，若后手取的点$v_0\not\in S$，则$M+u_0v_0$也为匹配，这与$M$是$G$的最大匹配矛盾
    - 故后手此时只能取$S$中的点，即$v_0\in S$
    - 此后先手只需取$v_0$在$M$中相配的点即可，不妨记为$u_1$
    - 若此时后手可以取$v_1\not\in S$，则轨道$u_0v_0u_1v_1$为增广轨道，这与$M$是$G$的最大匹配矛盾
    - 故后手此时只能取$S$中的点
    - 以此类推，后手任取$S$中的一点$v_i$后，先手均可取$v_i$在$M$中相配的点$u_i$，直至后手无点可取，先手必胜

## 五.6 证明：$8\times8$的正方形去除对角上的两个$1\times1$的小正方形后，不能用$1\times2$的长方形覆盖

- ![img](https://iknow-pic.cdn.bcebos.com/2fdda3cc7cd98d10dd3db5a0333fb80e7aec90b2?x-bce-process=image%2Fresize%2Cm_lfit%2Cw_600%2Ch_800%2Climit_1%2Fquality%2Cq_85%2Fformat%2Cf_auto)
- 按上图所示为各方块染色
- 则摆入任何一个$1\times2$的长方形都将恰好覆盖一个红色格和一个绿色格
- 而一共有$32$个绿色格，$30$个红色格，故不可能全部覆盖

## 五.7 证明：二分图$G$有完备匹配的充要条件是，对任何$S\subseteq V(G)$，都满足$|N(S)|\geq|S|$。这个命题对一般图成立吗？

- #### 必要性:

    - 假设二分图划分点集$V(G)=X\cup Y$且$X\cap Y=\emptyset$，且$|X|\geq |Y|$
    - $\forall S\subseteq X$，显然都有$S\subseteq V(G)$和$|N(S)|\geq|S|$，故由$Hall$定理知二分图存在将$X$中所有顶点都许配的匹配$M$
    - 由于$|X|\geq|Y|$，故$Y$中所有顶点也被$M$许配，即$G$由完备匹配

- #### 充分性：

    - 若二分图$G$有完备匹配
    - 由$Hall$定理知，$\forall S\subseteq X$或$S\subseteq Y$，都满足$|N(S)|\geq|S|$
    - 若$S=S_1\cup S_2$，且$S_1\subseteq X$，$S_2\subseteq Y$
    - 则$|N(S)|=|N(S_1)|+|N(S_2)|\geq |S_1|+|S_2|=|S|$
    - 原题得证