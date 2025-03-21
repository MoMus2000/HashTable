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
  Entry* entries  = malloc(sizeof(Entry) * MAP_CAP);
  for(int i=0; i<table->capacity; ++i){
    entries[i].key   = NULL;
  }
  table->entries = entries;
}

Entry* findKey(Entry *entries, ObjString *key, int capacity){
  uint32_t index = (key->hash % capacity);
  for(;;){
    Entry *entry = &entries[index];
    /*if (entry->key == key || entry->key == NULL){*/
    if (entry->key == NULL){
      return entry;
    }
    else if(strcmp(entry->key->string, key->string) == 0){
      /*print("Found a key that exists %s", entry->key->string);*/
      /*print("UserKey %s", key->string);*/
      /*print("-----------------------------------");*/
      return entry;
    }
    index = (index+1) % capacity;
  }
}

bool resizeTable(Table* table){
  if (table->count >= (table->capacity * 0.50)){
      print("Resizing Table");
      Entry* entries = realloc(table->entries, sizeof(Entry)*table->capacity*table->capacity);
      for(int i=0; i<table->capacity*table->capacity; ++i){
        entries[i].key = NULL;
      }
      for(int i=0; i<table->capacity; ++i){
        if(table->entries[i].key == NULL) continue;
        Entry *dest = findKey(entries, table->entries[i].key, table->capacity*table->capacity);
        dest->key   = table->entries[i].key;
        dest->value = table->entries[i].value;
      }
      table->capacity = table->capacity*table->capacity;
      table->entries  = entries;
      return true;
  }
  return false;
}

Entry* tableSet(Table* table, ObjString* key, void* value){
  if(resizeTable(table)){
    print("Resized the table");
  }
  Entry* entry = findKey(table->entries, key, table->capacity);
  if(entry->key == NULL) table->count++;
  entry->key   = key;
  entry->value = (void *)value;
  return entry;
}

