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

void ProcesoBase::cambiarSubestado (const string& nuevoSubestado){
    subestado = nuevoSubestado;
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

string ProcesoBase::getSubestado() const {
    return subestado;
}


string ProcesoBase::toString() const {
    return "Nombre: " + nombre + ", Prioridad: " + to_string(prioridad) + ", Estado: " 
    + estado + (subestado.empty() ? "" : ", Subestado: " + subestado);
}

//ProcesoNormal
ProcesoNormal::ProcesoNormal(const string& nombre, int prioridad)
    : ProcesoBase(nombre, prioridad) {}

void ProcesoNormal::ejecutarInstruccion() {
    static int instruccionesEjecutadas = 0;
    cambiarEstado("En ejecucion");
    cambiarSubestado("Activo");

    cout << "Ejecutando instruccion normal del proceso: " << nombre << "\n";
    instruccionesEjecutadas++;

    if (instruccionesEjecutadas >= 3) {
        cambiarEstado("finalizado");
        cambiarSubestado("");
    } else {
       
        cambiarSubestado("Cortado");
        cambiarEstado("Listo"); 
    }
}


//ProcesoEentrada/Salida
ProcesoES::ProcesoES(const string& nombre, int prioridad)
    : ProcesoBase(nombre, prioridad) {}

void ProcesoES::ejecutarInstruccion() {
    cambiarEstado("En ejecucion");
    cambiarSubestado("Activo");

    cout << "Inicio de operacion de E/S en el proceso: " << nombre << "\n";
    this_thread::sleep_for(chrono::milliseconds(1500));//simula operacion de E/S
    cambiarEstado("finalizado");
    cambiarSubestado("");
    cout << "Fin de operacion de E/S en el proceso: " << nombre << "\n";
}

