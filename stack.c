#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/// The stack data structure is also a type of list. In this case, 
/// elements are pushed onto the stack’s top and then popped off. When multiple 
/// elements are pushed and then popped,the stack exhibits First-In-Last-Out (FILO) behavior. 
/// The first element pushed on tothe stack is the last element popped off.
/// (Understanding and Using Pointers, Richard Reese)

typedef struct _node {
  void *data;
  struct _node *next;
} Node;

typedef struct stack {
  Node *head;
  Node *tail;
} Stack;

void initializeStack(Stack *stack) {
  stack->head = NULL;
  stack->tail = NULL;
}

void push(Stack *stack, void *data) {
  Node *node = (Node *) malloc(sizeof(Node));
  node->data = data;

  if (stack->head == NULL) {
    stack->tail = node;
    node->next = NULL;
  } else
    node->next = stack->head;
  
  stack->head = node;
}

void *pop(Stack *stack) {
  Node *tmp = stack->head;
  void *data;

  if (stack->head == NULL) {
    data = NULL;
  } else if (stack->tail == stack->head) {
    stack->head = stack->tail = NULL;
    data = tmp->data;
    free(tmp);
  } else {
    stack->head = stack->head->next; 
    data = tmp->data;
    free(tmp);
  }

  return data;
}

int main() {
  Stack stack;

  initializeStack(&stack);

  push(&stack, "a");
  push(&stack, "b");
  push(&stack, "c");

  assert(stack.head != NULL);
  assert(stack.tail != NULL);
  assert(stack.head->data == "c");
  assert(stack.tail->data == "a");

  pop(&stack);
  assert(stack.head->data == "b");
  assert(stack.tail->data == "a");
  
  pop(&stack);
  assert(stack.head->data == "a");
  assert(stack.tail->data == "a");
  assert(stack.head != NULL);
  assert(stack.tail != NULL);

  pop(&stack);
  assert(stack.head == NULL);
  assert(stack.tail == NULL);

  return 0;     
}
