typedef struct dictionary Dictionary;
typedef struct word Word;

Dictionary* createDictionary ();
void freeDictionary (Dictionary *dic);

Word* addWord (Dictionary* dic, char* word);
char* getWord (Word* word);

Word* findExactMatch (Dictionary* dic, char* word);
Word* findBestMatch (Dictionary* dic, char* word);
Word** findPrefix (Dictionary* dic, char* prefix);
