#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <stdbool.h>

#define BPLUS_M 340 

typedef struct b_plus_tree {

    int num_keys;
    int keys[BPLUS_M-1];
    bool is_leaf;

    union {
        struct b_plus_tree *children[BPLUS_M];
        struct {
            long offsets[BPLUS_M-1];               
            struct b_plus_tree *next;
        } leaf;             
    } ptrs;

} BPlusTreeNode;

typedef struct {
    BPlusTreeNode *root;
} BPlusTree;

BPlusTree *createBPlusTree();
BPlusTreeNode *createBPlusTreeNode(bool is_leaf);
void BPlusInsert(BPlusTree *tree, int key, long offset);
BPlusTreeNode *BPlusSearch(BPlusTreeNode *root, int key);
void BPlusPrintInLevels(BPlusTreeNode *root);
void BPlusPrintRange(BPlusTreeNode *root, int start, int end);
void BPlusPrintAgeGreaterThan(BPlusTreeNode *root, int min_age);
void insertNonFullBP(BPlusTreeNode *node, int key, long offset);
void splitChildBP(BPlusTreeNode *parent, int index);

#endif 
