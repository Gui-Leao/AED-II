#include "BPlusTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

BPlusTree *createBPlusTree() {

    BPlusTree *b_plus_tree = (BPlusTree *)malloc(sizeof(BPlusTree));
    if (b_plus_tree){
        b_plus_tree->root = NULL;
    }
    return b_plus_tree;
}

BPlusTreeNode *createBPlusTreeNode(bool is_leaf) {
    BPlusTreeNode *new_node = (BPlusTreeNode *)malloc(sizeof(BPlusTreeNode));
    if (new_node) {
        new_node->num_keys = 0;
        new_node->is_leaf = is_leaf;
        if (is_leaf) {
            new_node->ptrs.leaf.next = NULL;
        } else {
            for (int i = 0; i < BPLUS_M; i++){
                new_node->ptrs.children[i] = NULL;
            }
        }
    }
    return new_node;
}


void splitChildBP(BPlusTreeNode *parent, int index) {
    BPlusTreeNode *child = parent->ptrs.children[index];
    BPlusTreeNode *new_node = createBPlusTreeNode(child->is_leaf);

    int mid = BPLUS_M / 2;

    if (child->is_leaf) {
        // Número de chaves no novo nó
        new_node->num_keys = child->num_keys - mid;

        // Copia as chaves e offsets para o novo nó
        for (int i = 0; i < new_node->num_keys; i++) {
            new_node->keys[i] = child->keys[mid + i];
            new_node->ptrs.leaf.offsets[i] = child->ptrs.leaf.offsets[mid + i];
        }

        // Atualiza a lista encadeada das folhas
        new_node->ptrs.leaf.next = child->ptrs.leaf.next;
        child->ptrs.leaf.next = new_node;

        // Ajusta o número de chaves do nó original (só a metade esquerda)
        child->num_keys = mid;

        // **Promove a primeira chave do novo nó (NÃO remove da folha!)**
        for (int i = parent->num_keys; i > index; i--) {
            parent->ptrs.children[i + 1] = parent->ptrs.children[i];
            parent->keys[i] = parent->keys[i - 1];
        }
        parent->ptrs.children[index + 1] = new_node;
        parent->keys[index] = new_node->keys[0];  // separador para o pai
        parent->num_keys++;
    } else {
        // Divisão de nó interno
        new_node->num_keys = child->num_keys - mid - 1;

        // Copia as chaves da metade direita (após a chave promovida)
        for (int i = 0; i < new_node->num_keys; i++) {
            new_node->keys[i] = child->keys[mid + 1 + i];
        }

        // Copia os filhos correspondentes
        for (int i = 0; i <= new_node->num_keys; i++) {
            new_node->ptrs.children[i] = child->ptrs.children[mid + 1 + i];
        }

        // Ajusta o número de chaves do nó original (metade esquerda)
        child->num_keys = mid;

        // Promove a chave do meio para o pai (como separador)
        for (int i = parent->num_keys; i > index; i--) {
            parent->ptrs.children[i + 1] = parent->ptrs.children[i];
            parent->keys[i] = parent->keys[i - 1];
        }
        parent->ptrs.children[index + 1] = new_node;
        parent->keys[index] = child->keys[mid];  // separador para o pai
        parent->num_keys++;
    }
}


void insertNonFullBP(BPlusTreeNode *node, int key, long offset) {
    int i = node->num_keys - 1;

    if (node->is_leaf) {
        // Desloca para abrir espaço mantendo ordenação
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            node->ptrs.leaf.offsets[i + 1] = node->ptrs.leaf.offsets[i];
            i--;
        }
        // Insere chave e offset
        node->keys[i + 1] = key;
        node->ptrs.leaf.offsets[i + 1] = offset;
        node->num_keys++;
    } else {
        // Busca o filho onde a chave deve ser inserida
        while (i >= 0 && node->keys[i] > key) i--;
        i++;

        // Se o filho está cheio, divide antes de descer
        if (node->ptrs.children[i]->num_keys == BPLUS_M - 1) {
            splitChildBP(node, i);
            // Verifica se devemos descer para o novo nó à direita
            if (node->keys[i] < key) i++;
        }

        // Continua inserindo no filho apropriado
        insertNonFullBP(node->ptrs.children[i], key, offset);
    }
}


void BPlusInsert(BPlusTree *tree, int key, long offset) {
    if (!tree->root) {
        tree->root = createBPlusTreeNode(true);
        tree->root->keys[0] = key;
        tree->root->ptrs.leaf.offsets[0] = offset;
        tree->root->num_keys = 1;
        tree->root->ptrs.leaf.next = NULL;
        return;
    }
    if (tree->root->num_keys == BPLUS_M - 1) {
        BPlusTreeNode *new_root = createBPlusTreeNode(false);
        new_root->ptrs.children[0] = tree->root;
        splitChildBP(new_root, 0);
        tree->root = new_root;
    }
    insertNonFullBP(tree->root, key, offset);
}

BPlusTreeNode *BPlusSearch(BPlusTreeNode *node, int key) {
    while (node) {
        int i = 0;
        while (i < node->num_keys && key >= node->keys[i]) i++;
        if (node->is_leaf) {
            for (int j = 0; j < node->num_keys; j++) {
                if (node->keys[j] == key) {
                    printf("Valor encontrado: %d\n", node->keys[j]);
                    FILE *fp = fopen("DB/alunos.txt", "r");
                    if (fp) {
                        fseek(fp, node->ptrs.leaf.offsets[j], SEEK_SET);
                        char buffer[256];
                        if (fgets(buffer, sizeof(buffer), fp)) {
                            printf("Registro: %s", buffer);
                        }
                        fclose(fp);
                    }
                    return node;
                }
            }
            return NULL;
        } else {
            node = node->ptrs.children[i];
        }
    }
    return NULL;
}

void BPlusPrintInLevels(BPlusTreeNode *root) {
    if (!root) return;
    BPlusTreeNode *level[100];
    int front = 0, rear = 0;
    level[rear++] = root;
    while (front < rear) {
        int count = rear - front;
        for (int i = 0; i < count; i++) {
            BPlusTreeNode *node = level[front++];
            printf("[");
            for (int k = 0; k < node->num_keys; k++) {
                printf("%d", node->keys[k]);
                if (k < node->num_keys - 1) printf(" ");
            }
            printf("] ");
            if (!node->is_leaf) {
                for (int k = 0; k <= node->num_keys; k++) {
                    if (node->ptrs.children[k]) level[rear++] = node->ptrs.children[k];
                }
            }
        }
        printf("\n");
    }
}

void BPlusPrintRange(BPlusTreeNode *root, int start, int end) {
    if (!root) return;
    BPlusTreeNode *node = root;
    while (!node->is_leaf) node = node->ptrs.children[0];
    FILE *fp = fopen("DB/alunos.txt", "r");
    if (!fp) return;
    while (node) {
        for (int i = 0; i < node->num_keys; i++) {
            if (node->keys[i] >= start && node->keys[i] <= end) {
                fseek(fp, node->ptrs.leaf.offsets[i], SEEK_SET);
                char buffer[256];
                if (fgets(buffer, sizeof(buffer), fp)) {
                    printf("Registro: %s", buffer);
                }
            }
        }
        node = node->ptrs.leaf.next;
    }
    fclose(fp);
}

void BPlusPrintAgeGreaterThan(BPlusTreeNode *root, int min_age) {
    if (!root) return;
    BPlusTreeNode *node = root;
    while (!node->is_leaf) node = node->ptrs.children[0];
    FILE *fp = fopen("DB/alunos.txt", "r");
    if (!fp) return;
    while (node) {
        for (int i = 0; i < node->num_keys; i++) {
            fseek(fp, node->ptrs.leaf.offsets[i], SEEK_SET);
            char buffer[256];
            if (fgets(buffer, sizeof(buffer), fp)) {
                unsigned int id;
                char name[50];
                int age;
                if (sscanf(buffer, "%u %49[^0-9] %d", &id, name, &age) == 3) {
                    if (age > min_age) {
                        buffer[strcspn(buffer, "\n")] = 0;
                        printf("Registro: %s\n", buffer);
                    }
                }
            }
        }
        node = node->ptrs.leaf.next;
    }
    fclose(fp);
}
