#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Prompt user for key & check for positive integer
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (!isdigit(argv[1][i]) || argc != 2)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else
        {
            int x = atoi(argv[1]);
        }
    }
    //Cycle through characters and shift by +key (x)
    string p = get_string("plaintext: ");

    printf("ciphertext: ");
    int x = atoi(argv[1]);
    for (int i = 0, len = strlen(p); i < len; i++)
    {
        //if isupper true shift +k places and remain uppercase
   
        if (isupper(p[i]))
        {
            printf("%c", (((p[i] - 'A') + x) % 26) + 'A');
        }
        //if islower true shift +k places and remain lowercase
        if (islower(p[i]))
        {
            printf("%c", (((p[i] - 'a') + x) % 26) + 'a');
        }
        //if ispunct true just print the corresponding punctuation
        else if (ispunct(p[i]))
        {
            printf("%c", p[i]);
        }
        
        //if isspace is true print the whitespace
        else if (isspace(p[i]))
        {
            printf(" ");
        }
    }
    printf("\n");


}
