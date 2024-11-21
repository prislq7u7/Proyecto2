#include "..\include\procesos.h"

#include <thread>
#include <chrono>



//ProcesoBase
ProcesoBase::ProcesoBase(const string& nombre, int prioridad)
    : nombre(nombre), prioridad(prioridad), estado("Listo") {}

ProcesoBase::~ProcesoBase() {}

void ProcesoBase::cambiarEstado(const string& nuevoEstado) {
    estado = nuevoEstado;
}

string ProcesoBase::getNombre() const {
    return nombre;
}

int ProcesoBase::getPrioridad() const {
    return prioridad;
}

string ProcesoBase::getEstado() const {
    return estado;
}

string ProcesoBase::toString() const {
    return "Nombre: " + nombre + ", Prioridad: " + to_string(prioridad) + ", Estado: " + estado;
}

//ProcesoNormal
ProcesoNormal::ProcesoNormal(const string& nombre, int prioridad)
    : ProcesoBase(nombre, prioridad) {}

void ProcesoNormal::ejecutarInstruccion() {
    static int instruccionesEjecutadas = 0;
    cout << "Ejecutando instrucción normal del proceso: " << nombre << "\n";
    instruccionesEjecutadas++;
    if (instruccionesEjecutadas >= 3) { // Ejemplo: termina tras 3 instrucciones
        cambiarEstado("finalizado");
    }
}


//ProcesoEentrada/Salida
ProcesoES::ProcesoES(const string& nombre, int prioridad)
    : ProcesoBase(nombre, prioridad) {}

void ProcesoES::ejecutarInstruccion() {
    cout << "Inicio de operación de E/S en el proceso: " << nombre << "\n";
    this_thread::sleep_for(chrono::milliseconds(1500)); // Simula operación de E/S
    cambiarEstado("finalizado");
    cout << "Fin de operación de E/S en el proceso: " << nombre << "\n";
}

