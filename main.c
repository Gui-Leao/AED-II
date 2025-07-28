#include "BTree.h"
#include "BPlusTree.h"
#include "queue.h"
#include <time.h>


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
    char tipo[10];
    clock_t start,end;
    double duration;

    BTree *b_tree = NULL;
    BPlusTree *bplus_tree = NULL;

    printf("Escolha a árvore (btree/bplustree): ");
    scanf("%s", tipo);
    getchar();
    if (strcmp(tipo, "btree") == 0) {
        printf("teste b tree\n");
        b_tree = createBTree();
    } else {
        bplus_tree = createBPlusTree();
    }

    while(scanf("%s",opc) != EOF){
        if (strcmp("insert",opc)==0){
            Student *student = createStudent();
            long offset = saveInFile(student);
            if (b_tree)
                Insert(b_tree, student->id, offset);
            else
                BPlusInsert(bplus_tree, student->id, offset);
        }
        else if (strcmp("print",opc)==0){
            if (b_tree && b_tree->root) {
                printInLevels(b_tree->root);
            } else if (bplus_tree && bplus_tree->root) {
                BPlusPrintInLevels(bplus_tree->root);
            }
        }
        else if (strcmp("search",opc)==0){
            scanf("%d", &value);
            if (b_tree && b_tree->root) {
                searchBTree(b_tree->root, value);
            } else if (bplus_tree && bplus_tree->root) {
                BPlusSearch(bplus_tree->root, value);
            }
        }
        else if (strcmp("range",opc)==0){
            int start, end;
            start = clock();
            scanf("%d %d", &start, &end);
            if (b_tree && b_tree->root) {
                printRange(b_tree->root, start, end);
            } else if (bplus_tree && bplus_tree->root) {
                BPlusPrintRange(bplus_tree->root, start, end);
            }
            end = clock();
            duration = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Tempo de execução: %.6f segundos\n", duration);
        }
        else if (strcmp("age",opc)==0){
            int min_age;
            start=clock();
            scanf("%d", &min_age);
            if (b_tree && b_tree->root) {
                printAgeGreaterThan(b_tree->root, min_age);
            } else if (bplus_tree && bplus_tree->root) {
                BPlusPrintAgeGreaterThan(bplus_tree->root, min_age);
            }
            end = clock();
            duration = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Tempo de execução: %.6f segundos\n", duration);
        }
        else if (strcmp("in-order",opc)==0){
            if (b_tree && b_tree->root) {
                inOrder(b_tree->root);
                printf("\n");
            }
        }
    }
    return 0;
}