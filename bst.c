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

void* bstFind(BSTNode* root, void* data, int (*cmp)(void*, void*)){
    if(root==NULL) return NULL;

    int result = cmp(root->data,data);
    if(result==0){
        return data;
    }
    if(result>0){
        return bstFind(root->left,data,cmp);
    }
    return bstFind(root->right, data, cmp);
}

void bstInorder(BSTNode* root, void (*print)(void*)){
    if(root==NULL){
        return;
    }    
    bstInorder(root->left, print);
    print(root->data);
    bstInorder(root->right, print);
}
void bstPreorder(BSTNode* root, void (*print)(void*)){
    if(root==NULL){
        return;
    }
    print(root->data);
    bstPreorder(root->left, print);
    bstPreorder(root->right, print);
}
void bstPostorder(BSTNode* root, void (*print)(void*)){
    if(root==NULL){
        return;
    }
    bstPostorder(root->left, print);
    bstPostorder(root->right, print);
    print(root->data);
}
void bstFree(BSTNode* root, void (*freeData)(void*)){
    if(root==NULL){
        return;
    }
    bstFree(root->left,freeData);
    bstFree(root->right, freeData);
    freeData(root->data);
    free(root);
}