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
    cout << "Ingrese el nombre del archivo a abrir (con extensión): ";
    cin >> nombreArchivo;
    //Simulador simulador;
   // simulador.leerArchivoProcesos(nombreArchivo, cola);
    //leer proceso desde el archivo
    leerArchivoProcesos(nombreArchivo, cola);

    //imprime la cola
    cout << "Cola cargada desde archivo:\n" << cola.toString() << endl;
    
    //sacar y ejecutar procesos
    ProcesoBase* proceso = nullptr;
    while ((proceso = cola.pop()) != nullptr) {
        proceso->ejecutarInstruccion();  //ejecutar instrucción del proceso
        planificador.agregarProceso(proceso);
    }

    int opcion;
    cout << "\nSeleccione el algoritmo de planificación:\n";
    cout << "1. Round Robin\n";
    cout << "2. Ejecución por Prioridad\n";
    cout << "Ingrese su opción (1 o 2): ";
    cin >> opcion;
    string resultado;
    if (opcion == 1) {
        resultado = planificador.ejecutarRoundRobin();
        
    } else if (opcion == 2) {
        planificador.ejecutarPorPrioridad();
    } else {
        cout << "Finalizando el programa";
    }
    string salidaEsperada;
    cout << "Ingrese el nombre del archivo con la salida esperada: ";
    cin >> salidaEsperada;
    Simulador simulador;
    simulador.compararArchivos(salidaEsperada, resultado);
    string resultadoComparacion;
    resultadoComparacion = simulador.compararArchivos(salidaEsperada, resultado);
    cout << resultadoComparacion;
    return 0;
}