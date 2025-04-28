
#include "Sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <stdlib.h>

#define DEBUG
#define PARAMNO 2
#define DEBUGMAX 50
#define NL 10

//done 2. w pliku z main() zdefiniowac typ wskaznikowy na funkcje sortujace !! typedef int (*pFType)()
//done 3. w main() zdefiniowac lokalna tablice pSortTab (bez rozmiaru - []) i zainicjowana od razu na adresy funkcji sortujacych (nazwy)
//done 4. w main() zdefiniowac tablice napisow - nazw tych sortowan (do wypisywania)

void initTab( int* pTab, int nSize );
void printTab( int* pTab, int nSize );
int createTab( int**, int );

typedef void ( *pFType)(int*, int ); //! wskaŸnik do tablicy przyjmuj¹cej int* tablicê oraz int rozmiar


// argc - rozmiar tablicy argV >= 1
//! argV[0] zawsze jest nazwa programu, elem argV sa stringi (lancuchy znakowe)
int main( int argc, char* argv[] )
{ 
  //sprawdzic parametry
  if( argc != PARAMNO ) //musz¹ byæ 2 - nazwa + size
  {
    printf( "Usage: %s <Size of table>\n", argv[0] );
    return 1;
  }
  
  //obliczyc rozmiar tablicy
  int tabsize = atoi( argv[1] );

  //alokacja tablicy wzorcowej i jej zainicjowanie (funkje)
  int* pTab = NULL;
  if( !createTab( &pTab, tabsize ) )  {
    printf( "Memory allocation error! - pTab\n" );
    return 2;
  }

  initTab( pTab, tabsize );

  
  pFType pSortTab[] = {simpleInsertion, bubbleSort, simpleSelection, mixSort, heapSort, quickSort, halfSort}; //tablica wskaŸników
  const char* tabNames[] = {"simpleInsertion", "bubbleSort", "simpleSelection", "mixSort", "heapSort", "quickSort", "halfSort"};

  //! wydruk na warunkowej kompil
  // Dla testow nalezy na warunkowej kopilacji wypisac np pierwzych 50 elementow (po 10 w linii)
  // funkcja Testowo (warunk kompil) wypisac przed i po sortow - testowac dla malych tablic np 20 elem - czy samo sortowanie dziala

#ifdef DEBUG
  printf( "Tab before sort:\n" );
  //int temp;
 // if( tabsize < DEBUGMAX ) temp = tabsize; else temp = DEBUGMAX;
  printTab(pTab, ( tabsize < DEBUGMAX )? tabsize: DEBUGMAX );
#endif // DEBUG


  //----------odczytac czasy poszczegolnych sortowan

  //! alokacja pamieci na tabl do sortow
  int* pCpTab = NULL;
  if( !createTab( &pCpTab, tabsize ) )
  {
    printf( "Memory allocation error! - pCpTable" );
    return 3;
  }
  
  // obliczyc rozmiar tablicy adresow funkcji
  int iterations = sizeof( pSortTab )/sizeof( pFType ); //!wielkoœæ tablicy/wielkoœæ elementów
  
  /* 5. Zainicjowac losowo dynamicznie stworzona tablice wzorcowa o rozmiarze przekazanym przez 
    parametr fun main(), ktora bedzie kopiowana (memcpy() -<memory.h>) przed kazdym sortowaniem
    do tablicy sortowanej i w petli sortowac ja  i wypisac nazwe sortowania i ile czasu zajmuje.
    Do pomiaru czasu tylko jedna zmienna (czas przed rozpoczeciem sortowania)
    Oczywiscie sortowania sa wywolywane poprzez tablice adresow do funkcji!!!!*/

  //TO W PETLI for
  // wkopiowanie do niej tabl wzorcowej
  for ( int i = 0; i <iterations; i++ ) 
  {
    memcpy( pCpTab, pTab, sizeof(int)*tabsize ); 

  // -- odczytac czas  clock()
  clock_t start = clock();
  // -- posortowac
  pSortTab[i]( pCpTab, tabsize );
  // -- odczytac czas i wypisac czas sortowania (wzor w helpach), wypisac nazwe srtowania
  clock_t end = clock();
  printf( "\nMetoda: %s, czas: %lf sekund, %0.2lf milisekund\n", 
    tabNames[i], (double)( end - start ) / CLOCKS_PER_SEC, (double)( end - start ) / CLOCKS_PER_SEC * 1000  );
  //! lub ((clock_t)1000) i ((clock_t)1000) * 1000)
  
  // -- na warunkowej kompilacji wydruk posortowanej
#ifdef DEBUG
  printf( "Tab after sort:\n" );
  printTab( pCpTab,  ( tabsize < DEBUGMAX )? tabsize: DEBUGMAX );
#endif
  }
  // zwolnic pamiec
  free( pTab );
  return 0;
}

int createTab( int** pTab, int nSize )
{
  *pTab = ( int*)malloc( nSize*sizeof(int) );
  if( !*pTab ) // if( *pTab = NULL )
    return 0;
  // wyzerowac tablice, do tego nigdy nie uzywac petli (np for)
  memset( *pTab, 0, nSize*sizeof(int) );
  return 1;
}

void printTab( int* pTab, int nSize )
{
  for( int i=0; i<nSize; i++ /*, pTab++*/)
  {
    printf("%d ", *pTab++ ); //co 10 linie nl  // *( pTab + i*sizeof(int) );
    if( ((i+1) % NL) == 0 ) printf( "\n" );  
  }
}

void initTab( int* pTab, int nSize ) 
{
  srand( (unsigned int)time(NULL) );
  for( int i=0;i< nSize; i++ )
  {
    pTab[i] = rand() % nSize;
  }
}