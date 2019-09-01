#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <ctype.h>
#include <string>
#include <clocale>

using namespace std;

string vocabulario = "abcdefghijklmnopqrstuvwxyz., ";

string read()
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

void write(string frase)
{
    ofstream fh;
    fh.open("dataGenerado.txt");
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

void GeneradorTexto(vector<double> frecuencia)
{
    srand(time(NULL));
    string texto="";
    for(int i=0;i < 4000;i++)
    {
        texto = texto + vocabulario[rand()%(vocabulario.size())];
    }

    write(texto);

    texto = "";
    for(int i=0;i < 4000;i++)
    {
        texto = texto + vocabulario[rand()%(vocabulario.size())];
    }

    //cout<<texto<<endl;
    return;
}




int main()
{
    setlocale(LC_CTYPE,"Spanish");
    vector<double> fr = frecuencia(read());
    fr = Normalizar(fr);
    /*for(int i=0;i<fr.size();i++)
    {
        cout<<fr[i]<<" ";
    }
    cout<<endl;
    */
    Entropia(fr);

    GeneradorTexto(fr);

    return 0;
}
