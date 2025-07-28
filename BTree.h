#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define M 204

typedef struct b_tree_node{

    int num_keys;
    int keys[M-1];
    long offsets[M-1];
    struct b_tree_node *children[M];
    bool is_leaf;

}BTreeNode;

typedef struct b_tree{
    BTreeNode *root;
}BTree;


BTree *createBTree();
void Insert(BTree *b_tree, int key, long offset);
void inOrder(BTreeNode *root);
void printInLevels(BTreeNode *raiz);
BTreeNode *createBTreeNode(bool is_leaf);
void insertNonFull(BTreeNode *node, int key, long offset);
void splitChild(BTreeNode *parent, int index);
int lowerBound(int keus[],int n, int key);
BTreeNode * searchBTree(BTreeNode *node,int key);
void printRange(BTreeNode *root, int start, int end);
void printAgeGreaterThan(BTreeNode *root, int min_age);


#endif 