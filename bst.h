#ifndef BST_H
#define BST_H

#include "game.h"

typedef struct BSTNode {
    void* data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct {
    BSTNode* root;
    int (*compare)(void*, void*);
    void (*print)(void*);
    void (*freeData)(void*);
} BST;

BST* createBST(int (*cmp)(void*, void*), void (*print)(void*), void (*freeData)(void*));
BSTNode* bstInsert(BSTNode* root, void* data, int (*cmp)(void*, void*));
void* bstFind(BSTNode* root, void* data, int (*cmp)(void*, void*));
void bstInorder(BSTNode* root, void (*print)(void*));
void bstPreorder(BSTNode* root, void (*print)(void*));
void bstPostorder(BSTNode* root, void (*print)(void*));
void bstFree(BSTNode* root, void (*freeData)(void*));

// Copare Functions

int* compareItem(Item *i1, Item *i2){
    int cmp = strcmp(i1->name,i2->name);
    if(!cmp){
        return cmp;
    }
    
    if((i1->value)!=(i2->value)){
        return ((i1->value)-(i2->value));
    }
    return i1->type;
}
int* compareItem(Item *i1, Item *i2);
int* compare
int* compareInt(int* a, int* b);
char* compareChar(char* a, char* b);
char* compareString(char* a, char* b);
#endif
