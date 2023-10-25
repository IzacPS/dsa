#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *prev;
    struct Node *next;
};

typedef struct Node Node;

typedef struct {
    Node *head;
}DoublyLinkedList;


void llist_init(DoublyLinkedList *new){
    new->head = NULL;
}

void llist_traverse(DoublyLinkedList *ll){
    Node *cur = ll->head;

    printf("head-> ");

    while(cur){
        printf("[%d]<->", cur->data);
        cur = cur->next;
    }
    printf("[null]\n");
}

void llist_insert_at_begining(DoublyLinkedList *ll, int value){
    Node *new = calloc(1, sizeof(*new));
    new->data = value;
    if(ll->head){
        new->next = ll->head;
        ll->head->prev = new;
    }
    ll->head = new;
}
void llist_insert_at_end(DoublyLinkedList *ll, int value){
    Node *cur = ll->head;
    while(cur->next)
        cur = cur->next;
    Node *new = calloc(1, sizeof(*new));
    new->data = value;
    cur->next = new;
    new->prev = cur;
}
void llist_insert_at_position(DoublyLinkedList *ll, int pos, int value){
    Node *cur = ll->head;
    for(int i = 0; i < pos || cur == NULL; i++, cur=cur->next);
    if(cur){
        Node *new = calloc(1, sizeof(*new));  
        new->data = value;
        cur->prev->next = new; 
        new->prev = cur->prev;
        new->next = cur;
        cur->prev = new;
    }
}

void llist_delete_at_begining(DoublyLinkedList *ll){
    Node *h = ll->head;
    ll->head = h->next;
    ll->head->prev = NULL;
    free(h);
}

void llist_delete_at_end(DoublyLinkedList *ll){
    Node *cur = ll->head;
    while(cur->next)
        cur = cur->next;
    Node *prev = cur->prev;
    prev->next = NULL;
    free(cur);
}

void llist_delete_at_position(DoublyLinkedList *ll, int pos){
    Node *cur = ll->head;
    for(int i = 0; i < pos || cur == NULL; i++, cur=cur->next);
    if(cur){
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        free(cur);
    }
}

int llist_search(DoublyLinkedList *ll, int value, Node *out){
    Node *cur = ll->head;
    while(cur->next || cur->data == value);
    if(cur){
        *out = *cur;
        return 1;
    }
    return 0;
}


int main(int argc, char *argv[])
{
    DoublyLinkedList ll;
    llist_init(&ll);

    printf("insert at beginning 4 and 10\n");
    llist_insert_at_begining(&ll, 10);
    llist_insert_at_begining(&ll, 4);
    llist_traverse(&ll);

    printf("insert at end 7, 9, 45, 64, 23\n");
    llist_insert_at_end(&ll, 7);
    llist_insert_at_end(&ll, 9);
    llist_insert_at_end(&ll, 45);
    llist_insert_at_end(&ll, 64);
    llist_insert_at_end(&ll, 23);
    llist_traverse(&ll);

    printf("insert at position 1, 3 and 1\n");
    llist_insert_at_position(&ll, 1, 3);
    llist_insert_at_position(&ll,1, 1);
    llist_traverse(&ll);

    printf("delete at beginning two times\n");
    llist_delete_at_begining(&ll);
    llist_delete_at_begining(&ll);
    llist_traverse(&ll);

    printf("delete at end two times\n");
    llist_delete_at_end(&ll);
    llist_delete_at_end(&ll);
    llist_traverse(&ll);

    printf("delete at position 1 two times\n");
    llist_delete_at_position(&ll, 1);
    llist_delete_at_position(&ll, 1);
    llist_traverse(&ll);

    return 0;
}
