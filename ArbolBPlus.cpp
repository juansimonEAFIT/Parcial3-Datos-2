#include "ArbolBPlus.h"
#include <iostream>

ArbolBPlus::ArbolBPlus(int grado) : raiz(nullptr), orden(grado) {}

std::unordered_map<std::string, Tabla> tablas;

void ArbolBPlus::createTable(const std::string& nombre, const std::vector<std::string>& columnas) {
    if (tablas.find(nombre) != tablas.end()) {
        std::cerr << "Error: La tabla '" << nombre << "' ya existe." << std::endl;
        return;
    }

    // Crear la nueva tabla
    Tabla* nuevaTabla = new Tabla(nombre, columnas);

    // Inserta la tabla en el árbol B+ y organiza en orden alfabético
    if (raiz == nullptr) {
        raiz = new NodoBPlus(true);
        raiz->claves.push_back(nombre);
        raiz->tablas.push_back(nuevaTabla);
    } else {
        if (raiz->claves.size() == static_cast<size_t>(2 * orden - 1)) {
            NodoBPlus* nuevaRaiz = new NodoBPlus(false);
            nuevaRaiz->hijos.push_back(raiz);
            dividirNodo(nuevaRaiz, 0, raiz);
            insertarNoLleno(nuevaRaiz, nombre, nuevaTabla);
            raiz = nuevaRaiz;
        } else {
            insertarNoLleno(raiz, nombre, nuevaTabla);
        }
    }
    tablas[nombre] = *nuevaTabla;

    // Confirmación de creación de tabla
    std::cout << "Ejecutando: CREATE TABLE " << nombre << " (";
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i] << (i < columnas.size() - 1 ? ", " : "");
    }
    std::cout << ")\n";
}

// Implementación básica de dividirNodo
void ArbolBPlus::dividirNodo(NodoBPlus* nodo, int indice, NodoBPlus* hijo) {
    // Crea un nuevo nodo que contendrá las claves superiores de "hijo"
    NodoBPlus* nuevoNodo = new NodoBPlus(hijo->esHoja);
    nuevoNodo->claves.resize(orden - 1);

    // Mueve las claves superiores de "hijo" a "nuevoNodo"
    for (int j = 0; j < orden - 1; ++j) {
        nuevoNodo->claves[j] = hijo->claves[j + orden];
    }

    // Si "hijo" es una hoja, mueve también los punteros a tablas
    if (hijo->esHoja) {
        nuevoNodo->tablas.assign(hijo->tablas.begin() + orden, hijo->tablas.end());
        hijo->tablas.resize(orden - 1);
    } else {
        // Si no es hoja, mueve los hijos correspondientes al nuevo nodo
        nuevoNodo->hijos.resize(orden);
        for (int j = 0; j < orden; ++j) {
            nuevoNodo->hijos[j] = hijo->hijos[j + orden];
        }
    }

    // Reduce el tamaño de "hijo" (nodo original)
    hijo->claves.resize(orden - 1);

    // Inserta un nuevo hijo en el nodo padre
    nodo->hijos.insert(nodo->hijos.begin() + indice + 1, nuevoNodo);

    // Mueve la clave del medio de "hijo" al nodo actual (padre)
    nodo->claves.insert(nodo->claves.begin() + indice, hijo->claves[orden - 1]);
}


// Implementación básica de insertarNoLleno
void ArbolBPlus::insertarNoLleno(NodoBPlus* nodo, const std::string& clave, Tabla* tabla) {
    if (nodo->esHoja) {
        // Inserta en el lugar ordenado en el nodo hoja
        auto it = std::lower_bound(nodo->claves.begin(), nodo->claves.end(), clave);
        size_t pos = it - nodo->claves.begin();
        nodo->claves.insert(it, clave);
        nodo->tablas.insert(nodo->tablas.begin() + pos, tabla);
    } else {
        // Encuentra el hijo apropiado para la clave
        int i = nodo->claves.size() - 1;
        while (i >= 0 && clave < nodo->claves[i]) {
            i--;
        }
        i++;

        // Si el nodo hijo está lleno, divídelo
        if (nodo->hijos[i]->claves.size() == static_cast<size_t>(2 * orden - 1)) {
            dividirNodo(nodo, i, nodo->hijos[i]);
            if (clave > nodo->claves[i]) {
                i++;
            }
        }
        insertarNoLleno(nodo->hijos[i], clave, tabla);
    }
}



// Implementación básica de seleccionar
void ArbolBPlus::seleccionar(const std::string& tabla, const std::vector<std::string>& columnas) {
    std::cout << "Ejecutando: SELECT ";
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i] << (i < columnas.size() - 1 ? ", " : "");
    }
    std::cout << " FROM " << tabla << std::endl;
}

// Implementación básica de actualizar
void ArbolBPlus::actualizar(const std::string& tabla, const std::map<std::string, std::string>& asignaciones, const std::string& condicion) {
    std::cout << "Ejecutando: UPDATE " << tabla << " SET ";
    size_t i = 0;
    for (const auto& asignacion : asignaciones) {
        std::cout << asignacion.first << " = " << asignacion.second;
        if (i < asignaciones.size() - 1) std::cout << ", ";
        ++i;
    }
    std::cout << " WHERE " << condicion << std::endl;
}

// Implementación básica de eliminar
void ArbolBPlus::eliminar(const std::string& tabla, const std::string& condicion) {
    std::cout << "Ejecutando: DELETE FROM " << tabla << " WHERE " << condicion << std::endl;
}

void ArbolBPlus::insertar(const std::string& tabla, const std::vector<std::string>& columnas, const std::vector<std::string>& valores) {
    std::cout << "Ejecutando: INSERT INTO " << tabla << " (";
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i];
        if (i < columnas.size() - 1) std::cout << ", ";
    }
    std::cout << ") VALUES (";
    for (size_t i = 0; i < valores.size(); ++i) {
        std::cout << valores[i];
        if (i < valores.size() - 1) std::cout << ", ";
    }
    std::cout << ")\n";
}