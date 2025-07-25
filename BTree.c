#include "BTree.h"
#include "queue.h"


BTree *createBTree(){

    BTree *b_tree = (BTree *)malloc(sizeof(BTree));
    if(b_tree){
        b_tree->root = NULL;
    }
    return b_tree;
}

BTreeNode *createBTreeNode(bool is_leaf) {

    BTreeNode *new_node = (BTreeNode *)malloc(sizeof(BTreeNode));
    if (new_node){
        new_node->num_keys = 0;
        new_node->is_leaf = is_leaf;
        for (int i = 0; i < M; i++) {
            new_node->children[i] = NULL;
        }
        return new_node;

    }
}


void printInLevels(BTreeNode *raiz) {

    if (raiz == NULL) return;

    Queue *q = createQueue();
    enqueue(q, raiz);

    while (!emptyQueue(q)) {
        int level_size = 0;
        QueueNode *temp = q->front;
        // Conta quantos nós existem neste nível
        while (temp) {
            level_size++;
            temp = temp->next;
        }

        // Imprime todos os nós deste nível
        for (int i = 0; i < level_size; i++) {
            BTreeNode *atual = dequeue(q);

            // Imprime as chaves reais (não todas as posições do array)
            printf("[");
            for (int k = 0; k < atual->num_keys; k++) {
                printf("%d", atual->keys[k]);
                if (k < atual->num_keys - 1) printf(" ");
            }
            printf("] ");

            // Enfileira os filhos reais
            for (int k = 0; k <= atual->num_keys; k++) {
                if (atual->children[k]) {
                    enqueue(q, atual->children[k]);
                }
            
            }

        }

        printf("\n"); // Quebra de linha para separar os níveis
    }
}

void splitChild(BTreeNode *parent, int index) {

    BTreeNode *child = parent->children[index];
    BTreeNode *new_node = createBTreeNode(child->is_leaf);
    
    new_node->num_keys = M/2 - 1;
    
    for (int i = 0; i < M/2 - 1; i++) {
        new_node->keys[i] = child->keys[i + M/2];
    }
    
    if (!child->is_leaf) {
        for (int i = 0; i < M/2; i++) {
            new_node->children[i] = child->children[i + M/2];
        }
    }
    
    child->num_keys = M/2 - 1;
    
    for (int i = parent->num_keys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    
    parent->children[index + 1] = new_node;
    
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    
    parent->keys[index] = child->keys[M/2 - 1];
    parent->num_keys++;
}

void insertNonFull(BTreeNode *node, int key) {

    int i = node->num_keys - 1;
    
    if (node->is_leaf) {
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        i++;
        
        if (node->children[i]->num_keys == M - 1) {
            splitChild(node, i);
            
            if (node->keys[i] < key) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

void Insert(BTree *b_tree, int key) {

    BTreeNode *aux_node = b_tree->root;

    if (aux_node == NULL) {
        // Árvore vazia
        b_tree->root = createBTreeNode(true);
        b_tree->root->keys[0] = key;
        b_tree->root->num_keys = 1;
    } else {
        if (aux_node->num_keys == M - 1) {
            //Caso o nó esteja cheio
            BTreeNode *new_root = createBTreeNode(false);
            new_root->children[0] = aux_node;
            splitChild(new_root, 0);
            b_tree->root = new_root;
        }
        insertNonFull(b_tree->root, key);
    }
}

void inOrder(BTreeNode *root) {

    if (root != NULL) {
        int i;
        for (i = 0; i < root->num_keys; i++) {
            inOrder(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        inOrder(root->children[i]);
    }
}


int lowerBound(int keys[], int n, int key) {

    int left = 0, right = n;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (keys[mid] < key) left = mid + 1;
        else right = mid;
        
    }

    return left;
}

BTreeNode * searchBTree(BTreeNode *node,int key){

    BTreeNode *aux_node = node;
    while(aux_node){
        int ind = lowerBound(aux_node->keys,aux_node->num_keys,key);
        if (ind < aux_node->num_keys && aux_node->keys[ind] == key) {
            printf("Valor encontrado : %d\n",aux_node->keys[ind]);
            return aux_node;
        }
        if(aux_node->is_leaf) return NULL;

        aux_node = aux_node->children[ind];
    }

    return NULL;
}

