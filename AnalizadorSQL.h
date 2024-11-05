#ifndef ANALIZADOR_SQL_H
#define ANALIZADOR_SQL_H

#include "ArbolBPlus.h"  // Biblioteca del árbol B+, para operaciones SQL simuladas
#include <string>        // Para manejo de cadenas de texto (std::string)
#include <vector>        // Para manejo de listas de elementos (std::vector)
#include <map>           // Para pares clave-valor en las asignaciones (std::map)
#include <sstream>       // Para manipulación de flujo de texto (std::istringstream)
#include <algorithm>     // Para operaciones de transformación (std::transform)

// Clase AnalizadorSQL analiza comandos SQL y utiliza ArbolBPlus para ejecutar cada comando
class AnalizadorSQL {
public:
    // Constructor de AnalizadorSQL que recibe una referencia al árbol B+
    AnalizadorSQL(ArbolBPlus& arbol);

    // Función principal para analizar y procesar el comando SQL recibido
    void analizar(const std::string& comando);

private:
    ArbolBPlus& arbol;  // Referencia al árbol B+ para ejecutar comandos SQL

    // Funciones privadas que analizan comandos SQL específicos y los descomponen en parámetros
    void analizarInsertar(std::istringstream& flujo);
    void analizarSeleccionar(std::istringstream& flujo);
    void analizarActualizar(std::istringstream& flujo);
    void analizarEliminar(std::istringstream& flujo);

    // Funciones auxiliares para procesar listas de columnas/valores y asignaciones
    std::vector<std::string> procesarLista(const std::string& parte);
    std::map<std::string, std::string> procesarAsignaciones(const std::string& parte);
    std::string limpiar(const std::string& cadena);  // Función para limpiar espacios en blanco
};

#endif
