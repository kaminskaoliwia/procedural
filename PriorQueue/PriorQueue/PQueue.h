
#include "global.h"

#define PRIOR_ERROR 
#define POS_ERROR -1

typedef struct    // zachowac oryginalne nazwy!!!!!!  
{
    PQINFO*  pInfo;       // Ptr to user info  
    int nPrior;           // prior value (int) for the user info 

} PQItem;         // type of the queue item


typedef struct   // zachowac oryginalne nazwy!!!!!!
{
    PQItem** pPQueue;     // kolejka realizowana w postaci stogu  (dynamiczna tablica)
    int PQSize;           // rozmiar calkowity kolejki priorytetowej
    int nPQCurrSize;      // ilosc elelemntow w kolejce (jednoczensie indeks pierwszego wolnego miejsc w kolejce) 

} PQueue;


// kreuje kolejke o zadanym rozmiarze i zwraca wskaznik do niej lub NULL gdy blad
PQueue* PQInit( int nSize );     

// zwraca 0 lub 1 - kolejka pusta/nie pusta
int PQisEmpty( PQueue* q );  

// zwraca ilosc elementow w kolejce
int PQSize( PQueue* q );     

// zwraca najwiekszy priorytet w kolejce (z zerowej pozycji) lub PRIOR_ERROR
int PQMaxPrior( PQueue* q ); 

// wstawia do kolejki informacje o zadanym priorytecie, zwraca 0 (niepowodzenie) lub 1 (powodzenie)
int PQEnqueue( PQueue* q, PQINFO* pInfo, int nPrior );

// zwraca informacje o najwyzszym priorytecie lub NULL gdy niepowodzenie
PQINFO* PQDequeue( PQueue* q );  

// czysci cala kolejke zwalniajac pamiec alokowana przez uzytkownika (na info), nie znana struktura do zwolnienia 
// dlatego przekazac trzeba funkcje uzytkownika do zwolnienia pamieci przez parametr 
void PQClear( PQueue* q, void( __cdecl* FreeInfo )( const void* )  );

// Corrected declaration of PQClear function
void PQClear(PQueue* q, void(__cdecl* FreeInfo)(const void*));
             
// zwraca w parametrze we-wy NULL (kolejka) usuwaj�c wszyskto wczesniej (czyszczenie kolejki)
void PQRelease( PQueue** q, void( __cdecl* FreeInfo )( const void* ) );

// drukuje w porzadku preorder (rekurencyjnie) od zadanej pozycji, aby wydrukowa� info uzytkownika przekazac 
// trzeba funkcje drukujaca ta informacje. Dodatkowo, drukuje priorytet w okraglych nawiasach oraz pozycje w 
// kolejce w kwadratowych nawiasach
void PQPrint( PQueue* q, void(__cdecl* PrintInfo)(const void* ), int nRoot );
