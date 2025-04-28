
#include <iostream>
#include "PQueue.h"

PQINFO* allocInfo(int a, int b, int c);
void freeInfo( const void *pInfo );
void printInfo( const void *pInfo );
int compareInfo( void const* x, void const* y); //Zwraca - 1 pierwszy mniejszy, 1 jesli pierwszy wiekszy else 0.


int main()
{
    std::cout << "Hello World!\n";
}

PQINFO* allocInfo(int a, int b, int c)
{
  PQINFO* pNew = ( PQINFO*)malloc(sizeof(PQINFO) ); // alokuje pamiec, pierwszy pusty wskaŸnik
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

  return pNew; // returnuje pNew typu wskaznik do QINFO
}

void freeInfo( const void *pInfo )
{
  if ( !pInfo ) return;
  free( ( (PQINFO*)pInfo )->pTab );
  free( (PQINFO*)pInfo );
}

void printInfo( const void *pInfo )
{
  printf( "key = %d pTab[0] = %d pTab[1] = %d\n",
    ((PQINFO*)pInfo)->key,
    ((PQINFO*)pInfo)->pTab[0],
    ((PQINFO*)pInfo)->pTab[1] );
}

int compareInfo( void const* x, void const* y)
{
  if( ( (PQINFO*)x )->key > ( (PQINFO*)y )->key ) return 1;
  if( ( (PQINFO*)x )->key < ( (PQINFO*)y )->key ) return -1;
  return 0;
}