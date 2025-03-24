Temat:  POROWNANIE CZASOW SORTOWAN
-----------------------------------

1. ZDEFINIOWANY MODUL z funkcjami sortujacymi
 - wstawianie   simpleInsertion()
 - wybieranie   simpleSelection()
 - babelkowe    bubbleSort()
 - mieszane (bablekowe)
 - polowkowe (modyfikacja wstawiania o wyszukiwanie polowkowe)
 - stogowe (HeapSort)
 - szybkie  (QuickSort)

 W naglowku (Sort.h) - tylko naglowki funckji sortujacych 
 W .cpp implementacje sortowan oraz dodatkowych funkcji (naglowki definiowane na gorze)

 2. w pliku z main() zdefiniowac typ wskaznikowy na funkcje sortujace !!
 3. w main() zdefiniowac lokalna tablice pSortTab (bez rozmiaru - []) i zainicjowana
    od razu na adresy funkcji sortujacych (nazwy)
 4. w main() zdefiniowac tablice napisow - nazw tych sortowan (do wypisywania)

 5. Zainicjowac losowo dynamicznie stworzona tablice wzorcowa o rozmiarze przekazanym przez 
    parametr fun main(), ktora bedzie kopiowana (memcpy() -<memory.h>) przed kazdym sortowaniem
    do tablicy sortowanej i w petli sortowac ja  i wypisac nazwe sortowania i ile czasu zajmuje.
    Do pomiaru czasu tylko jedna zmienna (czas przed rozpoczeciem sortowania)
    Oczywiscie sortowania sa wywolywane poprzez tablice adresow do funkcji!!!!

 6. Tablice tworzone dynamicznie!! (malloc(), memset())

 7. Wielkosc tablicy jest wczytywana z parametrow main() (argv[1] bedzie stringiem wiec trzbea przekonwetowac 
    do liczby int - atoi())

 8. Dla testow nalezy na warunkowej kopilacji wypisac np pierwzych 50 elementow (po 10 w linii) - funkcja
    Testowo (warunk kompil) wypisac przed i po sortow - testowac dla malych tablic np 20 elem 
    - czy samo sortowanie dziala


  
