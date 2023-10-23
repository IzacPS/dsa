#include <stdio.h>
#include <stdlib.h>

#define QUEUE_CAPACITY 10

typedef struct{
    int data[QUEUE_CAPACITY];
    int front;
    int back;
}Queue;


void queue_init(Queue *q){
    q->front = -1;
    q->back = -1;
}

int queue_is_full(Queue *q){
    return (q->front == q->back);
}

int queue_is_empty(Queue *q){
    return (q->front == q->back);
}

void queue_enqueue(Queue *q, int value){
    if(!queue_is_full(q)){
        q->back = (q->back + 1) % QUEUE_CAPACITY;
        q->data[q->back] = value; 
    }
}

void queue_dequeue(Queue *q){
    if(!queue_is_empty(q)){
        q->front = abs(q->front - 1) % QUEUE_CAPACITY;
    }
}

int queue_peek(Queue* q, int *out){
    if(!queue_is_empty(q)){
        *out = q->data[q->front];
        return 1;
    } 
    return 0;
}

int main(int argc, char *argv[])
{

    return EXIT_SUCCESS;
}
