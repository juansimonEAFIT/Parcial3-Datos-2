#ifndef NODO_BPLUS_H
#define NODO_BPLUS_H

#include "Tabla.h"
#include <vector>
#include <string>

class NodoBPlus {
public:
    bool esHoja;                              // Indica si el nodo es una hoja
    std::vector<std::string> claves;          // Claves para organizar las tablas
    std::vector<Tabla*> tablas;               // Punteros a las tablas en el nodo hoja (si es hoja)
    std::vector<NodoBPlus*> hijos;            // Punteros a hijos (para nodos internos)
    NodoBPlus* siguiente;                     // Puntero al siguiente nodo hoja

    NodoBPlus(bool esHoja);
};

#endif
