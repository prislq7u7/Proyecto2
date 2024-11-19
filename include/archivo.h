#ifndef _ARCHIVO_H_
#define _ARCHIVO_H_

#include "cola.h"
#include "procesos.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


void leerArchivoProcesos(const string& nombreArchivo, Cola<ProcesoBase>& cola);


#endif
