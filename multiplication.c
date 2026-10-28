
#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int n = 0, m = 0;
    Dlist *p = *head1;
    while (p != NULL)
    {
        n++;
        p = p->next;
    }

    p = *head2;
    while (p != NULL)
    {
        m++;
        p = p->next;
    }
    int *a = malloc(n * sizeof(int));
    int *b = malloc(m * sizeof(int));
    int *res = calloc(n + m, sizeof(int));
    if (a == NULL || b == NULL || res == NULL)
    {
        free(a);
        free(b);
        free(res);
        return FAILURE;
    }
    p = *head1;
    for (int i = 0; i < n; i++)
    {
        a[i] = p->data;
        p = p->next;
    }
    p = *head2;
    for (int i = 0; i < m; i++)
    {
        b[i] = p->data;
        p = p->next;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        int carry = 0;

        for (int j = m - 1; j >= 0; j--)
        {
            int pos = i + j + 1;
            int product = a[i] * b[j] + res[pos] + carry;

            res[pos] = product % 10;
            carry = product / 10;
        }

        res[i] += carry;
    }

    int start = 0;
    while (start < n + m - 1 && res[start] == 0)
        start++;

    for (int i = start; i < n + m; i++)
    {
        Dlist *new = malloc(sizeof(Dlist));

        if (new == NULL)
        {
            free(a);
            free(b);
            free(res);
            return FAILURE;
        }
        new->data = res[i];
        new->prev = *tailR;
        new->next = NULL;

        if (*headR == NULL)
            *headR = new;
        else
            (*tailR)->next = new;

        *tailR = new;
    }

    free(a);
    free(b);
    free(res);

    return SUCCESS;
}

