
#include "Sort.h"

void simpleInsertion( int* tab, int nSize )
{
	for( int i = 1; i < nSize; i++ )
	{
		int temp = tab[i];
		int j = i - 1;

		while( tab[j] > temp && j>=0 )
			tab[j + 1] = tab[j--];

		tab[j + 1] = temp;
	}  
}

void simpleSelection()
{
	for( int i = 0; i < nSize - 1; i++ )
	{
		int k = i;
		int temp = tab[i];
		for( int j = i + 1; j < nSize; j++ )
			if( tab[j] < temp )
			{
				k = j;
				temp = tab[j];
			}
		tab[k] = tab[i];
		tab[i] = temp;
	}
}

void bubbleSort()
{
	for( int i = 1; i < nSize; i++ )
		for( int j = nSize - 1; j >= i; j-- )
			if( tab[j - 1] > tab[j] )
			{
				int temp = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = temp;
			}
}