#include <stdio.h>

#include "extclib/tree.h"

int main(void) {
    Tree *tree = new_tree(STRING_TYPE, DECIMAL_TYPE);

    set_tree(tree, string("B"), decimal(10));
    set_tree(tree, string("A"), decimal(20));
    set_tree(tree, string("C"), decimal(30));

    del_tree(tree, string("B"));

    uint8_t *elem = "A";
    if (in_tree(tree, string(elem))) {
        printf("%d\n", get_tree(tree, string(elem)).decimal);
    }

    println_tree(tree);
    println_tree_branches(tree);
    
    free_tree(tree);
    return 0;
}
