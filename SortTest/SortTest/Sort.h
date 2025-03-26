
// W naglowku (Sort.h) - tylko naglowki funckji sortujacych

#ifndef  _SORT_H
#define _SORT_H

void simpleInsertion( int* tab, int nSize );
void simpleSelection( int* tab, int nSize );
void bubbleSort( int* tab, int nSize );
void mixSort( int* tab, int nSize );
void halfSort( int* tab, int nSize );
void quickSort( int* tab, int nSize );
void heapSort( int* tab, int nSize );
void sort( int* tab, int l, int p );
void update( int l, int p, int* tab );

#endif