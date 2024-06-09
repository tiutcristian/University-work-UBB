/*
* Problem statement:
    It is given a number in base 2 represented on 32 bits. Write to the console the number in base 16. (use the quick conversion)
*/

#include <stdio.h>

// the function declared in module.asm
void bin_to_hex(int bin_len, char bin_nr[], char hex_nr[]);

// length of a string
int len(char nr[])
{
    int i = 0;
    while (nr[i] != '\0' && i < 32)
        i++;
    return i;
}

void rev_str(char nr[])
{
    int n = len(nr);
    for (int i = 0; i < n / 2; i++)
    {
        char aux = nr[i];
        nr[i] = nr[n - i - 1];
        nr[n - i - 1] = aux;
    }
}

void print_string(char nr[])
{
    int n = len(nr);
    for (int i = 0; i < n; i++)
    {
        int curr_digit = nr[i] - '0';
        if (curr_digit < 10)
            printf("%d", curr_digit);
        else
            printf("%c", curr_digit - 10 + 'A');
    }
    printf("\n");
}

int main()
{    
    char nr_base_2[32];
    char nr_base_16[8];

    scanf("%s", nr_base_2);
    rev_str(nr_base_2);
    bin_to_hex(len(nr_base_2), nr_base_2, nr_base_16);
    rev_str(nr_base_16);
    print_string(nr_base_16);

    return 0;
}
