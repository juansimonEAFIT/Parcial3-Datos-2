#include "ArbolBPlus.h"
#include "AnalizadorSQL.h"
#include <iostream>

int main() {
    ArbolBPlus arbol(3);
    AnalizadorSQL analizador(arbol);

    std::string comando;
    // while (true) {
    //     std::cout << "SQL> ";
    //     std::getline(std::cin, comando);

    //     if (comando == "exit") {
    //         std::cout << "Saliendo del programa.\n";
    //         break;
    //     }

    //     analizador.analizar(comando);
    // }

    arbol.createTable("Clientes", {"ID", "Nombre", "Edad", "Ciudad"});
    arbol.createTable("Productos", {"ID", "Nombre", "Precio"});
    arbol.createTable("Ventas", {"ID", "ID_Cliente", "ID_Producto", "Fecha"});
    arbol.mostrarArbol();

    return 0;
}
