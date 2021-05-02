/*******************************************************************************************************/
/***                                                                                                 ***/
/***  The Classical Hodgkin-Huxley model. Version 0.01                                               ***/
/***  By Mehran Noori                                                                                ***/
/***  Date : 1400/02/10                                                                              ***/
/***                                                                                                 ***/
/***  The following code is developed in C++ by GNU C++ compiler (v.10.2.0) in 64-bit Manjaro 21     ***/
/***                                                                                                 ***/
/*******************************************************************************************************/

/*
 *
 * Compile this code in the Linux shell by:
 *   $ c++ -std=c++11 hh-main-euler.cpp -o hh-euler.out
 * 
 * then execute it in the shell by:
 *   $ ./hh-main.out
 * 
 * program create a data file "hh_data_euler.txt"
 * use "plot.py" script to see plot
 * 
 */

#include <iostream>
#include <fstream>
#include <ctime>
#include <math.h>

using namespace std;

/****************************** Const and variables *******************************/
const double g_Na = 120,
             g_K  = 36,
             g_L  = 0.3,        // mS/cm^2
             v_Na = 45,
             v_K  = -82,
             v_L  = -59,        // mV
             C_m  = 1;          // micro farad

ofstream file_object;           // make an object to creat a file for saving datas
std::string file_name = "hh_data_euler.txt";

double t       = 0.,             // time and time step (ms)
       t_final = 100.,
       delta_t = 0.01;
       //steps = 0;

double V = -70.,
       m = 0.,
       h = 0.,
       n = 0.,
       I = 10.;

/****************************** functions initiation ******************************/
void init();                   // initials values function
void run();
void done();

double alpha_m(double);
double alpha_h(double);
double alpha_n(double);
double beta_m(double);
double beta_h(double);
double beta_n(double);

double f_v(double,double,double,double);
double f_x(double,double,double);

/*********************************** calculate  ***********************************/
int main(){ ///////////////// main function ////////////////
    cout << "\tThe Classical Hodgkin-Huxley model\n";
    cout << "\tBy Mehran Noori\t Version 0.01\n";
    cout << "\n\tprogram in running\n";

    clock_t runtime = clock();

    init();
    run();
    done();

    cout <<"\tRunime : "<< (double)(clock() - runtime)/CLOCKS_PER_SEC <<"sec"<< endl;
}

void init(){ /////////////// initial function ///////////////
    m = alpha_m(V) / (alpha_m(V) + beta_m(V));
    h = alpha_h(V) / (alpha_h(V) + beta_h(V));
    n = alpha_n(V) / (alpha_n(V) + beta_n(V));

    file_object.open(file_name);
    /* inside the tada file is like bellow
               #t   v    m    h    n
               .    .    .    .    .
               .    .    .    .    .
                        ...
               .    .    .    .    .
     **************************************/
}

void run(){///////calculate V, m, n, h and save to file/////// 
    file_object << "#t:v:m:h:n\n";
    do{
        file_object << t <<','<< V <<','<< m <<','<< h <<','<< n << endl;
        V = delta_t * f_v(V,m,h,n) + V;
        m = delta_t * f_x(m ,alpha_m(V), beta_m(V)) + m;
        h = delta_t * f_x(h ,alpha_h(V), beta_h(V)) + h;
        n = delta_t * f_x(n ,alpha_n(V), beta_n(V)) + n;
        
        t = t + delta_t;
    }
    while (t <= t_final);
}

void done(){/////////// It's not neccessary ////////////
    file_object.close();
    cout << "\tDone\n";
    cout <<"\t\""<< file_name << "\" created and datas is stored\n"
         << "\tRun plot.py script to see the plot.\n";
}

/**********************************************************************************/
double alpha_m(double v){
    return (0.1*(v+45.)) / (1.-exp(-0.1*(v+45.)));
}
double alpha_h(double v){
    return 0.07 * exp(-(v+70.)/20.);
}
double alpha_n(double v){
    return 0.01 * (v+60.) / (1. - exp( -0.1*(v+60) ));
}
double beta_m(double v){
    return 4. * exp( -(v+70.)/18. );
}
double beta_h(double v){
    return 1. / (1 + exp( -0.1*(v+40.) ));
}
double beta_n(double v){
    return (1./8.) * exp(-(v+70.)/80.);
}
/**********************************************************************************/
double f_v(double v,double m,double h,double n){
    return (I-g_Na*pow(m,3)*h*(v-v_Na)-g_K*pow(n,4)*(v-v_K)-g_L*(v-v_L))/C_m;
}
double f_x(double x, double alpha, double beta){
     return alpha * (1 - x) - beta * x;
}