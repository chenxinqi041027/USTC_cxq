#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

// 邻接矩阵结构体
typedef struct {
    int edges[MAX_VERTICES][MAX_VERTICES];
    int n; // 顶点数
} AdjMatrix;

// 创建邻接矩阵
void createAdjMatrix(AdjMatrix* G) {
    int V, E;
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &V, &E);
    G->n = V;

    // 初始化邻接矩阵
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            G->edges[i][j] = 0;
        }
    }

    // 输入每条边的两个顶点和权值
    printf("Enter the two vertices and weight of each edge (separated by space):\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        G->edges[u][v] = w;
        G->edges[v][u] = w;
    }
}

// 输出邻接矩阵
void printAdjMatrix(AdjMatrix* G) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            printf("%d ", G->edges[i][j]);
        }
        printf("\n");
    }
}

void prim(AdjMatrix* G) {
    int visited[MAX_VERTICES];
    int parent[MAX_VERTICES]; // 存储每个顶点在最小生成树中的父节点
    int distance[MAX_VERTICES]; // 存储每个顶点到最小生成树的距离
    int minDistance, u, v;

    // 初始化visited、parent和distance数组
    for (int i = 0; i < G->n; i++) {
        visited[i] = 0;
        parent[i] = -1;
        distance[i] = INT_MAX;
    }

    // 选取起点为第一个顶点
    distance[0] = 0;

    for (int count = 0; count < G->n-1; count++) {
        // 找出当前未加入最小生成树的顶点中到最小生成树距离最短的顶点
        minDistance = INT_MAX;
        for (int i = 0; i < G->n; i++) {
            if (!visited[i] && distance[i] < minDistance) {
                minDistance = distance[i];
                u = i;
            }
        }

        visited[u] = 1;

        // 更新与u相邻的顶点到最小生成树的距离和它们的父节点
        for (int v = 0; v < G->n; v++) {
            if (G->edges[u][v] && !visited[v] && G->edges[u][v] < distance[v]) {
                parent[v] = u;
                distance[v] = G->edges[u][v];
            }
        }
    }

    // 输出最小生成树的边信息
    printf("Minimum Spanning Tree:\n");
    for (int i = 1; i < G->n; i++) {
        printf("(%d, %d, %d)\n", parent[i], i, G->edges[i][parent[i]]);
    }
}

int main() {
    AdjMatrix adjMatrix;
    createAdjMatrix(&adjMatrix);
    printAdjMatrix(&adjMatrix);

    prim(&adjMatrix);

    return 0;
}
