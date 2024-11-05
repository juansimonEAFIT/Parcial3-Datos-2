#include "ArbolBPlus.h"
#include <iostream>

ArbolBPlus::ArbolBPlus(int grado) : grado(grado), raiz(nullptr) {}

// Implementación del método insertar
void ArbolBPlus::insertar(const std::string& tabla, const std::vector<std::string>& columnas, const std::vector<std::string>& valores) {
    std::string clave = valores[0]; // Suponiendo que la primera columna es la clave
    if (raiz == nullptr) {
        raiz = new NodoBPlus(true);
        raiz->claves.push_back(clave);
    } else {
        if (raiz->claves.size() == 2 * grado - 1) {
            NodoBPlus* nuevaRaiz = new NodoBPlus(false);
            nuevaRaiz->hijos.push_back(raiz);
            dividirNodo(nuevaRaiz, 0, raiz);
            insertarNoLleno(nuevaRaiz, clave);
            raiz = nuevaRaiz;
        } else {
            insertarNoLleno(raiz, clave);
        }
    }
}

void ArbolBPlus::dividirNodo(NodoBPlus* nodo, int indice, NodoBPlus* hijo) {
    NodoBPlus* nuevoNodo = new NodoBPlus(hijo->esHoja);
    nuevoNodo->claves.resize(grado - 1);
    for (int j = 0; j < grado - 1; ++j) {
        nuevoNodo->claves[j] = hijo->claves[j + grado];
    }
    if (!hijo->esHoja) {
        nuevoNodo->hijos.resize(grado);
        for (int j = 0; j < grado; ++j) {
            nuevoNodo->hijos[j] = hijo->hijos[j + grado];
        }
    }
    hijo->claves.resize(grado - 1);
    nodo->hijos.insert(nodo->hijos.begin() + indice + 1, nuevoNodo);
    nodo->claves.insert(nodo->claves.begin() + indice, hijo->claves[grado - 1]);
}

void ArbolBPlus::insertarNoLleno(NodoBPlus* nodo, const std::string& clave) {
    int i = nodo->claves.size() - 1;
    if (nodo->esHoja) {
        nodo->claves.push_back("");
        while (i >= 0 && clave < nodo->claves[i]) {
            nodo->claves[i + 1] = nodo->claves[i];
            --i;
        }
        nodo->claves[i + 1] = clave;
    } else {
        while (i >= 0 && clave < nodo->claves[i]) {
            --i;
        }
        ++i;
        if (nodo->hijos[i]->claves.size() == 2 * grado - 1) {
            dividirNodo(nodo, i, nodo->hijos[i]);
            if (clave > nodo->claves[i]) {
                ++i;
            }
        }
        insertarNoLleno(nodo->hijos[i], clave);
    }
}

// Implementación del método seleccionar
void ArbolBPlus::seleccionar(const std::string& tabla, const std::vector<std::string>& columnas) {
    std::cout << "Ejecutando: SELECT ";
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i];
        if (i < columnas.size() - 1) std::cout << ", ";
    }
    std::cout << " FROM " << tabla << std::endl;

    // Aquí se debería implementar la lógica para buscar y mostrar los datos seleccionados
    NodoBPlus* nodo = raiz;
    while (nodo != nullptr) {
        for (const auto& clave : nodo->claves) {
            std::cout << clave << " ";
        }
        nodo = nodo->siguiente;
    }
    std::cout << std::endl;
}

// Implementación del método actualizar
void ArbolBPlus::actualizar(const std::string& tabla, const std::map<std::string, std::string>& asignaciones, const std::string& condicion) {
    std::cout << "Ejecutando: UPDATE " << tabla << " SET ";
    size_t i = 0;
    for (const auto& asignacion : asignaciones) {
        std::cout << asignacion.first << " = " << asignacion.second;
        if (i < asignaciones.size() - 1) std::cout << ", ";
        ++i;
    }
    std::cout << " WHERE " << condicion << std::endl;

    // Aquí se debería implementar la lógica para buscar y actualizar los datos
    NodoBPlus* nodo = buscarNodo(raiz, condicion);
    if (nodo != nullptr) {
        for (auto& clave : nodo->claves) {
            if (clave == condicion) {
                for (const auto& asignacion : asignaciones) {
                    clave = asignacion.second; // Actualiza la clave con el nuevo valor
                }
            }
        }
    }
}

// Implementación del método eliminar
void ArbolBPlus::eliminar(const std::string& tabla, const std::string& condicion) {
    std::cout << "Ejecutando: DELETE FROM " << tabla << " WHERE " << condicion << std::endl;

    // Aquí se debería implementar la lógica para buscar y eliminar los datos
    eliminarClave(raiz, condicion);
}

// Función auxiliar para buscar un nodo en el árbol B+
NodoBPlus* ArbolBPlus::buscarNodo(NodoBPlus* nodo, const std::string& clave) {
    if (nodo == nullptr) return nullptr;

    int i = 0;
    while (i < nodo->claves.size() && clave > nodo->claves[i]) {
        ++i;
    }

    if (i < nodo->claves.size() && clave == nodo->claves[i]) {
        return nodo;
    }

    if (nodo->esHoja) {
        return nullptr;
    } else {
        return buscarNodo(nodo->hijos[i], clave);
    }
}

// Función auxiliar para eliminar una clave de un nodo en el árbol B+
void ArbolBPlus::eliminarClave(NodoBPlus* nodo, const std::string& clave) {
    if (nodo == nullptr) return;

    int i = 0;
    while (i < nodo->claves.size() && clave > nodo->claves[i]) {
        ++i;
    }

    if (i < nodo->claves.size() && clave == nodo->claves[i]) {
        nodo->claves.erase(nodo->claves.begin() + i);
        if (nodo->esHoja) {
            if (nodo->claves.empty() && nodo == raiz) {
                delete nodo;
                raiz = nullptr;
            }
        } else {
            // Implementar la lógica para manejar la eliminación en nodos internos
        }
    } else {
        if (!nodo->esHoja) {
            eliminarClave(nodo->hijos[i], clave);
        }
    }
}
