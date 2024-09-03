# 六：$Euler$图与$Hamilton$图

## $Euler$图

- $Euler$迹：经过图$G$每条边的形迹
    - $Euler$回路
        - $Euler$图，连通图中的等价命题
            1. $G$的每个顶点的度数都是偶数
            2. $G$可以表示成无公共边的圈之并
        - 平面$Euler$图至多是$\nu(G)-2$个无公共边的圈的并
    - $Euler$迹存在当且仅当最多有两个度数为奇数的点
- 有向图$D$连通，有以下等价命题：
    - $D$是$Euler$图
    - $\forall v\in V(D)$，$\deg^+(v)=\deg^-(v)$
    - $D$可以表示成无公共边的有向圈之并
- $Fleury$算法：
    - 每次尽量选择剩余边图的非桥边
    - 时间复杂度：$O(\varepsilon^2\nu)$
- 逐步插入回路法：
    - $O(\varepsilon+\nu^2)$

## 中国邮递员问题

- 最优投递线路，回路权和最小
- $Edmonds-Johnson$算法：
    - $O(\nu^4)$
    - 对所有奇度顶点构造最短距离作为边权的加权完全图，求加权完全图总权最小的完备匹配（$O(\nu^4)$），随后求$Euler$回路

## $Hamilton$图

- $Hamilton$轨道：经过图$G$每个顶点的轨道
    - $Hamilton$圈
        - $Hamilton$图：含有$Hamilton$圈的图
            - 正十二面体、平凡图、完全图……
- 点数为奇数的二分图不可能是$Hamilton$图
- $Hamilton$图中，对$V(G)$的每个非空真子集$S$，均有$\omega(G-S)\leq|S|$（连通片个数）
    - 假设$H$为$Hamilton$圈，则$\omega(G-S)\leq\omega(H-S)\leq|S|$
- $Petersen$图不是$Hamilton$图
- $Dirac$定理：若简单图满足$\nu(G)\geq3$，$\delta(G)\geq\frac{\nu(G)}{2}$，则$G$是$Hamilton$图
    - 若对于某对不相邻顶点有$deg(u)+deg(v)\geq\nu(G)$，则$G$是$Hamilton$图当且仅当$G+uv$是$Hamilton$图
    - 简单图$G$是$Hamilton$图，当且仅当它的闭包$c(G)$是$Hamilton$图
- 闭包$c(G)$：反复连接$G$中度数之和不小于$\nu(G)$的不相邻点对，直至无法连接为止
    - 闭包唯一确定
- 若$\nu(G)\geq3$，对$G$的任意一对顶点$u,v$，若$deg(u)+deg(v)\geq\nu(G)-1$，则$G$有$Hamilton$轨道；若$deg(u)+deg(v)\geq\nu(G)$，则$G$是$Hamilton$图

## 旅行商问题

- 最小$Hamilton$圈
- 最近邻法
    - 对于满足三角不等式的完全加权图，$\displaystyle\frac{d}{d_0}\leq\frac{1}{2}\left(\lceil\log_2n\rceil+1\right)$
- 最小生成树法：
    - 求得最小生成树$T$，为树上每一条边添加一条与原边同权的平行边，求$Euler$回路
    - 沿回路顺序，若遍历至已遍历过的点，则直接跳过并走原图的边
    - 对于满足三角不等式的完全正加权图，$\displaystyle\frac{d}{d_0}<2$
- 最小权匹配法：
    - 在最小生成树上的奇度顶点求总权最小的完备匹配，增加相应的边，求$Euler$回路
    - $O(\nu^3)$，$\displaystyle\frac{d}{d_0}<\frac{3}{2}$