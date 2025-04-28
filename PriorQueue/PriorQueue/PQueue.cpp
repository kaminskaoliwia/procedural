
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
  // alokuje pami�� do kolejki
  PQueue* pNew = ( PQueue*)calloc(1, sizeof(PQueue) );
  if( !pNew ) // je�eli si� nie utworzy�a
    return NULL;

  // ustawienie wska�nik�w
  pNew->PQSize = nSize;
  pNew->nPQCurrSize = 0;

  // je�eli nie ma miejsca
  if( pNew->pPQueue == NULL ) return NULL;

  // zwraca wska�nik na nast�pne wolne miejsce
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

int PQMaxPrior( PQueue* q ) //! zwraca najwi�kszy priorytet w kolejce
{
  if (PQisEmpty(q)) return PRIOR_ERROR;
  return q->pPQueue[0]->nPrior;
}

//! dodaje element do kolejki priorytetowej
/* PQueue* q - wska�nik na struktur� kolejki priorytetowej
* PQINFO* pInfo - dane kt�re maj� zosta� dodane
* nPrior - priorytet nowego elementu
*/
int PQEnqueue( PQueue* q, PQINFO* pInfo, int nPrior )  
{  
  if (!q || q->nPQCurrSize >= q->PQSize) return 0;

  PQItem* p = (PQItem*)calloc( 1, sizeof( PQItem ) ); // dynamiczne alokowanie pami�ci
  if( !p )
    return 0;

  p->pInfo = pInfo; // przypisanie warto�ci do nowego elementu
  p->nPrior = nPrior; // przypisanie priorytetu do nowego elementu
  PQEnQueue( q, p );

  q->pPQueue[q->nPQCurrSize] = p; //! umieszczenie nowego elementu na koncu kolejki
  q->nPQCurrSize++; // zwieksza ilosc elementow w kolejce

  return 1;
}

//! usuwa i zwraca element o najwy�szym priorytecie z kolejki
PQINFO* PQDequeue( PQueue* q )
{
  return ( PQisEmpty( q ) ) ? NULL : PQDeQueue( q );

 }

//! __cdecl to konwencja wywo�ywania funkcji typowa dla wi�kszo�ci kompilator�w C w systemie Windows. 
//! M�wi jakie argumenty maj� by� przekazywane do funkcji i jak ma odbywa� si� oczyszczanie stosu po jej wywo�aniu.
//! *FreeInfo = mamy wska�nik na funkcj� o nazwie FreeInfo.
//! (const void*) = typ argumentu kt�ry funkcja przyjmuje

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

  //! rekurencyjnie wypisuje najpierw lewe, p�niej prawe dziecko w kopcu O ILE ISTNIEJE
  if( nRoot * 2 + 1 < q->nPQCurrSize ) PQPrint( q, PrintInfo, nRoot * 2 + 1 );
  if( nRoot * 2 + 2 < q->nPQCurrSize ) PQPrint( q, PrintInfo, nRoot * 2 + 2 );
}

//! U�ywana po usuni�ciu elementu z g�ry kopca
/* Element z do�u kopca jest przenoszony na g�r�, a p�niej nast�puje sortowanie
Czyli tutaj szykamy dzieci rodzic�w, a w UpdateUp szukamy rodzic�w dzieci */
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

//! U�ywana do dodania nowego elementu na koniec kolejki
/* przesuwa nowy element do g�ry, je�li jego priorytet jest wi�kszy ni� rodzica. */
void UpdateUp(int l, int p, PQItem** tab )
{
  // funkcja dzia�a dop�ki nie dotrzemy do korzenia, i przechodzi na rodzic�w
  for( int i = p; p >= l; i = (i-1) / 2 ) //! (i-1)/2 - indeks rodzica w kopcu binarnym 
  {
    if( tab[i]->nPrior > tab[ (i-1) / 2 ]->nPrior ) // je�li dziecko ma wyzszy priorytet zamieniamy z rodzicem
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

  PQItem* p = q->pPQueue[0]; //! pobiera dane o najwy�szym priorytecie
  PQINFO* pInfo = p->pInfo;
  free( p );

  q->nPQCurrSize--; // zmniejszenie ilo�ci element�w kolejki

  //! je�eli kolejka ma jeszcze jakie� elementy to trzeba heapify
  if (q->nPQCurrSize > 0) {
    q->pPQueue[0] = q->pPQueue[q->nPQCurrSize]; // ostatni element na pocz�tek - tak jak w sortowaniu stogowym
    UpdateDown(0, q->nPQCurrSize - 1, q->pPQueue); // heapify

  return pInfo;
}

  void PQEnQueue( PQueue* q, PQItem* p )
  {
    q->pPQueue[q->nPQCurrSize] = p;
    UpdateUp( 0, q->nPQCurrSize, q->pPQueue ); // przeniesienie w g�r� w kopcu
  }
