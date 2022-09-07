//Universidad del Valle de Guatemala
//Programacion de Microprocesadores
//Seccion 21
//Catedratico Roger Diaz
//Segundo Semestre 2022
//Jose Daniel Gomez Cabrera 21429
//Actividad: Laboratorio 4 Parte 1

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
using namespace std;

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//VARIABLES SECTION
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

//Products
string products[] = {"Pastel de chocolate","White mocha","Cafe Americano","Latte 8onz","Toffee coffee","Cappuccino 8onz","S'mores Latte","Cafe tostado molido"};

//Prices
double prices[] = {60.0, 32.0, 22.0, 24.0, 28.0, 24.0, 32.0, 60.0};

//Unit cost
double unit_costs[] = {20.0,19.20,13.20,17.20,20.10,17.20,23.00,20.00};

//July: Sold Units, profit per unit, utilities per unit, total profit of the month, variable costs
int sold_units_july[] = {300,400,1590,200,390,1455,800,60};
double *profits_july; // [8] <---- sold_units_july * prices
double *utilities_july; // [8] <---- profits_july - (sold_units_july * unit_costs)
double total_profit_july = 0; // <---- total of profits_july
double variable_costs_july = 45640.0;
double utility_july = 0; // <---- (total of utilities_july) - variable_costs_july
bool july_finished = false;
int *july_pthreads_finished_state;

//August: Sold Units, profit per unit, utilities per unit, total profit of the month, variable costs, 
int sold_units_august[] = {250,380,800,250,600,1200,1540,15};
double *profits_august; // [8] <---- sold_units_august * prices
double *utilities_august; // [8] <---- profits_august - (sold_units_august * unit_costs)
double total_profit_august = 0; // <---- total of profits_august
double variable_costs_august = 40590.0;
double utility_august = 0; // <---- (total of utilities_august) - variable_costs_august
bool august_finished = false;
int *august_pthreads_finished_state;

//Mutex for Pthread printing
bool printing = true;

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//SUB-RUTINE SECTION
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

void *evaluate_products(void *pthread_number){
    long tID = (long)pthread_number;
    if(tID<8){
        //Profit per unit
        profits_july[tID] = sold_units_july[tID] * prices[tID];

        //Utility per unit
        utilities_july[tID] = profits_july[tID] - (sold_units_july[tID] * unit_costs[tID]);
        july_pthreads_finished_state[tID] = 1; //Utility finished!!! it is for line 72 and 82

        //Total profit of the month
        total_profit_july += profits_july[tID];

        //Evaluate if the pthreads finished of calculate utilities_july array
        july_finished = true;
        int counter = 0;
        while((july_finished)&&(counter<8)){
            if(july_pthreads_finished_state[counter]==0){
                july_finished = false;
            }
            counter++;
        }

        //if them finished, calculate utility of the month
        if(july_finished){
            //Eureka!
            double total_utility = 0;
            for(int k = 0; k<8 ;k++){
                total_utility += utilities_july[k];
            }
            utility_july = total_utility-variable_costs_july;
        } 

        //Mutex
        while(!printing){}
        printing = false;
        cout << "Thread " << tID  <<": " << products[tID] << " de Julio" << endl; 
        printing = true;     
    }
    else{
        tID = tID-8;

        //Profit per unit
        profits_august[tID] = sold_units_august[tID]*prices[tID];
        
        //Utility per unit
        utilities_august[tID] = profits_august[tID] - (sold_units_august[tID] * unit_costs[tID]);
        august_pthreads_finished_state[tID] = 1; //Utility finished!!! it is for line 105 and 115

        //Total profit of the month
        total_profit_august += profits_august[tID];

        //Evaluate if the pthreads finished of calculate utilities_august array
        august_finished = true;
        int counter = 0;
        while((august_finished)&&(counter<8)){
            if(august_pthreads_finished_state[counter]==0){
                august_finished = false;
            }
            counter++;
        }

        //if them finished, calculate utility of the month
        if(july_finished){
            //Eureka!
            double total_utility = 0;
            for(int k = 0; k<8 ;k++){
                total_utility += utilities_august[k];
            }
            utility_august = total_utility-variable_costs_august;
        }

        //Mutex
        while(!printing){}
        printing = false;
        cout << "Thread " << (tID+8)  <<": " << products[tID] << " de Agosto" << endl;         
        printing = true;
    }
}

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//MAIN PROGRAM SECTION
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

void init();
void welcome();
void closing();
void creating_pthreads();
void show_results();
void show_july();
void show_august();

int main(){
    init();
    welcome();
    creating_pthreads();

    int rc;
    long i;
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //FOR TO CREATE PTHREADS
    for(i = 0; i<16; i++){
        rc = pthread_create(&tid, &attr, evaluate_products, (void *)i);
    }

    //FOR TO EXECUTE JOIN
    for(i = 0; i<16; i++){
        rc = pthread_join(tid, NULL);
    }
    
    show_results();
    closing();

    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//FUNCTIONS SECTION
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

void init(){
    //JULY
    profits_july = new double[8];
    utilities_july = new double[8];
    july_pthreads_finished_state = new int[8];
    //AUGUST
    profits_august = new double[8];
    utilities_august = new double[8];
    august_pthreads_finished_state = new int[8];
}

void welcome(){
    cout << "\n---------------------------------------------------------" << endl;
    cout << "Bienvenido a la parte 1 del Lab 4!" << endl;
    cout << "- Jose Daniel Gomez Cabrera 21429 -" << endl;
    cout << "---------------------------------------------------------"<< endl;
    cout << "Este es un programa de rentabilidad para &Cafe de UVG!"<< endl;
    cout << "---------------------------------------------------------"<< endl;
}

void closing(){
    cout << "---------------------------------------------------------"<< endl;
    cout << "- Muchas gracias por utilizar este programa!" << endl;
    cout << "- Vuelve Pronto!" << endl;
    cout << "---------------------------------------------------------"<< endl;
    cout << endl;
}

void creating_pthreads(){
    cout << "\nCreando Pthreads...\nPthreads creados con exito!...\nProcesando datos de &Cafe!" << endl;
    cout << "\n-------- PTHREADS --------\n" << endl;
}

void show_results(){
    cout << "\n---------------------------------------------------------"<< endl;
    cout << "---------------------- RESULTADOS! ----------------------" << endl;
    cout << "---------------------------------------------------------\n\n"<< endl;
    show_july();
    cout << "\n" << endl;
    show_august();
    cout << "\n" << endl;
}

void show_july(){
    cout << "------------- JULIO -------------" << endl;
    cout << "Ventas de Julio:"<< endl;
    for(int j = 0; j<8; j++){
        cout << "     " << products[j] << ": Q " << profits_july[j] << endl;
        cout << "           " << "Utilidad: Q " << utilities_july[j] << "\n" << endl;
    }
    cout << "Total de ventas: Q " << total_profit_july << endl;
    cout << "Costos Variables: Q " << variable_costs_july << endl;
    cout << "Utilidad del mes: Q " << utility_july << endl;
    cout << "-------------------------------" << endl;
}

void show_august(){
    cout << "------------ AGOSTO -------------" << endl;
    cout << "Ventas de Agosto:"<< endl;
    for(int j = 0; j<8; j++){
        cout << "     " << products[j] << ": Q " << profits_august[j] << endl;
        cout << "           " << "Utilidad: Q " << utilities_august[j] << "\n" << endl;
    }
    cout << "\nTotal de ventas: Q " << total_profit_august << endl;
    cout << "Costos Variables: Q " << variable_costs_august << endl;
    cout << "Utilidad del mes: Q " << utility_august << endl;
    cout << "---------------------------------" << endl;
}
