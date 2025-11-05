#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARENA_IMPLEMENTATION
#include "arena.h"

static Arena default_arena = {0};

void print_string(char* msg){
  printf("Message: %s\n", msg);
}

int main(int argc, char** argv){

  char* msg = arena_alloc(&default_arena, 64);
  strcpy(msg, "This is a sample string\0");
  
  print_string(msg);

  arena_alloc(&default_arena, 128);

  return 0;

}

