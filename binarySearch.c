#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *root = NULL;

struct Node *stack[20];
int top = -1;

struct Node* stack2[20];
int top2 = -1;

struct Node *pop()
{
    return stack[top--];
};

void push(struct Node *root)
{
    stack[++top] = root;
};

void push2(struct Node* root){
    stack2[++top2] = root;
}

struct Node* pop2(){
    return stack2[top2--];
}

void clear_input()
{
    int c;
    while ((c = getchar()) != '\n');
}

int valid(char input[]){
    for (int i = 0; i < strlen(input); i++)
        {
            if (!isdigit(input[i]))
            {
                return 0;
            }
        }
    return 1;
}

struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
};

void insertNode(int data)
{

    struct Node *newNode = createNode(data);
    struct Node *current = root;
    struct Node *parent = NULL;

    if (root == NULL)
    {
        root = newNode;
        current = root;
        return;
    }

    while (current != NULL)
    {
        parent = current;
        if (data < current->data)
        {
            current = current->left;
        }
        else if (data > current->data)
        {
            current = current->right;
        }
        else
        {
            free(newNode);
        }
    }

    if (data < parent->data)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }
}

void preOrder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

void manualPreOrder(struct Node *root){
    if (root == NULL)
    {
        printf("Tree is Empty!..");
        return;
    }

    push(root);
    while (top != -1)
    {
        struct Node *check = pop();

        printf("%d ", check->data);

        if (check->right != NULL)
        {
            push(check->right);
        }
        if (check->left != NULL)
        {
            push(check->left);
        }
    }
}

void manualInOrder(struct Node* root){

    if(root == NULL){
        return;
    }

    struct Node* printNode = root;
    while(printNode!=NULL || top!=-1){

        while(printNode!=NULL){
            push(printNode);
            printNode = printNode->left;
        }

    printNode = pop();
    printf("%d ",printNode->data);
    printNode = printNode->right;
    }
};

void manualPostOrder(struct Node* root){

    if(root == NULL){
        return;
    }

    push(root);
    
    while(top!=-1){
    struct Node* printNode = pop();
    push2(printNode);
    
    if(printNode->left != NULL){
        push(printNode->left);
    }
    if(printNode->right != NULL){
        push(printNode->right);
    }
    }

    while(top2!=-1){
        struct Node* printNode = pop2();
        printf("%d ",printNode->data);
    }

}

struct Node* minNode(struct Node *node){
    while (node != NULL && node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

struct Node* deleteNode(struct Node *root, int value){

    if(root == NULL){
        printf("Tree is Empty!..");
        return root;
    }

    struct Node* current = root;
    struct Node* parent = NULL;

    while(current!=NULL && current->data!=value){
        parent = current;

        if(value < current->data){
            current = current->left;
        }else if(value > current->data){
            current = current->right;
        }
    }

    if(current == NULL){
        printf("Value Not Found!..");
        return root;
    }

    // If 1 or No childrens

    if(current->left == NULL || current->right == NULL){

        struct Node* child = (current->left!=NULL) ? current->left : current->right;

        if(parent == NULL){
            free(current);
            return child;
        }

        if(parent->left == current){
            parent->left = child;
        }else if(parent->right == current){
            parent->right = child;
        }

        free(current);
    }

    // 2 Childrens
    else {
        struct Node* rightSub = current->right;
        struct Node* rightSubParent = current;

        while (rightSub->left != NULL) {
            rightSubParent = rightSub;
            rightSub = rightSub->left;
        }

        current->data = rightSub->data;

        if (rightSubParent->left == rightSub)
            rightSubParent->left = rightSub->right;
        else
            rightSubParent->right = rightSub->right;

        free(rightSub);
    }

    printf("The value %d Deleted Sucessfully!..",value);

}

struct Node* updateNode(struct Node* root, int oldValue, int newValue) {
    
    printf("Updating %d to %d...\n", oldValue, newValue);

    deleteNode(root, oldValue);

    insertNode(newValue);
    
    return root;
}

int main()
{
    int choice, value,updated;
    char input[10];

    while (1)
    {
        printf("\n--- Tree Menu ---\n");
        printf("1. Insert Node\n");
        printf("2. Update Node\n");
        printf("3. PreOrder Traverse\n");
        printf("4. PostOrder Traverse\n");
        printf("5. InOrder Traverse\n");
        printf("6. Delete Node\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%s", &input);
        

        if (!valid(input))
        {   
            printf("Invalid input! \n");
            clear_input();
            continue;
        }

        choice = atoi(input);

        switch (choice)
        {
        case 1:
            printf("Enter value to Insert: ");
            scanf("%s", &input);
            if (!valid(input)){
                printf("Invalid input! \n");
                clear_input();
                continue;
            }
            value = atoi(input);
            insertNode(value);
            break;
        case 2:
            printf("Enter value to Update: ");
            scanf("%s", &input);
            if (!valid(input)){
                printf("Invalid input! \n");
                clear_input();
                continue;
            }
            value = atoi(input);
            printf("Enter the updated value: ");
            scanf("%s", &input);
            if (!valid(input)){
                printf("Invalid input! \n");
                clear_input();
                continue;
            }
            updated = atoi(input);
            updateNode(root,value,updated);
            break;
        case 3:
            manualPreOrder(root);
            break;
        case 4:
            manualPostOrder(root);
            break;
        case 5:
            manualInOrder(root);
            break;
        case 6:
            printf("Enter value to Delete: ");
            scanf("%s", &input);
            if (!valid(input)){
                printf("Invalid input! \n");
                clear_input();
                continue;
            }
            value = atoi(input);
            deleteNode(root,value);
            break;
        case 7:
            printf("Exiting program. :) \n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}