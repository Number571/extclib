#include "extclib/hashtab.h"
#include "extclib/dynamic.h"
#include "extclib/bigint.h"
#include "extclib/list.h"

// gcc main.c extclib/extclib.o -o main

int main(void) {
    HashTab *hashtab = new_hashtab(100, STRING_ELEM, DYNAMIC_ELEM);

    set_hashtab(hashtab, string("A"), dynamic(new_dynamic('L', list(new_list(DECIMAL_ELEM)))));
    set_hashtab(hashtab, string("B"), dynamic(new_dynamic('B', bigint(new_bigint("87215378126371524781263781")))));
    set_hashtab(hashtab, string("C"), dynamic(new_dynamic('s', string("hello, world!"))));

    push_list(value_dynamic(get_hashtab(hashtab, string("A")).dynamic).list, decimal(5));
    push_list(value_dynamic(get_hashtab(hashtab, string("A")).dynamic).list, decimal(10));
    push_list(value_dynamic(get_hashtab(hashtab, string("A")).dynamic).list, decimal(20));

    println_dynamic(get_hashtab(hashtab, string("B")).dynamic);

    println_hashtab(hashtab);
    free_hashtab(hashtab);
    return 0;
}
