#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 2048

int TOTAL_COLLISION = 0;
int TOTAL_INSERTION = 0;

typedef struct {
  char* key;
  void* value;
} Entry;

typedef struct {
  Entry** entries;
  int count;
  int capacity;
} Map;

//unsigned int simpleHash(const char* str){
//  unsigned int hash = 0;
//    while (*str) {
//        hash = hash * 31 + (unsigned char)(*str++);
//    }
//    return hash;
//}

//unsigned int simpleHash(const char* str) {
//    unsigned int hash = 2166136261u;
//    while (*str) {
//        hash ^= (unsigned char)(*str++);
//        hash *= 16777619u;
//    }
//    return hash;
//}

unsigned int simpleHash(const char* str) {
    unsigned int hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + (unsigned char)(*str++); // hash * 33 + c
    }
    return hash;
}

void growCapacity(Map* map) {
  int newCapacity = map->capacity * 2;

  printf("Growing Capacity To: %d\n", newCapacity);

  Entry** entries = calloc(newCapacity, sizeof(Entry*));

  for(int i=0; i<map->capacity; i++){
    Entry* entry = map->entries[i];
    if(entry != NULL){
      int newHash = simpleHash(entry->key) % newCapacity;
      while(entries[newHash] != NULL){
        newHash = (newHash + 1) % newCapacity;
      }
      entries[newHash] = entry;
    }
  }
  
  free(map->entries);
  map->entries = entries;
  map->capacity = newCapacity;
}

void addKey(char* key, void* value, Map* map){
  if(((float)map->count / map->capacity) > 0.30f){
    growCapacity(map);
  }

  Entry* entry = malloc(sizeof(Entry));

  int hash = simpleHash(key) % map->capacity;

  if(map->entries[hash] == NULL) {
    entry->key = malloc(strlen(key)+1);
    strcpy(entry->key, key);
    entry->value = value;
    map->entries[hash] = entry;
    TOTAL_INSERTION ++;
  } else {
    int idx = hash;
    while(map->entries[idx]!= NULL){
      idx = (idx + 1) % map->capacity;
    }
    entry->key = malloc(strlen(key)+1);
    strcpy(entry->key, key);
    entry->value = value;
    map->entries[idx] = entry;
    TOTAL_COLLISION ++;
  }
  map->count ++;
}


Entry* getEntry(char* key, Map* map) {
  int capacity = map->capacity;
  int hash = simpleHash(key) % capacity;
  int start = hash;

  while(map->entries[hash] != NULL) {
    if (strcmp(map->entries[hash]->key, key) == 0){
      return map->entries[hash];
    }
    hash = (hash + 1) % capacity;
    if (hash == start) break;  // full circle, not found
  }
  Entry entry = *map->entries[hash];

  return NULL;
}

void randomString(char* buffer, int length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charsetSize = sizeof(charset) - 1; // exclude null terminator

    for (int i = 0; i < length; i++) {
        int key = rand() % charsetSize;
        buffer[i] = charset[key];
    }
    buffer[length] = '\0';  // null-terminate
}

int main(int argc, char* argv[]){
  Map map = {0};

  map.capacity  = INITIAL_CAPACITY;
  map.entries   = calloc(INITIAL_CAPACITY, sizeof(Entry*));

  const int keyLength = 10;   // length of each key
  char key[keyLength + 1];

  for(int i=0; i< 50000; i++){
    randomString(key, keyLength);
    addKey(key, (void* )55, &map);
  }


  printf("Total Collisions: %d, Total Insertions: %d\n", TOTAL_COLLISION, TOTAL_INSERTION);

  return 0;
}


