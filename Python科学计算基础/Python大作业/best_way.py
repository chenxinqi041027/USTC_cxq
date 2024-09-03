import tkinter
#from PIL import Image, ImageTk
import numpy as np
import matplotlib.pyplot as plt # 导入 Matplotlib 工具包
import networkx as nx  # 导入 NetworkX 工具包
import sys

#创建无向图，并赋予代价和奖励
figure = nx.Graph()#创建画布
figure.add_edges_from([(0,1,{'cost':3,'reward':2}),(0,2,{'cost':1,'reward':2}),(0,3,{'cost':1,'reward':2}),
                            (1,2,{'cost':1,'reward':2}),(1,4,{'cost':1,'reward':2}),(1,9,{'cost':4,'reward':3}),
                            (2,3,{'cost':2,'reward':1}),(2,4,{'cost':2,'reward':1}),(2,5,{'cost':1,'reward':3}),
                            (3,5,{'cost':2,'reward':2}),(3,6,{'cost':3,'reward':2}),(3,7,{'cost':1,'reward':2}),
                            (4,5,{'cost':4,'reward':3}),(4,9,{'cost':1,'reward':2}),(5,6,{'cost':3,'reward':1}),
                            (5,9,{'cost':1,'reward':2}),(5,10,{'cost':4,'reward':3}),(5,12,{'cost':3,'reward':2}),
                            (6,7,{'cost':1,'reward':1}),(6,8,{'cost':2,'reward':2}),(6,12,{'cost':2,'reward':1}),
                            (6,13,{'cost':4,'reward':3}),(6,14,{'cost':3,'reward':2}),(7,8,{'cost':4,'reward':3}),
                            (8,14,{'cost':3,'reward':2}),(8,15,{'cost':3,'reward':2}),(9,10,{'cost':1,'reward':2}),
                            (9,11,{'cost':1,'reward':3}),(10,11,{'cost':3,'reward':2}),(10,12,{'cost':3,'reward':1}),
                            (11,12,{'cost':3,'reward':4}),(11,16,{'cost':6,'reward':5}),(12,13,{'cost':2,'reward':1}),
                            (12,16,{'cost':3,'reward':4}),(13,14,{'cost':3,'reward':4}),(13,15,{'cost':2,'reward':1}),
                            (13,16,{'cost':2,'reward':1}),(13,17,{'cost':3,'reward':1}),(14,15,{'cost':1,'reward':3}),
                            (15,17,{'cost':3,'reward':2}),(16,17,{'cost':1,'reward':3})])  # 向图中添加多条赋权边: (node1,node2,cost,reward)

pos={0:(0,8),1:(7,12),2:(6,9),3:(5,6),4:(11,10),5:(14,8),  # 指定顶点位置
        6:(17,6),7:(10,4),8:(19,4),9:(18,12),10:(21,10),11:(28,12),
        12:(25,8),13:(30,7),14:(24,5),15:(29,4),16:(32,10),17:(37,8)}

fig, ax = plt.subplots(figsize=(9, 6))
nx.draw(figure, pos, with_labels=True, node_color='cyan', alpha=0.8)
cost_label = nx.get_edge_attributes(figure,'cost')  # 边的权值
reward_label = nx.get_edge_attributes(figure,'reward')  # 边的权值
nx.draw_networkx_edge_labels(figure,pos,edge_labels=cost_label,label_pos=0.4,font_color='m')  # 显示边的权值
nx.draw_networkx_edge_labels(figure,pos,edge_labels=reward_label,label_pos=0.6,font_color='m')  # 显示边的权值
nx.draw_networkx_nodes(figure,pos,nodelist=[0,17],node_color='yellow')  # 设置顶点颜色：N1,N17
plt.savefig('squares_plot.png',bbox_inches='tight') #保存图片
figure_1 = figure_2 = figure_3 = figure.copy()#复制图像

#创建窗口的函数
def initial(title_):
    windows = tkinter.Tk()#创建窗口
    windows.title(title_)#设置标题
    windows.geometry('500x500')
    windows.configure(background='White')
    return windows
window = initial('选择必经点，必经边，禁止边')

#输入框
#设置必经点
text1 = tkinter.Label(window,bd=4,fg='black',bg='white',text='输入必经点，中间用空格隔开')
text1.place(x=0,y=0)
entry1 = tkinter.Entry(window,width=20)
entry1.place(x=0,y=20)

#设置必经边
text2 = tkinter.Label(window,bd=4,fg='black',bg='white',text='输入必经边的首尾顶点，中间用空格隔开')
text2.place(x=0,y=50)
entry2 = tkinter.Entry(window,width=20)
entry2.place(x=0,y=70)

#设置禁止边
text3 = tkinter.Label(window,bd=4,fg='black',bg='white',text='输入禁止边首尾顶点，中间用空格隔开')
text3.place(x=0,y=100) 
entry3 = tkinter.Entry(window,width=20)
entry3.place(x=0,y=120)

#设置能接受的最小代价值
text4 = tkinter.Label(window,bd=4,fg='black',bg='white',text='输入能接受的最大代价值')
text4.place(x=0,y=150) 
entry4 = tkinter.Entry(window,width=20)
entry4.place(x=0,y=170)

#主函数
def main(r,s,t,u):
    #获取键入值
    a=[];b=[];c=[]
    temp1 = r.get()
    a = temp1.split()#必经点
    temp2 = s.get()
    b = temp2.split()#必经边
    temp3 = t.get()
    c = temp3.split()#禁止边
    temp4 = u.get()
    d = int(temp4)#最大代价值
    window.destroy()#关闭窗口
    #处理键入值
    must = b+a
    for i in range(0,len(must)):
        must[i] = int(must[i])
    must=tuple(must)#改成元组
    figure1 = figure.copy()#copy图像
    for i in range(0,len(c)-1,2):
        figure1.remove_edge(int(c[i]),int(c[i+1])) 
    #置初值
    Path_cost = minPath = 1e9  
    minWPath =[]
    maxPath = maxPath_result=0  
    for path in nx.all_simple_paths(figure1, 0, 17):  # 所有起点为0、终点为17的简单路径
        if all(n in path for n in (tuple(set(must)))): # 满足路径中包括必经点和必经边的路径
            #解决必经边，判断必经边相邻
            flag=0
            for i in range(0,len(b),2):
                p=path.index(must[i])#起点的位置
                if(path[p-1]!=must[i+1] and path[p+1]!=must[i+1]):#判断是否相邻
                    flag=1
                    break
            if(flag==1):continue
            Path_cost = sum(figure1.edges[edge]['cost'] for edge in nx.utils.pairwise(path))#计算路径的cost
            Path_reward = sum(figure1.edges[edge]['reward'] for edge in nx.utils.pairwise(path))#计算路径的reward
            if Path_cost < minPath:#取最小代价
                minPath = Path_cost
                minWPath = path
            if Path_reward > maxPath:#取最大奖赏
                maxPath = Path_reward
                maxWPath = path
            if Path_cost < d:#判断代价值是否小于指定值
                if Path_reward >maxPath_result:#取其中的最大奖赏
                    maxPath_result = Path_reward
                    maxPath_result_cost = Path_cost
                    maxWPath_result = path
    #最小代价
    def fig1():
        edgeList1 = []
        for i in range(len(minWPath)-1):
            edgeList1.append((minWPath[i],minWPath[i+1]))
        nx.draw_networkx_edges(figure_1,pos,edgelist=edgeList1,edge_color='b',width=4)  # 设置边的颜色，蓝色
        plt.savefig('最小代价.png',bbox_inches='tight') #保存图片
        print("\n最优路径问题（带有禁止点、禁止边、必经点、必经边的约束条件）")
        print("N0 到 N17 的最小代价: ", minWPath)
        print("N0 到 N17 的最小代价值: ", minPath)
     #最大奖赏
    def fig2():
        edgeList2 = []
        for i in range(len(maxWPath)-1):
            edgeList2.append((maxWPath[i],maxWPath[i+1]))
        nx.draw_networkx_edges(figure_2,pos,edgelist=edgeList2,edge_color='y',width=4)  # 设置边的颜色，黄色
        plt.savefig('最大奖赏.png',bbox_inches='tight') #保存图片
        print("\n最优路径问题（带有禁止点、禁止边、必经点、必经边的约束条件）")
        print("N0 到 N17 的最大奖赏: ", maxWPath)
        print("N0 到 N17 的最大奖赏值: ", maxPath)
    #条件最优路径
    def fig3():
        edgeList3 = []
        for i in range(len(maxWPath_result)-1):
            edgeList3.append((maxWPath_result[i],maxWPath_result[i+1]))
        nx.draw_networkx_edges(figure_3,pos,edgelist=edgeList3,edge_color='k',width=4)  # 设置边的颜色，黑色
        plt.savefig('条件最优路径.png',bbox_inches='tight') #保存图片
        print("\n最优路径问题（带有禁止点、禁止边、必经点、必经边的约束条件）")
        print("N0 到 N17 的最优路径: ", maxWPath_result)
        print("N0 到 N17 的代价值: ", maxPath_result_cost)
        print("N0 到 N17 的奖赏值: ", maxPath_result)

    #新建窗口
    window1 = initial('选择条件')
    button1 = tkinter.Button(window1,width=10,height=1,command=lambda:fig1(),text='最小代价')
    button1.place(x=0,y=0)
    button2 = tkinter.Button(window1,width=10,height=1,command=lambda:fig2(),text='最大奖赏')
    button2.place(x=0,y=50)
    button3 = tkinter.Button(window1,width=10,height=1,command=lambda:fig3(),text='最优路径')
    button3.place(x=0,y=100)
    button4 = tkinter.Button(window1,width=10,height=1,command=lambda:(window1.destroy(),sys.exit(0)),text='关闭窗口')
    button4.place(x=0,y=150)
    window1.mainloop()#等待消息循环

#设置获取输入的按钮
button = tkinter.Button(window,width=20,height=1,command=lambda:(main(entry1,entry2,entry3,entry4)),text='生成条件最短路径')
button.place(x=10,y=200)
window.mainloop() #使窗口等待



