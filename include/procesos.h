#ifndef _PROCESOS_H_
#define _PROCESOS_H_

#include <string>
#include <iostream>

using namespace std;

class ProcesoBase {
protected:
    string nombre;  //nombre proceso
    int prioridad;  //prioridad proceso (0-10)
    string estado;  //estado: listo, en ejecucion, bloqueado, finalizado
    string subestado; //Subestados cuando está 'en ejecución': ctivo, cortado

public:
    ProcesoBase(const string& nombre, int prioridad);
    virtual ~ProcesoBase();

    //método virtual
    virtual void ejecutarInstruccion() = 0;

    //método normal
    void cambiarEstado(const string& nuevoEstado);
    void cambiarSubestado (const string& nuevoEstado);

    //getters
    string getNombre() const;
    int getPrioridad() const;
    string getEstado() const;
    string getSubestado() const;

    //obtener la informacion como string
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
