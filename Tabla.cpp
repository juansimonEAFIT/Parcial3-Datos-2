#include "Tabla.h"
#include <iostream>
#include <algorithm>
#include <String>

// Constructor para inicializar la tabla con nombre y columnas
Tabla::Tabla(const std::string& nombre, const std::vector<std::string>& columnas)
    : nombre(nombre), columnas(columnas) {}

// Inserta una fila en la tabla
void Tabla::insertarFila(const std::vector<std::string>& fila) {
    filas.push_back(fila);
}

// Mostrar la tabla según ciertas columnas y condición


void Tabla::mostrarTabla(const std::vector<std::string>& columnas, const std::string& condicion) {
    std::cout << "Tabla: " << nombre << std::endl;
    std::cout << "Columnas: ";
    for (const auto& col : columnas) {
        std::cout << col << " ";
    }
    std::cout << std::endl;

    bool fila_mostrada = false;  // Bandera para verificar si se mostró alguna fila

    // Iterar sobre cada fila en la tabla
    for (const auto& fila : filas) {
        // Verificar si la fila cumple con la condición (si no hay condición, mostrar todas las filas)
        if (condicion.empty() || evaluarCondicion(fila, condicion)) {
            fila_mostrada = true;

            // Imprimir solo las columnas especificadas en el vector 'columnas'
            for (const auto& col : columnas) {
                auto it = std::find(this->columnas.begin(), this->columnas.end(), col);
                if (it != this->columnas.end()) {
                    size_t index = std::distance(this->columnas.begin(), it);
                    std::cout << fila[index] << " ";
                }
            }
            std::cout << std::endl; // Nueva línea después de cada fila
        }
    }

    if (!fila_mostrada) {
        std::cout << "No se encontraron filas que coincidan con la condición.\n";
    }
}



bool Tabla::evaluarCondicion(const std::vector<std::string>& fila, const std::string& condicion) {
    if (condicion.empty()) return true; // Sin condición, siempre es verdadero

    size_t pos = condicion.find('=');
    if (pos == std::string::npos) return false;

    std::string columna = limpiar(condicion.substr(0, pos));
    std::string valor = limpiar(condicion.substr(pos + 1));

    // Elimina comillas dobles si están alrededor del valor
    if (!valor.empty() && valor.front() == '"' && valor.back() == '"') {
        valor = valor.substr(1, valor.size() - 2);
    }

    // Buscar la columna en el vector de nombres de columnas
    auto it = std::find(this->columnas.begin(), this->columnas.end(), columna);
    if (it != this->columnas.end()) {
        size_t index = std::distance(this->columnas.begin(), it);
        return (index < fila.size() && fila[index] == valor);
    }
    return false;
}

std::string Tabla::limpiar(const std::string& cadena) {
    const char* espacios = " \t\n";
    size_t inicio = cadena.find_first_not_of(espacios);
    size_t fin = cadena.find_last_not_of(espacios);

    if (inicio == std::string::npos) {
        return "";  // Cadena vacía si solo tiene espacios
    }

    std::string resultado = cadena.substr(inicio, fin - inicio + 1);

    // Elimina comillas simples alrededor de la cadena si existen
    if (resultado.front() == '\'' && resultado.back() == '\'') {
        resultado = resultado.substr(1, resultado.size() - 2);
    }

    return resultado;
}

// Actualiza filas en la tabla que cumplan con la condición
void Tabla::actualizarTabla(const std::map<std::string, std::string>& asignaciones, const std::string& condicion) {
    for (auto& fila : filas) {
        if (evaluarCondicion(fila, condicion)) {
            for (const auto& asignacion : asignaciones) {
                auto it = std::find(columnas.begin(), columnas.end(), asignacion.first);
                if (it != columnas.end()) {
                    size_t index = std::distance(columnas.begin(), it);
                    fila[index] = asignacion.second;
                }
            }
        }
    }
}

// Elimina filas de la tabla que cumplan con la condición
void Tabla::eliminarFilas(const std::string& condicion) {
    filas.erase(std::remove_if(filas.begin(), filas.end(),
                               [this, &condicion](const std::vector<std::string>& fila) {
                                   return evaluarCondicion(fila, condicion);
                               }),
                filas.end());
}

// Sobrecarga del operador de salida para mostrar la tabla completa
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
