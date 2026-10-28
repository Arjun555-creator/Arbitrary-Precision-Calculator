
#include "apc.h"
#include <string.h>

static void remove_leading_zeros(int *num, int *len)
{
    int i = 0;

    while (i < *len - 1 && num[i] == 0)
        i++;

    if (i > 0)
    {
        memmove(num, num + i, (*len - i) * sizeof(int));
        *len -= i;
    }
}

static int compare_numbers(int *a, int la, int *b, int lb)
{
    if (la > lb)
        return 1;
    if (la < lb)
        return -1;

    for (int i = 0; i < la; i++)
    {
        if (a[i] > b[i])
            return 1;
        if (a[i] < b[i])
            return -1;
    }

    return 0;
}

static void subtract_numbers(int *a, int *la, int *b, int lb)
{
    int i = *la - 1;
    int j = lb - 1;
    int borrow = 0;

    while (i >= 0)
    {
        int value = a[i] - borrow - (j >= 0 ? b[j] : 0);

        if (value < 0)
        {
            value += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        a[i] = value;
        i--;
        j--;
    }

    remove_leading_zeros(a, la);
}

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    if (*head2 == NULL || ((*head2)->data == 0 && *head2 == *tail2))
    {
        printf("Error: Division by zero\n");
        return FAILURE;
    }

    int la = 0, lb = 0;
    Dlist *temp;

    for (temp = *head1; temp != NULL; temp = temp->next)
        la++;

    for (temp = *head2; temp != NULL; temp = temp->next)
        lb++;

    int *a = malloc((la + decimal2 + 12) * sizeof(int));
    int *b = malloc((lb + decimal1 + 2) * sizeof(int));
    int *rem = malloc((la + decimal2 + 15) * sizeof(int));
    int *quot = malloc((la + decimal2 + 12) * sizeof(int));

    if (a == NULL || b == NULL || rem == NULL || quot == NULL)
    {
        free(a);
        free(b);
        free(rem);
        free(quot);
        return FAILURE;
    }

    int i = 0;
    for (temp = *head1; temp != NULL; temp = temp->next)
        a[i++] = temp->data;

    i = 0;
    for (temp = *head2; temp != NULL; temp = temp->next)
        b[i++] = temp->data;

    int alen = la;
    int blen = lb;

    remove_leading_zeros(a, &alen);
    remove_leading_zeros(b, &blen);

    if (alen == 1 && a[0] == 0)
    {
        insert_at_last(headR, tailR, 0);
        result_decimal = 0;
        result_sign = 1;
        free(a);
        free(b);
        free(rem);
        free(quot);
        return SUCCESS;
    }

    if (decimal2 > decimal1)
    {
        int zeros = decimal2 - decimal1;
        for (i = 0; i < zeros; i++)
            a[alen++] = 0;
    }
    else if (decimal1 > decimal2)
    {
        int zeros = decimal1 - decimal2;
        for (i = 0; i < zeros; i++)
            b[blen++] = 0;
    }

    for (i = 0; i < 10; i++)
        a[alen++] = 0;

    int rlen = 1;
    rem[0] = 0;
    int qlen = 0;

    for (i = 0; i < alen; i++)
    {
        if (rlen == 1 && rem[0] == 0)
            rem[0] = a[i];
        else
            rem[rlen++] = a[i];

        remove_leading_zeros(rem, &rlen);

        int qdigit = 0;

        while (compare_numbers(rem, rlen, b, blen) >= 0)
        {
            subtract_numbers(rem, &rlen, b, blen);
            qdigit++;
        }

        quot[qlen++] = qdigit;
    }

    remove_leading_zeros(quot, &qlen);

    for (i = 0; i < qlen; i++)
    {
        if (insert_at_last(headR, tailR, quot[i]) == FAILURE)
        {
            free(a);
            free(b);
            free(rem);
            free(quot);
            return FAILURE;
        }
    }

    result_decimal = 10;
    result_sign = 1;

    free(a);
    free(b);
    free(rem);
    free(quot);

    return SUCCESS;
}

