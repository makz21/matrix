#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "funkcje.h"

using namespace std;

Matrix::rcMatrix::rcMatrix(){
    row=0;
    column=0;
    wsk=NULL;
    cref=1;
}

Matrix::rcMatrix::rcMatrix(unsigned int wiersz, unsigned int kolumna){
    cref=1;    
    row=wiersz;
    column=kolumna;
    wsk=new double*[wiersz];
    for(unsigned int i=0;i<wiersz;i++){
        wsk[i]=new double[kolumna];
    }
}

Matrix::rcMatrix::~rcMatrix(){
    for(unsigned int i=0;i<row;i++){
        delete [] wsk[i];
    }
    delete [] wsk;
    wsk=NULL;
}

Matrix::rcMatrix *Matrix::rcMatrix::detach(){
	rcMatrix *pointer;
	if(cref==1){
		return this;
	}
	pointer=new rcMatrix(row,column);
	for(unsigned i=0;i<row;i++){
		for(unsigned j=0;j<column;j++){
			pointer->wsk[i][j]=wsk[i][j];
		}
	}
	cref--;
	return pointer;
}
