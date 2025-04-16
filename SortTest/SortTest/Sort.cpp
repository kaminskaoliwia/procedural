
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

void simpleSelection( int* tab, int nSize )
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

void bubbleSort( int* tab, int nSize )
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

void mixSort( int* tab, int nSize ) // cocktail sort - bubble sort "od dwóch stron"
{
	int start = 1; // pocz¹tek
	int end = nSize - 1; // koniec
	int last = nSize - 1; // ostatnia pozycja, na której nast¹pi³a zmiana
	do
	{
		for( int j = end; j >= start; j-- ) // przechodzimy od koñca do pocz¹tku
			if( tab[j - 1] > tab[j] ) // jeœli element po lewej wiêkszy - zamieniamy
			{
				int temp = tab[j - 1]; 
				tab[j - 1] = tab[j];
				tab[j] = temp;
				last = j; // zapamiêtujemy ostatnie miejsce
			}

		start = last + 1; // bo wczeœniejsze s¹ ju¿ posortowane
		
		for( int j = start; j < end; j++ ) // idziemy od pocz¹tku
			if( tab[j - 1] > tab[j] ) 
			{
				int temp = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = temp;
				last = j;
			}
		end = last - 1; // na koñcu jest ju¿ posortowane

	}while( start <= end ); // robimy dopóki dalej istnieje przedzia³
}

void halfSort( int* tab, int nSize )
{
	for( int i = 1; i < nSize; i++ ) // tab[0] traktujemy jako posortowany
	{
		int temp = tab[i]; // aktualna liczba której miejsca szukamy
		int l = 0; // zakres szukania
		int p = i - 1;

		while( l <= p )	// podobnie jak w wyszukiwaniu po³ówkowym
		{
			int m = ( l + p ) / 2;
			if( tab[m] > temp )
				p = m - 1;
			else
				l = m + 1;
		}

		for( int j = i - 1; j >= l; j-- ) // przesuwamy elementy wiêksze w prawo, aby wstawiæ temp
			tab[j + 1] = tab[j];

		tab[l] = temp; // wstawiamy temp
	}
}

void quickSort( int* tab, int nSize )
{
	sort( tab, 0, nSize - 1 ); // funkcja pomocnicza
}

void sort( int* tab, int start, int end )
{
	int i = start;
	int j = end;
	int pivot = tab[ ( start + end ) / 2 ]; // œrodek tablicy
	do
	{
		// szukamy elementow i - wiekszych, j - mniejszych
		while( tab[i++] < pivot ); 
		while( pivot < tab[j--] );
		// zamieniamy miejscami
		if( i <= j )
		{
			int w = tab[i];
			tab[i++] = tab[j];
			tab[j--] = w;
		}

	} while( j >= i ); // trwa dopóki siê nie przetn¹

	if( start < j ) sort( tab, start, j ); // rekurencyjnie sortujemy lew¹ czêœæ
	if( i < end ) sort( tab, i, end ); // rekurencyjnie sortujemy praw¹ czêœæ
}

void heapSort( int* tab, int nSize )
{
	int l = nSize / 2; // ostatni wêze³ (drugi tier) 
	int p = nSize - 1; // indeks ostatniego elem tab

	for( int i = l-1; i >= 0; i-- )
		update( i, p, tab ); // funkcja pomocniczna

	for( int i = p; i>0; i-- ) // po build maxHeap sortujemy
	{
		int temp = tab[0]; // najwiekszy element kopca zamieniamy z ostatnim
		tab[0] = tab[i];
		tab[i] = temp;
		update( 0, i-1, tab ); // nie bierzemy pod uwage juz najwiekszego elementu, zostal wyrzucony
	}
}

void update( int l, int p, int* tab )  // l - rodzic, p - ostatni elem kopca
{	
	// heapify - building max heap, szukanie najwiekszej wartosc na góre
	if( l==p ) return; // wêze³ nie ma dzieci
	int i = l; // i = l - parent
	int j = 2 * i + 1; // lewe dziecko wêz³a i w kopcu
	int temp = tab[i]; // wartoœæ rodzica
	
	while( j <= p ) // gdy dziecko <= rodzic
	{
		if( j < p ) // je¿eli dziecko < rodzic
			if( tab[j] <= tab[j + 1] ) //! pytanie czy mo¿na to j++ tu wstawiæ
				j++;	// wybieramy wiêksze dziecko = lewe lub prawe

		if( tab[j] < temp ) 
			break;	/* sprawdzamy czy wiêksze dziecko jest mniejsze od rodzica
			je¿eli tak to wszystko jest okej i koñczymy, je¿eli nie to musimy
			zamieniæ rodzica z dzieckiem */
		
		tab[i] = tab[j]; // zamieniamy dziecko z rodzicem
		i = j;	// nowy rodzic
		j = 2 * i + 1; // nowe lewe dziecko, prawe to 2*i+2
	}
	tab[i] = temp; // wstawiamy zapamiêtan¹ wartoœæ rodzica na jego nowe (je¿eli zamieniliœmy) miejsce
}