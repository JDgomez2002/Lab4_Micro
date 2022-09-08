//Universidad del Valle de Guatemala
//Programacion de Microprocesadores
//Seccion 21
//Catedratico Roger Diaz
//Segundo Semestre 2022
//Jose Daniel Gomez Cabrera 21429
//Actividad: Laboratorio 4 Parte 2

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
using namespace std;

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//VARIABLES SECTION
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

//Packaching queue
int packaging_queue = 0;

//Celar
int coffee_celar = 0;

//coffee order amount
int total_coffee_amount;
int *coffee_order_amounts; //separate amounts for both threads

//Mutex
pthread_mutex_t coffee_mutex;

//Conditional variable
pthread_cond_t conditional_variable;

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//SUBRUTINE SECTION
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

//Coffee machines
void* toaster(void* arg){
    long tID = (long)arg;
    for(int i = 0; i<(coffee_order_amounts[tID]) ;i++){
        pthread_mutex_lock(&coffee_mutex);
        packaging_queue++;
        cout << "Tostadora " << (tID+1) << ": 1 lb producida" << endl;
        pthread_mutex_unlock(&coffee_mutex);
        pthread_cond_signal(&conditional_variable);
        sleep(1);
    }
    return 0;
}

//Packaging machine
void* packager(void* arg){
    for(int i = 0; i<total_coffee_amount ;i++){
        pthread_mutex_lock(&coffee_mutex);
        if((packaging_queue+coffee_celar)<total_coffee_amount){
            while(packaging_queue < 5){
                printf("\nSin cantidad minima para empacar (5)...\n\n");
                pthread_cond_wait(&conditional_variable, &coffee_mutex);
            }
        }
        packaging_queue--;
        printf("\nLa Empacadora empaco 1lb de cafe.\n   Cantidad en silo: %d\n", packaging_queue);
        coffee_celar++;
        printf("   Cantidad en Bodega: %d\n\n", coffee_celar);
        pthread_mutex_unlock(&coffee_mutex);
        sleep(1);
    }
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//MAIN SECTION
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

void welcome();
void closing();
void request_coffee_amount();
void show_results();

int main(int argc, char* argv[]){
    welcome();
    request_coffee_amount();

    pthread_t th[3];
    pthread_mutex_init(&coffee_mutex, NULL);
    pthread_cond_init(&conditional_variable, NULL);

    long i;

    for(i = 0; i < 3; i++){
        if(i == 2){
            pthread_create(&th[i], NULL, &packager, (void *)i);
        }
        else{
            pthread_create(&th[i], NULL, &toaster, (void *)i);
        }
    }

    for(int j = 0; j < 3; j++){
        pthread_join(th[j], NULL);
    }

    show_results();
    closing();
    
    pthread_mutex_destroy(&coffee_mutex);
    pthread_cond_destroy(&conditional_variable);
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//FUNCTIONS SECTION
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------

void welcome(){
    cout << "\n---------------------------------------------------------" << endl;
    cout << "Bienvenido a la parte 2 del Lab 4!" << endl;
    cout << "- Jose Daniel Gomez Cabrera 21429 -" << endl;
    cout << "---------------------------------------------------------"<< endl;
    cout << "Este es un programa de produccion de cafe molido!"<< endl;
    cout << "---------------------------------------------------------\n"<< endl;
}

void closing(){
    cout << "\n---------------------------------------------------------"<< endl;
    cout << "- Muchas gracias por utilizar este programa!" << endl;
    cout << "- Vuelve Pronto!" << endl;
    cout << "---------------------------------------------------------"<< endl;
    cout << endl;
}

void request_coffee_amount(){
    // int coffee_order;
    coffee_order_amounts = new int[2];
    cout << "Ingrese la cantidad de bolsas de cafe a entregar >> ";
    cin >> total_coffee_amount;
    if((total_coffee_amount%2)==0){
        coffee_order_amounts[0] = total_coffee_amount/2;
        coffee_order_amounts[1] = total_coffee_amount/2;
    }
    else{
        coffee_order_amounts[0] = total_coffee_amount/2;
        coffee_order_amounts[1] = (total_coffee_amount/2)+1;
    }
    cout << "\n" << endl;
    cout << "Produciendo " << total_coffee_amount << " Libras de cafe!" << endl;
    cout << "---------------------------------------------------------"<< endl;
}

void show_results(){
    cout << "---------------------------------------------------------"<< endl;
    cout << "\nSe ha completado la produccion!" << endl;
    cout << "\nEstado de la Bodega: " << total_coffee_amount << " Libras de Cafe!" << endl;
    
}