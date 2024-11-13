#include "ArbolBPlus.h"
#include <iostream>
#include <algorithm>

ArbolBPlus::ArbolBPlus(int grado) : raiz(nullptr), orden(grado) {}

void ArbolBPlus::createTable(const std::string& nombre, const std::vector<std::string>& columnas) {
    if (tablas.find(nombre) != tablas.end()) {
        std::cerr << "Error: La tabla '" << nombre << "' ya existe." << std::endl;
        return;
    }

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

    std::cout << "Ejecutando: CREATE TABLE " << nombre << " (";
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i] << (i < columnas.size() - 1 ? ", " : "");
    }
    std::cout << ")\n";
}

void ArbolBPlus::dividirNodo(NodoBPlus* padre, int indiceHijo, NodoBPlus* hijo) {
    NodoBPlus* nuevoNodo = new NodoBPlus(hijo->esHoja);
    int totalKeys = hijo->claves.size();
    int splitIndex = totalKeys / 2;

    if (hijo->esHoja) {
        nuevoNodo->claves.assign(hijo->claves.begin() + splitIndex, hijo->claves.end());
        nuevoNodo->tablas.assign(hijo->tablas.begin() + splitIndex, hijo->tablas.end());
        hijo->claves.resize(splitIndex);
        hijo->tablas.resize(splitIndex);

        nuevoNodo->siguiente = hijo->siguiente;
        hijo->siguiente = nuevoNodo;

        std::string clavePromovida = nuevoNodo->claves.front();
        padre->claves.insert(padre->claves.begin() + indiceHijo, clavePromovida);
        padre->hijos.insert(padre->hijos.begin() + indiceHijo + 1, nuevoNodo);
    } else {
        std::string clavePromovida = hijo->claves[splitIndex];
        nuevoNodo->claves.assign(hijo->claves.begin() + splitIndex + 1, hijo->claves.end());
        nuevoNodo->hijos.assign(hijo->hijos.begin() + splitIndex + 1, hijo->hijos.end());
        hijo->claves.resize(splitIndex);
        hijo->hijos.resize(splitIndex + 1);

        padre->claves.insert(padre->claves.begin() + indiceHijo, clavePromovida);
        padre->hijos.insert(padre->hijos.begin() + indiceHijo + 1, nuevoNodo);
    }
}

void ArbolBPlus::insertarNoLleno(NodoBPlus* nodo, const std::string& clave, Tabla* tabla) {
    if (nodo->esHoja) {
        auto it = std::upper_bound(nodo->claves.begin(), nodo->claves.end(), clave);
        size_t pos = it - nodo->claves.begin();
        nodo->claves.insert(it, clave);
        nodo->tablas.insert(nodo->tablas.begin() + pos, tabla);
    } else {
        int i = nodo->claves.size() - 1;
        while (i >= 0 && clave < nodo->claves[i]) {
            i--;
        }
        i++;

        NodoBPlus* hijo = nodo->hijos[i];
        if (hijo->claves.size() == static_cast<size_t>(orden)) {
            dividirNodo(nodo, i, hijo);
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

void ArbolBPlus::seleccionar(const std::string& tabla, const std::vector<std::string>& columnas, const std::string& condicion) {
    std::cout << "Ejecutando: SELECT ";
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i] << (i < columnas.size() - 1 ? ", " : "");
    }
    std::cout << " FROM " << tabla;
    if (!condicion.empty()) std::cout << " WHERE " << condicion;
    std::cout << std::endl;

    auto it = tablas.find(tabla);
    if (it == tablas.end()) {
        std::cerr << "Error: La tabla '" << tabla << "' no existe." << std::endl;
        return;
    }
    it->second.mostrarTabla(columnas, condicion);
}

void ArbolBPlus::actualizar(const std::string& tabla, const std::map<std::string, std::string>& asignaciones, const std::string& condicion) {
    std::cout << "Ejecutando: UPDATE " << tabla << " SET ";
    size_t i = 0;
    for (const auto& asignacion : asignaciones) {
        std::cout << asignacion.first << " = " << asignacion.second;
        if (i < asignaciones.size() - 1) std::cout << ", ";
        ++i;
    }
    std::cout << " WHERE " << condicion << std::endl;

    auto it = tablas.find(tabla);
    if (it == tablas.end()) {
        std::cerr << "Error: La tabla '" << tabla << "' no existe." << std::endl;
        return;
    }
    it->second.actualizarTabla(asignaciones, condicion);
}

void ArbolBPlus::eliminar(const std::string& tabla, const std::string& condicion) {
    std::cout << "Ejecutando: DELETE FROM " << tabla << " WHERE " << condicion << std::endl;

    auto it = tablas.find(tabla);
    if (it == tablas.end()) {
        std::cerr << "Error: La tabla '" << tabla << "' no existe." << std::endl;
        return;
    }
    it->second.eliminarFilas(condicion);
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

    auto it = tablas.find(tabla);
    if (it == tablas.end()) {
        std::cerr << "Error: La tabla '" << tabla << "' no existe." << std::endl;
        return;
    }
    it->second.insertarFila(valores);
}
