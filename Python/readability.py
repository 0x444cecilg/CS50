from cs50 import get_string


text = get_string("Text: ")

letters = 0
words = 1
sentences = 0
length = len(text)

    
# When a letter entered count letter
for i in range(length):
    if text[i].isalpha():
        letters += 1
        
    if text[i] == ' ':
        words += 1
        
    # Count the sentences
    if text[i] == '.' or text[i] == '?' or text[i] == '!':
        sentences += 1
        
# letters / 100 words & sentences / 100 words
    
l = (letters / words) * 100
s = (sentences / words) * 100
    
# Use formula to create index variable number to gauge grade level  
index = round(0.0588 * l - 0.296 * s - 15.8)

# if result less than 1 before grade 1 
if index < 1:
    print("Before Grade 1")

# if result greater than 1 after grade 16 
elif index > 16:
    print("Grade 16+")

# else print grade within range   
else: 
    print(f"Grade {index}")