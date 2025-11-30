#include <stdlib.h>
#include <stdio.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *queue[100];
int rear = -1, front = -1;
struct Node *root = NULL;
 
void enqueue(struct Node *n){
    queue[++rear] = n;
};

struct Node* dequeue(){
    struct Node* temp = queue[++front];
    return temp;
}

int isEmpty(){
    return front == rear;
}

struct Node* createNode(int data){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
};

struct Node* insertNode(int data){

    struct Node *newNode = createNode(data);

    if(root == NULL){
        root = newNode;
        return root;
    }

    front = -1;
    rear = -1;
    enqueue(root);

    while (!isEmpty()) {
        struct Node* check = dequeue();

        if (check->left == NULL) {
            check->left = newNode;
            return root;
        } else {
            enqueue(check->left);
        }

        if (check->right == NULL) {
            check->right = newNode;
            return root;
        } else {
            enqueue(check->right);
        }
    }
    return root;
}

void search(int valueToFind) {
    if (root == NULL) {
        return;
    }

    front = -1;
    rear = -1;
    enqueue(root);

    while (!isEmpty()) {
        struct Node* current = dequeue();

        if (current->data == valueToFind) {
            printf("Value Found!..");
            return;
        }

        if (current->left != NULL) {
            enqueue(current->left);
        }
        if (current->right != NULL) {
            enqueue(current->right);
        }
    }
    printf("Value Not Found!..");

    return; 
}

void update(int valueToUpdate, int updatedValue) {
    if (root == NULL) {
        return;
    }

    front = -1;
    rear = -1;
    enqueue(root);

    while (!isEmpty()) {
        struct Node* current = dequeue();

        if (current->data == valueToUpdate) {
            printf("\nValue Found!..\nUpdating Value!..\nValue update to %d",updatedValue);
            current->data = valueToUpdate;
            return;
        }

        if (current->left != NULL) {
            enqueue(current->left);
        }
        if (current->right != NULL) {
            enqueue(current->right);
        }
    }

    printf("\nValue Not Found!..\n");
    return; 
}

void inOrder(struct Node* root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

void preOrder(struct Node* root){
    if(root == NULL) {
        return;
    }
    printf("%d ",root->data);
    preOrder(root->left);
    preOrder(root->right);
}

// Stack

struct Node* stack[20];
int top = -1;

struct Node* stack2[20];
int top2 = -1;

void push(struct Node* root){
    stack[++top] = root;
}

struct Node* pop(){
    return stack[top--];
}
void push2(struct Node* root){
    stack2[++top2] = root;
}

struct Node* pop2(){
    return stack2[top2--];
}

void manualPreOrder(struct Node *root){

    if(root == NULL){
        return;
    }

    push(root);
    while(top!=-1){
        struct Node* printNode = pop();
        printf("%d ",printNode->data);
        if(printNode->right!=NULL){
            push(printNode->right);
        }
        if(printNode->left!=NULL){
            push(printNode->left);
        }
    }

};

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

void deleteNode(int value){

    if(root == NULL){
        printf("Tree is empty!..\n");
        return;
    }

    enqueue(root);
    struct Node *current = NULL, *target = NULL, *last = NULL, *secondLast = NULL;

    while (!isEmpty()){
        current = dequeue();
        if(current->data == value){
            target = current;
        }
        
        if(current->left!=NULL){
            enqueue(current->left);
            secondLast = current;
        }
        
        if(current->right!=NULL){
            enqueue(current->right);
            secondLast = current;
        }
    }
    
    last = current;
    if(target == NULL){
        printf("Value Not Found!..");
    }else{
        printf("Value Found!..\nDeleting Node!..\n");
        target->data = last->data;
        if(secondLast->right == last){
            secondLast->right = NULL;
        }
        if(secondLast->left == last){
            secondLast->left = NULL;
        }

        printf("Node with value %d Deleted Sucessfully!..\n",value);
        free(last);

    }
    


}
int main(){

    struct Node* new = insertNode(10);
    new = insertNode(20);
    new = insertNode(30);
    new = insertNode(40);
    new = insertNode(50);
    new = insertNode(60);
    new = insertNode(70);
    new = insertNode(80);
    // inOrder(root);
    // search(542);
    // update(20,35);
    preOrder(root);
    deleteNode(40);
    manualPreOrder(root);
    // manualInOrder(root);
    // manualPostOrder(root);
    

    return 0;
}