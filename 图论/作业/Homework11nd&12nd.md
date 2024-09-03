# Homework11nd&12nd

## 七

- ### 2.

    - > 若$G$是$\nu$个顶点$\varepsilon$条边的简单图，证明$\displaystyle\chi(G)\geq\frac{\nu^2}{\nu^2-2\varepsilon}$

        - 不妨记$k=\chi(G)$
        - 假设某种正常$k-$顶点着色方案为$V(G)=S_1\cup S_2\cup\cdots\cup S_k$，且$S_i\cap S_j=\emptyset$，$1\leq i,j\leq k$且$i\neq j$
        - 记$n_i=|S_i|$，$1\leq i\leq k$，则有$\displaystyle\nu=\sum_{i=1}^k n_i$
        - 则$\displaystyle\varepsilon\leq\frac{1}{2}\sum_{i=1}^kn_i(\nu-n_i)=\frac{1}{2}\left(\nu^2-\sum_{i=1}^kn_i^2\right)\leq\frac{1}{2}\left[\nu^2-\frac{1}{k}\left(\sum_{i=1}^kn_i\right)^2\right]=\frac{\nu^2}{2}\left(1-\frac{1}{k}\right)$
        - 即有$\displaystyle\chi(G)=k\geq\frac{\nu^2}{\nu^2-2\varepsilon}$

- ### 4.

    - > 设$G$的度数序列为$d_1,d_2,\cdots,d_\nu$，且$d_1\geq d_2\geq\cdots\geq d_\nu$，则$\chi(G)\leq\max_i\min\{d_i+1,i\}$

        - 设度数序列对应的顶点序列为$v_1,v_2,\cdots,v_\nu$依次染色
        - 不妨设$\min\{d_i+1,i\}$最大值最先在$p$处取到
        - 若$d_p+1<p$，则显然有$p>1$和$d_p+1\leq p-1$、$d_p+1\leq d_{p-1}+1$，即$\min\{d_p+1,p\}\leq\min\{d_{p-1},p-1\}$，矛盾
        - 若$d_p+1\geq p$，则将前$p$个点分别染色为$1,2,\cdots,p$，对于剩余的任意一点$v_j(p<j\leq\nu)$，由于$\min\{d_{j}+1,j\}\leq p$，故有$d_j<p$
        - 则可为$v_j$染一种不同于其邻点的颜色，且包含于$p$种颜色中，此即为一种正常$p-$顶点着色方案
        - 故$\chi(G)\leq\max_i\min\{d_i+1,i\}$

- ### 6.

    - > 证明：$\chi(G)+\chi(G^{C})\leq\nu+1$

        - 数学归纳法证明命题$\chi(G)+\chi(G^C)\leq\nu+1$
        - 当$\nu=0$时，命题成立
        - 若当$\nu(\geq0)$时命题成立，在$\nu$阶图$G$中增加一个点$u$，并将其与点集$S=\{v_1,v_2,\cdots,v_k\}$中所有点相连，其中$0\leq k\leq\nu$，$v_k\in V(G)$，得到$\nu+1$阶图$G'$
        - 若$S$包含了所有的$\chi(G)$种颜色，则$u$只能染成新的颜色，即$\chi(G')=\chi(G)+1$，且$\deg_G(u)=k\geq\chi(G)$
        - 对于$G'^C$，若$V(G)-S$也包含了所有的$\chi(G')$种颜色，则$\chi(G'^C)=\chi(G^C)+1$，且$\deg_{G^C}(u)=\nu-k\geq\chi'(G)$
        - 若上述两个假设同时成立，则$\nu=\deg_G(u)+\deg_{G^C}(u)\geq\chi(G)+\chi(G^C)$，此时有$\chi(G')+\chi({G'}^C)\leq\nu+2$，命题成立
        - 若上述假设不同时成立，则$\chi(G')+\chi(G'^C)\leq\chi(G)+\chi(G^C)+1\leq\nu+2$，命题成立
        - 综上，$\chi(G)+\chi(G^C)\leq\nu+1$

- ### 8.

    - > 轮是一个圈上加一个新顶点，把圈上的每个顶点都和新顶点之间连一条边，求$\nu$阶轮的边色数

        - 设$\nu$阶轮图$G$，$\nu\geq4$
        - 则$\Delta(G)=\nu-1$，$\chi'(G)=\nu-1$，着色方案如下
        - <img src="file:///C:\Users\23764\Documents\Tencent Files\2376419868\Image\C2C\Image1\599C7DE4D0E10D92E7ADA2AB5E739661.png" alt="img" style="zoom:50%;" />

- ### 14.

    - > 设有$4$名教师$x_1,x_2,x_3,x_4$给五个班级$y_1,y_2,y_3,y_4,y_5$上课，某天的教学要求如下：
        > $$
        > A=\begin{matrix}&y_1&y_2&y_3&y_4&y_5\\x_1&1&0&1&0&0\\x_2&1&0&1&1&0\\x_3&0&1&1&1&1\\x_4&0&1&0&1&2\end{matrix}
        > $$

    - > （1）这一天最少需要安排多少课时？试排出这样的课表

      - 最少课时即为$\chi'(G)=\Delta(G)=4$

    - > （2）不增加课时数的情况下，试排出一个使用教室最少的课表

      - 最少需要$\left\lceil\frac{\varepsilon(G)}{\chi'(G)}\right\rceil=4$间教室
      - ![img](file:///C:\Users\23764\Documents\Tencent Files\2376419868\Image\C2C\Image1\47CF7F430C13D83352E84B576AC5A55C.png)

- ### 16.

    - > 证明：若一个平面图的平面嵌入是$Euler$图，则它的对偶图是二分图

        - 若$G$是$Euler$图，则其中所有顶点度数均为偶数
        - 则对于$G$中点$v$在$G^*$中对应的面$f_v$有$\deg_{G^*}(f_v)=\deg_G(v)$
        - 由于两偶圈通过消除重合边缘而连接得到的也是偶圈，故$G^*$中无奇圈，即为二分图

- ### 17.

    - > 设$G$是$\nu(\geq4)$阶极大平面图的平面嵌入，证明：$G$的对偶图$G^*$是$2-$边连通的$3$次正则图
    
        - $\forall f\in F(G)$，有$\deg_G(f)=3$
        - 故面$f$对应的点$v_f$满足$\deg_{G^*}(v_f)=3$，且$G^*$显然是$2-$边连通的

## 八

- ### 1.

    - > 有多少种方式把$K_5$定向成竞赛图

        - $\displaystyle 2^{\varepsilon(K_5)}=2^{10}=1024$

- ### 2.

    - > 设$D$是没有有向圈的有向图

    - > （1）证明：$\delta^-=0$

        - 若没有有向圈的有向图$D$满足$\delta^-\ge1$，即$\forall v\in V(D)$有$\deg^-(v)\geq1$
        - 则任取一点$v_0$，记$S=\{v_0\}$。
        - 由于$\deg^-(v_0)\geq1$，则可找到其外邻顶点$v_1$且$v_1\not\in S$
        - 令$S=S\cup\{v_1\}$，并找到$v_1$的外邻顶点$v_2$且$v_2\not\in S$
        - 以此类推，由于$D$有限，故对于某点$v_k$，无法找到其不在$S$中的外邻顶点
        - 而$deg^-(v_k)\geq1$，故$v_k$有外邻顶点在$S$内，即有有向圈，与题设矛盾
        - 故$\delta^-=0$

    - > 试证：存在$D$的一个顶点序列$v_1,v_2,\cdots,v_\nu$，使得对于任给$i(1\leq i\leq\nu)$，$D$的每条以$v_i$为终点的有向边在$\{v_1,v_2,\cdots,v_{i-1}\}$中都有它的起点

        - 由于$D$无有向圈，则有拓扑排序，而且刚好符合要求

- ### 3.

    - > 证明：任给无向图$G$，$G$都有一个定向图$D$，使得对于所有$v\in V(G)$，都有$\left|\deg^+(v)-\deg^-(v)\right|\leq1$成立
    
        - 仅需考虑$G$连通
        - 若$G$中无奇度顶点，则$G$为$Euler$图。找到$G$的一条$Euler$回路并按回路走向给每条边定向，即有$\deg^+(v)=\deg^-(v)$，$\forall v\in V(G)$
        - 若$G$中有奇度顶点$v_1,v_2,\cdots,v_k$（$k$必为偶数），增加一点$v_0$并与所有奇度顶点连一条边，得到图$G'$
        - 则$G'$为$Euler$图，找到其一条$Euler$回路并定向，此时$\deg^{+'}(v)=\deg^{-'}(v)$，$\forall v\in V(G')$
        - 删去增加的$k$条边对应的有向边后有$|\deg^+(v)-\deg^-(v)|
            \leq1$，$\forall v\in V(G)$