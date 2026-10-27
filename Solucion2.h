#ifndef SOLUCION2_H
#define SOLUCION2_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <string>
#include "Solucion1.h"

using namespace std;

// ENTENDER MAÑANA**********************************************************************
typedef list<uchar*>::iterator IteradorNodo;

class ListaCircularSTL {
private:
    list<uchar*> l; // Contenedor std::list (nombrado l como en 07 Listas Enlazadas.pdf pág. 30)

    // Mueve el iterador al nodo siguiente de forma circular
    void avanzarDerecha(IteradorNodo& it) {
        ++it;
        if (it == l.end()) {
            it = l.begin();
        }
    }

    // Mueve el iterador al nodo anterior de forma circular (sin usar std::prev)
    void avanzarIzquierda(IteradorNodo& it) {
        if (it == l.begin()) {
            it = l.end();
            --it; // Queda apuntando al último elemento de la lista
        } else {
            --it;
        }
    }

public:
    ListaCircularSTL() {}

    ~ListaCircularSTL() {
        IteradorNodo it = l.begin();
        while (it != l.end()) {
            delete[] *it;
            ++it;
        }
    }

    IteradorNodo getInicio() {
        return l.begin();
    }

    // Búsqueda recibiendo el puntero P por dirección (02 Funciones Arreglos.pdf pág. 3)
    bool search(IteradorNodo* P, const uchar* x, char direccion) {
        if (l.empty()) return false;

        if (*P == l.end()) {
            *P = l.begin();
        }

        if (igual_palabras(**P, x)) {
            return true;
        }

        // Regla de la pauta: si busca hacia adelante y x es menor que **P, reinicia al comienzo
        if (direccion == 'D' && menor_palabra(x, **P)) {
            *P = l.begin();
            if (igual_palabras(**P, x)) return true;
        }

        IteradorNodo puntoPartida = *P;

        if (direccion == 'D') {
            while (true) {
                IteradorNodo sig = *P;
                avanzarDerecha(sig);

                if (sig == l.begin() || sig == puntoPartida) {
                    return false;
                }

                *P = sig;

                if (igual_palabras(**P, x)) {
                    return true;
                }
                if (menor_palabra(x, **P)) {
                    return false; // Como está ordenada, si nos pasamos ya no existe
                }
            }
        } else {
            while (true) {
                if (*P == l.begin() || menor_palabra(x, **P)) {
                    return false;
                }

                IteradorNodo ant = *P;
                avanzarIzquierda(ant);

                if (ant == puntoPartida) {
                    return false;
                }

                *P = ant;

                if (igual_palabras(**P, x)) {
                    return true;
                }

                IteradorNodo ultimo = l.end();
                --ultimo;
                if (*P != ultimo && menor_palabra(**P, x)) {
                    return false;
                }
            }
        }
    }

    // Inserción ordenada en la lista
    bool insert(const uchar* x, IteradorNodo& P) {
        IteradorNodo it = l.begin();
        while (it != l.end() && menor_palabra(*it, x)) {
            ++it;
        }

        if (it != l.end() && igual_palabras(*it, x)) {
            return false; // No insertar duplicados
        }

        uchar* copia = copiar_palabra(x);
        bool estabaVacia = l.empty();

        l.insert(it, copia);

        if (estabaVacia) {
            P = l.begin();
        }
        return true;
    }

    // Eliminación cuidando que P no apunte a un nodo borrado
    bool remove(const uchar* x, IteradorNodo& P) {
        IteradorNodo it = l.begin();
        while (it != l.end() && menor_palabra(*it, x)) {
            ++it;
        }

        if (it != l.end() && igual_palabras(*it, x)) {
            if (it == P) {
                ++P;
                if (P == l.end()) {
                    P = l.begin();
                }
            }
            delete[] *it;
            l.erase(it);
            if (l.empty()) {
                P = l.end();
            }
            return true;
        }
        return false;
    }

    int size() { return l.size(); }
};

#endif