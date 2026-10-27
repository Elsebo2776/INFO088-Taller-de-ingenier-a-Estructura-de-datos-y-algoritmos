#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

typedef unsigned char uchar;

#define colchon 0.25

// funcion menor_palabra: esta funcion es comparar la palabra con la palabra siguiente y te indica  cual de las 2 van primero en orden ASCII.
// no mueve, solo va, mira e indica si la palabra esta bien en ese lugar o no.
bool menor_palabra(const uchar* a, const uchar* b) {
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
// igualmente como la funcion anterior solo mira, no mueve ni nada.
bool igual_palabras(const uchar* a, const uchar* b) {
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
//direción de memoria dinamica.
uchar* copiar_palabra(const uchar* origen) {
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
//con esto tenemos un "puente" entre la info que tiene la lista y como nosotros buscamos la info.
uchar* crear_Palabra(const string& str) {
    int largo = str.length();
    uchar* nueva = new uchar[largo + 1];
    for (int i = 0; i < largo; i++) {
        nueva[i] = (uchar)str[i];
    }
    nueva[largo] = '\0';
    return nueva;
}


class _ {
private:
    vector<uchar*> S; // contenedor vector (nombrado S como en 08 Pilas Colas.pdf pág. 32)
    int item;         // cantidad actual de elementos en el arreglo
    int cap;          // capacidad máxima actual del vector
    double colchon;  // espacio adicional para que no exista un error por si faltan celdas

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
                ool menor_palabra(x, S[m])) {
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            m = (l + r) / 2;
        }
        return -1;
    }


    Arreglo_dinamico_ordenado(int largoInicial = 16, double ovh = colchon
) {
        item = 0;
        cap = largoInicial;
        colchon = ovh;
        S = vector<uchar*>(cap);
    }

    destructor__() {
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
            int extra = (int)(cap * colchon);
            if (extra == 0) extra = 1;
            reSize(cap + extra);
        }

        // Corrimiento de elementos mayores de derecha a izquierda (como debe ser)
        int j = item - 1;
        while (j >= 0ool menor_palabra(x, S[j])) {
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

    destructor_ListaCircularSTL() {
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
        if (direccion == 'D'ool menor_palabra(x, **P)) {
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
                ool menor_palabra(x, **P)) {
                    return false; // Como está ordenada, si nos pasamos ya no existe
                }
            }
        } else {
            while (true) {
                if (*P == l.begin()ool menor_palabra(x, **P)) {
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
                if (*P != ultimoool menor_palabra(**P, x)) {
                    return false;
                }
            }
        }
    }

    // Inserción ordenada en la lista
    bool insert(const uchar* x, IteradorNodo& P) {
        IteradorNodo it = l.begin();
        while (it != l.end()ool menor_palabra(*it, x)) {
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
        while (it != l.end()ool menor_palabra(*it, x)) {
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

// esta funcion se encarga de leer el archivo de las listas y cargar toooda esa info en un vector que tiene de info "uchar*"

vector<uchar*> leer_Archivo_Diccionario(const string& ruta) {
    vector<uchar*> palabras;
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << ruta << endl;
        return palabras;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty() && linea[linea.length() - 1] == '\r') {
            linea.erase(linea.length() - 1);
        }
        if (!linea.empty()) {
            palabras.push_back(crearPalabraDesdeString(linea));
        }
    }
    archivo.close();
    return palabras;
}

int main(int argc, char **argv) {
    string rutaD1 = "dicionarios/D1.txt";
    string rutaD2 = "dicionarios/D2.txt";
    int REP = 1000;

    if (argc >= 3) {
        rutaD1 = argv[1];
        rutaD2 = argv[2];
    }
    if (argc >= 4) {
        REP = atoi(argv[3]);
    }

    cout << "=== CARGANDO ARCHIVOS EN MEMORIA ===" << endl;
    vector<uchar*> datosD1 =_(rutaD1);
    vector<uchar*> datosD2 =_(rutaD2);

    int nD1 = datosD1.size();
    int nD2 = datosD2.size();

    if (nD1 == 0 || nD2 == 0) {
        cout << "Verifique que los archivos D1.txt y D2.txt existan." << endl;
        return EXIT_SUCCESS;
    }

    cout << "Palabras leidas D1: " << nD1 << " | D2: " << nD2 << endl << endl;

    _ sol1(16, colchon
);
    ListaCircularSTL sol2;
    IteradorNodo P = sol2.getInicio();

    // 1. EXPERIMENTO DE CONSTRUCCIÓN 
    cout << "=== 1. CONSTRUCCION (D1.txt) ===" << endl;
    auto iniS1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < nD1; i++) {
        sol1.insert(datosD1[i]);
    }
    auto finS1 = chrono::high_resolution_clock::now();
    double msConstS1 = chrono::duration<double, milli>(finS1 - iniS1).count();

    auto iniS2 = chrono::high_resolution_clock::now();
    for (int i = 0; i < nD1; i++) {
        sol2.insert(datosD1[i], P);
    }
    auto finS2 = chrono::high_resolution_clock::now();
    double msConstS2 = chrono::duration<double, milli>(finS2 - iniS2).count();

    cout << "[Solucion 1 - Vector] Tiempo: " << msConstS1 << " ms | Elementos: " << sol1.size() << endl;
    cout << "[Solucion 2 - Lista ] Tiempo: " << msConstS2 << " ms | Elementos: " << sol2.size() << endl << endl;

    // 2. EXPERIMENTO DE BÚSQUEDA (usando rand() % nD1 como en 02 Funciones Arreglos.pdf)
    cout << "=== 2. BUSQUEDA (REP = " << REP << ") ===" << endl;
    int valoresK[4] = {8, 32, 128, 512};

    for (int idx = 0; idx < 4; idx++) {
        int k = valoresK[idx];
        vector<uchar*> clavesBuscar(REP);

        for (int i = 0; i < REP; i++) {
            int posAleatoria = rand() % nD1;
            clavesBuscar[i] = datosD1[posAleatoria];
        }

        int exitoS1 = 0;
        auto t0_s1 = chrono::high_resolution_clock::now();
        for (int i = 0; i < REP; i++) {
            if (sol1.search(clavesBuscar[i])) exitoS1++;
        }
        auto t1_s1 = chrono::high_resolution_clock::now();
        double msBusqS1 = chrono::duration<double, milli>(t1_s1 - t0_s1).count();

        int exitoS2 = 0;
        P = sol2.getInicio();
        auto t0_s2 = chrono::high_resolution_clock::now();
        for (int i = 0; i < REP; i++) {
            char dir = ((i / k) % 2 == 0) ? 'D' : 'I';
            if (sol2.search(&P, clavesBuscar[i], dir)) exitoS2++;
        }
        auto t1_s2 = chrono::high_resolution_clock::now();
        double msBusqS2 = chrono::duration<double, milli>(t1_s2 - t0_s2).count();

        cout << "k = " << k << " -> [Vector]: " << msBusqS1 << " ms | [Lista]: " << msBusqS2 << " ms" << endl;
    }
    cout << endl;

    // 3. EXPERIMENTO DE INSERCIÓN Y ELIMINACIÓN INTERCALADA 
    cout << "=== 3. INSERCION Y ELIMINACION INTERCALADA (D2.txt) ===" << endl;
    double msInsS1 = 0.0, msElimS1 = 0.0;
    for (int i = 0; i < nD2; i++) {
        if (i % 2 == 0) {
            auto t0 = chrono::high_resolution_clock::now();
            sol1.insert(datosD2[i]);
            auto t1 = chrono::high_resolution_clock::now();
            msInsS1 += chrono::duration<double, milli>(t1 - t0).count();
        } else {
            auto t0 = chrono::high_resolution_clock::now();
            sol1.remove(datosD2[i]);
            auto t1 = chrono::high_resolution_clock::now();
            msElimS1 += chrono::duration<double, milli>(t1 - t0).count();
        }
    }

    double msInsS2 = 0.0, msElimS2 = 0.0;
    for (int i = 0; i < nD2; i++) {
        if (i % 2 == 0) {
            auto t0 = chrono::high_resolution_clock::now();
            sol2.insert(datosD2[i], P);
            auto t1 = chrono::high_resolution_clock::now();
            msInsS2 += chrono::duration<double, milli>(t1 - t0).count();
        } else {
            auto t0 = chrono::high_resolution_clock::now();
            sol2.remove(datosD2[i], P);
            auto t1 = chrono::high_resolution_clock::now();
            msElimS2 += chrono::duration<double, milli>(t1 - t0).count();
        }
    }

    cout << "[Solucion 1 - Vector] Insercion: " << msInsS1 << " ms | Eliminacion: " << msElimS1 << " ms" << endl;
    cout << "[Solucion 2 - Lista ] Insercion: " << msInsS2 << " ms | Eliminacion: " << msElimS2 << " ms" << endl;

    // Liberar memoria dinámica solicitada con new
    for (int i = 0; i < nD1; i++) delete[] datosD1[i];
    for (int i = 0; i < nD2; i++) delete[] datosD2[i];

    return EXIT_SUCCESS;
} 