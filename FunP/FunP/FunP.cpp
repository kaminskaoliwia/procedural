// FunP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define FUN_PTR_TYPE // trik do zakomentowywania, warunkowa kompilacja

int f1();
int f2();

int* fun1( int i );
int* fun2( int i );

int tab[] = { 10, 20, 30, 40, 50, 60, 70 };

int main()
{
#ifdef FUN_PTR_TYPE
  typedef int (*pFType)(); //pfType = nazwa TYPU wskaznikowego do funkcji bezparam zwracaj int
  typedef int* (*pFuntype)( int );
  pFType pf = f2;
  pFuntype pFun = fun1;

#else
  int (*pf)() = f2; // wskaŸnik do funkcji która zwraca int, mo¿na daæ &f2, nazwa funkcji to jej adres
  int* (*pFun)(int) = fun1; //pf to wsk do funkcji bezparametrowej zwracajacej int 
  //pfun to wsk do funkcji z parametrem int zwracajacym int*
#endif
  printf( "f2() = %d   fun1(2) = %d\n", pf(), *pFun( 2 ) ); //musimy wy³uskaæ int z int*
  printf( "&tab[3] = %x   pFun( 2 ) = %x\n\n", &(tab[3]), pFun(2));  
  return 0;
}

int f1()
{
  return 1;
}

int f2()
{
  return 2;
}

int* fun1( int i )
{
  return tab+i+1; //i>=6 blad po adr poza tab
}

int* fun2( int i )
{
  return tab+i+2;

}
