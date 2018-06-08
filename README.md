# polynneal

**Domaći zadatak 2 iz GA**

## Instrukcije za kompajliranje

Za kompajliranje rešenja potreban je CMake, kao i sledeće biblioteke instalirane
na sistemu:

* **CGAL** (za geometriju)
* **GMP** (zahteva ga CGAL)
* **MPFR** (zahteva ga CGAL)
* **SFML** (za grafiku)

Na Unix-baziranim sistemima, dovoljno je napraviti direktorijum za *build*
fajlove i unutra pozvati CMake da kreira `Makefile` a zatim pozvati `make`:

```
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
```

Na Windows sistemima može se koristiti CMake GUI alat koji je potrebno uputiti na
putanje do ovog direktorijuma i eventualno na putanje do gorepomenutih biblioteki
ukoliko CMake bude imao teškoća da ih nađe. Nakon toga, CMake može generisati
*build* fajlove za više sistema, npr. može se generisati Visual Studio projekat.

## Instrukcije za pokretanje

## Ručno pokretanje

Finalni izvršni fajl prima sledeće argumente na komandnoj liniji, sledećim
redosledom:

1. **Broj pokretanja**. Koliko puta pokrenuti algoritam.
2. **Faktor hlađenja**. Konstanta sa kojom se množi temperatura svake iteracije.
   Uglavnom je ovaj broj blizu ali ne i jednak 1. Ukoliko se promeni broj
   iteracija ili inicijalna temperatura, potrebno je promeniti i ovaj parametar
   kako bi se održao sličan tempo hlađenja.
3. **Inicijalna temperatura**. Vrednost temperature sa kojom se počinje.
4. **Broj iteracija**. Koliko puta izvršiti korak simuliranog kaljenja.
5. *opciono* **Flag za CSV izlaz**. Ukoliko je ovaj parametar jednak `csv`, na
   standardni izlaz će biti ispisan izveštaj u CSV formatu koji daje trenutnu i
   najbolju površinu kao i temperaturu na svakih 100 iteracija.
6. *opciono* **PNG filename prefiks**. Ako ovaj parametar postoji, smatraće se da je
   to prefiks na koji treba dodati nastavke za svako pokretanje kako bi se dobila
   putanja u koju će se snimiti PNG slika finalnog stanja algoritma. Nastavak
   koji se dodaje je oblika `_i.png`, gde je `i` broj pokretanja (počevši od 1).

Nakon pokretanja, na standardni izlaz za greške biće ispisan napredak algoritma,
kao i finalno rešenje kada algoritam završi. Na ekranu će biti prikazan prozor sa
trenutnim stanjem algoritma. Plavi poligon predstavlja trenutno stanje, dok
žuti poligon predstavlja globalno najbolje stanje pronađeno u toku algoritma.

### Automatsko pokretanje na test primerima

Za Unix sisteme postoje i korisne skripte `generate-reports.bash` i
`generate-graphs.bash`. Prva će pokrenuti program 5 puta za svaki test primer i
ispisati CSV izveštaje i PNG fajlove u `reports` poddirektorijum, dok će druga
pokrenuti `graphs/exhibit.py` Python skriptu koja generiše grafove (pozvati je sa
parametrom `-h` za pregled korišćenja ove skripte).

