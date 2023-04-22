#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Trie {
    int count;
    struct Trie *children[ALPHABET_SIZE];
};

void insert(struct Trie **ppTrie, char *word) {
    struct Trie *pTrie = *ppTrie;

    if (pTrie == NULL) {
        pTrie = (struct Trie*) malloc(sizeof(struct Trie));
        pTrie->count = 0;
      
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            pTrie->children[i] = NULL;
        }
        *ppTrie = pTrie;
    }

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
      
        if (pTrie->children[index] == NULL) {
            pTrie->children[index] = (struct Trie*) malloc(sizeof(struct Trie));
            pTrie->children[index]->count = 0;
          
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                pTrie->children[index]->children[j] = NULL;
            }
        }
        pTrie = pTrie->children[index];
    }
    pTrie->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            return 0;
        }
        pTrie = pTrie->children[index];
    }
    return pTrie->count;
}

struct Trie *deallocateTree(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (pTrie->children[i] != NULL) {
            deallocateTree(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie *trie = NULL;

     char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
   
    for (int i = 0; i < 5; i++) {
      insert(&trie, pWords[i]);
      printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    trie = deallocateTree(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}
