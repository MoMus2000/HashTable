#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// -------------------------------
#define HASHTABLE_IMPLEMENTATION
#include "hashtable.h"
// -------------------------------

#define print(fmt, ...) printf(fmt "\n", ##__VA_ARGS__)

Entry* tableGet(Table *table, ObjString* key){
  return findKey(table->entries, key, table->capacity);
}

ObjString* allocateString(char* chars, int length, uint32_t hash) {
  ObjString* string = malloc(sizeof(ObjString));
  string->string = chars;
  string->hash = hash;
  return string;
}

uint32_t hashString(char* key) {
  uint32_t hash = 2166136261u;
  for(int i=0; i<strlen(key); ++i){
    hash ^= (uint8_t)key[i];
    hash *= 16777619;
  }
  return hash;
}

void initTable(Table* table) {
  table->count    = 0;
  table->capacity = 1000;
  table->entries  = malloc(sizeof(Entry) * MAP_CAP);
  for(int i=0; i<table->capacity; ++i){
    table->entries[i].key   = NULL;
  }
}

Entry* findKey(Entry *entries, ObjString *key, int capacity){
  uint32_t index = (key->hash % capacity);
  for(;;){
    Entry *entry = &entries[index];
    if (entry->key == key || entry->key == NULL){
      return entry;
    }
    index = (index+1) % capacity;
  }
}

bool resizeTable(Table* table){
  if (table->count >= (table->capacity * 0.75)){
      print("Resizing Table");
      Entry* entries = realloc(table->entries, sizeof(Entry)*MAP_CAP*2);
      for(int i=0; i<MAP_CAP*2; ++i){
        entries[i].key = NULL;
      }
      for(int i=0; i<table->capacity; ++i){
        if(table->entries[i].key == NULL) continue;
        Entry *dest = findKey(entries, table->entries[i].key, MAP_CAP*2);
        dest->key   = table->entries[i].key;
        dest->value = table->entries[i].value;
      }
      table->capacity = MAP_CAP*2;
      table->entries  = entries;
      return true;
  }
  return false;
}

bool tableSet(Table* table, ObjString* key, void* value){
  if(resizeTable(table)){
    print("Resized the table");
  }
  Entry* entry = findKey(table->entries, key, table->capacity);
  if(entry->key == NULL) table->count++;
  entry->key   = key;
  entry->value = (void *)value;
  return true;
}

// Function to generate a random string
void generateRandomString(char *str, int length) {
    int charsetSize = sizeof(CHARSET) - 1;
    
    for (int i = 0; i < length; i++) {
        str[i] = CHARSET[rand() % charsetSize];
    }
    
    str[length] = '\0'; // Null-terminate the string
}

int main(){
  Table table;
  initTable(&table);

  for (int i = 0; i < STRING_COUNT*100*100; i++) {
    char* value = "123";
    char randomString[STRING_LENGTH + 1];  // Stack allocation for each string
    generateRandomString(randomString, STRING_LENGTH);
    printf("String %d: %s\n", i + 1, randomString);
    uint32_t hash = hashString(randomString);
    ObjString* alloc = allocateString(randomString, strlen(randomString), hash);
    tableSet(&table, alloc, &value);
  }

  /*uint32_t hash = hashString("HELLO");*/
  /*ObjString* alloc = allocateString("HELLO", strlen("HELLO"), hash);*/
  /*double d = 10.0;*/
  /*void* ptr = &d;*/
  /*tableSet(&table, alloc, ptr);*/
  /*printf("String : %f\n",  *(double *)tableGet(&table, alloc)->value);*/

  return 0;
}

