
#include "..\include\simulador.h"
#include <iostream>
#include <fstream>
#include <string>

Simulador::Simulador() {}

Simulador::~Simulador() {}


//funcion: leer procesos desde un archivo
void Simulador::leerArchivoProcesos(const string& nombreArchivo, Cola<ProcesoBase>& cola) {
    ifstream archivo(nombreArchivo);//abrir archivo
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    //leer línea por línea
    while (getline(archivo, linea)) {
        if (linea.find("proceso") == 0) {//detectar proceso
            size_t posNombre = linea.find(' ') + 1;//posicion del nombre
            size_t posPrioridad = linea.rfind(' ');//posicion de la prioridad
            string nombreProceso = linea.substr(posNombre, posPrioridad - posNombre);
            int prioridad = stoi(linea.substr(posPrioridad + 1));

            ProcesoBase* nuevoProceso = nullptr;

            //leer instrucciones del proceso
            while (getline(archivo, linea) && linea != "fin proceso") {
                if (linea.find("instruccion") == 0) {
                    if (!nuevoProceso) {//crear proceso normal
                        nuevoProceso = new ProcesoNormal(nombreProceso, prioridad);
                    }
                } else if (linea.find("e/s") == 0) {
                    if (!nuevoProceso) {//crear proceso de entrada/salida
                        nuevoProceso = new ProcesoES(nombreProceso, prioridad);
                    }
                }
            }

            //añadir proceso a la cola
            if (nuevoProceso) {
                cola.push(nuevoProceso);
            }
        }
    }

    archivo.close(); 
}
std::string Simulador::compararArchivos(const std::string& archivoEsperado, const std::string& archivoSalida) {
    std::ifstream archivo1(archivoEsperado);  // Archivo con salida esperada
    std::ifstream archivo2(archivoSalida);    // Archivo con salida del programa

    // Comprobar si ambos archivos se abren correctamente
    if (!archivo1.is_open() || !archivo2.is_open()) {
        return "Error al abrir uno de los archivos.";
    }

    std::string linea1, linea2;
    int lineaActual = 0;

    // Leer ambos archivos línea por línea y compararlas
    while (std::getline(archivo1, linea1) && std::getline(archivo2, linea2)) {
        ++lineaActual;
        if (linea1 != linea2) {
            return "Diferencia encontrada en línea " + std::to_string(lineaActual) + 
                   ":\nEsperada: " + linea1 + "\nObtenida: " + linea2;
        }
    }

    return "La salida es igual a la esperada.";
}

