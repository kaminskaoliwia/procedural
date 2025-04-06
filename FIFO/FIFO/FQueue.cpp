
#include "FQueue.h"

FQueue* FQCreate()                    // queue initiating  (NULL - fail)
{
  FQueue* pNew = (FQueue*)malloc(sizeof(FQueue) );
  if( !pNew )
  {
    return NULL;
  }
  pNew->pHead = pNew->pTail = NULL;

  return pNew;
}

int     FQEmpty( FQueue* q )          // if FIFO empty returned 1 else 0
{
  return !q || !(q->pHead);
}

int    FQEnqueue( FQueue* q, int x ) // insert new item at the end
{
  if( !q ) return 0;

  //todo memory allocation
  FQItem* pNew = (FQItem*)malloc(sizeof(FQItem) );
  if( !pNew ) {
    return 0;
  }

  //! przewi¹zaæ pTail na NewItem u¿ywaj¹c pNew
  pNew-> key = x;
  pNew-> pNext = NULL; // jako, ¿e dodajemy na koniec, nastêpny musi byæ pusty

  if( q->pHead == NULL)
  {
    q-> pHead = pNew;
  }
  else
  {
    q->pTail->pNext = pNew; //! nastêpny to nowy
  }

  q->pTail = pNew; //! tail pointer na nowy 
}

int     FQDequeue( FQueue* q )        //! take out the first item
{
  if(FQEmpty( q ) )
  {
    return 0;
  }

  FQItem* temp = q->pHead;
  int value = temp->key;
  q->pHead = q->pHead->pNext; 

  if (!q->pHead) {  // je¿eli kolejka stanie siê pusta
    q->pTail = NULL; 
  }
  free(temp);

  return value; 
}

void    FQClear( FQueue* q )          // clears the queue
{
  while(!FQEmpty( q ) )
  {
    FQDel( q );
  }

  q->pHead = q->pTail = NULL;
}

void    FQRemove( FQueue** q )         // clears the queue  (=QFClear()) and removes
{
  FQClear( *q );
  free( *q );
}

void    FQDel( FQueue* q )             //! removes only first item
{
  if(FQEmpty( q ) )
  {
    printf("\nERROR del: stack is empty!!!\n");
    return;
  }

  FQItem* temp = q->pHead; // tymczasowa zmienna wskazujaca na poczatek kolejki
  q->pHead = q->pHead->pNext; // q wskazuje teraz na nastepna
  free( temp ); // zwolnienie miejsca
}