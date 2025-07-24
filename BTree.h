#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define M 4

typedef struct b_tree_node{

    int num_keys; 
    int keys[M-1];
    struct b_tree_node *children[M]; 
    bool is_leaf; 

}BTreeNode;

typedef struct b_tree{
    BTreeNode *root;
}BTree;

// Tree operations
BTree *createBTree();
void Insert(BTreeNode **root, int key);
void inOrder(BTreeNode *root);
void imprimirPorNiveis(BTreeNode *raiz);

// Node operations (internal use)
BTreeNode *createBTreeNode(bool is_leaf);
void insertNonFull(BTreeNode *node, int key);
void splitChild(BTreeNode *parent, int index);


#endif 