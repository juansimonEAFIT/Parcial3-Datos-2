#ifndef ARBOL_BPLUS_H
#define ARBOL_BPLUS_H

#include "Tabla.h"
#include "NodoBPlus.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <map>
#include <iostream>

class ArbolBPlus {
private:
    NodoBPlus* raiz;
    int orden;
    std::unordered_map<std::string, Tabla> tablas; // Miembro de clase

    // Funciones auxiliares
    void dividirNodo(NodoBPlus* nodo, int indice, NodoBPlus* hijo);
    void insertarNoLleno(NodoBPlus* nodo, const std::string& clave, Tabla* tabla);
    void mostrarArbolAux(NodoBPlus* nodo, std::string prefix, bool esUltimo);

public:
    ArbolBPlus(int orden);

    void createTable(const std::string& nombre, const std::vector<std::string>& columnas);
    
    void insertar(const std::string& tabla, const std::vector<std::string>& columnas, const std::vector<std::string>& valores);
    void seleccionar(const std::string& tabla, const std::vector<std::string>& columnas, const std::string& condicion);
    void actualizar(const std::string& tabla, const std::map<std::string, std::string>& asignaciones, const std::string& condicion);
    void eliminar(const std::string& tabla, const std::string& condicion);
    void mostrarArbol();
};


#endif
