#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int rthread;
};

struct Node *root = NULL;

void clear_input()
{
    int c;
    while ((c = getchar()) != '\n');
}

int valid(char input[])
{
    for (int i = 0; i < strlen(input); i++)
    {
        if (!isdigit(input[i]))
            return 0;
    }
    return 1;
}

struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->rthread = 1;
    return newNode;
}

void insertNode(int data)
{
    struct Node *newNode = createNode(data);

    if (root == NULL)
    {
        root = newNode;
        return;
    }

    struct Node *current = root;
    struct Node *parent = NULL;

    while (1)
    {
        parent = current;
        if (data < current->data)
        {
            if (current->left != NULL)
                current = current->left;
            else
                break;
        }
        else if (data > current->data)
        {
            if (current->rthread == 0)
                current = current->right;
            else
                break;
        }
        else
        {
            printf("Duplicate Key!..");
            free(newNode);
            return;
        }
    }

    if (data < parent->data)
    {
        parent->left = newNode;
        newNode->right = parent;
        newNode->rthread = 1;
    }
    else
    {
        newNode->right = parent->right;
        newNode->rthread = 1;
        parent->right = newNode;
        parent->rthread = 0;
    }
}

struct Node *leftMost(struct Node *n)
{
    if (n == NULL)
        return NULL;
    while (n->left != NULL)
        n = n->left;
    return n;
}

void threadedInOrder(struct Node *root)
{
    if (root == NULL)
    {
        printf("Tree is Empty!..");
        return;
    }

    struct Node *current = leftMost(root);

    while (current != NULL)
    {
        printf("%d ", current->data);

        if (current->rthread == 1)
            current = current->right;
        else
            current = leftMost(current->right);
    }
}

// ------------------ DELETE FUNCTION -------------------

struct Node *findParent(int key)
{
    struct Node *current = root, *parent = NULL;

    while (current != NULL)
    {
        if (key < current->data)
        {
            if (current->left == NULL) break;
            parent = current;
            current = current->left;
        }
        else if (key > current->data)
        {
            if (current->rthread == 1) break;
            parent = current;
            current = current->right;
        }
        else
        {
            break;
        }
    }
    return parent;
}

void deleteNode(int key)
{
    struct Node *parent = NULL, *current = root;

    // Search node
    while (current != NULL)
    {
        if (key < current->data)
        {
            parent = current;
            current = current->left;
        }
        else if (key > current->data)
        {
            if (current->rthread == 1)
                current = NULL;
            else
            {
                parent = current;
                current = current->right;
            }
        }
        else
            break;
    }

    if (current == NULL)
    {
        printf("Value not found!\n");
        return;
    }

    // Case 1: Node has no left child
    if (current->left == NULL && current->rthread == 1)
    {
        if (parent == NULL)
            root = NULL;
        else if (parent->left == current)
            parent->left = NULL;
        else
        {
            parent->right = current->right;
            parent->rthread = 1;
        }
        free(current);
    }
    // Case 2: Node has only left child
    else if (current->left != NULL && current->rthread == 1)
    {
        struct Node *pred = current->left;
        while (pred->right != current)
            pred = pred->right;

        pred->right = current->right;

        if (parent == NULL)
            root = current->left;
        else if (parent->left == current)
            parent->left = current->left;
        else
            parent->right = current->left;

        free(current);
    }
    // Case 3: Node has a real right subtree — find inorder successor
    else
    {
        struct Node *succ_parent = current;
        struct Node *succ = current->right;

        while (succ->left != NULL)
        {
            succ_parent = succ;
            succ = succ->left;
        }

        current->data = succ->data;
        deleteNode(succ->data);
    }
}

// ------------------ UPDATE FUNCTION -------------------

void updateNode(int oldValue, int newValue)
{
    deleteNode(oldValue);
    insertNode(newValue);
}

int main()
{
    int choice, value, newValue;
    char input[10];

    while (1)
    {
        printf("\n--- Threaded Tree Menu ---\n");
        printf("1. Insert Node\n");
        printf("2. Display InOrder (Threaded)\n");
        printf("3. Delete Node\n");
        printf("4. Update Node\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%s", input);

        if (!valid(input))
        {
            printf("Invalid input!\n");
            clear_input();
            continue;
        }

        choice = atoi(input);

        switch (choice)
        {
        case 1:
            printf("Enter value to Insert: ");
            scanf("%s", input);
            if (!valid(input)) { printf("Invalid input!\n"); continue; }
            value = atoi(input);
            insertNode(value);
            break;

        case 2:
            threadedInOrder(root);
            break;

        case 3:
            printf("Enter value to Delete: ");
            scanf("%s", input);
            if (!valid(input)) { printf("Invalid input!\n"); continue; }
            value = atoi(input);
            deleteNode(value);
            break;

        case 4:
            printf("Enter old value: ");
            scanf("%s", input);
            if (!valid(input)) { printf("Invalid input!\n"); continue; }
            value = atoi(input);

            printf("Enter new value: ");
            scanf("%s", input);
            if (!valid(input)) { printf("Invalid input!\n"); continue; }
            newValue = atoi(input);

            updateNode(value, newValue);
            break;

        case 5:
            printf("Exiting Program.\n");
            exit(0);

        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
