import numpy as np
import matplotlib.pyplot as plt # 导入 Matplotlib 工具包
import networkx as nx  # 导入 NetworkX 工具包
'''1.算法搞明白
2.运用tkinter设置窗口 输入必经边 输入必经点 禁止边
3.将图像输出 并动态显示'''

# 问题：最优路径分析
import numpy as np
import matplotlib.pyplot as plt # 导入 Matplotlib 工具包
import networkx as nx  # 导入 NetworkX 工具包

# 问题：蚂蚁的最优路径分析（西安邮电大学第12届数学建模竞赛B题）
gAnt = nx.Graph()  # 创建：空的 无向图
gAnt.add_weighted_edges_from([(0,1,3),(0,2,1),(0,3,1),
                            (1,2,1),(1,4,1),(1,9,4),
                            (2,3,1),(2,4,2),(2,5,1),
                            (3,5,2),(3,6,2),(3,7,1),
                            (4,5,1),(4,9,1),
                            (5,6,1),(5,9,3),(5,10,1),(5,12,3),
                            (6,7,1),(6,8,2),(6,12,2),(6,13,4),(6,14,3),
                            (7,8,1),
                            (8,14,1),(8,15,3),
                            (9,10,1),(9,11,1),
                            (10,11,1),(10,12,2),
                            (11,12,1),(11,16,1),
                            (12,13,2),(12,16,1),
                            (13,14,1),(13,15,2),(13,16,2),(13,17,1),
                            (14,15,1),
                            (15,17,4),
                            (16,17,1)])  # 向图中添加多条赋权边: (node1,node2,weight)

pos={0:(0,8),1:(7,12),2:(6,9),3:(5,6),4:(11,10),5:(14,8),  # 指定顶点位置
     6:(17,6),7:(10,4),8:(19,4),9:(18,12),10:(21,10),11:(28,12),
     12:(25,8),13:(30,7),14:(24,5),15:(29,4),16:(32,10),17:(37,8)}

fig, ax = plt.subplots(figsize=(9, 6))
nx.draw(gAnt, pos, with_labels=True, node_color='cyan', alpha=0.8)
labels = nx.get_edge_attributes(gAnt,'weight')  # 边的权值
nx.draw_networkx_edge_labels(gAnt,pos,edge_labels=labels, font_color='m')  # 显示边的权值
nx.draw_networkx_nodes(gAnt,pos,nodelist=[0,17],node_color='yellow')  # 设置顶点颜色：N1,N17
nx.draw_networkx_nodes(gAnt,pos,nodelist=[7,12],node_color='lime')  # 设置顶点颜色：N7,N12
nx.draw_networkx_edges(gAnt,pos,edgelist=[(2,4),(13,14)],edge_color='lime',width=3)  # 设置指定边的颜色、宽度
nx.draw_networkx_edges(gAnt,pos,edgelist=[(11,12)],edge_color='r',width=3)  # 设置指定边的颜色、宽度
plt.show()
# 7. 限制条件：必经点 N7,N12，必经边 (N2,N4), (N13,N14)，禁止边 (11,12)
# 解决方案：遍历从起点到终点的简单路径，求满足必经边条件的最短路径
gAntS = gAnt.copy()
gAntS.remove_edge(11,12)  # 删除禁止边 (11,12)
lMinWPath = minWPath = 1e9  # 置初值
for path in nx.all_simple_paths(gAntS, 0, 17):  # 所有起点为0、终点为17的简单路径
    if all(n in path for n in (2,4,7,12,13,14)): # 满足路径中包括顶点 N7,N12
        # 检查 (N2,N4)
        p1 = path.index(2)  # N2 的位置
        if (path[p1-1]!=4 and path[p1+1]!=4): continue  # 判断 N2~N4 是否相邻
        # 检查 (N13,N14)
        p2 = path.index(13)  # # N13 的位置
        if (path[p2-1]!=14 and path[p2+1]!=14): continue  # 判断 N13~N14 是否相邻
        lenPath = sum(gAntS.edges[edge]['weight'] for edge in nx.utils.pairwise(path))
        if lenPath < lMinWPath:
            lMinWPath = lenPath
            minWPath = path

print("\n蚂蚁最优路径问题（带有禁止点、禁止边、必经点、必经边的约束条件）")
print("约束条件：必经点 N7,N12，必经边 (N2,N4), (N13,N14)，禁止边 (11,12)")
print("N0 到 N17 的最短加权路径: ", minWPath)
print("N0 到 N17 的最短加权路径长度: ", lMinWPath)

edgeList = []
for i in range(len(minWPath)-1):
    edgeList.append((minWPath[i],minWPath[i+1]))
nx.draw_networkx_edges(gAnt,pos,edgelist=edgeList,edge_color='b',width=4)  # 设置边的颜色
plt.show()
