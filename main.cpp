#include <iostream>        // Para entrada y salida estándar
#include <string>          // Para manejo de cadenas de texto
#include "ArbolBPlus.h"    // Encabezado del árbol B+, para operaciones SQL simuladas
#include "AnalizadorSQL.h" // Encabezado del analizador SQL, que interpreta comandos SQL

int main() {
    ArbolBPlus arbol;                 // Instancia de ArbolBPlus para manejar operaciones de SQL
    AnalizadorSQL analizador(arbol);  // Instancia de AnalizadorSQL que interpreta comandos

    std::string comando;
    while (true) {
        std::cout << "SQL> ";                // Indica al usuario que ingrese un comando
        std::getline(std::cin, comando);     // Lee el comando completo ingresado

        if (comando == "exit") break;        // Si el comando es "exit", finaliza el programa
        analizador.analizar(comando);        // Analiza y ejecuta el comando ingresado
    }

    return 0;
}
