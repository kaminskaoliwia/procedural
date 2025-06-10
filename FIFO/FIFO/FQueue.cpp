
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
  return !q || !(q->pHead); /* FQueue* = wskaźnik do struktury danych kolejki
    !q, sprawdza czy wgl istnieje, a q->pHead sprawdza czy są dane (kolejka mogła zostać utworzona
    ale niedodane zostały żadne dane)

    Strzałka ma w celu dostanie się do pHead przez wskaźnik do struktury q, równoważne jest:
    (*q).pHead
  */
}

int    FQEnqueue( FQueue* q, QINFO* p ) // insert new item at the end
{
  if( !q ) return 0; // jeżeli kolejka nie istnieje to nie

  // memory allocation
  FQItem* pNew = (FQItem*)malloc(sizeof(FQItem) );
  if( !pNew ) { // jeżeli nie ma miejsca
    return 0;
  }

  pNew-> pInfo = p; // nowy int k = x
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

QINFO* FQDequeue( FQueue* q )        //! take out the first item
{

  if( FQEmpty( q ) )
  {
    return 0;
  }

  QINFO* value = q->pHead->pInfo; // pobieramy wartość key z tempa i nazywamy tą wartość value
  //q->pHead = q->pHead->pNext; /* (*q).pHead = (*q).pHead.pNext, czyli naszym nowym pHead następna wartość*/
 
  FQDel( q );

  //if ( !q->pHead ) {  // jeżeli kolejka stanie się pusta
  //  q->pTail = NULL; // (*q).pTail staje się pusta
  //? poprawione -> przeniesione do FQDel 

  return value; // wartość już usuniętej wartości, która kiedyś była pHead
}

void   FQClear( FQueue* q, void(__cdecl* freeMem)(const void*) )          // clears the queue
{
  //! spraq=w q i freemem
 /* while( !FQEmpty( q ) )
  {
    FQDel( q );
  }*/
  //? poprawione
  if ( !q ) {
    printf( "FQCLEAR: Kolejka nie istnieje" );
    return;
  }

  if (!freeMem) {
    printf("FQCLEAR: Funkcja freeMem jest NULL\n");
    return;
  }

  while ( !FQEmpty( q ) ) 
  {
    freeMem( FQDequeue( q ) );
  }

  q->pHead = q->pTail = NULL;
}

void    FQRemove( FQueue** q, void (__cdecl* freeMem)(const void*) )         // clears the queue  (=QFClear()) and removes
{//!!!q i *q
  //? poprawione
  
  if ( !q || !*q ) {
    printf( "FQREMOVE: Kolejka nie istnieje.\n" );
    return;
  }

  FQClear( *q, freeMem );
  free( *q ); // zwalnia wskaźnik q      
  *q = NULL;
//!!! wynuloWAC KOLEJKE
//? poprawione
}

void    FQDel( FQueue* q )             //! removes only first item
{
  if( FQEmpty( q ) )
  {
    printf("\nFQDEL: Kolejka jest pusta lub nie istnieje.\n");
    return;
  }

  FQItem* temp = q->pHead; // tymczasowa zmienna wskazujaca na poczatek kolejki
  q->pHead = temp->pNext; // q wskazuje teraz na nastepna

  free(temp); // zwolnienie pamięci
 

  if ( FQEmpty( q ) )
  {
    q->pTail = NULL; //!przeniesione z FQDequeue
  }
}

void FQPrint( FQueue* q, void(__cdecl* printInfo )(const void*) )
{
  if (FQEmpty(q) || !printInfo ) {
    printf("\nFQPRINT: Kolejka jest pusta lub nie istnieje lub nie ma funkcji.\n");
    return;
  }

  FQItem* p = q->pHead;
  while (p != NULL) {
    printInfo(p->pInfo);  // wypisywanie pola 'key'
    p = p->pNext;
  }
}
