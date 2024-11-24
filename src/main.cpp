#include "..\include\cola.h"
#include "..\include\procesos.h"
#include "..\include\archivo.h"
#include "..\include\planificador.h"
#include "..\include\simulador.h"

#include <iostream>

using namespace std;

int main() {
    Cola<ProcesoBase> cola;
    int quantum = 5;
    Planificador<ProcesoBase> planificador(quantum);

    string nombreArchivo;
    bool archivoAbierto = false;

    // Solicitar archivo hasta que se abra correctamente
    while (!archivoAbierto) {
        cout << "Ingrese el nombre del archivo a abrir (con extension): ";
        cin >> nombreArchivo;

        ifstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            archivoAbierto = true;
            archivo.close();
        } else {
            cerr << "Error al abrir el archivo: " << nombreArchivo << ". Intente de nuevo.\n";
        }
    }
    //leer proceso desde el archivo
    leerArchivoProcesos(nombreArchivo, cola);

    //imprime la cola
    cout << "Cola cargada desde archivo:\n" << cola.toString() << endl;
    
    //sacar y ejecutar procesos
    ProcesoBase* proceso = nullptr;
    while ((proceso = cola.pop()) != nullptr) {
        proceso->ejecutarInstruccion();  //ejecutar instruccion del proceso
        planificador.agregarProceso(proceso);
    }

    int opcion;
    cout << "\nSeleccione el algoritmo de planificacion:\n";
    cout << "1. Round Robin\n";
    cout << "2. Ejecucion por Prioridad\n";
    cout << "Ingrese su opcion (1 o 2): ";
    cin >> opcion;
    string resultado;
    
    if (opcion == 1) {
        resultado = planificador.ejecutarRoundRobin();
        
    } else if (opcion == 2) {
        resultado = planificador.ejecutarPorPrioridad();
    } 
    if(opcion == 1 || opcion == 2){
        string salidaEsperada;
        cout << "Ingrese el nombre del archivo con la salida esperada: ";
        cin >> salidaEsperada;
        Simulador simulador;
        simulador.compararArchivos(salidaEsperada, resultado);
        string resultadoComparacion;
        resultadoComparacion = simulador.compararArchivos(salidaEsperada, resultado);
        cout << resultadoComparacion;
    }else {
        cout<< "Opción inválida";
    }
    return 0;
}