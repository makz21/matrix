#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <fstream>
#include "funkcje.h"

using namespace std;

int main(){
	Matrix A(3,3), B(3,3), C(3,3), D(3,3), E(3,3),F(3,3);
	C.Wczytaj("plik.txt");
	/*cout<<"Wartosc C: "<<endl<<C<<endl;
	D=C;
	cout<<D<<endl;
	if(D==C){
		cout<<"Macierze sa sobie rowne"<<endl;
	}
	else{
		cout<<"Macierze sa rozne"<<endl;
	}*/
	Wypelnij(A);
    Wypelnij(B);
    Wypelnij(E);

    cout<<"Wartosc  A"<<endl<<A<<endl;
    cout<<"Wartosc  B"<<endl<<B<<endl;
    A(2,2)=5;
    A=B=C;
	cout<<"Wartosc referencji: "<<A.getCref()<<endl<<endl;
    cout<<"Wartosc A po A(2,2)=5"<<endl<<A<<endl;
    try{
    	C=A*B;
	cout<<"Wartosc referencji: "<<C.getCref()<<endl<<endl;
    }
    catch(string w){
        cout<<"Wyjatek: "<<w<<endl;
    }
    cout<<"Wartosc  C=A*B"<<endl<<C<<endl;
	cout<<"Wartosc referencji: "<<C.getCref()<<endl<<endl;
    try{
    	D=A+B;
    }
    catch(string w){
        cout<<"Wyjatek: "<<w<<endl;
    }
    cout<<"Wartosc  D=A+B"<<endl<<D<<endl;
    try{
    	C+=A;
    }
    catch(string w){
        cout<<"Wyjatek: "<<w<<endl;
    }
    cout<<"Wartosc  B po C+=A"<<endl<<B<<endl;
    try{
   		B+=A;
    }
    catch(string w){
        cout<<"Wyjatek: "<<w<<endl;
    }    
    cout<<"Wartosc  B+=A"<<endl<<B<<endl;
    cout<<"Wartosc referencji: "<<B.getCref()<<endl<<endl;
    try{
    	A*=B;
    }
    catch(string w){
        cout<<"Wyjatek: "<<w<<endl;
    }
    cout<<"A*=B:"<<endl<<A<<endl;
	cout<<"Wartosc referencji: "<<A.getCref()<<endl<<endl;
	return 0;
}
