
//przyklad funkcji o zmiennej liczbie parametrow

#include <stdio.h>
#include <stdarg.h> // !!!!!!!!!

// funkcja nie musi byc int, zalezy od przykladow - tutaj int bo sumujemy parametry
int sum( int nFirst, ... ); //!!!!!!!!
//nFirst tutaj jest iloscia parametrow dalej w wywolaniu funkcji (WINDOWS)
// nFirst nie musi byc int, ale musi sie dac wyliczyc na podstawie nFirst 
// ile dalej jest parametrow

// ta sama nazwa z przyrostkiem V
int sumV( int nFirst, va_list args ); // !!!!!!!
// va_list jest zdefiniowane w pliku nag³ówkowym, typ zmiennej

int main()
{
  int res = sum( 8, 1, 2, 3, 4, 5, 6, 7, 8 ); // za 8 jest osiem parametrow
  printf("res = %d\n", res);
  res = sum( 4, 1, 2, 3, 4 );
  printf("res = %d\n", res);
  return 0;
}

int sum( int nFirst, ... )  {
  va_list args; // pointer to the variable argument     // !!!!!!!
  va_start( args, nFirst );                             // !!!!!!!

  int ret_val = sumV( nFirst, args );                   // !!!!!!! byc moze bez int-a
  va_end( args ); // reset variable arguments           // !!!!!!!

  return ret_val;
}

int sumV( int nFirst, va_list args )  {
  int sum = 0;
  for( int i = 0; i<nFirst; i++ ) {
    sum+= va_arg(args,int);                            // !!!!!!!
  } // wyciagamy argumenty po kolei

  return sum;
}

// zad dom - printf
// kazdy case ma miec break - przy kazdym case wywolujemy funkcje 
// va_arg trzeba uzyc d - int, c - char itp 
// wydrukowac c
// w OutDouble uzyc petli for, najlepiej z jedna instrukcja