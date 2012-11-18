#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#define N 100
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

void insertionSort(taskai *arr, int length) {
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
{
    int mas_dydis = N;
    int n;//dimensija
    taskai *taskuArray = new taskai[mas_dydis];

    cout<<"===Sprendziame pirmu budu===\n";
    cout<<"Iveskite uzdavinio dimensija(n):";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        if((i+1)==mas_dydis)
        {
            cout<<"Esam ife\n";
            taskai *tmptaskuArray = taskuArray;
            mas_dydis=mas_dydis*2;
            taskuArray = new taskai[mas_dydis];
            for(int j=0;j<i;j++)
                taskuArray[j]=tmptaskuArray[j];

            delete []tmptaskuArray;

        }
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
    delete []taskuArray;
}

void antras_budas(double p_apacia, double p_virsus, double p_apacia2, double p_virsus2, double p_fSprend, double p_epsilon)
{
    int mas_dydis=N;
    taskai *taskuArray = new taskai[mas_dydis];
    int ilgis=-1;
    cout<<"===Sprendziame antru budu===\n";
    do
    {
        if((ilgis+1)==mas_dydis)
        {
            cout<<"Esam ife\n";
            taskai *tmptaskuArray = taskuArray;
            mas_dydis=mas_dydis*2;
            cout<<"MAS_DYDIS="<<mas_dydis<<endl;
            taskuArray = new taskai[mas_dydis];
            for(int i=0;i<ilgis;i++)
                taskuArray[i]=tmptaskuArray[i];

            delete []tmptaskuArray;

        }
        ilgis++;
        taskuArray[ilgis].x1=rand() * (p_virsus - p_apacia) / RAND_MAX + p_apacia;
        taskuArray[ilgis].x2=rand() * (p_virsus2 - p_apacia2) / RAND_MAX + p_apacia2;
        taskuArray[ilgis].sprendinys=sixhump(taskuArray[ilgis].x1,taskuArray[ilgis].x2);
        cout<<ilgis<<'\t'<<taskuArray[ilgis].x1<<'\t'<<taskuArray[ilgis].x2<<'\t'<<taskuArray[ilgis].sprendinys<<endl;
    }
    while(fabs(p_fSprend-(taskuArray[ilgis].sprendinys))>p_epsilon);
    insertionSort(taskuArray, ilgis+1);
    cout<<"\nSurusiuotas masyvas pagal funkcijos sprendini(TOP 5)\n";
    for(int i=0;i<5;i++)
    {
        cout<<i<<'\t'<<taskuArray[i].x1<<'\t'<<taskuArray[i].x2<<'\t'<<taskuArray[i].sprendinys<<endl;
    }
    cout<<"Darbas baigtas\n";
    delete []taskuArray;
}

bool rusiavimas(const taskai a, taskai b)
{
    return a.sprendinys<b.sprendinys;
}

void trecias_budas(double p_apacia, double p_virsus, double p_apacia2, double p_virsus2)
{
    cout<<"===Sprendziame treciu budu===\n";
    vector <taskai> vec(0);
    taskai tmptaskai;
    int n;
    cout<<"Iveskite uzdavinio dimensija(n):";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        tmptaskai.x1=rand() * (p_virsus - p_apacia) / RAND_MAX + p_apacia;
        tmptaskai.x2=rand() * (p_virsus2 - p_apacia2) / RAND_MAX + p_apacia2;
        tmptaskai.sprendinys=sixhump(tmptaskai.x1,tmptaskai.x2);
        vec.push_back(tmptaskai);
        cout<<i<<'\t'<<vec[i].x1<<'\t'<<vec[i].x2<<'\t'<<vec[i].sprendinys<<endl;
    }
    sort(vec.begin(),vec.end(),rusiavimas);
    cout<<"\nSurusiuotas vektorius pagal funkcijos sprendini(TOP 5)\n";
    for(int j=0;j<5;j++)
        cout<<j<<'\t'<<vec[j].x1<<'\t'<<vec[j].x2<<'\t'<<vec[j].sprendinys<<endl;

    cout<<"Darbas baigtas\n";
}

void ketvirtas_budas(double p_apacia, double p_virsus, double p_apacia2, double p_virsus2, double p_fSprend, double p_epsilon)
{
    cout<<"===Sprendziame ketvirtu budu===\n";
    vector <taskai> vec(0);
    int ilgis=-1;
    taskai tmptaskai;
    do
    {
        ilgis++;
        tmptaskai.x1=rand() * (p_virsus - p_apacia) / RAND_MAX + p_apacia;
        tmptaskai.x2=rand() * (p_virsus2 - p_apacia2) / RAND_MAX + p_apacia2;
        tmptaskai.sprendinys=sixhump(tmptaskai.x1,tmptaskai.x2);
        vec.push_back(tmptaskai);
        cout<<ilgis<<'\t'<<vec[ilgis].x1<<'\t'<<vec[ilgis].x2<<'\t'<<vec[ilgis].sprendinys<<endl;
    }
    while(fabs(p_fSprend-(vec[ilgis].sprendinys))>p_epsilon);
    sort(vec.begin(),vec.end(),rusiavimas);
    cout<<"\nSurusiuotas vektorius pagal funkcijos sprendini(TOP 5)\n";
    for(int j=0;j<5;j++)
        cout<<j<<'\t'<<vec[j].x1<<'\t'<<vec[j].x2<<'\t'<<vec[j].sprendinys<<endl;
    cout<<"Darbas baigtas\n";
}

int main()
{
    cout << "Monte Carlo realizacijos pradzia\n";
    cout << "(RANDOM SEARCH METHOD)\n";
    //Kintamuju apsirasymas
    double fSprendinys=-1.031628453; // Uzdavinio sprendinys
    double epsilon=0.0001;  //paklaida 0.01 - 2.4s; 0.001 - 2.4s; 0.0001 - 2min
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
    cout << "Pasirinkite minimumo ieskojimo buda(1/2/3/4): ";
    cin >> budas;
    switch(budas)
    {
        case 1:pirmas_budas(apatinis_rezis,virsutinis_rezis,apatinis_rezis2,virsutinis_rezis2);
        break;
        case 2:antras_budas(apatinis_rezis,virsutinis_rezis,apatinis_rezis2,virsutinis_rezis2, fSprendinys, epsilon);
        break;
        case 3:trecias_budas(apatinis_rezis,virsutinis_rezis,apatinis_rezis2,virsutinis_rezis2);
        break;
        case 4:ketvirtas_budas(apatinis_rezis,virsutinis_rezis,apatinis_rezis2,virsutinis_rezis2, fSprendinys, epsilon);
        break;
        default:cout << "Nekorektiskai pasirinktas sprendimo budas.";
        break;
    }

    return 0;
}
