#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/// "A queue is a linear data structure whose behavior is similar to a waiting line. 
/// It typicallysupports two primary operations: enqueue and dequeue. The enqueue operation 
/// addsan element to the queue. The dequeue operation removes an element from the queue. 
/// Normally, the first element added to a queue is the first element dequeued from a queue.
/// This behavior is referred to as First-In-First-Out (FIFO)."
/// (Understanding and Using Pointers, Richard Reese)

typedef struct _node {
  void *data;
  struct _node *next;
} Node;

typedef struct _queue {
  Node *head;
  Node *tail;
} Queue;

void initializeQueue(Queue *queue) {
  queue->head = NULL;
  queue->tail = NULL;
}

void enqueue(Queue *queue, void *data) {
  Node *node = (Node *) malloc(sizeof(Node));
  node->data = data;

  if (queue->head == NULL) {
    queue->tail = node;
    node->next = NULL;
  } else
    node->next = queue->head;
  
  queue->head = node;
}

void *dequeue(Queue *queue) {
  Node *tmp = queue->head;
  void *data;

  if (queue->head == NULL) {
    data = NULL;
  } else if (queue->head == queue->tail) {
    queue->head = queue->tail = NULL; 
    data = tmp->data;
    free(tmp);
  } else {
    while (tmp->next != queue->tail) {
      tmp = tmp->next;
    }

    queue->tail = tmp;
    tmp = tmp->next;
    queue->tail->next = NULL;
    data = tmp->data;
    free(tmp);
  }

  return data;
} 

int main() {
  Queue queue;
  initializeQueue(&queue);

  enqueue(&queue, "a");
  enqueue(&queue, "b");
  enqueue(&queue, "c");

  assert(queue.head != NULL);
  assert(queue.tail != NULL);
  assert(queue.head->data == "c");
  assert(queue.tail->data == "a");

  dequeue(&queue);
  assert(queue.head->data == "c");
  assert(queue.tail->data == "b");

  dequeue(&queue);
  assert(queue.head != NULL);
  assert(queue.tail != NULL);

  dequeue(&queue);
  assert(queue.head == NULL);
  assert(queue.tail == NULL);

  return 0;
}
