// tabla.cpp
#include "Tabla.h"

Tabla::Tabla(const std::string& nombre, const std::vector<std::string>& columnas)
    : nombre(nombre), columnas(columnas) {}

void Tabla::insertarFila(const std::vector<std::string>& fila) {
    filas.push_back(fila);
}

void Tabla::mostrarTabla(const std::vector<std::string>& columnas) {

    // Vector para encontrar los índices de las columnas buscadas
    std::vector<size_t> indices;
    for (const auto& columna : columnas) {
        auto it = std::find(this->columnas.begin(), this->columnas.end(), columna);
        if (it != this->columnas.end()) {
            indices.push_back(std::distance(this->columnas.begin(), it));
        }
    }

    // Muestra el nombre de la tabla
    std::cout << "Tabla: " << nombre << std::endl;
    std::cout << "Columnas: ";

    // Muestra las columnas seleccionadas
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i];
        if (i < columnas.size() - 1) std::cout << ", ";
    }
    
    std::cout << std::endl;

    // Muestra los datos de la tabla
    for (const auto& fila : filas) {
        for (size_t i = 0; i < indices.size(); ++i) {
            std::cout << fila[indices[i]];
            if (i < indices.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }

    // std::cout << "Tabla: " << nombre << std::endl;

    // std::cout << "Columnas: ";
    
    // for (size_t i = 0; i < columnas.size(); ++i) {
    //     std::cout << columnas[i];
    //     if (i < columnas.size() - 1) std::cout << ", ";
    // }
    // std::cout << std::endl;

    // for (const auto& fila : filas) {
    //     for (size_t i = 0; i < columnas.size(); ++i) {
    //         std::cout << fila[i];
    //         if (i < fila.size() - 1) std::cout << ", ";
    //     }
    //     std::cout << std::endl;
    // }
}

void Tabla::actualizarTabla(const std::map<std::string, std::string>& asignaciones, const std::string& condicion) {
    for (auto& fila : filas) {
        if (condicion.empty() || fila[0] == condicion) {
            for (const auto& asignacion : asignaciones) {
                auto it = std::find(columnas.begin(), columnas.end(), asignacion.first);
                if (it != columnas.end()) {
                    fila[std::distance(columnas.begin(), it)] = asignacion.second;
                }
            }
        }
    }
}

void Tabla::eliminarFilas(const std::string& condicion) {
    filas.erase(std::remove_if(filas.begin(), filas.end(), [&condicion](const std::vector<std::string>& fila) {
        return condicion.empty() || fila[0] == condicion;
    }), filas.end());
}

std::ostream& operator<<(std::ostream& os, const Tabla& tabla) {
    os << "Tabla: " << tabla.nombre << std::endl;
    os << "Columnas: ";
    for (size_t i = 0; i < tabla.columnas.size(); ++i) {
        os << tabla.columnas[i];
        if (i < tabla.columnas.size() - 1) os << ", ";
    }
    os << std::endl;

    for (const auto& fila : tabla.filas) {
        for (size_t i = 0; i < fila.size(); ++i) {
            os << fila[i];
            if (i < fila.size() - 1) os << ", ";
        }
        os << std::endl;
    }

    return os;
}