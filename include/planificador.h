#ifndef _PLANIFICADOR_H_
#define _PLANIFICADOR_H_

#include "cola.h"
#include "procesos.h"
#include <iostream>
#include <string>
#include <fstream> 
#include <thread>
#include <chrono>


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
string Planificador<T>::ejecutarRoundRobin() {
    string nombreArchivo = "resultado_round_robin.txt";
    ofstream archivo(nombreArchivo); // Crea/abre el archivo de texto

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para escribir.\n";
        return "";
    }

    int iteracion = 0; // Para contar las iteraciones
    while (true) {
        archivo << "Iteracion: " << ++iteracion << "\n";
        cout << "Iteracion: " << iteracion << "\n";

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
            archivo << "Proceso " << proceso->getNombre() << " ya finalizado\n";
            cout << "Proceso " << proceso->getNombre() << " ya finalizado\n";
            continue;
        }

        proceso->cambiarEstado("en ejecucion");
        proceso->cambiarSubestado("activo");

        archivo << "Ejecutando proceso: " << proceso->getNombre() << "\n"
                << "Estado actual: " << proceso->getEstado() << "\n"
                << "Subestado: " << proceso->getSubestado() << "\n";

        cout << "Ejecutando proceso: " << proceso->getNombre() << "\n"
            << "Estado actual: " << proceso->getEstado() << "\n"
            << "Subestado: " << proceso->getSubestado() << "\n";


        // ejecuta el proceso durante el quantum o hasta que termine
        for (int i = 0; i < quantum; ++i) {
            archivo << "Ejecutando instruccion " << (i + 1) << " de " << quantum << "\n";
            cout << "Ejecutando instruccion " << (i + 1) << " de " << quantum << "\n";

            if (proceso->getEstado() == "finalizado") {
                archivo << "Proceso " << proceso->getNombre() << " ha finalizado durante la ejecucion\n";
                cout << "Proceso " << proceso->getNombre() << " ha finalizado durante la ejecucion\n";
                break;
            }
            proceso->ejecutarInstruccion();
            this_thread::sleep_for(chrono::milliseconds(1000)); // Simula 1 segundo de ejecucion
        }

            if (proceso->getEstado() != "finalizado") {
            proceso->cambiarSubestado("cortado");

            archivo << "Proceso " << proceso->getNombre() << " no termino\n"
                    << "Estado actual: " << proceso->getEstado() << "\n"
                    << "Subestado: " << proceso->getSubestado() << "\n";

            cout << "Proceso " << proceso->getNombre() << " no termino\n"
                << "Estado actual: " << proceso->getEstado() << "\n"
                << "Subestado: " << proceso->getSubestado() << "\n";

            proceso->cambiarEstado("listo");
            colaProcesos.push(proceso);

            } else {
            proceso->cambiarSubestado("");
            archivo << "Proceso " << proceso->getNombre() << " ha sido completado\n";
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
    cout << "Ordenando procesos por prioridad\n";
    Cola<T> colaOrdenada;

    // extrae todos los procesos de la cola original
    while (true) {
        T* procesoActual = colaProcesos.pop();
        if (procesoActual == nullptr) {
            break;
        }
        cout << "Insertando proceso: " << procesoActual->getNombre() 
             << " con prioridad " << procesoActual->getPrioridad() << "\n";

        Nodo<T>* nuevoNodo = new Nodo<T>(procesoActual);
        if (colaOrdenada.cabeza == nullptr) {
            colaOrdenada.cabeza = nuevoNodo;
        } else {
            Nodo<T>* anterior = nullptr;
            Nodo<T>* actual = colaOrdenada.cabeza;
            while (actual != nullptr && actual->dato->getPrioridad() <= procesoActual->getPrioridad()) {
                anterior = actual;
                actual = actual->sig;
            }

            if (anterior == nullptr) {
                // Insercion al inicio de la lista
                nuevoNodo->sig = colaOrdenada.cabeza;
                colaOrdenada.cabeza = nuevoNodo;
            } else {
                // Insercion en el medio o al final
                nuevoNodo->sig = actual;
                anterior->sig = nuevoNodo;
            }
        }
    }

    // ejecuta procesos en orden de prioridad
    cout << "Ejecutando procesos en orden de prioridad\n";
    while (true) {
        T* proceso = colaOrdenada.pop();
        if (proceso == nullptr) {
            cout << "Todos los procesos han sido ejecutados\n";
            break;
        }

        cout << "Ejecutando proceso: " << proceso->getNombre() 
             << " (Prioridad: " << proceso->getPrioridad() << ")\n";

        proceso->cambiarEstado("en ejecucion");
        proceso->cambiarSubestado("activo");
        cout << "Estado actual: " << proceso->getEstado() << " "
        << "Subestado: " << proceso->getSubestado() << endl;

        while (proceso->getEstado() != "finalizado") {
            proceso->ejecutarInstruccion();
            this_thread::sleep_for(chrono::milliseconds(1000)); // Simula 1 ciclo por instruccion
        }

        proceso->cambiarSubestado("");
        cout << "Proceso " << proceso->getNombre() << " finalizado\n";
    }

    cout << "Ejecucion por prioridad completada\n";
}


#endif