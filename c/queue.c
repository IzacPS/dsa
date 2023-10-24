#include <stdio.h>
#include <stdlib.h>

#define QUEUE_CAPACITY 10

typedef struct{
    int data[QUEUE_CAPACITY];
    int front;
    int back;
    int size;
}Queue;


void queue_init(Queue *q){
    q->front = 0;
    q->back = 0;
    q->size = 0;
}

int queue_is_full(Queue *q){
    return q->size == QUEUE_CAPACITY;
}

int queue_is_empty(Queue *q){
    return q->size == 0;
}

void queue_enqueue(Queue *q, int value){
    if(!queue_is_full(q)){
        q->back = (q->back + 1) % QUEUE_CAPACITY;
        q->data[q->back] = value; 
        q->size++;
    }
}

void queue_dequeue(Queue *q){
    if(!queue_is_empty(q)){
        q->front = (q->front + 1) % QUEUE_CAPACITY;
        q->size--;
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
    Queue q;
    queue_init(&q);
    if(queue_is_empty(&q))
        printf("is empty!\n");

    queue_enqueue(&q, 1);
    queue_enqueue(&q, 4);
    queue_enqueue(&q, 6);
    queue_enqueue(&q, 11);
    queue_enqueue(&q, 98);
    queue_enqueue(&q, 3);
    queue_enqueue(&q, 7);
    queue_enqueue(&q, 8);
    queue_enqueue(&q, 23);
    queue_enqueue(&q, 54);

    if(!queue_is_empty(&q))
        printf("not empty!\n");

    if(queue_is_full(&q))
        printf("is full!\n");

    return EXIT_SUCCESS;
}
