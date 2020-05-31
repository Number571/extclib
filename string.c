#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "string.h"

#define CONST_HASH 31

typedef struct String {
    uint8_t *chars;
    uint32_t hash;
    size_t len;
    size_t cap;
} String;

static void _realloc_string(String *string, size_t length);
static void _str_hash_len(uint8_t *str, uint32_t *hash, size_t *index);

extern String *new_string(uint8_t *str) {
    const size_t CAPMEM = 1000;
    String *string = (String*)malloc(sizeof(String));
    _str_hash_len(str, &string->hash, &string->len);
    string->cap = (CAPMEM + string->len) << 1;
    string->chars = (uint8_t*)malloc(string->cap * sizeof(uint8_t));
    memcpy(string->chars, str, string->len * sizeof(uint8_t));
    return string;
}

extern void cat_in_string(String *x, uint8_t *y) {
    size_t y_len = strlen(y);
    size_t new_len = x->len + y_len;
    if (new_len >= x->cap) {
        _realloc_string(x, new_len);
    }
    for (size_t i = 0, j = x->len; i < y_len; ++i, ++j) {
        x->hash = y[i] + CONST_HASH * x->hash;
        x->chars[j] = y[i];
    }
    x->len = new_len;
}

extern void cpy_in_string(String *x, uint8_t *y) {
    uint32_t hash;
    size_t length;
    _str_hash_len(y, &hash, &length);
    if (length >= x->cap) {
        _realloc_string(x, length);
    }
    x->len = length;
    x->hash = hash;
    memcpy(x->chars, y, length * sizeof(uint8_t));
}

extern int8_t catn_in_string(String *x, uint8_t *y, size_t quan) {
    size_t y_len = strlen(y);
    if (quan > y_len) {
        return 1;
    }
    size_t new_len = x->len + quan;
    if (new_len >= x->cap) {
        _realloc_string(x, new_len);
    }
    for (size_t i = 0, j = x->len; i < quan; ++i, ++j) {
        x->hash = y[i] + CONST_HASH * x->hash;
        x->chars[j] = y[i];
    }
    x->len = new_len;
    return 0;
}

extern int8_t cpyn_in_string(String *x, uint8_t *y, size_t quan) {
    uint32_t hash = 0;
    size_t length = 0;
    for (; y[length] && length < quan; ++length) {
        hash = y[length] + CONST_HASH * hash;
    }
    if (length != quan) {
        return 1;
    }
    if (length >= x->cap) {
        _realloc_string(x, length);
    }
    x->len = length;
    x->hash = hash;
    memcpy(x->chars, y, length * sizeof(uint8_t));
    return 0;
}

extern int8_t cmp_chars_string(String *x, uint8_t *y) {
    size_t i = 0;
    for (; i < x->len; ++i) {
        if (y[i] == '\0') {
            return -1;
        }
        if (x->chars[i] > y[i]) {
            return 1;
        }
        if (x->chars[i] < y[i]) {
            return -1;
        }
    }
    if (y[i] != '\0') {
        return -1;
    }
    return 0;
}

extern void cat_out_string(uint8_t *x, String *y) {
    strncat(x, y->chars, y->len);
}

extern void cpy_out_string(uint8_t *x, String *y) {
    strncpy(x, y->chars, y->len);
}

extern int8_t catn_out_string(uint8_t *x, String *y, size_t begin, size_t quan) {
    if (begin > y->len) {
        return 1;
    } 
    if (begin + quan > y->len) {
        return 2;
    }
    strncat(x, y->chars + begin, quan);
    return 0;
}

extern int8_t cpyn_out_string(uint8_t *x, String *y, size_t begin, size_t quan) {
    if (begin > y->len) {
        return 1;
    } 
    if (begin + quan > y->len) {
        return 2;
    }
    strncpy(x, y->chars + begin, quan);
}

extern void cat_string(String *x, String *y) {
    size_t new_len = x->len + y->len;
    if (new_len >= x->cap) {
        _realloc_string(x, new_len);
    }
    for (size_t i = 0, j = x->len; i < y->len; ++i, ++j) {
        x->hash = y->chars[i] + CONST_HASH * x->hash;
        x->chars[j] = y->chars[i];
    }
    x->len = new_len;
}

extern void cpy_string(String *x, String *y) {
    if (y->len >= x->cap) {
        _realloc_string(x, y->len);
    }
    x->len = y->len;
    x->hash = y->hash;
    memcpy(x->chars, y->chars, x->len * sizeof(uint8_t));
}

extern int8_t catn_string(String *x, String *y, size_t begin, size_t quan) {
    if (begin > y->len) {
        return 1;
    }
    size_t length = begin + quan;
    if (length > y->len) {
        return 2;
    }
    size_t new_len = x->len + quan;
    if (new_len >= x->cap) {
        _realloc_string(x, new_len);
    }
    for (size_t i = begin, j = x->len; i < length; ++i, ++j) {
        x->hash = y->chars[i] + CONST_HASH * x->hash;
        x->chars[j] = y->chars[i];
    }
    x->len = new_len;
    return 0;
}

extern int8_t cpyn_string(String *x, String *y, size_t begin, size_t quan) {
    if (begin > y->len) {
        return 1;
    }
    size_t length = begin + quan;
    if (length > y->len) {
        return 2;
    }
    if (quan >= x->cap) {
        _realloc_string(x, quan);
    }
    uint32_t hash = 0;
    for (size_t i = begin, j = 0; i < length; ++i, ++j) {
        hash = y->chars[i] + CONST_HASH * hash;
        x->chars[j] = y->chars[i];
    }
    x->hash = hash;
    x->len = quan;
    return 0;
}

extern _Bool eq_string(String *x, String *y) {
    if (x->len != y->len) {
        return 0;
    }
    if (x->hash != y->hash) {
        return 0;
    }
    for (size_t i = 0; i < x->len; ++i) {
        if (x->chars[i] != y->chars[i]) {
            return 0;
        }
    }
    return 1;
}

extern int8_t cmp_string(String *x, String *y) {
    if (x->len > y->len) {
        return 2;
    } else if (x->len < y->len) {
        return -2;
    }
    for (size_t i = 0; i < x->len; ++i) {
        if (x->chars[i] > y->chars[i]) {
            return 1;
        }
        if (x->chars[i] < y->chars[i]) {
            return -1;
        }
    }
    return 0;
}

extern int8_t cmp_chars(uint8_t *x, uint8_t *y) {
    int cond = strcmp(x, y);
    if (cond > 0) {
        return 1;
    } else if (cond < 0) {
        return -1;
    }
    return 0;
}

extern size_t sizeof_string(void) {
    return sizeof(String);
}

extern size_t len_string(String *string) {
    return string->len;
}

extern size_t cap_string(String *string) {
    return string->cap;
}

extern size_t hash_string(String *string) {
    return string->hash;
}

extern uint8_t get_string(String *string, size_t index) {
    if (index >= string->len) {
        fprintf(stderr, "%s\n", "index >= len");
        return 0;
    }
    return string->chars[index];
}

extern void print_string(String *string) {
    putchar('"');
    for (size_t i = 0; i < string->len; ++i) {
        putchar(string->chars[i]);
    }
    putchar('"');
}

extern void println_string(String *string) {
    print_string(string);
    putchar('\n');
}

extern void free_string(String *string) {
    free(string->chars);
    free(string);
}

static void _realloc_string(String *string, size_t length) {
    string->cap = length << 1;
    string->chars = (uint8_t*)realloc(string->chars, string->cap * sizeof(uint8_t));
}

static void _str_hash_len(uint8_t *str, uint32_t *hash, size_t *index) {
    *hash = 0;
    *index = 0;
    for (; str[*index]; ++*index) {
        *hash = str[*index] + CONST_HASH * *hash;
    }
}
