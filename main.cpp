#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include "Solucion1.h"
#include "Solucion2.h"

using namespace std;

// Función para leer los archivos D1.txt y D2.txt
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
            palabras.push_back(crear_Palabra(linea));
        }
    }
    archivo.close();
    return palabras;
}

int main(int argc, char **argv) {
    string rutaD1 = "D1.txt";
    string rutaD2 = "D2.txt";
    int REP = 1000;

    if (argc >= 3) {
        rutaD1 = argv[1];
        rutaD2 = argv[2];
    }
    if (argc >= 4) {
        REP = atoi(argv[3]);
    }

    cout << "=== CARGANDO ARCHIVOS EN MEMORIA ===" << endl;
    vector<uchar*> datosD1 = leer_Archivo_Diccionario(rutaD1);
    vector<uchar*> datosD2 = leer_Archivo_Diccionario(rutaD2);

    int nD1 = datosD1.size();
    int nD2 = datosD2.size();

    if (nD1 == 0 || nD2 == 0) {
        cout << "Verifique que los archivos D1.txt y D2.txt existan." << endl;
        return EXIT_SUCCESS;
    }

    cout << "Palabras leidas D1: " << nD1 << " | D2: " << nD2 << endl << endl;

    ArregloDinamico sol1(16, colchon);
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

    // 2. EXPERIMENTO DE BÚSQUEDA
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

    // Liberar memoria dinámica
    for (int i = 0; i < nD1; i++) delete[] datosD1[i];
    for (int i = 0; i < nD2; i++) delete[] datosD2[i];

    return EXIT_SUCCESS;
}