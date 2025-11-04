#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
  void* value;
  struct Node* next;
} Node;

typedef struct {
  Node* head;
  int size;
} LinkedList;


int main(){
  LinkedList* list;

  list = malloc(sizeof(LinkedList));


  Node* node1 = malloc(sizeof(Node));
  char *message = "Hello";
  node1->value = (void*)message;

  list->head = node1;

  Node* node2 = malloc(sizeof(Node));
  char *message1 = "Hello1";
  node2->value = (void*)message1;

  node1->next = node2;

  Node* current = list->head;

  while(current != NULL){
    printf("Pointing to %s\n", (char*)current->value);
    current = current->next;
  }

  return 0;
}

