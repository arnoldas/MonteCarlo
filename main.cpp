#include <iostream>
#include <cstdlib>
#include <cmath>
// funkcija  http://www.it.lut.fi/ip/evo/functions/node26.html
// six camel hump function
using namespace std;

    struct taskai
    {
        double x1;
        double x2;
        double sprendinys;
    };

double sixhump(double x0, double x1)
{
    double f = (4- 2.1 * x0 * x0 + (pow(x0,4))/3) * x0 * x0 + x0 * x1 + (-4+4*x1*x1)*(pow(x1,2));
    return f;
}

void insertionSort(taskai *arr/*int arr[]*/, int length) {
      int i, j;
      taskai tmp;
      for (i = 1; i < length; i++) {
            j = i;
            while (j > 0 && arr[j - 1].sprendinys > arr[j].sprendinys) {
                  tmp = arr[j];
                  arr[j] = arr[j - 1];
                  arr[j - 1] = tmp;
                  j--;
            }
      }
}

void pirmas_budas(double p_apacia, double p_virsus, double p_apacia2, double p_virsus2)
{   //susikuriam strukturu masyva
    int mas_dydis = 1;//iteraciju skaicius, kazkodel kai yra struktura, ji pati issiskiria kiek jai reikia vietos
    int n;//dimensija
    taskai *taskuArray = new taskai[mas_dydis];

    cout<<"===Sprendziame pirmu budu===\n";
    cout<<"Iveskite uzdavinio dimensija(n):";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        taskuArray[i].x1=rand() * (p_virsus - p_apacia) / RAND_MAX + p_apacia;
        taskuArray[i].x2=rand() * (p_virsus2 - p_apacia2) / RAND_MAX + p_apacia2;
        taskuArray[i].sprendinys=sixhump(taskuArray[i].x1,taskuArray[i].x2);
        cout<<i<<'\t'<<taskuArray[i].x1<<'\t'<<taskuArray[i].x2<<'\t'<<taskuArray[i].sprendinys<<endl;
    }
    insertionSort(taskuArray, n);
    cout<<"\nSurusiuotas masyvas pagal funkcijos sprendini(TOP 5)\n";
    for(int i=0;i<5;i++)
    {
        cout<<i<<'\t'<<taskuArray[i].x1<<'\t'<<taskuArray[i].x2<<'\t'<<taskuArray[i].sprendinys<<endl;
    }
    cout<<"Darbas baigtas\n";
}

void antras_budas(double p_apacia, double p_virsus, double p_apacia2, double p_virsus2)
{
    cout<<"===Sprendziame antru budu===\n";
}

int main()
{
    cout << "Monte Carlo realizacijos pradzia\n";
    cout << "(RANDOM SEARCH METHOD)\n";
    //Kintamuju apsirasymas
    double fSprendinys=-1.031628453; // Uzdavinio sprendinys
    double epsilon=0.001;  //paklaida
    int budas; //Uzdavinio sprendimo budas
    double virsutinis_rezis, apatinis_rezis, virsutinis_rezis2, apatinis_rezis2; // apsirasome intervalo rezius
    //cout << "Iveskite inervalo rerzius x1: ";
    //cin >> apatinis_rezis >> virsutinis_rezis;
    //cout << "Iveskite inervalo rerzius x2: ";
    //cin >> apatinis_rezis2 >> virsutinis_rezis2;
    apatinis_rezis = -1.9;
    virsutinis_rezis = 1.9;
    apatinis_rezis2 = -1.1;
    virsutinis_rezis2 = 1.1;
    cout << "Pasirinkite minimumo ieskojimo buda(1/2): ";
    cin >> budas;
    if(budas==1)
        pirmas_budas(apatinis_rezis,virsutinis_rezis,apatinis_rezis2,virsutinis_rezis2);
    else if(budas==2)
        antras_budas(apatinis_rezis,virsutinis_rezis,apatinis_rezis2,virsutinis_rezis2);
    else
      cout << "Nekorektiskai pasirinktas sprendimo budas.";

    return 0;
/*  double f, x; // Funkcijos reiksmes ir argumentas x
    int n; // Uzedavinio dimensija
    // Vektoriu kurimas, kuriu elementai yra atitiktiniai realus skaiciai

    if(budas==1)
    {
        cout << "Iveskite vektoriaus dimensija (n):";
        cin >> n;

        double vektorius[n], funkcija[200];

        for (int j=0; j<100; j++)
        {

            for(int i=0; i<n; i++)
            {
                if (i == 0)
                {
                    vektorius[i] = rand() * (virsutinis_rezis - apatinis_rezis) / RAND_MAX + apatinis_rezis;
                    cout << "Skaicius = " << vektorius[i] << endl; // pakeiciau
                }
                else
                {
                    vektorius[i] = rand() * (virsutinis_rezis2 - apatinis_rezis2) / RAND_MAX + apatinis_rezis2;
                    cout << "Skaicius = " << vektorius[i] << endl; // pakeiciau
                }

            }

            cout << "Funkcija = " << sixhump(&vektorius[0]) << endl; // pakeiciau
            cout << "===================================" << endl;
            funkcija[j] = sixhump(&vektorius[0]);
        }

        double min = funkcija[0];
        for (int i=0; i<100; i++)
        {
            if (funkcija[i] < min) min = funkcija[i];
        }
        cout << "MIN: " << min;
    }
    else if(budas==2)
    {

        rezultatai *r1=NULL, *r2=NULL;

        do
        {
            if(r1==NULL)
            {
                r1=(rezultatai *)malloc(sizeof(rezultatai));
                r2=r1;
            }
            else
            {
                r2->kitas=(rezultatai *)malloc(sizeof(rezultatai));
                r2=r2->kitas;
            }
            r2->x1=rand() * (virsutinis_rezis - apatinis_rezis) / RAND_MAX + apatinis_rezis;
            r2->x2=rand() * (virsutinis_rezis2 - apatinis_rezis2) / RAND_MAX + apatinis_rezis2;
            r2->fspr=(4-2.1*r2->x1 * r2->x1 + (pow(r2->x1,4))/3) * r2->x1 * r2->x1 + r2->x1 * r2->x2 + (-4+4*r2->x2*r2->x2)*(pow(r2->x2,2));
            r2->kitas=NULL;
            cout<<"X1="<<r2->x1<<" X2="<<r2->x2<<" sprend="<<r2->fspr<<endl;
        }
        while(fabs(fSprendinys-(r2->fspr))>epsilon);
        //reikia parasyt while(f_globalus-fmin)<epsilon(0.01 poto 0.001)
        cout<<"---------------------------------------------------------"<<endl;
        cout<<"X1="<<r2->x1<<" X2="<<r2->x2<<" sprend="<<r2->fspr<<endl;
    }
    else
        cout<<"Nekorektiðkai pasirinktas sprendimo budas.";
    return 0;*/
}
