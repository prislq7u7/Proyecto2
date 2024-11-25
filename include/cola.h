#ifndef _COLA_H_
#define _COLA_H_

#include <iostream>
#include <sstream>

using namespace std;

//clase Nodo
template <typename T>
class Nodo {
public:
    T* dato;       //puntero al dato genérico
    Nodo<T>* sig;  //untero al nodo siguiente

    Nodo(T* dato) : dato(dato), sig(nullptr) {}
    ~Nodo() { delete dato; }  //liberar memoria del dato
};

//clase Cola
template <typename T>
class Cola {
public:
    Nodo<T>* cabeza;  //puntero al primer nodo de la cola

    Cola();           //constructor
    ~Cola();          //destructor

    void push(T* dato);       //agregar nuevo elemento
    T* pop();                 //extraer el elemento al frente
    string toString() const;  //convertir la cola a string para depuración
};

//métodos:

//constructor
template <typename T>
Cola<T>::Cola() : cabeza(nullptr) {}

//destructor
template <typename T>
Cola<T>::~Cola() {
    while (cabeza != nullptr) {
        pop();//vaciar la cola liberando memoria
    }
}

//agregar un nuevo elemento a la cola
template <typename T>
void Cola<T>::push(T* dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);//crear un nuevo nodo
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;//si la cola está vacía, el nuevo nodo es la cabeza
    } else {
        Nodo<T>* it = cabeza;
        while (it->sig != nullptr) {
            it = it->sig;//avanzar al último nodo
        }
        it->sig = nuevoNodo;//agregar el nuevo nodo al final
    }
}

//sacar el elemento al frente de la cola
template <typename T>
T* Cola<T>::pop() {
    if (cabeza == nullptr) {
        return nullptr;//si la cola está vacía, no hay nada que sacar
    }

    Nodo<T>* nodoSacar = cabeza;  //apuntar al nodo que se va a sacar
    cabeza = cabeza->sig;         //avanzar la cabeza al siguiente nodo
    T* dato = nodoSacar->dato;    //extraer el dato del nodo
    nodoSacar->dato = nullptr;    //prevenir que el destructor del nodo borre el dato
    delete nodoSacar;             //liberar el nodo
    return dato;                  //retornar el dato extraído
}

//turn la cola a string 
template <typename T>
string Cola<T>::toString() const {
    stringstream ss;
    Nodo<T>* it = cabeza;

    while (it != nullptr) {
        ss << "Elemento: " << it->dato->toString() << "\n"; 
        it = it->sig;
    }

    return ss.str();
}

#endif


