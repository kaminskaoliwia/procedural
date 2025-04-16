
#include "FQueue.h"

FQueue* FQCreate()                    // queue initiating  (NULL - fail)
{
  FQueue* pNew = ( FQueue*)malloc(sizeof(FQueue) ); // alokuje pami��, pierwszy pusty wska�nik
  if( !pNew ) // je�eli nie ma miejsce
  {
    return NULL;
  }
  pNew->pHead = pNew->pTail = NULL; // wska�nik pNew wskazuj�cy na pHead/pTail = NULL

  return pNew; // returnuje pNew typu wska�nik do FQueue
}

int FQEmpty( FQueue* q ) // if FIFO empty returned 1 else 0
{
  return !q || !(q->pHead); /* FQueue* = wska�nik do struktury danych kolejki
    !q, sprawdza czy wgl istnieje, a q->pHead sprawdza czy s� dane (kolejka mog�a zosta� utworzona
    ale niedodane zosta�y �adne dane)

    Strza�ka ma w celu dostanie si� do pHead przez wska�nik do struktury q, r�wnowa�ne jest:
    (*q).pHead
  */
}

int    FQEnqueue( FQueue* q, QINFO* p ) // insert new item at the end
{
  if( !q ) return 0; // je�eli kolejka nie istnieje to nie

  //! memory allocation
  FQItem* pNew = (FQItem*)malloc(sizeof(FQItem) );
  if( !pNew ) { // je�eli nie ma miejsca
    return 0;
  }

  pNew-> pInfo = p; // nowy int k = x
  pNew-> pNext = NULL; // jako, �e dodajemy na koniec, nast�pny wska�nik musi by� pusty

  if( q->pHead == NULL) // je�eli nie ma �adnego member 
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

  FQItem* temp = q->pHead; // tworzymy nowy ska�nik na pHead o nazwie temp
  QINFO* value = temp->pInfo; // pobieramy warto�� key z tempa i nazywamy t� warto�� value
  q->pHead = q->pHead->pNext; /* (*q).pHead = (*q).pHead.pNext, czyli naszym nowym pHead
                                   nast�pna warto��*/

  if ( !q->pHead ) {  // je�eli kolejka stanie si� pusta
    q->pTail = NULL; // (*q).pTail staje si� pusta
  }
  free( temp ); // zwalniamy pami�� z tempa

  return value; // warto�� ju� usuni�tej warto�ci, kt�ra kiedy� by�a pHead
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
  free( *q ); // zwalnia wska�nik q       
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