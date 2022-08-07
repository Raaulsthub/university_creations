#include "dictionary.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
    CODIGO AVL CONSTRUIDO APARTIR DO TAD ENCONTRADO EM:
    http://www.each.usp.br/digiampietri/ACH2023/javaec/ArvoreAVL/arvoreAVL.c
*/

/* STRUCTS */

typedef struct word {
    char* word;
    Word* left;
    Word* right;
    int bal;
}Word;

typedef struct dictionary {
    Word* root;
}Dictionary;

/* STATIC */

static void freeDictionaryAux (Word* word) {
    if (word == NULL) {
        return;
    }
    freeDictionaryAux(word->left);
    freeDictionaryAux(word->right);
    free(word->word);
    free(word);
}

static Word* createWord (char* c) {
    if (c == NULL) return NULL;
    Word* newWord = (Word*) malloc (sizeof(Word));
    newWord->left = NULL;
    newWord->right = NULL;
    newWord->word = (char*) malloc (strlen(c) + 1);
    strcpy(newWord->word, c);
    newWord->bal = 0;
    return newWord;
}

static Word* rotacaoL (Word* p) {
    Word* u;
    Word* v;
    u = p->left;
    if (u->bal == -1) {
        p->left = u->right;
        u->right = p;
        p->bal = 0;
        u->bal = 0;
        return u;
    } else if (u->bal == 1) {
        v = u->right;
        u->right = v->left;
        v->left = u;
        p->left = v->right;
        v->right = p;
        if (v->bal == -1) p->bal = 1;
        else p->bal = 0;
        if (v->bal == 1) u->bal = -1;
        else u->bal = 0;
        v->bal = 0;
        return v;
    } else {
        p->left = u->right;
        u->right = p;
        u->bal = 1;
        return u;
    }
}

static Word* rotacaoR (Word* p) {
    Word* u;
    Word* v;
    u = p->right;
    if(u->bal == 1) {   
        p->right = u->left;
        u->left = p;
        p->bal = 0;
        u->bal = 0;
        return u;
    } else if (u->bal == -1) {  
        v = u->left;
        u->left = v->right;
        v->right = u;
        p->right = v->left;
        v->left = p;
        if(v->bal == 1) p->bal = -1;
        else p->bal = 0;
        if(v->bal == -1) u->bal = 1;
        else u->bal = 0;
        v->bal = 0;
        return v;
    }else {   
        p->right = u->left;
        u->left = p;
        u->bal = -1;
        return u;
    }
}

static Word* addWordAVL (Word** pp, char* ch, bool* alterou) {
    Word* p = *pp;
    static Word* ret = NULL;
    if (!p) {
        *pp = createWord(ch);
        ret = *pp;
        *alterou = true;
    } else {
        if (strcmp(ch, p->word) == 0){
            *alterou = false;
            ret = NULL;
        }
        else if (strcmp(ch, p->word) <= 0) {
            addWordAVL(&(p->left), ch, alterou);
            if (*alterou) {
                switch (p->bal) {
                    case 1:
                        p->bal = 0;
                        *alterou = false;
                        break;
                    case 2:
                        p->bal = -1;
                        break;
                    case -1:
                        *pp = rotacaoL(p);
                        *alterou = false;
                        break;
                }
            }
        } else {
            addWordAVL(&(p->right), ch, alterou);
            if (*alterou)
                switch (p->bal) {
                    case -1:
                        p->bal = 0;
                        *alterou = false;
                        break;
                    case 0:
                        p->bal = 1;
                        break;
                    case 1:
                        *pp = rotacaoR(p);
                        *alterou = false;
                        break;
            }
        }
    }
    return ret;
}

static Word* findExactMatchAux (Word* root, char* word) {
    if (root == NULL) return NULL;
    if (strcmp(word, root->word) == 0) return root;
    if (strcmp(word, root->word) < 0) {
        return findExactMatchAux(root->left, word);
    }
    return findExactMatchAux(root->right, word);
}

static int similarities(char* w1, char* w2) {
    int sim = 0;
    for (int i = 0; i < strlen(w1); i++) {
        if (w1[i] == w2[i]) {
            sim++;
        }
    }
    return sim;
}

static void findBestMatchAux (Word* root, char* word, Word** bestMatch, int* equalLetters) {
    if (root == NULL) return;
    if (strlen(root->word) == strlen(word)) {
        if (*bestMatch == NULL) {
            *bestMatch = root;
            *equalLetters = similarities(root->word, word);
        }
        else {
            int sim = similarities (root->word, word);
            if (sim > *equalLetters) {
                *equalLetters = sim;
                *bestMatch = root;
            } else if (sim == *equalLetters) {
                if (strcmp(root->word, (*bestMatch)->word) < 0) {
                    *bestMatch = root;
                } 
            }
        }
    }
    findBestMatchAux (root->left, word, bestMatch, equalLetters);
    findBestMatchAux (root->right, word, bestMatch, equalLetters);
}

static int hasPrefix(char* word, char* prefix) {
    for(int i = 0; i < strlen(prefix) ; i++) {
        if(word[i] != prefix[i]) {
            return -1;
        }
    }
    return 1;
}

static void findPrefixSize(Word* root, char* prefix, int* size) {
    if (root == NULL) return;
    findPrefixSize(root->left, prefix, size);
    if(hasPrefix(root->word, prefix) > 0) {
        (*size)++;
    }
    findPrefixSize (root->right, prefix, size);
}

static void buildPrefixVector (Word* root, char* prefix, int* index, Word** v) {
    if (root == NULL) return;
    buildPrefixVector(root->left, prefix, index, v);
    if(hasPrefix(root->word, prefix) > 0) {
        Word* w = (Word*) malloc (sizeof(Word));
        w->left = NULL;
        w->right = NULL;
        w->word = (char*) malloc (strlen(root->word) + 1);
        strcpy(w->word, root->word);
        v[*index] = w;
        (*index)++;
    }
    buildPrefixVector(root->right, prefix, index, v);
}

/* FUNCTIONS */

Dictionary* createDictionary () {
    Dictionary* dic = (Dictionary*) malloc (sizeof(Dictionary));
    dic->root = NULL;
    return dic;
}

void freeDictionary (Dictionary* dic) {
    freeDictionaryAux(dic->root);
    free(dic);
}

Word* addWord (Dictionary* dic, char* word) {
    bool alterou = false;
    return addWordAVL(&(dic->root), word, &alterou);
}

char* getWord (Word* word) {
    if (word != NULL) {
        char* w = (char*) malloc (strlen(word->word) + 1);
        strcpy(w, word->word);
        return w;
    } else {
        char* s = (char*) malloc (sizeof(char));
        s[0] = '\0';
        return s;
    }
}

Word* findExactMatch (Dictionary* dic, char* word) {
    return findExactMatchAux(dic->root, word);
}

Word* findBestMatch (Dictionary* dic, char* word) {
    int equalLetters = 0;
    Word* bestMatch = NULL;
    findBestMatchAux (dic->root, word, &bestMatch, &equalLetters);
    return bestMatch;
}

Word** findPrefix (Dictionary* dic, char* prefix) {
    int size = 0;
    findPrefixSize (dic->root, prefix, &size);
    Word** v = (Word**) malloc ((size + 1) * sizeof(Word*));
    int index = 0;
    buildPrefixVector (dic->root, prefix, &index, v);
    v[index] = NULL;
    return v;
}
