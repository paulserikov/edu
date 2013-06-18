#include <iostream>
#include <conio.h>
#include <cmath>
using namespace std;


int main(int argc, char *argv[])
{
	float dist, freq, h1, h2, deltaN, Wx, Bx, tau0;
	cout<<"Welcome to zadacha 12 solving programm\n!";
	cout<<"Calculation is valid for overland trail, located in the Central European part of Russia. \n Note, that signatures for the minimum phase and minimum phase fading equal! \n Please, input benchmark data...\n";
	cout<<"Test data is: 11, 30, 220, 250, -300, 28, 22, 6.3 | result: p0=10.3, ps=0.7*10^-5 \n";


	cout<<"Working frequency, GHz: ";
	cin>>freq;
	cout<<"Track distance, km: ";
	cin>>dist;
	cout<<"Height of first antenna, m: ";
	cin>>h1;
	cout<<"Height of second antenna, m: ";
	cin>>h2;
	cout<<"Parameter of atmosphere(radiometeorological option), units 1/meter: ";
	cin>>deltaN;
	cout<<"Width of signature, MHz: ";
	cin>>Wx;
	cout<<"Deep of signature, dB:  ";
	cin>>Bx;
	cout<<"Sample delay, ns:  ";
	cin>>tau0;


	float hlow=min(h1,h2);														// minimal antenna's height
	float ep=abs(h1-h2)/dist;													// slope of track
	float K=pow(10,-4.6-0.0027*deltaN);											// geoclimatic coefficient
	float p0 = K*pow(dist,3.1)*pow(1+abs(ep),-1.29)*pow(freq,0.8)*pow(10,-0.001*hlow);		// fast planning, the percentage of time for the average worst month during which exceeded the depth of fading

	float kappaS = 1-exp((-0.2)*pow((p0/100), 0.75));								// multipath activity parameter
	float taum = 0.7*pow(dist/50, 1.3);											// delay of the reflected signal
	float ps = 2.15*2*kappaS*(Wx*pow(10,-Bx/20)*pow(taum,2)/abs(tau0));				// the required percentage of the outage

	cout<<"\n\n====CONTROL DATA=====\n";
	cout<<"1) ep (slope of track) = "<<ep<<"\n";
	cout<<"2) K (geoclimatic coefficient) = "<<K<<"\n";
	cout<<"3) p0 (percentage of time) % = "<<p0<<"\n";
	cout<<"4) kappaS (multipath activity parameter) = "<<kappaS<<"\n";
	cout<<"5) Wx (width of signature) Mhz = "<<Wx<<"\n";
	cout<<"6) Bx (deep of signature) dB = "<<Bx<<"\n";
	cout<<"7) taum (delay of the reflected signal) ns = "<<taum<<"\n";
	cout<<"8) tau0 (sample delay) ns = "<<tau0<<"\n\n";

	cout<<"PERCENTAGE OF BREAK, % = "<<ps/100<<"\n";
	cout<<"Press any key to exit...";

	getch();
	return 0;
}
