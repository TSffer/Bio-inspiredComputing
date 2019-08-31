#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <ctype.h>
#include <string>

using namespace std;

string vocabulario = "abcdefghijklmnñopqrstuvwxyz., ";

string leer()
{
    ifstream ficheroEntrada;
    string frase;

    ficheroEntrada.open ("data.txt");
    getline(ficheroEntrada, frase);
    ficheroEntrada.close();

    for(auto&c : frase)
    {
        c = tolower(c);
    }
    //cout << "Frase leida: " << frase << endl;
    return frase;
}

vector<double> frecuencia(string frase)
{
    vector<double> fr(vocabulario.size(),0);
    for(int i=0;i<vocabulario.size();i++)
    {
        for(int j=0;j<frase.size();j++)
        {
            if(vocabulario[i] == (frase[j]))
            {
                fr[i]++;
            }
        }
    }

    return fr;
}

double Desviacion(vector<double> A, double &media)
{
    double sum = 0,t = 0;
    for(int i = 0; i < A.size();i++)
    {
        sum = sum + A[i];
    }
    double Media = sum/A.size();
    media = Media;
    
    for(int i = 0; i < A.size();i++)
    {
        t = t + pow(abs(A[i] - Media),2);
    }
    cout<<"Desviacion: "<<sqrt(t/A.size())<<endl;
    return sqrt(t/A.size());
}

vector<double> Normalizar(vector<double> A)
{
    double media,desviacion;
    desviacion = Desviacion(A,media);

    vector<double> v_n(A.size(),0);

    for(int i = 0;i < A.size();i++)
    {
        v_n[i] = (abs(A[i] - media)/desviacion)/(A.size());
    }
    return v_n;
}

double Hartley(vector<double> A)
{
    return log2(A.size());
}


double Shannon(vector<double> A)
{
    double x=0;
    for(int i=0;i<A.size();i++)
    {
        x = x + A[i]*log2(A[i]);
    }

    return -x;
}

void Entropia(vector<double> v)
{
    cout<<"Hartley: "<<Hartley(v)<<endl;
    cout<<"Shannon: "<<Shannon(v)<<endl;
}




int main()
{
    vector<double> fr = frecuencia(leer());
    fr = Normalizar(fr);
    for(int i=0;i<fr.size();i++)
    {
        cout<<fr[i]<<" ";
    }
    cout<<endl;

    Entropia(fr);

    return 0;
}
