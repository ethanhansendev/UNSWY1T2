////////////////////////////
// Binary Search Tree ADT //
// Ethan Hansen           //
////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _node *Tree;

typedef struct _node {
    int value;
    Tree left;
    Tree right;
} Node;

Tree newTree (int value) {
    Tree new = malloc(sizeof(struct _node));
    new->right = NULL;
    new->left = NULL;
    new->value = value;
    return new;
}

void freeTree(Tree tree) {
    if (tree == NULL) return;
    Tree temp = tree->right;
    freeTree(tree->left);
    free(tree);
    freeTree(temp);
}

Tree insertTree(Tree tree, int value) {
    if (tree == NULL) return newTree(value);
    if (tree->value > value) {
        tree->right = insertTree(tree->right, value);
    } else {
        tree->left = insertTree(tree->left, value);
    }
    return tree;
} 

int treeContains(Tree tree, int value) {
    if (tree == NULL) return 0;
    if (tree->value > value) {
        return treeContains(tree->right, value);
    } else if (tree->value < value) {
        return treeContains(tree->left, value);
    } else {
        return 1;
    }
    return 0;

}

void showTree(Tree tree) {
    if (tree == NULL) return;
    printf("%d->", tree->value);
    showTree(tree->left);
    showTree(tree->right);
}

Tree treeJoin(Tree treeone, Tree treetwo) {
    Tree parent = NULL;
    Tree current = treetwo;
    while (current->left != NULL) {
        parent = current;
        current = current->left;
    }
    if (parent != NULL) {
        parent->left = current->right;
        current->right = parent;
    }
    current->left = treeone;
    return current;
}

Tree deleteNode(Tree tree, int value) {
    if (!treeContains(tree, value) || tree == NULL) return NULL;
    Tree current = tree;
    Tree parent = NULL;

    // Find Node & Parent
    if (current->value > value) {
        tree->left = deleteNode(tree->left, value);
    } else if (current->value < value) {
        tree->right = deleteNode(tree->right, value);
    } else {
        if (tree->left == NULL && tree->right == NULL) {
            free(tree);
            return NULL;
        } else if (tree->left == NULL) {
            Tree right = tree->right;
            free(tree);
            return right;
        } else if (tree->left == NULL) {
            Tree right = tree->right;
            free(tree);
            return right;
        } else {
            Tree sub = treeJoin(tree->left, tree->right);
            free(tree);
            return sub;
        }
    }
    return NULL;
}

int main(void) {
    printf("Create a tree:\n");
    int value = 0;
    Tree tree = NULL;
    while (scanf("%d", &value) && value != -1) {
        tree = insertTree(tree, value);
    }
    showTree(tree);
    printf("\nDelete a node: ");
    scanf("%d", &value);
    tree = deleteNode(tree, value);
    showTree(tree);
    return 0;
}