#include <iostream>
#include <cmath>
#include <time.h>
#include <string>

using namespace std;

double func1(double x)
{
    return -x*x;
}

double f(double x,double y)
{
    return pow(100*(pow(x,2)-y),2) + pow(1-x,2);
}

double N_random(double mm, double nn) 
{
    return (double)(mm + rand() / (RAND_MAX / (nn - mm + 1.0) + 1.0));
}

double next_move(double x)
{
    return x + N_random(-0.2048,0.2048);
}

void next_move2(double &x, double &y)
{
    double xt, yt;
    xt = x + N_random(-0.2048,0.2048);
    yt = y + N_random(-0.2048,0.2048);

    if(xt <= 2.048 and xt >= -2.048)
    {
        x = xt; 
    }

    if(yt <= 2.048 and yt >= -2.048)
    {
        y = xt;
    }
}

void hill_climb(double x,int n)
{
    double current = x;
    double current_val= 0, next = 0;
    
    int i = 0;
    
    do
    {
        current_val = func1(current);
        next = next_move(current);
        
        if(func1(next) > current_val)
        {
            current = next;
            //cout<<current<<" "<< current_val<<endl;
        }
        
        cout<<current<<" "<< current_val<<endl;
         
        i++;
    }while(i <= n);
    
    return;
}

void hill_climb2(double x,double y,int n)
{
    double current_x = x;
    double current_y = y;
    double temp_x = 0,temp_y = 0;
    double current_val= 0, next = 0;
    
    int i = 0;
    srand (time(NULL));

    do
    {
        current_val = f(current_x,current_y);
        temp_x = current_x;
        temp_y = current_y;
        
        next_move2(temp_x,temp_y);
        
        if(f(temp_x,temp_y) > current_val)
        {
            current_x = temp_x;
            current_y = temp_y;
            //cout<<current_x<<" "<< current_y<<endl;
        }
        cout<<f(current_x,current_y)<<endl;
        i++;
    }while(i <= n);
}


////////////////////////////////////////////////////

#define N 10000


double pts[N] = { 0 };
double MU = 0.0;
double SIG = 1.0;



double q(double x) { 
  return (double) ((1.0/(sqrt(2.0*M_PI*pow(SIG,2.0)))*(exp(-(pow(x-MU,2.0)))/(2.0*pow(SIG,2.0)))));
}

double func3(double x,double y)
{
    return pow(100*(pow(x,2)-y),2)+pow(1-x,2);
}

void metropolis(int numIter, double *points) {
        double r = 0.0;
        double p = q(r);

        srand (time(NULL));

        int i = 0;
        while(i < numIter) {
                double rn = r + N_random(-1.0,0.0);
                double pn = q(rn);
                if (pn >= p) {
                        p = pn;
                        r = rn;
                } else {
                        double u = N_random(0.0,0.0); 
                        if(u < (double) (pn/p)) {
                                p = pn;
                                r = rn;
                        }
                }
                points[i] = r;
                i++;
        }
}

void metropolis2(int r1,int r2, int numIter, double *points) 
{
        double p = func3(r1,r2);

        srand (time(NULL));

        int i = 0;
        while(i < numIter) {
                double rn1 = r1 + N_random(-0.2048,0.2048);
                double rn2 = r2 + N_random(-0.2048,0.2048);
                double pn = func3(rn1,rn2);
                if (pn >= p) {
                        p = pn;
                        r1 = rn1;
                        r2 = rn2;
                } else {
                        double u = N_random(-0.2048,0.2048);
                        if(u < (double) (pn/p)) 
                        {
                                p = pn;
                                r1 = rn1;
                                r2 = rn2;
                        }
                }
                points[i] = r1;
                i++;
        }
}


int main()
{
    hill_climb2(0,0,100);
    
    metropolis2(0,0,N,pts);
    double temp = 0;
    for (int j = 0; j < N; j++) 
    {
        if(temp != pts[j])
        {
            temp = pts[j];
            cout<<pts[j]<<endl;
        }
    }
    return 0;
}