#ifndef ARBOLBPLUS_H
#define ARBOLBPLUS_H

#include <vector>
#include <string>
#include <map>
#include "NodoBPlus.h"

class ArbolBPlus {
public:
    ArbolBPlus(int grado = 3); // Constructor con un valor predeterminado para el grado
    void insertar(const std::string& tabla, const std::vector<std::string>& columnas, const std::vector<std::string>& valores);
    void seleccionar(const std::string& tabla, const std::vector<std::string>& columnas);
    void actualizar(const std::string& tabla, const std::map<std::string, std::string>& asignaciones, const std::string& condicion);
    void eliminar(const std::string& tabla, const std::string& condicion);

private:
    int grado;
    NodoBPlus* raiz;
    void dividirNodo(NodoBPlus* nodo, int indice, NodoBPlus* hijo);
    void insertarNoLleno(NodoBPlus* nodo, const std::string& clave);
    NodoBPlus* buscarNodo(NodoBPlus* nodo, const std::string& clave);
    void eliminarClave(NodoBPlus* nodo, const std::string& clave);
};

#endif // ARBOLBPLUS_H
