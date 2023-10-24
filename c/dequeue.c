#include <stdio.h>

#define DEQUEUE_CAPACITY 10

enum DequeueType{
    INPUT_RESTRICTED,
    OUTPUT_RESTRICTED 
};


typedef struct{
    int data[DEQUEUE_CAPACITY];
    int front;
    int back;
    int size;
    int dequeue_type;
}Dequeue;

void dequeue_init(Dequeue *dq, enum DequeueType type){
    dq->dequeue_type = type; 
    dq->front = 0;
    dq->back = 0;
    dq->size = 0;
}

int dequeue_is_empty(Dequeue *dq){
    return dq->size == 0;
}

int dequeue_is_full(Dequeue *dq){
    return dq->size == DEQUEUE_CAPACITY;
}

void dequeue_add_front(Dequeue *dq, int value){
    if(dq->dequeue_type == OUTPUT_RESTRICTED && !dequeue_is_full(dq)){
        dq->front--;
        if(dq->front < 0)
            dq->front = DEQUEUE_CAPACITY - 1;
        dq->data[dq->front] = value;
        dq->size++;
    } 
}

void dequeue_add_back(Dequeue *dq, int value){
    if(!dequeue_is_full(dq)){
        dq->back = (dq->back + 1) % DEQUEUE_CAPACITY;
        dq->data[dq->back] = value;
        dq->size++;
    }
}

int dequeue_remove_back(Dequeue *dq, int *value){
    if(dq->dequeue_type == INPUT_RESTRICTED && !dequeue_is_empty(dq)){
        *value = dq->data[dq->back];
        dq->back--;
        if(dq->back < 0)
            dq->back = DEQUEUE_CAPACITY - 1;
        dq->size--;
        return 1;
    }
    return 0;
}

int dequeue_remove_front(Dequeue *dq, int *value){
    if(!dequeue_is_empty(dq)){
        *value = dq->data[dq->front];
        dq->front = (dq->front + 1) % DEQUEUE_CAPACITY;
        dq->size--;
        return 1; 
    }
    return 0;
}


int main(int argc, char *argv[])
{
    Dequeue dq1;
    dequeue_init(&dq1, INPUT_RESTRICTED);

    printf("queue 1 input restricted\n");
    if(dequeue_is_empty(&dq1))
        printf("is empty!\n");

    dequeue_add_front(&dq1, 1);

    if(dequeue_is_empty(&dq1))
        printf("is empty!\n");

    dequeue_add_back(&dq1, 2);
    dequeue_add_back(&dq1, 3);
    dequeue_add_back(&dq1, 4);
    dequeue_add_back(&dq1, 5);
    dequeue_add_back(&dq1, 6);
    dequeue_add_back(&dq1, 7);
    dequeue_add_back(&dq1, 12);
    dequeue_add_back(&dq1, 44);
    dequeue_add_back(&dq1, 64);
    dequeue_add_back(&dq1, 97);
    
    if(!dequeue_is_empty(&dq1))
        printf("is not empty!\n");

    if(dequeue_is_full(&dq1))
        printf("is full!\n");

    Dequeue dq2;
    dequeue_init(&dq2, OUTPUT_RESTRICTED);

    printf("queue 2 output restricted\n");
    if(dequeue_is_empty(&dq2))
        printf("is empty!\n");

    dequeue_add_back(&dq2, 2);
    dequeue_add_back(&dq2, 3);
    dequeue_add_back(&dq2, 4);
    dequeue_add_back(&dq2, 5);
    dequeue_add_back(&dq2, 6);
    dequeue_add_back(&dq2, 7);
    dequeue_add_back(&dq2, 12);
    dequeue_add_back(&dq2, 44);
    dequeue_add_back(&dq2, 64);
    dequeue_add_back(&dq2, 97);

    if(!dequeue_is_empty(&dq2))
        printf("is not empty!\n");

    int value = 0;
    if(!dequeue_remove_back(&dq2, &value))
        printf("doesnt remove\n");
    

    if(dequeue_is_full(&dq2))
        printf("is full!\n");

    return 0;
}


