// Implements a dictionary's functionality
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = (LENGTH + 1) * 1000;

// Hash table
node *table[N];
int wordsTotal = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash word and access linked list index
    int index = hash(word);
    node *cursor = table[index];
    // Traverse linked list searching for the word in dictionary
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;

    }
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // My hash fucntion source: http://www.cse.yorku.ca/~oz/hash.html 
    unsigned long hash = 5381;

    int c = *word;
   
    // Added tolower to make case insensetive 
    c = tolower(c);

    while (*word != 0)
    {
        hash = ((hash << 5) + hash) + c;
        c = *word++;
        c = tolower(c);
    }
    // Added % N to prevent exceeding space provided in the table
    return hash % N;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // Open the dictionary file for reading
    FILE *inptr = fopen(dictionary, "r");

    // check for null
    if (inptr == NULL)
    {
        return false;
    }
    // create a buffer
    char word[LENGTH + 1];

    // read strings from file one at a time
    while (fscanf(inptr, "%s", word) != EOF)
    {
        // create a new node for each string
        node *n = malloc(sizeof(node));
        //check for NULL
        if (n == NULL)
        {
            return false;
        }

        // copy string into node
        strcpy(n->word, word);
        n->next = NULL;

        // Hash word to obtain hash value
        int index = hash(word);

        // Insert node into hash table at specified location

        if (table[index] == NULL)
        {
            table[index] = n;
        }

        else
        {
            n->next = table[index];
            table[index] = n;
        }
        wordsTotal++;
    }
    // close file
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // returns the total amount of words checked
    if (wordsTotal != 0)
    {
        return wordsTotal;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Iterate through the linked lists in hash table freeing each list
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = table[i];
        node *tmp = head;

        //Free all nodes
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
            
        }

    }
    return true;
}
