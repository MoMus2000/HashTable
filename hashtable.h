#ifdef HASHTABLE_IMPLEMENTATION

#define CHARSET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define STRING_COUNT 100   // Number of random strings
#define STRING_LENGTH 10   // Length of each random string
#define MAP_CAP 100*100*100

typedef struct {
  char*    string;
  uint32_t hash;
} ObjString;

typedef struct {
  ObjString* key;
  void*      value;
} Entry;

typedef struct {
  uint64_t    count;
  uint64_t    capacity;
  Entry* entries;
} Table;

void initTable(Table *table);

ObjString* allocateString(char* chars, int length, uint32_t hash);
 
uint32_t hashString(char* key);

Entry* findKey(Entry *entries, ObjString *key, int capacity);

bool resizeTable(Table* table);

Entry* tableSet(Table* table, ObjString* key, void* value);

Entry* tableGet(Table *table, ObjString* key);

#endif

