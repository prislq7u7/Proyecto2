#ifndef _PLANIFICADOR_H_
#define _PLANIFICADOR_H_

#define WIN32_LEAN_AND_MEAN  //excluye partes innecesarias de la cabecera windows.h
#include <windows.h>

#include "cola.h"
#include "procesos.h"
#include <iostream>
#include <string>
#include <fstream> 

using namespace std;

template <typename T>
class Planificador {
private:
    Cola<T> colaProcesos;  //cola para almacenar procesos
    int quantum;           //quantum fijo para Round Robin

public:
    Planificador(int quantum);
    void agregarProceso(T* proceso);
    string ejecutarRoundRobin();
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
std::string Planificador<T>::ejecutarRoundRobin() {
    std::string nombreArchivo = "resultado_round_robin.txt";
    std::ofstream archivo(nombreArchivo); // Crea/abre el archivo de texto

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para escribir.\n";
        return "";
    }

    int iteracion = 0; // Para contar las iteraciones
    while (true) {
        archivo << "Iteración: " << ++iteracion << "\n";
        cout << "Iteración: " << iteracion << "\n";

        archivo << "Estado actual de la cola:\n" << colaProcesos.toString() << "\n";
        cout << "Estado actual de la cola:\n" << colaProcesos.toString() << "\n";

        // Obtener el siguiente proceso de la cola
        T* proceso = colaProcesos.pop();
        if (proceso == nullptr) {
            archivo << "La cola está vacía. Terminando Round Robin.\n";
            cout << "La cola está vacía. Terminando Round Robin.\n";
            break;
        }

        archivo << "Proceso actual: " << proceso->getNombre() << " (Estado: " << proceso->getEstado() << ")\n";
        cout << "Proceso actual: " << proceso->getNombre() << " (Estado: " << proceso->getEstado() << ")\n";

        if (proceso->getEstado() == "finalizado") {
            archivo << "Proceso " << proceso->getNombre() << " ya finalizado. No será procesado nuevamente.\n";
            cout << "Proceso " << proceso->getNombre() << " ya finalizado. No será procesado nuevamente.\n";
            continue;
        }

        proceso->cambiarEstado("en ejecución");
        archivo << "Ejecutando proceso: " << proceso->getNombre() << "\n";
        cout << "Ejecutando proceso: " << proceso->getNombre() << "\n";

        // Ejecutar el proceso durante el quantum o hasta que termine
        for (int i = 0; i < quantum; ++i) {
            archivo << "Ejecutando instrucción " << (i + 1) << " de " << quantum << "\n";
            cout << "Ejecutando instrucción " << (i + 1) << " de " << quantum << "\n";

            if (proceso->getEstado() == "finalizado") {
                archivo << "Proceso " << proceso->getNombre() << " ha finalizado durante la ejecución.\n";
                cout << "Proceso " << proceso->getNombre() << " ha finalizado durante la ejecución.\n";
                break;
            }
            proceso->ejecutarInstruccion();
            Sleep(100); // Simula 1 segundo de ejecución
        }

        if (proceso->getEstado() != "finalizado") {
            archivo << "Proceso " << proceso->getNombre() << " no terminó. Cambiando estado a 'listo'.\n";
            cout << "Proceso " << proceso->getNombre() << " no terminó. Cambiando estado a 'listo'.\n";
            proceso->cambiarEstado("listo");
            colaProcesos.push(proceso);
        } else {
            archivo << "Proceso " << proceso->getNombre() << " ha sido completado.\n";
            cout << "Proceso " << proceso->getNombre() << " ha sido completado.\n";
        }
    }

    archivo << "Round Robin completado. Todos los procesos han sido gestionados.\n";
    cout << "Round Robin completado. Todos los procesos han sido gestionados.\n";

    archivo.close(); // Cierra el archivo al finalizar
    return nombreArchivo; // Devuelve el nombre del archivo generado
}


//por Prioridad
template <typename T>
void Planificador<T>::ejecutarPorPrioridad() {
    cout << "Ordenando procesos por prioridad...\n";
    Cola<T> colaOrdenada;

    while (true) {
        T* procesoActual = colaProcesos.pop();
        if (procesoActual == nullptr) {
            break;
        }

        cout << "Insertando proceso: " << procesoActual->getNombre() << " con prioridad " << procesoActual->getPrioridad() << "\n";

        if (colaOrdenada.cabeza == nullptr) {
            colaOrdenada.push(procesoActual);
        } else {
            Nodo<T>* anterior = nullptr;
            Nodo<T>* actual = colaOrdenada.cabeza;
            while (actual != nullptr && actual->dato->getPrioridad() >= procesoActual->getPrioridad()) {
                anterior = actual;
                actual = actual->sig;
            }
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

    cout << "Ejecutando procesos en orden de prioridad...\n";
    while (true) {
        T* proceso = colaOrdenada.pop();
        if (proceso == nullptr) {
            cout << "Todos los procesos han sido ejecutados.\n";
            break;
        }

        if (proceso->getEstado() != "finalizado") {
            cout << "Ejecutando proceso: " << proceso->getNombre() << " (Prioridad: " << proceso->getPrioridad() << ")\n";

            while (proceso->getEstado() != "finalizado") {
                proceso->ejecutarInstruccion();
                Sleep(100); // Simula 1 ciclo por instrucción
            }

            cout << "Proceso " << proceso->getNombre() << " finalizado.\n";
        }
    }
    cout << "Ejecución por prioridad completada.\n";
}


#endif