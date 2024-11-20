#ifndef _PLANIFICADOR_H_
#define _PLANIFICADOR_H_

#define WIN32_LEAN_AND_MEAN  //excluye partes innecesarias de la cabecera windows.h
#include <windows.h>

#include "cola.h"
#include "procesos.h"
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Planificador {
private:
    Cola<T> colaProcesos;  //cola para almacenar procesos
    int quantum;           //quantum fijo para Round Robin

public:
    Planificador(int quantum);
    void agregarProceso(T* proceso);
    void ejecutarRoundRobin();
    void ejecutarPorPrioridad();
};

//constructor
template <typename T>
Planificador<T>::Planificador(int quantum) : quantum(quantum) {}

// agrega un proceso a la cola
template <typename T>
void Planificador<T>::agregarProceso(T* proceso) {
    colaProcesos.push(proceso);
}

//Round Robin
template <typename T>
void Planificador<T>::ejecutarRoundRobin() {
    while (true) {
        // Obtener el siguiente proceso de la cola
        T* proceso = colaProcesos.pop();
        if (proceso == nullptr) {
            break;
        }

        if (proceso->getEstado() == "finalizado") {
            continue;
        }

        proceso->cambiarEstado("en ejecución");
        cout << "Ejecutando: " << proceso->getNombre() << " (Quantum: " << quantum << ")\n";

        //ejecutar el proceso durante el quantum o hasta que termine
        for (int i = 0; i < quantum; ++i) {
            if (proceso->getEstado() == "finalizado") {
                cout << "Proceso " << proceso->getNombre() << " ha finalizado durante la ejecución.\n";
                break;
            }

            proceso->ejecutarInstruccion();
            Sleep(100); // Simula 1 segundo de ejecución
        }

        if (proceso->getEstado() == "finalizado") {
            cout << "Proceso " << proceso->getNombre() << " ha terminado. No será reinsertado en la cola.\n";
        } else {
            proceso->cambiarEstado("listo");
            colaProcesos.push(proceso);
            cout << "Proceso " << proceso->getNombre() << " reinsertado en la cola para continuar en la siguiente iteración.\n";
        }
    }

    cout << "Round Robin completado. Todos los procesos han sido gestionados.\n";
}

//por Prioridad
template <typename T>
void Planificador<T>::ejecutarPorPrioridad() {
    //nueva cola para almacenar los procesos ordenados
    Cola<T> colaOrdenada;

    while (true) {
        T* procesoActual = colaProcesos.pop();
        if (procesoActual == nullptr) {
            break;
        }

        //insertar en la cola segun la prioridad
        if (colaOrdenada.cabeza == nullptr) {
            colaOrdenada.push(procesoActual);
        } else {
            Nodo<T>* anterior = nullptr;
            Nodo<T>* actual = colaOrdenada.cabeza;
            while (actual != nullptr && actual->dato->getPrioridad() >= procesoActual->getPrioridad()) {
                anterior = actual;
                actual = actual->sig;
            }
            //nuevo nodo para el proceso actual
            Nodo<T>* nuevoNodo = new Nodo<T>(procesoActual);
            if (anterior == nullptr) {
                nuevoNodo->sig = colaOrdenada.cabeza;
                colaOrdenada.cabeza = nuevoNodo;
            } else {
                nuevoNodo->sig = actual;
                anterior->sig = nuevoNodo;
            }
        }
    }
    //ejecutar en orden de prioridad
    while (true) {
        T* proceso = colaOrdenada.pop();
        if (proceso == nullptr) {
            break;  
        }

        if (proceso->getEstado() != "finalizado") {
            proceso->cambiarEstado("en ejecución");
            cout << "Ejecutando: " << proceso->getNombre() << " (Prioridad: " << proceso->getPrioridad() << ")\n";

            while (proceso->getEstado() != "finalizado") {
                proceso->ejecutarInstruccion();
                Sleep(100);  // Simula 1 ciclo por instrucción
            }
        }
    }
    cout << "Ejecución por prioridad completada.\n";
}

#endif