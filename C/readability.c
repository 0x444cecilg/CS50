#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    //Prompt user for text
    int letters = 0;
    int words = 1;
    int sentences = 0;
    string text = get_string("Text: ");
    
    //When a letter entered count letter
    
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        
        }
    
        //Count the words
        if (text[i] == ' ')
        {
            words++;
        }
       
        
        //Count the sentences
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
        
    }
    // letters / 100 words & sentences / 100 words
    
    float l = ((float) letters / words) * 100;
    float s = ((float) sentences / words) * 100;
    
    
    float index = round(0.0588 * l - 0.296 * s - 15.8);
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
   
    }
    else 
    {
        printf("Grade %i\n", (int) index);
    }
    
}