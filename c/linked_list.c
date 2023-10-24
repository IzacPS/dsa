#include <stdio.h>
#include <stdlib.h>



struct ListNode{
    int data; 
    struct ListNode *next; 
};
typedef struct ListNode ListNode;

typedef struct LinkedList{
    ListNode *head;
}LinkedList;

void llist_init(LinkedList *new){
    new->head = NULL;
}

void llist_traverse(LinkedList *ll){
    ListNode *cur = ll->head;

    printf("head-> ");

    while(cur){
        printf("[%d]->", cur->data);
        cur = cur->next;
    }
    printf("[null]\n");
}

void llist_insert_at_begining(LinkedList *ll, int value){
    ListNode *new = calloc(1, sizeof(*new));
    new->data = value;
    if(ll->head)
        new->next = ll->head;
    ll->head = new;
}
void llist_insert_at_end(LinkedList *ll, int value){
    ListNode *cur = ll->head; 
    while(cur->next)
        cur = cur->next;
    ListNode *new = calloc(1, sizeof(*new));
    new->data = value;
    cur->next = new;
}
void llist_insert_at_position(LinkedList *ll, int pos, int value){
    ListNode *cur = ll->head;
    for(int i = 0; i < pos - 1 || cur == NULL; i++, cur = cur->next);
    if(cur != NULL){
        ListNode *new = calloc(1, sizeof(*new)); 
        new->data = value;
        new->next = cur->next;
        cur->next = new;
    }
}

void llist_delete_at_begining(LinkedList *ll){
    if(ll->head){
        ListNode *node = ll->head;
        ll->head = ll->head->next;
        free(node);
    }
}
void llist_delete_at_end(LinkedList *ll){
    ListNode *cur = ll->head;
    while(cur->next->next)
        cur = cur->next;
    ListNode *aux = cur->next; 
    cur->next = aux->next;
    free(aux);
}
void llist_delete_at_position(LinkedList *ll, int pos){
    ListNode *cur = ll->head;
    for(int i = 0; i < pos - 1 || cur == NULL; i++, cur = cur->next);
    if(cur != NULL){
        ListNode *aux = cur->next;
        cur->next = aux->next;
        free(aux);
    } 
}

int llist_search(LinkedList *ll, int value, ListNode *out){
    ListNode *cur = ll->head;
    while(cur->next && cur->data != value)
        cur = cur->next;
    if(cur){
        *out = *cur; 
        return 1;
    }
    return 0;
}

void llist_sort(LinkedList *ll){

}

int main(int argc, char *argv[])
{
    LinkedList ll;
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
