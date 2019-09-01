#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <ctype.h>
#include <string>
#include <time.h>

using namespace std;

string vocabulario = "abcdefghijklmnopqrstuvwxyz., ";

string read(string filename)
{
    ifstream ficheroEntrada;
    string frase;

    ficheroEntrada.open(filename);
    getline(ficheroEntrada, frase);
    ficheroEntrada.close();

    for(auto&c : frase)
    {
        c = tolower(c);
    }
    //cout << "Frase leida: " << frase << endl;
    return frase;
}

void write(string frase,string filename)
{
    ofstream fh;
    fh.open(filename);
    fh << frase;
    fh.close();
    return;
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
        t = t + pow(A[i] - Media,2);
    }
    //cout<<"Desviacion: "<<sqrt(t/A.size())<<endl;
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

double Porcentaje(double N,double P)
{
    return N*P/100;
}

void GeneradorTexto(vector<double> frecuencia)
{
    srand(time(NULL));
    string texto="";
    for(int i=0;i < 4000;i++)
    {
        texto = texto + vocabulario[rand()%(vocabulario.size())];
    }
    write(texto,"dataGenerado1.txt");
    
    string vb = "";
    for(int i=0;i < frecuencia.size() ;i++)
    {
        for(int j=0;j<frecuencia[i];j++)
        {
            vb = vb + vocabulario[i];
        }
    }

    texto = "";
    for(int i=0;i < 4000;i++)
    {
        texto = texto + vb[rand()%(vb.size())];
    }
    write(texto,"dataGenerado2.txt");
    return;
}

void permutar(int p)
{
    string texto = read("data.txt");
    string tp = "";
    int pos1=0,pos2=0;
    for(int i = 0;i < p;i++)
    {
        pos1 = rand()%(texto.size()-1);
        pos2 = rand()%(texto.size()-1);
        tp[0] = texto[pos1];
        texto[pos1] = texto[pos2];
        texto[pos2] = tp[0];
    }
    vector<double> fr = frecuencia(texto);
    fr = Normalizar(fr);
    Entropia(fr);
}


int main()
{
    vector<double> fr = frecuencia(read("data.txt"));

    GeneradorTexto(fr);

    fr = Normalizar(fr);
    /*for(int i=0;i<fr.size();i++)
    {
        cout<<fr[i]<<" ";
    }
    cout<<endl;
    */
    Entropia(fr);
    permutar(4000);

    return 0;
}
