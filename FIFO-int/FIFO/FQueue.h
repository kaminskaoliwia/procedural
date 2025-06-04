#ifndef FQUEUE_H
#define FQUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct tagFQItem //definiuje strukture 
{ 
  int Info;
  tagFQItem* pNext;
  /*ptr to the next QItem   - pNext; */
} FQItem; 


typedef struct
{
  FQItem* pHead;  // ptr to the first queue item
  FQItem* pTail;  // ptr to the last queue item
} FQueue;  // typ kolejkowy

FQueue* FQCreate();                    // queue initiating  (NULL - fail)
int     FQEmpty( FQueue* q );          // if FIFO empty returned 1 else 0
int     FQEnqueue( FQueue* q, int x ); // insert new item at the end
int     FQDequeue( FQueue* q );        // wywoluje FQDel
void    FQClear( FQueue* q );          // clears the queue
void    FQRemove( FQueue** q ); // clears the queue (=QFClear()) and removes
void    FQDel( FQueue* q );            // removes only first item
void    FQPrint( FQueue* q ); // adres funkcji do drukowania informacji

#endif