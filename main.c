#include "BTree.h"
#include "queue.h"


typedef struct {
    unsigned int id;
    char name[50];
    int age;
} Student;

Student * createStudent(){
    Student *student = (Student*)malloc(sizeof(Student));
    if (student){
        scanf("%u", &student->id);
        getchar();
        fgets(student->name, sizeof(student->name), stdin);
        student->name[strcspn(student->name, "\n")] = 0;
        scanf("%d", &student->age);
        getchar();
    }
    return student;
}

long saveInFile(Student *student) {
    FILE *fp = fopen("DB/alunos.txt", "a+");
    long offset = -1;
    if (fp) {
        fseek(fp, 0, SEEK_END);
        offset = ftell(fp);
        fprintf(fp, "%u %s %d\n", student->id, student->name, student->age);
        fclose(fp);
    }
    return offset;
}

            
int main(){
    unsigned int value;
    char opc[20];
    BTree *b_tree= createBTree();
    //BTreeNode *root = NULL;

    while(scanf("%s",opc) != EOF){
        if (strcmp("insert",opc)==0){
            Student *student = createStudent();
            // Salva no arquivo único e obtém offset
            long offset = saveInFile(student);
            Insert(b_tree, student->id, offset);
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