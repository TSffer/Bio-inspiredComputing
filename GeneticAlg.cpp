#include <string>
#include <utility> 
#include <vector>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
using namespace std;

//NUM CROMOSOMAS->es el tamaño de la poblacion
//N_Nodes-> es el numero de ciudades que deben recorrerse

const int Num_Cromosomas = 100, N_Nodes = 7;

typedef struct  Chrom
{
    int bitx[N_Nodes];
    int bity[N_Nodes];
    double fit;
}chrom;

class AGenetico
{
	private:
		double crProb, MutationProb;
		chrom MejorCromosoma;
		chrom Poblacion[Num_Cromosomas];
		chrom Nueva_Poblacion[Num_Cromosomas];

	public:

		chrom recorrido;
		int check;
		int corrections = 0;

		AGenetico():Poblacion()
		{
			this->crProb = 0.85;
			this->MutationProb = 0.05;
			srand(time(NULL));
			check = 0;
            int random=0;
			//GENERACION DE LA POBLACION INICIAL
			for(int i = 0; i < Num_Cromosomas; i++)
			{
				for(int j = 0; j < N_Nodes; j++)
				{
					random = rand();
                    random = (random%2);
					Poblacion[i].bitx[j] = random;
                    random = rand();
                    random = (random%2);
					Poblacion[i].bity[j] = random;
				}
			}

			for(int i = 0; i < Num_Cromosomas; i++)
			{
				for(int j = 0; j < N_Nodes; j++)
				{
					cout<<Poblacion[i].bitx[j]<<", ";
					cout<<Poblacion[i].bity[j]<<", ";
				}
				cout<<endl;
			}
		}


        double f(double x,double y)
        {
			if((x > 100) and (x < -100))
			{
				x = rand() % 100;
			}

			if((y > 100) and (y < -100))
			{
				y = rand() % 100;
			}

            return ( 0.5 - (pow(sin(sqrt(pow(x,2) + pow(y,2))),2) - 0.5) / pow(1.0 + 0.001*(pow(x,2)+pow(y,2)),2) );
        }
        

        int converter(int* b)
        {
            int decimal = 0;
            int multiplicador = 1;
            int caracterActual;
            for (int i = N_Nodes - 1; i >= 0; i--) 
            {
                caracterActual = b[i];
                if (caracterActual == 1) 
                {
                    decimal += multiplicador;
                }
                multiplicador = multiplicador * 2;
            }
            return decimal;
        }

		void SigGeneracion()
		{
			double Pesos_Rutas[Num_Cromosomas];

			for(int i = 0; i < Num_Cromosomas; i++)
			{
				Pesos_Rutas[i] = f(converter(Poblacion[i].bitx),converter(Poblacion[i].bity));//(1/Distancia_Recorrida(Poblacion[i]));///GT
            }

			check++;
			
            int Index1 = 0, Index2 = 0;

			Index1 = max_element(Pesos_Rutas, Pesos_Rutas + Num_Cromosomas) - Pesos_Rutas;

			this->MejorCromosoma = Poblacion[Index1];

			double HFits = 0;
			
			for(int i = 0; i < Num_Cromosomas; i++)
			{
				if((i != Index1) and (Pesos_Rutas[i] > HFits))
				{
					HFits = Pesos_Rutas[i];
					Index2 = i;
				}
			}

			int Count = 0;

			//COPY NUEVAPOBLACION
			for(int i = 0; i < N_Nodes; i++)
			{
				Nueva_Poblacion[Count].bitx[i] = Poblacion[Index1].bitx[i];
                Nueva_Poblacion[Count].bity[i] = Poblacion[Index1].bity[i];
			}
			Count++;
			//copyToNueva_Poblacion
			for(int i = 0; i < N_Nodes; i++)
			{
				Nueva_Poblacion[Count].bitx[i] = Poblacion[Index2].bitx[i];
                Nueva_Poblacion[Count].bity[i] = Poblacion[Index2].bity[i];
			}
			Count++;
            int ix = 0;
			while(1) //ADD
			{
				chrom father;
				chrom mother;
				father = Selection(Pesos_Rutas,ix);
				mother = Selection(Pesos_Rutas,ix);

				/*while ((mother.bitx == father.bitx) and (mother.bity == father.bity))
				{
					mother = Selection(Pesos_Rutas,ix);
				}*/
                
				chrom ChilA;
				chrom ChilB;

				crossover(father, mother, ChilA, ChilB);
				Mutar_Cromosoma(ChilA);
				Mutar_Cromosoma(ChilB);
				
				for(int i = 0; i < N_Nodes; i++)
				{
					Nueva_Poblacion[Count].bitx[i] = ChilA.bitx[i];
                    Nueva_Poblacion[Count].bity[i] = ChilA.bity[i];
				}			
				Count++;
			
				if(Count == Num_Cromosomas)
				{
					break;
				}


				for(int i = 0; i < N_Nodes; i++)
				{
					Nueva_Poblacion[Count].bitx[i] = ChilB.bitx[i];
                    Nueva_Poblacion[Count].bity[i] = ChilB.bity[i];
				}				
				Count++;
				
				if(Count == Num_Cromosomas)
				{
					break;
				}
			}

			for(int i = 0; i < Num_Cromosomas; i++)
			{
				memcpy(Poblacion[i].bitx, Nueva_Poblacion[i].bitx,sizeof(int) * N_Nodes);
                memcpy(Poblacion[i].bity, Nueva_Poblacion[i].bity,sizeof(int) * N_Nodes);
			}
		}


		static double Random(double M)
		{
			return ((double)rand() * M) / (double)RAND_MAX;
		}

		chrom Selection(double *P_rutas,int &ix) const
		{	
            return Poblacion[(int)(((double)rand() * Num_Cromosomas) / ((double)RAND_MAX + 1))];
		}
		
        bool cmpfunc(const double a, const double b) 
        {
            return ( a < b);
        }

		void Mutar_Cromosoma(chrom &Cromosoma)
		{
			double random = Random(1);
			if(random > MutationProb)
			{
				return;
			}			

			int tmp;
			int random1 = (int)(((double)rand() * N_Nodes) / ((double)RAND_MAX + 1));//(int)random
			int random2 = (int)(((double)rand() * N_Nodes) / ((double)RAND_MAX + 1));
			while(random1 == random2)
			{
				random2 = (int)(((double)rand() * N_Nodes) / ((double)RAND_MAX + 1));
			}

			tmp = Cromosoma.bitx[random1];
			Cromosoma.bitx[random1] = Cromosoma.bitx[random2];
			Cromosoma.bitx[random2] = tmp;

            tmp = Cromosoma.bity[random1];
			Cromosoma.bity[random1] = Cromosoma.bity[random2];
			Cromosoma.bity[random2] = tmp;
		}
		
		void crossover(chrom father, chrom mother, chrom &ChilA, chrom &ChilB)
		{
			double random = Random(1);
			if(random > crProb)
			{
				memcpy(ChilA.bitx,father.bitx,sizeof(int) * N_Nodes); 
				memcpy(ChilB.bitx, mother.bitx, sizeof(int) * N_Nodes);

                memcpy(ChilA.bity,father.bity,sizeof(int) * N_Nodes); 
				memcpy(ChilB.bity, mother.bity, sizeof(int) * N_Nodes);
				return;
			}

			int C_Index1 = (int)Random(N_Nodes);
			int C_Index2 = (int)Random(N_Nodes);

			while(C_Index2 == C_Index1)
			{
				C_Index2 = (int)(((double)rand() * N_Nodes) / ((double)RAND_MAX + 1));
			}

			int start;
			int end;
			if(C_Index1 < C_Index2)
			{
				start = C_Index1;
				end = C_Index2;
			}
			else
			{
				start = C_Index2;
				end = C_Index1;
			}
			
			memcpy(ChilA.bitx,father.bitx,sizeof(int)*N_Nodes);
			memcpy(ChilB.bitx,mother.bitx,sizeof(int)*N_Nodes);
			memcpy(ChilA.bity,father.bity,sizeof(int)*N_Nodes);
			memcpy(ChilB.bity,mother.bity,sizeof(int)*N_Nodes);

			memcpy(ChilA.bitx + start,mother.bitx + start,sizeof(int)*(end - start));
			memcpy(ChilB.bitx + start,father.bitx + start,sizeof(int)*(end - start));		
			memcpy(ChilA.bity + start,mother.bity + start,sizeof(int)*(end - start));
			memcpy(ChilB.bity + start,father.bity + start,sizeof(int)*(end - start));		


			for(int i = 0; i < N_Nodes; i++)
			{

				if((i  >= start) and (i  < end)) 
				{
				}
				else
				{
					
					for(int j = start; j < end; j++)
					{
						if(ChilA.bitx[i] == ChilA.bitx[j])
						{
							ChilA.bitx[i] = -1;
						}
						if(ChilB.bitx[i] == ChilB.bitx[j])
						{
							ChilB.bitx[i] = -1;
						}
					}
				}
			}

			for(int i = 0; i < N_Nodes; i++)
			{
				if(ChilA.bitx[i] == -1)
				{
					//repair
					for(int j = 0; j < N_Nodes; j++)
					{
						int * missing = find(ChilA.bitx, ChilA.bitx + N_Nodes, ChilB.bitx[j]);

						if(missing == (ChilA.bitx + N_Nodes))
						{
							ChilA.bitx[i] = ChilB.bitx[j];
							break;
						}
					}
				}

				if(ChilB.bitx[i] == -1)
				{
					//repair
					for(int j = 0; j < N_Nodes; j++)
					{
						int * missing = find(ChilB.bitx, ChilB.bitx + N_Nodes, ChilA.bitx[j]);

						if(missing == (ChilB.bitx + N_Nodes))
						{
							ChilB.bitx[i] = ChilA.bitx[j];
							break;
						}
					}
				}
			}

		}
		
		bool Duplicado_Cromosoma(chrom cromosoma, int populationCount)  // evita la existencia de cromosomas identicos
		{
			for(int i = 0; i < populationCount; i++)
			{
				if(check < populationCount)
				{
					corrections = check;
				}
				else
				{
					corrections = populationCount;
				}

				int Count = 0;
				for(int j = 0; j < N_Nodes; j++)
				{
					if(cromosoma.bitx[j] != Nueva_Poblacion[i].bitx[j])
					{
						break;
					}
					Count++;
				}

				if(Count == N_Nodes)
				{
					return true;
				}
			}
			return false;
		}

		void start(int iter)
		{
			int  num_generation = 0;
			double val = -1;
            cout<<"\n"<<endl;
			cout<<"MEJORA DE LA SOLUCION POR ITERACION"<<endl;
			cout<<"\n"<<endl;
			while(num_generation < iter)
			{
				SigGeneracion();
                
				double newP = f(converter(MejorCromosoma.bitx),converter(MejorCromosoma.bity)); //(1/Distancia_Recorrida(MejorCromosoma));
				if(newP > val)
				{
					val = newP;
					//printf("Iteracion en que mejora: %i : %0.6f \n",num_generation,newP);
					cout<<num_generation<<","<<val<<endl;
				}
				
                num_generation++;
			}

			cout<<endl;
		}
};




int main(int argc,char** argv)
{
    //INICIA LAS OPERACIONES con un numero de iteraciones de 100
	AGenetico *ga = new AGenetico();
	ga->start(40000);

	return 0;
}