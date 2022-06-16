// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"

#define offset 97

// Represents a node in a hash table
int wcount = 0;
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *ctmp;
    char w = word[0];
    w = tolower(w);
    char word_lower[LENGTH + 1];
    for(int i = 0, k = strlen(word); i<=k; i++ )
        {
            word_lower[i] = tolower(word[i]);
        }

    ctmp = table[hash(word_lower)];
    // printf("%p", ctmp); //d
    // printf("word_lower: %s\n", word_lower); //d
       while(ctmp != NULL)
       {
        //    printf("LW: %s\n", ctmp -> word); //d
           if(strcmp(word_lower,ctmp->word) == 0)
           {
                return true;
           }
           ctmp = ctmp->next;
       }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return (word[0]-offset);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }
    //  char *w = malloc((LENGTH + 1) * sizeof(char));
    char w[LENGTH + 1]; /// Damn, no need to malloc, solve later

    while(fscanf(f,"%s",w) != EOF)
    {
        // creates space for new node
        node *ltmp = malloc(sizeof(node));
        // printf("Loading something\n"); //d
        if(ltmp == NULL)
        {
            fprintf(stderr, "Unable to allocate memory for temporary node.");
            return false;
        }
        // printf("Word: %s\n", w); //d
        strcpy(ltmp->word,w);
        ltmp->next = table[hash(w)];
        table[hash(w)] = ltmp;
        wcount ++;
    }
    fclose(f);


    // printf("Passed successfuly"); //d
    return true;


}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Releases memory
    for(int i = 0; i < N; i++)
    {
        node *utmp = table[i];
        while(utmp != NULL)
        {
            node *utmp2 = utmp;
            utmp = utmp->next;
            free(utmp2);
        }
    }
    return true;
}
