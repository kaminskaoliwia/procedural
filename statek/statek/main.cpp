/*==================
BACKTRACKING  algorytm z nawrotami
-------------
ogólny algorytm wyszukiwania wszystkich (lub kilku) rozwiązań niektórych problemów 
obliczeniowych, który stopniowo generuje kandydatów na rozwiązanie jednak, 
gdy stwierdzi, że znaleziony kandydat x nie może być poprawnym rozwiązaniem, 
nawraca (ang. "backtracks") do punktu, gdzie może podjąć inną decyzje 
związaną z jego budową
==============================*/
//! algorytm typu dziel i zwyciężąj = szybkie sortowanie
//! algorytmy dynamiczne = problem plecakowy

#define N 10//zdefini stale N i M - wymiary  (na 10)  tam gdzie main()
#define M 10
#define SHIP_DEPTH 5    // glebokosc zanurzenia okretu   tam gdzie main()
// #define LESSON
// #define OWNTEST

#include "statek.h"

int** CreateTab2D( int nCol, int nRow );  
void freeTab2D( int*** pTab );
void printMatrix( int** pTab, int pCol, int nRow );


int main(int argc, char* argv[])
{
  if( argc != 2 )//!!!!
  {
    printf( "Usage: %s <file_name>\n", argv[0] );
    return 1;
  }
   
  /*
  //!!argc
  //Wykreowac dynamicznie dwie tablice dwuwymiarowe (ogolnie moga byc rozne wymiary szerok i wysok)
  // kreowanie  druga metoda tworzenia dynamicznego tablic 2D

  // wyzerowac obie tablice (zaleznie czy bylo malloc czy calloc) 
  // wczytac dane (sprawdzic argc)  glebokosci 
  10 12 9 10 8 6 4 4 7 8
    10 12 9 10 8 4 5 6 6 5
    6 9  9  5 4 6 4 4 7 8
    ....
    // Jezeli nie znaleziono drogi od (0,0) do (N-1,M-1)- funkcja rekur root - wypisac
    // "** Nie ma mozliwosci doplynac do portu!!\n\n";

    // jesli ok to wypisac trase
    //zwolnic pamiec!! - w funkcji */
  int** pTab = CreateTab2D( N,M );
  int** pRoot = CreateTab2D( N,M );

  if( !pTab || !pRoot )
  {
    printf("ERROR: mem allocation!!" );
    freeTab2D( &pTab );
    freeTab2D( &pRoot );
    return 3;
  }

  if( !setTab( argv[1], pTab, N, M ) ) {
    printf( "ERROR: setTab!!" );
    return 2;
  }

  printf("\nWydruk kontrolny pTab:\n");
  printMatrix( pTab, N, M );


 /* if ( setTab(const_cast<char*>("macierz.txt"), pTab, N, M ) ) {
    printf("pTab:\n");
    printMatrix( pTab, N, M );
  } else {
    printf("ERROR: setTab\n");
    return 2;
  }
  */
  //printf("\npRoot:\n");
  //printMatrix( pRoot, N, M );

  int wynik = root( pTab, N, M, SHIP_DEPTH, 0, 0, pRoot, N-1, M-1 );
  if ( wynik )
  {
    printf("\nSciezka zostala znaleziona\n");
    printMatrix( pRoot, N, M );
  }
  else
  {
    printf("\nSciezka nie zostala znaleziona\n");
  }

  //printf("\nPo root:\n");
 // printMatrix( pRoot, N, M );
  
  freeTab2D( &pTab );
  freeTab2D( &pRoot );

#ifdef LESSON

  int** pTab = CreateTab2D( N, M );
  if( !pTab )
  {
    printf("ERROR: Memory allocation\n");
    return 1;
  }

  pTab[1][3] = 5;
  pTab[2][7] = 5;
  pTab[3][1] = 5;
  pTab[6][2] = 5;
  printMatrix( pTab, N, M );
  freeTab2D( &pTab );
#endif

#ifdef OWNTEST
  clearRoot( pRoot, N, M );
  int** pTabTest = CreateTab2D( 3,3 );
  int** pRootTest = CreateTab2D( 3,3 );
  int nDimTEST = 3;

  pTabTest[0][0] = 7;
  pTabTest[0][1] = 7;
  pTabTest[0][2] = 7;

  pTabTest[1][0] = 4;
  pTabTest[1][1] = 4;
  pTabTest[1][2] = 7;
  
  pTabTest[2][0] = 6;
  pTabTest[2][1] = 4;
  pTabTest[2][2] = 7;

  printf("\npTabTest:\n");
  printMatrix( pTabTest, nDimTEST, nDimTEST );
 
  printf("\npRootTest:\n");
  printMatrix( pRootTest, nDimTEST, nDimTEST );

  int x_startTEST = 0;
  int y_startTEST = 0;
  int x_destTEST = 2;
  int y_destTEST = 2;

  int wynikTEST = root(pTabTest, nDimTEST, nDimTEST, SHIP_DEPTH, x_startTEST, y_startTEST, pRootTest, x_destTEST, y_destTEST );
  if( wynikTEST )
  {
    printf("\nSciezka zostala znaleziona\n");
  }
  else
  {
    printf("\nSciezka nie zostala znaleziona\n");
  }

  printf("\nPo root:\n");
  printMatrix( pRootTest, nDimTEST, nDimTEST );

  freeTab2D( &pTabTest );
  freeTab2D( &pRootTest );

#endif

}
//==========================================================


int** CreateTab2D( int nCol, int nRow )  
{  
      int** p = (int**)calloc( nCol, sizeof(int*) );  //alokacja tablicy tablic
      if( !p ) return NULL;  
      p[0] = (int*)calloc( nCol*nRow, sizeof(int) );  // alokacja wszystkich wierszy naraz
      int* v = p[0];

      for( int i = 1; i<nRow; i++ ) // dowiązanie adresów wieszy
      {
        v += nCol;
        p[i] = v;
      }
      return p;  
}

void freeTab2D( int*** pTab )
{
  if( !pTab || !(*pTab) ) return;
  free((*pTab)[0]);  // zwolnic 0-owy elem tablicy 
  free(*pTab);       // zwolnic tablice tablic
  *pTab = NULL;  // wynulowac wskaznik
}

void printMatrix( int** pTab, int nCol, int nRow )
{
  if ( pTab == NULL )
  {
    printf("\nERROR: Tablica nie istnieje\n");
    return;
  }

  int *v = *pTab;
  for (int i =  0; i < nCol; i++) {
    for (int j = 0; j < nRow; j++) {
      printf("%3d ", *(v + i * nRow + j));
    }
    printf("\n");
  }
}