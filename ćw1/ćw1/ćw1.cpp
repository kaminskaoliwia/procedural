
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
// typ strukturalny może być "tablicą" gdzie dane mogą różnić się typem

#define MAX 8

void printTab( int* pTab, int nSize );

typedef struct
{
  double mX; // m - member
  double mY;

} Point; // nazwa typu, od tego czasu point jest zdefiniowany

int main()
{
  Point pt1 = { 1, 4.56 };
  Point pt = { 0 };

  // Jak dostać się do elementu struktury?
  pt.mX = 4;
  pt.mY = -12;
  printf( "(%lf,%lf)\n", pt.mX, pt.mY );

  // Wskaźnik na point, zawsze należy inicjować (wymóg metodologii programowania)
  //Point* pPt = &pt;
 // Point* pPt = NULL; // NULL = 0, tylko uzywamy przy wskaznikach, w liczbach cyfrowo
  Point* pPt = (Point*)malloc(sizeof(Point)); // malloc - memory alocation 
    //zawsze trzeba zrzutowac na typ taki jak zmienna po lewej stronie
    //rozmiar w bajtach

  if( pPt == NULL )
  {
    printf( "Memory allocation error\n" );
    return 1;
  }
  memset( pPt, 0, (sizeof(Point)) ); //ile bajtów alokujemy tyle zerujemy
  //pPt wskazuje na strukturę
  pPt->mX = 9;
  pPt->mY = -5;
  printf( "(%lf,%lf)\n", pPt->mX, pPt->mY );

  //---------------------------------------------------
  int t[MAX] = { 1,2 }; // nazwa tablicy jest wskaźnikiem, jest stały
  // ale jeżeli t weźmiemy przez parametr, który jest kopią
  printTab( t, MAX );

  int* pTab = ( int*)malloc(MAX*sizeof(int) ); //z lewej gwiazdka, sizeof bez gwiazdki
                                               //z lewej dwie gwiazdki, sizeof jedna
  if( !pTab ) {
    printf( "Memory allocation error : pTab\n" );
    return 2;
  }
  memset( pTab, 0, MAX*sizeof(int) );
  pTab[0] = 2;
  pTab[2] = -4;
  pTab[5] = 15;
  printf("\n");
  printTab( pTab, MAX) ;

  //zwalniamy pamięć
  free( pPt );
  free( pTab );
  return 0;
}

void printTab( int* pTab, int nSize ) {

  for(int i=0; i<nSize; i++)
    printf("%d ", *pTab++);      
}

//w przypadku continue!!
// for(int i=0; i<nSize; pTab++)
//  printf("%d ", *pTab++);


// *(pTab + i*sizeof(int))
// *(pTab+2) = 5; == pTab[2]