// Решение задачи оптимизации полинома 3-го порядка
// программа находит минимальное значение функции на отрезке

#include <iostream>
#include <math.h>
using namespace std;

double f(double x);
double A,B,C,D,a,b;

int main(void)
{
double tau=(sqrt(5.)-1.)/2.;
double eps=pow(10,-6);


cout<<"Введите A: ";
cin>>A;
cout<<"Введите B: ";
cin>>B;
cout<<"Введите C: ";
cin>>C;
cout<<"Введите D: ";
cin>>D;
cout<<"Введите нижнюю границу изменения x (минимум): ";
cin>>a;
cout<<"Введите верхнюю границу изменения x (максимум): ";
cin>>b;

double x1,x2;
while (b-a>eps)
    {
    x1=b-tau*(b-a);
    x2=a+tau*(b-a);
    if (f(x1)>=f(x2))
       b=x2;
    else
       a=x1; 
    }
cout<<"Максимум равен: "<<f(x1)<<"\n";

return 0;
}

double f(double x)
{
return A*pow(x,3)+B*pow(x,2)+C*x+D;
}
