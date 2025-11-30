#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void clear_input() {
    int c;
    while ((c = getchar()) != '\n');
}

int valid(char input[]) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
            return 0;
        }
    }
    return 1;
}

void merge(int arr[], int start, int mid, int end) {
    int size = end - start + 1;
    int temp[size];
    int i = start, j = mid + 1, k = 0;

    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= end)
        temp[k++] = arr[j++];

    for (i = 0; i < size; i++)
        arr[start + i] = temp[i];
}

void mergeSort(int arr[], int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

void binarySearch(int arr[], int value, int size) {
    int start = 0, end = size - 1;
    int found = 0;

    while (start <= end) {
        int mid = (start + end) / 2;

        if (value == arr[mid]) {
            printf("Value found at index: %d\n", mid);
            found = 1;
            break;
        } else if (value < arr[mid])
            end = mid - 1;
        else
            start = mid + 1;
    }

    if (!found)
        printf("Value not found!\n");
}

int main() {
    int choice = 1;
    char input[10];
    int arr[100];
    int size = 0;

    while (choice) {
        printf("\n=== Search & Sort ===\n");
        printf("1. Create & Sort\n");
        printf("2. Search\n");
        printf("3. Display Array\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%s", input);

        if (!valid(input)) {
            printf("Invalid input!\n");
            clear_input();
            continue;
        }

        choice = atoi(input);

        if (choice == 1) {
            printf("Enter number of elements: ");
            scanf("%s", input);
            if (!valid(input)) {
                printf("Invalid input!\n");
                clear_input();
                continue;
            }
            size = atoi(input);

            printf("Enter %d elements: ", size);
            for (int i = 0; i < size; i++) {
                scanf("%s", input);
                if (!valid(input)) {
                    printf("Invalid input! Enter again: ");
                    clear_input();
                    i--;
                    continue;
                }
                arr[i] = atoi(input);
            }

            mergeSort(arr, 0, size - 1);
            printf("\nArray sorted successfully!\nSorted array: ");
            for (int i = 0; i < size; i++)
                printf("%d ", arr[i]);
            printf("\n");

        } else if (choice == 2) {
            if (size == 0) {
                printf("Create array first!\n");
                continue;
            }

            printf("Enter value to search: ");
            scanf("%s", input);
            if (!valid(input)) {
                printf("Invalid input!\n");
                clear_input();
                continue;
            }
            int value = atoi(input);

            binarySearch(arr, value, size);

        } else if (choice == 3) {
            if (size == 0) {
                printf("No array yet.\n");
            } else {
                printf("Current array: ");
                for (int i = 0; i < size; i++)
                    printf("%d ", arr[i]);
                printf("\n");
            }

        } else if (choice == 4) {
            printf("Exiting.. :)\n");
            break;
        } else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
