#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode{
    element data;
    struct ListNode* link;
}ListNode;

void print_list(ListNode *head){
    for (ListNode *p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
}       

/*void printing_all(ListNode* head){
    if(head == NULL){
        printf("\n");
        return;
    }
    printf("%d -> ", head->data);
    printing_all(head->link);
}*/

ListNode* insert_first(ListNode* head){
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    printf("data?(num only)");
    scanf("%d", &node->data);
    node->link = head;
    head = node;
    printing_all(head);
    return head;
}

ListNode* insert(ListNode* head, ListNode* pre){
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    printf("data?(num only)");
    scanf("%d", &node->data);
    node->link = pre->link;
    pre->link = node;
    printing_all(head);
    return head;
}

ListNode* delete_first(ListNode* head){
    ListNode* removed;
    if(head == NULL) return NULL;
    removed = head;
    head = removed->link;
    free(removed);
    printing_all(head);
    return head;
}


ListNode* delete(ListNode* head, ListNode* pre){
    if (pre == NULL || pre->link == NULL) return head;
    ListNode* removed;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    printing_all(head);
    return head;
}

int main(){
    ListNode* head = NULL;

    head = (ListNode*)malloc(sizeof(ListNode));
    printf("data?(num only)");
    scanf("%d", &head->data);
    head->link = NULL;
    printing_all(head);

    ListNode *p;
    p = (ListNode*)malloc(sizeof(ListNode));
    printf("data?(num only)");
    scanf("%d", &p->data);
    p->link = NULL;
    head->link = p;
    printing_all(head);

    ListNode *pr;
    pr = (ListNode*)malloc(sizeof(ListNode));
    printf("data?(num only)");
    scanf("%d", &pr->data);
    pr->link = NULL;
    p->link = pr;
    printing_all(head);

    ListNode *pre;
    pre = (ListNode*)malloc(sizeof(ListNode));
    printf("data?(num only)");
    scanf("%d", &pre->data);
    pre->link = NULL;
    pr->link = pre;
    printing_all(head);

    head = insert_first(head);
    head = insert(head, pr);
    head = delete_first(head);
    head = delete(head, pr);
}