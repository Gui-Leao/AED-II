#include "queue.h"

Queue createQueueNode(BTreeNode *tree_node){
    QueueNode *node = (*QeueuNode)malloc(sizeof(QueueNode));
    if(node){
        node->tree_node->tree_node;
        node->next = NULL;
    }
    return node;
}

Queue createQueue(){
    Queue *q = (*Queue)malloc(sizeof(Queue));
    if (q){
        q->front = q->rear = NULL;
    }
    return q;
}

bool emptyQueue(Queue *q){
    return q->front == NULL;
}

void enqueue(Queue *q, BTreeNode *tree_node){
    QueueNode new_node = createQueueNode(q,tree_node);
    if(!emptyQueue(q)) q->rear->next = new_node;
    else q->front = new_node;
    q->rear = new_node;

}

BTreeNode dequeue(Queue *q){
    Node aux_node = q->front;
    if (!emptyQueue(q)){
        q->front = aux_node->next;
        if (q->front == NULL){
            q->rear = NULL;
        }
        aux_node->next = NULL;
        return aux_node;
    }
    return aux_node;
}


