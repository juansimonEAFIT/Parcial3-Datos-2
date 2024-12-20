#ifndef TABLA_H
#define TABLA_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

struct Tabla {
    std::string nombre;
    std::vector<std::string> columnas;
    std::vector<std::vector<std::string>> filas;

    Tabla() = default;  // Constructor predeterminado
    Tabla(const std::string& nombre, const std::vector<std::string>& columnas);

    void insertarFila(const std::vector<std::string>& fila);
    void mostrarTabla(const std::vector<std::string>& columnas, const std::string& condicion);
    void actualizarTabla(const std::map<std::string, std::string>& asignaciones, const std::string& condicion);
    void eliminarFilas(const std::string& condicion);
    bool evaluarCondicion(const std::vector<std::string>& fila, const std::string& condicion);
    static std::string limpiar(const std::string& cadena);
};

#endif
