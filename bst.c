#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bst.h"

BST* createBST(int (*cmp)(void*, void*), void (*print)(void*), void (*freeData)(void*)){
    BST *tree;
    BSTNode *root;
    tree=malloc(sizeof(BST));
    tree->compare=cmp;
    tree->print=print;
    tree->freeData=freeData;
    tree->root=NULL;
}

BSTNode* bstInsert(BSTNode* root, void* data, int (*cmp)(void*, void*)){
    if(root==NULL){
        return -1;
    }
    if(cmp(root->data,data)){
        if(root->left!=NULL){
            return bstInsert(root->left,data,cmp);
        }
        root->left=createBST;
        return 0;
    }
    if(!cmp(root->data,data)){
        if(root->right!=NULL){
            return bstInsert(root->right,data,cmp);
        }
        root->right=createBST;
        return 0;
    }
    return 0;
}

int compareInt(int *a, int *b){
    if(*a>*b){
        return 1;
    }
    return 0;
}
int compareChar(char *a, char *b){
    if(*a>*b){
        return 1;
    }
    return 0;
}
int compareString(char *a, char *b){
    return(strcmp(a,b)>0);
}    