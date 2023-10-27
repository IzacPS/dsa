#include <stdio.h>
#include <string.h>

enum BinaryHeapType{
    MIN_HEAP,
    MAX_HEAP
};

#define BINARY_HEAP_CAPACITY 10


//node: i
//left child:  2i + 1
//right child: 2i + 2
//parent: (i - 1) / 2

typedef struct{
    int data[BINARY_HEAP_CAPACITY];
    int size;
    int type;
}BinaryHeap;

void binary_heap_init(BinaryHeap *h, enum BinaryHeapType type){
    memset(h, 0,sizeof(*h)); 
    h->type = type;
}

void binary_heap_print(BinaryHeap *h){
    for(int i = 1, k = 0; k < h->size; i*=2){
        for(int j = 0; j < i && k < h->size; j++, k++){
            printf("%d\t", h->data[k]);
        } 
        printf("\n");
    }
}


void binary_heap_siftup(BinaryHeap *h, int node_pos){
    int parent = (node_pos == 0) ? -1 : (node_pos - 1) / 2;
    if(h->type == MIN_HEAP){
        while(parent >= 0 && h->data[parent] > h->data[node_pos]){
            int aux = h->data[parent];
            h->data[parent] = h->data[node_pos];
            h->data[node_pos] = aux;

            node_pos = parent;
            parent = (node_pos - 1) / 2;
        } 
    }else{
        while(parent >= 0 && h->data[parent] < h->data[node_pos]){
            int aux = h->data[parent];
            h->data[parent] = h->data[node_pos];
            h->data[node_pos] = aux;

            node_pos = parent;
            parent = (node_pos - 1) / 2;
        } 
    }
}

int lchild(int index){
    return 2 * index + 1;
}

int rchild(int index){
    return 2 * index + 2;
}


void binary_heap_siftdown(BinaryHeap *h, int node_pos){
    if(h->type == MIN_HEAP){
        int next = (h->data[lchild(node_pos)] < h->data[node_pos]) ? lchild(node_pos) : rchild(node_pos);
        while(next < BINARY_HEAP_CAPACITY && h->data[next] < h->data[node_pos]){
            int aux = h->data[next];
            h->data[next] = h->data[node_pos];
            h->data[node_pos] = aux;

            node_pos = next;
            next = (h->data[lchild(node_pos)] < h->data[node_pos]) ? lchild(node_pos) : rchild(node_pos);
        }
    }else{
        int next = (h->data[lchild(node_pos)] > h->data[node_pos]) ? lchild(node_pos) : rchild(node_pos);
        while(next < BINARY_HEAP_CAPACITY && h->data[next] > h->data[node_pos]){
            int aux = h->data[next];
            h->data[next] = h->data[node_pos];
            h->data[node_pos] = aux;

            node_pos = next;
            next = (h->data[lchild(node_pos)] > h->data[node_pos]) ? lchild(node_pos) : rchild(node_pos);
        }

    }
}

void binary_heap_heapfy(BinaryHeap *h){
    int i = h->data[h->size - 1];
    i = (i - 1) / 2;
    while(i > 0){
        binary_heap_siftdown(h, i--);
    }
}

void binary_heap_insert(BinaryHeap *h, int value){
    h->data[h->size] = value; 
    binary_heap_siftup(h, h->size++);
}

void binary_heap_remove(BinaryHeap *h, int index){}

int binary_heap_get(BinaryHeap *h){
    return h->data[0];
}

int binary_heap_extract(BinaryHeap *h){
    int value = h->data[0];
    h->data[0] = h->data[--h->size];
    binary_heap_siftdown(h, 0);
    return value;
}

void binary_heap_update(BinaryHeap *h, int pos, int value){
    int old = h->data[pos];
    h->data[pos] = value;
    if(h->type == MIN_HEAP){
        if(old < value)
            binary_heap_siftdown(h, pos);
        else
            binary_heap_siftup(h, pos);
    }else{
        if(old < value)
            binary_heap_siftup(h, pos);
        else
            binary_heap_siftdown(h, pos);
    }
}


int main(int argc, char *argv[])
{
    BinaryHeap h; 
    binary_heap_init(&h,MIN_HEAP);

    binary_heap_insert(&h, 3);
    binary_heap_insert(&h, 9);
    binary_heap_insert(&h, 2);
    binary_heap_insert(&h, 1);
    binary_heap_insert(&h, 4);
    binary_heap_insert(&h, 5);

    binary_heap_print(&h);
    printf("\n");

    printf("min: %d\n", binary_heap_get(&h));
    printf("\n");

    binary_heap_insert(&h, -1);

    binary_heap_print(&h);
    printf("\n");

    binary_heap_update(&h, 4, -2);

    binary_heap_print(&h);
    printf("\n");


    BinaryHeap hm;
    binary_heap_init(&hm,MIN_HEAP);

    binary_heap_insert(&hm, 3);
    binary_heap_insert(&hm, 9);
    binary_heap_insert(&hm, 2);
    binary_heap_insert(&hm, 1);
    binary_heap_insert(&hm, 4);
    binary_heap_insert(&hm, 5);

    binary_heap_print(&hm);
    printf("\n");

    printf("min: %d\n", binary_heap_get(&hm));
    printf("\n");

    binary_heap_insert(&hm, -1);

    binary_heap_print(&hm);
    printf("\n");

    binary_heap_update(&hm, 4, -2);

    binary_heap_print(&hm);
    printf("\n");

    BinaryHeap hh;
    binary_heap_init(&hh,MAX_HEAP);
    binary_heap_insert(&hh, 4);
    binary_heap_insert(&hh, 1);
    binary_heap_insert(&hh, 3);
    binary_heap_insert(&hh, 2);
    binary_heap_insert(&hh, 16);
    binary_heap_insert(&hh, 9);
    binary_heap_insert(&hh, 10);
    binary_heap_insert(&hh, 14);
    binary_heap_insert(&hh, 8);
    binary_heap_insert(&hh, 7);

    binary_heap_print(&hh);
    printf("\n");

    return 0;
}
