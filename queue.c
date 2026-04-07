#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5\

typedef int element;

typedef struct {
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} QueueType;

void create(x){

}

void init(QueueType *q){

}

int is_empty(QueueType *q){
    if(q->rear == q->front)
        return 1;
    else return 0;
}

void is_full(QueueType *q){
    if(q->rear == q->front-1)
        return 1;
    else return 0;
}

enqueue(q, e){
    if(1)
    ;
}

dequeue(QueueType *q){
    if(is_empty(q))
    ;
}

peek(q){

}