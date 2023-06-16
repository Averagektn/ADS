#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int data;
    struct tree *left;
    struct tree *right;
    int rTag;
}tree;

void goLeft(tree *p, tree *value);

void goRight(tree *p, tree *value){
    if (p->right == NULL || p->rTag == 0){
        p->right = value;
    }
    else {
        p = p->right;
        if (p->data > value->data)
            goLeft(p, value);
        else
            goRight(p, value);
    }
}

void goLeft(tree *p, tree *value){
    if (p->left == NULL)
        p->left = value;
    else {
        p = p->left;
        if (p->data > value->data)
            goLeft(p, value);
        else
            goRight(p, value);
    }
}

tree *add(tree *ptr, int elem){
    tree *tmp, *save = ptr;
    tmp = (tree*)malloc(sizeof(tree));
    tmp->data = elem;
    tmp->left = NULL;
    tmp->right = NULL;
    if (ptr == NULL)
        return tmp;
    else {
        if (ptr->data > elem)
            goLeft(ptr, tmp);
        else
            goRight(ptr, tmp);

    }
    return save;
}

void printTree (tree *p, int n){
    if (p->rTag != 0 && p->right != NULL) {
        printTree(p->right, n + 1);
    }

    for (int i = 0; i < n - 1; i++)
        printf("   ");
    if (n)
        printf("|->");
    printf("%d", p->data);
    if (p->rTag == 0)
        printf("(%d)",p->right->data);
    printf("\n");
    if (p->left != NULL)
        printTree(p->left, n+1);
}

void preorder(tree *ptr){
    if (ptr == NULL) {
        printf("0 ");
        return;
    }
    printf("(%d) ", ptr->data);
    preorder(ptr->left);
    printf("%d ", ptr->data);
    preorder(ptr->right);
    printf("%d ", ptr->data);
}

void inorder(tree *ptr){
    if (ptr == NULL) {
        printf("0 ");
        return;
    }
    printf("%d ", ptr->data);
    inorder(ptr->left);
    printf("(%d) ", ptr->data);
    inorder(ptr->right);
    printf("%d ", ptr->data);
}

void postorder(tree *ptr){
    if (ptr == NULL || ptr->rTag == 0) {
        printf("0 ");
        return;
    }
    printf("%d ", ptr->data);
    postorder(ptr->left);
    printf("%d ", ptr->data);
    postorder(ptr->right);
    printf("(%d) ", ptr->data);
}

void deThread(tree *ptr){
    if (ptr == NULL)
        return;
    if (ptr->rTag == 0)
        ptr->right = NULL;
    deThread(ptr->left);
    deThread(ptr->right);
}

tree *y = NULL;
void sim_print(tree *p);
void rightSew(tree *p){
    if (y != NULL){
        if (y->right == NULL){
            y->rTag = 0;
            y->right = p;
        }
        else
            y->rTag = 1;
    }
    y = p;
}
void sim_print(tree *p){
    if  (p != NULL){
        sim_print(p->left);
        rightSew(p);
        sim_print(p->right);
    }
}

void rightThread(tree *ptr){
    y = NULL;
    tree *tmp = ptr;
    deThread(ptr);
    while (tmp->right != NULL)
        tmp = tmp->right;
    sim_print(ptr);
    tmp->right = ptr;
    tmp->rTag = 0;
}

tree *find(tree *ptr, int value){
    while (ptr->left != NULL || ptr->rTag != 0){
        if (ptr->left != NULL && ptr->left->data == value)
            return ptr;
        if (ptr->rTag != 0 && ptr->right->data == value)
            return ptr;
        if (ptr->data > value)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    return NULL;
}

tree* deleteRoot(tree *ptr){
    if (ptr->left == NULL && ptr->rTag == 0)
        return NULL;
    if (ptr->left == NULL && ptr->rTag != 0)
        return ptr->right;
    if (ptr->left != NULL && ptr->rTag == 0)
        return ptr->left;
    if (ptr->left != NULL && ptr->rTag != 0){
        tree *tmp = ptr->left, *p;
        if (ptr->left->rTag == 0){
            ptr->data = ptr->left->data;
            p = ptr->left->left;
            free(ptr->left);
            ptr->left = p;
            return ptr;
        }
        while (tmp->right->rTag != 0 && tmp->right != NULL)
            tmp = tmp->right;
        ptr->data = tmp->right->data;
        tmp->rTag = 0;
        p = tmp->right->right;
        free(tmp->right);
        tmp->right = p;
        return ptr;
    }
    return ptr;
}

tree* delete(tree *ptr, int value){
    tree* save = ptr;
    if (ptr == NULL)
        return NULL;
    if (ptr->data == value){
        ptr = deleteRoot(ptr);
        return ptr;
    }
    ptr = find(ptr, value);
    if (ptr == NULL)
        return save;
    // right
    if (ptr->rTag != 0 && ptr->right->data == value)
        ptr->right = deleteRoot(ptr->right);
    // left
    if (ptr->left != NULL && ptr->left->data == value)
        ptr->left = deleteRoot(ptr->left);
    return save;
}

int main() {
    tree *head = NULL;
    int isAdd = 1, isDelete = 1, num;

    while (isAdd){
        printf("Enter element to add\n");
        scanf_s("%d", &num);
        head = add(head, num);
        printTree(head, 0);
        printf("To add another element press 1. To stop press 0\n");
        scanf_s("%d", &isAdd);
    }

    printTree(head, 0);
    printf("\nPreorder:\n");
    preorder(head);
    printf("\nInorder:\n");
    inorder(head);
    printf("\nPostorder:\n");
    postorder(head);
    rightThread(head);
    printf("\nThreaded tree:\n");
    printTree(head,0);

    while (isDelete){
        printf("\nEnter element to delete\n");
        scanf_s("%d", &num);
        head = delete(head, num);
        rightThread(head);
        printTree(head, 0);
        printf("To delete another element press 1. To stop press 0\n");
        scanf_s("%d", &isDelete);
    }
}
