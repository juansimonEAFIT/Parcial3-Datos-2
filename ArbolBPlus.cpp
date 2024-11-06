#include "ArbolBPlus.h"
#include <iostream>
#include <algorithm>

ArbolBPlus::ArbolBPlus(int grado) : raiz(nullptr), orden(grado) {}

// std::unordered_map<std::string, Tabla> tablas;

void ArbolBPlus::createTable(const std::string& nombre, const std::vector<std::string>& columnas) {
    if (tablas.find(nombre) != tablas.end()) {
        std::cerr << "Error: La tabla '" << nombre << "' ya existe." << std::endl;
        return;
    }

    // Crear la nueva tabla
    Tabla* nuevaTabla = new Tabla(nombre, columnas);

    if (raiz == nullptr) {
        raiz = new NodoBPlus(true);
        raiz->claves.push_back(nombre);
        raiz->tablas.push_back(nuevaTabla);
    } else {
        if (raiz->claves.size() == static_cast<size_t>(orden)) {
            NodoBPlus* nuevaRaiz = new NodoBPlus(false);
            nuevaRaiz->hijos.push_back(raiz);
            dividirNodo(nuevaRaiz, 0, raiz);
            raiz = nuevaRaiz;
        }
        insertarNoLleno(raiz, nombre, nuevaTabla);
    }
    tablas[nombre] = *nuevaTabla;

    // Mensaje de confirmación
    std::cout << "Ejecutando: CREATE TABLE " << nombre << " (";
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i] << (i < columnas.size() - 1 ? ", " : "");
    }
    std::cout << ")\n";
}



// Función para dividir un nodo lleno en dos y ajustar los hijos y claves en el nodo padre
void ArbolBPlus::dividirNodo(NodoBPlus* padre, int indiceHijo, NodoBPlus* hijo) {
    int maxClaves = orden;
    int minClaves = (orden + 1) / 2;
    NodoBPlus* nuevoNodo = new NodoBPlus(hijo->esHoja);

    int totalKeys = hijo->claves.size();
    int splitIndex = totalKeys / 2; // Punto de división

    // Para nodos hoja
    if (hijo->esHoja) {
        // Copiar la segunda mitad de las claves y tablas al nuevo nodo
        nuevoNodo->claves.assign(hijo->claves.begin() + splitIndex, hijo->claves.end());
        nuevoNodo->tablas.assign(hijo->tablas.begin() + splitIndex, hijo->tablas.end());

        // Redimensionar el nodo hijo
        hijo->claves.resize(splitIndex);
        hijo->tablas.resize(splitIndex);

        // Ajustar punteros de hojas
        nuevoNodo->siguiente = hijo->siguiente;
        hijo->siguiente = nuevoNodo;

        // Promover la primera clave del nuevo nodo
        std::string clavePromovida = nuevoNodo->claves.front();

        // Insertar clave promovida y nuevo nodo en el padre
        padre->claves.insert(padre->claves.begin() + indiceHijo, clavePromovida);
        padre->hijos.insert(padre->hijos.begin() + indiceHijo + 1, nuevoNodo);
    }
    // Para nodos internos
    else {
        // Promover la clave central al padre
        std::string clavePromovida = hijo->claves[splitIndex];

        // Copiar claves y hijos al nuevo nodo
        nuevoNodo->claves.assign(hijo->claves.begin() + splitIndex + 1, hijo->claves.end());
        nuevoNodo->hijos.assign(hijo->hijos.begin() + splitIndex + 1, hijo->hijos.end());

        // Redimensionar el nodo hijo
        hijo->claves.resize(splitIndex);
        hijo->hijos.resize(splitIndex + 1);

        // Insertar clave promovida y nuevo nodo en el padre
        padre->claves.insert(padre->claves.begin() + indiceHijo, clavePromovida);
        padre->hijos.insert(padre->hijos.begin() + indiceHijo + 1, nuevoNodo);
    }
}



// Inserción en un nodo no lleno
void ArbolBPlus::insertarNoLleno(NodoBPlus* nodo, const std::string& clave, Tabla* tabla) {
    if (nodo->esHoja) {
        // Encontrar la posición donde insertar la clave
        auto it = std::upper_bound(nodo->claves.begin(), nodo->claves.end(), clave);
        size_t pos = it - nodo->claves.begin();

        // Insertar la clave y la tabla
        nodo->claves.insert(it, clave);
        nodo->tablas.insert(nodo->tablas.begin() + pos, tabla);
    } else {
        // Encontrar el hijo apropiado para descender
        int i = nodo->claves.size() - 1;
        while (i >= 0 && clave < nodo->claves[i]) {
            i--;
        }
        i++;

        NodoBPlus* hijo = nodo->hijos[i];

        // Si el hijo está lleno, dividirlo
        if (hijo->claves.size() == static_cast<size_t>(orden)) {
            dividirNodo(nodo, i, hijo);

            // Después de dividir, determinar en qué hijo debemos insertar
            if (clave > nodo->claves[i]) {
                i++;
            }
        }
        insertarNoLleno(nodo->hijos[i], clave, tabla);
    }
}


void ArbolBPlus::mostrarArbol() {
    std::cout << "Árbol B+ con estructura jerárquica:\n";
    mostrarArbolAux(raiz, "", true);
}

void ArbolBPlus::mostrarArbolAux(NodoBPlus* nodo, std::string prefix, bool esUltimo) {
    if (!nodo) return;

    std::cout << prefix;
    std::cout << (esUltimo ? "└── " : "├── ");

    for (size_t i = 0; i < nodo->claves.size(); i++) {
        std::cout << nodo->claves[i];
        if (i < nodo->claves.size() - 1) {
            std::cout << " , ";
        }
    }
    std::cout << std::endl;

    if (!nodo->esHoja) {
        for (size_t i = 0; i < nodo->hijos.size(); i++) {
            mostrarArbolAux(nodo->hijos[i], prefix + (esUltimo ? "    " : "│   "), i == nodo->hijos.size() - 1);
        }
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