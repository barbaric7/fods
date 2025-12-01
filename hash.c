#include <stdio.h>

#define SIZE 10

int hash(int key) {
    return key % SIZE;
}

    void insert(int table[], int key) {
        int index = hash(key);
        int start = index;

        while(table[index] != -1 && table[index] != -2) {
            index = (index + 1) % SIZE;
            if(index == start) {
                printf("Hash Table is Full! Cannot insert %d\n", key);
                return;
            }
        }
        table[index] = key;
}

int search(int table[], int key) {
    int index = hash(key);
    int start = index;

    while(table[index] != -1) {
        if(table[index] == key)
            return index;

        index = (index + 1) % SIZE;
        if(index == start)
            break;
    }
    return -1;
}

void delete(int table[], int key) {
    int index = search(table, key);
    if(index == -1) {
        printf("%d Not Found, cannot delete.\n", key);
        return;
    }
    table[index] = -2;  // Mark as deleted
    printf("%d Deleted.\n", key);
}

void display(int table[]) {
    printf("\nHash Table:\n");
    for(int i = 0; i < SIZE; i++) {
        if(table[i] == -1)
            printf("%d : EMPTY\n", i);
        else if(table[i] == -2)
            printf("%d : DELETED\n", i);
        else
            printf("%d : %d\n", i, table[i]);
    }
}

int main() {
    int table[SIZE];
    int choice, key;

    // initialize table with -1 (empty)
    for(int i = 0; i < SIZE; i++)
        table[i] = -1;

    while(1) {
        printf("\n--- HASH TABLE MENU ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(table, key);
                break;

            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                int index = search(table, key);
                if(index != -1)
                    printf("%d Found at index %d\n", key, index);
                else
                    printf("%d Not Found.\n", key);
                break;

            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete(table, key);
                break;

            case 4:
                display(table);
                break;

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid Choice, try again.\n");
        }
    }
}