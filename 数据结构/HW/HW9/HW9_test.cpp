#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
//边
typedef struct ArcNode {
    int adjvex;
    struct ArcNode* nextarc;
} ArcNode;
//顶点
typedef struct VertexNode {
    int data;//编号
    ArcNode* firstarc;
} VertexNode;

typedef struct {
    VertexNode vertices[MAXSIZE];
    int visited[MAXSIZE];
    int vexnum, arcnum;//顶点数量，边数量
} ALGraph;

ALGraph createGraph(int vexnum, int arcnum) {
    ALGraph G;
    G.vexnum = vexnum;
    G.arcnum = arcnum;
    
    for (int i = 0; i < vexnum; i++) {
        G.vertices[i].data = i;//顶点编号
        G.vertices[i].firstarc = NULL;
        G.visited[i] = 0;
    }
    
    printf("Enter the arcs in the format (start end):\n");
    for (int i = 0; i < arcnum; i++) {
        int start, end;
        scanf("%d %d", &start, &end);
        
        ArcNode* arc = (ArcNode*)malloc(sizeof(ArcNode));
        //连接构造图
        arc->adjvex = end;
        arc->nextarc = G.vertices[start].firstarc;
        G.vertices[start].firstarc = arc;
        
        arc = (ArcNode*)malloc(sizeof(ArcNode));
        arc->adjvex = start;
        arc->nextarc = G.vertices[end].firstarc;
        G.vertices[end].firstarc = arc;
    }
    
    return G;
}

int exist_path_len(ALGraph G, int i, int j, int k) {
    if (i == j && k == 0)
        return 1; // 找到了一条路径，且长度符合要求
    else if (k > 0) {
        G.visited[i] = 1;
        ArcNode* p = G.vertices[i].firstarc;
        while (p) {
            int l = p->adjvex;
            if (!G.visited[l] && exist_path_len(G, l, j, k - 1))//递归查找，每次将剩余路径减一
                return 1; 
            p = p->nextarc;
        }
        G.visited[i] = 0; //若没有找到则将结点恢复至未访问状态
    }
    return 0; // 没找到
}

int main(){
    int vexnum, arcnum;
    printf("Enter the number of vertices in the graph: ");//图的顶点数
    scanf("%d", &vexnum);
    printf("Enter the number of arcs in the graph: ");//图的边数
    scanf("%d", &arcnum);
    
    ALGraph graph = createGraph(vexnum, arcnum);//创建图
    
    int start, end, length;
    printf("Enter the start vertex: ");//起点
    scanf("%d", &start);
    printf("Enter the end vertex: ");//终点
    scanf("%d", &end);
    printf("Enter the required path length: ");//路径长度
    scanf("%d", &length);
    
    if (exist_path_len(graph, start, end, length))
        printf("There exists a simple path of length %d between vertex %d and %d.\n", length, start, end);//存在
    else
        printf("There does not exist a simple path of length %d between vertex %d and %d.\n", length, start, end);//不存在
    
    return 0;
}
