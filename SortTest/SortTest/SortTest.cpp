
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define PARAMNO 3
#define MAX 50
#define NL 10

/*2. w pliku z main() zdefiniowac typ wskaznikowy na funkcje sortujace !! typedef int (*pFType)()
3. w main() zdefiniowac lokalna tablice pSortTab (bez rozmiaru - []) i zainicjowana
od razu na adresy funkcji sortujacych (nazwy)
4. w main() zdefiniowac tablice napisow - nazw tych sortowan (do wypisywania)
*/

void initTab( int* pTab, int nSize );
void printTab( int* pTab, int nSize );
int createTab( int**, int );

// argc - rozmiar tablicy argV >= 1
// argV[0] zawsze jest nazwa programu, elem argV sa stringi (lancuchy znakowe)
int main( int argc, char* argv[] )
{ 
  //sprawdzic parametry
  //obliczyc rozmiar tablicy

  //alokacja tablicy wzorcowej i jej zainicjowanie (funkje)

  // wydruk na warunkowej kompil


  //----------odczytac czasy poszczegolnych sortowan

  // alokacja pamieci na tabl do sortow
  // obliczyc rozmiar tablicy adresoww funkcji

  //TO W PETLI for
  // wkopiowanie do niej tabl wzorcowej

  // -- odczytac czas  clock()
  // -- posortowac
  // -- odczytac czas i wypisac czas sortowania (wzor w helpach), wypisac nazwe srtowania
  // -- na warunkowej kompilacji wydruk posortowanej

  // zwolnic pamiec

  return 0;
}

int createTab( int** pTab, int nSize )
{
  *pTab = (int*)malloc( nSize*sizeof(int) );
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
    if(((i+1) % NL) == 0) printf("\n");  
  }
}

void initTab( int* pTab, int nSize ) 
{
  srand((unsigned int)time(NULL));
  for( int i=0;i< nSize; i++ )
  {
    *pTab = rand() % nSize;
  }
}