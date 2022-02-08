#include "list.h"

static void init_node(node *np) {
    np->next = np;
    np->prev = np;
    np->value = 0;
}

static node *new_node() {
    node *ret = (node *)malloc(sizeof(node));
    init_node(ret);
    return ret;
}

static void set_node(node *np, node *next_p, node *prev_p, unsigned value) {
    np->next = next_p;
    np->prev = prev_p;
    np->value = value;
}

static void init_list_op(OP *);

static size_t size_of_list(list *lp) { return lp->size; }

static int empty_list(list *lp) { return size_of_list(lp) == 0; }

static unsigned pop_back_list(list *lp) {
    if (!empty_list(lp)) {
        unsigned ret = lp->nil.prev->value;
        node *new_back = lp->nil.prev->prev;
        node *to_delete = lp->nil.prev;
        set_node(&(lp->nil), lp->nil.next, new_back, lp->nil.value);
        set_node(new_back, &(lp->nil), new_back->prev, new_back->value);
        free(to_delete);
        lp->size--;
        return ret;
    } else {
        exit(126);
    }
}

static void clear_list(list *lp) {
    while (!empty_list(lp)) {
        pop_back_list(lp);
    }
}

static void init_list(list *lp) {
    static OP op;
    init_list_op(&op);
    init_node(&(lp->nil));
    lp->size = 0;
    lp->op = &op;
}

list *new_list() {
    list *ret = malloc(sizeof(list));
    init_list(ret);
    return ret;
}

static size_t append_list(list *lp, unsigned value) {
    node *np = new_node();
    node *old_back = lp->nil.prev;
    set_node(np, &(lp->nil), (lp->nil).prev, value);
    set_node(old_back, np, old_back->prev, old_back->value);
    set_node(&(lp->nil), lp->nil.next, np, lp->nil.value);
    lp->size++;
    return size_of_list(lp);
}

static size_t prepend_list(list *lp, unsigned value) {
    node *np = new_node();
    node *old_front = lp->nil.next;
    set_node(np, (lp->nil).next, &(lp->nil), value);
    set_node(old_front, old_front->next, np, old_front->value);
    set_node(&(lp->nil), np, lp->nil.prev, lp->nil.value);
    lp->size++;
    return size_of_list(lp);
}

static unsigned pop_front_list(list *lp) {
    if (!empty_list(lp)) {
        unsigned ret = lp->nil.next->value;
        node *new_front = lp->nil.next->next;
        node *to_delete = lp->nil.next;
        set_node(&(lp->nil), new_front, lp->nil.prev, lp->nil.value);
        set_node(new_front, new_front->next, &(lp->nil), new_front->value);
        free(to_delete);
        lp->size--;
        return ret;
    } else {
        exit(126);
    }
}

static void destruct_list(list *lp) {
    clear_list(lp);
    free(lp);
}

static list *copy_list(list *lp) {
    list *ret = new_list();
    node *traverse = &(lp->nil);
    while (size_of_list(ret) < size_of_list(lp)) {
        traverse = traverse->prev;
        prepend_list(ret, traverse->value);
    }
    return ret;
}

static void init_list_op(OP *p) {
    p->append = append_list;
    p->prepend = prepend_list;
    p->pop_back = pop_back_list;
    p->pop_front = pop_front_list;
    p->copy = copy_list;
    p->is_empty = empty_list;
    p->size_of = size_of_list;
    p->clear = clear_list;
    p->destruct = destruct_list;
}
