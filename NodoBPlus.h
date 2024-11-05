#ifndef NODOBPLUS_H
#define NODOBPLUS_H

#include <vector>
#include <string>

class NodoBPlus {
public:
    bool esHoja;
    std::vector<std::string> claves;
    std::vector<NodoBPlus*> hijos;
    NodoBPlus* siguiente;

    NodoBPlus(bool esHoja);
};

#endif // NODOBPLUS_H
