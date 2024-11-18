#ifndef _PROCESOS_H_
#define _PROCESOS_H_

#include <string>
#include <iostream>

using namespace std;

class ProcesoBase {
protected:
    string nombre;  //nombre proceso
    int prioridad;  //prioridad proceso (0-10)
    string estado;  //estado: listo, en ejecución, bloqueado, finalizado

public:
    ProcesoBase(const string& nombre, int prioridad);
    virtual ~ProcesoBase();

    //método virtual
    virtual void ejecutarInstruccion() = 0;

    //método normal
    void cambiarEstado(const string& nuevoEstado);

    //getters
    string getNombre() const;
    int getPrioridad() const;
    string getEstado() const;

    //obtener la información como string
    string toString() const;
};

class ProcesoNormal : public ProcesoBase {
public:
    ProcesoNormal(const string& nombre, int prioridad);
    void ejecutarInstruccion() override;
};

class ProcesoES : public ProcesoBase {
public:
    ProcesoES(const string& nombre, int prioridad);
    void ejecutarInstruccion() override;
};

#endif
