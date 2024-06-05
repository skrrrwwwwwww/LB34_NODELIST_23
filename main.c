// Лабораторная работа №33. Двоичные деревья
// Студент: Тюрин Леонид 
// Группа: ИВТ1-23
// Вставить после максимального элемента цепочки L1 компонент, 
// равный среднему арифметическому компонентов списка L2; перед 
// минимальным элементом списка L1 – компонент, равный 
// произведению компонентов списка L2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}node;

node *create_node(int data){
    node *new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node *insert_node(node *root, int data){
    if(root == NULL){
        return create_node(data);
    }
    if(data < root->data){
        root->left = insert_node(root->left, data);
    }
    else if(data > root->data){
        root->right = insert_node(root->right, data);
    }
    return root;
}

void print_tree(node *root){
    if(root == NULL){
        return;
    }
    print_tree(root->left);
    printf("%d ", root->data);
    print_tree(root->right);
}
// Функция для поиска максимального элемента в дереве
int max_element(node *root){
    if(root == NULL){
        return -1;
    }
    int max_value = root->data;
    int left_max = max_element(root->left);
    int right_max = max_element(root->right);
    if(left_max > max_value){
        max_value = left_max;
    }
    if(right_max > max_value){
        max_value = right_max;
    }
    return max_value;
}
// Функция для поиска минимального элемента в дереве
int min_element(node *root){
    if(root == NULL){
        return -1;
    }
    if(root->left == NULL){
        return root->data;
    }
    int min_value = min_element(root->left);
    int right_min = min_element(root->right);
    if(right_min < min_value){
        min_value = right_min;
    }
    return min_value;
}
// Функция для поиска среднего арифметического элементов в дереве
float average_element(node *root){
    if(root == NULL){
        return 0;
    }
    int sum = 0;
    int count = 0;
    node *current = root;
    while(current != NULL){
        sum += current->data;
        count++;
        current = current->right;
    }
    return (float)sum / count;
}
// Функция для поиска компонента в дереве
node *search_component(node *root, int data){
    if(root == NULL){
        return NULL;
    }
    if(root->data == data){
        return root;
    }
    node *left_component = search_component(root->left, data);
    if(left_component != NULL){
        return left_component;
    }
    node *right_component = search_component(root->right, data);
    if(right_component != NULL){
        return right_component;
    }
    return NULL;
}
// Функция для вставки элемента после максимального элемента в дереве
node *insert_after_max(node *root, int data){
    int max_value = max_element(root);
    node *max_node = search_component(root, max_value);
    if(max_node == NULL){
        return NULL;
    }
    node *new_node = create_node(data);
    if(max_node->right == NULL){
        max_node->right = new_node;
    }
    else{
        node *current = max_node->right;
        while(current->right != NULL){
            current = current->right;
        }
        current->right = new_node;
    }
    return root;
}
// Функция для вставки элемента перед минимальным элементом в дереве
node *insert_before_min(node *root, int data){
    int min_value = min_element(root);
    node *min_node = search_component(root, min_value);
    if(min_node == NULL){
        return NULL;
    }
    node *new_node = create_node(data);
    if(min_node->left == NULL){
        min_node->left = new_node;
    }
    else{
        node *current = min_node->left;
        while(current->left != NULL){
            current = current->left;
        }
        current->left = new_node;
    }
    return root;
}
// Главная функция программы
int main(void) {
    
    srand(time(NULL));
    
    node *root = NULL;
    int n;
    
    printf("Введите количество элементов дерева: ");
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++){
        int data = rand() % 100; // Сгенерировать случайное число
        root = insert_node(root, data);
    }
  
    printf("Дерево: ");
    print_tree(root);
    printf("\n");
    printf("Максимальный элемент: %d\n", max_element(root));
    printf("Минимальный элемент: %d\n", min_element(root));
    printf("Среднее арифметическое элементов: %.2f\n", average_element(root));
    
    int data;
    
    // Вставка после максимального элемента среднего арифметического
    root = insert_after_max(root, (int)average_element(root));
    printf("Дерево после вставки после максимального элемента: ");
    print_tree(root);
    printf("\n");
    
    // Вставка перед минимальным элементом произведения элементов дерева
    int product = 1;
    node *current = root;
    while (current != NULL){
        product *= current->data;
        current = current->right;
    }
    root = insert_before_min(root, product);
    printf("Дерево после вставки перед минимальным элементом: ");
    print_tree(root);
    printf("\n");
    
    return 0;
}