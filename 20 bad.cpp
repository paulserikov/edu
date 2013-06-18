// ITU 452 recommendation
// radiometeorological parameters is beta0 = 0.0055%


#include <iostream>
#include <conio.h>
#include <cmath>
using namespace std;


double J (double x) {			// аппроксимация к дифракционным потерям над одиночным клиновидным препятствием
	if (x<-0.78) return 0;
	else return 6.9+20*log(sqrt(pow(x-0.1,2)+1)+x-0.1);
}


double I (double x) {				// аппроксимация обратной кумулятивной функции нормального	распределения
	if (x<0.000001) x=0.000001;
	if (x>0.5) {
		cout<<"Error 1: cumulative function does not exist";
		return 0;
	}
	double t = sqrt((-2)*log(x));
	return ((0.010328*t+0.802853)*t+2.515516698)/(((0.001308*t+0.189269)*t+1.432788)*t+1);
}



int main(int argc, char *argv[])
{
	double d, dlt, dlr, f, p, lat, ht, hr, deltaN, part;
	cout<<"Welcome to zadacha 20 solving programm\n!";

	cout<<"| Need data is: 190, 95, 87, 22, 0.01, 40, 100, 75, 40 |\n";

	cout<<"Input track distance, km: ";
	cin>>d;
	cout<<"Input radiohorizont for transmitter, km: ";
	cin>>dlt;
	cout<<"Input radiohorizont for receiver, km: ";
	cin>>dlr;
	cout<<"Input frequency, GHz: ";
	cin>>f;
	cout<<"Input time percent: ";
	cin>>p;
	cout<<"Geographical latitude of track, grad: ";
	cin>>lat;
	cout<<"Height of transmitter antenna, m: ";
	cin>>ht;
	cout<<"Height of receiver antenna, m: ";
	cin>>hr;
	cout<<"Parameter of atmosphere(radiometeorological option), units: ";
	cin>>deltaN;
	cout<<"Part of track under water, percents (if track is overland input zero): ";
	cin>>part;


	const double gamma0 = 0.13;						// погонное ослабление в сухом воздухе
	// p0 = 7.5+2.5*part; 							// плотность паров воды. part - часть трассы, проходящая над водой
	const double gammap0 = 0;						// погонное ослабление в парах воды ITU 676. т.к. территория полностью сухопутная считаю нулем.
	double Ag=(gamma0+gammap0)*d; 					// gamma0, gamma(p0) - согласно ITU 676 recommendation gamma0 = 0.07 db/km. для наших расчетов почему-то брали 0.13

	double Lbfsg = 92.5 + 20*log(f)+20*log(d)+Ag;
	cout<<"Main atmospheric losses is "<<Lbfsg<<" db \n";		// основные потери из-за распространения в свободном пространстве и ослабления в атмосферных газах

	double Esp = 2.6*(1-exp(-0.1*(dlt+dlr)))*log(p/50.0);		// поправка, учитывающая эффекты многолучевости и фокусировки при проценте времени p
	double Lbop = Lbfsg + Esp;
	cout<<"Main atmospheric losses with correction of is "<<Lbop<<" db \n";

	double k50 = 157.0/(157.0-deltaN);		// медианное значение коэффициента эквивалентного радиуса Земли
	double ae = 6371*k50;					// медианное значение эквивалентного радиуса Земли
	cout<<"ae is "<<ae<<" km \n";


	double abeta = 6371*3.0;				// эквивалентный радиус Земли, превышенный на beta0% времени.
	double dlm = d;							//самый длинный участок территории вдали от моря, над которым проходит трасса по дуге большого круга
	double dtm = d;
	double lambda = 0.3/f;					// длина волны, м


	// ----------------------------------------------------------------------- //

	double tau=1-exp(-4.12*0.0001*pow(dlm,2.41));											// вспомогательный параметр для расчета mu1
	double mu1=pow(pow(10,-dtm/(16-6.6*tau))+pow(pow(10,-0.496-0.354*tau),5),0.2);			// параметр. зависит от угла, под которым трасса проходит над сушей

	cout<<"Mu1 is (must not be >1): "<<mu1<<"\n";
	if (mu1>1) {
			cout<<"Error 2: mu1>1"; }
	double mu4, beta0;

	if (lat>70) {
		mu4 = pow(10,0.3*log(mu1));
		beta0 = 4.17*mu1*mu4;			// параметр beta0 (%) аномальных условий распространения
	}
	else {
		mu4 = pow(10, (-0.935+0.0176*abs(lat))*log(mu1));
		beta0=pow(10,-0.015*abs(lat)+1.67)*mu1*mu4;
	}

	cout<<"Beta0 is: "<<beta0<<"\n";
	// ----------------------------------------------------------------------- //

	double correction1 = cos (1/tan(0.001*((ht-hr)/d)));		// поправка для общего наклона трассы, проверить высоты: высоты передатчика над уровнем моря (Высота центра антенны над средним уровнем моря != Эффективные высоты антенн над местностью)
	cout<<"correction1 is: "<<beta0<<"\n";

	// double hi, di, Hi;
	//double min, max;


	//for (hi=100.0;hi<8848.0;hi++) {
	//	for (di=dlt;d<d-dlr;d++) {
	//Hi = hi+1000*(di*(d-di)/2*ae)*((ht*(d-di)+hr*di)/d);				// вертикальный просвет
	//if (min>Hi) min=Hi;
	//if (max<Hi) max = Hi;
	//	}																// maximize x+1000*(y*(190-y)/2*8549)*((100*(190-y)+75*y)/190) on 100<x<8848 95<y<103  3.37 * 10^12
	//}
	//cout<<"Min H is: "<<min<<"| Max H is: "<<max<<"\n";

	double max=3.37*pow(10,12)											//  maximize 3.37*10^12*on 100<x<8848
	double v50 = correction1*max*sqrt(0.002*d/lambda*di*(d-di));		// дифракционный параметр главной кромки препятствия (чтоб его найти, нужно знать профиль высот)
	double Lm50 = J(v50);


	double Lt50, Lr50 = 0; 												// для второстепенной кромки передатчика - нет
	double Ld50 = Lm50 + (1-exp(-Lm50/6))*(Lt50+Lr50+10+0.04*d); 		// Медианные дифракционные потери, исп. медианное значение эквивалентного радиуса Земли (ae)
	cout <<"Ld50 is: "<<Ld50<<" db\n";

	double Ldbeta;
	if (Ld50==0) Ldbeta=0; else {
		Ldbeta = 0;						// Дифракционные потери, не превышающиеся для beta0 % времени, исп. расчет коэффициента эквивалентного радиуса Земли, превышенного на beta0% времени (abeta)
										// почти точно так же как и Lm50
	}


	double Fi;
	if (p==50) Fi = 0;
	if ((beta0<p)&(p<50)) {
		Fi = I(p/100)/I(beta0/100);
	}
	if (beta0>=p)	Fi = 1;

	long double Ldp = Ld50 + Fi*(Ldbeta-Ld50);			// дифракционные потери, не превышаемые для p% времени

	long double Lbd=Lbop+Ldp;							// основные потери передачи, связанные с дифракцией, не превышенные для p% времени
	cout<<"Result main losses, db: "<<Lbd;
	getch();
	return 0;
}
