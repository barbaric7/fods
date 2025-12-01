#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int arr[],int size){

    for(int i=0; i<size-1; i++){

        int swapped = 0;

        for(int j=0; j<size-i-1; j++){
            if(arr[j] > arr[j+1]){

                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;

                swapped = 1;
            }
        }

        if(!swapped){
            break;
        }
    }
}

void binarySearch(int arr[],int size,int value){

    int start = 0;
    int end = size-1;
    int found = 0;

    while(start<=end){

        int mid = (start + end)/2;

        if(value == arr[mid]){
            printf("Value Found at Index %d",mid);
            found = 1;
            break;
        }else if(value > mid){
            start = mid+1;
        }else if(value < mid){
            end = mid - 1;
        }
    };

    if(!found){
        printf("Value Not Found!.. :(");
    };



};


void selectionSort(int arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        int minIndex = i;

        // find the smallest element in remaining array
        for(int j = i + 1; j < size; j++) {
            if(arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // swap only if new minimum found
        if(minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

void mergeSort( int arr[], int start, int end){

    while(start < end){
        int mid = ( start + end )/2;

        mergeSort(arr,start,mid);
        mergeSort(arr,mid+1,end);
        merge(arr,start,mid,end);
    }

}

void merge(int arr[],int start, int mid,int end){

    int size = end-start+1;
    int newArr[size];
    int i = start; 
    int j= mid+1;
    int k=0;

    while(i<=mid && j<=end){
        if(arr[i]<arr[j]){
            newArr[k++] = arr[i++];
        }else{
            newArr[k++] = arr[j++];
        }
    }

    while(i<=mid){
        newArr[k++] = arr[i++];
    }
    while (j<=end){
        newArr[k++] = arr[j++];
    }

    for(int i=0; i<size; i++){
        arr[i] = newArr[i];
    }
    
}

int main(){

    int size = 0,input = 0;
    printf("Enter the size of Array : ");
    scanf("%d",&size);

    int arr[size];

    for(int i=0; i<size; i++){
        printf("\nEnter %d No. : \n",i+1);
        scanf("%d",&input);
        arr[i] = input;
    }

    bubbleSort(arr,size);

    printf("The array is : ");
    for(int i=0; i<size; i++){
        printf("%d ",arr[i]);
    }

    binarySearch(arr,size,10);

    return 0;
}