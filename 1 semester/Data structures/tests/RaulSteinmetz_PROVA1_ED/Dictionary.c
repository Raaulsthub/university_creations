#include "Dictionary.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* STRUCTS */

typedef struct word {
    char* word;
    struct word* prox;
    struct word* ant;
}word;

typedef struct dictionary {
    Word* first;
}Dictionary;

/* STATIC FUNCTIONS */
static Word* searchForPushed (Dictionary* dic, Word* w) {
    Word* p = dic->first;
    while(p != NULL) {
        if(strcmp(w->word, p->word) < 0){
            return p;
        }
        p = p->prox;
    }
    return p;
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

static int lexicoGraphicalAnalysis(char* chalanger, char* contender, char* compared) {
    //position
    for (int i = 0; i < strlen(compared); i++) {
        if (chalanger[i] == compared[i] && contender[i] != compared[i]) {
            return 1;
        }
        if (chalanger[i] != compared[i] && contender[i] == compared[i]) {
            return -1;
        }
    }
    //alphabetical distance
    for (int i = 0; i < strlen(compared); i++) {
        if (chalanger[i] != compared[i]) {
            if ((chalanger[i] - compared[i]) * (chalanger[i] - compared[i]) < (contender[i] - compared[i]) * (contender[i] - compared[i])) {
                return 1;
            }
            else if ((chalanger[i] - compared[i]) * (chalanger[i] - compared[i]) > (contender[i] - compared[i]) * (contender[i] - compared[i])) {
                return -1;
            }
        }
    }
    return 0;
}

static int hasPrefix(char* word, char* prefix) {
    for(int i = 0; i < strlen(prefix) ; i++) {
        if(word[i] != prefix[i]) {
            return -1;
        }
    }
    return 1;
}

/* FUNCTIONS */

Dictionary* createDictionary () {
    Dictionary* dic = (Dictionary*) malloc (sizeof(Dictionary));
    dic->first = NULL;
    return dic;
}

void freeDictionary (Dictionary* dic) {
    Word* p;
    while (dic->first != NULL) {
        p = dic->first->prox;
        free(dic->first->word);
        free(dic->first);
        dic->first = p;
    }
    free(dic);
}



Word* addWord (Dictionary* dic, char* word) {
    if (findExactMatch(dic, word) != NULL) {
        return NULL;
    }
    Word* newWord = (Word*) malloc (sizeof(Word));
    newWord->word = (char*) malloc (strlen(word) + 1);
    strcpy(newWord->word, word);
    if (dic->first != NULL) {
        Word* p = searchForPushed(dic, newWord);
        if (p == NULL) {
            Word* pt = dic->first;
            while (pt->prox != NULL) {
                pt = pt->prox;
            }
            pt->prox = newWord;
            newWord->ant = pt;
            newWord->prox = NULL;
        }
        else {
            if (dic->first != p)
                p->ant->prox = newWord;
            newWord->ant = p->ant;
            p->ant = newWord;
            newWord->prox = p;
        }
        if (dic->first == p) {
            dic->first = newWord;
        }
    }
    else {
        newWord->ant = NULL;
        newWord->prox = NULL;
        dic->first = newWord;
    }
    return newWord;
}

char* getWord(Word* word) {
    if (word != NULL){
        char* w = (char*) malloc (strlen(word->word) + 1);
        strcpy(w, word->word);
        return w;
    }
    else {
        char* s = (char*) malloc (sizeof(char));
        s[0] = '\0';
        return s;
    }
}

Word* findExactMatch(Dictionary* dic, char* word) {
    Word* pt = dic->first;
    while (pt != NULL) {
        if (strcmp(word, pt->word) == 0) {
            return pt;
        }
        pt = pt->prox;
    }
    return NULL;
}

Word* findBestMatch (Dictionary* dic, char* word) {
    Word* pt = dic->first;
    int size = strlen(word);
    Word* bestMatch = NULL;
    int quantity = 0;
    while (pt != NULL) {
        if(size == strlen(pt->word)) {
            int equalLetters = similarities(pt->word, word);
            if (equalLetters > quantity || quantity == 0) {
                bestMatch = pt;
                quantity = equalLetters;
            }
            else if (equalLetters == quantity) {
                int a = lexicoGraphicalAnalysis(pt->word, bestMatch->word, word);
                if (a > 0) {
                    bestMatch = pt;
                }
            }
        }
        pt = pt->prox;
    }
    return bestMatch;
}

Word** findPrefix (Dictionary* dic, char* prefix) {
    Word* pt = dic->first;
    int size = 0;
    while (pt != NULL) {
        if (hasPrefix(pt->word, prefix) > 0) {
            size++;
        }
        pt = pt->prox;
    }
    Word** v = (Word**) malloc ((size + 1) * sizeof(Word*));
    pt = dic->first;
    int i = 0;
    while (pt != NULL) {
        if (hasPrefix(pt->word, prefix) > 0) {
            Word* w = (Word*) malloc (sizeof(Word));
            w->prox = NULL;
            w->ant = NULL;
            w->word = (char*) malloc (strlen(pt->word) + 1);
            strcpy(w->word, pt->word);
            v[i] = w;
            i++;
        }
        pt = pt->prox;
    }
    v[i] = NULL;
    return v;
}