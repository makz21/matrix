#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "funkcje.h"
using namespace std;
                
Matrix::Mref::operator double() const{
	return s.read(i,k);       
}

Matrix::Mref &Matrix::Mref::operator = (double c){
	s.write(i,k,c); 
	return *this;
}
  
Matrix::Mref &Matrix::Mref::operator = (const Mref& ref){
	return operator= ((double)ref);   
}
