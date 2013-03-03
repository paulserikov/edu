#include <iostream.h>
#include <math.h>
using namespace std;

double f(double x);

void main()
{
double tau=(sqrt(5.)-1.)/2.;
double eps=1e-7;
double a=-0.5
double b=0.5;
double x1,x2;
while (b-a>eps)
    {
    x1=b-tau*(b-a);
    x2=a+tau*(b-a);
    if (f(x1)>f(x2))
       b=x2;
    else
       a=x1; 
    }
cout<<x1;
}

double f(double x)
{
return 1/3*x*x*x+(1+x)*(ln(1+x)+1);
}
