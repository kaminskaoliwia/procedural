
#include <iostream>
#include "FQueue.h"

#define ADD_ELEM_1 4
#define DEL_ELEM_1 3
#define ADD_ELEM_2 2
#define DEL_ELEM_2 1

/* trzy funkcje: jedna z nich zwalnia pamiêæ (adres trzeba przekazaæ do clear i remove)
parametry moga byc usuwane przez wywolujacego albo wywolywanego
__cdecl oznacza ¿e jest usuwane przez wywolujacego 
wywolywanego sciaga to konwencja Pascalowa
piszemy t¹ kolejkê jakby to by³a biblioteka funkcji (przyk³ad bibliotecznej definicji qsort)
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
   for( int i =1; i<=ADD_ELEM_1; i++ )
   {
      QINFO* pInfo = allocInfo( i, i+1, i+2 );
      if( !pInfo )
      {
        printf("ERROR: memory allocation!!\n");
        return 2;
      }

      if( !FQEnqueue(q, pInfo) )
      {
        printf("ERROR: EnQueue!!\n");
        return 3;
       }
   }

   printf("Queue created, added %d elements:\n", ADD_ELEM_1);
   FQPrint( q, printInfo );

  // usun¹æ 3 elementy
   printf("\nDeleting %d elements\n", DEL_ELEM_1);
   for( int i = 0; i < DEL_ELEM_1; i++ )
   {
      QINFO* p = FQDequeue( q );
      printf("\nDeleted item:\n");
      printInfo( p );
      freeInfo( p );
   }
   printf( "\nQueue after deleting %d elements:\n", DEL_ELEM_1 );
   FQPrint( q, printInfo );

   FQClear( q, freeInfo );
   printf("\nQueue after clearing:\n");
   FQPrint( q, printInfo );


   // dodac dwa elementy (wydrukowac kolejke) 
   for( int i = 0; i < ADD_ELEM_2; i++ )
   {
     QINFO* pInfo = allocInfo( i, i+1, i+2 );
     if( !pInfo ) {
       printf( "ERROR: memory allocation error or queue does not exist!!" );
       return 4;
     }
     if( !FQEnqueue(q, pInfo) )
     {
       printf("ERROR: EnQueue!!\n");
       return 5;
     }
   }

   printf("\nAdding to the queue %d elements:\n", ADD_ELEM_2);
   FQPrint( q, printInfo );

    // wyczyœciæ kolejke
   
     // usun¹æ jeden
     printf("\nDeleting an element:\n");
     QINFO* p = FQDequeue( q );
     printInfo( p );
     freeInfo( p );

     // usun¹æ ca³¹ kolejkê
     FQRemove( &q, freeInfo );

   return 0;
}

QINFO* allocInfo(int a, int b, int c)
{
  QINFO* pNew = ( QINFO*)malloc(sizeof(QINFO) ); // alokuje pamiêæ, pierwszy pusty wskaŸnik
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

  return pNew; // returnuje pNew typu wskaŸnik do QINFO
}

void freeInfo( const void *pInfo )
{
  if ( !pInfo ) return;
  free( ( (QINFO*)pInfo )->pTab );
  free( (QINFO*)pInfo );
}

void printInfo( const void *pInfo )
{
  if ( !pInfo ) return;
  printf( "key = %d pTab[0] = %d pTab[1] = %d\n",
    ((QINFO*)pInfo)->key,
    ((QINFO*)pInfo)->pTab[0],
    ((QINFO*)pInfo)->pTab[1] );
}
