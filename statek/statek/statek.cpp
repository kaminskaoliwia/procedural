
#include <stdio.h>
#include <stdlib.h>
#include "statek.h"
#include <corecrt_memory.h>

//! zdefiniowac typ wyliczeniowy: kierunki ruchu : UP RIGHT DOWN LEFT  (wartosci kolejne od 0)
typedef enum { UP, RIGHT, DOWN, LEFT } moves;


//-------------------------------------------------------------
int move( int** pTab, int nRow, int nCol, int nDepth, int moves,
  int x, int y, int* px, int* py, int** pRoot ) { 
  // x  y - wsporzedne skad robimy nowy ruch
  // wykonac kolejny ruch w kierunku move obliczajac nowe wspolrzedne *px *py
  
  switch ( moves ) 
  {
    case UP: *px-=1; *py = y; break;
    case RIGHT: *px=x; *py+=1; break;
    case DOWN: *px+=1; *py=y; break;
    case LEFT: *px=x; *py-=1; break;
  }
  // sprawdzic czy nowe indeksy *px i *py sa w zakresie indeksow tablicy
  if (*px < 0 || *px >= nRow || *py < 0 || *py >= nCol) return 0;

  // a nastepnie sprawdzic warunek czy nie jest za plytko ">nDepth " oraz
  if ( pTab[*px][*py] < nDepth ) return 0;
  if( pRoot[*px][*py] != 0 ) return 0;

  //  jesli wszystkie warunki poprawne to zwracamy 1
  //    else 0
  return 1;
}   

//----------------------------------------------------------------------------------
int root( int** pTab, int nRow, int nCol, int nDepth,  int x, int y, int** pRoot,
  int x_dest, int y_dest )
{  
  // tabl pRoot pamieta droge   -   numer ruchu pole przez ktore odwiedzono (plynie statek) 
  //                                0 pole nie odwiedzone
  // wstawic do tablicy pRoot kolejny numer ruchu
  static int n = 1;
  pRoot[x][y] = n++;

  
  if( x == x_dest && y == y_dest ) // statek dotarl do portu
    return 1;
  int x_new = 0;
  int y_new = 0;

  //! sprwadzic wszystkie mozliwosci ruchu
for (int dir = UP; dir <= LEFT; ++dir) {
    // zdefiniowac nowe wspolrzedne (zmienne lokalne xnew, ynew) 
 
     if (move(pTab, nRow, nCol, nDepth, dir, x, y, &x_new, &y_new, pRoot)) {
        // zwiêkszamy iloœæ ruchów
       if (root(pTab, nRow, nCol, nDepth, x_new, y_new, pRoot, x_dest, y_dest))   
         //jesli wykonanie kolejnego kroku sie powiodlo - rekurencyjnie root()
       {
         return 1; // sukces
                   // jesli ruch jest mozliwy w zadanym kierunku 

       }
       
       --n; //! porazka = backtracking
       pRoot[x][y] = 0;      // jesli wracamy to ustawiamy w pRoot ze ruch byl zly

     }
   }
  return 0;
}   


void clearRoot( int** pRoot, int nRow, int nCol )
{
  memset( *pRoot, 0, nRow*nCol*sizeof(int) );
}

int setTab( char* sFile, int** pTab, int nRow, int nCol )
{
  FILE* file = NULL; // uchwyt pliku
  if( ( ( file = fopen( sFile, "r" ) ) == NULL ) ) return 0;

  for( int i = 0; i < nRow; i++ )
  {
    int* v = *pTab++; // sposób wskaŸnikowy podany w projekcie Macierzy
    for( int j = 0; j < nCol; j++ )
    {
      if( fscanf( file, "%d", v++ ) == EOF )
      {
        fclose( file );
        return 0; 
      }
    }
  }
  fclose(file);
  return 1;
}