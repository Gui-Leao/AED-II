#include "BTree.h"
#include "queue.h"

int main(){
    int value;
    char opc[20];
    //BTree *b_tree= createBTree();
    BTreeNode *root = NULL;

    while(scanf("%s",opc) != EOF){
        if (strcmp("insert",opc)==0){
            scanf("%d",&value);
            Insert(&root,value);
        }
        // else if (strcmp("delete",opc)==0){
        //     scanf("%d",&value);
        //     rem_node = removeTree(t,value);
        //     if(rem_node!=NULL){
        //         printf("%d\n",rem_node->value);
        //     }
        // }
        else if (strcmp("print",opc)==0){
            if(root){
                imprimirPorNiveis(root);
            }
        }
       }
    return 0;
}