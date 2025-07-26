#include "BTree.h"
#include "queue.h"

typedef struct {
    unsigned int id;          
    char nome[50];
    int idade;
} Aluno;

int main(){
    unsigned int value;
    char opc[20];
    BTree *b_tree= createBTree();
    //BTreeNode *root = NULL;

    while(scanf("%s",opc) != EOF){
        if (strcmp("insert",opc)==0){
            Aluno aluno;
            scanf("%u", &aluno.id);
            getchar(); // consome o '\n' após o id
            fgets(aluno.nome, sizeof(aluno.nome), stdin);
            aluno.nome[strcspn(aluno.nome, "\n")] = 0; // remove o '\n' do final
            scanf("%d", &aluno.idade);
            getchar(); // consome o '\n' após a idade

            char filename[64];
            snprintf(filename, sizeof(filename), "DB/aluno_%u.txt", aluno.id);
            FILE *fp = fopen(filename, "w");
            if (fp) {
                fprintf(fp, "%u %s %d\n", aluno.id, aluno.nome, aluno.idade);
                fclose(fp);
                fp = fopen(filename, "r"); 
            }
            Insert(b_tree, aluno.id, fp);
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
                // if(node){
                //     inOrder(node);
                //     printf("\n");
                // }
                    
                //else printf("Não encontrado !!\n");
            
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