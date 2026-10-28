#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    Dlist *p1 = *head1;
    Dlist *p2 = *head2;
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;
    int len1 = 0, len2 = 0;
    int cmp = 0, borrow = 0;

    while (p1 != NULL)
    {
        len1++;
        p1 = p1->next;
    }

    while (p2 != NULL)
    {
        len2++;
        p2 = p2->next;
    }

    if (len1 > len2)
        cmp = 1;
    else if (len1 < len2)
        cmp = -1;
    else
    {
        p1 = *head1;
        p2 = *head2;

        while (p1 != NULL)
        {
            if (p1->data > p2->data)
            {
                cmp = 1;
                break;
            }

            if (p1->data < p2->data)
            {
                cmp = -1;
                break;
            }

            p1 = p1->next;
            p2 = p2->next;
        }
    }

    result_sign = (cmp < 0) ? -1 : 1;

    if (cmp == 0)
    {
        Dlist *new = malloc(sizeof(Dlist));

        if (new == NULL)
            return FAILURE;

        new->data = 0;
        new->prev = NULL;
        new->next = NULL;
        *headR = new;

        return SUCCESS;
    }

    if (cmp < 0)
    {
        t1 = *tail2;
        t2 = *tail1;
    }

    while (t1 != NULL)
    {
        int d1 = t1->data - borrow;
        int d2 = (t2 != NULL) ? t2->data : 0;

        if (d1 < d2)
        {
            d1 += 10;
            borrow = 1;
        }
        else
            borrow = 0;

        Dlist *new = malloc(sizeof(Dlist));

        if (new == NULL)
            return FAILURE;

        new->data = d1 - d2;
        new->prev = NULL;
        new->next = *headR;

        if (*headR != NULL)
            (*headR)->prev = new;

        *headR = new;

        t1 = t1->prev;

        if (t2 != NULL)
            t2 = t2->prev;
    }

    while (*headR != NULL && (*headR)->data == 0 && (*headR)->next != NULL)
    {
        Dlist *temp = *headR;
        *headR = temp->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}
