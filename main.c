#include "BTree.h"
#include "queue.h"

int main(){
    int value;
    char opc[20];
    BTree *b_tree= createBTree();
    //BTreeNode *root = NULL;

    while(scanf("%s",opc) != EOF){
        if (strcmp("insert",opc)==0){
            scanf("%d",&value);
            Insert(b_tree,value);
        }
        // else if (strcmp("delete",opc)==0){
        //     scanf("%d",&value);
        //     rem_node = removeTree(t,value);
        //     if(rem_node!=NULL){
        //         printf("%d\n",rem_node->value);
        //     }
        // }
        else if (strcmp("print",opc)==0){
            if(b_tree->root){
                printInLevels(b_tree->root);
            }
        
        }
        else if (strcmp("search",opc)==0){
            if(b_tree->root){
                scanf("%d",&value);
                BTreeNode *node = searchBTree(b_tree->root,value);
                if(node){
                    inOrder(node);
                    printf("\n");
                }
                    
                else printf("Não encontrado !!\n");
            
            }
        }

        else if (strcmp("in-order",opc)==0){
            if(b_tree->root){
                inOrder(b_tree->root);
                printf("\n");
            }
        }
       }
    return 0;
}