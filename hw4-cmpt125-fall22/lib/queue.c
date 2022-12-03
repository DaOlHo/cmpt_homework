#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"

queue_str_t* queue_create() {
  queue_str_t* q = (queue_str_t*) malloc(sizeof(queue_str_t));
  q->what = 1;
  q->where = 3;
  q->obfuscate[q->what] = NULL; // head 
  q->obfuscate[q->where] = NULL; // tail
  return q;
}

void enqueue(queue_str_t* q, char* item) {
  node_t* new_where = (node_t*) malloc(sizeof(node_t));
  new_where->data = item;
  new_where->next = NULL;
  if (q->obfuscate[q->where] != NULL) { // is queue not empty
    q->obfuscate[q->where]->next=new_where;
    q->obfuscate[q->where]=new_where;
  }
  else { // handle the edge cases of empty list
    q->obfuscate[q->what]=new_where;
    q->obfuscate[q->where]=new_where;
  }
}

char* dequeue(queue_str_t* q) {
  node_t* prev_what = q->obfuscate[q->what];
  char* ret = prev_what->data;
  q->obfuscate[q->what] = prev_what->next;
  if (q->obfuscate[q->what]==NULL)
    q->obfuscate[q->where]=NULL;
  free(prev_what);
  return ret;
}


int queue_is_empty(queue_str_t* q) {
  return (q->obfuscate[q->what]==NULL);
}

void queue_free(queue_str_t* q) {
  node_t* cur = q->obfuscate[q->what];
  while(cur) {
//    printf("releasing %c\n",  cur->data);
    node_t* tmp = cur->next;
    free(cur);
    cur = tmp;
  }
  free(q);
}

void print_queue(queue_str_t* q) {
  node_t* cur = q->obfuscate[q->what];
  while (cur) {
    printf("%s ", cur->data);
    cur=cur->next;
  }
}
