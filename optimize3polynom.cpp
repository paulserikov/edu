// how to check compile?
// make install build-essential packet
// run user_name:~$ g++ demo.cpp
// run ./a.out
// для нескольких переменных -  http://www.gotdotnet.ru/blogs/antonnazarov/11718/
// check it in wolfram plot -2*x^3+x^2+2*x-1 from x=-10 to 10
// http://habrahabr.ru/post/149470/

#define ITERATIONS 1000
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;	// обязательно если не хочешь все время писать std::cout

float polinom (float x);
float derr (float x);
float A, B, C, D, x1, x2;
float mas[2];
int n=2;

//float *arr; arr=(float*)malloc(n*sizeof(float));

int main (void)
{
cout<<"Введите A: ";
cin>>A;
cout<<"Введите B: ";
cin>>B;
cout<<"Введите C: ";
cin>>C;
cout<<"Введите D: ";
cin>>D;
cout<<"Введите нижнюю границу изменения x (минимум): ";
cin>>x1;
cout<<"Введите верхнюю границу изменения x (максимум): ";
cin>>x2;

float z;				// текущее знач функции
float pr=pow(10,-6);	//точность


cout<<"Значение функции на нижней границе: "<<polinom(x1)<<"\n";
cout<<"Значение функции на верхней границе: "<<polinom(x2)<<"\n";

for (z=x1;z<=x2;z+=pr)
	{
		float m=derr(z);
		if (fabs(m)<=derr(pr))
			{
				float m1=polinom(z);
				for(int i=0; i<n; i++) 
					{
    					mas[i] = m1;
						cout<<mas[i]<<"\n";
					}	
			}
	}
	
return 0;
}


float polinom (float x)		// вычисление значения
{
    float y=A*pow(x,3)+B*pow(x,2)+C*x+D;
    return (y);
}

float derr (float x)		// вычисление производной
{
    float y=3*A*pow(x,2)+2*B*x+C;
    return (y);
}
