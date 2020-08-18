#include <stdio.h>
#include<cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>//losowanie
#include <ctime>
//nie dziala obsluga bledow oraz loswanie bez powtorzen
using namespace std;



class  zrobtest{


private:

  const char drk ='#';
  int ile_odpowiedzi=4;
  char plikwejsciowy[50]="bazatestu.txt"; //plik z baza testu
  char plikwyjsciowy[50]="nowytest.txt"; // plik wyjsciowy
  fstream mojStrumien; //  deskryptor pliku mozna tez zmienic na ifstream
  fstream plikw;//deskryptor pliku wyjsciowego

  string zdanie="";
  string Spytanie[10],Spoprawna[10],Sniepoprawna[10];
  char Znak;
  int pytanie=0;int poprawne=0; int niepoprawne=0;
  string wczytanadrk,tytul;
  char drkbyla='1';
  bool powtorzlos=false;
  int wylosowana,wylosowanapoprawna,wylosowananiepoprawna[10];
  string dozapisu="Nowy test";
  int Nrpytania=1;
  string odp="";
//metody
   int wylosuj(int dana);

public:
 bool zakonczprogram=false;
//metody
zrobtest(void);
~zrobtest(void);
void ustawgenerator();//ninapisna
void wykonujetest();

}; //-------------------koniec definicji kasy------------------
zrobtest::zrobtest(void){
cout <<"konstruktor"<<endl;
do{
mojStrumien.open(plikwejsciowy , std::ios::in );
//ifstream mojStrumien("tescik.txt"); //rownowazne deklaracje dostepu do pliku
if (mojStrumien.fail() ){cout <<"blad otwarcia pliku wejsciowego: "<<plikwejsciowy<<endl<<" wcisnij 'x' by zakonczyc lub podaj nazwe pliku wejsciowego: "<<flush;
                         cin >>plikwejsciowy;}
if ( strcmp(plikwejsciowy,"x")==0){ zakonczprogram=true; return ;}

}while  (mojStrumien.fail() );

plikw.open( plikwyjsciowy, std::ios::out );


}
zrobtest::~zrobtest(void){
cout <<"destruktor"<<endl;

 plikw.close();
    mojStrumien.close();

}
//losowanie
int zrobtest::wylosuj (int dana)
{
 return (( std::rand() % dana )+1 );
}
//glowna metoda
void zrobtest::wykonujetest(){  //przeslij jeszcze deskryptor pliku
 while( !mojStrumien.eof() ){//az osiagnie koniec pliku wtedy nie odczytuje i wypisuje

       mojStrumien.get(Znak);

     if (Znak==drk)  {


        mojStrumien>>wczytanadrk; //wczytaj caly wyraz dyrektyw
        //zapamietaj wszystkie warianty pytan
        if(drkbyla=='s'){ tytul=zdanie;  }
        if(drkbyla=='q'){ Spytanie[pytanie]=zdanie;cout<<Spytanie[pytanie];}
        if(drkbyla=='p'){ Spoprawna[poprawne]=zdanie;cout<<Spoprawna[poprawne];}
        if(drkbyla=='n'){ Sniepoprawna[niepoprawne]=zdanie;cout<<Sniepoprawna[niepoprawne];}
        if(drkbyla=='c'){  }
        if(drkbyla=='s'){dozapisu=tytul;plikw.write( &dozapisu[0],dozapisu.length() );
             }
        if ( (wczytanadrk[0]=='q'|| wczytanadrk[0]=='e')&& (drkbyla =='n'||drkbyla=='p')) {

        {
            wylosowana= wylosuj(pytanie);
            cout<<"zapissss: " <<" pyt "<<pytanie<<" wyl "<<wylosowana<<Spytanie[wylosowana]<<" * ";
            plikw<<endl<<Nrpytania<<")" <<Spytanie[wylosowana]<<endl;
            Nrpytania++;


          if(niepoprawne<3)cout<<"za malo negatywnych odpowiedzi w pytaniu: "<<pytanie;
          if (poprawne==0) cout<< "za malo poprawnych odpowiedzi w pytaniu: "<<pytanie;
           //losujemy odpowiedzi
           wylosowanapoprawna = wylosuj(4);

          for (int k=1;k<=ile_odpowiedzi;k++){
            switch (k){
            case 1 : odp = "a)";break;
            case 2 : odp =  "b)";break;
            case 3 : odp = "c)";break;
            case 4 : odp = "d)";break;}
            if (k==wylosowanapoprawna) {plikw<<odp<< Spoprawna[wylosuj(poprawne)];wylosowananiepoprawna[k]=-1;}

            else
            {

   //niepoprawne odpowiedzi bez powtorzen

                do{
                wylosowananiepoprawna[k]=wylosuj(niepoprawne);

                powtorzlos=false;
                for (int i=1;i<k;i++)
                {

                if (wylosowananiepoprawna[i]== wylosowananiepoprawna[k]){powtorzlos=true;}

                }


                }while(powtorzlos==true);
                plikw<< odp<<Sniepoprawna[wylosowananiepoprawna[k]]; //zapisz niepoprawna
            }
          }

            pytanie=0;poprawne=0;niepoprawne=0;//albo wszyskie 1 chyba pytanie=1
}
         }

       cout <<"byla"<<drkbyla;
       drkbyla=wczytanadrk[0];;

       cout<<"  #:"<<wczytanadrk<<" ";//Spytanie[pytanie];;//pobieramy i co robimy
       zdanie="";//wymaz poprzednie zdanie


      if (wczytanadrk[0]=='q') { pytanie++; }
      if (wczytanadrk[0]=='p') { poprawne++;}
      if (wczytanadrk[0]=='n') { niepoprawne++;}

                                       // pytanie=0;poprawne=0;niepoprawne=0;inst=false; cout<<"tur";

     }
     else{

        zdanie =zdanie+Znak;

        }

  }



}
//ustawianie generatora
void zrobtest::ustawgenerator(){
srand( time( NULL ) );//ustaw generator losowy
}


int main (){

zrobtest zrobietescik; //tworzymy obiekt klasy

zrobietescik.ustawgenerator();//ustawiamy generator licvzb pseudolosowych
if (zrobietescik.zakonczprogram==false )zrobietescik.wykonujetest(); //jezeli udalo sie znalezc baze testu wykonaj nowy test

  return 0;
}







/*

https://www.geeksforgeeks.org/5-different-methods-find-length-string-c/
ofstream

This data type represents the output file stream and is used to create files and to write information to files.
2

ifstream

This data type represents the input file stream and is used to read information from files.
3

fstream

This data type represents the file stream generally, and has the capabilities of both ofstream and ifstream which means it can create files, write information to files, and read information from files.

https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm

http://cpp0x.pl/kursy/Kurs-C++/Obsluga-plikow/305

*/
