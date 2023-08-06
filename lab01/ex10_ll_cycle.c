#include <stddef.h>
#include "ex10_ll_cycle.h"

int ll_has_cycle(node *head) {
    /* TODO: Implement ll_has_cycle */
    node* pointer1=head;
    node* pointer2=head;
    while (pointer1!=NULL && (*pointer1).next!=NULL){
        pointer1=(*(*pointer1).next).next;
        pointer2=(*pointer2).next;
        if (pointer1==pointer2){
            return 1;
        }
    }
    return 0;
}
