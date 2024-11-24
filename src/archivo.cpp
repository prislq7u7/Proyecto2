#include "..\include\archivo.h"

#include <iostream>
#include <fstream>
#include <string>


//funcion: leer procesos desde un archivo
void leerArchivoProcesos(const string& nombreArchivo, Cola<ProcesoBase>& cola) {
    ifstream archivo(nombreArchivo);//abrir archivo
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
