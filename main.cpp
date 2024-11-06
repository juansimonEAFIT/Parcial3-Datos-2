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

    arbol.insertar("Clientes", {"ID", "Nombre", "Edad", "Ciudad"}, {"1", "Juan", "25", "CDMX"});
    arbol.insertar("Clientes", {"ID", "Nombre", "Edad", "Ciudad"}, {"2", "Ana", "30", "Guadalajara"});
    arbol.insertar("Clientes", {"ID", "Nombre", "Edad", "Ciudad"}, {"3", "Pedro", "40", "Monterrey"});
    arbol.insertar("Clientes", {"ID", "Nombre", "Edad", "Ciudad"}, {"4", "María", "35", "CDMX"});

    arbol.mostrarArbol();
    std::cout << "\nTabla original" << std::endl;
    arbol.seleccionar("Clientes", {"ID", "Nombre"});

    std::cout << "\nTabla actualizada 1" << std::endl;
    arbol.actualizar("Clientes", {{"Edad", "26"}}, "ID = 1");
    arbol.seleccionar("Clientes", {"ID", "Nombre", "Edad"});

    std::cout << "\nTabla actualizada 2" << std::endl;
    arbol.eliminar("Clientes", "ID = 2");
    arbol.seleccionar("Clientes", {"ID", "Nombre", "Edad"});


    return 0;
}
