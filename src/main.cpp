#include "..\include\cola.h"
#include "..\include\procesos.h"
#include "..\include\archivo.h"

#include <iostream>

using namespace std;

int main() {
    Cola<ProcesoBase> cola;

    string nombreArchivo;
    cout << "Ingrese el nombre del archivo a abrir (con extensión): ";
    cin >> nombreArchivo;

    //leer proceso desde el archivo
    leerArchivoProcesos(nombreArchivo, cola);

    //imprime la cola
    cout << "Cola cargada desde archivo:\n" << cola.toString() << endl;

    //sacar y ejecutar procesos
    ProcesoBase* proceso = nullptr;
    while ((proceso = cola.pop()) != nullptr) {
        proceso->ejecutarInstruccion();  //ejecutar instrucción del proceso
        delete proceso;                  //liberar memoria 
    }

    return 0;
}
