#include <limits.h>
#include <stdio.h>

struct MinMax{
    int min;
    int max;
};

struct MinMax get_min_max(int *arr, int size){
    struct MinMax mm = {INT_MAX, INT_MIN};
    for(int i = 0; i < size; i++){
        if(arr[i] < mm.min){
            mm.min = arr[i];
        }
        if(arr[i] > mm.max){
            mm.max = arr[i];
        }
    }
    return mm;
}


int main(int argc, char *argv[])
{
    int arr[] = {3, 2, 1, 10000, 167}; 

    struct MinMax mm = get_min_max(arr, 5);
    


    printf("min: %d, max: %d", mm.min, mm.max);

    return 0;
}
