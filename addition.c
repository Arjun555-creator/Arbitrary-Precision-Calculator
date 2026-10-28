#include "apc.h"

int addition(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2,
             Dlist **headR)
{
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;
    int carry = 0;

    while (t1 != NULL || t2 != NULL || carry)
    {
        int sum = carry;

        if (t1 != NULL)
        {
            sum += t1->data;
            t1 = t1->prev;
        }

        if (t2 != NULL)
        {
            sum += t2->data;
            t2 = t2->prev;
        }

        carry = sum / 10;

        Dlist *new = malloc(sizeof(Dlist));
        if (new == NULL)
            return FAILURE;

        new->data = sum % 10;
        new->prev = NULL;
        new->next = *headR;

        if (*headR != NULL)
            (*headR)->prev = new;

        *headR = new;
    }

    return SUCCESS;
}
