#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
* Purpose:      This is a recursive routine that prints a subtree
*               starting at a Node.  Usually it is not called directly,
*               but it is called by tree_print().
*
*               We use an "in-order" traversal of the tree.  This means
*               that the following order is followed:
*
*                   1. if node is NULL, then just return
*                   2. recurse to node->left
*                   3. print count and key of node
*                   4. recurse to node->right
*
*               When printing a Node, use the printf() format string
*               "%d %d\n".  The first number is the count of the Node;
*               the second number is the key of the Node.
*
* Paramter:     A pointer to the root node of the tree.
*
* Returns:      nothing
*/
void tree_print_node(Node *node) {
    //assert(node);
    // replace this line with your source code

    if (node == NULL) { //check if node is null
        return;
    }
    tree_print_node(node->left); //recurse left
    printf("%d %d\n", node->count, node->key); //print count and key
    tree_print_node(node->right); //recurse right

}

/*
* Purpose:      Print a Tree by calling tree_print_node() with the
*               root node of the tree.
*
*               The value of tree->root might be NULL, in which case
*               the tree is empty and nothing is printed.
*
* Parameter:    Pointer to the Tree.
*
* Returns:      nothing
*/
void tree_print(Tree *tree) {
    assert(tree);
    // replace this line with your source code
    
    if(tree->root == NULL){ //check if root is null
       return; 
    }
    tree_print_node(tree->root);

}

/*
* Purpose:      Allocate a new (empty) tree.
*
*               Remember to use assert() to check that calloc() returns 
*               a non-NULL pointer.
*
* Parameters:   none
*
* Returns:      Pointer to a new Tree.
*/
Tree *tree_alloc(void) {
    // replace this line with your source code
    Tree *tree = (Tree *)calloc(1, sizeof(Tree)); //allocate memory for tree
    assert(tree != NULL); //check if allocation was successful
    return tree;
}

/*
* Purpose:      This is the most important part of the Tree abstract
*               data type.
*
*               This function searches for the key, and then:
*               
*                 - If the key is IN THE TREE, then increment the count
*                   for that key.
*               
*                 - If the key is NOT IN THE TREE, then add it to the
*                   tree, and set its count to 1.
*               
*               See Section 2.2 of the assignment PDF for more information.
*
* Parameters:   tree    - Pointer to the Tree.
*               key     - The value to add to the Tree.
*
* Returns:      nothing
*/
void tree_add(Tree *tree, int key) {
    assert(tree);
    // replace this line with your source code

    Node **cur = &tree->root; //pointer to pointer to current node
    while (*cur){
        if(key <(*cur)->key){
            cur = &(*cur)->left; //move to left child
        } else if (key > (*cur)->key){
            cur = &(*cur)->right; //move to right child
        } else {
            (*cur)->count += 1; //key found, increment count
            return;
        } 
    }
    *cur = (Node *)calloc(1, sizeof(Node)); //key not found, allocate memory for new node
    (*cur)->key = key; //set key
    (*cur)->count = 1; //set count to 1
}

/*
* Purpose:      This is a recursive routine that frees a subtree
*               starting at a node.  Usually it is not called
*               directly, but it is called by tree_free().
*
*               We use a "postorder" traversal of the tree to free all
*               of the nodes of the tree.  This means that the
*               following order is followed:
*
*                  1. if node is NULL, then just return.
*                  2. recurse to node->left
*                  3. recurse to node->right
*                  4. free the node
*
* Parameter:    Pointer to the root node of the tree.
*
* Returns:      nothing
*/
void tree_free_node(Node *node) {
    // replace this line with your source code
    if (node == NULL) { 
        return;
    }
    tree_free_node(node->left);
    tree_free_node(node->right);
    free(node);
}

/*
* Purpose:      Free a Tree that had been allocated by tree_alloc().
*
*                 1. If the tree pointer *p already is NULL, then the
*                    tree already has been freed, and so just return.
*                 2. Free the nodes of the tree by calling tree_free_node()
*                    with the root of the tree.
*                 3. Free the tree node by calling free(*p);
*                 4. Set the tree pointer to NULL:  *p = NULL;
*
* Parameter:    p  -  Pointer to a pointer to the node to be freed.
*/
void tree_free(Tree **p) {
    assert(p);
    // replace this line with your source code
    if (*p == NULL){ //check if tree is already null
        return;
    }
    tree_free_node((*p)->root); //free nodes
    free(*p); //free tree
    *p = NULL; //set pointer to null
}

/*
* Purpose:      Recursive routine for printing a debugging dump of a
*               binary tree.  Usually this routine is not called
*               directly, but it is called by tree_dump().
*
* Parameters:   node    - pointer to the root node of the tree
*               level   - indentation level
*               prefix  - char to print first:  <, /, or \
*
* Returns:      nothing
*/
void tree_dump_node(Node *node, int level, char prefix) {
    if (node) {
        tree_dump_node(node->right, level + 1, '/');
        printf("%*c %d (x%d)\n", 4 * level + 1, prefix, node->key,
                node->count);
        tree_dump_node(node->left, level + 1, '\\');
    } else {
        printf("%*c NULL\n", 4 * level + 1, prefix);
    }
}

/*
* Purpose:      Print debugging output by calling tree_dump_node() with
*               the root of the tree.
*
*               The result of calling this routine is a text-based image of
*               the tree that is printed sideways with the root on the
*               left.  For example, this is the debugging output for a tree
*               with 314 at the root, 76 to the left, and 95064 to the
*               right.  (Rotate your head to the left to see it with the
*               root at the top.)
*
*                                 / NULL
*                             / 95064 (x2)
*                                 \ NULL
*                         < 314 (x1)
*                                 / NULL
*                             \ 76 (x3)
*                                 \ NULL
*
* Parameter:    Pointer to the root node of the tree.
*
* Returns:      nothing
*/
void tree_dump(Tree *tree) {
    assert(tree);
    tree_dump_node(tree->root, 0, '<');
}

