# 作业9nd

## 五.11：设$G$是顶点集合划分为$X$和$Y$的二分图，则$G$的最大匹配中边数等于$|X|-\displaystyle\max_{S\subset X}\large(|S|-|N(S)|\big)$

- 由$König-Egerváry$定理知二分图$G$中有$\alpha(G)=\beta(G)$
- 对于$G$的某个覆盖$C$，不妨设$S=X-C\cap X$，$T=C\cap Y$
- 则$\forall uv\in E(G)$且$u\in S$，$v\in Y$，都有$v\in T$
- 即$N(S)\subseteq T$
- 故$\beta(G)=\displaystyle\min_{S\subseteq X,N(S)\subseteq T,T\subseteq Y}\left\{|X|-|S|+|T|\right\}=\min_{S\subseteq X}\left\{|X|-|S|+|N(S)|\right\}=|X|-\max_{S\subseteq X}\left\{|S|-|N(S)|\right\}$
- 即$\alpha(G)=|X|-\displaystyle\max_{S\subseteq X}\left\{|S|-|N(S)|\right\}$

## 五.13：用$Tutte$定理来证明$Hall$定理

- 充分性：
    - 当二分图$G$中存在将$X$中顶点都许配的匹配$M$
    - 则$\forall S\subseteq X$，$S$内的点都被$M$许配，故$|N(S)|\geq|S|$

- 必要性：
    - 若对于二分图$G$，$\forall S\subseteq X$都有$|N(S)|\geq|S|$
    - 则显然有$|Y|\geq|N(X)|\geq|X|$
    - 若二分图$G$中不存在将$X$中顶点都许配的匹配，则$\forall Y'\subseteq Y$且$|Y'|=|X|$，均满足由点$X+Y'$及其内部边构成的子图$G'$无完备匹配
    - 且$\forall S\subseteq X$都有$|N'(S)|\geq|S|$
    - 由$Tutte$定理知$\exist S\subseteq V(G)$，有$o(G'-(X-S))>|X-S|$
    - 则$|Y'-N'(S)|+o(S+N'(S))>|X-S|$，即$o(S+N'(S))+S>N'(S)$
    - 对于$S+N'(S)$点生成子图$G''$，记其中奇片分别为$G_1,G_2,\cdots,G_n$
    - 则显然对于任意奇片$G_i$，都有$|V(G_i)\cap S|<|V(G_i)\cap N'(S)|$
    - 则$N'(S)\geq o(S+N'(S))+S$，矛盾
    - 故$\forall Y'\subseteq Y$且$|Y'|=|X|$，均不存在使$o(G'-(X-S))>|X-S|$的$S$
    - 由$Tutte$定理知，二分图$G$中存在将$X$都许配的匹配

## 五.14：若$G$是$k-1$边连通的$k$次正则图，且$\nu(G)$是偶数，则$G$有完备匹配

- 当$k=1$时结论显然成立
- 当$k\geq2$时，任取$S\subseteq V(G)$
- 若$S=\emptyset$，由于$\nu(G)$为偶数，故$o(G-S)=0\leq|S|=0$
- 若$S\neq\emptyset$，记$G-S$中的奇片分别为$G_1,G_2,\cdots,G_n$，并定义$m_i=|\{uv|u\in G_i,v\in S且uv\in E(G)\}|$
- 由于$\kappa'(G)=k-1$，故$m_i\geq\kappa'(G)=k-1$
- 若对于某个奇片$G_p$，其满足$m_p=k-1$
- 则$m_p=\displaystyle\sum_{v\in V(G_p)}\deg_G(v)-2\varepsilon(G_p)=k\nu(G_p)-2\varepsilon(G_p)=k-1$
- 即$2\varepsilon(G_p)=k(\nu(G_p)-1)+1$，而由于$G_p$为奇片，故等式无法成立
- 则对于所有奇片$G_i$都有$m_i\geq k$
- 故有$k|S|\geq\displaystyle\sum_{i=1}^nm_i\geq kn$
- 即$|S|\geq o(G-S)$
- 综上，由$Tutte$定理知，原命题成立。

## 五.16：由$a,b,c,d,e,f$六个人组成检查团，检查$5$个单位的工作。若某单位与某人有过工作联系，则不能选派此人到该单位去检查工作。已知第一单位与$b,c,d$有过联系，第二单位与$a,e,f$有过联系，第三单位与$a,b,e,f$，第四单位与$a,b,d,f$，第五单位与$a,b,c$有过联系，请列出去各个单位进行检查的人员名单。

- | 一   | 二   | 三   | 四   | 五   |
    | ---- | ---- | ---- | ---- | ---- |
    | a    | b    | d    | e    | f    |

## 五.19：证明：$Kuhn-Munkreas$算法中修改顶标后，$\hat{l}$仍然是可行顶标

- 若存在$x\in X$，$y\in Y$满足$\hat{l}(x)+\hat{l}(y)<w(xy)$
- 则显然$\hat{l}(x)=l(x)-\alpha_l$，$\hat{l}(y)=l(y)$且$x\in S$，$y\not\in T$
- 故$\displaystyle\min_{x_i\in S,y_j\not\in T}\{l(x_i)+l(y_j)-w(x_iy_j)\}=\alpha_l>l(x)+l(y)-w(xy)$，矛盾
- 故$\hat{l}$任然是可行顶标

## 五.20：$Kuhn-Munkreas$算法种修改顶标后，由可行顶标$\hat{l}$得到相等子图$G_{\hat{l}}$。证明：在算法的第$(3)$步，在$G_{\hat{l}}$上找到的顶点子集$T$包含了在$G_l$上找到的顶点子集$T$，且至少多一个顶点。由此可知，$kuhn-Munkreas$算法最终能够找到某个相等子图，该相等子图有完美匹配，从而说明$Kuhn-Munkreas$算法的正确性

- 不妨假设$\alpha_l=l(x)+l(y)-w(xy)$，其中$x\in S$，$y\in \complement_YT$
- 则修改后$\hat{l}(x)+\hat{l}(y)=l(x)-\alpha_l+l(y)=w(xy)$，
- 不妨记$u$到$x$的交错轨道为$P(u,x)=uy_1x_1y_2x_2\cdots x$，则$M'=M\oplus E(P(u,x))+\{xy\}$即为更大的匹配
- 则在$G_{\hat{l}}$上找到的顶点子集$T$将至少比在$G_l$上找到的顶点子集$T$多一个点$y$，原题得证

## 六.3：设$G$是恰有$2k$个奇度顶点的连通图，证明：$G$中存在$k$条边不重的形迹$P_1,P_2,\cdots,P_k$，使得$E(G)=\displaystyle\bigcup_{i=1}^kE(P_i)$

- 不妨记$G$中$2k$个奇度顶点分别为$v_1,v_2,\cdots,v_{2k}$，定义图$G'$满足$V(G')=V(G)$，$E(G')=E(G)+\displaystyle\sum_{i=1}^k\{v_{2i-1}v_{2i}\}$
- 则$G'$中所有顶点度数均为偶数，存在$Euler$回路，不妨记其为$P$
- 在$P$中删除边$\{v_1v_2\},\{v_3v_4\},\cdots,\{v_{2k-1}v_{2k}\}$后将分为$k$段边不重的形迹，即为所求

## 六.5：如何将$9$个$\alpha$，$9$个$\beta$，$9$个$\gamma$排成一个圆形，使得由这些$\alpha,\beta,\gamma$产生的$27$个长为$3$的符号串在其中都只出现且只出现一次？

- 定义包含$27$个点的有向图$D$，其中$V(D):=\{x_0,x_1,\cdots,x_{26}\}$

- 对于点$x_i$和$x_j$，$i\neq j$，设$i$和$j$的三进制表示分别为$(i_2i_1i_0)_3$和$(j_2j_1j_0)_3$，边$x_ix_j$存在当且仅当满足$i_1=j_2$和$i_0=j_1$

- 则$\forall v\in V(D)$，都有$\deg^+(v)=3=\deg^-(v)$，则$D$是$Euler$图

- 可构造$\alpha\alpha\alpha\beta\alpha\alpha\gamma\alpha\beta\beta\alpha\beta\gamma\alpha\gamma\beta\alpha\gamma\gamma\beta\beta\beta\gamma\beta\gamma\gamma\gamma$

    