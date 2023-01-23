from cs50 import get_float

change = float(0)
while change <= 0:
    
    change = get_float("Change owed? ")
    
cents = int(change * 100)
    
# Take out quarters
coins = int(0)
quarters = int(cents / 25)
coins = coins + quarters 
cents = cents - (25 * quarters)
  
# Take out dimes
dimes = int(cents / 10)
coins = coins + dimes
cents = cents - (10 * dimes)
      
# Take out nickels
nickels = int(cents / 5)
coins = coins + nickels
cents = cents - (5 * nickels)
   
# Add up coins
coins = coins + cents
    
    
print(f"You have {coins} coins.")

    
  