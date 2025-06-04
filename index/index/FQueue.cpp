
#include "FQueue.h"

FQueue* FQCreate()                    // queue initiating  (NULL - fail)
{
  FQueue* pNew = ( FQueue*)malloc(sizeof(FQueue) ); // alokuje pamięć, pierwszy pusty wskaźnik
  if( !pNew ) // jeżeli nie ma miejsce
  {
    return NULL;
  }
  pNew->pHead = pNew->pTail = NULL; // wskaźnik pNew wskazujący na pHead/pTail = NULL

  return pNew; // returnuje pNew typu wskaźnik do FQueue
}

int FQEmpty( FQueue* q ) // if FIFO empty returned 1 else 0
{
  return !q || !(q->pHead);
}

int    FQEnqueue( FQueue* q, int x ) // insert new item at the end
{
  if( !q ) return 0; // jeżeli kolejka nie istnieje to nie

  //! memory allocation
  FQItem* pNew = (FQItem*)malloc(sizeof(FQItem) );
  if( !pNew ) { // jeżeli nie ma miejsca
    return 0;
  }

  pNew-> Info = x; 
  pNew-> pNext = NULL; // jako, że dodajemy na koniec, następny wskaźnik musi być pusty

  if( q->pHead == NULL) // jeżeli nie ma żadnego member 
  {
    q-> pHead = pNew; // to nasz nowy member jest wskazywany na przez pHead
  }
  else
  {
    q->pTail->pNext = pNew; // (*q).pTail.pNext = pNew
  }

  q->pTail = pNew; // (*q).pTail = pNew

return 1;
}

int FQDequeue( FQueue* q )        //! take out the first item
{

  if( FQEmpty( q ) )
  {
    return 0;
  }

  int value = q->pHead->Info; // pobieramy wartość key z tempa i nazywamy tą wartość value
  //q->pHead = q->pHead->pNext; /* (*q).pHead = (*q).pHead.pNext, czyli naszym nowym pHead następna wartość*/
  while( !FQEmpty( q ) )
  {
    FQDel( q );
  }

  return value; // wartość już usuniętej wartości, która kiedyś była pHead
}

void   FQClear( FQueue* q )          // clears the queue
{

  if ( !q ) {
    printf( "FQCLEAR: Kolejka nie istnieje" );
    return;
  }

  while( !FQEmpty( q ) )
  {
    FQDequeue( q );
  }
  q->pHead = q->pTail = NULL;
}

void    FQRemove( FQueue** q )         // clears the queue  (=QFClear()) and removes
{
  if ( !q || !*q ) {
    printf( "FQREMOVE: Kolejka nie istnieje.\n" );
    return;
  }

  free( *q ); // zwalnia wskaźnik q      
  *q = NULL;
}

void    FQDel( FQueue* q )             //! removes only first item
{
  if(FQEmpty( q ) )
  {
    printf("\nFQDEL: Kolejka jest pusta.\n");
    return;
  }

  FQItem* temp = q->pHead; // tymczasowa zmienna wskazujaca na poczatek kolejki
  q->pHead = q->pHead->pNext; // q wskazuje teraz na nastepna
  //if
  free( temp ); // zwolnienie miejsca

  if ( FQEmpty( q ) )
  {
    q->pTail = NULL; //!przeniesione z FQDequeue
  }
}

void FQPrint( FQueue* q )
{
  if (FQEmpty(q)) {
    printf("\nFQPRINT: Kolejka jest pusta.\n");
    return;
  }

  FQItem* p = q->pHead;
  while (p != NULL) {
    printf("%d ", p->Info);  // wypisywanie pola 'key'
    p = p->pNext;
  }
}
