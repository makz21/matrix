#include <iostream>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include "funkcje.h"
using namespace std;

Matrix::Matrix(){
    data=new rcMatrix();
}

Matrix::Matrix(unsigned int wier, unsigned int kol){
    data=new rcMatrix(wier,kol);
}

Matrix::Matrix(const Matrix& Object){
    Object.data->cref++;
    data=Object.data;
}

Matrix::~Matrix(){
	if(--data->cref==0){
		delete data;
	}
}


double Matrix::read(unsigned int i,unsigned int j) const{
    return data->wsk[i-1][j-1];
}

void Matrix::write(unsigned int i, unsigned int j, const double x){
    data = data->detach();
    data->wsk[i-1][j-1] = x;
}

Matrix& Wypelnij(Matrix& Object){
    for(unsigned i=0;i<Object.data->row;i++){
        for(unsigned j=0;j<Object.data->column;j++){
            Object.data->wsk[i][j]=rand()%100+1;
        }
    }
    return Object;
}

Matrix& Matrix::Wczytaj(const char *string){
    unsigned int m=0,n=0;
    ifstream inFile;
    inFile.open(string);
    if(inFile.good()){
        inFile>>m;
        inFile>>n;
        data=data->detach();
        for(unsigned int i=0;i<m;i++){
            for(unsigned int j=0;j<n;j++){
                inFile>>data->wsk[i][j];
            }
        }
        inFile.close();
    }
    return *this;
}

Matrix& Matrix::operator=(const Matrix& Object){
	Object.data->cref++;
	if(--data->cref==0){
		delete data;
	}
	data=Object.data;
	return *this;
}

Matrix Matrix::operator+(const Matrix& Object) throw(string){
	Matrix A(data->row,data->column);
	if(data->row!=Object.data->row || data->column!=Object.data->column){
		string wyjatek = "Macierze A i B nie sa sobie rowne.";
		throw wyjatek;
	}
	else{
		unsigned int i,j;
		for(i=0; i<data->row;i++){
			for(j=0; j<data->column; j++){  
				A.data->wsk[i][j]=data->wsk[i][j]+Object.data->wsk[i][j];
			}
		}
	}
	return A;
}

Matrix Matrix::operator-(const Matrix& Object) throw(string){
	Matrix A(data->row,data->column);
	if(data->row!=Object.data->row || data->column!=Object.data->column){
		string wyjatek = "Macierze A i B nie sa sobie rowne.";
		throw wyjatek;	
	}
	else{
		for(unsigned i=0;i<data->row;i++){
			for(unsigned j=0;j<data->column;j++){
				A.data->wsk[i][j]=data->wsk[i][j]-Object.data->wsk[i][j];
			}
		}
	}
	return A;
}

Matrix Matrix::operator*(const Matrix& Object) throw(string){
	double temp=0;
	Matrix A(data->row,data->column);
	if(data->column!=Object.data->row){
		string wyjatek = "Macierze A i B nie sa sobie rowne.";
		throw wyjatek;
	}
	else{
		for(unsigned i=0;i<data->row;i++){
			for(unsigned j=0;j<Object.data->column;j++){
				for(unsigned k=0;k<data->column;k++){
					temp+=data->wsk[i][j]*Object.data->wsk[j][k];
				}
			A.data->wsk[i][j]=temp;
			}
		}
	}
	return A;
}

Matrix& Matrix::operator+=(const Matrix& Object) throw(string){
	if(data->row!=Object.data->row || data->column!=Object.data->column){
		string wyjatek = "Macierze A i B nie sa sobie rowne.";
		throw wyjatek;	
	}
	else{
		data=data->detach();
		for(unsigned i=0;i<data->row;i++){
			for(unsigned j=0;j<data->column;j++){
				data->wsk[i][j]+=Object.data->wsk[i][j];
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& Object) throw(string){
	if(data->row!=Object.data->row || data->column!=Object.data->column){
		string wyjatek = "Macierze A i B nie sa sobie rowne.";
		throw wyjatek;	
	}
	else{
		data=data->detach();
		for(unsigned i=0;i<data->row;i++){
			for(unsigned j=0;j<data->column;j++){
				data->wsk[i][j]-=Object.data->wsk[i][j];
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& Object) throw(string){
	if(data->column!=Object.data->row){
		string wyjatek = "Macierze A i B nie sa sobie rowne.";
		throw wyjatek;
	}
	else{
		unsigned m=0,n=0;
		double temp=0;
		m=data->row;
		n=Object.data->column;
		Matrix A(m,n);
		for(unsigned i=0;i<data->row;i++){
			for(unsigned j=0;j<Object.data->column;j++){
				for(unsigned k=0;k<data->column;k++){
					temp+=data->wsk[i][k]*Object.data->wsk[k][j];
				}
				A.data->wsk[i][j] = temp;
                temp=0;
			}
		}
		data=data->detach();
		for(unsigned i=0;i<m;i++){
			for(unsigned j=0;j<n;j++){
				data->wsk[i][j]=A.data->wsk[i][j];
			}
		}		
	}
	return *this;
}

bool Matrix::operator == (const Matrix& Object){	
	unsigned int i,j;
	for(i=0;i<data->row;i++){
		for(j=0;j<data->column;j++){
			if(data->wsk[i][j]!=Object.data->wsk[i][j]){
			return false;
			}	
		}
	}
	return true;
}

ostream& operator<<(ostream& o,const Matrix& Object){
	for(unsigned i=0;i<Object.data->row;i++){
		for(unsigned j=0;j<Object.data->column;j++){
			o<<Object.data->wsk[i][j]<<" ";
		}
		o<<endl;
	}
	return o;
}

Matrix::Mref Matrix::operator()(unsigned int i, unsigned int j){
    return Mref(*this,i,j);
}

unsigned int Matrix::getCref(){
    return data->cref;
}
