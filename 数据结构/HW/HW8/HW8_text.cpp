#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

//创建结点
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

//创建链表
typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX_VERTICES];
    int visited[MAX_VERTICES];
} Graph;

//创建图
Graph* createGraph(int vertices) {//根据结点个数创建图
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;//初始化visited[n]
    }

    return graph;
}

//加边
void addEdge(Graph* graph, int src, int dest) {
    //在两个结点之间加边，即进行链表指针域连接
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    //由于是无向图，要进行两次加边操作
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

//非递归的深度优先算法
void DFS(Graph* graph, int startVertex) {
    int stack[MAX_VERTICES];//定义一个数组作为栈
    int top = -1;//栈顶指针

    stack[++top] = startVertex;//将起点压入栈中

    while (top >= 0) {
        int currentVertex = stack[top--];

        if (!graph->visited[currentVertex]) {//visited[n]为0，即还未被访问，需要输出
            printf("%d ", currentVertex);
            graph->visited[currentVertex] = 1;//标记为访问过
        }

        Node* temp = graph->adjLists[currentVertex];

        while (temp) {//遍历所有的邻接结点
            int adjVertex = temp->vertex;

            if (!graph->visited[adjVertex]) {//存入还未被访问过的结点
                stack[++top] = adjVertex;
            }

            temp = temp->next;
        }
    }
}

//释放空间
void freeGraph(Graph* graph) {
    if (graph) {
        for (int i = 0; i < graph->numVertices; i++) {
            Node* node = graph->adjLists[i];
            Node* temp;

            while (node) {
                temp = node;
                node = node->next;
                free(temp);
            }
        }

        free(graph);
    }
}

// Sample test case
int main() {
    Graph* graph = createGraph(6);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);

    printf("The Result: ");
    DFS(graph, 0);

    freeGraph(graph);

    return 0;
}
