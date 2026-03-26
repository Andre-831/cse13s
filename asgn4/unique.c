#include "tree.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  unique NUM NUM NUM ...       (normal output)\n");
    printf("        unique -d NUM NUM NUM ...    (debugging output)\n");
    exit(0);
}

/*
* purpose:  Check that the given string only has valid digits chars(0-9).
*           If any char is not a digit call print_usage() and exit.
*
* Parameter:  s - pointer to the string to check
*
*
* Returns:    nothing (void)
*
*/

void check_number(const char *s) { 
    // replace this comment with your code
    for (int i = 0; s[i] != '\0'; i++){
        if(!isdigit(s[i])){
            print_usage();
        }
    }
}

/*
* purpose:  Main function for the program. Reads command line arguments
*          and stores them in a binary tree. Each num is added only once but 
*          with a count of how many times it appeared.
*
*          if -d option is given, prints a debugging dump of the tree.
*          otherwise prints numbers and their counts in order.
*
* Parameters:  argc - number of command line arguments
*              argv - array of strings with the command line arguments
*
* Returns: 0 when program ends successfully.
*/


int main(int argc, char **argv) {
    // replace this comment with your code

    Tree *tree = tree_alloc(); //make a new tree
    bool d_seen = false; //flag for -d option

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-d") == 0){
            d_seen = true;
            continue;
        }
        check_number(argv[i]);
        tree_add(tree, atoi(argv[i]));
    }
    if(d_seen){
        tree_dump(tree);
    }
    else{
        tree_print(tree);
    }
    tree_free(&tree);


    return 0;
}
