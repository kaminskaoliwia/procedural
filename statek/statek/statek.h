
#ifndef STATEK_H
#define STATEK_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int move( int** pTab, int nRow, int nCol, int nDepth, 
  int move, int x, int y, int* px, int* py, int** pRoot );

/* pTab - tablica okreslajaca glebokosc w kazdym kwadracie
nRow, nCol - rozmiar pTab, 
nDepth - glebokosc zanurzenia statku 
move - kierunek ruchu (wart typu wylicz)
//! od zero do rozmiar - 1
x, y - indeksy w tablicy skad wykonujemy kolejny ruch np. zaczynamy od 0,0
px, py - nowe wspolrzedne  (parametry WYJŒCIOWE)
pRoot - tablica pamietajaca ruchy o rozm nRow, nCol
*/

//! zrobiæ switcha i obliczaæ: gdy idziemy do góry to x-1!!!! w jednej linijce
int root( int** pTab, int nRow, int nCol, int nDepth,  
  int x, int y, int** pRoot, int x_dest, int y_dest  );   //--- rekurencyja
/* pTab tabl glebokosci   o romiarze nRow  i nCol
dDepth - glebokosc zanurzenia statku (!)
x, y - wspolrzedne skad robimy kolejny ruch
pRoot tablica kolejnych ruchow (w pole wstawia sie numer kolejnego ruchu)
x_dest, y_dest - wsporzedne portu
*/


void clearRoot( int** pRoot, int nRow, int nCol );
// zeruje tablice  

int setTab( char* sFile, int** pTab, int nRow, int nCol ); 
// wczytuje dane z pliku
// sFile -  nazwa pliku wejsciowego - parametr main()
// pTab  - tablica glebokosci morza
// param: nRow, nCol wymiary tablicy glebokosci morza
// w razie niepowodzenia otwarcia pliku do odczytu zwraca 0 
// else 1

#endif