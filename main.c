#include <stdio.h>
#define HASHTABLE_IMPLEMENTATION
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hashtable.h"

#define print(fmt, ...) printf(fmt "\n", ##__VA_ARGS__)

int main(){
  Table table;
  initTable(&table);

  FILE* file = fopen("sonnets.txt", "r");

  if(file == NULL) {
    print("File Could Not be Open");
    return 1;
  }

  ssize_t      read;
  char* line = NULL;
  size_t len = 0;

  uint32_t hash = hashString("HI");
  ObjString* tokenString = allocateString("HI", strlen("HI"), hash);
  int count1 = 1000;
  Entry* entry = tableSet(&table, tokenString, (void *)&count1);

  print("Entry entry: %u hash Index: %llu ", hash, hash%table.capacity);
  print("Entry entry: %s String ", tokenString->string);
  print("Entry entry: %p Fetched ", entry);
  print("Entry entry: %p Fetched KEY", entry->key);
  print("Entry entry: %s Fetched string", entry->key->string);
  print("Entry entry: %d Fetched string", *(int*)entry->value);

  while((read = getline(&line, &len, file)) != -1){
    char *tokens = strtok(line, " ");
    while(tokens != NULL){
      uint32_t hash = hashString(tokens);
      ObjString* tokenString = allocateString(tokens, strlen(tokens), hash);
      /*print("Entry entry: %s String ", tokenString->string);*/
      Entry* fetched = tableGet(&table, tokenString);
      if(fetched->key != NULL){
        /*print("Entry entry: %u hash Index: %u ", hash, hash%table.capacity);*/
        /*print("Entry entry: %p Fetched ", fetched);*/
        /*print("Entry entry: %p Fetched KEY", fetched->key);*/
        /*print("Entry entry: %s Fetched string", fetched->key->string);*/
        /*print("Entry entry: %s Actual string", tokens);*/
        /*print("Entry entry: %u Fetched value", *(int*)fetched->value);*/
        int count = *(int*)fetched->value+1;
        Entry* entry = tableSet(&table, tokenString, (void *)&count);
      }
      /*if(fetched == NULL){*/
        int count = 1;
        Entry* entry = tableSet(&table, tokenString, (void *)&count);
      /*}*/
      tokens = strtok(NULL, " ");
    }
  }


  hash = hashString("HI");
  tokenString = allocateString("HI", strlen("HI"), hash);
  Entry* fetched = tableGet(&table, tokenString);
  print("Entry entry: %u hash Index: %llu ", hash, hash%table.capacity);
  print("Entry entry: %s String ", tokenString->string);
  print("Entry entry: %p Fetched ", fetched);
  print("Entry entry: %p Fetched KEY", fetched->key);
  print("Entry entry: %s Fetched string", fetched->key->string);
  print("Entry entry: %d Fetched string", *(int*)fetched->value);

  print("Table count %llu", table.count);
}

