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
double *profits_july; // <---- sold_units_july * prices
double *utilities_july; // <---- profits_july - (sold_units_july * unit_costs)
double total_profit_july = 0; // <---- total of profits_july
double variable_costs_july = 45640.0;
double utility_july = 0; // <---- (total of utilities_july) - variable_costs_july

//August: Sold Units, profit per unit, utilities per unit, total profit of the month, variable costs
int sold_units_august[] = {250,380,800,250,600,1200,1540,15};
double *profits_august; // <---- sold_units_august * prices
double *utilities_august; // <---- profits_august - (sold_units_august * unit_costs)
double total_profit_august = 0; // <---- total of profits_august
double variable_costs_august = 40590.0;
double utility_august = 0; // <---- (total of utilities_august) - variable_costs_august

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//SUB-RUTINE SECTION
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//MAIN PROGRAM SECTION
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

void init();
void welcome();
void closing();

int main(){
    init();
    welcome();

    
    
    closing();
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
    //AUGUST
    profits_august = new double[8];
    utilities_august = new double[8];
}

void welcome(){
    cout << "\n---------------------------------------------------------" <<endl;
    cout << "Bienvenido a la parte 1 del Lab 4!" <<endl;
    cout << "- Jose Daniel Gomez Cabrera 21429 -" <<endl;
    cout << "---------------------------------------------------------"<<endl;
    cout << "Este es un programa de rentabilidad para &Cafe de UVG!"<<endl;
    cout << "---------------------------------------------------------"<<endl;
}

void closing(){
    cout << "---------------------------------------------------------"<<endl;
    cout << "- Muchas gracias por utilizar este programa!" << endl;
    cout << "- Vuelve Pronto!" << endl;
    cout << "---------------------------------------------------------"<<endl;
    cout << endl;
}

