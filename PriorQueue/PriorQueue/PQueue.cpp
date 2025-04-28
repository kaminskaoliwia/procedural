
#include <stdio.h>
#include <stdlib.h>
#include "PQueue.h"

//! funkcje pomocnicze
void UpdateDown( int l, int p, PQItem** tab ); // update heap down between index l and p  <--- modified Update() from HeapSort 
void UpdateUp(int l, int p, PQItem** tab ); // update heap up between index l and p  
PQINFO* PQDeQueue( PQueue* q );
void PQEnQueue( PQueue* q, PQItem* p );


PQueue* PQInit( int nSize )
{
  // alokuje pamiêæ do kolejki
  PQueue* pNew = ( PQueue*)calloc(1, sizeof(PQueue) );
  if( !pNew ) // je¿eli siê nie utworzy³a
    return NULL;

  // ustawienie wskaŸników
  pNew->PQSize = nSize;
  pNew->nPQCurrSize = 0;

  // je¿eli nie ma miejsca
  if( pNew->pPQueue == NULL ) return NULL;

  // zwraca wskaŸnik na nastêpne wolne miejsce
  return pNew;
}

int PQisEmpty( PQueue* q )
{
  return !q || !(q->nPQCurrSize); // zwraca 1 (pusta) lub 0 (niepusta)
}

int PQSize( PQueue* q )
{
  return q->nPQCurrSize; // zwraca aktualny rozmiar
}

int PQMaxPrior( PQueue* q ) //! zwraca najwiêkszy priorytet w kolejce
{
  if (PQisEmpty(q)) return PRIOR_ERROR;
  return q->pPQueue[0]->nPrior;
}

//! dodaje element do kolejki priorytetowej
/* PQueue* q - wskaŸnik na strukturê kolejki priorytetowej
* PQINFO* pInfo - dane które maj¹ zostaæ dodane
* nPrior - priorytet nowego elementu
*/
int PQEnqueue( PQueue* q, PQINFO* pInfo, int nPrior )  
{  
  if (!q || q->nPQCurrSize >= q->PQSize) return 0;

  PQItem* p = (PQItem*)calloc( 1, sizeof( PQItem ) ); // dynamiczne alokowanie pamiêci
  if( !p )
    return 0;

  p->pInfo = pInfo; // przypisanie wartoœci do nowego elementu
  p->nPrior = nPrior; // przypisanie priorytetu do nowego elementu
  PQEnQueue( q, p );

  q->pPQueue[q->nPQCurrSize] = p; //! umieszczenie nowego elementu na koncu kolejki
  q->nPQCurrSize++; // zwieksza ilosc elementow w kolejce

  return 1;
}

//! usuwa i zwraca element o najwy¿szym priorytecie z kolejki
PQINFO* PQDequeue( PQueue* q )
{
  return ( PQisEmpty( q ) ) ? NULL : PQDeQueue( q );

 }

//! __cdecl to konwencja wywo³ywania funkcji typowa dla wiêkszoœci kompilatorów C w systemie Windows. 
//! Mówi jakie argumenty maj¹ byæ przekazywane do funkcji i jak ma odbywaæ siê oczyszczanie stosu po jej wywo³aniu.
//! *FreeInfo = mamy wskaŸnik na funkcjê o nazwie FreeInfo.
//! (const void*) = typ argumentu który funkcja przyjmuje

void PQClear( PQueue* q, void( __cdecl* FreeInfo )( const void* )  )
{
 while( !PQisEmpty( q ) )
   FreeInfo( PQDequeue( q ) );
}

//! Usuwa cala kolejke wraz z pamiecia
void PQRelease( PQueue** q, void( __cdecl* FreeInfo )( const void* ) )
{
  PQClear( *q, FreeInfo );
  free( *q );
  *q = NULL;
}


void PQPrint( PQueue* q, void(__cdecl* PrintInfo)(const void* ), int nRoot )
{
  if( PQisEmpty( q ) ) return;

  // wypisuje priorytet oraz indeks elementu w kolejce 
  printf( "(%d)[%d] ", q->pPQueue[nRoot]->nPrior, nRoot );

  //! rekurencyjnie wypisuje najpierw lewe, póŸniej prawe dziecko w kopcu O ILE ISTNIEJE
  if( nRoot * 2 + 1 < q->nPQCurrSize ) PQPrint( q, PrintInfo, nRoot * 2 + 1 );
  if( nRoot * 2 + 2 < q->nPQCurrSize ) PQPrint( q, PrintInfo, nRoot * 2 + 2 );
}

//! U¿ywana po usuniêciu elementu z góry kopca
/* Element z do³u kopca jest przenoszony na górê, a póŸniej nastêpuje sortowanie
Czyli tutaj szykamy dzieci rodziców, a w UpdateUp szukamy rodziców dzieci */
void UpdateDown( int l, int p, PQItem** tab )
{
  if( l == p ) return; // sprawdza czy jest wiecej niz jeden element
  int i = l; 
  int j = 2 * i + 1; // lewe dziecko binarnie
  PQItem* temp = tab[i];
  while( j <= p )
  {
    if( j < p )
      if( tab[j]->nPrior <= tab[j + 1]->nPrior )
        j++;

    if( tab[j]->nPrior < temp->nPrior )
      break;
    tab[i] = tab[j];
    i = j;
    j = 2 * i + 1;
  }
  tab[i] = temp;
}

//! U¿ywana do dodania nowego elementu na koniec kolejki
/* przesuwa nowy element do góry, jeœli jego priorytet jest wiêkszy ni¿ rodzica. */
void UpdateUp(int l, int p, PQItem** tab )
{
  // funkcja dzia³a dopóki nie dotrzemy do korzenia, i przechodzi na rodziców
  for( int i = p; p >= l; i = (i-1) / 2 ) //! (i-1)/2 - indeks rodzica w kopcu binarnym 
  {
    if( tab[i]->nPrior > tab[ (i-1) / 2 ]->nPrior ) // jeœli dziecko ma wyzszy priorytet zamieniamy z rodzicem
    {
      PQItem* temp = tab[ (i-1) / 2 ];
      tab[ (i-1) / 2 ] = tab[i];
      tab[i] = temp;
      continue; // sprawdzamy jeszcze raz warunek dla nowego rodzica
    }
    break; // przerywamy petle jezeli priorytet rodzica jest rowny lub wiekszy od nowego elementu
  }
}

PQINFO* PQDeQueue( PQueue* q )
{

  PQItem* p = q->pPQueue[0]; //! pobiera dane o najwy¿szym priorytecie
  PQINFO* pInfo = p->pInfo;
  free( p );

  q->nPQCurrSize--; // zmniejszenie iloœci elementów kolejki

  //! je¿eli kolejka ma jeszcze jakieœ elementy to trzeba heapify
  if (q->nPQCurrSize > 0) {
    q->pPQueue[0] = q->pPQueue[q->nPQCurrSize]; // ostatni element na pocz¹tek - tak jak w sortowaniu stogowym
    UpdateDown(0, q->nPQCurrSize - 1, q->pPQueue); // heapify

  return pInfo;
}

  void PQEnQueue( PQueue* q, PQItem* p )
  {
    q->pPQueue[q->nPQCurrSize] = p;
    UpdateUp( 0, q->nPQCurrSize, q->pPQueue ); // przeniesienie w górê w kopcu
  }
