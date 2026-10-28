#include "apc.h"
int result_sign = 1;
int decimal1 = 0;
int decimal2 = 0;
int result_decimal = 0;
int main(int argc, char *argv[])
{
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;
    if (argc != 4)
    {
        printf("Usage: %s operand1 operator operand2\n", argv[0]);
        return FAILURE;
    }

    if (validate_number(argv[1]) == FAILURE ||
        validate_number(argv[3]) == FAILURE)
    {
        printf("Invalid operand\n");
        return FAILURE;
    }
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (argv[1][i] == '.')
            continue;

        if (insert_at_last(&head1, &tail1, argv[1][i] - '0') == FAILURE)
            return FAILURE;
    }
    for (int i = 0; argv[3][i] != '\0'; i++)
    {
        if (argv[3][i] == '.')
            continue;

        if (insert_at_last(&head2, &tail2, argv[3][i] - '0') == FAILURE)
            return FAILURE;
    }
    while (head1 != tail1 && head1->data == 0)
    {
        Dlist *temp = head1;
        head1 = head1->next;
        head1->prev = NULL;
        free(temp);
    }

    while (head2 != tail2 && head2->data == 0)
    {
        Dlist *temp = head2;
        head2 = head2->next;
        head2->prev = NULL;
        free(temp);
    }
    if (argv[2][1] != '\0' || (argv[2][0] != '+' && argv[2][0] != '-' && argv[2][0] != 'x' && argv[2][0] != 'X' && argv[2][0] != '*' && argv[2][0] != '/'))
    {
        printf("Invalid operator\n");
        return FAILURE;
    }
    char oper = argv[2][0];
    char *dot1 = NULL;
    char *dot2 = NULL;
    for (int i = 0; argv[1][i] != '\0'; i++)
        if (argv[1][i] == '.')
            dot1 = &argv[1][i];
    for (int i = 0; argv[3][i] != '\0'; i++)
        if (argv[3][i] == '.')
            dot2 = &argv[3][i];
    decimal1 = (dot1 != NULL) ? (int)(&argv[1][0] + strlen(argv[1]) - dot1 - 1) : 0;
    decimal2 = (dot2 != NULL) ? (int)(&argv[3][0] + strlen(argv[3]) - dot2 - 1) : 0;
    result_sign = 1;
    switch (oper)
    {
        case '+':
        case '-':
        {
            int scale = (decimal1 > decimal2) ?
                         decimal1 : decimal2;
            while (decimal1 < scale)
            {
                if (insert_at_last(&head1, &tail1, 0) == FAILURE)
                    return FAILURE;
                decimal1++;
            }
            while (decimal2 < scale)
            {
                if (insert_at_last(&head2, &tail2, 0) == FAILURE)
                    return FAILURE;
                decimal2++;
            }
            result_decimal = scale;
            if (oper == '+')
                addition(&head1, &tail1, &head2, &tail2, &headR);
            else
                subtraction(&head1, &tail1, &head2, &tail2, &headR);

            break;
        }

        case 'x':
        case 'X':
        case '*':
            result_decimal = decimal1 + decimal2;

            multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            break;
        case '/':
            if (head2->data == 0 && head2 == tail2)
            {
                printf("Error: Division by zero\n");
                return FAILURE;
            }
            result_decimal = 10;
           division(&head1, &tail1, &head2, &tail2, &headR, &tailR);
           break;
    }
    if (result_sign < 0)
        printf("-");

    print_list(headR);

    return SUCCESS;
}

int insert_at_last(Dlist **head, Dlist **tail, int digit)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
        return FAILURE;
    new->data = digit;
    new->prev = *tail;
    new->next = NULL;
    if (*head == NULL)
        *head = new;
    else
        (*tail)->next = new;

    *tail = new;
    return SUCCESS;
}
int validate_number(char *str)
{
    int i = 0;
    int digits = 0;
    int dots = 0;
    if (str[0] == '\0')
        return FAILURE;
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
            digits++;
        else if (str[i] == '.')
            dots++;
        else
            return FAILURE;
        if (dots > 1)
            return FAILURE;
        i++;
    }
    return (digits > 0) ? SUCCESS : FAILURE;
}
void print_list(Dlist *head)
{
    int count = 0;
    Dlist *temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    if (head == NULL)
    {
        printf("0\n");
        return;
    }
    if (result_decimal == 0)
    {
        while (head != NULL)
        {
            printf("%d", head->data);
            head = head->next;
        }

        printf("\n");
        return;
    }
    if (count <= result_decimal)
    {
        printf("0.");
        for (int i = 0; i < result_decimal - count; i++)
            printf("0");
        while (head != NULL)
        {
            printf("%d", head->data);
            head = head->next;
        }
    }
    else
    {
        int integer_digits = count - result_decimal;
        int pos = 0;
        while (head != NULL)
        {
            if (pos == integer_digits)
                printf(".");

            printf("%d", head->data);
            head = head->next;
            pos++;
        }
    }
    printf("\n");
}

