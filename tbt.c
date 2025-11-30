#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int rthread;
};

struct Node *root = NULL;

/* -------- Utility Functions -------- */

void clear_input() {
    int c;
    while ((c = getchar()) != '\n');
}

int valid(char input[]) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) return 0;
    }
    return 1;
}

struct Node *createNode(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->rthread = 1;
    return newNode;
}

/* -------- Insert Function -------- */

void insertNode(int data) {
    struct Node *newNode = createNode(data);

    if (root == NULL) {
        root = newNode;
        return;
    }

    struct Node *current = root, *parent;

    while (1) {
        parent = current;

        if (data < current->data) {
            if (current->left != NULL)
                current = current->left;
            else break;
        } 
        else if (data > current->data) {
            if (current->rthread == 0)
                current = current->right;
            else break;
        } 
        else {
            printf("Duplicate key!..\n");
            free(newNode);
            return;
        }
    }

    if (data < parent->data) {
        parent->left = newNode;
        newNode->right = parent;
        newNode->rthread = 1;
    } 
    else {
        newNode->right = parent->right;
        newNode->rthread = 1;
        parent->right = newNode;
        parent->rthread = 0;
    }
}

/* -------- Leftmost Helper -------- */

struct Node *leftMost(struct Node *n) {
    while (n && n->left)
        n = n->left;
    return n;
}

/* -------- Inorder Traversal (Threaded) -------- */

void threadedInOrder(struct Node *root) {
    if (!root) {
        printf("Tree is empty!\n");
        return;
    }

    struct Node *current = leftMost(root);

    while (current) {
        printf("%d ", current->data);

        if (current->rthread == 1)
            current = current->right;
        else
            current = leftMost(current->right);
    }
}

/* -------- Search Function -------- */

struct Node* search(int key) {
    struct Node *current = root;

    while (current) {
        if (key == current->data)
            return current;

        if (key < current->data)
            current = current->left;
        else {
            if (current->rthread == 0)
                current = current->right;
            else break;
        }
    }
    return NULL;
}

/* -------- Update (Search + Replace) -------- */

void updateNode(int oldVal, int newVal) {
    struct Node *node = search(oldVal);

    if (!node) {
        printf("Value %d not found! Cannot update.\n", oldVal);
        return;
    }

    delete(node->data); // optional: if delete was implemented

    node->data = newVal;
    printf("Node updated: %d → %d\n", oldVal, newVal);
}

/* -------- MENU -------- */

int main() {
    int choice, value, oldVal, newVal;
    char input[10];

    while (1) {
        printf("\n--- Threaded Binary Tree Menu ---\n");
        printf("1. Insert Node\n");
        printf("2. Search Node\n");
        printf("3. Update Node\n");
        printf("4. InOrder (Threaded Traversal)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%s", input);

        if (!valid(input)) {
            printf("Invalid input!\n");
            clear_input();
            continue;
        }

        choice = atoi(input);

        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%s", input);
            if (!valid(input)) {
                printf("Invalid number!\n");
                break;
            }
            insertNode(atoi(input));
            break;

        case 2:
            printf("Enter value to search: ");
            scanf("%s", input);
            if (!valid(input)) break;

            struct Node *res;
            res = search(atoi(input));
            if (res)
                printf("Value found: %d\n", res->data);
            else
                printf("Value not found.\n");
            break;

        case 3:
            printf("Enter existing value: ");
            scanf("%d", &oldVal);
            printf("Enter new value: ");
            scanf("%d", &newVal);
            updateNode(oldVal, newVal);
            break;

        case 4:
            threadedInOrder(root);
            break;

        case 5:
            printf("Exiting... 😊\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
