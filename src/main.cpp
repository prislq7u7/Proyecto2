#include <iostream>
#include "..\include\cola.h"
#include "..\include\procesos.h"

using namespace std;

int main() {
    Cola<ProcesoBase> cola;

    cola.push(new ProcesoNormal("Proceso1", 5));
    cola.push(new ProcesoES("Proceso2", 3));

    //mostrar la cola
    cout << "Cola actual:\n" << cola.toString() << endl;

    //sacar y ejecutar procesos
    ProcesoBase* proceso = nullptr;
    while ((proceso = cola.pop()) != nullptr) {
        proceso->ejecutarInstruccion();  //ejecutar instrucción del proceso
        delete proceso;                  //liberar memoria 
    }

    return 0;
}
