# 作业10nd

## 6.7

> 给出一个算法，在有$Euler$迹的图中求出一条$Euler$迹

- 若图$G$存在$Euler$迹，则其中奇度顶点的个数只能为$0$或$2$
- 若奇度顶点个数为$2$，则连接该两点得到图$G'$，显然图$G'$有$Euler$回路。
- 使用$Fleury$算法或逐步插入回路法即可得到$G'$的$Euler$回路$P$，删除额外添加的边即为$G$的一条$Euler$迹
- 若奇度顶点个数为$0$，则直接求$Euler$回路即可

## 6.8

> 求下图的一条最优投递线路
>
> <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221108213200152.png" alt="image-20221108213200152" style="zoom: 50%;" />

- 使用$Edmonds-Johnson$算法
    1. 图$G$的奇度顶点集$V=\{v_1,v_2,v_3,v_4\}$
    2. 由$Floyd$算法或$Dijkstra$算法得$K_4$：
        - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221108213844903.png" alt="image-20221108213844903" style="zoom: 50%;" />
    3. $K_4$的最优完备匹配$M=\{v_1v_2,v_3v_4\}$
    4. 在$G$中增加$v_1,v_2$间最短轨迹$P(v_1,v_2)=v_1v_7v_2$和$v_3,v_4$间最短轨迹$P(v_3,v_4)=v_3v_4$的平行边，得到$G^*$
        - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221108214512843.png" alt="image-20221108214512843" style="zoom:50%;" />
    5. 其中一条$Euler$回路为$v_1v_6v_2v_7v_1v_5v_4v_3v_4v_7v_3v_2v_7v_1$，即为一条最优投递路线

## 6.9

> 设$G$是二分图，证明：若$G$是$Hamilton$图，则$G$必有偶数个顶点。

- 若$G$有奇数个顶点，则$G$上的$Hamilton$圈即为奇圈，这与$G$为二分图矛盾
- 故$G$必有偶数个顶点

> $Herschel$图是否为$Hamilton$图
>
> <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221108215412038.png" alt="image-20221108215412038" style="zoom:50%;" />

- 该图为二分图，且有奇数个顶点，故不为$Hamilton$图

## 6.12

> 求$K_n$中无公共边的$Hamilton$圈的个数

- 假设无公共边的$Hamilton$圈的个数为$m$，则$nm\leq\frac{1}{2}n(n-1)$，即$m\leq\frac{n-1}{2}$
- 若$n$为奇数，不妨令$n=2k+1$（$k\in\Bbb{N}$）
- 将顶点$1,2,3,\cdots,2k$逆时针排成一圈，$2k+1$置于中央，下图即为一种$Hamilton$圈
- <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221108222903205.png" alt="image-20221108222903205" style="zoom:33%;" />
- 每次旋转外围的$2k$个点，改变$2k+1$相邻的两点，即可得到类似的一共$k$个无公共边的$Hamilton$圈
- 若$n$为偶数，不妨令$n=2k+2$（$k\in\Bbb{N}$）
- 则在$n=2k+1$的基础上增加一个点$2k+2$，令其每次在$Hamilton$圈上挑选一对不同的点并插入其之间，可得到一共$k$个无公共边的$Hamilton$圈
- 则$K_n$中无公共边的$Hamilton$圈的个数为$\lfloor\frac{n-1}{2}\rfloor$

## 6.17

> 设$G$是$\nu$阶无向简单图，边数$\varepsilon=\frac{1}{2}(\nu-1)(\nu-2)+2$

1. ###### 证明：$G$是$Hamilton$图

    - 若$\nu=1$，则$G$显然是$Hamilton$图
    - 对于$G$中度数最小的两点$v_1$、$v_2$，有$\displaystyle deg(v_1)+deg(v_2)=2\varepsilon-\sum_{u\in V(G),u\neq v_1且u\neq v_2}deg(u)\geq2\varepsilon-(\nu-2)(\nu-3)-(deg(v_1)+deg(v_2))$
    - 即$deg(v_1)+deg(v_2)\geq\nu$，故$G$中任意两点度数之和不小于$\nu$，则$G$为$Hamilton$图

2. ###### 举例说明，当$\varepsilon=\frac{1}{2}(\nu-1)(\nu-2)+1$时，$G$不一定是$Hamilton$图

    - 当$G=K_{1,\nu-1}$时，显然不是$Hamilton$图

## 6.19

> 若围一张圆桌坐着至少六个人，那么一定可以调整他们的位置，使得每个人两侧都挨着新邻居

- 同$6.12$，当人数$n\geq5$时，$K_n$中无公共边的$Hamilton$圈的个数为$\lfloor\frac{n-1}{2}\rfloor\geq2$
- 即存在多种坐法保证任何两人之间为新邻居

## 6.20

> 今有$\nu$个人，已知他们中的任何两人合起来认识其余的$\nu-2$人。
>
> 证明：当$\nu\geq3$时，这$\nu$个人能排成一列，使得中间任何人都认识两边的人，而两头的人认识左边（或右边）的人。
>
> 当$\nu\geq4$时，这$\nu$个人能排成一个圆圈，使得每个人都认识两边的人

- 将人抽象为顶点，将认识关系抽象为边，则原题可简化为关系网$G$中是否存在$Hamilton$轨道或$Hamilton$圈
- 当$\nu=3$时，显然存在$Hamilton$轨道，且若$\varepsilon=3$则有$Hamilton$图
- 当$\nu\geq4$时，若$G$不存在$Hamiton$圈，则$\exist v_1,v_2\in V(G)$满足$deg(v_1)+deg(v_2)<\nu$
- 而其余的$\nu-2$个点均与该两点中的至少一点相邻，故$\nu>deg(v_1)+deg(v_2)\geq\nu-2$，且易知$v_1$与$v_2$不相邻
- 不妨拆分$V(G)-\{v_1,v_2\}=X\cup Y$，$X=\{u|uv_1\in E(G)\}$，$Y=\{u|uv_2\in E(G)\}$
- $|X\cap Y|=deg(v_1)-deg(v_2)-(\nu-2)\leq1$
- 由于$\nu\geq4$，故$|X\cup Y-X\cap Y|\geq4-2-1=1$
- 若任取$X-X\cap Y$（假设其不为空）中的一点$v_3$，考虑$v_1,v_3$，则其均不与$v_2$相邻，不成立
- 故对于$G$中任意两点$v_1,v_2$，都有$deg(v_1)+deg(v_2)\geq\nu$，$G$为$Hamilton$图

## 6.22

> $5$阶完全加全图如下
>
> <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221108230858810.png" alt="image-20221108230858810" style="zoom: 33%;" />

1. ###### 用最近邻法求以$a$为起点的旅行商问题的近似解

    - $H=adebca$，$W=26$

2. ###### 用最小生成树法求以$a,b$为起点的旅行商问题的近似解

    - 最小生成树$T$如下，并为各边增加平行边得到$G^*$
    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221108231526490.png" alt="image-20221108231526490" style="zoom:33%;" />
    - 从$a$出发，$G^*$的一条$Euler$回路$C_a=adecedaba$，则$H_a=adecba$，$W_a=21$
    - 从$b$出发，$G^*$的一条$Euler$回路$C_b=badecedab$，则$H_b=badecb$，$W_b=21$

3. ###### 用最小权匹配法求旅行商问题的近似解

    - 最小生成树$T$中奇度顶点集为$V=\{b,c\}$，其导出子图中最优完备匹配$M=\{bc\}$，将$M$中各边加入$T$后得到$G^*$
    - <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221108231832639.png" alt="image-20221108231832639" style="zoom:33%;" />
    - 从任意一点出发，绕一圈即为$Euler$回路和$Hamilton$圈，$W=21$