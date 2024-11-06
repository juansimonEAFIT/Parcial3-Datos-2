#ifndef ANALIZADOR_SQL_H
#define ANALIZADOR_SQL_H

#include "ArbolBPlus.h"
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

class AnalizadorSQL {
public:
    AnalizadorSQL(ArbolBPlus& arbol);
    void analizar(const std::string& comando);

private:
    ArbolBPlus& arbol;
    
    // Funciones de análisis para cada tipo de comando SQL
    void analizarCreateTable(std::istringstream& flujo);
    void analizarInsertar(std::istringstream& flujo);
    void analizarSeleccionar(std::istringstream& flujo);
    void analizarActualizar(std::istringstream& flujo);
    void analizarEliminar(std::istringstream& flujo);

    std::vector<std::string> procesarLista(const std::string& parte);
    std::map<std::string, std::string> procesarAsignaciones(const std::string& parte);
    std::string limpiar(const std::string& cadena);
    void analizarComandoExtendido(std::istringstream& flujo, const std::string& comando);
};

#endif
