#include <iostream>
#include <cassert>

using namespace std;

class Matrix{
	private:
		class rcMatrix{
			friend class Matrix; 
			public:
				double **wsk;
				unsigned int row,column;
				unsigned int cref;
				rcMatrix();
				rcMatrix(unsigned int, unsigned int);
				~rcMatrix();
				rcMatrix* detach();
		};
		rcMatrix *data;
	public:
		class Mref{   
		    friend class Matrix;
		    Matrix& s;
		    unsigned int i,k;
		    Mref (Matrix& m, unsigned int r, unsigned int c): s(m), i(r), k(c) {}     
		    public:
				operator double() const;
				Mref& operator = (double c);
				Mref& operator = (const Mref& ref);
    };
		Matrix();
		Matrix(unsigned int, unsigned int);
		Matrix(const Matrix&);
		~Matrix();
		
        Matrix& operator=(const Matrix&);
        Matrix operator+(const Matrix&) throw(string);
        Matrix operator-(const Matrix&) throw(string);
        Matrix operator*(const Matrix&) throw(string);
        Matrix& operator+=(const Matrix&) throw(string);
        Matrix& operator-=(const Matrix&) throw(string);
        Matrix& operator*=(const Matrix&) throw(string);
    
        Matrix& Wczytaj(const char*);
		friend Matrix& Wypelnij(Matrix&);
        friend Matrix& Zeruj(Matrix&);
        double read(unsigned int, unsigned int) const; 
    	void write(unsigned int, unsigned int, const double);
        bool operator == (const Matrix &);
        friend ostream& operator<<(ostream& o,const Matrix&);
		Mref operator()(unsigned int, unsigned int);
    
        unsigned int getCref();
};
