#include "queue.h"

QueueNode * createQueueNode(BTreeNode *tree_node){
    QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    if(node){
        node->tree_node = tree_node;
        node->next = NULL;
    }
    return node;
}

Queue * createQueue(){
    Queue *q = (Queue*)malloc(sizeof(Queue));
    if (q){
        q->front = q->rear = NULL;
    }
    return q;
}

bool emptyQueue(Queue *q){
    return q->front == NULL;
}

void enqueue(Queue *q, BTreeNode *tree_node){
    QueueNode *new_node = createQueueNode(tree_node);
    if(!emptyQueue(q)) q->rear->next = new_node;
    else q->front = new_node;
    q->rear = new_node;

}

BTreeNode * dequeue(Queue *q){
    QueueNode *aux_node = q->front;
    if (!emptyQueue(q)){
        BTreeNode *tree_node = aux_node->tree_node;
        q->front = aux_node->next;
        if (q->front == NULL){
            q->rear = NULL;
        }
        aux_node->next = NULL;
        return tree_node;
    }
    free(aux_node);
    return NULL;
}


