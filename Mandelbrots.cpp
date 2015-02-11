#include <iomanip>
#include <iostream>
#include <fstream>
#define ROWS 512
#define COLS 512
#define MAXITERS 1000

using namespace std;

struct Complex {
double real;
double imag;
};

Complex mult(Complex a, Complex b){
Complex c;
c.real = a.real*b.real - a.imag*b.imag;
c.imag = b.real*a.imag + a.real*b.imag;
return c;
}

Complex operator*(Complex a, Complex b){
return mult(a,b);
}

Complex add(Complex a, Complex b){
Complex c;
c.real = a.real+b.real;
c.imag = a.imag+b.imag;
return c;
}

Complex operator+(Complex a, Complex b){
return add(a,b);
}

int mbrotIters(Complex c){
int i=0;
Complex z;
z.real=0;
z.imag=0;

while(i<MAXITERS){
z=z*z+c;	
if((z.real*z.real+z.imag*z.imag)>4)break;
i++;
}

return i;
}

void mbrot(Complex c1, Complex c2){
int i,j;
Complex cx;
int iters;
ofstream fout;

fout.open ("mandeloutput.ppm");
fout<<"P3"<<std::endl;
fout << COLS <<"  "<<ROWS <<std::endl;
fout <<"255 0 "<<std::endl;
	

for(i=0;i<ROWS;++i){
for(j=0;j<COLS;++j){
   cx.real = c1.real+(j*(c2.real-c1.real)/COLS);
   cx.imag = c1.imag+(i*(c2.imag-c1.imag)/ROWS);
   iters = mbrotIters(cx);
   if(iters==MAXITERS)fout<<"0 9 0 "; 
   else fout<< iters <<" 0 0 "; 
   
}
fout << endl;
}
}

int main()
{
	ifstream mandel("mandelinput.txt");
	if(!mandel.is_open () )
	{
		cout<<" The File did not open\n";
		return 0;
	}

Complex c1;
Complex c2;

mandel>> c1.real;
mandel>> c1.imag;
mandel>> c2.real;
c2.imag = c1.imag - (c2.real - c1.real);


mbrot(c1,c2);

return 0;

}


