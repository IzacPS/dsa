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


void binary_heap_siftup(BinaryHeap *h, int node_pos){
    int parent = (node_pos - 1) / 2;
    if(h->type == MIN_HEAP){
        while(parent > 0 && h->data[parent] > h->data[node_pos]){
            int aux = h->data[parent];
            h->data[parent] = h->data[node_pos];
            h->data[node_pos] = aux;

            node_pos = parent;
            parent = (node_pos - 1) / 2;
        } 
    }else{
        while(parent > 0 && h->data[parent] < h->data[node_pos]){
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
    binary_heap_siftup(h, h->size);
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

    return 0;
}
