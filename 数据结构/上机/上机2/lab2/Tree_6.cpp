#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//树结点
struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

//创建新结点
struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

//创建表达式树
struct Node* buildExpressionTree(char* postfix) {
    struct Node* stack[100];//栈
    int top = -1;//栈顶指针

    int len = strlen(postfix);
    for (int i = len-1; i >= 0; i--) {
        struct Node* newNode = createNode(postfix[i]);

        if (isdigit(postfix[i])) {//判断是否是数字
            stack[++top] = newNode;
        } else {
            newNode->left = stack[top--];
            newNode->right = stack[top--];
            stack[++top] = newNode;
        }
    }

    return stack[top];
}

//先序遍历
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%c ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

//中序遍历
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%c ", root->data);
        inorderTraversal(root->right);
    }
}

//后序遍历
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%c ", root->data);
    }
}

//计算结果
int evaluateExpressionTree(struct Node* root) {
    if (isdigit(root->data)) {
        return root->data - '0';
    }

    int leftVal = evaluateExpressionTree(root->left);//递归计算
    int rightVal = evaluateExpressionTree(root->right);

    switch (root->data) {
        case '+':
            return leftVal + rightVal;
        case '-':
            return leftVal - rightVal;
        case '*':
            return leftVal * rightVal;
        case '/':
            return leftVal / rightVal;
        default:
            printf("Invalid operator\n");
            exit(1);
    }
}

int main() {
    char postfix[100];

    printf("Enter the postfix expression: ");
    scanf("%s", postfix);

    struct Node* expressionTree = buildExpressionTree(postfix);

    printf("\nPreorder traversal result: ");
    preorderTraversal(expressionTree);

    printf("\nInorder traversal result: ");
    inorderTraversal(expressionTree);

    printf("\nPostorder traversal result: ");
    postorderTraversal(expressionTree);

    int result = evaluateExpressionTree(expressionTree);
    printf("\nThe value of the expression is: %d\n", result);

    return 0;
}
/*
*3-2+51
3*(2-(5+1))
*/