#include <stdio.h>

#define STACK_CAPACITY 10

typedef struct {
    int data[STACK_CAPACITY];
    int top;
}Stack;


void stack_init(Stack *s){
    s->top = -1;
}

void stack_push(Stack *s, int value){
    if(s->top < STACK_CAPACITY){
        s->data[++s->top] = value;
    }
}

void stack_pop(Stack *s){
    if(s->top != -1){
        s->top--;
    }
}

int stack_is_empty(Stack *s){
    return s->top == -1;
}

int stack_is_full(Stack *s){
    return s->top == STACK_CAPACITY - 1;
}


int stack_peek(Stack *s, int *out){
    if(s->top != -1){
        *out = s->data[s->top];
        return 1;
    } 
    return 0;
}

int main(int argc, char *argv[])
{
    Stack s;
    stack_init(&s);

    stack_push(&s, 4);
    stack_push(&s, 5);
    stack_push(&s, 10);
    stack_push(&s, 8);
    stack_push(&s, 1);
    stack_push(&s, 45);
    stack_push(&s, 2);
    stack_push(&s, 87);
    stack_push(&s, 4);
    stack_push(&s, 5);

    int val = 0;
    if(stack_peek(&s, &val)){
        printf("keep: %d\n", val);
    }

    if(stack_is_full(&s)){
        printf("is full!\n");
    }

    for(int i = 0; i < 10; i++){
        stack_pop(&s);
    } 

    if(!stack_peek(&s, &val)){
        printf("has no value!\n");
    }

    if(!stack_is_full(&s)){
        printf("is empty!\n");
    }

    return 0;
}

