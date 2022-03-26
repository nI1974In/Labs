#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

// Струкртура узла дерева
struct Viktor_tree {
    int key;                    // Ключ (значение) узла                
    int pow;                    // Степень узла
    struct Viktor_tree* parent; // Указатель на родителя узла
    struct Viktor_tree** heir;  // Указатель на динамический массив указателей на дочерние узлы
};

// Функция создания узла
struct Viktor_tree* create_elem(struct Viktor_tree* A, struct Viktor_tree* parent_n, int key_n) {

    struct Viktor_tree* A_tmp = (struct Viktor_tree*)calloc(1, sizeof(struct Viktor_tree));             // Выделение памяти для узла

    if (A_tmp == NULL) {                                                                                // Проверка на выделение памяти

        printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 1.0 -   ");
        printf("\n   Element %d can't be created because memory wasn't allocated.   ", key_n);
        printf("\n   ");

        return NULL;                                                                                        // Если память по какой-то причине не выделилась, то возвращаем NULL
    }

    A = A_tmp;                                                                                          // Иначе, если память успешно выделилась, то присваиваем указатель на выделенную память указателю нашего узла

    struct Viktor_tree** heir_tmp = (struct Viktor_tree**)calloc(10, sizeof(struct Viktor_tree*));      // Выделение памяти на массив указателей из 10 элементов

    if (heir_tmp == NULL) {                                                                             // Проверка на выделение памяти

        printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 1.1 -   ");
        printf("\n   Element %d can't be created because memory wasn't allocated.   ", key_n);
        printf("\n   ");

        free(A);                                                                                            // Если память уже здесь по какой-то причине не выделилась, то сначала освобождаем ранее выделенную память
        return NULL;                                                                                        // и уже потом снова возвращаем NULL
    }

    A->heir = heir_tmp;                                                                                 // Иначе, если вы оказались везучим, то присваиваем указателю на массив нашего узла указатель на ранее выделенную память
    A->key = key_n;                                                                                     // Присваиваем в значение ключа нашего узла переданный в аргументе ключ
    A->pow = 0;                                                                                         // Ставим значение степени на 0
    A->parent = parent_n;                                                                               // И точно также указателю на родителя узла присваиваем переданный в аргументе указатель

    return A;                                                                                           // В конце, как знак успешного завершения создания узла возвращаем указатель на него
}

// Глобальная переменная для учёта кол-ва отступов в процедуре print_tree
int count = 1;
// Процедура вывода дерева
void print_tree(struct Viktor_tree* A) {

    if (A == NULL) {                                                                                    // Проверка на нулевой указатель

        printf("--------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 2.0 -   ");
        printf("\n   Tree is empty.   ");
        printf("\n");

        return;                                                                                             // Если он в самом деле оказался пустым, то прерываем процедуру, ибо нечего выводить
    }

    printf("|  %d\n", A->key);                                                                          // Иначе выводим ключ нашего узла
    ++count;                                                                                            // и увеличиваем значение глобальной переменной для учёта числа выполненных рекурсий

    for (int i = 0; i < A->pow; ++i) {                                                                  // Далее, перебираем все дочерние узлы

        for (int j = 0; j < count; ++j) {                                                                   // Предварительно вставляя дополнительные пробелы для выделения дочерних узлов

            printf("   ");
        }

        print_tree(A->heir[i]);                                                                             // Вызываем эту же процедуру для дочерних узлов
    }

    --count;                                                                                            // Уменьшаем значение глобальной переменной
}

// Функция нахождения узла в дереве по ключу
struct Viktor_tree* find_elem(struct Viktor_tree* A, int key_n) {

    if (A == NULL) {                                                                                    // Проверка на нулевой указатель

        printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 3.0 -   ");
        printf("\n   Element %d can't be found because the tree is empty.   ", key_n);
        printf("\n   ");

        return NULL;                                                                                        // Если указатель пуст, то возвращаем NULL, т.к. не понятно в каком дереве/узле искать наш ключ
    }

    if (A->key == key_n) {                                                                              // Иначе, если ключ главного узла нашего дерева равен ключу, который передали в аргументе

        return A;                                                                                           // то возвращаем указатель на него
    }

    struct Viktor_tree* tmp = NULL;                                                                     // Инициализируем временный указатель на узел NULL'ом

    for (int i = 0; i < A->pow; ++i) {                                                                  // Перебираем все дочерний узлы нашего узла

        if (A->heir[i]->key == key_n) {                                                                     // Если ключ дочернего узла равен переданному в аргументе ключу

            return A->heir[i];                                                                                  // то возвращаем указатель на него
        }
        else if (A->heir[i]->pow != 0) {                                                                    // Иначе, если у дочернего элемента тоже имеются дочерние элементы

            tmp = find_elem(A->heir[i], key_n);                                                                 // то присваиваем временному указателю результат этой же функции вызванной для дочернего элемента 

            if (tmp != NULL) {                                                                                  // Если в результате окажется не пустой указатель - значит это указатель на нужый нам узел  

                return tmp;                                                                                         // возвращаем найденный указатель на узел и завершаем преждевременно функцию
            }
        }
    }

    return tmp;                                                                                         // Если после перебора всех узлов дерева мы не завершили преждевременно функцию -> значений tmp = NULL и возвращаем его, как знак отсутствия нужного нам узла
}

// Процедура добавления узла по ключу родителя
void add_elem(struct Viktor_tree* A, int parent_key, int key_n) {

    if (A == NULL) {                                                                                    // Проверка на нулевой указатель 

        printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 4.0 -   ");
        printf("\n   Element %d can't be added because the tree is empty.   ", key_n);
        printf("\n   ");

        return;                                                                                             // Если он оказался пустым, то прерываем процедуру, ибо некуда добавлять узел
    }

    if (find_elem(A, key_n) != NULL) {                                                                  // Проверяем с помощью функции find_elem существование такого же узла в нашем дереве

        printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 4.1 -   ");
        printf("\n   Element %d already exists.   ", key_n);
        printf("\n   ");

        return;                                                                                             // Если такой узел уже существует, то прерываем процедуру, т.к. не должно быть дубликатов ввиду определения дерева
    }

    struct Viktor_tree* parent = find_elem(A, parent_key);                                              // Иначе указателю parent присваиваем указатель на родительский узел узла, который должен быть добавлен

    if (parent == NULL) {                                                                               // Если указатель пуст, то такого узла не существует

        printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 4.2 -   ");
        printf("\n   Element %d can't be added to %d because %d doesn't exist.   ", key_n, parent_key, parent_key);
        printf("\n   ");

        return;                                                                                             // поэтому преждевременно завершаем процедуру
    }


    if ((parent->pow > 0) && (parent->pow % 10 == 0)) {                                                 // Иначе, если число дочерних элементов родительского узла равно 10, 20, 30 ...

        struct Viktor_tree** tmp = (struct Viktor_tree**)realloc(parent->heir, ((parent->pow + 10) * sizeof(struct Viktor_tree*)));     // то выделяем дополнительно 10 новых мест в памяти для нового узла, т.к. ранее выделенная память вся занята

        if (tmp == NULL) {                                                                                  // Если ЦП душит жаба на выделение памяти

            printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 4.3 -   ");
            printf("\n   Element %d can't be added to %d because memory wasn't reallocated.   ", key_n, parent_key);
            printf("\n   ");

            return;                                                                                             // то заверщаем процедуру, т.к. мест больше нет
        }

        parent->heir = tmp;                                                                                 // Иначе присваиваем указатель на перевыделенную память для массива нашему указателю

        for (int i = parent->pow; i < (parent->pow + 10); ++i) {                                            // И обнуляем все дополнительные указатели в нашем массиве, что раньше делал автоматически calloc 
            parent->heir[i] = NULL;
        }
    }

    parent->heir[parent->pow] = create_elem(parent->heir[parent->pow], parent, key_n);                  // Создаём в массиве нашего родителя новый дочерний узел в качестве последнего элемента массива 

    if (parent->heir[parent->pow] == NULL) {                                                            // Если возникла ошибка и память не выделилась

        printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 4.4 -   ");
        printf("\n   Element %d can't be added to %d because it wasn't created.   ", key_n, parent_key);
        printf("\n   ");

        return;                                                                                             // то заверщаем процедуру преждевременно
    }

    printf("\n   Element %d successfully added to element %d.", parent->heir[parent->pow]->key, parent->key);
    printf("\n   ");
    ++(parent->pow);                                                                                    // Увеличиваем степень родительского узла, к которому был добавлен наш узел
}

// Процедура удаления узла по ключу
void delete_elem(struct Viktor_tree* A, int key_n) {

    if (A == NULL) {                                                                                    // Проверка на пустой указатель

        printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 5.0 -   ");
        printf("\n   Element %d can't be deleted because tree is empty.   ", key_n);
        printf("\n   ");

        return;                                                                                             // Если указатель оказался пуст, то завершаем процедуру, т.к. неоткуда удалять узел
    }

    struct Viktor_tree* delete = find_elem(A, key_n);                                                   // Иначе находим узел, который надо удалить

    if (delete == NULL) {                                                                               // Если мы его не нашли

        printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 5.1 -   ");
        printf("\n   Element %d already doesn't exist.   ", key_n);
        printf("\n   ");

        return;                                                                                             // то заверщаем процедуру, ввиду итак не существования нужного узла
    }

    for (int i = 0; i < delete->pow; ++i) {                                                             // Перед удалением нашего узла еребираем все дочерние узлы

        if (delete->heir[i] != NULL) {
            delete_elem(delete->heir[i], delete->heir[i]->key);                                                 // и вызываем процедуру удаления для них
            delete->heir[i] = NULL;                                                                             // попутно обнуляя указатели на них
        }
    }

    if (delete->parent != NULL) {                                                                       // Затем, если у узла есть родитель

        for (int i = 0; i < delete->parent->pow; ++i) {                                                     // Находим в родительском массиве указателей на дочерние узлы нашего узла, который необходимо удалить, указатель на наш узел

            if (delete->parent->heir[i] != NULL) {

                if (delete->parent->heir[i]->key == key_n) {

                    if (i == (delete->parent->pow - 1)) {

                        delete->parent->heir[i] = NULL;                                                                     // И если он последний в этом массиве, то просто обнуляем его
                    }
                    else {

                        for (int j = i; j < (delete->parent->pow - 1); ++j) {

                            delete->parent->heir[j] = delete->parent->heir[j + 1];                                              // Иначе, если он находится в начале или между другими элементами массива, то на его место сдвигаем правый элемент и так до последенего
                        }

                        delete->parent->heir[delete->parent->pow - 1] = NULL;                                               // а последний указатель обнуляем
                    }

                    --(delete->parent->pow);                                                                                // обнулив указатель на наш узел в родительском массиве, уменьшаем его число дочерних узлов 
                    break;                                                                                                  // и прерываем цикл, так как нужный указатель был обнулён
                }
            }
        }
    }

    free(delete->heir);                                                                                 // Наконец, разобравшись с дочерними узлами и изменив родительский узел, мы со спокойной душой освобождаем сперва память нашего массива указателей
    free(delete);                                                                                       // а затем непосредственно узла   

    printf("\n   Element %d successfully deleted.", key_n);
    printf("\n   ");
}

// Функция нахождения степени дерева
int max_tree_pow(struct Viktor_tree* A) {

    if (A == NULL) {                                                                                    // Проверка на пустой указатель

        printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 6.0 -   ");
        printf("\n   Tree's pow can't be calculated because tree is empty.   ");
        printf("\n   ");

        return 0;                                                                                           // Если дерева нет, то и узлов нема
    }

    int max_pow = A->pow;                                                                               // Иначе присваиваем целочисленной переменной значение главного узла
    int max_heir_pow = 0;                                                                               // И инициализируем переменную для учёта степени дочерних узлов

    for (int i = 0; i < A->pow; ++i) {                                                                  // Собственно перебираем дочерние узлы

        max_heir_pow = max_tree_pow(A->heir[i]);                                                            // Вызывая для каждого эту же функцию

        if (max_heir_pow > max_pow) {                                                                       // И сравниваем со степенью нашего узла

            max_pow = max_heir_pow;                                                                             // Больше, значит присваиваем, нет - пропускаем
        }
    }

    return max_pow;                                                                                         // В итоге мы получим наибольшую степень среди всех узлов нашего дерева
}

// Функция выбора опции меню 
int menu_options()
{
    while (1) {																						    // бесконечный цикл для ввода одного из доступных символов

        switch (_getch()) {																		        // получение символа

        case '1': 																					        // добавить узел
            return 1;
            break;

        case '2': 																					        // вывести дерево
            return 2;
            break;

        case '3': 																					        // удалить узел
            return 3;
            break;

        case '4': 																					        // вычислить степень дерева
            return 4;
            break;

        case 27: 																					        // выйти из программы P.S. (27 = Esc)
            return 0;
            break;

        case '8':
            return 8;
            break;
        }
    }
}

void print_menu() {

    system("cls");

    printf("\n   ");
    printf("\n                                          Main menu                                           ");
    printf("\n   ========================================================================================   ");
    printf("\n   ");
    printf("\n   Add element | 1 |                  Display tree | 2 |               Delete element | 3 |   ");
    printf("\n   ");
    printf("\n   Calculate tree's pow | 4 |         Exit | Esc |                                            ");
    printf("\n   ");
    printf("\n   ========================================================================================   ");
    printf("\n   ");
}

void free_buff() {
    int tmp;

    tmp = scanf("%*[^\n]");
    tmp = scanf("%*c");
}

int main() {

    struct Viktor_tree* A = NULL;

    print_menu();

    printf("\n   Hello, wor... I mean user!");
    printf("\n   ");
    printf("\n   ");
    printf("\n      This program will never be sponsored by ZZZ, and it uses only the Latin alphabet.");
    printf("\n   That's why you shouldn't wonder why your attempt to confirm the action [Y\\N] doesn't");
    printf("\n   work. Just change the language.");
    printf("\n   ");
    printf("\n   Pay $197.99 to unlock Russian.");
    printf("\n   Here are the details of my card: 2*** **** **** 9970");
    printf("\n   ");

    int flag = 1;

    int parent_key = 0;
    int key_n = 0;
    char ch = ' ';
    
    while (flag) {

        switch (menu_options()) {

        case 0:

            print_menu();

            printf("\n   Goodbye.");
            printf("\n   ");

            flag = 0;
            break;

        case 1: {

            print_menu();

            if (A != NULL) {

                printf("\n   Please, input parent integer element key: ");

                while (!scanf("%d", &parent_key)) {
          
                    free_buff();

                    print_menu();

                    printf("\n   Is that you Viktor? Input CORRECT parent element integer key, don't be silly: ");

                }

                free_buff();

                print_menu();

                printf("\n   Parent element integer key: %d   ", parent_key);
                printf("\n   ");
            }

            printf("\n   Please, input element key: ");

            while (!scanf("%d", &key_n)) {

                free_buff();

                print_menu();

                if (A != NULL) {

                    printf("\n   Parent element integer key: %d   ", parent_key);
                    printf("\n   ");
                }

                printf("\n   Viktor, input CORRECT element integer key, the last one wasn't: ");

            }

            free_buff();

            print_menu();

            if (A != NULL) {

                if (key_n == parent_key) {

                    printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 0.0 -   ");
                    printf("\n   Element %d can't be added to itself.   ", key_n);
                    printf("\n   ");

                    break;
                }

                printf("\n   Parent element integer key: %d   ", parent_key);
                printf("\n   ");
            }

            printf("\n   Element integer key: %d   ", key_n);
            printf("\n   ");

            if (A != NULL) {

                printf("\n   Do you want add element %d to element %d? [Y\\N]", key_n, parent_key);
                printf("\n   ");
            }
            else {

                printf("\n   Do you want add %d as main element of tree? [Y\\N]", key_n);
                printf("\n   ");
            }

            do {
                ch = _getch();
            } while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N');

            print_menu();

            if (ch == 'y' || ch == 'Y') {

                if (A != NULL) {

                    add_elem(A, parent_key, key_n);
                }
                else {

                    A = create_elem(A, NULL, key_n);

                    if (A != NULL) {

                        printf("\n   Element %d successfully added.", key_n);
                        printf("\n   ");
                    }
                }
            }
            else {

                printf("\n   The adding process was breaked.");
                printf("\n   ");
            }

            break;
        }
        case 2:
            
            print_menu();

            printf("\n   ");

            print_tree(A);

            printf("   ");

            break;
        
        case 3:

            print_menu();

            if (A == NULL) {                                            

                printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 0.1 -   ");
                printf("\n   Tree is empty.   ");
                printf("\n   ");

                break;
            }

            printf("\n   Please, input element integer key to delete: ");

            while (!scanf("%d", &key_n)) {

                free_buff();

                print_menu();

                printf("\n   Are you an imbecile or something? Just input element integer key to delete. It's not hard: ");
            }

            free_buff();

            print_menu();

            printf("\n   Element integer key to delete: %d   ", key_n);
            printf("\n   ");

            printf("\n   Do you want delete element %d? [Y\\N]", key_n);
            printf("\n   ");

            do {
                ch = _getch();
            } while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N');

            print_menu();

            if (ch == 'y' || ch == 'Y') {

                if (A->key == key_n) {

                    delete_elem(A, key_n);
                    A = NULL;
                }
                else {

                    delete_elem(A, key_n);
                }

            }
            else {

                printf("\n   The deleting process was breaked.");
                printf("\n   ");
            }

            break;
        case 4:

            print_menu();

            if (A == NULL) {

                printf("\n   --------------------------!!!ACHTUNG!!!ACHTUNG!!!ACHTUNG!!!----------------------- 0.2 -   ");
                printf("\n   Tree is empty.   ");
                printf("\n   ");

                break;
            }

            printf("\n   The tree's pow: %d", max_tree_pow(A));
            printf("\n   ");

            break;

        case 8:

        {

            system("cls");

            printf("\n       ************************************************************************************");
            printf("\n       *                                                                                  *");
            printf("\n       * .^  .!:.:~~~~!!!!^         ......::^^^~~~!!!7777!!~^^^:!YYY5555PPPPPPPPPPPPPJYPP *");
            printf("\n       * .^  .~..:~~~~~~~!:   ..:::.::^^^~~!!777??777777!!~~^^::~JJJYYYY5P5555555PPP5JJ5P *");
            printf("\n       * .^  .~..:~~~~~~~~^:^~^:...:^^~~~!!77777?7777777777!~^::~?J?JYYYYY5YYYYYY555Y??55 *");
            printf("\n       * .^  .~..:^^~^~~^^~~!!^....:^~~!!!7777777777777777777!~:~????JJJYYYJJYYYYYY5J??YY *");
            printf("\n       * .^  .~..:^^^^^:^~~~!~:.....:^!!77777777777777777777777!!7?????JJJJJJJJYYYY5J7?YY *");
            printf("\n       * .^   ~...^^^^.:^~~~^:.::...::~777777777777!!!!!!!!!!!!!777????JJJJJJJJJJJYY?7?JJ *");
            printf("\n       *  ^.  ^...^^:..::^^^^..::::::^~!77777777777!!!!!!!!!!!!!!!7777??JJJ?????JJJJ?77JJ *");
            printf("\n       *  ^.  ^...^^..::::^^^:::^^^^^^~~!!!!!!77777!!!!!!!!!!!!!!!!777??JJ?????JJJJJ?!7JJ *");
            printf("\n       *  ^.  ^:..^:..:::::^^^^^^^^~^^^~~~~!7????77777!!!!!!!!!!!!!777???J?????JJJJJ7!?JJ *");
            printf("\n       *  ^.  ^:..^: .:::::^^^^^^:~~^~^:~!?JY555555YYJ?77!!!!777???777?????????JJJJJ7!7JJ *");
            printf("\n       *  ^.  ^:..:.  .:::^^~~^^^^~~^::~?Y555555PPPP55YJJ?7??J5PPP5YJ???????????JJJJ7!7?? *");
            printf("\n       *  :.  ^:..:.  .::^~~~~^:^^~^^^!?JJJYYY5555YJYJYYYJ??Y5PPPP5555???????????JYJ7!7?? *");
            printf("\n       *  ^.  ^:....  .:^^~~^^:::::::^?J??J5555555PPP5YY5Y?J5PGGPPPP5Y7!!????????JJJ7!7?? *");
            printf("\n       *  :.  ^:..:.  .~!!~^:::^~~~!7?YY?JYYYY5YJY5PP55Y5J7!Y5GG55P5YJ???JY????JJJJJ7!7?? *");
            printf("\n       *  ::  ^^....^~!!!~^::^::~~77?JJJ77??YYYYYJY5YYJYYJ?!!?Y5YYYY??7~~7??????JJJ?7!7?? *");
            printf("\n       *  ::  ^^ ..!7777!!^:^^::^^^~~!!????JJJJJJJ?????JJJ?7!!?JJJ??7?7~!???????JJJ?7!7?? *");
            printf("\n       *  ::  :^ ..~7~777!~::^^:::^^^~7?JJJJJJJJ????JJJJ7???7!7JJJ?77777????????JJJ?7!7?? *");
            printf("\n       *  ::  :^ ..:!^!7??!..^~^::^~~7??JJJJJ??????YYJJ?77???7!77??7!77?????????JJJ?7!??? *");
            printf("\n       *  :^  :^ .::::~7??!..:^^::^~!!777?????????Y5Y77??????7!!!!!!!!7?????????JJJ?7!??? *");
            printf("\n       *  :^  :~ .:^::^7777^ .:^^:^^~!7!7??JJ???JY5P5Y5555YYYYJ?7777!!7?????????JJJJ7!??7 *");
            printf("\n       *  :^  :~..:^^^:^^^!~ .^^^^:^~!77?JJJJJJJY5PPPPPGPGPP55J???777!7?????????JYJ?!!7?? *");
            printf("\n       *  :~  :~..:^^^~^::^:..:^~^:^~!7?JJJJJJJ555PPPPPPPPPPYJ???J?7777?????????JJY?!!7?? *");
            printf("\n       *  .~  .~..:^^^^^^: .^.:^^^^^~!?JYYYYYY5555PPPPPP5YYYJJJJ???777?????????JJYYJ77??? *");
            printf("\n       *  .~  .~..:^^^^^^^. ..:^^^^^~!?JYYYYYY55PPPPPPPP5YJYYY555??777??JJ??????JJYJ77??? *");
            printf("\n       *  .~. .!...^^^^^^:.   .^^^^~!7?JJYYYYY5PPPP55YYJJJ?????Y5Y?777???J??????JYJ?77??? *");
            printf("\n       *  .!. .!...^^^^^^. .  .:^^^~!7?JYYY55YYY5555555YYYYYJJ??JJJ?77??????????JJJ?77??? *");
            printf("\n       *  .7: .!...^^^^^.   ..:::^^~!7?YY5Y555YJJY55555YYYYYJJJ???J77???????????JYY?77??? *");
            printf("\n       *  .7:  !...^^^:.      .:^^^~~!?Y555YYYYYYYYYYYJJJ???????7??77???????????JYYJ77??? *");
            printf("\n       *   7:  !:..^:.:        .:^^^~!?Y5PPYY555YYYJJJJJ???7777???777???J???????JYYJ77?J? *");
            printf("\n       * ~~?!^^!:.:^~~~~:.:.....::^~~!7J5PPP5555YY5YYYJJJJJJ????777777??J???????JYYJ77??? *");
            printf("\n       * ^^::...:~!7????J?7~^^:.:~~~~!!7J5PPPPP5Y55PPPP5555YYYJ7!!?YYJJJJ?????JJJYYJ77?J? *");
            printf("\n       * ~^:::^!7??JJJY5Y5PP55J!!777??77?JYPPPPPPPPPGGGGGGPP5YJ?7!!!J555P5J???JJJYYJ77?J? *");
            printf("\n       * :^!7?JJJJJYYY55PPPPPGGGGPP555YYJJJY5PPGGGGGGGGGPP555YJ?7?7!~?5PPPP5J???YYYJ77??? *");
            printf("\n       * 7???????JJJYY555PPPPGGGGGGGBGGGPP555YY5PGGGGPPP5JJY?J?J??77!?55PPPGG5J?J5YJ77?J? *");
            printf("\n       * PPP5YJJJYYY55YY555PPPPPGGBBBBBBBBBBBGGP555PG5YJ??J5??7?YYYY5PPPP5PPGGG5YYYJ77?JJ *");
            printf("\n       * BBBBGGP5555555PP55PPPPPPGGGBBBBBBB#####BBGBBBBGPYY5J77J5PPPPPPPPP55PPPGGP5J77JJ? *");
            printf("\n       * GGGGGPGGP55PPPPPPPPPPPPPPPGGGBBBBBB##BBB##B######BBP5PGBGGPPPPPPPPP55PPGGGY77?JJ *");
            printf("\n       *                                     V. E. Zaycev                                 *");
            printf("\n       ************************************************************************************");

            break;

        }
        }
    }

    return 0;
}