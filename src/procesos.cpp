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
    cout << "Ejecutando instrucción normal en el proceso: " << nombre << endl;
}

//ProcesoEentrada/Salida
ProcesoES::ProcesoES(const string& nombre, int prioridad)
    : ProcesoBase(nombre, prioridad) {}

void ProcesoES::ejecutarInstruccion() {
    cout << "Inicio de operación de E/S en el proceso: " << nombre << endl;
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "Fin de operación de E/S en el proceso: " << nombre << endl;
}
