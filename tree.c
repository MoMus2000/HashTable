#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int value;
  struct Node* left;
  struct Node* right;
} Node;

typedef struct{
  Node* root;
} Tree;


void traversal(Node* t){
  if(t == NULL){
    return;
  }

  printf("Val: %d\n", t->value);

  traversal(t->left);
  traversal(t->right);
}


int main(){
  Tree* t = malloc(sizeof(Tree));
  Node* root = malloc(sizeof(Node));
  root->value = 5;
  root->left = malloc(sizeof(Node));
  root->left->value = 3;

  root->left->right = NULL;
  root->left->left = NULL;

  root->right = malloc(sizeof(Node));
  root->right->value = 4;

  root->right->right = NULL;
  root->right->left = NULL;


  t->root = root;

  traversal(t->root);
  
   // 5
  // / \
 // 3   4

  return 0;
}

