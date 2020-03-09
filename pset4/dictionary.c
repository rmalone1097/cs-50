// Implements a dictionary's functionality using trie structure

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;
unsigned int wCounter = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    int wLength = strlen(word);
    node *cursor = root;
    int cindex;
    char letter;

    for (int i = 0; i < wLength; i++)
    //for (int i = 0; word[i] != '\0'; i++)
    {
        letter = tolower(word[i]);

        //children index is the letter - 97 since 97 is the 'a' ascii value
        if (letter == '\'')
        //if (word[i] == '\'')
        {
            //cindex = N - 1;
            cindex = 26;
        }
        else
        {
            //cindex = tolower(word[i]) - 97;
            cindex = letter - 97;
        }

        if (cursor -> children[cindex] == NULL)
        {
            return false;
        }
        cursor = cursor -> children[cindex];
    }
    if (cursor -> is_word)
    {
        return true;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    char letter;
    int cindex;
    node *cursor;
    int lCounter = 0;

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO

        cursor = root;
        int wlength = strlen(word);

        for (int i = 0; i < wlength; i++)
        //for (int i = 0; word[i] != '\0'; i++)
        {
            lCounter++;
            letter = word[i];

            //children index is the letter - 97 since 97 is the 'a' ascii value
            if (letter == '\'')
            {
                cindex = N - 1;
            }
            else
            {
                cindex = word[i] - 97;
            }

            if (cursor -> children[cindex] == NULL)
            {

                //cursor -> children[cindex] = malloc(sizeof(node));
                node *newnode = malloc(sizeof(node));
                if (newnode == NULL)
                {
                    return false;
                }
                for (int j = 0; j < N; j++)
                {
                    newnode->children[j] = NULL;
                }

                cursor -> children[cindex] = newnode;
            }

            cursor = cursor -> children[cindex];
        }
        cursor -> is_word = true;
        wCounter++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wCounter;
}



void clear (node *cursor)
{
    for (int i = 0; i < N; i++)
    {
        if (cursor -> children[i] != NULL)
        {
            clear(cursor -> children[i]);
        }
    }

    free(cursor);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO

    //node *cursor = root;
    clear(root);
    return true;
}
