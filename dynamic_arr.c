#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  void** elements;
  int size;
  int capacity;
} Array;

void resize_arr(Array* arr){
  arr->capacity = arr->capacity * 2;
  void** elements = malloc(arr->capacity * sizeof(void*));
  for(int i=0; i<arr->size; i++){
    elements[i] = arr->elements[i];
  }
  free(arr->elements);
  arr->elements = elements;
}

void init_arr(Array* arr){
  arr->size = 0;
  arr->capacity = 5;
  arr->elements = malloc(arr->capacity * sizeof(void*));
}

void append(Array* arr, void* elem){
  arr->elements[arr->size] = elem;
  arr->size += 1;
  if (((float)arr->size / arr->capacity) > 0.7) {
    resize_arr(arr);
  }
}

int main(){
  Array arr;
  init_arr(&arr);

  for(int i=0; i<100; i++){
    append(&arr, (void*)(intptr_t)i);
  }

  for(int i=0; i<100; i++){
    printf("Elem: %d\n", (int)(intptr_t)arr.elements[i]);
  }

  printf("Dynamic Arr Cap: %d\n", arr.capacity);

  return 0;
}

