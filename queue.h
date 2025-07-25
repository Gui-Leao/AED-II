#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "BTree.h"

typedef struct queue_node {
    BTreeNode *tree_node;
    struct queue_node *next;
} QueueNode;

typedef struct queue{
    QueueNode *front, *rear;
} Queue;

QueueNode * createQueueNode(BTreeNode *tree_node);
Queue * createQueue();
bool emptyQueue(Queue *q);
void enqueue(Queue *q,BTreeNode *tree_node);
BTreeNode * dequeue(Queue *q);

#endif