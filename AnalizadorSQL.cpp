#include "AnalizadorSQL.h"
#include <iostream>
#include <regex>

AnalizadorSQL::AnalizadorSQL(ArbolBPlus& arbol) : arbol(arbol) {}

void AnalizadorSQL::analizar(const std::string& comando) {
    std::istringstream flujo(comando);
    std::string palabraClave;
    flujo >> palabraClave;

    std::transform(palabraClave.begin(), palabraClave.end(), palabraClave.begin(), ::tolower);

    if (palabraClave == "create") {
        analizarCreateTable(flujo);
    } else if (palabraClave == "insert") {
        analizarInsertar(flujo);
    } else if (palabraClave == "select") {
        analizarSeleccionar(flujo);
    } else if (palabraClave == "update") {
        analizarActualizar(flujo);
    } else if (palabraClave == "delete") {
        analizarEliminar(flujo);
    } else {
        std::cerr << "Comando no reconocido.\n";
    }
}

// Función para analizar el comando CREATE TABLE
void AnalizadorSQL::analizarCreateTable(std::istringstream& flujo) {
    std::string restoComando;
    std::getline(flujo, restoComando);

    std::regex createTableRegex(R"(\s*table\s+(\w+)\s*\(([^)]+)\)\s*)", std::regex::icase);
    std::smatch matches;

    if (std::regex_search(restoComando, matches, createTableRegex)) {
        std::string nombreTabla = matches[1].str();
        std::string columnasStr = matches[2].str();

        std::vector<std::string> columnas = procesarLista(columnasStr);
        arbol.createTable(nombreTabla, columnas);
    } else {
        std::cerr << "Error: Sintaxis incorrecta para CREATE TABLE.\n";
    }
}

// Función para analizar el comando INSERT
void AnalizadorSQL::analizarInsertar(std::istringstream& flujo) {
    std::string restoComando;
    std::getline(flujo, restoComando);

    std::regex insertRegex(R"(into\s+(\w+)\s*\(([^)]+)\)\s*values\s*\(([^)]+)\))", std::regex::icase);
    std::smatch matches;

    if (std::regex_search(restoComando, matches, insertRegex)) {
        std::string nombreTabla = matches[1].str();
        std::string columnasStr = matches[2].str();
        std::string valoresStr = matches[3].str();

        std::vector<std::string> columnas = procesarLista(columnasStr);
        std::vector<std::string> valores = procesarLista(valoresStr);

        arbol.insertar(nombreTabla, columnas, valores);
    } else {
        std::cerr << "Error: Sintaxis incorrecta para INSERT.\n";
    }
}

// Función para analizar el comando SELECT
void AnalizadorSQL::analizarSeleccionar(std::istringstream& flujo) {
    std::string restoComando;
    std::getline(flujo, restoComando);

    std::regex selectRegex(R"(\(([^)]+)\)\s*from\s+(\w+))", std::regex::icase);
    std::smatch matches;

    if (std::regex_search(restoComando, matches, selectRegex)) {
        std::string columnasStr = matches[1].str();
        std::string nombreTabla = matches[2].str();

        std::vector<std::string> columnas = procesarLista(columnasStr);
        arbol.seleccionar(nombreTabla, columnas);
    } else {
        std::cerr << "Error: Sintaxis incorrecta para SELECT.\n";
    }
}

// Función para analizar el comando UPDATE
void AnalizadorSQL::analizarActualizar(std::istringstream& flujo) {
    std::string restoComando;
    std::getline(flujo, restoComando);

    std::regex updateRegex(R"((\w+)\s+set\s+([^ ]+)\s+where\s+(.+))", std::regex::icase);
    std::smatch matches;

    if (std::regex_search(restoComando, matches, updateRegex)) {
        std::string nombreTabla = matches[1].str();
        std::string asignacionesStr = matches[2].str();
        std::string condicion = matches[3].str();

        std::map<std::string, std::string> asignaciones = procesarAsignaciones(asignacionesStr);
        arbol.actualizar(nombreTabla, asignaciones, condicion);
    } else {
        std::cerr << "Error: Sintaxis incorrecta para UPDATE.\n";
    }
}

// Función para analizar el comando DELETE
void AnalizadorSQL::analizarEliminar(std::istringstream& flujo) {
    std::string restoComando;
    std::getline(flujo, restoComando);

    std::regex deleteRegex(R"(from\s+(\w+)\s+where\s+(.+))", std::regex::icase);
    std::smatch matches;

    if (std::regex_search(restoComando, matches, deleteRegex)) {
        std::string nombreTabla = matches[1].str();
        std::string condicion = matches[2].str();

        arbol.eliminar(nombreTabla, condicion);
    } else {
        std::cerr << "Error: Sintaxis incorrecta para DELETE.\n";
    }
}

// Función auxiliar para procesar listas en formato item1, item2
std::vector<std::string> AnalizadorSQL::procesarLista(const std::string& parte) {
    std::vector<std::string> items;
    std::string item;
    std::istringstream flujo(parte);
    while (std::getline(flujo, item, ',')) {
        items.push_back(limpiar(item));
    }
    return items;
}

// Función auxiliar para procesar asignaciones en formato col=val, col=val
std::map<std::string, std::string> AnalizadorSQL::procesarAsignaciones(const std::string& parte) {
    std::map<std::string, std::string> asignaciones;
    std::string asignacion;
    std::istringstream flujo(parte);
    while (std::getline(flujo, asignacion, ',')) {
        auto pos = asignacion.find('=');
        if (pos != std::string::npos) {
            std::string columna = limpiar(asignacion.substr(0, pos));
            std::string valor = limpiar(asignacion.substr(pos + 1));
            asignaciones[columna] = valor;
        }
    }
    return asignaciones;
}

// Función auxiliar para eliminar espacios en blanco al inicio y final de una cadena
std::string AnalizadorSQL::limpiar(const std::string& cadena) {
    const char* espacios = " \t\n";
    size_t inicio = cadena.find_first_not_of(espacios);
    size_t fin = cadena.find_last_not_of(espacios);
    return inicio == std::string::npos ? "" : cadena.substr(inicio, fin - inicio + 1);
}
