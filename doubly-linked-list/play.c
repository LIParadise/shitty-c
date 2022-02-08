#include "list.h"
#include <ctype.h>
#include <stdio.h>

void dummy_dump_and_clear(list* lp){
    list *copied = lp->op->copy(lp);
    printf("In order:\n");
    while(!lp->op->is_empty(lp)){
        char delimiter = (lp->op->size_of(lp)== 1)? '\n' : ' ';
        printf("%u%c", lp->op->pop_front(lp), delimiter);
    }
    printf("Reverse order:\n");
    while(!copied->op->is_empty(copied)){
        char delimiter = (copied->op->size_of(copied) == 1)? '\n' : ' ';
        printf("%u%c", lp->op->pop_back(copied), delimiter);
    }

    copied->op->destruct(copied);
    lp->op->clear(lp);
}

int main() {
    unsigned value;
    char action;
    list *my_list = new_list();
    while (scanf(" %c %u", &action, &value) == 2) {
        action = tolower(action);
        switch (action) {
            case 'p':
                my_list->op->prepend(my_list, value);
                break;
            case 'a':
                my_list->op->append(my_list, value);
                break;
            default:
                goto done_collecting_input;
        };
    }

done_collecting_input:;

    dummy_dump_and_clear(my_list);
    for( unsigned u = 0; u < 10; ++u ){
        if( u >= 5 ){
            my_list->op->append(my_list, u);
        }else{
            my_list->op->prepend(my_list, u);
        }
    }
    dummy_dump_and_clear(my_list);

    my_list->op->destruct(my_list);

    return 0;
}
