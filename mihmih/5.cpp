#include <iostream>
#include <conio.h>
#include <cmath>
using namespace std;


int main(int argc, char *argv[])
{
	cout<<"Welcome to zadacha 5 solving programm\n!";
	cout<<"Solutions for the worst case when the carrier frequencies for useful and interfering signal are coincide\n";
	cout<<"| Need data is: 20, 50, 120, 1.47, 3, 4.096, 110, 7, 800 |";
	cout<<"Please, input benchmark data for USEFUL signal...\n";

	double n, Fsv, deltaF, M, deltaF1;
	cout<<"The number of channels of tone frequency: ";
	cin>>n;
	cout<<"The upper cutoff frequency of the linear spectrum, kHz: ";
	cin>>Fsv;
	cout<<"Frequency deviation per channel, kHz: ";
	cin>>deltaF;
	cout<<"Efficient modulation index: ";
	cin>>M;
	cout<<"Bandwidth, MHz: ";
	cin>>deltaF1;


	cout<<"Please, input benchmark data for INTERFERING signal...\n";

	double R, Fmv, deltaF2, P;
	cout<<"Transfer speed digital stream, Mbit/s: ";
	cin>>R;
	cout<<"The upper cutoff frequency of the linear spectrum, kHz: ";
	cin>>Fmv;
	cout<<"Bandwidth, MHz: ";
	cin>>deltaF2;
	cout<<"the maximum power of the interfering signal, pWatt: ";
	cin>>P;

	// double rF = Fsv/Fmv; 																// relative frequency
	// cout<<"Please, look at the graph and enter g for M="<<M<<"and q="<<rF<<"\n";
	// cout<<"g= ";
	// double g;
	// cin>>g;

	double D10 = (Fsv/R)*pow(sin(M_PI*Fsv/R)/M_PI*Fsv/R, 2);							// for 4-FM use 2*Fsv/R
	cout<<"Value of function D10 = "<<D10<<"\n";
	double qm =88.4 - 10*log10(P)+20*log10(Fsv/deltaF)-10*log10(Fsv)+10*log10(D10);
	cout<<"PROTECTION RATIO (qm), dB = "<<qm<<"dB\n";
	cout<<"Press any key to exit...";
	getch();
	return 0;
}
