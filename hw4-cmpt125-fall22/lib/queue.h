#ifndef QUEUE_STR_H
#define QUEUE_STR_H

struct node {
	char* data;
	struct node* next;
};

typedef struct node node_t;

// queue of chars
typedef struct {
  node_t* obfuscate[5];
  int what;
  int where;
} queue_str_t; 


// creates a new queue
queue_str_t* queue_create();

// enqueue a given item to the queue
void enqueue(queue_str_t* q, char* item);

// dequeue from the queue
// Pre condition: queue is not empty
char* dequeue(queue_str_t* q);

// returns 1 if the queue is empty, and returns 0 otherwise
int queue_is_empty(queue_str_t* q);

// free queue
void queue_free(queue_str_t* q);

void print_queue(queue_str_t* q);

#endif
