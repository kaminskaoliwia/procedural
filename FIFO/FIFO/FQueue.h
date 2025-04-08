#ifndef FQUEUE_H
#define FQUEUE_H

#include "global.h" // dostarczany przez uzytkownika tej kolejki
#include <stdio.h>
#include <stdlib.h>

typedef struct tagFQItem //definiuje strukture 
{ 
  int key;
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
int     FQDequeue( FQueue* q );        // take out the first item
void    FQClear( FQueue* q );          // clears the queue
void    FQRemove( FQueue** q );         // clears the queue  (=QFClear()) and removes
void    FQDel( FQueue* q );            // removes only first item

#endif