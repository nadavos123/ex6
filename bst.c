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
    if(root=NULL){                    
        root=malloc(sizeof(BSTNode));
        root->data=data;
        root->right=NULL;
        root->left=NULL;
        return root;
    }
    if(root->left==NULL&&!cmp(data, root->data)){
        return(bstInsert(root->left, data, cmp));
    }
    return(bstInsert(root->right, data, cmp));
    
}
BST* createBST(int (*cmp)(void*, void*), void (*print)(void*), void (*freeData)(void*)){

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
    if(strcmp(a,b)>0){
        return 1;
    }
    return 0;
}    