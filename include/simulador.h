#ifndef _SIMULADOR_H
#define _SIMULADOR_H

#include "cola.h"
#include "procesos.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


class Simulador {
private:


public:
    // Constructor vacío
    Simulador();
    ~Simulador(); 

//funcion: leer procesos desde un archivo
void leerArchivoProcesos(const string& nombreArchivo, Cola<ProcesoBase>& cola);
string compararArchivos(const std::string& archivoEsperado, const std::string& archivoSalida);
};
#endif