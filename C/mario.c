#include <cs50.h>
#include <stdio.h>

int main(void)
{
   int n = 0;
    while (n < 1 || n > 8) 
    {
        n = get_int("Height: ");
    }
    
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++)
      {
          if (j < n - i - 1)
          {
             printf(" ");
          }
          else 
        { 
           printf("#");
        }
        
      }
       printf("\n");
   }
}
// j = n - (i + 1)
