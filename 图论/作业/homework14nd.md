# homework14nd

## 九

> 9.证明：若供需约束的网络$N$存在可行流$f$，则其附加网络$N'$上一定存在流函数$f'$，使得任给$1\leq j\leq n$，$f'$使得边$(y_j,y_0)$都满载

- 对于有供需约束的网络$N$的可行流$f$，有$\displaystyle\sum_{e\in\alpha(y_j)}f(e)-\sum_{e\in\beta(y_j)}f(e)\geq\rho(y_j)$，$y_j\in Y$
- 显然存在其他可行流$f^-$，通过减小一些边的流量使$\displaystyle\sum_{e\in\alpha(y_j)}f(e)-\sum_{e\in\beta(y_j)}f(e)=\rho(y_j)$，$y_j\in Y$
- 对于其附加网络$N'$，可以认为是在可行流方案$f^-$中，令所有汇点$y_j$蓄积的流量分别通过边$(y_j,y_0)$汇入$y_0$，故$\forall y_j\in Y$，$c((y_j,y_0))=\rho(y_j)=\displaystyle\sum_{e\in\alpha(y_j)}f^-(e)-\sum_{e\in\beta(y_j)}f^-(e)$，即为满载

> 15.证明：假设$f$与$f'$为网络$N$上的流函数，且$\operatorname{Val}(f)=\operatorname{Val}(f')$，证明$f-f'$是$N$上的一个循环

- $\displaystyle\sum_{e\in\alpha(s)}(f-f')(e)-\sum_{e\in\beta(s)}(f-f')(e)=\operatorname{Val}(f')-\operatorname{Val}(f)=0$
- $\displaystyle\sum_{e\in\alpha(t)}(f-f')(e)-\sum_{e\in\beta(t)}(f-f')(e)=\operatorname{Val}(f)-\operatorname{Val}(f')=0$
- $\forall v\in V(D)-\{s,t\}$，$\displaystyle\sum_{e\in\alpha(v)}(f-f')(e)-\sum_{e\in\beta(v)}(f-f')(e)=0-0=0$
- 综上，$f-f'$是$N$上的一个循环

> 17.修改算法`9.4`，求有供需约束网络的最大流

- 输入：有供需约束网络$N=(D,X,Y,\sigma,\rho,c)$
- 输出：$N$的最大流函数$f$，或断定$N$没有可行流
- （1）构造$N$的附加网络$N'=(D',x_0,y_0,c')$
- （2）用$2F$算法求出$N'$的最大流函数$f'$
- （3）若$f'$满足：任给$1\leq j\leq n$，$f'$使得边$(y_j,y_0)$满载，即$f'((y_j,y_0))=c'((y_j,y_0))$，则转第（4）步；否则，输出结论“$N$没有可行流”，算法停止
- （4）构造新网络$N''=(D',x_0,y_0,c'')$
    - $\displaystyle c''(e)=\begin{cases}c'(e)-f'(e),&e=(x_0,x_i)或e\in E(D)\\\infty,&e=(y_j,y_0)\end{cases}$
- （5）用$2F$算法求出$N''$的最大流函数$f''$
- （6）将$f'+f''$限制到网络$N$上，即任给$e\in E(D)\sub E(D')$，令$f(e)=f'(e)+f''(e)$。$f$就是$N$的最大流。算法停止

> 19.证明引理9.6：任给有向图$D$中的一个非负的循环$f$，$f$都是一些有向圈导出循环的线性组合。若$f$的函数值都是整数，则$f$是有向圈导出循环的某个线性组合，使得该线性组合中的系数都是非负整数

- 对于有向图$D$中的非负循环$f$，设其支撑为边子集$E'$，边导出子图$D[E']$。
- 则显然$D[E']$中不存在入度为零的点，也不存在出度为零的点，则$D[E']$中一定含有有向圈。
- 不妨设$D[E']$的某个有向圈$C$含有正函数值边$e_+$（均为负值同理），令$\tilde{f}(e)=\begin{cases}f(e)-f(e_+),&e\in C\\f(e),&e\not\in C\end{cases}$
- 经过若干次操作直至$f'$无支撑，则说明$f$都是一些有向圈导出循环的线性组合
- 若$f$的函数值都是整数，则上述操作中$f(e_+)$或$|f(e_-)|$即为该有向圈在线性组合中的系数，负值圈反向即可

<div style="page-break-after:always"></div>

## 十

> 1.给出图$G$的一颗生成树$T$，求出$G$关于$T$的一组基本圈组和圈空间$\mathcal{C}(G)$中的所有向量，并给出图示
>
> <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221206225428321.png" alt="image-20221206225428321" style="zoom: 33%;" />

- 生成树$T$如下：

- <img src="C:\Users\23764\AppData\Roaming\Typora\typora-user-images\image-20221206225531690.png" alt="image-20221206225531690" style="zoom:33%;" />

- 基本圈组：
    $$
    \begin{align}
    &(e_1,e_2,e_3)\\
    &(e_1,e_2,e_4,e_5)\\
    &(e_4,e_6,e_7)\\
    &(e_1,e_2,e_6,e_8)\\
    \end{align}
    $$

- 圈空间$\mathcal{C}(G)$：
    $$
    \begin{array}{c|c}
    边子集&边向量\\
    \hline
    \emptyset&(0,0,0,0,0,0,0,0)\\
    \{e_5,e_7,e_8\}&(0,0,0,0,1,0,1,1)\\
    \{e_4,e_6,e_7\}&(0,0,0,1,0,1,1,0)\\
    \{e_4,e_5,e_6,e_8\}&(0,0,0,1,1,1,0,1)\\
    \{e_3,e_6,e_8\}&(0,0,1,0,0,1,0,1)\\
    \{e_3,e_5,e_6,e_7\}&(0,0,1,0,1,1,1,0)\\
    \{e_3,e_4,e_7,e_8\}&(0,0,1,1,0,0,1,1)\\
    \{e_3,e_4,e_5\}&(0,0,1,1,1,0,0,0)\\
    \{e_1,e_2,e_6,e_8\}&(1,1,0,0,0,1,0,1)\\
    \{e_1,e_2,e_5,e_6,e_7\}&(1,1,0,0,1,1,1,0)\\
    \{e_1,e_2,e_4,e_7,e_8\}&(1,1,0,1,0,0,1,1)\\
    \{e_1,e_2,e_4,e_5\}&(1,1,0,1,1,0,0,0)\\
    \{e_1,e_2,e_3\}&(1,1,1,0,0,0,0,0)\\
    \{e_1,e_2,e_3,e_6,e_8\}&(1,1,1,0,0,1,0,1)\\
    \{e_1,e_2,e_3,e_5,e_7,e_8\}&(1,1,1,0,1,0,1,1)\\
    \{e_1,e_2,e_3,e_4,e_6,e_7\}&(1,1,1,1,0,1,1,0)\\
    \end{array}
    $$

> 3.证明：给定连通图$G$的一颗生成树$T$，其对应的基本割集组$S_1,S_2,\cdots,S_{\nu-1}$为$\mathcal{S}(G)$的一组基，$\mathcal{S}(G)$的维数为$\nu-1$

- 给定一组常数$k_1,k_2,\cdots,k_{\nu-1}$，若
    $$
    \begin{align}
    &k_1S_1+k_2S_2+\cdots+k_{\nu-1}S_{\nu-1}\\
    =&(k_1,k_2,\cdots,k_{\nu-1},*,\cdots,*)\\
    =&(0,0,\cdots,0,0,\cdots,0)
    \end{align}
    $$

- 则必有$k_1=k_2=\cdots k_{\nu-1}=0$，故$S_1,S_2,\cdots,S_{\nu-1}$线性无关

- $\forall V'\in V(G)$且$V'\neq\emptyset$，设$(V',\overline{V'})$上属于$T$的边为$e_{i_1},e_{i_2},\cdots,e_{i_{t}}$，则有
    $$
    \begin{align}
    T的边\ \ \ \ \ \ &非T的边\\
    (V',\overline{V'})+S_{i_1}+S_{i_2}+\cdots+S_{i_{t}}=(0,0,\cdots,0,&*,\cdots,*)
    \end{align}
    $$

- 一方面因为$(V',\overline{V'})+S_{i_1}+S_{i_2}+\cdots S_{i_t}\in\mathcal{S}(G)$；另一方面，$(V',\overline{V'})+S_{i_1}+S_{i_2}+\cdots S_{i_t}\in E(G)-E(T)$，不可能为割集，故只能为零向量。

- 因而$(V',\overline{V'})=S_{i_1}+S_{i_2}+\cdots S_{i_t}$，即$\mathcal{S}(G)$中的任意一个割断向量都可以表示成$S_1,S_2,\cdots,S_{\nu-1}$的线性组合

- 综上$S_1,S_2,\cdots,S_{\nu-1}$是$\mathcal{S}(G)$的一组基，$\mathcal{S}(G)$的维数为$\nu-1$
