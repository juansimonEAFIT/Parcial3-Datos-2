#ifndef TABLA_H
#define TABLA_H

#include <string>
#include <vector>

struct Tabla {
    std::string nombre;
    std::vector<std::string> columnas;
    std::vector<std::vector<std::string>> filas;

    Tabla() = default;  // Constructor predeterminado
    Tabla(const std::string& nombre, const std::vector<std::string>& columnas);
};

#endif
