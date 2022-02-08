#pragma once

#include <stddef.h>
#include <stdlib.h>

typedef struct node node;
typedef struct list list;
typedef struct OP OP;

struct node {
    node *next;
    node *prev;
    unsigned value;
};

struct OP {
    size_t (*append)(list *, unsigned);
    size_t (*prepend)(list *, unsigned);
    unsigned (*pop_back)(list *);
    unsigned (*pop_front)(list *);
    size_t (*size_of)(list *);
    int (*is_empty)(list *);
    list *(*copy)(list *);
    void (*clear)(list *);
    void (*destruct)(list *);
};

struct list {
    node nil;
    size_t size;
    OP *op;
};

list *new_list();
