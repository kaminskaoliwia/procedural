// ParamFunMain.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define PARAMNO 3
#define MAX 10

int createTab( int** pTab, int nSize );
void printTab( int* pTab, int nSize ); // int pTab[]

// argc - rozmiar tablicy argV >= 1
// argV[0] zawsze jest nazwa programu, elem argV s¹ stringi (³añcuchy znakowe)
int main( int argc, char* argv[] ) // zwyczajowa nazwa
{
  if( argc != PARAMNO )
  {
    printf("Usage: %s <tab_size> <file_name>\n", argv[0] );
    return 1; // u¿yæ unikalnej wartoœci != 0
  }

  int nSize = atoi( argv[1] ); //funkcja bibl konwertujaca str do int
  printf("nSize = %d\n", nSize);

  //zdefiniowac tab int dynamicznie
  int* pTab = NULL;
  if(!createTab( &pTab, nSize ) )
  {
    printf( "Memory allocation error!!\n" );
    return 2;
  }

  FILE* fin = NULL; // uchwyt pliku
  if( ( fin=fopen(argv[2], "rt" ) ) == NULL ) // "rt" t - domyslnie
  {
    printf( "Error open input file %s\n", argv[2] );
    return 3;
  }

  int* v = pTab;
  for( int i=0; i<nSize; i++ )
  {
    // scanf( "%d", &(pTab[i]) ); //czytanie z klawiatury czyli z stdin
    // fscanf( fin,"%d", &(pTab[i]) );
    fscanf( fin,"%d", v++ );
  }

  printTab( pTab, nSize );

  free( pTab );
  fclose( fin );
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
    if(((i+1) % MAX) == 0) printf("\n");  
  }
}

