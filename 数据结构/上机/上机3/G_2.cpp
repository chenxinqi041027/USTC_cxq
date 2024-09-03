#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// 邻接矩阵结构体
typedef struct {
    int edges[MAX_VERTICES][MAX_VERTICES];
    int n; // 顶点数
} AdjMatrix;

// 邻接表结构体
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} AdjList[MAX_VERTICES];

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

// 创建邻接表
/*void createAdjList(AdjList adjList) {
    int V, E;
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    // 初始化邻接表
    for (int i = 0; i < V; i++) {
        adjList[i].head = NULL;
    }

    // 输入每条边的两个顶点和权值
    printf("Enter the two vertices and weight of each edge (separated by space):\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        // 创建新节点
        Node* node1 = (Node*)malloc(sizeof(Node));
        node1->vertex = v;
        node1->weight = w;
        node1->next = adjList[u].head;
        adjList[u].head = node1;

        Node* node2 = (Node*)malloc(sizeof(Node));
        node2->vertex = u;
        node2->weight = w;
        node2->next = adjList[v].head;
        adjList[v].head = node2;
    }
}*/

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

// 输出邻接表
/*void printAdjList(AdjList adjList) {
    printf("Adjacency List:\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (adjList[i].head != NULL) {
            printf("%d -> ", i);
            Node* currentNode = adjList[i].head;
            while (currentNode != NULL) {
                printf("(%d, %d) ", currentNode->vertex, currentNode->weight);
                currentNode = currentNode->next;
            }
            printf("\n");
        }
    }
}*/

// 深度优先遍历
/*void dfs(AdjMatrix* G, int visited[], int v) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < G->n; i++) {
        if (G->edges[v][i] && !visited[i]) {
            dfs(G, visited, i);
        }
    }
}*/

// 非递归深度优先遍历
void non_recursive_dfs(AdjMatrix* G, int visited[], int v) {
    int stack[MAX_VERTICES];
    int top = -1;
    stack[++top] = v;

    while (top != -1) {
        int w = stack[top--];

        if (!visited[w]) {
            visited[w] = 1;
            printf("%d ", w);

            for (int i = G->n-1; i >= 0; i--) {
                if (G->edges[w][i] && !visited[i]) {
                    stack[++top] = i;
                }
            }
        }
    }
}

// 广度优先遍历
void bfs(AdjMatrix* G, int visited[], int v) {
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    queue[rear++] = v;
    visited[v] = 1;

    while (front != rear) {
        int w = queue[front++];
        printf("%d ", w);

        for (int i = 0; i < G->n; i++) {
            if (G->edges[w][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

int main() {
    AdjMatrix adjMatrix;
    createAdjMatrix(&adjMatrix);
    printAdjMatrix(&adjMatrix);

    AdjList adjList;
    //createAdjList(adjList);
    //printAdjList(adjList);

    int visited[MAX_VERTICES];
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = 0;
    }

    //printf("Depth First Traversal:\n");
    //dfs(&adjMatrix, visited, 0);
    //printf("\n");

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

    return 0;
}
