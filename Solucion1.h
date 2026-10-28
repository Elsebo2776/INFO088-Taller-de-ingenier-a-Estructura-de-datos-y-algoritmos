#ifndef SOLUCION1_H
#define SOLUCION1_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

typedef unsigned char uchar;

#define colchon 0.25

// funcion menor_palabra: esta funcion es comparar la palabra con la palabra siguiente y te indica  cual de las 2 van primero en orden ASCII.
// no mueve, solo va, mira e indica si la palabra esta bien en ese lugar o no.
inline bool menor_palabra(const uchar* a, const uchar* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
        i++;
    }
    return (a[i] == '\0' && b[i] != '\0');
}

// funcion igual_palabra: esta  funcion es para determinar si las palabras "a" y "b" son una palabra iguales.
// igualmente como la funcion anterior solo mira, no mueve.
inline bool igual_palabras(const uchar* a, const uchar* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }
    return (a[i] == '\0' && b[i] == '\0');
}

// funcion copiar_palabra: esta funcion observa si es igual la palabra que escogiste con alguna de la lista completa y la copia en una 
// dirección de memoria dinamica.
inline uchar* copiar_palabra(const uchar* origen) {
    int largo = 0;
    while (origen[largo] != '\0') {
        largo++;
    }
    uchar* nueva = new uchar[largo + 1];
    for (int i = 0; i <= largo; i++) {
        nueva[i] = origen[i];
    }
    return nueva;
}

// funcion crear_palabra: Convierte un string leído del archivo a un arreglo dinámico en un uchar
// con esto tenemos un "puente" entre la info que tiene la lista y como nosotros buscamos la info.
inline uchar* crear_Palabra(const string& str) {
    int largo = str.length();
    uchar* nueva = new uchar[largo + 1];
    for (int i = 0; i < largo; i++) {
        nueva[i] = (uchar)str[i];
    }
    nueva[largo] = '\0';
    return nueva;
}

// Solución 1: Arreglo Dinámico Ordenado
class Arreglo_dinamico_ordenado {
private:
    vector<uchar*> S; // contenedor vector
    int item;         // cantidad actual de elementos en el arreglo
    int cap;          // capacidad máxima actual del vector
    double colchon_val;  // espacio adicional para que no exista un error por si faltan celdas

    // funcion reSize: ajusta la capacidad del arreglo dinamico copiando elementos cuando el espacio se agota
    void reSize(int newCap) {
        vector<uchar*> nuevoS(newCap);
        for (int i = 0; i < item; i++) {
            nuevoS[i] = S[i];
        }
        S = nuevoS;
        cap = newCap;
    }

    // Búsqueda Binaria 
    int binarySearch(const uchar* x) {
        if (item == 0) return -1;
        int l, m, r;
        l = 0;
        r = item - 1;
        m = r / 2;
        while (l <= r) {
            if (igual_palabras(x, S[m])) {
                return m;
            } else {
                if (menor_palabra(x, S[m])) {
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            m = (l + r) / 2;
        }
        return -1;
    }

public:
    Arreglo_dinamico_ordenado(int largoInicial = 16, double ovh = colchon) {
        item = 0;
        cap = largoInicial;
        colchon_val = ovh;
        S = vector<uchar*>(cap);
    }

    ~Arreglo_dinamico_ordenado() {
        for (int i = 0; i < item; i++) {
            delete[] S[i];
        }
    }

    bool search(const uchar* x) {
        int pos = binarySearch(x);
        return (pos != -1);
    }

    // Inserción manteniendo el orden mediante corrimientos 
    bool insert(const uchar* x) {
        // antifuplicado :)
        if (binarySearch(x) != -1) {
            return false;
        }

        // Si alcanzamos la capacidad máxima, aplicamos el reSize con el colchon
        if (item == cap) {
            int extra = (int)(cap * colchon_val);
            if (extra == 0) extra = 1;
            reSize(cap + extra);
        }

        // Corrimiento de elementos mayores de derecha a izquierda (como debe ser)
        int j = item - 1;
        while (j >= 0 && menor_palabra(x, S[j])) {
            S[j + 1] = S[j];
            j = j - 1;
        }

        S[j + 1] = copiar_palabra(x);
        item++;
        return true;
    }

    // localiza la palabra que se debe eliminar y verifica si existe o se la imagino el codigo jajaja.
    bool remove(const uchar* x) {
        int pos = binarySearch(x);
        if (pos == -1) {
            return false;
        }

        delete[] S[pos]; // liberador de memoria dinamica

        for (int i = pos; i < item - 1; i++) {
            S[i] = S[i + 1];
        }
        item--;
        return true;
    }

    int size() { return item; }
    int capacity() { return cap; }
};

#endif
