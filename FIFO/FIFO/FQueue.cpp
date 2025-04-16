
#include "FQueue.h"

FQueue* FQCreate()                    // queue initiating  (NULL - fail)
{
  FQueue* pNew = ( FQueue*)malloc(sizeof(FQueue) ); // alokuje pamiêæ, pierwszy pusty wskaŸnik
  if( !pNew ) // je¿eli nie ma miejsce
  {
    return NULL;
  }
  pNew->pHead = pNew->pTail = NULL; // wskaŸnik pNew wskazuj¹cy na pHead/pTail = NULL

  return pNew; // returnuje pNew typu wskaŸnik do FQueue
}

int FQEmpty( FQueue* q ) // if FIFO empty returned 1 else 0
{
  return !q || !(q->pHead); /* FQueue* = wskaŸnik do struktury danych kolejki
    !q, sprawdza czy wgl istnieje, a q->pHead sprawdza czy s¹ dane (kolejka mog³a zostaæ utworzona
    ale niedodane zosta³y ¿adne dane)

    Strza³ka ma w celu dostanie siê do pHead przez wskaŸnik do struktury q, równowa¿ne jest:
    (*q).pHead
  */
}

int    FQEnqueue( FQueue* q, QINFO* p ) // insert new item at the end
{
  if( !q ) return 0; // je¿eli kolejka nie istnieje to nie

  //! memory allocation
  FQItem* pNew = (FQItem*)malloc(sizeof(FQItem) );
  if( !pNew ) { // je¿eli nie ma miejsca
    return 0;
  }

  pNew-> pInfo = p; // nowy int k = x
  pNew-> pNext = NULL; // jako, ¿e dodajemy na koniec, nastêpny wskaŸnik musi byæ pusty

  if( q->pHead == NULL) // je¿eli nie ma ¿adnego member 
  {
    q-> pHead = pNew; // to nasz nowy member jest wskazywany na przez pHead
  }
  else
  {
    q->pTail->pNext = pNew; // (*q).pTail.pNext = pNew
  }

  q->pTail = pNew; // (*q).pTail = pNew
}

QINFO* FQDequeue( FQueue* q )        //! take out the first item
{
  if(FQEmpty( q ) )
  {
    return 0;
  }

  FQItem* temp = q->pHead; // tworzymy nowy skaŸnik na pHead o nazwie temp
  QINFO* value = temp->pInfo; // pobieramy wartoœæ key z tempa i nazywamy t¹ wartoœæ value
  q->pHead = q->pHead->pNext; /* (*q).pHead = (*q).pHead.pNext, czyli naszym nowym pHead
                                   nastêpna wartoœæ*/

  if ( !q->pHead ) {  // je¿eli kolejka stanie siê pusta
    q->pTail = NULL; // (*q).pTail staje siê pusta
  }
  free( temp ); // zwalniamy pamiêæ z tempa

  return value; // wartoœæ ju¿ usuniêtej wartoœci, która kiedyœ by³a pHead
}

void   FQClear( FQueue* q, void(__cdecl* freeMem)(const void*) )          // clears the queue
{
  while( !FQEmpty( q ) )
  {
    FQDel( q );
  }

  q->pHead = q->pTail = NULL;
}

void    FQRemove( FQueue** q, void (__cdecl* freeMem)(const void*) )         // clears the queue  (=QFClear()) and removes
{
  FQClear( *q );
  free( *q ); // zwalnia wskaŸnik q       
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

void    FQPrint( FQueue* q, void (__cdecl *freeMem)( const void* ) )
{

}