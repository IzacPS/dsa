#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
}DynamicArray;


void reverse(DynamicArray *arr){
    for(int i = arr->size - 1, j = 0; j < arr->size / 2; i--, j++){
        int aux = arr->data[i]; 
        arr->data[i] = arr->data[j];
        arr->data[j] = aux;
    }
}

void traverse(DynamicArray *arr){
    printf("[");
    for(int i = 0; i < arr->size; i++){
        printf("%d,", arr->data[i]);
    }
    printf("]\n");
}

void insert(DynamicArray *arr, int value){
    if(arr->size == arr->capacity){
        arr->data = realloc(arr->data, sizeof(int) * arr->size * 2);
    }
    arr->data[arr->size++] = value;
}

void delete(DynamicArray *arr, int value){
    for(int i = 0; i < arr->size; i++){
        if(arr->data[i] == value){
            for(int j = i; j < arr->size - 1; j++)
                arr->data[j] = arr->data[j + 1];
            arr->size--;
        }
    }
}

int search(DynamicArray *arr, int value){
    for(int i = 0; i < arr->size; i++){
        if(arr->data[i] == value)
            return i;
    }
    return -1;
}

int binary_search(DynamicArray *arr, int value){
    int mid = 0;
    int left = 0;
    int right = arr->size;
    do{
        //mid = left + ((right - left) / 2);
        mid  = (right + left) / 2;
        if(arr->data[mid] == value) 
        {
            return mid;
        }
        else if(arr->data[mid] > value)
        {
            right = mid;
        }
        else if(arr->data[mid] < value) 
        {
            left = mid;
        }
        
    }while(left != right);
    return -1;
}


void sort(DynamicArray *arr){
    int swapped = 0;
    for(int i = 0; i < arr->size; i++){
        for(int j = i + 1; j < arr->size; j++){
            if(arr->data[i] > arr->data[j]){
                int aux = arr->data[i];
                arr->data[i] = arr->data[j];
                arr->data[j] = aux;
                swapped = 1;
            }
        }
        if(!swapped)
            break;
    }
}

int main(int argc, char *argv[])
{
    DynamicArray arr;
    arr.data = calloc(1, sizeof(int) * 10);
    arr.size = 0;
    arr.capacity = 10;

    insert(&arr,17);
    insert(&arr,46);
    insert(&arr,1 );
    insert(&arr,77);
    insert(&arr,34);
    insert(&arr,49);
    insert(&arr,90);
    insert(&arr,92);
    insert(&arr,41);
    insert(&arr,98);
    
    traverse(&arr);
    printf("search value 77. Pos: %d\n", search(&arr, 77));
    sort(&arr);

    traverse(&arr);
    printf("search value 77. Pos: %d\n", binary_search(&arr, 77));

    delete(&arr, 77);
    traverse(&arr);

    reverse(&arr);
    traverse(&arr);

    return 0;
}
