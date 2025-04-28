
#include <stdio.h>
#include <stdlib.h> // malloc calloc free
#include <memory.h> // memset

double* createTab_m( int nSize ); // m - malloc
double* createTab_c( int nSize ); // c - calloc

int main()
{
    double *pTab = createTab_c( 10 );
    pTab[0] = 12.345;
    pTab[1] = -434.989;
    free( pTab );
    return 0;
}

double* createTab_m( int nSize )
{
    double* p = (double*)malloc( nSize * sizeof(double) );
    if( !p ) return NULL; // do wskaznikow NULL
    memset( p, 0, nSize * sizeof(double) );
    return p;
}

double* createTab_c( int nSize )
{
  return (double*)calloc( nSize, sizeof(double) ); // calloc(ilosc elem tablicy, rozmiar)
// zwraca p albo nie p 
}

// jednym wyra¿eniem pytajnikowym return maxsize currentsize, warunek w nawiasach!
