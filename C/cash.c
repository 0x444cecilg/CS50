#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Get change owed
    float n = 0;
    while (n <= 0)
    {
        n = get_float("Change owed? ");
    }
    int cents = round(n * 100);
    
    // Take out quarters
    int coins = 0;
    int quarters = cents / 25;
    coins = coins + quarters; 
    cents = cents - (25 * quarters);
  
    
    // Take out dimes
    int dimes = cents / 10;
    coins = coins + dimes;
    cents = cents - (10 * dimes);
      
    // Take out nickels
    int nickels = cents / 5;
    coins = coins + nickels;
    cents = cents - (5 * nickels);
   
    // Add up coins
    coins = coins + cents;
    
    
    printf("You have %i coins.", coins);

    
    printf("\n");
}