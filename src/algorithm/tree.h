#ifndef TREE_H
#define TREE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct BiTree {
    char c;
    BiTree *lchild;
    BiTree *rchild;
};


void Build_(BiTree *root, char s[], int &i) {
    if (i >= strlen(s)) {
        root = NULL;
    } else if (s[i] == '#') {
        i++;
        root = NULL;
    } else {
        root = (BiTree *) malloc(sizeof(BiTree));
        root->c = s[i];
        i++;
        Build_(root->lchild, s, i);
        Build_(root->rchild, s, i);
    }
}

void Inorder(BiTree *root) {
    if (root == NULL) {
        return;
    }
    Inorder(root->lchild);
    printf("%c", root->c);
    Inorder(root->rchild);
    return;
}

int tree_test() {
    char s[100] = "abcdef";
//    scanf("%s", s);
    int i = 0;
    BiTree *root;
    Build_(root, s, i);
    Inorder(root);
    return 0;
}

#endif // TREE_H
