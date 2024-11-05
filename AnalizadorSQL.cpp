#include "AnalizadorSQL.h"
#include <iostream>

// Constructor de AnalizadorSQL que recibe un árbol B+ de referencia
AnalizadorSQL::AnalizadorSQL(ArbolBPlus& arbol) : arbol(arbol) {}

// Función principal para analizar el comando SQL y redirigirlo al método adecuado
void AnalizadorSQL::analizar(const std::string& comando) {
    std::istringstream flujo(comando);  // Flujo para dividir el comando en palabras clave
    std::string palabraClave;
    flujo >> palabraClave;  // Extrae la primera palabra clave (INSERT, SELECT, etc.)

    // Convierte la palabra clave a minúsculas para facilitar la comparación
    std::transform(palabraClave.begin(), palabraClave.end(), palabraClave.begin(), ::tolower);

    // Redirige el comando a la función adecuada según la palabra clave
    if (palabraClave == "insert") analizarInsertar(flujo);
    else if (palabraClave == "select") analizarSeleccionar(flujo);
    else if (palabraClave == "update") analizarActualizar(flujo);
    else if (palabraClave == "delete") analizarEliminar(flujo);
    else std::cout << "Comando no reconocido.\n";
}

// Función para analizar un comando INSERT
void AnalizadorSQL::analizarInsertar(std::istringstream& flujo) {
    std::string en, tabla, parteColumnas, parteValores;
    flujo >> en >> tabla >> parteColumnas >> parteValores;

    std::vector<std::string> columnas = procesarLista(parteColumnas);
    std::vector<std::string> valores = procesarLista(parteValores);

    arbol.insertar(tabla, columnas, valores);  // Ejecuta el comando en el árbol B+
}

// Función para analizar un comando SELECT
void AnalizadorSQL::analizarSeleccionar(std::istringstream& flujo) {
    std::string parteColumnas, desde, tabla;
    flujo >> parteColumnas >> desde >> tabla;

    std::vector<std::string> columnas = procesarLista(parteColumnas);
    arbol.seleccionar(tabla, columnas);  // Ejecuta el comando en el árbol B+
}

// Función para analizar un comando UPDATE
void AnalizadorSQL::analizarActualizar(std::istringstream& flujo) {
    std::string tabla, establecer, parteAsignaciones, donde, condicion;
    flujo >> tabla >> establecer >> parteAsignaciones >> donde >> condicion;

    std::map<std::string, std::string> asignaciones = procesarAsignaciones(parteAsignaciones);
    arbol.actualizar(tabla, asignaciones, condicion);  // Ejecuta el comando en el árbol B+
}

// Función para analizar un comando DELETE
void AnalizadorSQL::analizarEliminar(std::istringstream& flujo) {
    std::string desde, tabla, donde, condicion;
    flujo >> desde >> tabla >> donde >> condicion;

    arbol.eliminar(tabla, condicion);  // Ejecuta el comando en el árbol B+
}

// Función auxiliar para procesar listas en formato (item1,item2)
std::vector<std::string> AnalizadorSQL::procesarLista(const std::string& parte) {
    std::vector<std::string> items;
    std::string item;
    std::istringstream flujo(parte.substr(1, parte.size() - 2)); // Elimina paréntesis
    while (std::getline(flujo, item, ',')) {
        items.push_back(limpiar(item));
    }
    return items;
}

// Función auxiliar para procesar asignaciones en formato col=val,col=val
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
