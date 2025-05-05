#ifndef FQUEUE_H
#define FQUEUE_H

#include "global.h" // dostarczany przez uzytkownika tej kolejki

#include <stdio.h>
#include <stdlib.h>

typedef struct tagFQItem //definiuje strukture 
{ 
  QINFO* pInfo; // zamiast klucz int to wskaünik na typ (niewiadomo czy to int czy inny)
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
int     FQEnqueue( FQueue* q, QINFO* p ); // insert new item at the end
QINFO*  FQDequeue( FQueue* q );        // take out the first item
void    FQClear( FQueue* q, void(__cdecl* freeMem)(const void*) );          // clears the queue
void    FQRemove( FQueue** q, void (__cdecl* freeMem)(const void*) ); // clears the queue (=QFClear()) and removes
void    FQDel( FQueue* q );            // removes only first item
void    ( __cdecl* freeMem )( const void* ); 
void    FQPrint( FQueue* q ); // adres funkcji do drukowania informacji

#endif