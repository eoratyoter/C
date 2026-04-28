#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode{
    element data;
    struct ListNode* link;
}ListNode;

typedef struct dListNode{
    struct dListNode* llink;
    element data;
    struct dListNode* rlink;
}dListNode;

typedef struct Headnode{
    struct ListNode* link;
}HeadNode;

typedef struct dHeadnode{
    struct dListNode* link;
}dHeadNode;

int circle = 0;

void printing_all1(HeadNode* head, ListNode* node, int circle){
    if(node == head->link && circle == 1){
        printf("NULL\n");
        circle = 0;
        return;
    }
    if(circle == 0){
        circle = 1;
    }
    printf("%d -> ", node->data);
    printing_all1(head, node->link, circle);
}
/*void print_list(ListNode *head){
    for (ListNode *p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
}*/       
void printing_all(HeadNode* head){
    if(head->link == NULL){
        printf("NULL\n");
        return;
    }
    printing_all1(head, head->link, circle);
    return;
}


HeadNode* insert_first(HeadNode* head){
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    printf("data?(num only)");
    scanf("%d", &node->data);
    if(head->link == NULL){
        head->link = node;
        node->link = head->link;
    }else{
        node->link = head->link;
        head->link = node;
    }
    return head;
}

HeadNode* insert(HeadNode* head, ListNode* pre){
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    printf("data?(num only)");
    scanf("%d", &node->data);
    if(head->link == NULL){
        head->link = node;
        node->link = head->link;
    }else if(pre==head->link){
        node->link = pre->link;
        pre->link = node;
        head->link = node;
    }else{
        node->link = pre->link;
        pre->link = node;
    }
    return head;
}

HeadNode* insert_last(HeadNode* head){
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    printf("data?(num only)");
    scanf("%d", &node->data);
    if(head->link == NULL){
        head->link = node;
        node->link = head->link;
    }else{
        node->link = head->link->link;
        head->link->link = node;
        head->link = node;
    }
    return head;
}

HeadNode* delete_first(HeadNode* head){
    
    if(head->link == NULL) return NULL;
    if(head->link->link == head->link){
        free(head->link);
        head = NULL;
    }else{
        ListNode* removed = head->link;
        head->link = removed->link;
        free(removed);
    }
    return head;
}


HeadNode* delete(HeadNode* head, ListNode* pre){
    if(head->link == NULL) return NULL;
    if (pre == pre->link){
        free(pre);
        head->link = NULL;
    }else{
        if(pre->link == head->link) head->link = pre;
        ListNode* removed;
        removed = pre->link;
        pre->link = removed->link;
        free(removed);
    }
    return head;
}

HeadNode* delete_last(HeadNode* head){
    ListNode* pre, *removed;
    if(head->link == NULL) return NULL;
    if (head->link->link == head->link){
        removed = head->link;
        head->link = NULL;
    }else{
        pre = head->link->link;
        while(pre->link != head->link) pre = pre->link;
        
        removed = head->link;
        pre->link = removed->link;
        head->link = pre;
    }
    free(removed);
    return head;
}
//---------------dlist---------------
void printing_all1(dHeadNode* head, ListNode* node){
    if(node == head->link && circle == 1){
        printf("NULL\n");
        circle = 0;
        return;
    }
    if(circle == 0){
        circle = 1;
    }
    printf("%d -> ", node->data);
    printing_all1(head, node->link, circle);
}
/*void print_list(ListNode *head){
    for (ListNode *p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
}*/       
void printing_all(HeadNode* head){
    if(head->link == NULL){
        printf("NULL\n");
        return;
    }
    printing_all1(head, head->link, circle);
    return;
}


HeadNode* insert_first(HeadNode* head){
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    printf("data?(num only)");
    scanf("%d", &node->data);
    if(head->link == NULL){
        head->link = node;
        node->link = head->link;
    }else{
        node->link = head->link;
        head->link = node;
    }
    return head;
}

HeadNode* insert(HeadNode* head, ListNode* pre){
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    printf("data?(num only)");
    scanf("%d", &node->data);
    if(head->link == NULL){
        head->link = node;
        node->link = head->link;
    }else if(pre==head->link){
        node->link = pre->link;
        pre->link = node;
        head->link = node;
    }else{
        node->link = pre->link;
        pre->link = node;
    }
    return head;
}

HeadNode* insert_last(HeadNode* head){
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    printf("data?(num only)");
    scanf("%d", &node->data);
    if(head->link == NULL){
        head->link = node;
        node->link = head->link;
    }else{
        node->link = head->link->link;
        head->link->link = node;
        head->link = node;
    }
    return head;
}

HeadNode* delete_first(HeadNode* head){
    
    if(head->link == NULL) return NULL;
    if(head->link->link == head->link){
        free(head->link);
        head = NULL;
    }else{
        ListNode* removed = head->link;
        head->link = removed->link;
        free(removed);
    }
    return head;
}


HeadNode* delete(HeadNode* head, ListNode* pre){
    if(head->link == NULL) return NULL;
    if (pre == pre->link){
        free(pre);
        head->link = NULL;
    }else{
        if(pre->link == head->link) head->link = pre;
        ListNode* removed;
        removed = pre->link;
        pre->link = removed->link;
        free(removed);
    }
    return head;
}

HeadNode* delete_last(HeadNode* head){
    ListNode* pre, *removed;
    if(head->link == NULL) return NULL;
    if (head->link->link == head->link){
        removed = head->link;
        head->link = NULL;
    }else{
        pre = head->link->link;
        while(pre->link != head->link) pre = pre->link;
        
        removed = head->link;
        pre->link = removed->link;
        head->link = pre;
    }
    free(removed);
    return head;
}

int main(){
    HeadNode* head = (HeadNode*)malloc(sizeof(HeadNode));
    head->link = NULL;
    head = insert_last(head);
    head = insert_last(head);
    head = insert_last(head);
    head = insert_last(head);
    printing_all(head);
    return 0;

    /*head = insert_last(head);
    head = insert(head, head->link);
    head = delete_first(head);
    head = delete(head, head->link);*/
}