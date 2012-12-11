//
//  main.cpp
//  SteepestDescent
//
//  Created by Remigijus Paulavicius on 11/20/12.
//  Copyright (c) 2012 Remigijus Paulavicius. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstdlib> // rand(), srand()
#include <vector>
#include <algorithm>
#include <ctime>
#include "sixhump.h"
#include "matlab.h"
#include <stdio.h>
#define N 2
#define SPRENDINIAI 6
using namespace std;

struct taskai
{
    double x1;
    double x2;
    double sprendinys;
};
/*double sixhump(double x0, double x1)
{
    double f = (4- 2.1 * x0 * x0 + (pow(x0,4))/3) * x0 * x0 + x0 * x1 + (-4+4*x1*x1)*(pow(x1,2));
    return f;
}*/
// Vektoriaus begalines (max) normos funkcijos deklaracija
double Vector_Max_Norm(double v[], int n);

// Greiciausio nusileidimo (angl. Steepest Descent) metodo deklaracija
int  Steepest_Descent(double (*f)(double *), void (*df)(double *, double *),
     int (*stopping_rule)(double*, double, double*, double, double*, int, int),
                          double a[], double *fa, double *dfa, double cutoff,
						double cutoff_scale_factor, double tolerance, int n);
//Niutono Raphsono algoritmas
int Newton_Raphson_ndim( void (*f)(double*, double*),
                   void (*df)(double*, double*, double*),
                              int (*Stopping_Rule)(double*, double*, int),
                                             double *a, double *fa, int n);

// Generuoja atsitiktini realu skaiciu tarp dLow and dHigh
double GetRandomNumber(double dLow, double dHigh){
    return static_cast<double>(rand())/RAND_MAX*(dHigh-dLow) + dLow;
}

// Apskaiciuoja Six-hump Camel Back funkcijos reiksme taske x
double SixHumpCamelBack(double *x){
    return (4-2.1*x[0]*x[0]+x[0]*x[0]*x[0]*x[0]/3)*x[0]*x[0] + x[0]*x[1] + (-4+4*x[1]*x[1])*x[1]*x[1];
}
void SixHumpCamelBack_R(double *x, double *fa)
{
    fa[0]=(4-2.1*x[0]*x[0]+x[0]*x[0]*x[0]*x[0]/3)*x[0]*x[0] + x[0]*x[1] + (-4+4*x[1]*x[1])*x[1]*x[1];
}
// Apskaiciuoja Six-hump Camel Back gradiento reiksme taske x
void SixHumpCamelBackGradient(double *x, double *fGrad){
    fGrad[0] = 8*x[0]-8.4*x[0]*x[0]*x[0]+2*x[0]*x[0]*x[0]*x[0]*x[0]+x[1];
    fGrad[1] = x[0]-8*x[1]+16*x[1]*x[1]*x[1];
}

// Algoritmo sustojimo salyga kontroliuojanti funkcija
int StoppingRule(double* a, double fa, double* x, double fx, double* dfa, int
iteration, int n){
	double fEps = abs(fx - fa); // Funkcijos reiksmiu skirtumas
	double xa[n];
	for(int i = 0; i < n; ++i) xa[i] = x[i]-a[i];
	double xEps = Vector_Max_Norm(xa, 2); // Argumento skirtumo norma
	double dfaEps = Vector_Max_Norm(dfa, 2); // Gradiento norma
	if(iteration > 3)
		return -6;
	else
		return 0;
}

bool rusiavimas(const taskai a, taskai b)
{
    return a.sprendinys<b.sprendinys;
}

void RandomSearch(double *a, double *region)//musu montecarlo funkcija     as manau turetu buti cia void o ne double
{
    cout<<"===Sprendziame treciu budu===\n";
    vector <taskai> vec(0);
    taskai tmptaskai;
    int n;
    int jj=0;
    cout<<"Iveskite uzdavinio dimensija(n):";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        tmptaskai.x1=rand() * (region[1] - region[0]) / RAND_MAX + region[0];
        tmptaskai.x2=rand() * (region[3] - region[2]) / RAND_MAX + region[2];
        tmptaskai.sprendinys=sixhump(tmptaskai.x1,tmptaskai.x2);
        vec.push_back(tmptaskai);
        cout<<i<<'\t'<<vec[i].x1<<'\t'<<vec[i].x2<<'\t'<<vec[i].sprendinys<<endl;
    }
    sort(vec.begin(),vec.end(),rusiavimas);
    cout<<"\nSurusiuotas vektorius pagal funkcijos sprendini(TOP 3)\n";
    for(int j=0;j<(SPRENDINIAI/2);j++)
        //cout<<j<<'\t'<<vec[j].x1<<'\t'<<vec[j].x2<<'\t'<<vec[j].sprendinys<<endl;
        {
        a[jj]=vec[j].x1;
        jj++;
        a[jj]=vec[j].x2;
        cout<<j<<'\t'<<vec[j].x1<<'\t'<<vec[j].x2<<'\t'<<vec[j].sprendinys<<endl;
        }

    cout<<"Darbas baigtas\n";
    vec.clear();
}

int main(int argc, const char * argv[])
{
	double region[] = {-1.9, 1.9, -1.1, 1.1};
	double xreiksmes[SPRENDINIAI];
	double a[2];
	int i=0;
	sixhumpInitialize();
	sixhumpTerminate();
	//int budas;
	srand(time(0)); // Naudoja vis kita seed'a
    //cout<<"1-Steepest Descent\t2-Newton Raphson\n";
    //cin>>budas;
    //if(budas==1)
    //{
        RandomSearch(xreiksmes, region); /*!!!!!!!!!!!!!!!!!!!!!uzdavinio esme perduoti i a geriausius montecarlo metodu surastas 3 geriausias reiksmes!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    //	double a[N] = {0.0, 1.0}; // N-matis Vektorius
        /*srand(time(0)); // Naudoja vis kita seed'a
        double a[N]; // N-matis Vektorius
        for(int i = 0; i < N; ++i){
            a[i] = GetRandomNumber(region[2*i], region[2*i+1]);
        }*/
        while(i<SPRENDINIAI)
        {
            a[0]=xreiksmes[i];
            i++;
            a[1]=xreiksmes[i];
            i++;
            double fa = SixHumpCamelBack(a); // Funkcijos reiksme pradiniame taske a
            double dfa[N];
            SixHumpCamelBackGradient(a, dfa); // Funkcijos gradiento reiksme taske a
            double cutoff = 1.0, cutoff_scale_factor = 1.0; // Pap. parametrai
            double tolerance = 0.01;
            int err = Steepest_Descent( SixHumpCamelBack, SixHumpCamelBackGradient, StoppingRule,
            a, &fa, dfa, cutoff, cutoff_scale_factor, tolerance, N);
            switch (err)
            {
                case 0:
                    cout << "Success" << endl;
                    break;
                case -1:
                    cout << "In the line search three points are collinear." << endl;
                    break;
                case -2:
                    cout << "In the line search the extremum of the parabola through the three points is a maximum." << endl;
                    break;
                case -3:
                    cout << "Int the line search the initial points failed to satisfy the condition that x1 < x2 < x3 and fx1 > fx2 < fx3." << endl;
                    break;
                case -4:
                    cout << "Not enough HEAP memory." << endl;
                    break;
                case -5:
                    cout << "The gradient evaluated at the initial point vanishes." << endl;
                case -6:
                    cout << "Exceed maximal number of iterations." << endl;
                break;
            }
            cout << "Greiciausio nusileidimo (angl. Steepest Descent) metodu" << endl;
            cout << "surastas sprendinys yra:" << endl;
            cout << "xMin = (" << a[0] << ", " << a[1] << ")" << endl;
            cout << "f(xMin) = " << fa << endl;
            cout << "*****************************************************\n";
    }
	return 0;
}

