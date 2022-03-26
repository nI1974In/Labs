#include <stdlib.h>
#include <stdio.h>

struct Viktor_tree {
    int key;                        // ключ
    int pow;                        // число преемников
    struct Viktor_tree* parent;     // родитель
    struct Viktor_tree* heir;       // массив преемников
};

// Процедура инициализации узла
void init_elem(struct Viktor_tree* A, struct Viktor_tree* parent_n, int key_n) {
    A->key = key_n;
    A->pow = 0;
    A->parent = parent_n;
    A->heir = (struct Viktor_tree*)malloc(10 * sizeof(struct Viktor_tree*));
    printf("Element %d initialized\n", A->key);
}

// Процедура удаления узла в дереве по ключу
void delete_elem(struct Viktor_tree* A, int key_n) {

    if (A->key == key_n) {

        for (int i = 0; i < A->pow; ++i) {
            delete_elem(&(A->heir[i]), A->heir[i].key);
        }

        free(A->heir);

        if (A->parent != NULL) { --(A->parent->pow); }
        A->parent = NULL;
        A->key = 0;

        printf("Element %d deleted\n", key_n);

    }
    else {

        for (int i = 0; i < A->pow; ++i) {
            delete_elem(&(A->heir[i]), key_n);
        }
    }

}

// Глобальная переменная для учёта рекурсии
int count = 0;
// Процедура вывода узла и его преемников
void print_tree(struct Viktor_tree* A) {

    ++count;
    printf("|\t%d\n", A->key);

    for (int i = 0; i < A->pow; ++i) {

        for (int j = 0; j < count; ++j) {
            printf("\t");
        }

        print_tree(&(A->heir[i]));
    }

    --count;
}

void add_elem(struct Viktor_tree* A, int parent_key, int heir_key) {

    if (A->key == parent_key) {


        if ((A->pow / 10 > 0) && (A->pow % 10 == 0) && (A->heir != NULL)) { 

            struct Viktor_tree* temp = (struct Viktor_tree*) realloc(A->heir, (A->pow + 10) * sizeof(struct Viktor_tree*));

            if (temp != NULL) { A->heir = temp; }
            
        }
        
        init_elem(&(A->heir[A->pow]), A, heir_key);
        printf("Element %d added to %d\n", A->heir[A->pow].key, A->key);
        ++(A->pow);

    }
    else {

        for (int i = 0; i < A->pow; ++i) {
            add_elem(&(A->heir[i]), parent_key, heir_key);
        }
    }

}

int main() {

    struct Viktor_tree A;

    init_elem(&A, NULL, 10);

    print_tree(&A);

    delete_elem(&A, 10);

    print_tree(&A);

    init_elem(&A, NULL, 7);

    print_tree(&A);

    add_elem(&A, 7, 5);

    print_tree(&A);

    add_elem(&A, 7, 4);

    print_tree(&A);

    add_elem(&A, 7, 2);

    print_tree(&A);

    add_elem(&A, 2, 1);

    print_tree(&A);

    add_elem(&A, 2, 3);

    print_tree(&A);

    add_elem(&A, 4, 9);

    print_tree(&A);

    add_elem(&A, 9, 8);

    print_tree(&A);

    delete_elem(&A, 9);

    print_tree(&A);

    delete_elem(&A, 3);

    print_tree(&A);

    for (int i = 0; i < 11; i++)
    {
        add_elem(&A, 2, (10 + i));

        print_tree(&A);
    }

    return 0;
}