## 二（2）：

  - 设树叶数量为$\displaystyle n_1=|V(T)|-\sum_{i=2}^kn_i$
  - 则$\displaystyle\sum_{u\in V(T)}deg(u)=\sum_{i=1}^ni\cdot n_i=\sum_{i=2}^ki\cdot n_i+|V(T)|-\sum_{i=2}^kn_i=2(|V(T)|-1)$
  - 有$\displaystyle|V(T)|=2+\sum_{i=2}^k(i-1)n_i$
  - 树叶数量为$\displaystyle n_1=|V(T)|-\sum_{i=2}^kn_i=2+\sum_{i=2}^k(i-2)n_i$

## 二（4）：

  - 不妨设度数为$i$的顶点数为$m_i$，$i=1,2,\cdots,\Delta(T)$
  - $$
    \begin{align}
    有\sum_{i=1}^{\Delta(T)}i*m_i&=2\sum_{i=1}^{\Delta(T)}m_i-2\\
    2&=\sum_{i=1}^{\Delta(T)}(2-i)m_i\\
    2&=m_1-\sum_{i=2}^{\Delta(T)}(i-2)m_i\\
    2&\leq m_1-(n-2)m_n\\
    2&\leq m_1-(n-2)\\
    n&\leq m_1
    \end{align}
    $$
  - 即至少有$n$片树叶

## 二（5）：

- 必要性：
    - 若$G$是森林
    - 不妨定义一个$V(G)$外的新点$u_e$，并由其向$G$的所有连通片中的某一个点连一条边，得到图$G'$
    - 将$G$的各连通片缩为点后，$E(G')-E(G)$和连通片及点$u_e$构成星图，且连通片内部无圈，故$G'$也无圈
    - 又$G'$无重边、无环且连通，故$G'$为树
    - 有$|E(G')|=\varepsilon+\omega=|V(G')|-1=\nu+1-1=\nu$
    - 故有$\varepsilon=\nu-\omega$
- 充分性：
    - 同理构造图$G'$
    - 由于$\varepsilon=\nu-\omega$，故$|E(G')|=\varepsilon+\omega=\nu=|V(G')|-1$
    - 而且$G'$与$G$所有的连通片连通，故$G'$为树
    - 而删除树$G'$上任意数量的边后得到图$G$，$G$必为森林
- $Q.E.D.$