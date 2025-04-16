
#include <iostream>
#include "FQueue.h"

/* trzy funkcje: jedna z nich zwalnia pami�� (adres trzeba przekaza� do clear i remove)
parametry moga byc usuwane przez wywolujacego albo wywolywanego
__cdecl oznacza �e jest usuwane przez wywolujacego 
wywolywanego sciaga to konwencja Pascalowa
piszemy t� kolejk� jakby to by�a biblioteka funkcji (przyk�ad bibliotecznej definicji qsort)
*/

// zdefiniowac allocInfo (trzy parametry typu int a, b ,c) do alokacji pamieci informacji - zwraca wskaznik do QInfo
QINFO* allocInfo(int a, int b, int c);
// freeInfo - typu void i z parametr const void
void freeInfo( const void *pInfo );

// printInfo -||-
void printInfo( const void *pInfo );

int main()
{
   FQueue* q = FQCreate();
   
   if (!q )
   {
    printf("ERROR: create queue!!!\n");
    return 1;
   }

    // dodac do kolejki 4 wlwmenty (wydrukowac kolejke)
   for( int i =1; i<=4; i++ )
   {
      QINFO* pInfo = allocInfo( i, i+1, i+2 );
      if( !FQEnqueue(q, pInfo) )
      {
        printf("ERROR in EnQueue!!\n");
        return 2;
       }
   }

   FQPrint( q, printInfo );

  // usun�� 3 elementy
   for( int i = 0; i++; i<3 )
   {
      QINFO* p = FQDequeue( q );
      printInfo( p );
      freeInfo( p );
   }

   // dodac dwa elementy (wydrukowac kolejke) 
   for( int i = 0; i < 3; i++ )
   {
     QINFO* pInfo = allocInfo( i, i+1, i+2 );
     if( !FQEnqueue(q, pInfo) )
     {
       printf("ERROR in EnQueue!!\n");
       return 2;
     }
   }

    // wyczy�ci� kolejke
     FQClear( q, freeInfo );

     // usun�� jeden
     QINFO* p = FQDequeue( q );
     printInfo( p );
     freeInfo( p );

     // usun�� ca�� kolejk�
     FQRemove( &q, freeInfo );

   return 0;
}

QINFO* allocInfo(int a, int b, int c)
{
  QINFO* pNew = ( QINFO*)malloc(sizeof(QINFO) ); // alokuje pami��, pierwszy pusty wska�nik
  if( !pNew ) return NULL;

  pNew->pTab = ( int* )malloc(sizeof(int) * 2 );
  if ( !(pNew->pTab) )
  {
    free( pNew );
    return NULL;
  }
  
  pNew->key = a;
  pNew->pTab[0] = b;
  pNew->pTab[1] = c;

  return pNew; // returnuje pNew typu wska�nik do QINFO
}

void freeInfo( const void *pInfo )
{
  if ( !pInfo ) return;
  free( ( (QINFO*)pInfo )->pTab );
  free( (QINFO*)pInfo );
}

void printInfo( const void *pInfo )
{
  printf( "key = %d pTab[0] = %d pTab[1] = %d\n",
    ((QINFO*)pInfo)->key,
    ((QINFO*)pInfo)->pTab[0],
    ((QINFO*)pInfo)->pTab[1] );
}