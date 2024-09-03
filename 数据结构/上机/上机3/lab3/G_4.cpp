#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100
//邻接矩阵
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
// 非递归深度优先遍历
void non_recursive_dfs(AdjMatrix* G, int visited[], int v) {
    int stack[MAX_VERTICES];
    int top = -1;
    stack[++top] = v;//入栈

    while (top != -1) {
        int w = stack[top--];//取栈顶指针

        if (!visited[w]) {
            visited[w] = 1;
            printf("%d ", w);

            for (int i = G->n-1; i >= 0; i--) {
                if (G->edges[w][i] && !visited[i]) {
                    stack[++top] = i;//入栈
                }
            }
        }
    }
}
// 广度优先遍历
void bfs(AdjMatrix* G, int visited[], int v) {
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    queue[rear++] = v;//入队
    visited[v] = 1;

    while (front != rear) {
        int w = queue[front++];//取队首
        printf("%d ", w);

        for (int i = 0; i < G->n; i++) {
            if (G->edges[w][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
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

// Dijkstra算法
void dijkstra(AdjMatrix* G, int source) {
    int dist[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    int path[MAX_VERTICES];

    // 初始化
    for (int i = 0; i < G->n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        path[i] = -1;
    }

    dist[source] = 0;

    for (int count = 0; count < G->n - 1; count++) {
        int u = -1;
        int minDist = INT_MAX;

        // 找出当前未加入最短路径的顶点中距离最短的顶点
        for (int i = 0; i < G->n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                u = i;
                minDist = dist[i];
            }
        }

        visited[u] = true;

        // 更新与u相邻的顶点的最短距离和路径
        for (int v = 0; v < G->n; v++) {
            if (!visited[v] && G->edges[u][v] && dist[u] + G->edges[u][v] < dist[v]) {
                dist[v] = dist[u] + G->edges[u][v];
                path[v] = u;
            }
        }
    }

    // 输出结果
    printf("Shortest paths from vertex %d:\n", source);
    for (int i = 0; i < G->n; i++) {
        if (i == source) {
            continue;
        }

        printf("vertex:%d dist:%d path: %d", i, dist[i],i);

        // 回溯查找路径
        int j = path[i];
        while (j != -1) {
            printf(" <- %d ", j);
            j = path[j];
        }
        printf("\n");
    }
}
 
int main() {
    AdjMatrix adjMatrix;
    createAdjMatrix(&adjMatrix);
    printAdjMatrix(&adjMatrix);

    int visited[MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = 0;
    }

    printf("Non-recursive Depth First Traversal:\n");
    non_recursive_dfs(&adjMatrix, visited, 0);
    printf("\n");

    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = 0;
    }

    printf("Breadth First Traversal:\n");
    bfs(&adjMatrix, visited, 0);
    printf("\n");

    prim(&adjMatrix);

    int source;
    printf("Enter the source vertex for Dijkstra's algorithm: ");
    scanf("%d", &source);
    dijkstra(&adjMatrix, source);

    return 0;
}
/*
0 1 7
0 2 2
0 4 1
0 5 8
0 6 9
0 7 9
0 8 5
0 9 8
1 2 1
1 3 3
1 6 1
1 8 7
1 9 3
2 3 9
2 4 2
2 5 7
2 6 6
2 7 4
2 8 8
2 9 5
3 4 7
3 5 9
3 6 6
3 8 2
4 5 2
4 6 7
4 8 5
4 9 8
5 6 3
5 7 2
5 8 3
5 9 5
6 7 6
6 8 6
6 9 3
7 8 9
7 9 6
8 9 3

*/